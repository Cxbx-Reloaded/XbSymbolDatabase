// TODO: Fix SPDX license in util/helper.hpp down to MIT
// TODO: Fix license in XbSymbolDatabase down to MIT
// SPDX-License-Identifier: GPL-2.0-or-later

// SPDX-FileCopyrightText: 2019 RadWolfie

// SimpleIni library is licensed to MIT
// xxHash library is licensed to BSD-2-Clause

#include <clocale>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <string>
// TODO: Need fix multi-threading
// Known bug from XbSymbolDatabase:
// * Console log appear to only output one at a time from one thread to next.
// * Sometimes get error'd for certain libraries. Some sort of conflict occurred.
//#define ENABLE_MULTI_THREAD
#ifdef ENABLE_MULTI_THREAD
#include <thread>
#endif

#include <libXbSymbolDatabase.h>
#include <xref/list_xref.h>
#include <SimpleIni.h>
#include <xxhash.h>

bool operator==(const CSimpleIni::Entry& i, const CSimpleIni::Entry& ii)
{
    return std::strcmp(i.pItem, ii.pItem) == 0;
}

#include "Xbe.h"
#include "util/helper.hpp"
#include "libverify.hpp"
#include "util/cliConfig.hpp"

#define _128_MiB 0x08000000

std::map<uint32_t, symbol_result> g_SymbolAddresses;
std::ios_base::fmtflags cout_fmt = std::cout.flags();
unsigned int XbSDB_test_error = 0;
unsigned int XbUnitTest_error = 0;

static const char* cli_argument_str = "> XbSymbolUnitTest"
                                      " [-h|--help]"
                                      " default.xbe"
                                      " [-out|--out <output to specific folder>]"
                                      " [-f]"
                                      " [-v|--verbose]\n";

#define UNITTEST_OK 0
#define UNITTEST_FAIL_INVALID_ARG 1
#define UNITTEST_FAIL_XBSDB 2
#define UNITTEST_FAIL_OPEN_FILE 3
#define UNITTEST_FAIL_INVALID_XBE 4
#define UNITTEST_FAIL_UNABLE_ALLOC_MEM 5
#define UNITTEST_FAIL_SYMBOLS_NOT_FOUND 6
#define UNITTEST_FAIL_SYMBOLS_DIFF_SIZE 7
#define UNITTEST_FAIL_SYMBOLS_NOT_MATCH 8
#define UNITTEST_FAIL_DATABASE_NOT_SYNC 9

// Buffer generation result in case user want to save as cache file.
// Which will be use to compare against generated cache result.
CSimpleIni gen_result(false, true, false);

static const char* section_XbSDb_messages = "XbSDb Messages";
static const char* section_XbSUT_messages = "XbSUT Messages";
static struct {
    const char* unknown = "UNKNOWN";
    const char* warn = "WARN";
    const char* error = "ERROR";
} sect_generic_messages;

static const char* section_certificate = "Certificate";
static struct {
    const char* name = "Name";
    const char* TitleID = "TitleID";
    const char* TitleIDHex = "TitleIDHex";
    const char* Region = "Region";
} sect_certificate;

static const char* section_libs = "Libs";
static struct {
    const char* BuildVersion = "BuildVersion";
    const char* DSOUND = "DSOUND";
    const char* JVS = "JVS";
} sect_libs;

static void pause_for_user_input(void)
{
    std::cout << "Press 'enter' key to continue...";
    (void)std::getchar();
}

static int invalid_argument(int argc, char** argv)
{
    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("Input correct usage argument as described below.\n") + cli_argument_str);

#if _DEBUG
    // Verbose ARG output test
    while (argc > 0) {
        argc--;
        std::cout << "ARG" << argc << ": " << argv[argc] << "\n";
    }
#endif

    pause_for_user_input();
    return UNITTEST_FAIL_INVALID_ARG;
}

static void help_argument(void)
{
    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, std::string("Usage arguments:\n") + cli_argument_str);
}

static int output_result_XbSDb(void)
{
    std::cout << "XbSymbolDatabase Test: ";
    if (XbSDB_test_error == 0) {
        std::cout << "PASS\n";
        return UNITTEST_OK;
    }

    std::cout << "FAIL - " << XbSDB_test_error << " errors\n";
    return UNITTEST_FAIL_XBSDB;
}

// Add arguments here that are valid to use within application.
cli_config::argtype cliArgValidate(const std::string& arg)
{
    using cli_config::argtype;

    // Output to folder
    if (arg == "out") {
        return argtype::pair;
    }
    // request cli argument details
    else if (arg == "h") {
        return argtype::single;
    }
    else if (arg == "help") {
        return argtype::single;
    }
    // Force overwrite existing file
    else if (arg == "f") {
        return argtype::single;
    }
    // verbose mode
    else if (arg == "v") {
        return argtype::single;
    }
    else if (arg == "verbose") {
        return argtype::single;
    }
    return argtype::unknown;
}

template<bool doCache>
void Generic_OutputMessage(xb_output_message mFlag, const char* section, const std::string& message)
{
    switch (mFlag) {
        case XB_OUTPUT_MESSAGE_INFO: {
            std::cout << "INFO   : " << message << std::endl;
            break;
        }
        case XB_OUTPUT_MESSAGE_WARN: {
            std::cout << "WARNING: " << message << std::endl;
            if constexpr (doCache) {
                gen_result.SetValue(section, sect_generic_messages.warn, message.c_str());
            }
            break;
        }
        case XB_OUTPUT_MESSAGE_ERROR: {
            std::cout << "ERROR  : " << message << std::endl;
            if constexpr (doCache) {
                gen_result.SetValue(section, sect_generic_messages.error, message.c_str());
            }
            break;
        }
        case XB_OUTPUT_MESSAGE_DEBUG: {
            std::cout << "DEBUG  : " << message << std::endl;
            break;
        }
        default: {
            std::cout << "UNKNOWN: " << message << std::endl;
            if constexpr (doCache) {
                gen_result.SetValue(section, sect_generic_messages.unknown, message.c_str());
            }
            break;
        }
    }
}
template void Generic_OutputMessage<true>(xb_output_message mFlag, const char* section, const std::string& message);
template void Generic_OutputMessage<false>(xb_output_message mFlag, const char* section, const std::string& message);

static void XbSDb_OutputMessage(xb_output_message mFlag, const char* message)
{
    Generic_OutputMessage<true>(mFlag, section_XbSDb_messages, message);
}

void Custom_OutputMessage(xb_output_message mFlag, const std::string& section, const std::string& key, const std::string& value)
{
    const std::string message = key + " = " + value;
    switch (mFlag) {
        case XB_OUTPUT_MESSAGE_INFO: {
            std::cout << "INFO   : " << message << "\n";
            break;
        }
        case XB_OUTPUT_MESSAGE_WARN: {
            std::cout << "WARNING: " << message << "\n";
            break;
        }
        case XB_OUTPUT_MESSAGE_ERROR: {
            std::cout << "ERROR  : " << message << "\n";
            break;
        }
        case XB_OUTPUT_MESSAGE_DEBUG: {
            std::cout << "DEBUG  : " << message << "\n";
            break;
        }
        default: {
            std::cout << "UNKNOWN: " << message << "\n";
            break;
        }
    }
    gen_result.SetValue(section.c_str(), key.c_str(), value.c_str());
}

static void EmuRegisterSymbol(const char* library_str,
                       uint32_t library_flag,
                       uint32_t xref_index,
                       const char* symbol_str,
                       uint32_t func_addr,
                       uint32_t build)
{
    // Report invalid index
    if (xref_index == -1) {
        std::cout
            << "ERROR  : Symbol could not be register due to xref index is -1: "
            << XbSymbolDatabase_LibraryToString(library_flag) << " (b"
            << std::dec << std::setfill('0') << std::setw(4) << build << ") 0x"
            << std::setfill('0') << std::setw(8) << std::hex << func_addr
            << " -> " << symbol_str << "\n";
        XbUnitTest_error++;
        return;
    }
    // Ignore kernel indexes
    if (xref_index <= XREF_KT_COUNT) {
        // TODO: Should we output a warning or info message about kernel thunk
        // being output?
        return;
    }

    // Ignore registered symbol in current database.
    symbol_result hasSymbol = g_SymbolAddresses[xref_index];

    if (hasSymbol.addr != 0) {
        // But check if symbol name is different from xref entry.
        if (hasSymbol.symbol != symbol_str) {
            std::cout
                << "ERROR  : Symbol names returned for same xref index: \n"
                << XbSymbolDatabase_LibraryToString(hasSymbol.library_flag)
                << " (b" << std::dec << std::setfill('0') << std::setw(4)
                << hasSymbol.build << ") 0x" << std::setfill('0')
                << std::setw(8) << std::hex << hasSymbol.addr << " -> "
                << hasSymbol.symbol << "\nvs\n"
                << XbSymbolDatabase_LibraryToString(library_flag) << " (b"
                << std::dec << std::setfill('0') << std::setw(4) << build
                << ") 0x" << std::setfill('0') << std::setw(8) << std::hex
                << func_addr << " -> " << symbol_str << "\n";
            XbUnitTest_error++;
        }
        return;
    }

#ifdef _DEBUG
    // Output some details
    std::cout << "[" << std::setw(8) << std::hex << std::this_thread::get_id()
              << "] Symbol Detected: "
              << XbSymbolDatabase_LibraryToString(library_flag) << " (b"
              << std::dec << std::setfill('0') << std::setw(4) << build
              << ") 0x" << std::setfill('0') << std::setw(8) << std::hex
              << func_addr << " -> " << symbol_str << "\n";
    std::cout.flags(cout_fmt);
#endif
    hasSymbol.addr = func_addr;
    hasSymbol.build = build;
    hasSymbol.library_flag = library_flag;
    hasSymbol.symbol = symbol_str;

    g_SymbolAddresses[xref_index] = hasSymbol;
}

static xb_xbe_type GetXbeType(const xbe_header* pXbeHeader)
{
    // Detect if the XBE is for Chihiro (Untested!) :
    // This is based on
    // https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L29
    if ((pXbeHeader->dwEntryAddr & 0xf0000000) == 0x40000000) {
        return XB_XBE_TYPE_CHIHIRO;
    }

    // Check for Debug XBE, using high bit of the kernel thunk address :
    // (DO NOT test like
    // https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L33
    // !)
    if ((pXbeHeader->dwKernelImageThunkAddr & 0x80000000) > 0) {
        return XB_XBE_TYPE_DEBUG;
    }

    // Otherwise, the XBE is a Retail build :
    return XB_XBE_TYPE_RETAIL;
}

static bool VerifyXbeIsBuiltWithXDK(const xbe_header* pXbeHeader,
                             lib_versions& lib_vers,
                             std::filesystem::path path_xbe)
{
    size_t xb_start_addr =
        reinterpret_cast<size_t>(pXbeHeader) - pXbeHeader->dwBaseAddr;
    xbe_library_version* pLibraryVersion = nullptr;
    xbe_certificate* pCertificate = nullptr;
    xbe_section_header* pSections = nullptr;

    //
    // initialize Microsoft XDK scanning
    //

    if (pXbeHeader->dwMagic != FourCC("HEBX")) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Xbe does not have valid magic!");
        return false;
    }

    if (pXbeHeader->pLibraryVersionsAddr != 0) {
        pLibraryVersion = reinterpret_cast<xbe_library_version*>(
            xb_start_addr + pXbeHeader->pLibraryVersionsAddr);
    }
    else {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Xbe does not contain library versions!");
        return false;
    }

    if (pXbeHeader->pCertificateAddr != 0) {
        pCertificate = reinterpret_cast<xbe_certificate*>(
            xb_start_addr + pXbeHeader->pCertificateAddr);
    }
    else {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Xbe does not contain certificate pointer!");
        return false;
    }

    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Detected Microsoft XDK application...");

    uint16_t buildVersion = 0;
    pSections = reinterpret_cast<xbe_section_header*>(
        xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    uint32_t sectionSize = pXbeHeader->dwSections;
    const char* section_str;

    // Output Symbol Database version
    std::cout << "XbSymbolDatabase_LibraryVersion: "
              << XbSymbolDatabase_LibraryVersion() << "\n";

    // Store Certificate Details
    const std::string& title_name = getXbeTitle(pXbeHeader);
    std::cout << "Name                  : " << title_name << "\n";
    gen_result.SetValue(section_certificate, sect_certificate.name, title_name.c_str());
    const std::string& title_id = FormatTitleId(pCertificate->dwTitleId);
    std::cout << "TitleID               : " << title_id << "\n";
    std::cout << "TitleIDHex            : 0x" << std::hex << pCertificate->dwTitleId << "\n";
    gen_result.SetValue(section_certificate, sect_certificate.TitleID, title_id.c_str());
    gen_result.SetLongValue(section_certificate, sect_certificate.TitleIDHex, pCertificate->dwTitleId, nullptr, true);
    std::cout << "Region                : 0x" << std::hex << pCertificate->dwGameRegion << "\n";
    gen_result.SetLongValue(section_certificate, sect_certificate.Region, pCertificate->dwGameRegion, nullptr, true);

    // Hash the loaded XBE's header, use it as a filename
    std::cout << "Xbe header hash       : " << getXbeHeaderHash(pXbeHeader) << "\n";
    std::cout.flags(cout_fmt);

    // Store Library Details
    for (uint32_t i = 0; i < pXbeHeader->dwLibraryVersions; i++) {
        const std::string LibraryName(pLibraryVersion[i].szName,
                                      pLibraryVersion[i].szName + 8);
        const std::string BuildVersion = std::to_string(pLibraryVersion[i].wBuildVersion) + "." + std::to_string(pLibraryVersion[i].wFlags.QFEVersion);
        std::cout << "Library Name[" << std::setw(2) << i
                  << "]      : " << LibraryName << " (b" << BuildVersion << ")\n";
        gen_result.SetValue(section_libs, LibraryName.c_str(), BuildVersion.c_str());

        if (buildVersion < pLibraryVersion[i].wBuildVersion) {
            buildVersion = pLibraryVersion[i].wBuildVersion;
        }

        // Translate string to flag for quicker assignment.
        uint32_t lib_flag = XbSymbolDatabase_LibraryToFlag(LibraryName.c_str());
        switch (lib_flag) {
            case XbSymbolLib_D3D8:
                lib_vers.d3d8 = pLibraryVersion[i].wBuildVersion;
                break;
            case XbSymbolLib_D3D8LTCG:
                lib_vers.d3d8ltcg = pLibraryVersion[i].wBuildVersion;
                break;
#if 0
            case XbSymbolLib_D3DX8:
                lib_vers.d3dx8 = pLibraryVersion[i].wBuildVersion;
                break;
#endif
            case XbSymbolLib_DSOUND:
                lib_vers.dsound = pLibraryVersion[i].wBuildVersion;
                break;
            case XbSymbolLib_XACTENG:
                lib_vers.xacteng = pLibraryVersion[i].wBuildVersion;
                break;
            case XbSymbolLib_XAPILIB:
                lib_vers.xapilib = pLibraryVersion[i].wBuildVersion;
                break;
            case XbSymbolLib_XGRAPHC:
                lib_vers.xgraphic = pLibraryVersion[i].wBuildVersion;
                break;
            case XbSymbolLib_XNET:
            case XbSymbolLib_XNETN:
            case XbSymbolLib_XNETS:
                lib_vers.xnet = pLibraryVersion[i].wBuildVersion;
                // Technically, it is combined with XONLINE library. So, check
                // if XONLINE doesn't exist then force check.
                if (!lib_vers.xonline) {
                    lib_vers.xonline = pLibraryVersion[i].wBuildVersion;
                }
                break;
            case XbSymbolLib_XONLINE:
            case XbSymbolLib_XONLINES:
            case XbSymbolLib_XONLINLS:
                lib_vers.xonline = pLibraryVersion[i].wBuildVersion;
                // Technically, it is combined with XNET library. So, check if
                // XNET doesn't exist then force check.
                if (!lib_vers.xnet) {
                    lib_vers.xnet = pLibraryVersion[i].wBuildVersion;
                }
                break;
        }
    }
    std::cout.flags(cout_fmt);

    // Check if DSOUND library is not found then do force verify.
    // So far this only occur in XDK 4039 build.
    if (!lib_vers.dsound) {
        // Force verify if DSOUND section do exist, then append.
        for (unsigned int i = 0; i < sectionSize; i++) {
            section_str = reinterpret_cast<const char*>(
                xb_start_addr + pSections[i].SectionNameAddr);

            if (std::strncmp(section_str, Lib_DSOUND, 8) == 0) {
                lib_vers.dsound = buildVersion;
                std::cout << "Library Name[ ?]      : DSOUND   (b" << buildVersion << ")\n";
                gen_result.SetLongValue(section_libs, sect_libs.DSOUND, buildVersion);
                break;
            }
        }
    }

    // Force verify if title is chihiro or contains "boot.id" folder, then append.
    if (GetXbeType(pXbeHeader) == XB_XBE_TYPE_CHIHIRO ||
        std::filesystem::exists(path_xbe.parent_path() / "boot.id")) {
        lib_vers.jvs = buildVersion;
        //                                    XAPILIB  (
        std::cout << "Library Name[ ?]      : JVS      (b" << buildVersion << ")\n";
        gen_result.SetLongValue(section_libs, sect_libs.JVS, buildVersion);
    }

    std::cout << "BuildVersion          : " << buildVersion << "\n";
        gen_result.SetLongValue(section_libs, sect_libs.BuildVersion, buildVersion);

    std::cout << "\n";
    return true;
}


static bool GetXbSymbolDatabaseFilters(const xbe_header* pXbeHeader,
                                bool is_raw,
                                XbSDBLibraryHeader& library_output,
                                XbSDBSectionHeader& section_output)
{
    std::string error_msg = "unknown";

    library_output.count =
        XbSymbolDatabase_GenerateLibraryFilter(pXbeHeader, nullptr);

    if (library_output.count != 0) {
        library_output.filters = new XbSDBLibrary[library_output.count];
    }
    else {
        error_msg = "library_input.count variable return 0.";
        goto scanError;
    }

    if (library_output.filters == nullptr) {
        error_msg =
            "Unable to allocate buffer for library_input.filters variable.";
        goto scanError;
    }

    (void)XbSymbolDatabase_GenerateLibraryFilter(pXbeHeader, &library_output);

    section_output.count =
        XbSymbolDatabase_GenerateSectionFilter(pXbeHeader, nullptr, is_raw);

    if (section_output.count != 0) {
        section_output.filters = new XbSDBSection[section_output.count];
    }
    else {
        error_msg = "section_input.count variable return 0.";
        goto scanError;
    }

    if (section_output.filters == nullptr) {
        error_msg =
            "Unable to allocate buffer for section_input.filters variable.";
        goto scanError;
    }

    (void)XbSymbolDatabase_GenerateSectionFilter(pXbeHeader, &section_output, is_raw);
    return true;

scanError:
    if (library_output.filters) {
        delete[] library_output.filters;
        library_output.filters = nullptr;
    }

    if (section_output.filters) {
        delete[] section_output.filters;
        section_output.filters = nullptr;
    }

    XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "GetXbSymbolDatabaseFilters failed for: " + error_msg);
    pause_for_user_input();
    return false;
}

static bool VerifyXbSymbolDatabaseFilters(const xbe_header* pXbeHeader)
{
    XbSDBLibraryHeader library_input = {};
    XbSDBSectionHeader section_input = {};

    std::cout << "Getting library and section filters...\n";

    if (!GetXbSymbolDatabaseFilters(pXbeHeader, true, library_input, section_input)) {
        return false;
    }

    // Verbose both library and section filters.
    std::cout << "Outputting library filters...\n";

    unsigned int i;
    for (i = 0; i < library_input.count; i++) {
        std::stringstream str_format;
        str_format << "Library[" << i << "]\n    name    = "
                   << std::string().assign(library_input.filters[i].name, 0, 8)
                   << ";\n    build   = " << std::dec
                   << library_input.filters[i].build_version
                   << ";\n    qre ver = 0x" << std::hex
                   << library_input.filters[i].qfe_version
                   << ";\n    flag    = 0x" << std::hex
                   << library_input.filters[i].flag << ";\n";
        std::cout << str_format.str();
    }

    std::cout << "\nOutputting section filters...\n";

    for (i = 0; i < section_input.count; i++) {
        std::stringstream str_format;
        str_format << "Section[" << i << "]\n     name        = "
                   << std::string().assign(section_input.filters[i].name, 0, 8)
                   << ";\n     virt addr   = 0x" << std::hex
                   << section_input.filters[i].xb_virt_addr
                   << ";\n     buffer addr = 0x" << std::hex
                   << section_input.filters[i].buffer_lower
                   << ";\n     buffer size = 0x" << std::hex
                   << section_input.filters[i].buffer_size << ";\n";
        std::cout << str_format.str();
    }

    delete[] library_input.filters;
    delete[] section_input.filters;

    std::cout << "\n";

    return true;
}

static void ScanXbe(const xbe_header* pXbeHeader, bool is_raw)
{
    std::string error_msg = "unknown";

    // Ensure nothing is still in g_SymbolAddresses before new scan process
    // start.
    g_SymbolAddresses.clear();

    XbSymbolContextHandle pHandle;
    XbSDBLibraryHeader library_input = {};
    XbSDBSectionHeader section_input = {};

    if (!GetXbSymbolDatabaseFilters(pXbeHeader, is_raw, library_input, section_input)) {
        return;
    }

#ifdef ENABLE_MULTI_THREAD
    std::vector<std::thread> threads;
    auto ScanLibraryFunc = [](XbSymbolContextHandle pHandle,
                              const XbSDBLibrary* library) -> void {
        unsigned int LastUnResolvedXRefs = 0, CurrentUnResolvedXRefs = 0;
        bool xref_first_pass =
            true; // Set to true for search speed optimization
        do {
            LastUnResolvedXRefs = CurrentUnResolvedXRefs;

            // Start library scan against symbol database we want to
            // search for address of symbols and xreferences.
            CurrentUnResolvedXRefs +=
                XbSymbolContext_ScanLibrary(pHandle, library, xref_first_pass);

            xref_first_pass = false;
        } while (LastUnResolvedXRefs < CurrentUnResolvedXRefs);
    };
#endif

    xbaddr kt_addr = XbSymbolDatabase_GetKernelThunkAddress(pXbeHeader);

    if (!XbSymbolDatabase_CreateXbSymbolContext(&pHandle, EmuRegisterSymbol, library_input, section_input, kt_addr)) {
        error_msg = "Unable to create XbSymbolContext handle.";
        goto scanError;
    }

    // delete[] library_input.filters;
    // library_input.filters = nullptr;
    delete[] section_input.filters;
    section_input.filters = nullptr;

    // For output various false detection messages.
    XbSymbolContext_SetBypassBuildVersionLimit(pHandle, true);
    XbSymbolContext_SetContinuousSigScan(pHandle, true);
    XbSymbolContext_SetFirstDetectAddressOnly(pHandle, true);

    XbSymbolContext_ScanManual(pHandle);

    // TODO: Replace below to use XbSymbolContext_ScanLibrary function to speed
    // up scan process. Either by replace toolset to CLANG or wait until MSVC
    // support C11 standard. Perhaps use macro to detect compiler selection?
    // Then toggle between the two.
#ifndef ENABLE_MULTI_THREAD
     XbSymbolContext_ScanAllLibraryFilter(pHandle);
#else
    for (unsigned i = 0; i < library_input.count; i++) {
        threads.emplace_back(
            std::thread(ScanLibraryFunc, pHandle, &library_input.filters[i]));
    }

    for (auto& thread : threads) {
        thread.join();
    }
#endif
    delete[] library_input.filters;
    library_input.filters = nullptr;

    XbSymbolContext_RegisterXRefs(pHandle);

    XbSymbolContext_Release(pHandle);

    std::cout << "\n";

    return;

scanError:
    if (library_input.filters) {
        delete[] library_input.filters;
    }

    if (section_input.filters) {
        delete[] section_input.filters;
    }

    XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "ScanXbe failed for: " + error_msg);
    pause_for_user_input();
}

static int run_test_raw(const xbe_header* pXbeHeader)
{
    std::cout << "Scanning raw xbe file...\n";

    ScanXbe(pXbeHeader, true);

    std::cout << "Scanning raw xbe file... COMPLETE!\n";

    return UNITTEST_OK;
}

static int run_test_virtual(const xbe_header* pXbeHeader, const uint8_t* xbe_data)
{
    void* xb_environment = std::calloc(_128_MiB, 1);

    if (xb_environment == (void*)0) {
        std::cout
            << "ERROR: Unable to allocate 128 MiB of virtual xbox memory!\n";
        pause_for_user_input();
        return UNITTEST_FAIL_UNABLE_ALLOC_MEM;
    }

    std::cout << "Loading sections into virtual xbox memory...\n";

    std::memcpy((uint8_t*)xb_environment + pXbeHeader->dwBaseAddr, pXbeHeader, sizeof(xbe_header));

    if (sizeof(xbe_header) < pXbeHeader->dwSizeofHeaders) {

        uint32_t extra_size = pXbeHeader->dwSizeofHeaders - sizeof(xbe_header);
        std::memcpy((uint8_t*)xb_environment + pXbeHeader->dwBaseAddr +
                        sizeof(xbe_header),
                    (uint8_t*)xbe_data + sizeof(xbe_header),
                    extra_size);
    }

    xbe_section_header* pSectionHeaders =
        (xbe_section_header*)((uint8_t*)xb_environment +
                              pXbeHeader->pSectionHeadersAddr);

    // Load sections into virtualize xbox memory
    for (uint32_t s = 0; s < pXbeHeader->dwSections; s++) {

        if (pSectionHeaders[s].dwFlags.bPreload) {

            if (pSectionHeaders[s].dwVirtualAddr +
                    pSectionHeaders[s].dwVirtualSize >
                _128_MiB) {
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "section request virtual size allocation "
                                                             "outside 128MiB "
                                                             "range, skipping...");
                continue;
            }

            if (pSectionHeaders[s].dwVirtualAddr +
                    pSectionHeaders[s].dwSizeofRaw >
                _128_MiB) {
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "section request raw size allocation "
                                                             "outside 128MiB "
                                                             "range, skipping...");
                continue;
            }

            std::memset((uint8_t*)xb_environment +
                            pSectionHeaders[s].dwVirtualAddr,
                        0,
                        pSectionHeaders[s].dwVirtualSize);

            std::memcpy((uint8_t*)xb_environment +
                            pSectionHeaders[s].dwVirtualAddr,
                        xbe_data + pSectionHeaders[s].dwRawAddr,
                        pSectionHeaders[s].dwSizeofRaw);

            // Let XbSymbolDatabase know this section is loaded.
            pSectionHeaders[s].dwSectionRefCount++;
            std::cout << "Section preloaded: "
                      << (const char*)((uint8_t*)xb_environment +
                                       pSectionHeaders[s].SectionNameAddr)
                      << "\n";
        }
    }

    std::cout << "Scanning virtual xbox environment...\n";

    ScanXbe((xbe_header*)((uint8_t*)xb_environment + pXbeHeader->dwBaseAddr),
            false);

    std::free(xb_environment);

    std::cout << "Scanning virtual xbox environment... COMPLETE!\n";

    return UNITTEST_OK;
}

int main(int argc, char** argv)
{
    std::setlocale(LC_ALL, "en_US.utf8");
    std::string xbe_path;
    int test_ret = UNITTEST_OK;

    cli_config::SetArgTypeValidateCallback(cliArgValidate);

    // Check for valid args then make valid key/value binds.
    if (!cli_config::GenConfig(argv, argc)) {
        return invalid_argument(argc, argv);
    }

    // Check if user request for help detail.
    if (cli_config::hasKey("h") || cli_config::hasKey("help")) {
        help_argument();
        return UNITTEST_OK;
    }

    // Get xbe's file path even if it's not given.
    cli_config::GetValue(cli_config::filepath, &xbe_path);

    xb_output_message xbsdb_output = XB_OUTPUT_MESSAGE_INFO;
    if (cli_config::hasKey("v") || cli_config::hasKey("verbose")) {
        xbsdb_output = XB_OUTPUT_MESSAGE_DEBUG;
    }

    XbSymbolDatabase_SetOutputVerbosity(xbsdb_output);
    XbSymbolDatabase_SetOutputMessage(XbSDb_OutputMessage);
    XbSDB_test_error = XbSymbolDatabase_TestOOVPAs();

    std::cout << "Total symbols in XbSymbolDatabase: "
              << XbSymbolDatabase_GetTotalSymbols(XbSymbolLib_ALL) << "\n";

    // Perform self test to verify all symbol registers are validated.
    if (!run_test_verify_libraries()) {
        // If not, do not allow to run unit test until this is resolve first.
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Databases from libXbSymbolDatabase and XbSymbolUnitTest are not in sync!");
        pause_for_user_input();
        return UNITTEST_FAIL_DATABASE_NOT_SYNC;
    }

    // Do not process xbe test verification if file path is not given.
    if (xbe_path.empty()) {
        test_ret = output_result_XbSDb();
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_INFO, "No file path to xbe given, unit test end.");
        return test_ret;
    }

    std::ifstream xbeFile = std::ifstream(xbe_path, std::ios::binary);
    if (!xbeFile.is_open()) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Unable to open the file!");
        pause_for_user_input();
        return UNITTEST_FAIL_OPEN_FILE;
    }

    std::string fileData = std::string(std::istreambuf_iterator<char>(xbeFile),
                                       std::istreambuf_iterator<char>());
    std::cout << "File size: " << fileData.size() << " byte(s).\n";

    const uint8_t* xbe_data =
        reinterpret_cast<const uint8_t*>(fileData.data());

    const xbe_header* pXbeHeader =
        reinterpret_cast<const xbe_header*>(xbe_data);

    // Buffer generation result in case user want to save as cache file.
    // Which will be use to compare against generated cache result.
    gen_result.Reset();

    lib_versions lib_vers{};

    if (!VerifyXbeIsBuiltWithXDK(pXbeHeader, lib_vers, xbe_path)) {
        pause_for_user_input();
        return UNITTEST_FAIL_INVALID_XBE;
    }

    // Force results, XbSDb, and XbSUT Messages sections to near top for cache file usage.
    gen_result.SetValue(results_str.c_str(), nullptr, nullptr);
    gen_result.SetValue(section_XbSDb_messages, nullptr, nullptr);
    gen_result.SetValue(section_XbSUT_messages, nullptr, nullptr);

    if (!VerifyXbSymbolDatabaseFilters(pXbeHeader)) {
        pause_for_user_input();
        return UNITTEST_FAIL_INVALID_XBE;
    }
    std::string gen_result_temp;
    gen_result.Save(gen_result_temp);

    test_ret = run_test_raw(pXbeHeader);
    if (test_ret != UNITTEST_OK) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Raw test failed!");
        pause_for_user_input();
        return test_ret;
    }

    std::cout << "\n";

    std::map<uint32_t, symbol_result> g_SymbolAddressesRaw = g_SymbolAddresses;
    // Clear raw's results since we're only keeping virtual's results.
    gen_result.Reset();
    // Retrieve verification data after run raw test.
    gen_result.LoadData(gen_result_temp);

    test_ret = run_test_virtual(pXbeHeader, xbe_data);
    if (test_ret != UNITTEST_OK) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Virtual test failed!");
        pause_for_user_input();
        return test_ret;
    }

    std::cout << "\n";

    std::cout << "Verifying symbols registered...\n";

    // Ensure both raw and simulated xbox environment do have symbols detected.
    if (g_SymbolAddresses.size() == 0 || g_SymbolAddressesRaw.size() == 0) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Symbols are not detected!");
        pause_for_user_input();
        return UNITTEST_FAIL_SYMBOLS_NOT_FOUND;
    }

    // Then check both raw and simulated do indeed have same size.
    if (g_SymbolAddresses.size() != g_SymbolAddressesRaw.size()) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Registered symbols are not even; Raw xbe: " + std::to_string(g_SymbolAddressesRaw.size()) + " - Sim xbox: " + std::to_string(g_SymbolAddresses.size()));

        // Remove all identical symbols
        for (const auto& xref : g_SymbolAddresses) {
            g_SymbolAddressesRaw.erase(xref.first);
        }
        for (const auto& xref : g_SymbolAddressesRaw) {
            g_SymbolAddresses.erase(xref.first);
        }

        // Now report what's missing compared to other.
        for (const auto& xref : g_SymbolAddresses) {
            std::cout << "ERROR  : g_SymbolAddressesRaw is missing "
                      << XbSymbolDatabase_LibraryToString(xref.second.library_flag)
                      << " (b" << std::dec << std::setfill('0') << std::setw(4)
                      << xref.second.build
                      << ") 0x" << std::hex << std::setfill('0') << std::setw(8)
                      << xref.second.addr
                      << " -> " << xref.second.symbol << "\n";
        }
        for (const auto& xref : g_SymbolAddressesRaw) {
            std::cout << "ERROR  : g_SymbolAddresses is missing "
                      << XbSymbolDatabase_LibraryToString(xref.second.library_flag)
                      << " (b" << std::dec << std::setfill('0') << std::setw(4)
                      << xref.second.build
                      << ") 0x" << std::hex << std::setfill('0') << std::setw(8)
                      << xref.second.addr
                      << " -> " << xref.second.symbol << "\n";
        }

        pause_for_user_input();
        return UNITTEST_FAIL_SYMBOLS_DIFF_SIZE;
    }
    else {
        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Symbol registered size...OK!");
    }

    // Finally, check each string and addresses are the same.
    if (!std::equal(g_SymbolAddresses.begin(), g_SymbolAddresses.end(), g_SymbolAddressesRaw.begin())) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Symbol registered does not match raw vs virtual xbox.");
        pause_for_user_input();
        return UNITTEST_FAIL_SYMBOLS_NOT_MATCH;
    }
    else {
        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Symbol registered matching...OK!");
    }

    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Scanning xbe file is completed.");
    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Verifying detected symbols against unit test's symbols...\n");

    unsigned full_lib_count = 0;
    size_t error_count = 0;
    run_test_verify_symbols(lib_vers, g_SymbolAddresses, full_lib_count, error_count);

    // Append internal errors such as EmuRegisterSymbol function's result.
    error_count += XbUnitTest_error;

    if (error_count) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_WARN, "XbSymbolUnitTest: FAIL - " + std::to_string(error_count) + " errors");
    }

    // Check for out argument has input to store symbols cache and results to a folder.
    if (!cli_config::hasKey("out")) {
        if (cli_config::hasKey("f")) {
            XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_WARN, "-f argument require --out argument.");
        }
    }
    else {
        // Verify output folder is not empty.
        std::string output_dir;
        (void)cli_config::GetValue("out", &output_dir);
        if (output_dir.empty()) {
            XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "--out argument require input value.");
            return invalid_argument(argc, argv);
        }

        std::filesystem::path output_path = output_dir;
        // Check if directory do not exist.
        if (!std::filesystem::exists(output_path)) {
            // Check if parent directory do not exist.
            if (!std::filesystem::exists(output_path.parent_path())) {
                // Since parent directory do not exist, then path to output directory was not created.
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Output directory does not exist!");
                return invalid_argument(argc, argv);
            }
            // Check if we are able to create directory.
            std::error_code err;
            if (!std::filesystem::create_directory(output_path, err)) {
                XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Unable to create directory, error code: " + err.message());
                return invalid_argument(argc, argv);
            }
        }

        bool doSave = true;
        auto XbeTitle = getXbeTitle(pXbeHeader);
        PurgeBadChar(XbeTitle);
        std::filesystem::path file_name = XbeTitle + "-" + getXbeHeaderHash(pXbeHeader) + ".ini";
        // Since output directory do exist, check if we have existing cache file.
        std::filesystem::path cache_file = output_path / file_name;
        if (std::filesystem::exists(cache_file)) {
            // If does exist, then we want to compare the difference between generated to cached results.
            CSimpleIni cache_result(false, true, false);
            cache_result.LoadFile(cache_file.c_str());

            // use local storage to re-use allocated memory.
            CSimpleIni::TNamesDepend cache_sections;
            CSimpleIni::TNamesDepend cache_keys;
            CSimpleIni::TNamesDepend cache_values;
            CSimpleIni::TNamesDepend gen_sections;
            CSimpleIni::TNamesDepend gen_keys;
            CSimpleIni::TNamesDepend gen_values;

            size_t local_error_count = 0;

            // Check for any missing data may not be included in generated and cache contents.
            gen_result.GetAllSections(gen_sections);
            cache_result.GetAllSections(cache_sections);
            for (auto gSection = gen_sections.begin(); gSection != gen_sections.end();) {
                const auto& foundSection = std::find(cache_sections.begin(), cache_sections.end(), *gSection);
                if (foundSection == cache_sections.end()) {
                    gSection++;
                    continue;
                }
                // Get list of keys in a section.
                gen_result.GetAllKeys(gSection->pItem, gen_keys);
                cache_result.GetAllKeys(gSection->pItem, cache_keys);

                // Search through generated keys
                for (auto gKey = gen_keys.begin(); gKey != gen_keys.end();) {
                    const auto& foundKey = std::find(cache_keys.begin(), cache_keys.end(), *gKey);
                    if (foundKey == cache_keys.end()) {
                        gKey++;
                        continue;
                    }
                    // Get all values from a key.
                    gen_result.GetAllValues(gSection->pItem, gKey->pItem, gen_values);
                    cache_result.GetAllValues(gSection->pItem, gKey->pItem, cache_values);

                    // Search through generated values
                    for (auto gValue = gen_values.begin(); gValue != gen_values.end();) {
                        const auto& foundValue = std::find(cache_values.begin(), cache_values.end(), *gValue);
                        // Skip if not found.
                        if (foundValue == cache_values.end()) {
                            gValue++;
                            continue;
                        }

                        // Remove found value from list to avoid being report.
                        gValue = gen_values.erase(gValue);
                        cache_values.erase(foundValue);
                    }
                    // output which values has not been found
                    local_error_count += gen_values.size() + cache_values.size();
                    for (const auto& gValue : gen_values) {
                        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("cache file does not have [") + gSection->pItem + "] " + gKey->pItem + " = \"" + gValue.pItem + "\" value!");
                    }
                    for (const auto& cValue : cache_values) {
                        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("generated result does not have [") + gSection->pItem + "] " + gKey->pItem + " = \"" + cValue.pItem + "\" value!");
                    }

                    // Remove found key from list to avoid being report.
                    gKey = gen_keys.erase(gKey);
                    cache_keys.erase(foundKey);
                }

                // output which keys has not been found
                local_error_count += gen_keys.size() + cache_keys.size();
                for (const auto& gKey : gen_keys) {
                    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("cache file does not have [") + gSection->pItem + "] " + gKey.pItem + " key!");
                    gen_result.GetAllValues(gSection->pItem, gKey.pItem, gen_values);
                    local_error_count += gen_values.size();
                    for (const auto& gValue : gen_values) {
                        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("cache file does not have [") + gSection->pItem + "] " + gKey.pItem + " = \"" + gValue.pItem + "\" value!");
                    }
                }
                for (const auto& cKey : cache_keys) {
                    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("generated result does not have [") + gSection->pItem + "] " + cKey.pItem + " key!");
                    cache_result.GetAllValues(gSection->pItem, cKey.pItem, cache_values);
                    local_error_count += cache_values.size();
                    for (const auto& cValue : cache_values) {
                        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("generated result does not have [") + gSection->pItem + "] " + cKey.pItem + " = \"" + cValue.pItem + "\" value!");
                    }
                }

                // Remove found section from list to avoid being report.
                gSection = gen_sections.erase(gSection);
                cache_sections.erase(foundSection);
            }

            // output which sections has not been found
            local_error_count += gen_sections.size() + cache_sections.size();
            for (const auto& gSection : gen_sections) {
                XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("cache file does not have [") + gSection.pItem + "] section!");
                gen_result.GetAllKeys(gSection.pItem, gen_keys);
                for (const auto& gKey : gen_keys) {
                    gen_result.GetAllValues(gSection.pItem, gKey.pItem, gen_values);
                    local_error_count += gen_values.size();
                    for (const auto& gValue : gen_values) {
                        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("cache file does not have [") + gSection.pItem + "] " + gKey.pItem + " = \"" + gValue.pItem + "\" value!");
                    }
                }
            }
            for (const auto& cSection : cache_sections) {
                XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("generated result does not have [") + cSection.pItem + "] section!");
                cache_result.GetAllKeys(cSection.pItem, cache_keys);
                for (const auto& cKey : cache_keys) {
                    cache_result.GetAllValues(cSection.pItem, cKey.pItem, cache_values);
                    local_error_count += cache_values.size();
                    for (const auto& cValue : cache_values) {
                        XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, std::string("generated result does not have [") + cSection.pItem + "] " + cKey.pItem + " = \"" + cValue.pItem + "\" value!");
                    }
                }
            }

            if (local_error_count) {
                XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_ERROR, "XbSymbolUnitTest: FAIL - " + std::to_string(local_error_count) + " errors; generated result does not match with cache file!");
                error_count++;
            }

            // Check force overwrite argument exist
            if (!cli_config::hasKey("f")) {
                doSave = false;
            }
        }
        // Check if we want save to cache file.
        if (doSave) {
            gen_result.SaveFile(cache_file.c_str(), false);
        }
    }

    if (full_lib_count) {
        XbSUT_OutputMessage(XB_OUTPUT_MESSAGE_INFO, "XbSymbolUnitTest: Total of " + std::to_string(full_lib_count) + " full libraries found");
    }

    test_ret = output_result_XbSDb();

    XbSUT_OutputMessage<false>(XB_OUTPUT_MESSAGE_INFO, "Unit test end.");

    if (error_count) {
        pause_for_user_input();
    }

    return test_ret;
}

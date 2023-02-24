// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// ******************************************************************
// *
// *   XbSymbolDatabase.c
// *
// *  XbSymbolDatabase is free software; you can redistribute them
// *  and/or modify them under the terms of the GNU General Public
// *  License as published by the Free Software Foundation; either
// *  version 2 of the license, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// *  GNU General Public License for more details.
// *
// *  You should have recieved a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// *
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *  (c) 2016-2018 Luke Usher
// *  (c) 2016-2017 PatrickvL
// *  (c) 2017-2019 RadWolfie
// *  (c) 2017-2018 jarupxx
// *  (c) 2018 x1nixmzeng
// *
// *  All rights reserved
// *
// ******************************************************************
#define _XBOXKRNL_DEFEXTRN_

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h> // for static_assert

#ifdef _MSC_VER
#include <intrin.h>
static inline uint32_t BitScanReverse(uint32_t value)
{
    unsigned long index;
    if (!_BitScanReverse(&index, value)) {
        return 32;
    }
    return index;
}
#elif __GNUC__
static inline uint32_t BitScanReverse(uint32_t value)
{
    if (value == 0) {
        return 32;
    }
    return 31 - __builtin_clz(value);
}
#else
#error Unsupported platform
#endif

// ******************************************************************
// * Xbox Symbol Database
// ******************************************************************

#include "libXbSymbolDatabase.h"
#include "Xbe.h"

// __COUNTER__ is currently suppported for msvc, gcc, and clang
#define SYMBOL_COUNTER_VALUE __COUNTER__

// ******************************************************************
// * Xbox Symbol OOVPA Database
// ******************************************************************

#include <xref/list_xref.h>
#include "Xapi_OOVPA.inl"
#include "D3D8_OOVPA.inl"
#include "D3D8LTCG_OOVPA.inl"
#include "DSound_OOVPA.inl"
#include "JVS_OOVPA.inl"
#include "XGraphic_OOVPA.inl"
#include "XNet_OOVPA.inl"
#include "XOnline_OOVPA.inl"
#include "XActEng_OOVPA.inl"

#define PAIRSCANSEC_MAX 4

typedef uint8_t* memptr_t;

typedef struct _OutputHandler {
    xb_output_message verbose_level;
    xb_output_message_t func;
} OutputHandler;

// Library Type is a requirement to prevent another thread
// doing the same scan process.
typedef enum _eLibraryType {
    LT_UNKNOWN = -1,
    LT_KERNEL = 0,
    LT_D3D,
    LT_AUDIO,
    LT_JVS,
    LT_XAPI,
    LT_GRAPHIC,
    LT_NETWORK,
    LT_MAX,
    LT_COUNT = LT_MAX
} eLibraryType;

typedef enum _eScanStage {
    SS_NONE = 0,
    SS_1_MANUAL,
    SS_2_SCAN_LIBS,
} eScanStage;

typedef struct _iXbSymbolLibraryContext {
    uint32_t xref_registered;
    bool is_active;
} iXbSymbolLibraryContext;

typedef struct _iXbSymbolLibrarySession {
    const XbSDBLibrary* pLibrary;
    eLibraryType iLibraryType;
} iXbSymbolLibrarySession;

typedef struct _iXbSymbolContext {
    bool strict_build_version_limit;
    bool one_time_scan;
    bool scan_first_detect;
    uint32_t library_filter;
    xbaddr xref_database[XREF_COUNT];
    OutputHandler output;
    xb_symbol_register_t register_func;
    XbSDBLibraryHeader library_input;
    XbSDBSectionHeader section_input;
    eScanStage scan_stage;
    iXbSymbolLibraryContext library_contexts[LT_COUNT];
} iXbSymbolContext;

typedef const struct _PairScanLibSec {
    uint32_t library;
    const char* section[PAIRSCANSEC_MAX];
} PairScanLibSec;

typedef const struct _SymbolDatabaseList {
    PairScanLibSec LibSec;

    OOVPATable* SymbolsTable;
    unsigned int SymbolsTableCount;
} SymbolDatabaseList;

typedef bool (*custom_scan_func_t)(iXbSymbolContext* pContext,
                                   const iXbSymbolLibrarySession* pLibrarySession,
                                   SymbolDatabaseList* pLibraryDB,
                                   const XbSDBSection* pSection);

SymbolDatabaseList SymbolDBList[] = {
    // Support inline functions in .text section
    { XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG, { Sec_text, Sec_D3D, Sec_FLASHROM }, D3D8_OOVPA, D3D8_OOVPA_COUNT },

    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    { XbSymbolLib_D3D8LTCG, { Sec_text, Sec_D3D }, D3D8LTCG_OOVPA, D3D8LTCG_OOVPA_COUNT },

    // NOTE: Likely is a D3D Helper library.
    // Jarupxx mention this is not a requirement?
    //{ Lib_D3DX8, { Sec_D3DX }, _OOVPA, _OOVPA_COUNT },

    // Only used for manual scan purpose as a workaround since both FLASHROM
    // and text section will lead to false detection for non-manual signatures, see comment below.
    { XbSymbolLib_DSOUND, { Sec_DSOUND, Sec_rdata, Sec_FLASHROM, Sec_text }, DSound_OOVPA_manual, DSound_OOVPA_manual_COUNT },

    // NOTE: By adding FLASHROM to scan section may will lead false detection.
    // Since some symbols has very short asm codes.
    { XbSymbolLib_DSOUND, { Sec_DSOUND, Sec_rdata, Sec_FLASHROM }, DSound_OOVPA, DSound_OOVPA_COUNT },

    // DSOUNDH is just meant to define hot fix, there is no separate section
    //{ XbSymbolLib_DSOUNDH, { Sec_DSOUND }, &DSound_OOVPA, DSound_OOVPA_COUNT },

    // Only used in Chihiro applications
    { XbSymbolLib_JVS, { Sec_text, Sec_XPP, Sec_FLASHROM }, JVSLIB_OOVPA, JVSLIB_OOVPA_COUNT },

    //
    { XbSymbolLib_XACTENG, { Sec_XACTENG, Sec_FLASHROM }, XACTENG_OOVPA, XACTENG_OOVPA_COUNT },

    // test case: Power Drome (Unluckily, it use LTCG version of the library.)
    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    //{ XbSymbolLib_XACTENLT, { Sec_XACTENG }, XACTENGLT_OOVPA, XACTENGLT_OOVPA_COUNT },

    //
    { XbSymbolLib_XAPILIB, { Sec_text, Sec_XPP, Sec_FLASHROM }, XAPILIB_OOVPA, XAPILIB_OOVPA_COUNT },

    // Support inline functions in .text section
    { XbSymbolLib_XGRAPHC, { Sec_text, Sec_XGRPH, Sec_FLASHROM }, XGRAPHC_OOVPA, XGRAPHC_OOVPA_COUNT },

    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    //{ XbSymbolLib_XGRAPHCL, { Sec_XGRPH }, XGRAPHCL_OOVPA, XGRAPHCL_OOVPA_COUNT },

    // Added Sec_text and Sec_XNET just in case.
    // TODO: Do we need to keep Sec_XNET in here?
    // TODO: Need to find out which function is only part of XOnlines.
    // Fun fact, XONLINES are split into 2 header sections.
    { XbSymbolLib_XONLINE | XbSymbolLib_XONLINES | XbSymbolLib_XONLINLS, { Sec_text, Sec_XONLINE, Sec_XNET, Sec_FLASHROM }, XONLINE_OOVPA, XONLINE_OOVPA_COUNT },

    // Added Sec_text just in case.
    // TODO: Need to find out which function is only part of XNets.
    // XNETS only has XNET, might be true.
    // XNETN's test case: Stake
    { XbSymbolLib_XNET | XbSymbolLib_XNETS | XbSymbolLib_XNETN | XbSymbolLib_XONLINE | XbSymbolLib_XONLINES | XbSymbolLib_XONLINLS, { Sec_text, Sec_XNET, Sec_FLASHROM }, XNET_OOVPA, XNET_OOVPA_COUNT },
};

// ******************************************************************
// * SymbolDBListCount
// ******************************************************************
const unsigned int SymbolDBListCount = XBSDB_ARRAY_SIZE(SymbolDBList);

const char SectionList[][8] = {
    Sec_text,
    Sec_FLASHROM,
    Sec_rdata,
    Sec_D3D,
    Sec_D3DX,
    Sec_DSOUND,
    Sec_XACTENG,
    Sec_XID,
    Sec_XPP,
    Sec_XPPDat,
    Sec_XGRPH,
    Sec_XONLINE,
    Sec_XNET
};

const unsigned int SectionListTotal = XBSDB_ARRAY_SIZE(SectionList);

#if _DEBUG
xb_output_message g_output_verbose_level = XB_OUTPUT_MESSAGE_DEBUG;
#else
xb_output_message g_output_verbose_level = XB_OUTPUT_MESSAGE_INFO;
#endif

// Intended for send the message as-is without formating.
// (To avoid corrupted string when perform a bad coding.
//  Plus certain message need special character without format.)
void output_message(OutputHandler* pOutput, xb_output_message mLevel, const char* message)
{
    // Check if output function is set.
    // Plus if pass minimum verbose level to output.
    if (pOutput->func != NULL && mLevel >= pOutput->verbose_level) {
        pOutput->func(mLevel, message);
    }
}

// Intended to format the message with given extra parameters.
void output_message_format(OutputHandler* pOutput, xb_output_message mLevel, const char* format, ...)
{
    char bufferTemp[2048];

    // Check if output function is set.
    // Plus if pass minimum verbose level to output.
    if (pOutput->func != NULL && mLevel >= pOutput->verbose_level) {
        va_list args;
        va_start(args, format);
        (void)vsprintf(bufferTemp, format, args);
        va_end(args);

        pOutput->func(mLevel, bufferTemp);
    }
}

// ported from Dxbx's XbeExplorer
static xb_xbe_type GetXbeType(const xbe_header* pXbeHeader)
{
    // Detect if the XBE is for Chihiro (Untested!) :
    // This is based on https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L29
    if ((pXbeHeader->dwEntryAddr & 0xf0000000) == 0x40000000) {
        return XB_XBE_TYPE_CHIHIRO;
    }

    // Check for Debug XBE, using high bit of the kernel thunk address :
    // (DO NOT test like https://github.com/radare/radare2/blob/7ffe2599a192bf5b9333560345f80dd97f096277/libr/bin/p/bin_xbe.c#L33 !)
    if ((pXbeHeader->dwKernelImageThunkAddr & 0x80000000) > 0) {
        return XB_XBE_TYPE_DEBUG;
    }

    // Otherwise, the XBE is a Retail build :
    return XB_XBE_TYPE_RETAIL;
}

static bool iXbSymbolContext_AllowSetParameter(iXbSymbolContext* pContext)
{
    bool bRet = (pContext->scan_stage == SS_NONE);

    if (!bRet) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Cannot set parameter value after first and during scan call.");
    }

    return bRet;
}

static bool iXbSymbolContext_AllowScanLibrary(iXbSymbolContext* pContext)
{
    bool bRet = (pContext->scan_stage == SS_2_SCAN_LIBS);

    if (!bRet) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "XbSymbolContext_ScanManual must be call first before scan for library's symbols.");
    }

    return bRet;
}

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

#include "internal_functions.h"


// ******************************************************************
// * global API functions
// ******************************************************************

xb_output_message_t g_output_func = NULL;
void XbSymbolDatabase_SetOutputMessage(xb_output_message_t message_func)
{
    g_output_func = message_func;
}

bool XbSymbolDatabase_SetOutputVerbosity(xb_output_message verbose_level)
{
    if (verbose_level < XB_OUTPUT_MESSAGE_MAX) {
        g_output_verbose_level = verbose_level;
        return true;
    }
    // Return false only when requested level is invalid.
    return false;
}

const char* XbSymbolDatabase_LibraryToString(uint32_t library_flag)
{
    switch (library_flag) {
        case XbSymbolLib_D3D8: {
            return Lib_D3D8;
        }
        case XbSymbolLib_D3D8LTCG: {
            return Lib_D3D8LTCG;
        }
        case XbSymbolLib_D3DX8: {
            return Lib_D3DX8;
        }
        case XbSymbolLib_DSOUND: {
            return Lib_DSOUND;
        }
        case XbSymbolLib_JVS: {
            return Lib_JVS;
        }
        case XbSymbolLib_XACTENG: {
            return Lib_XACTENG;
        }
        case XbSymbolLib_XAPILIB: {
            return Lib_XAPILIB;
        }
        case XbSymbolLib_XGRAPHC: {
            return Lib_XGRAPHC;
        }
        case XbSymbolLib_XNET: {
            return Lib_XNET;
        }
        case XbSymbolLib_XNETN: {
            return Lib_XNETN;
        }
        case XbSymbolLib_XNETS: {
            return Lib_XNETS;
        }
        case XbSymbolLib_XONLINE: {
            return Lib_XONLINE;
        }
        case XbSymbolLib_XONLINES: {
            return Lib_XONLINES;
        }
        case XbSymbolLib_XONLINLS: {
            return Lib_XONLINLS;
        }
        default: {
            return Lib_UNKNOWN;
        }
    }
}

// NOTE: Library string must return only one specific flag, cannot make a mix combo flags.
//       Otherwise, internal scan and XbSymbolDatabase_LibraryToString will not function correctly.
uint32_t XbSymbolDatabase_LibraryToFlag(const char* library_name)
{
    if (strncmp(library_name, Lib_D3D8, 8) == 0) {
        return XbSymbolLib_D3D8;
    }
    if (strncmp(library_name, Lib_D3D8LTCG, 8) == 0) {
        return XbSymbolLib_D3D8LTCG;
    }
    if (strncmp(library_name, Lib_D3DX8, 8) == 0) {
        return XbSymbolLib_D3DX8;
    }
    if (strncmp(library_name, Lib_DSOUND, 8) == 0) {
        return XbSymbolLib_DSOUND;
    }
    if (strncmp(library_name, Lib_JVS, 8) == 0) {
        return XbSymbolLib_JVS;
    }
    if (strncmp(library_name, Lib_XACTENG, 8) == 0) {
        return XbSymbolLib_XACTENG;
    }
    if (strncmp(library_name, Lib_XAPILIB, 8) == 0) {
        return XbSymbolLib_XAPILIB;
    }
    if (strncmp(library_name, Lib_XGRAPHC, 8) == 0) {
        return XbSymbolLib_XGRAPHC;
    }
    if (strncmp(library_name, Lib_XNET, 8) == 0) {
        return XbSymbolLib_XNET;
    }
    if (strncmp(library_name, Lib_XNETN, 8) == 0) {
        return XbSymbolLib_XNETN;
    }
    if (strncmp(library_name, Lib_XNETS, 8) == 0) {
        return XbSymbolLib_XNETS;
    }
    if (strncmp(library_name, Lib_XONLINE, 8) == 0) {
        return XbSymbolLib_XONLINE;
    }
    if (strncmp(library_name, Lib_XONLINES, 8) == 0) {
        return XbSymbolLib_XONLINES;
    }
    if (strncmp(library_name, Lib_XONLINLS, 8) == 0) {
        return XbSymbolLib_XONLINLS;
    }
    return 0;
}

uint32_t XbSymbolDatabase_GetLibraryDependencies(uint32_t library_flag, XbSDBLibraryHeader library_filters)
{
    uint32_t flag_dependencies;
    switch (library_flag) {
        default:
            return 0;
        case XbSymbolLib_D3DX8:
            flag_dependencies = XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG;
            break;
        case XbSymbolLib_XACTENG:
            return XbSymbolLib_DSOUND;
#if 0 // Disabled since internal scan will scan XNET(N|S) library anyway.
        case XbSymbolLib_XONLINE:
        case XbSymbolLib_XONLINES:
        case XbSymbolLib_XONLINLS:
            flag_dependencies = XbSymbolLib_XNET | XbSymbolLib_XNETN | XbSymbolLib_XNETS;
            break;
#endif
    }

    // TODO: Should we go with this method or convert into a function for separate dependency process?
    uint32_t ret_dependencies = 0;
    for (unsigned i = 0; i < library_filters.count; i++) {
        if (library_filters.filters[i].flag & flag_dependencies) {
            ret_dependencies |= library_filters.filters[i].flag;
        }
    }
    // If flag dependency is/are found, then return those.
    if (ret_dependencies) {
        return ret_dependencies;
    }
    // If not, then return whole dependency filters.
    return flag_dependencies;
}

uint32_t XbSymbolContext_GetLibraryDependencies(XbSymbolContextHandle pHandle, uint32_t library_flag)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;
    // Forward call to XbSymbolDatabase_GetLibraryDependencies.
    return XbSymbolDatabase_GetLibraryDependencies(library_flag, pContext->library_input);
}

// TODO: Expose to third-party?
bool XbSymbolHasDSoundSection(const void* xb_header_addr)
{
    const xbe_header* pXbeHeader = xb_header_addr;
    memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    xbe_section_header* pSectionHeaders = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    const char* SectionName;
    bool has_dsound = false;

    // Verify if title do contain DirectSound library section.
    for (unsigned int v = 0; v < pXbeHeader->dwSections; v++) {
        SectionName = (const char*)(xb_start_addr + pSectionHeaders[v].SectionNameAddr);

        if (strncmp(SectionName, Lib_DSOUND, 8) == 0) {
            has_dsound = true;
            break;
        }
    }

    return has_dsound;
}

uint32_t XbSymbolDatabase_GenerateLibraryFilter(const void* xb_header_addr, XbSDBLibraryHeader* library_header)
{
    uint32_t library_flag;
    const xbe_header* pXbeHeader = xb_header_addr;
    const memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    const xbe_library_version* xb_library_versions = (xbe_library_version*)(xb_start_addr + pXbeHeader->pLibraryVersionsAddr);
    unsigned int library_total = pXbeHeader->dwLibraryVersions;
    unsigned int count = 0;
    uint16_t build_version = 0;
    bool has_dsound_library = false;
    bool has_d3d8__ltcg_library = false;
    xb_xbe_type XbeType = GetXbeType(xb_header_addr);
    OutputHandler output = {
        .func = g_output_func,
        .verbose_level = g_output_verbose_level
    };

    // Only process XDK applications.
    if (pXbeHeader->pLibraryVersionsAddr != 0) {

        for (unsigned library_index = 0; library_index < library_total; library_index++) {

            library_flag = XbSymbolDatabase_LibraryToFlag(xb_library_versions[library_index].szName);

            // Keep the highest build version for manual checklist.
            if (build_version < xb_library_versions[library_index].wBuildVersion) {
                build_version = xb_library_versions[library_index].wBuildVersion;
            }

            // If library is unknown to the database, skip it.
            if (library_flag == 0) {
                continue;
            }

            // If found DSOUND library, then skip the manual check.
            if (library_flag == XbSymbolLib_DSOUND) {
                if (!has_dsound_library) {
                    has_dsound_library = true;
                }
            }

            // If D3D8 and D3D8LTCG library details may had bundled by accident, then do manual fix below.
            // See details from https://github.com/Cxbx-Reloaded/XbSymbolDatabase/issues/178
            if (library_flag & (XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG)) {
                if (has_d3d8__ltcg_library) {
                    if (library_header != NULL) {
                        if (library_flag == XbSymbolLib_D3D8LTCG) {
                            // Force set to D3D8LTCG if D3D8 flag was found first.
                            internal_LibraryFilterUpdateFlagIfExist(library_header->filters,
                                                                    count,
                                                                    XbSymbolLib_D3D8,
                                                                    XbSymbolLib_D3D8LTCG);
                        }
                        // Update duplicated library detail
                        internal_LibraryFilterUpdateVersionIfGreater(library_header->filters,
                                                                     count,
                                                                     XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG,
                                                                     xb_library_versions[library_index].wBuildVersion,
                                                                     xb_library_versions[library_index].wFlags.QFEVersion);
                    }

                    // Skip duplicate library finding.
                    continue;
                }
                else if (!has_d3d8__ltcg_library) {
                    has_d3d8__ltcg_library = true;
                }
            }

            // Append the information to the array.
            if (library_header != NULL) {

                library_header->filters[count].flag = library_flag;
                library_header->filters[count].build_version = xb_library_versions[library_index].wBuildVersion;
                library_header->filters[count].qfe_version = xb_library_versions[library_index].wFlags.QFEVersion;
                memcpy(library_header->filters[count].name, XbSymbolDatabase_LibraryToString(library_flag), 8);

                if ((library_flag & (XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG)) > 0) {

                    // Functions in this library were updated by June 2003 XDK (5558) with Integrated Hotfixes,
                    // However August 2003 XDK (5659) still uses the old function.
                    // Please use updated 5788 instead.
                    if (xb_library_versions[library_index].wBuildVersion >= 5558 &&
                        xb_library_versions[library_index].wBuildVersion <= 5659 &&
                        xb_library_versions[library_index].wFlags.QFEVersion > 1) {

                        output_message_format(&output, XB_OUTPUT_MESSAGE_WARN,
                                              "D3D8 version 1.0.%d.%d Title Detected: This game uses an alias version 1.0.5788",
                                              xb_library_versions[library_index].wBuildVersion,
                                              xb_library_versions[library_index].wFlags.QFEVersion);

                        library_header->filters[count].build_version = 5788;
                    }
                }
            }
            count++;
        }

        // Manual check if DSOUND section do exist.
        if (!has_dsound_library) {
            if (XbSymbolHasDSoundSection(xb_header_addr)) {
                if (library_header != NULL) {
                    library_header->filters[count].flag = XbSymbolLib_DSOUND;
                    library_header->filters[count].build_version = build_version;
                    library_header->filters[count].qfe_version = 0;
                    (void)strncpy(library_header->filters[count].name, Lib_DSOUND, 8);
                }
                count++;
            }
        }

        // Manual check if Xbe type is debug or Chihiro
        if (XbeType != XB_XBE_TYPE_RETAIL) {
            if (library_header != NULL) {
                library_header->filters[count].flag = XbSymbolLib_JVS;
                library_header->filters[count].build_version = build_version;
                library_header->filters[count].qfe_version = 0;
                (void)strncpy(library_header->filters[count].name, Lib_JVS, 8);
            }
            count++;
        }
    }

    return count;
}

uint32_t XbSymbolDatabase_GenerateSectionFilter(const void* xb_header_addr, XbSDBSectionHeader* section_header, bool is_raw)
{
    const xbe_header* pXbeHeader = xb_header_addr;
    const memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    const xbe_section_header* xb_section_headers = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    const xbe_section_header* sh_index;
    XbSDBSection* sv_index;
    unsigned int section_total = pXbeHeader->dwSections;
    unsigned int count = 0;
    const char* SectionName;
    uint32_t kernel_thunk_addr;

    if (pXbeHeader->pSectionHeadersAddr != 0) {

        kernel_thunk_addr = XbSymbolDatabase_GetKernelThunkAddress(xb_header_addr);

        for (unsigned section_index = 0; section_index < section_total; section_index++) {

            SectionName = (const char*)(xb_start_addr + xb_section_headers[section_index].SectionNameAddr);
            sh_index = &xb_section_headers[section_index];

            // Verify if section is preload. If not, then skip it.
            // Intend for optimization usage and avoid false positive detection.
            if ((sh_index->dwFlags_value & XBE_SECTION_HEADER_FLAGS_PRELOAD) == 0) {
                continue;
            }

            bool is_detected = false;

            for (unsigned int SectionList_index = 0; SectionList_index < SectionListTotal; SectionList_index++) {

                // Once match is found, increase the count plus append to section vars.
                if (strncmp(SectionName, SectionList[SectionList_index], 8) == 0) {
                    is_detected = true;
                    break;
                }
            }

            // If section is not on the filter list, check if there is kernel thunk table within section to enforce include it.
            if (is_detected == false) {
                if (kernel_thunk_addr >= sh_index->dwVirtualAddr && kernel_thunk_addr < (sh_index->dwVirtualAddr + sh_index->dwSizeofRaw)) {
                    // Once found within range, then enforce add section to the filter.
                    is_detected = true;
                }
            }

            // If detected, then register into filter list.
            if (is_detected == true) {
                if (section_header != NULL) {
                    sv_index = &section_header->filters[count];

                    memcpy(sv_index->name, SectionName, 8);
                    sv_index->xb_virt_addr = sh_index->dwVirtualAddr;
                    sv_index->buffer_size = sh_index->dwSizeofRaw;

                    if (is_raw) {
                        sv_index->buffer_lower = (memptr_t)xb_header_addr + sh_index->dwRawAddr;
                    }
                    else {
                        sv_index->buffer_lower = xb_start_addr + sh_index->dwVirtualAddr;
                    }
                }

                count++;
            }
        }
    }

    return count;
}

xbaddr XbSymbolDatabase_GetKernelThunkAddress(const void* xb_header_addr)
{
    xb_xbe_type xbe_type = GetXbeType(xb_header_addr);

    uint32_t kernel_thunk_addr = *(uint32_t*)((uint8_t*)xb_header_addr + 0x0158);
    kernel_thunk_addr ^= XB_XOR_KT[xbe_type];

    return kernel_thunk_addr;
}

#include "internal_db_version.h"
unsigned int XbSymbolDatabase_LibraryVersion()
{
    // Calculate this just once
    static unsigned int CalculatedHash = 0;
    if (CalculatedHash == 0) {
        CalculatedHash = HashSymbolDataArray(SymbolDBList, SymbolDBListCount);
    }
    return CalculatedHash;
}

#include "internal_tests.h"
unsigned int XbSymbolDatabase_TestOOVPAs()
{
    SymbolDatabaseVerifyContext context = { 0 };
    context.output.func = g_output_func;
    context.output.verbose_level = g_output_verbose_level;
    return SymbolDatabaseVerifyContext_VerifyDatabaseList(&context);
}

// ******************************************************************
// * XbSymbolContextHandle manager functions
// ******************************************************************

bool XbSymbolDatabase_CreateXbSymbolContext(XbSymbolContextHandle* ppHandle,
                                            xb_symbol_register_t register_func,
                                            XbSDBLibraryHeader library_input,
                                            XbSDBSectionHeader section_input,
                                            xbaddr kernel_thunk)
{
    if (register_func == NULL) {
        goto EmptyCleanup;
    }

    // Verify if Microsoft XDK library do exist
    if (library_input.count == 0 || library_input.filters == NULL) {
        goto EmptyCleanup;
    }

    // Verify if we have sections exist to process.
    if (section_input.count == 0 || section_input.filters == NULL) {
        goto EmptyCleanup;
    }

    *ppHandle = calloc(1, sizeof(iXbSymbolContext));

    if (*ppHandle == NULL) {
        goto EmptyCleanup;
    }

    iXbSymbolContext* pContext = (iXbSymbolContext*)*ppHandle;

    pContext->scan_stage = SS_NONE;

    pContext->register_func = register_func;

    // Initialize default values to context handler.
    pContext->strict_build_version_limit = true;
    pContext->one_time_scan = true;
    pContext->scan_first_detect = false;
    pContext->output.verbose_level = g_output_verbose_level;
    pContext->output.func = g_output_func;
    pContext->library_filter = 0;

    // Copy pointers and values to context handler.
    pContext->library_input.count = library_input.count;
    pContext->library_input.filters = malloc(sizeof(XbSDBLibrary) * library_input.count);
    if (pContext->library_input.filters == NULL) {
        goto ContextCleanup;
    }

    pContext->section_input.count = section_input.count;
    pContext->section_input.filters = malloc(sizeof(XbSDBSection) * section_input.count);
    if (pContext->section_input.filters == NULL) {
        goto LibraryCleanup;
    }

    memcpy(pContext->library_input.filters, library_input.filters, sizeof(XbSDBLibrary) * library_input.count);
    memcpy(pContext->section_input.filters, section_input.filters, sizeof(XbSDBSection) * section_input.count);

    // Mark all Xrefs initially as undetermined
    memset((void*)pContext->xref_database, XREF_ADDR_UNDETERMINED, sizeof(pContext->xref_database));

    // Find specific section contains the kernel thunk.
    bool kt_found = false;
    for (unsigned int i = 0; i < pContext->section_input.count; i++) {
        XbSDBSection* section = pContext->section_input.filters + i;
        uintptr_t virt_start_relative = (uintptr_t)section->buffer_lower - section->xb_virt_addr;

        // Once found, start register the kernel xreferences.
        if (kernel_thunk >= section->xb_virt_addr && kernel_thunk < (section->xb_virt_addr + section->buffer_size)) {
            uint32_t* kt = (uint32_t*)(virt_start_relative + kernel_thunk);
            xbaddr kt_addr = kernel_thunk;
            kt_found = true;
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG,
                                  "Kernel thunk is found in %.8s section",
                                  section->name);

            while (*kt > 0) {
                unsigned int index = *kt & 0x7FFFFFFF;
                // Check if the index is within range, then add to the xreference database.
                if (index > 0 && index < XREF_KT_COUNT) {
                    internal_SetXRefDatabase(pContext, LT_KERNEL, index, kt_addr);
                }
                else {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                          "Unable to register kernel thunk: index=%u; vaddr=0x%08x",
                                          index, kt_addr);
                }
                kt++;
                kt_addr += 4;
            }
            break;
        }
    }

    if (!kt_found) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                       "Kernel thunk is not found from sections input, certain symbol's OOVPAs may not be detected.");
    }

    // clang-format off
    // Request a few fundamental XRefs to be derived instead of checked
    // D3D
    pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] = XREF_ADDR_DERIVE;                     //In use
    pContext->xref_database[XREF_D3D_g_Stream] = XREF_ADDR_DERIVE;                             //In use
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_PixelShader] = XREF_ADDR_DERIVE;          //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_Textures] = XREF_ADDR_DERIVE;             //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_Palettes] = XREF_ADDR_DERIVE;             //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_RenderTarget] = XREF_ADDR_DERIVE;         //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_DepthStencil] = XREF_ADDR_DERIVE;         //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_VerticalBlankEvent] = XREF_ADDR_DERIVE;   //In use
#if 0                                                                                          //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_SwapCallback] = XREF_ADDR_UNDETERMINED;   //In use // Manual check only.
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_VBlankCallback] = XREF_ADDR_UNDETERMINED; //In use // Manual check only.
#endif                                                                                         //
    pContext->xref_database[XREF_OFFSET_D3DDevice__m_VertexShader] = XREF_ADDR_DERIVE;         //In use
    // JVS                                                                                     //
    pContext->xref_database[XREF_JVS_g_pPINSA] = XREF_ADDR_DERIVE;                             //In use
    pContext->xref_database[XREF_JVS_g_pPINSB] = XREF_ADDR_DERIVE;                             //In use
    // XAPILIB                                                                                 //
    pContext->xref_database[XREF_g_XapiCurrentTopLevelFilter] = XREF_ADDR_DERIVE;              //In use
    pContext->xref_database[XREF_g_DeviceType_Gamepad] = XREF_ADDR_DERIVE;                     //In use
    pContext->xref_database[XREF_g_DeviceType_Keyboard] = XREF_ADDR_DERIVE;                    //In use
    pContext->xref_database[XREF_g_DeviceType_IRDongle] = XREF_ADDR_DERIVE;                    //In use
    pContext->xref_database[XREF_g_DeviceTypeInfoTableBegin] = XREF_ADDR_DERIVE;               //In use
    pContext->xref_database[XREF_g_DeviceTypeInfoTableEnd] = XREF_ADDR_DERIVE;                 //In use
    pContext->xref_database[XREF_g_XapiAltLett_MU] = XREF_ADDR_DERIVE;                         //In use
    pContext->xref_database[XREF_g_XapiMountedMUs] = XREF_ADDR_DERIVE;                         //In use
    pContext->xref_database[XREF_OFFSET_XapiCurrentFiber] = XREF_ADDR_DERIVE;                  //In use
    pContext->xref_database[XREF_OFFSET_XapiLastErrorCode] = XREF_ADDR_DERIVE;                 //In use
    pContext->xref_database[XREF_OFFSET_XapiThreadFiberData] = XREF_ADDR_DERIVE;               //In use
    pContext->xref_database[XREF_XAPI__tls_array] = XREF_ADDR_DERIVE;                          //In use
    pContext->xref_database[XREF_XAPI__tls_index] = XREF_ADDR_DERIVE;                          //In use
    pContext->xref_database[XREF_XapiThreadNotifyRoutineList] = XREF_ADDR_DERIVE;              //In use
    pContext->xref_database[XREF_XGetSectionSize] = XREF_ADDR_DERIVE;                          //In use
    // clang-format on

    // Mark all library contexts as zero-initialized for scan activity.
    memset(pContext->library_contexts, 0, sizeof(pContext->library_contexts));

    return true;

    // Failure cleanup crew handle
    //FullCleanup:

    //SectionCleanup:
    //free(pContext->section_input.filters);

LibraryCleanup:
    free(pContext->library_input.filters);

ContextCleanup:
    free(*ppHandle);

EmptyCleanup:
    *ppHandle = NULL;
    return false;
}

void XbSymbolContext_Release(XbSymbolContextHandle pHandle)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    for (unsigned int i = 0; i < LT_COUNT; i++) {
        if (pContext->library_contexts[i].is_active) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type is currently active: %u", i);
        }
    }

    free(pHandle);
}


// ******************************************************************
// * XbSymbolContext API functions
// ******************************************************************

void XbSymbolContext_SetBypassBuildVersionLimit(XbSymbolContextHandle pHandle, bool bypass_limit)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (iXbSymbolContext_AllowSetParameter(pContext)) {
        pContext->strict_build_version_limit = !bypass_limit;
    }
}

void XbSymbolContext_SetContinuousSigScan(XbSymbolContextHandle pHandle, bool enable)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (iXbSymbolContext_AllowSetParameter(pContext)) {
        pContext->one_time_scan = !enable;
    }
}

void XbSymbolContext_SetFirstDetectAddressOnly(XbSymbolContextHandle pHandle, bool enable)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (iXbSymbolContext_AllowSetParameter(pContext)) {
        pContext->scan_first_detect = enable;
    }
}

bool XbSymbolContext_RegisterLibrary(XbSymbolContextHandle pHandle, uint32_t library_filter)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (!iXbSymbolContext_AllowSetParameter(pContext)) {
        return false;
    }

    // Check to make sure all flags are acceptable before set.
    if ((library_filter & ~XbSymbolLib_ALL) > 0) {
        return false;
    }

    pContext->library_filter = library_filter;
    return true;
}

#include "manual_custom.h"
void XbSymbolContext_ScanManual(XbSymbolContextHandle pHandle)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (pContext->scan_stage >= SS_1_MANUAL) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Manual rescan request is skip.");
        return;
    }
    pContext->scan_stage = SS_1_MANUAL;

    for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {

        const XbSDBLibrary* pLibrary = pContext->library_input.filters + lv;
        eLibraryType i_LibraryType = internal_GetLibraryType(pLibrary->flag);

        if (i_LibraryType <= LT_UNKNOWN || LT_MAX <= i_LibraryType) {
            continue;
        }

        iXbSymbolLibrarySession libSession = {
            .pLibrary = pLibrary,
            .iLibraryType = i_LibraryType
        };

        if ((pLibrary->flag & (XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG)) > 0) {
            // TODO: Do we need to check twice?
            // Perform check twice, since sections can be in different order.
            for (unsigned int loop = 0; loop < 2; loop++) {
                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                // By doing this method will reduce false detection dramatically. If it had happened before.
                if (!manual_scan_library_custom(pContext, manual_scan_section_dx8, &libSession)) {
                    continue;
                }
                break;
            }
        }
        else if ((pLibrary->flag & XbSymbolLib_DSOUND) > 0) {
            // Perform check twice, since sections can be in different order.
            for (unsigned int loop = 0; loop < 2; loop++) {
                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                // By doing this method will reduce false detection dramatically. If it had happened before.
                if (!manual_scan_library_custom(pContext, manual_scan_section_dsound, &libSession)) {
                    continue;
                }
                break;
            }
        }
        else if ((pLibrary->flag & XbSymbolLib_XAPILIB) > 0) {
            manual_scan_library_custom(pContext, manual_scan_section_xapilib, &libSession);
        }
    }

    pContext->scan_stage = SS_2_SCAN_LIBS;
}

unsigned int XbSymbolContext_ScanLibrary(XbSymbolContextHandle pHandle,
                                         const XbSDBLibrary* pLibrary,
                                         bool xref_first_pass)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;
    eLibraryType iLibraryType = internal_GetLibraryType(pLibrary->flag);

    if (iLibraryType <= LT_UNKNOWN || LT_MAX <= iLibraryType) {
        return 0;
    }

    iXbSymbolLibrarySession librarySession = {
        .pLibrary = pLibrary,
        .iLibraryType = iLibraryType
    };

    unsigned int xref_count = pContext->library_contexts[iLibraryType].xref_registered;

    if (!iXbSymbolContext_AllowScanLibrary(pContext)) {
        return 0;
    }

    // If library type is active, do nothing.
    if (!internal_SetLibraryTypeStart(pContext, iLibraryType)) {
        return 0;
    }

    SymbolDatabaseList* pSymbolDB;
    unsigned db_i = 0;
    while ((pSymbolDB = internal_FindLibraryDB(pLibrary->flag, &db_i))) {
        db_i++;
        for (unsigned int s = 0; s < pContext->section_input.count; s++) {

            // Initialize a matching specific section is currently pair with library in order to scan specific section only.
            // By doing this method will reduce false detection dramatically. If it had happened before.
            for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                if (pSymbolDB->LibSec.section[d3] != NULL &&
                    strncmp(pContext->section_input.filters[s].name, pSymbolDB->LibSec.section[d3], 8) == 0) {

                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section",
                                          pLibrary->name, pSymbolDB->LibSec.section[d3]);

                    internal_OOVPA_scan(pContext, pSymbolDB->SymbolsTable, pSymbolDB->SymbolsTableCount,
                                        &librarySession, pContext->section_input.filters + s, xref_first_pass);
                    break;
                }
            }

            // NOTE: Do not use break since database entry can have multiple same library entries even doesn't have 2+ bit flags.
            // Affected case: DSound's manual scan required more sections.
#if 0
            // Use the break if there are 2+ bit flags set such as include LTCG flag in std flag's oovpa database like D3D8.
            if ((SymbolDBList[d2].LibSec.library & ~pLibrary->flag) == 0) {
                break;
            }
#endif
        }
    }

    xref_count = pContext->library_contexts[iLibraryType].xref_registered - xref_count;

    internal_SetLibraryTypeEnd(pContext, iLibraryType);

    return xref_count;
}

void XbSymbolContext_ScanAllLibraryFilter(XbSymbolContextHandle pHandle)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (!iXbSymbolContext_AllowScanLibrary(pContext)) {
        return;
    }

    // Library input should not be above 4 * 8 (32) total.
    if (pContext->library_input.count > sizeof(uint32_t) * 8) {
        return;
    }

    uint32_t library_scan = 0;
    uint32_t library_completion = 0;
    bool not_first_pass[sizeof(uint32_t) * 8] = { false }; // Set to invert true for search speed optimization
    uint32_t library_dependency[sizeof(uint32_t) * 8] = { 0 };
    // Get Library's dependency flag(s)
    for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {
        const XbSDBLibrary* library = pContext->library_input.filters + lv;
        if (internal_LibraryFilterPermitScan(pContext, library->flag)) {
            library_dependency[lv] = XbSymbolContext_GetLibraryDependencies(pHandle, library->flag);
            library_scan |= library->flag;
        }
    }

    // TODO: Update this loop for dependency check up.
    // Repeat process until all libraries has been scanned.
    do {
        for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {
            const XbSDBLibrary* library = pContext->library_input.filters + lv;

            // Keep scanning active library until it is done or skipped.
            do {
                // Temporary placeholder until v2.0 API's section scan function is ready or may be permanent in here.
                // Skip specific library if third-party set to specific library.
                if (!internal_LibraryFilterPermitScan(pContext, library->flag)) {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Skipping %.8s (%hu) scan.", library->name, library->build_version);
                }
                else {
                    // Check if we already completed library scan first.
                    if (XbSymbolDatabase_CheckDependencyCompletion(library_completion, library->flag)) {
                        // Skip if already been scanned.
                        break;
                    }

                    // Check if any dependency is set and if they are completed
                    if (library_dependency[lv] && !XbSymbolDatabase_CheckDependencyCompletion(library_completion, library_dependency[lv])) {
                        // Skip if any dependency library isn't done yet.
                        break;
                    }
                    // Start library scan against symbol database we want to search for address of symbols and xreferences.
                    unsigned counter = XbSymbolContext_ScanLibrary(pHandle, library, !not_first_pass[lv]);

                    // If no additional symbols found, then set as scan completed.
                    if (counter == 0) {
                        XbSymbolDatabase_SetLibraryCompletion(library_completion, library->flag);
                    }
                    // Once first pass is done, multiple passes may will occur for any xref dependency symbols haven't been found.
                    if (!not_first_pass[lv]) {
                        not_first_pass[lv] = true;
                    }
                }
            } while (true);
        }

    } while (!XbSymbolDatabase_CheckDependencyCompletion(library_completion, library_scan));
}

// Does individual registration of derived XRef's that are useful but not yet registered.
// Called after entire scan.
void XbSymbolContext_RegisterXRefs(XbSymbolContextHandle pHandle)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (pContext->register_func == NULL) {
        return;
    }

    // Any symbols that are not registered, check into below function's library calls.
    // Then add missing symbol(s) to appropriate library's function.
    manual_register_symbols(pContext);
}


// ******************************************************************
// * global API functions (required to be at end of the file)
// ******************************************************************

// Aka the basic example to handle the scan process.
bool XbSymbolScan(const void* xb_header_addr,
                  xb_symbol_register_t register_func,
                  bool is_raw)
{
    bool bCheckJVS = false;

    XbSymbolContextHandle pHandle;
    iXbSymbolContext* iContext;
    XbSDBLibraryHeader library_input = { 0 };
    XbSDBSectionHeader section_input = { 0 };

    // Step 1, let's get the total sum of array to allocate library input.
    library_input.count = XbSymbolDatabase_GenerateLibraryFilter(xb_header_addr, NULL);
    // If total sum is zero, then the input is invalid.
    if (library_input.count == 0) {
        return false;
    }
    // Then allocate the necessary memory requirement to obtain the information.
    library_input.filters = malloc(sizeof(XbSDBLibrary) * library_input.count);
    // Verify if memory has been allocated.
    if (library_input.filters == NULL) {
        return false;
    }
    // Finally, obtain the information for internal scan process.
    (void)XbSymbolDatabase_GenerateLibraryFilter(xb_header_addr, &library_input);

    // Step 2, let's get the total sum of array to allocate section input.
    section_input.count = XbSymbolDatabase_GenerateSectionFilter(xb_header_addr, NULL, is_raw);
    // If total sum is zero, then the input is invalid.
    if (section_input.count == 0) {
        goto LibraryCleanup;
    }
    // Then allocate the necessary memory requirement to obtain the information.
    section_input.filters = malloc(sizeof(XbSDBSection) * section_input.count);
    // Verify if memory has been allocated.
    if (section_input.filters == NULL) {
        goto LibraryCleanup;
    }
    // Finally, obtain the information for internal scan process.
    (void)XbSymbolDatabase_GenerateSectionFilter(xb_header_addr, &section_input, is_raw);

    xb_xbe_type xbe_type = GetXbeType(xb_header_addr);

    uint32_t kernel_thunk_addr = XbSymbolDatabase_GetKernelThunkAddress(xb_header_addr);

    // Step 3, initialize context handle to pre-allocate the requirement.
    // However, calling global functions are recommended first for any customization.
    if (!XbSymbolDatabase_CreateXbSymbolContext(&pHandle, register_func, library_input, section_input, kernel_thunk_addr)) {
        goto FullCleanup;
    }
    // After initialize, we do not need to keep the allocated filter arrays in memory.
    free(section_input.filters);
    free(library_input.filters);

    iContext = (iXbSymbolContext*)pHandle;

    output_message_format(&iContext->output, XB_OUTPUT_MESSAGE_DEBUG, "xbe type is %s", xbe_type_str[xbe_type]);

    // Step 4, perform manual scan requirement to collect the necessary requirement
    // before perform general scan.
    XbSymbolContext_ScanManual(pHandle);

    // Step 5, do a full scan process.
    XbSymbolContext_ScanAllLibraryFilter(pHandle);

    // Step 6, register any xrefs (which doesn't have its own OOVPA)
    XbSymbolContext_RegisterXRefs(pHandle);

    // Finally, after all the scan process is done, release the context handler.
    XbSymbolContext_Release(pHandle);

    return true;

// Failure cleanup crew handle
FullCleanup:

#if 0
SectionCleanup:
#endif
    free(section_input.filters);

LibraryCleanup:
    free(library_input.filters);

    return false;
}

// Require to be at end of various functions may use manual register calls in order to count properly.
unsigned XbSymbolDatabase_GetTotalSymbols(uint32_t library_filter)
{
    unsigned db_i = 0, total = SYMBOL_COUNTER_VALUE;
    SymbolDatabaseList* pLibraryDB;
    while ((pLibraryDB = internal_FindLibraryDB(library_filter, &db_i))) {
        db_i++;
        total += pLibraryDB->SymbolsTableCount;
    }
    return total;
}

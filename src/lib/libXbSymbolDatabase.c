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
// TODO: Most compilers haven't include C11's thread support for multi-thread safe.
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_THREADS__)
#define MULTI_THREAD_SAFE true
#include <threads.h>
#endif

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

// ******************************************************************
// * Xbox Symbol OOVPA Database
// ******************************************************************

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
    xb_output_message   verbose_level;
    xb_output_message_t func;
} OutputHandler;

// Library Type is a requirement to prevent another thread
// doing the same scan process.
typedef enum _eLibraryType {
    LT_KERNEL = 0,
    LT_D3D,
    LT_AUDIO,
    LT_JVS,
    LT_XAPI,
    LT_GRAPHIC,
    LT_NETWORK,
    LT_UNKNOWN,
    LT_COUNT=LT_UNKNOWN
} eLibraryType;

typedef enum _eScanStage {
    SS_NONE = 0,
    SS_1_MANUAL,
    SS_2_SCAN_LIBS,
} eScanStage;

typedef struct _iXbSymbolLibraryContext {
    uint32_t    xref_registered;
    bool        is_active;
} iXbSymbolLibraryContext;

typedef struct _iXbSymbolLibrarySession {
    const XbSDBLibrary* pLibrary;
    eLibraryType iLibraryType;
} iXbSymbolLibrarySession;

typedef struct _iXbSymbolContext {
    bool                    strict_build_version_limit;
    bool                    one_time_scan;
    bool                    scan_first_detect;
    uint32_t                library_filter;
    xbaddr                  xref_database[XREF_COUNT];
    OutputHandler           output;
    xb_symbol_register_t    register_func;
    XbSDBLibraryHeader      library_input;
    XbSDBSectionHeader      section_input;
    eScanStage              scan_stage;
    iXbSymbolLibraryContext library_contexts[LT_COUNT];
#ifdef MULTI_THREAD_SAFE
    mtx_t                   mutex;
#endif
} iXbSymbolContext;

typedef bool (*custom_scan_func_t)(iXbSymbolContext* pContext,
                                   const iXbSymbolLibrarySession* pLibrary,
                                   const XbSDBSection* pSection);

typedef const struct _PairScanLibSec {
    uint32_t library;
    const char* section[PAIRSCANSEC_MAX];
} PairScanLibSec;

typedef const struct _SymbolDatabaseList {
    PairScanLibSec  LibSec;

    OOVPATable*     OovpaTable;
    unsigned int    OovpaTableCount;
} SymbolDatabaseList;

SymbolDatabaseList SymbolDBList[] = {
    // Support inline functions in .text section
    { XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG,{ Sec_text, Sec_D3D, Sec_FLASHROM }, D3D8_OOVPA, D3D8_OOVPA_COUNT },

    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    { XbSymbolLib_D3D8LTCG,{ Sec_D3D }, D3D8LTCG_OOVPA, D3D8LTCG_OOVPA_COUNT },

    // NOTE: Likely is a D3D Helper library.
    // Jarupxx mention this is not a requirement?
    //{ Lib_D3DX8,{ Sec_D3DX }, _OOVPA, _OOVPA_COUNT },

    // Only used for manual scan purpose as a workaround since both FLASHROM
    // and text section will lead to false detection for non-manual signatures, see comment below.
    { XbSymbolLib_DSOUND,{ Sec_DSOUND, Sec_rdata, Sec_FLASHROM, Sec_text }, DSound_OOVPA_manual, DSound_OOVPA_manual_COUNT },

    // NOTE: By adding FLASHROM to scan section may will lead false detection.
    // Since some symbols has very short asm codes.
    { XbSymbolLib_DSOUND,{ Sec_DSOUND, Sec_rdata, Sec_FLASHROM }, DSound_OOVPA, DSound_OOVPA_COUNT },

    // DSOUNDH is just meant to define hot fix, there is no separate section
    //{ XbSymbolLib_DSOUNDH,{ Sec_DSOUND }, &DSound_OOVPA, DSound_OOVPA_COUNT },

    // Only used in Chihiro applications
    { XbSymbolLib_JVS,{ Sec_text, Sec_XPP, Sec_FLASHROM }, JVSLIB_OOVPA, JVSLIB_OOVPA_COUNT },

    //
    { XbSymbolLib_XACTENG, { Sec_XACTENG, Sec_FLASHROM }, XACTENG_OOVPA, XACTENG_OOVPA_COUNT },

    // test case: Power Drome (Unluckily, it use LTCG version of the library.)
    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    //{ XbSymbolLib_XACTENLT,{ Sec_XACTENG }, XACTENGLT_OOVPA, XACTENGLT_OOVPA_COUNT },

    //
    { XbSymbolLib_XAPILIB,{ Sec_text, Sec_XPP, Sec_FLASHROM }, XAPILIB_OOVPA, XAPILIB_OOVPA_COUNT },

    // Support inline functions in .text section
    { XbSymbolLib_XGRAPHC,{ Sec_text, Sec_XGRPH, Sec_FLASHROM }, XGRAPHC_OOVPA, XGRAPHC_OOVPA_COUNT },

    // LTCG database have to be after standard library or otherwise the scan process will not work correctly.
    //{ XbSymbolLib_XGRAPHCL ,{ Sec_XGRPH }, XGRAPHCL_OOVPA, XGRAPHCL_OOVPA_COUNT },

    // Added Sec_text and Sec_XNET just in case.
    // TODO: Do we need to keep Sec_XNET in here?
    // TODO: Need to find out which function is only part of XOnlines.
    // Fun fact, XONLINES are split into 2 header sections.
    { XbSymbolLib_XONLINE | XbSymbolLib_XONLINES, { Sec_text, Sec_XONLINE, Sec_XNET, Sec_FLASHROM }, XONLINE_OOVPA, XONLINE_OOVPA_COUNT },

    // Added Sec_text just in case.
    // TODO: Need to find out which function is only part of XNets.
    // XNETS only has XNET, might be true.
    // XNETN's test case: Stake
    { XbSymbolLib_XNET | XbSymbolLib_XNETS | XbSymbolLib_XNETN | XbSymbolLib_XONLINE | XbSymbolLib_XONLINES,
        { Sec_text, Sec_XNET, Sec_FLASHROM }, XNET_OOVPA, XNET_OOVPA_COUNT },
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
    Sec_XPP,
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

static bool iXbSymbolContext_Lock(iXbSymbolContext* pContext)
{
#ifdef MULTI_THREAD_SAFE
    // Lock to this thread only during the scan process until the scan is done.
    int mtxStatus = mtx_lock(&pContext->mutex);
    if (mtxStatus != thrd_success) {
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Unable to lock mutex: %d", mtxStatus);
        return false;
    }
#endif

    return true;
}

static void iXbSymbolContext_Unlock(iXbSymbolContext* pContext)
{
#ifdef MULTI_THREAD_SAFE
    // Lock to this thread only during the scan process until the scan is done.
    (void)mtx_unlock(&pContext->mutex);
#endif
}

static bool iXbSymbolContext_AllowSetParameter(iXbSymbolContext* pContext)
{
    bool bRet;

    if (!iXbSymbolContext_Lock(pContext)) {
        return false;
    }

    bRet = (pContext->scan_stage == SS_NONE);

    if (!bRet) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Cannot set parameter value after first and during scan call.");
    }

    iXbSymbolContext_Unlock(pContext);

    return bRet;
}

static bool iXbSymbolContext_AllowScanLibrary(iXbSymbolContext* pContext)
{
    bool bRet;

    if (!iXbSymbolContext_Lock(pContext)) {
        return false;
    }

    bRet = (pContext->scan_stage == SS_2_SCAN_LIBS);

    if (!bRet) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "XbSymbolContext_ScanManual must be call first before scan for library's symbols.");
    }

    iXbSymbolContext_Unlock(pContext);

    return bRet;
}

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

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
    return 0;
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
    unsigned int library_index = 0;
    const xbe_section_header* xb_section_headers = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    unsigned int section_total = pXbeHeader->dwSections;
    unsigned int section_index = 0;
    unsigned int count = 0;
    uint16_t build_version = 0;
    bool has_dsound_library = false;
    xb_xbe_type XbeType = GetXbeType(xb_header_addr);
    OutputHandler output;
    output.func = g_output_func;
    output.verbose_level = g_output_verbose_level;

    // Only process XDK applications.
    if (pXbeHeader->pLibraryVersionsAddr != 0) {

        for (library_index; library_index < library_total; library_index++) {

            library_flag = XbSymbolDatabase_LibraryToFlag(xb_library_versions[library_index].szName);

            // If library is unknown to the database, skip it.
            if (library_flag == 0) {
                continue;
            }

            // Keep the highest build version for manual checklist.
            if (build_version < xb_library_versions[library_index].wBuildVersion) {
                build_version = xb_library_versions[library_index].wBuildVersion;
            }

            // If found DSOUND library, then skip the manual check.
            if (library_flag == XbSymbolLib_DSOUND && !has_dsound_library) {
                has_dsound_library = true;
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
    unsigned int section_index = 0;
    unsigned int count = 0;
    const char* SectionName;

    if (pXbeHeader->pSectionHeadersAddr != 0) {

        for (section_index; section_index < section_total; section_index++) {

            SectionName = (const char*)(xb_start_addr + xb_section_headers[section_index].SectionNameAddr);

            for (unsigned int SectionList_index = 0; SectionList_index < SectionListTotal; SectionList_index++) {

                // Once match is found, increase the count plus append to section vars.
                if (strncmp(SectionName, SectionList[SectionList_index], 8) == 0) {

                    if (section_header != NULL) {
                        sv_index = &section_header->filters[count];
                        sh_index = &xb_section_headers[section_index];

                        memcpy(sv_index->name, SectionList[SectionList_index], 8);
                        sv_index->xb_virt_addr = sh_index->dwVirtualAddr;
                        sv_index->buffer_size = xb_section_headers[section_index].dwSizeofRaw;

                        if (is_raw) {
                            sv_index->buffer_lower = (memptr_t)xb_header_addr + sh_index->dwRawAddr;
                        }
                        else {
                            sv_index->buffer_lower = xb_start_addr + sh_index->dwVirtualAddr;
                        }
                    }

                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

// NOTE: PatrickvL state the arguments are named differently and the function does something that has another meaning,
//       the implementation could be changed if the need ever arises.
static inline void GetXRefEntry(OOVPA* oovpa, int index, uint32_t* xref_out, uint16_t* offset_out)
{
    *xref_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].xref.index;
    *offset_out = ((LOOVPA*)oovpa)->Lovp[index].offset;
}

static inline void GetOovpaEntry(OOVPA* oovpa, int index, uint32_t* offset_out, uint8_t* value_out)
{
    *offset_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].offset;
    *value_out = (uint8_t)((LOOVPA*)oovpa)->Lovp[index].value;
}

bool CompareOOVPAToAddress(iXbSymbolContext* pContext, OOVPA* Oovpa, memptr_t cur, uintptr_t xb_start_virt_addr)
{
    uint32_t v = 0; // verification counter

    // Check all XRefs, stop if any does not match
    for (; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint16_t Offset;

        // get currently registered (un)known address
        GetXRefEntry(Oovpa, v, &XRef, &Offset);
        xbaddr XRefAddr = pContext->xref_database[XRef];
        // Undetermined XRef cannot be checked yet
        // (XbSymbolLocateFunction already checked this, but this check
        // is cheap enough to keep, and keep this function generic).
        if (XRefAddr == XREF_ADDR_UNDETERMINED)
            return false;

        // Don't verify an xref that has to be (but isn't yet) derived
        if (XRefAddr == XREF_ADDR_DERIVE)
            continue;

        xbaddr ActualAddr = *(xbaddr*)(cur + Offset);
        // check if PC-relative or direct reference matches XRef
        if ((ActualAddr + (xbaddr)((uintptr_t)cur - xb_start_virt_addr) + Offset + 4 != XRefAddr) && (ActualAddr != XRefAddr))
            return false;
    }

    // Check all (Offset,Value)-pairs, stop if any does not match
    for (; v < Oovpa->Count; v++) {
        uint32_t Offset;
        uint8_t ExpectedValue;

        // get offset + value pair
        GetOovpaEntry(Oovpa, v, &Offset, &ExpectedValue);
        uint8_t ActualValue = *(uint8_t*)(cur + Offset);
        if (ActualValue != ExpectedValue)
            return false;
    }

    // all offsets matched
    return true;
}

// Return if the given (XRef'erenced) address is not set yet.
static inline bool internal_IsXRefAddrUnset(xbaddr XRefAddr)
{
    return (XRefAddr == XREF_ADDR_UNDETERMINED) || (XRefAddr == XREF_ADDR_DERIVE);
}

// Return if the given (XRef'erenced) address is valid.
static bool internal_IsXRefAddrValid(xbaddr XRefAddr)
{
    return (XRefAddr + 1) > (XREF_ADDR_DERIVE + 1); // Implies also not equal to XREF_ADDR_UNDETERMINED (-1) nor XREF_ADDR_NOT_FOUND (0)
}

// Obligatory function for setting an address in the XRefDataBase
// (only initialization may write to XRefDataBase outside of this function).
static inline void internal_SetXRefDatabase(iXbSymbolContext* pContext, eLibraryType iLibraryType, uint32_t XRef, xbaddr XRefAddr)
{
    // Count when changing from an initial value to a valid value
    if (internal_IsXRefAddrUnset(pContext->xref_database[XRef])) {
        pContext->library_contexts[iLibraryType].xref_registered++;
    }
    pContext->xref_database[XRef] = XRefAddr; // Besides initialization, this is the only code that writes values to XRefDataBase
}

// locate the given function, searching within lower and upper bounds
void* internal_LocateFunction(iXbSymbolContext* pContext,
                              eLibraryType iLibraryType,
                             const char* szFuncName,
                             uint16_t version,
                             OOVPA* Oovpa,
                             const XbSDBSection* pSection,
                             bool xref_first_pass)
{
    memptr_t buffer_upper = (memptr_t)pSection->buffer_lower + pSection->buffer_size;
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;

    // skip out if this is an unnecessary search
    if (!xref_first_pass && Oovpa->XRefCount == XRefZero && Oovpa->XRefSaveIndex == XRefNoSaveIndex)
        return 0;

    uint32_t derive_indices = 0;
    void* symbol_address = NULL;

    // Check all XRefs are known (if not, don't do a useless scan) :
    for (unsigned int v = 0; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint16_t Offset;

        // get currently registered (un)known address
        GetXRefEntry(Oovpa, v, &XRef, &Offset);
        xbaddr XRefAddr = pContext->xref_database[XRef];
        // Undetermined XRef cannot be checked yet
        if (XRefAddr == XREF_ADDR_UNDETERMINED)
            // Skip this scan over the address range
            return 0;

        // Don't verify an xref that has to be (but isn't yet) derived
        if (XRefAddr == XREF_ADDR_DERIVE) {
            // Mark (up to index 32) which xref needs to be derived
            derive_indices |= (1 << v);
            continue;
        }
    }

    // correct upper bound with highest Oovpa offset
    uint32_t count = Oovpa->Count;
    {
        uint32_t Offset;
        uint8_t Value; // ignored

        GetOovpaEntry(Oovpa, count - 1, &Offset, &Value);
        buffer_upper -= Offset;
    }

    //
    unsigned int detect_selection = Oovpa->DetectSelect;
    unsigned int counter = 0;

    // search all of the buffer memory range
    for (memptr_t cur = pSection->buffer_lower; cur < buffer_upper; cur++) {
        if (CompareOOVPAToAddress(pContext, Oovpa, cur, virt_start_relative)) {

            // Increase the counter whenever detected address is found.
            counter++;

            while (derive_indices > 0) {
                uint32_t XRef;
                uint16_t Offset;
                uint32_t derive_index;

                // Extract an index from the indices mask
                derive_index = BitScanReverse(derive_indices);
                derive_indices ^= (1 << derive_index);

                // get currently registered (un)known address
                GetXRefEntry(Oovpa, derive_index, &XRef, &Offset);

                // Calculate the address where the XRef resides and read the address it points to
                uint32_t XRefAddr = *(uint32_t*)(cur + Offset);

                // NOTE: Commented out code belows are no longer valid since we are using lower and upper passdown only.

                /* For now assume it's a direct reference;
                // TODO : Check if it's PC-relative reference?
                if (XRefAddr + cur + Offset + 4 < XBE_MAX_VA)
                XRefAddr = XRefAddr + cur + Offset + 4;
                */

                // Does the address seem valid?
                /*if (XRefAddr < XBE_MAX_VA) {
                    // save and count the derived address
                    SetXRefDataBase(pContext, XRef, XRefAddr);
                }*/

                // Check if selection is default (zero) then perform the standard procedure.
                if (detect_selection == 0) {
                    if (!pContext->scan_first_detect || (pContext->scan_first_detect && symbol_address == NULL)) {
                        internal_SetXRefDatabase(pContext, iLibraryType, XRef, XRefAddr);
                    }
                }
                // Otherwise, perform a detected selection procedure.
                else {
                    // If counter match the target selection, then save the ref address.
                    if (detect_selection == counter) {
                        internal_SetXRefDatabase(pContext, iLibraryType, XRef, XRefAddr);
                    }
                }
            }

            // Check if selection is default (zero) then perform the standard procedure.
            if (detect_selection == 0) {

                if (symbol_address != NULL) {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                        "Duplicate symbol detection found for %s (%hu), 0x%08x vs 0x%08x",
                        szFuncName, version, symbol_address, cur - virt_start_relative);
                }

                if (!pContext->scan_first_detect || (pContext->scan_first_detect && symbol_address == NULL)) {
                    symbol_address = cur - virt_start_relative;
                }

                if (pContext->one_time_scan) {
                    break;
                }
            }
            // Otherwise, perform a detected selection procedure.
            else {
                // If counter match the detected selection, then perform a force break here
                // with address set.
                if (detect_selection == counter) {
                    symbol_address = cur - virt_start_relative;

                    if (pContext->one_time_scan) {
                        break;
                    }
                }
                // Otherwise, let's log debug info about what is skipped address detection.
                else {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG,
                        "Skipped symbol detection found for %s (%hu), 0x%08x",
                        szFuncName, version, cur - virt_start_relative);
                }
            }
        }
    }

    return symbol_address;
}

#define LocateFunctionCast(pContext, iLibraryType, szFuncName, version, Oovpa, pSection) \
        internal_LocateFunction(pContext, iLibraryType, szFuncName, version, (OOVPA*)Oovpa, pSection, false)

static void internal_RegisterValidXRefAddr(iXbSymbolContext* pContext,
                                           const char* library_name,
                                           uint32_t library_flag,
                                           uint32_t XRefIndex,
                                           uint16_t version,
                                           const char* symbol_name)
{
    xbaddr xSymbolAddr = pContext->xref_database[XRefIndex];

    if (internal_IsXRefAddrValid(xSymbolAddr)) {
        pContext->register_func(library_name, library_flag, symbol_name, xSymbolAddr, version);
    }
}

static void internal_RegisterXRef(iXbSymbolContext* pContext,
                                         const iXbSymbolLibrarySession* pLibrarySession,
                                         uint32_t XRefIndex,
                                         uint16_t version,
                                         const char* symbol_name,
                                         uint32_t symbol_addr,
                                         bool do_register)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    xbaddr xRefAddr = pContext->xref_database[XRefIndex];

    if (internal_IsXRefAddrValid(xRefAddr)) {

        if (pContext->xref_database[XRefIndex] != symbol_addr) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Duplicate XREF address found for %s (%hu), %08X vs %08X!",
                symbol_name, version, xRefAddr, symbol_addr);
        }

        if (pContext->scan_first_detect) {
            return;
        }
    }

    internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XRefIndex, symbol_addr);
    if (do_register && pContext->register_func != NULL) {
        pContext->register_func(pLibrary->name, pLibrary->flag, symbol_name, symbol_addr, version);
    }
}

static void internal_RegisterSymbol(iXbSymbolContext* pContext,
                                    const iXbSymbolLibrarySession* pLibrarySession,
                                    uint32_t XRefIndex,
                                    uint16_t version,
                                    const char* symbol_name,
                                    uint32_t symbol_addr)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // do we need to save the found address?
    if (XRefIndex != XRefNoSaveIndex) {
        // If XRef is not found, save it then register once.
        if (pContext->xref_database[XRefIndex] == XREF_ADDR_UNDETERMINED) {
            internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XRefIndex, symbol_addr);
            if (pContext->register_func != NULL) {
                pContext->register_func(pLibrary->name, pLibrary->flag, symbol_name, symbol_addr, version);
            }
        }
    }
    else if (pContext->register_func != NULL) {
        pContext->register_func(pLibrary->name, pLibrary->flag, symbol_name, symbol_addr, version);
    }
}

static void internal_OOVPA_register(iXbSymbolContext* pContext,
                                    OOVPATable* OovpaTable,
                                    const iXbSymbolLibrarySession* pLibrarySession,
                                    xbaddr address)
{
    if (OovpaTable != NULL) {

        OOVPA* Oovpa = OovpaTable->Oovpa;

        internal_RegisterSymbol(pContext, pLibrarySession, Oovpa->XRefSaveIndex, OovpaTable->Version,
                                       OovpaTable->szFuncName, address);
    }
}

static void internal_OOVPA_scan(iXbSymbolContext* pContext,
                                        OOVPATable* OovpaTable,
                                        unsigned int OovpaTableCount,
                                        const iXbSymbolLibrarySession* pLibrarySession,
                                        const XbSDBSection* pSection,
                                        bool xref_first_pass)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    // traverse the full OOVPA table
    OOVPATable* pLoopEnd = &OovpaTable[OovpaTableCount];
    OOVPATable* pLoop = OovpaTable;
    OOVPATable* pLastKnownSymbol = NULL;
    uint32_t pLastKnownFunc = 0;
    const char* SymbolName = NULL;

    for (; pLoop < pLoopEnd; pLoop++) {

        if (SymbolName == NULL) {
            SymbolName = pLoop->szFuncName;
        } else if (strcmp(SymbolName, pLoop->szFuncName) != 0) {
            SymbolName = pLoop->szFuncName;
            if (pLastKnownSymbol != NULL) {
                // Now that we found the address, store it (regardless if we patch it or not)
                internal_OOVPA_register(pContext, pLastKnownSymbol, pLibrarySession, pLastKnownFunc);
                pLastKnownSymbol = NULL;
                pLastKnownFunc = 0;
            }
        }

        // Skip higher build version
        if (pContext->strict_build_version_limit && pLibrary->build_version < pLoop->Version)
            continue;

        // Search for each function's location using the OOVPA
        xbaddr pFunc = (xbaddr)(uintptr_t)internal_LocateFunction(pContext, iLibraryType, pLoop->szFuncName, pLoop->Version, pLoop->Oovpa, pSection, xref_first_pass);
        if (pFunc == 0) {
            continue;
        }

        if (pFunc == pLastKnownFunc && pLastKnownSymbol == pLoop - 1) {
            //if (g_SymbolAddresses[pLastKnownSymbol->szFuncName] == 0) {
                output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Duplicate OOVPA signature found for %s, %hu vs %hu!", pLastKnownSymbol->szFuncName, pLastKnownSymbol->Version, pLoop->Version);
            //}
        }

        if (pLibrary->build_version < pLoop->Version) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "OOVPA signature is too high for [%hu] %s!", pLoop->Version, pLoop->szFuncName);
        }

        pLastKnownFunc = pFunc;
        pLastKnownSymbol = pLoop;
    }

    if (pLastKnownSymbol != NULL) {
        internal_OOVPA_register(pContext, pLastKnownSymbol, pLibrarySession, pLastKnownFunc);
    }
}

static eLibraryType internal_GetLibraryType(uint32_t library)
{
    switch (library) {
        default:
            return LT_UNKNOWN;
        case XbSymbolLib_D3D8:
        case XbSymbolLib_D3D8LTCG:
            return LT_D3D;
        case XbSymbolLib_DSOUND:
        case XbSymbolLib_XACTENG:
            return LT_AUDIO;
        case XbSymbolLib_JVS:
            return LT_JVS;
        case XbSymbolLib_XAPILIB:
            return LT_XAPI;
        case XbSymbolLib_XGRAPHC:
            return LT_GRAPHIC;
        case XbSymbolLib_XONLINE:
        case XbSymbolLib_XONLINES:
        case XbSymbolLib_XNET:
        case XbSymbolLib_XNETS:
        case XbSymbolLib_XNETN:
            return LT_NETWORK;
    }
}

xbaddr XbSymbolDatabase_GetKernelThunkAddress(const void* xb_header_addr)
{
    xb_xbe_type xbe_type = GetXbeType(xb_header_addr);

    uint32_t kernel_thunk_addr = *(uint32_t*)((uint8_t*)xb_header_addr + 0x0158);
    kernel_thunk_addr ^= XB_XOR_KT[xbe_type];

    return kernel_thunk_addr;
}

static bool internal_SetLibraryTypeStart(iXbSymbolContext* pContext, eLibraryType library_type)
{
    if (!iXbSymbolContext_AllowScanLibrary(pContext)) {
        return false;
    }

    bool ret = false;

    // Accept request if library type is known and is inactive.
    if (library_type < LT_UNKNOWN && !pContext->library_contexts[library_type].is_active) {
        // Then accept the scan request.
        pContext->library_contexts[library_type].is_active = true;
        ret = true;
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type active: %u", library_type);
    }

    iXbSymbolContext_Unlock(pContext);

    return ret;
}

static void internal_SetLibraryTypeEnd(iXbSymbolContext* pContext, eLibraryType library_type)
{
    (void)iXbSymbolContext_Lock(pContext);

    // If library is active, deny the scan request.
    if (!pContext->library_contexts[library_type].is_active) {
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Attempted to set already inactive library type %u.", library_type);
    }

    pContext->library_contexts[library_type].is_active = false;
    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type inactive: %u", library_type);

    iXbSymbolContext_Unlock(pContext);
}

#if 0
bool XbSymbolScanSection(uint32_t xbe_base_address,
                         uint32_t xbe_size,
                         const char* section_name,
                         uint32_t section_virtual_address,
                         uint32_t section_size,
                         uint16_t build_verison,
                         xb_symbol_register_t register_func)
{

    // Invalid argument
    if (section_name == NULL || xbe_size == 0 || section_size == 0 || register_func == NULL) {
        return 0;
    }

    for (uint32_t d2 = 0; d2 < SymbolDBListCount; d2++) {

        if (g_library_flag == 0 || (SymbolDBList[d2].LibSec.library & g_library_flag) > 0) {

            const char* LibraryName = XbSymbolDatabase_LibraryToString(SymbolDBList[d2].LibSec.library);

            //Initialize a matching specific section is currently pair with library in order to scan specific section only.
            //By doing this method will reduce false detection dramatically. If it had happened before.
            for (uint32_t d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                if (SymbolDBList[d2].LibSec.section[d3] != NULL && strcmp(section_name, SymbolDBList[d2].LibSec.section[d3]) == 0) {

                    // traverse the full OOVPA table
                    OOVPATable* pLoopEnd = &SymbolDBList[d2].OovpaTable[SymbolDBList[d2].OovpaTableCount];
                    OOVPATable* pLoop = SymbolDBList[d2].OovpaTable;
                    OOVPATable* pLastKnownSymbol = NULL;
                    uint32_t pLastKnownFunc = 0;
                    const char* SymbolName = NULL;
                    for (; pLoop < pLoopEnd; pLoop++) {

                        if (SymbolName == NULL) {
                            SymbolName = pLoop->szFuncName;
                        } else if (strcmp(SymbolName, pLoop->szFuncName) != 0) {
                            XbSymbolRegisterOOVPA(pLastKnownSymbol, LibraryName, SymbolDBList[d2].LibSec.library, pLastKnownFunc, register_func);

                            SymbolName = pLoop->szFuncName;
                            pLastKnownSymbol = NULL;
                            pLastKnownFunc = 0;
                        }

                        //* NOTE: For time being, let's preserve this code in case we need to re-enable it with updated argument.
                        // Skip higher build version
                        if (build_version < pLoop->Version) {
                            continue;
                        }
                        //*/

                        // Search for each function's location using the OOVPA
                        uint32_t pFunc = XbSymbolLocateFunction(pLoop->Oovpa, section_virtual_address, section_virtual_address+section_size);
                        if (pFunc == 0)
                            continue;

                        pLastKnownFunc = pFunc;
                        pLastKnownSymbol = pLoop;
                    }
                    XbSymbolRegisterOOVPA(pLastKnownSymbol, LibraryName, SymbolDBList[d2].LibSec.library, pLastKnownFunc, register_func);
                    break;
                }
            }
        }
    }
    return 1;
}
#endif

bool XbSymbolDatabase_CreateXbSymbolContext(XbSymbolContextHandle* ppHandle,
                   xb_symbol_register_t register_func,
                   XbSDBLibraryHeader library_input,
                   XbSDBSectionHeader section_input,
                   xbaddr        kernel_thunk)
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

#ifdef MULTI_THREAD_SAFE
    if (mtx_init(&pContext->mutex, mtx_plain) != thrd_success) {
        goto ContextCleanup;
    }
#endif

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
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Kernel thunk is found in %8s section", section->name);

            while (*kt > 0) {
                unsigned int index = *kt & 0x7FFFFFFF;
                // Check if the index is within range, then add to the xreference database.
                if (index > 0 && index < XREF_KT_COUNT) {
                    internal_SetXRefDatabase(pContext, LT_KERNEL, index, kt_addr);
                } else {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                          "Unable to register kernel thunk: index=%u; vaddr=0x%08x", index, kt_addr);
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

    // Request a few fundamental XRefs to be derived instead of checked
    pContext->xref_database[XREF_D3DDEVICE] = XREF_ADDR_DERIVE;                                 //In use
    pContext->xref_database[XREF_D3DRS_CULLMODE] = XREF_ADDR_DERIVE;                            //In use
    pContext->xref_database[XREF_D3DRS_MULTISAMPLERENDERTARGETMODE] = XREF_ADDR_DERIVE;         //In use
    pContext->xref_database[XREF_D3DRS_ROPZCMPALWAYSREAD] = XREF_ADDR_DERIVE;                   //In use
    pContext->xref_database[XREF_D3DRS_ROPZREAD] = XREF_ADDR_DERIVE;                            //In use
    pContext->xref_database[XREF_D3DRS_DONOTCULLUNCOMPRESSED] = XREF_ADDR_DERIVE;               //In use
    pContext->xref_database[XREF_D3DRS_STENCILCULLENABLE] = XREF_ADDR_DERIVE;                   //In use
    pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] = XREF_ADDR_DERIVE;                      //In use
    pContext->xref_database[XREF_G_STREAM] = XREF_ADDR_DERIVE;                                  //In use
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_PIXELSHADER] = XREF_ADDR_DERIVE;
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_TEXTURES] = XREF_ADDR_DERIVE;
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_PALETTES] = XREF_ADDR_DERIVE;
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_RENDERTARGET] = XREF_ADDR_DERIVE;
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_DEPTHSTENCIL] = XREF_ADDR_DERIVE;
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_VERTICALBLANKEVENT] = XREF_ADDR_DERIVE;     //In use
    //pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK] = XREF_ADDR_UNDETERMINED;   //In use // Manual check only.
    //pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_VBLANKCALLBACK] = XREF_ADDR_UNDETERMINED; //In use // Manual check only.
    pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_VERTEXSHADER] = XREF_ADDR_DERIVE;           //In use

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
#ifdef MULTI_THREAD_SAFE
    (void)mtx_lock(&pContext->mutex);
#endif

    for (unsigned int i = 0; i < LT_COUNT; i++) {
        if (pContext->library_contexts[i].is_active) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type is currently active: %u", i);
        }
    }

#ifdef MULTI_THREAD_SAFE
    (void)mtx_unlock(&pContext->mutex);
    mtx_destroy(&pContext->mutex);
#endif

    free(pHandle);
}

static void manual_scan_section_dx8_register_xrefs(iXbSymbolContext* pContext,
                                                   const iXbSymbolLibrarySession* pLibrarySession,
                                                   memptr_t pFunc,
                                                   xbaddr DerivedAddr_D3DRS_CULLMODE,
                                                   uint32_t patchOffset,
                                                   uint32_t Increment,
                                                   uint32_t Decrement)
{
    if (pFunc == NULL) {
        return;
    }
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    // Temporary verification - is XREF_D3DDEVICE derived correctly?
    xbaddr DerivedAddr_D3DDevice = *(xbaddr*)(pFunc + 0x03);
    if (pContext->xref_database[XREF_D3DDEVICE] != DerivedAddr_D3DDevice) {

        if (pContext->xref_database[XREF_D3DDEVICE] != XREF_ADDR_DERIVE) {
            output_message(&pContext->output, XB_OUTPUT_MESSAGE_INFO, "Second derived XREF_D3DDEVICE differs from first!");
        }

        internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XREF_D3DDEVICE, DerivedAddr_D3DDevice);
    }
    pContext->register_func(pLibrary->name, pLibrary->flag, "D3DDEVICE", DerivedAddr_D3DDevice, 0);

    // Temporary verification - is XREF_D3D_RenderState_CullMode derived correctly?
    if (pContext->xref_database[XREF_D3DRS_CULLMODE] != DerivedAddr_D3DRS_CULLMODE) {

        if (pContext->xref_database[XREF_D3DRS_CULLMODE] != XREF_ADDR_DERIVE) {
            output_message(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Second derived XREF_D3D_RenderState_CullMode differs from first!");
        }

        internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XREF_D3DRS_CULLMODE, DerivedAddr_D3DRS_CULLMODE);
    }
    // Register the offset of D3DRS_CULLMODE, this can be used to programatically locate other render-states in the calling program
    pContext->register_func(pLibrary->name, pLibrary->flag, "D3DRS_CULLMODE", DerivedAddr_D3DRS_CULLMODE, 0);

    // Derive address of EmuD3DDeferredRenderState from D3DRS_CULLMODE
    xbaddr EmuD3DDeferredRenderState = DerivedAddr_D3DRS_CULLMODE - Decrement + Increment;
    patchOffset -= Increment;

    // Derive address of a few other deferred render state slots (to help xref-based function location)
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_PSTEXTUREMODES, DerivedAddr_D3DRS_CULLMODE - 11*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_VERTEXBLEND, DerivedAddr_D3DRS_CULLMODE - 10*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_FOGCOLOR, DerivedAddr_D3DRS_CULLMODE - 9*4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_FILLMODE, DerivedAddr_D3DRS_CULLMODE - 8 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_BACKFILLMODE, DerivedAddr_D3DRS_CULLMODE - 7 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_TWOSIDEDLIGHTING, DerivedAddr_D3DRS_CULLMODE - 6 * 4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_NORMALIZENORMALS, DerivedAddr_D3DRS_CULLMODE - 5*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_ZENABLE, DerivedAddr_D3DRS_CULLMODE - 4*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_STENCILENABLE, DerivedAddr_D3DRS_CULLMODE - 3*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_STENCILFAIL, DerivedAddr_D3DRS_CULLMODE - 2*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_FRONTFACE, DerivedAddr_D3DRS_CULLMODE - 1*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_CULLMODE, DerivedAddr_D3DRS_CULLMODE - 0*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_TEXTUREFACTOR, DerivedAddr_D3DRS_CULLMODE + 1*4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_ZBIAS, DerivedAddr_D3DRS_CULLMODE + 2 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_LOGICOP, DerivedAddr_D3DRS_CULLMODE + 3 * 4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_EDGEANTIALIAS, DerivedAddr_D3DRS_CULLMODE + 4*4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLEANTIALIAS, DerivedAddr_D3DRS_CULLMODE + 5 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLEMASK, DerivedAddr_D3DRS_CULLMODE + 6 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLEMODE, DerivedAddr_D3DRS_CULLMODE + 7 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLERENDERTARGETMODE, DerivedAddr_D3DRS_CULLMODE + 8 * 4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_SHADOWFUNC, DerivedAddr_D3DRS_CULLMODE + 9*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_LINEWIDTH, DerivedAddr_D3DRS_CULLMODE + 10*4);

    if (pLibrary->build_version >= 4627 && pLibrary->build_version <= 5933) {// Add XDK 4627
        internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_SAMPLEALPHA, DerivedAddr_D3DRS_CULLMODE + 11 * 4);
    }

    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_DXT1NOISEENABLE, EmuD3DDeferredRenderState + patchOffset - 3 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_YUVENABLE, EmuD3DDeferredRenderState + patchOffset - 2 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_OCCLUSIONCULLENABLE, EmuD3DDeferredRenderState + patchOffset - 1 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_STENCILCULLENABLE, EmuD3DDeferredRenderState + patchOffset + 0 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_ROPZCMPALWAYSREAD, EmuD3DDeferredRenderState + patchOffset + 1 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_ROPZREAD, EmuD3DDeferredRenderState + patchOffset + 2 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_DONOTCULLUNCOMPRESSED, EmuD3DDeferredRenderState + patchOffset + 3 * 4);

    pContext->register_func(pLibrary->name, pLibrary->flag, "D3DDeferredRenderState", EmuD3DDeferredRenderState, 0);
}

static void manual_scan_section_dx8_register_D3DTSS(iXbSymbolContext* pContext,
                                                    const iXbSymbolLibrarySession* pLibrarySession,
                                                    memptr_t pFunc,
                                                    uint32_t pXRefOffset)
{
    if (pFunc == NULL) {
        return;
    }
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    xbaddr DerivedAddr_D3DTSS_TEXCOORDINDEX = 0;
    int Decrement = 0x70; // TODO : Rename into something understandable

    // TODO : Remove this when XREF_D3D_TextureState_TexCoordIndex derivation is deemed stable
    {
        DerivedAddr_D3DTSS_TEXCOORDINDEX = *(xbaddr*)(pFunc + pXRefOffset);

        // Temporary verification - is XREF_D3DTSS_TEXCOORDINDEX derived correctly?
        if (pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] != DerivedAddr_D3DTSS_TEXCOORDINDEX) {

            if (pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] != XREF_ADDR_DERIVE) {
                output_message(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Second derived XREF_D3DTSS_TEXCOORDINDEX differs from first!");
            }

            //SetXRefDataBase(pContext, iLibraryType, XREF_D3DTSS_BUMPENV, DerivedAddr_D3DTSS_TEXCOORDINDEX - 28*4);
            internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DTSS_TEXCOORDINDEX, DerivedAddr_D3DTSS_TEXCOORDINDEX);
            //SetXRefDataBase(pContext, iLibraryType, XREF_D3DTSS_BORDERCOLOR, DerivedAddr_D3DTSS_TEXCOORDINDEX + 1*4);
            //SetXRefDataBase(pContext, iLibraryType, XREF_D3DTSS_COLORKEYCOLOR, DerivedAddr_D3DTSS_TEXCOORDINDEX + 2*4);
        }
    }

    uint32_t EmuD3DDeferredTextureState = DerivedAddr_D3DTSS_TEXCOORDINDEX - Decrement;

    pContext->register_func(pLibrary->name, pLibrary->flag, "D3DDeferredTextureState", EmuD3DDeferredTextureState, 0);
}

static void manual_scan_section_dx8_register_stream(iXbSymbolContext* pContext,
                                                    const iXbSymbolLibrarySession* pLibrarySession,
                                                    memptr_t pFunc,
                                                    uint32_t iCodeOffsetFor_g_Stream)
{
    if (pFunc == NULL) {
        return;
    }
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // Read address of Xbox_g_Stream from D3DDevice_SetStreamSource
    uint32_t Derived_g_Stream = *((uint32_t*)(pFunc + iCodeOffsetFor_g_Stream));

    // Temporary verification - is XREF_G_STREAM derived correctly?
    // TODO : Remove this when XREF_G_STREAM derivation is deemed stable
#if 0  // TODO: How can we enforce it for callback?
    VerifySymbolAddressAgainstXRef("g_Stream", Derived_g_Stream, XREF_G_STREAM);
#endif

    // Now that both Derived XREF and OOVPA-based function-contents match,
    // correct base-address (because "g_Stream" is actually "g_Stream"+8") :
    Derived_g_Stream -= 8;
    pContext->register_func(pLibrary->name, pLibrary->flag, "g_Stream", Derived_g_Stream, 0);
}

static bool manual_scan_section_dx8(iXbSymbolContext* pContext,
                                    const iXbSymbolLibrarySession* pLibrarySession,
                                    const XbSDBSection* pSection)
{
    // Generic usage
    memptr_t pFunc = 0;
    xbaddr xSymbolAddr = 0;
    // offset for stencil cull enable render state in the deferred render state buffer
    uint32_t DerivedAddr_D3DRS_CULLMODE = 0;
    int Decrement = 0; // TODO : Rename into something understandable
    int Increment = 0; // TODO : Rename into something understandable
    int patchOffset = 0; // TODO : Rename into something understandable
    int OOVPA_version;
    int iCodeOffsetFor_g_Stream;
    int pXRefOffset = 0; // TODO : Rename into something understandable
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    // TODO: Why do we need this? Also, can we just scan library versions for this only?
    // Save D3D8 build version
    //g_BuildVersion = BuildVersion;

    if (pLibrary->flag == XbSymbolLib_D3D8) {

        // locate D3DDevice_SetRenderState_CullMode first
        if (pLibrary->build_version < 3911) {
            // Not supported, currently ignored.
        }
        else if (pLibrary->build_version < 4034) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetRenderState_CullMode", 3911,
                &D3DDevice_SetRenderState_CullMode_3911, pSection);
        }
        else {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetRenderState_CullMode", 4034,
                &D3DDevice_SetRenderState_CullMode_4034, pSection);
        }

        // then locate D3DDeferredRenderState
        if (pFunc != 0) {
            // NOTE: Is a requirement to align properly.
            pFunc += virt_start_relative;

            // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
            // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
            if (pLibrary->build_version < 3911) {
                // Not supported, currently ignored.
            }
            else if (pLibrary->build_version < 4034) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x25);
                Decrement = 0x1FC;  // TODO: Clean up (?)
                Increment = 82 * 4;
                patchOffset = 140 * 4; // Verified 3925 and 3948

                //Decrement = 0x19F;  // TODO: Clean up (?)
                //Increment = 72 * 4;
                //patchOffset = 142*4; // TODO: Verify
            }
            else if (pLibrary->build_version <= 4361) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x200;
                Increment = 82 * 4;
                patchOffset = 142 * 4;
            }
            else if (pLibrary->build_version < 4627) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x204;
                Increment = 83 * 4;
                patchOffset = 143 * 4;
            }
            else { // 4627-5933
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x24C;
                Increment = 92 * 4;
                patchOffset = 162 * 4;
            }
        }
    }
    else { // D3D8LTCG
        // locate D3DDevice_SetRenderState_CullMode first
        pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetRenderState_CullMode", 1045,
            &D3DDevice_SetRenderState_CullMode_1045, pSection);
        pXRefOffset = 0x2D; // verified for 3925
        if (pFunc == 0) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetRenderState_CullMode", 1049,
                &D3DDevice_SetRenderState_CullMode_1049, pSection);
            pXRefOffset = 0x31; // verified for 4039
        }

        if (pFunc == 0) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetRenderState_CullMode", 1052,
                &D3DDevice_SetRenderState_CullMode_1052, pSection);
            pXRefOffset = 0x34;
        }

        if (pFunc == 0) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetRenderState_CullMode", 1053,
                &D3DDevice_SetRenderState_CullMode_1053, pSection);
            pXRefOffset = 0x35;
        }

        // then locate D3DDeferredRenderState
        if (pFunc != 0) {
            // NOTE: Is a requirement to align properly.
            pFunc += virt_start_relative;

            // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
            // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
            if (pLibrary->build_version < 3911) {
                // Not supported, currently ignored.
            }
            else if (pLibrary->build_version < 4034) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x1FC;  // TODO: Clean up (?)
                Increment = 82 * 4;
                patchOffset = 140 * 4; // Verified 3925 and 3948

                //Decrement = 0x19F;  // TODO: Clean up (?)
                //Increment = 72 * 4;
                //patchOffset = 142*4; // TODO: Verify
            }
            else if (pLibrary->build_version <= 4361) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x200;
                Increment = 82 * 4;
                patchOffset = 142 * 4;
            }
            else if (pLibrary->build_version < 4627) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x204;
                Increment = 83 * 4;
                patchOffset = 143 * 4;
            }
            else { // 4627-5933
                // NOTE: Burnout 3 is (pFunc + 0x34), Black is (pFunc + 0x35)
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x24C;
                Increment = 92 * 4;
                patchOffset = 162 * 4;
            }
        }
    }
    manual_scan_section_dx8_register_xrefs(pContext, pLibrarySession, pFunc, DerivedAddr_D3DRS_CULLMODE, patchOffset, Increment, Decrement);

    // then locate D3DDeferredTextureState
    if (pLibrary->flag == XbSymbolLib_D3D8) {

        if (pLibrary->build_version < 3911) {
            // Not supported, currently ignored.
            pFunc = 0;
        }
        else if (pLibrary->build_version < 4034) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 3911,
                &D3DDevice_SetTextureState_TexCoordIndex_3911, pSection);
            pXRefOffset = 0x11;
        }
        else if (pLibrary->build_version < 4242) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 4034,
                &D3DDevice_SetTextureState_TexCoordIndex_4034, pSection);
            pXRefOffset = 0x18;
        }
        else if (pLibrary->build_version < 4627) {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 4242,
                &D3DDevice_SetTextureState_TexCoordIndex_4242, pSection);
            pXRefOffset = 0x19;
        }
        else {
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 4627,
                &D3DDevice_SetTextureState_TexCoordIndex_4627, pSection);
            pXRefOffset = 0x19;
        }
    }
    else { // D3D8LTCG
        // verified for 3925
        pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_0", 2039,
            &D3DDevice_SetTextureState_TexCoordIndex_0_2039, pSection);
        pXRefOffset = 0x08;

        if (pFunc == 0) { // verified for 4039
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2040,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2040, pSection);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4432
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 1944,
                &D3DDevice_SetTextureState_TexCoordIndex_1944, pSection);
            pXRefOffset = 0x19;
        }

        if (pFunc == 0) { // verified for 4531
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2045,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2045, pSection);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4627 and higher
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2058,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2058, pSection);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4627 and higher
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 1958,
                &D3DDevice_SetTextureState_TexCoordIndex_1958, pSection);
            pXRefOffset = 0x19;
        }

        if (pFunc == 0) { // verified for World Series Baseball 2K3
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2052,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2052, pSection);
            pXRefOffset = 0x15;
        }

        if (pFunc == 0) { // verified for Ski Racing 2006
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_0", 2058,
                &D3DDevice_SetTextureState_TexCoordIndex_0_2058, pSection);
            pXRefOffset = 0x15;
        }
    }

    if (pFunc != 0) {
        // NOTE: Is a requirement to align properly.
        pFunc += virt_start_relative;
        manual_scan_section_dx8_register_D3DTSS(pContext, pLibrarySession, pFunc, pXRefOffset);
    }

    // Locate Xbox symbol "g_Stream" and store it's address
    pFunc = 0;
    // verified for D3D8 with 4361, 4627, 5344, 5558, 5659, 5788, 5849, 5933
    // and verified for LTCG with 4432, 4627, 5344, 5558, 5849
    iCodeOffsetFor_g_Stream = 0x22;

    if (pLibrary->flag == XbSymbolLib_D3D8) {
        if (pLibrary->build_version >= 4034) {
            OOVPA_version = 4034;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 4034,
                &D3DDevice_SetStreamSource_4034, pSection);
        }
        else {
            OOVPA_version = 3911;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 3911,
                &D3DDevice_SetStreamSource_3911, pSection);
            iCodeOffsetFor_g_Stream = 0x23; // verified for 3911
        }
    }
    else { // D3D8LTCG
        if (pLibrary->build_version > 4039) {
            OOVPA_version = 4034; // TODO Verify
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 1044,
                &D3DDevice_SetStreamSource_1044, pSection);
        }

        if (pFunc == 0) { // LTCG specific
            OOVPA_version = 4034; // TODO Verify
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource_4", 2058,
                &D3DDevice_SetStreamSource_4_2058, pSection);
            iCodeOffsetFor_g_Stream = 0x1E;
        }

        if (pFunc == 0) { // verified for 4039
            OOVPA_version = 4034;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource_8", 2040,
                &D3DDevice_SetStreamSource_8_2040, pSection);
            iCodeOffsetFor_g_Stream = 0x23;
        }

        if (pFunc == 0) { // verified for 3925
            OOVPA_version = 3911;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 1039,
                &D3DDevice_SetStreamSource_1039, pSection);
            iCodeOffsetFor_g_Stream = 0x47;
        }
    }

    if (pFunc != 0) {
        // NOTE: Is a requirement to align properly.
        pFunc += virt_start_relative;

        manual_scan_section_dx8_register_stream(pContext, pLibrarySession, pFunc, iCodeOffsetFor_g_Stream);
    }

    // Manual check require for able to self-register these symbols:
    // * D3DDevice_SetSwapCallback
    // * D3DDevice_SetVerticalBlankCallback

    // First, check if D3D__PDEVICE is found.
    if (pContext->xref_database[XREF_D3DDEVICE] != XREF_ADDR_DERIVE &&
        // Then, check at least one of symbol's member variable is not found.
        pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK] == XREF_ADDR_UNDETERMINED) {

        // Scan if event handle variable is not yet derived.
        if (pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_VERTICALBLANKEVENT] == XREF_ADDR_DERIVE) {
            xSymbolAddr = (xbaddr)(uintptr_t)LocateFunctionCast(pContext, iLibraryType, "D3DDevice__m_VerticalBlankEvent__ManualFindGeneric_3911", 3911,
                &D3DDevice__m_VerticalBlankEvent__ManualFindGeneric_3911, pSection);
        }

        // We are not registering D3DDevice__m_VerticalBlankEvent__ManualFindGeneric itself, as it is NOT a symbol.


        // If not found, skip manual register.
        if (pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_VERTICALBLANKEVENT] == XREF_ADDR_DERIVE) {
            return false;
        }

        // Finally, manual register the symbol variables.
        xSymbolAddr = pContext->xref_database[XREF_OFFSET_D3DDEVICE_M_VERTICALBLANKEVENT];
        internal_SetXRefDatabase(pContext, iLibraryType, XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK, xSymbolAddr - 8);
        internal_SetXRefDatabase(pContext, iLibraryType, XREF_OFFSET_D3DDEVICE_M_VBLANKCALLBACK, xSymbolAddr - 4);
    }
    // If D3D__PDEVICE is not found, the scan is not complete
    // and will continue scan to next given section.
    else {
        return false;
    }

    return true;
}

static bool manual_scan_section_dsound(iXbSymbolContext* pContext,
                                       const iXbSymbolLibrarySession* pLibrarySession,
                                       const XbSDBSection* pSection)
{
    // Generic usage
    xbaddr xblower = pSection->xb_virt_addr;
    xbaddr xbupper = pSection->xb_virt_addr + pSection->buffer_size;
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;
    xbaddr xFuncAddr = 0;
    memptr_t pFuncAddr = 0;
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    /*
    bool testRun = 1;
    while (testRun) {
    }//*/

    // Scan for DirectSoundStream's constructor function.
    if (pContext->xref_database[XREF_CDirectSoundStream_Constructor] == XREF_ADDR_UNDETERMINED) {
        xFuncAddr = (xbaddr)(uintptr_t)LocateFunctionCast(pContext, iLibraryType, "CDirectSoundStream_Constructor", 3911,
            &CDirectSoundStream_Constructor_3911, pSection);

        // If not found, skip the rest of the scan.
        if (xFuncAddr == 0) {
            return false;
        }

        internal_RegisterSymbol(pContext, pLibrarySession, XREF_CDirectSoundStream_Constructor, 3911,
            "CDirectSoundStream_Constructor", xFuncAddr);

        // TODO: If possible, integrate into the OOVPA structure.
        internal_RegisterXRef(pContext, pLibrarySession, XREF_DSS_VOICE_VTABLE, 3911,
            NULL, *(xbaddr*)(virt_start_relative + xFuncAddr + 0x14), false);
        internal_RegisterXRef(pContext, pLibrarySession, XREF_DSS_STREAM_VTABLE, 3911,
            NULL, *(xbaddr*)(virt_start_relative + xFuncAddr + 0x1B), false);
    }

    // Verify both variables are already set from the scan function above.
    if (pContext->xref_database[XREF_DSS_STREAM_VTABLE] == XREF_ADDR_DERIVE ||
        pContext->xref_database[XREF_DSS_VOICE_VTABLE] == XREF_ADDR_DERIVE) {

        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Something went wrong with finding DSS' vtables...");
        return false;
    }

    // Finally, manually add CDirectSoundStream's AddRef and Release functions.
    if (pContext->xref_database[XREF_CDirectSoundStream_AddRef] == XREF_ADDR_UNDETERMINED) {
        xbaddr vtable = pContext->xref_database[XREF_DSS_STREAM_VTABLE];

        if (xblower <= vtable && vtable < xbupper) {
            pFuncAddr = (memptr_t)virt_start_relative + vtable;

            internal_RegisterSymbol(pContext, pLibrarySession, XREF_CDirectSoundStream_AddRef, 3911,
                "CDirectSoundStream_AddRef", *(uint32_t*)(pFuncAddr + 0 * 4));

            internal_RegisterSymbol(pContext, pLibrarySession, XREF_CDirectSoundStream_Release, 3911,
                "CDirectSoundStream_Release", *(uint32_t*)(pFuncAddr + 1 * 4));

            internal_RegisterSymbol(pContext, pLibrarySession, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_GetInfo", *(uint32_t*)(pFuncAddr + 2 * 4));

            internal_RegisterSymbol(pContext, pLibrarySession, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_GetStatus", *(uint32_t*)(pFuncAddr + 3 * 4));

            internal_RegisterSymbol(pContext, pLibrarySession, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_Process", *(uint32_t*)(pFuncAddr + 4 * 4));

            internal_RegisterSymbol(pContext, pLibrarySession, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_Discontinuity", *(uint32_t*)(pFuncAddr + 5 * 4));

            internal_RegisterSymbol(pContext, pLibrarySession, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_Flush", *(uint32_t*)(pFuncAddr + 6 * 4));

            // NOTE: it is possible to manual add GetInfo, GetStatus, Process, Discontinuity,
            // and Flush functions.
        }
        else {
            return false;
        }

    }

    return true;
}

static bool manual_scan_library_custom(iXbSymbolContext* pContext,
                                       custom_scan_func_t custom_scan_func,
                                       const iXbSymbolLibrarySession* pLibSession)
{
    bool scan_ret = false;

    const XbSDBSection* pSectionScan;

    for (unsigned int d2 = 0; d2 < SymbolDBListCount; d2++) {

        if ((pLibSession->pLibrary->flag & SymbolDBList[d2].LibSec.library) > 0) {
            for (unsigned int s = 0; s < pContext->section_input.count; s++) {

                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                // By doing this method will reduce false detection dramatically. If it had happened before.
                for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                    if (SymbolDBList[d2].LibSec.section[d3] != NULL &&
                        strncmp(pContext->section_input.filters[s].name, SymbolDBList[d2].LibSec.section[d3], 8) == 0) {

                        pSectionScan = pContext->section_input.filters + s;

                        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section",
                                              pLibSession->pLibrary->name, pSectionScan->name);

                        scan_ret = custom_scan_func(pContext, pLibSession, pSectionScan);

                        if (scan_ret) {
                            // let's return true here instead of waste the loops for nothing.
                            return scan_ret;
                        }
                    }
                }
            }
            // Use the break if there are 2+ bit flags set such as include LTCG flag in std flag's oovpa database like D3D8.
            if ((SymbolDBList[d2].LibSec.library & ~pLibSession->pLibrary->flag) == 0) {
                break;
            }
        }
    }
    return scan_ret;
}

void XbSymbolContext_ScanManual(XbSymbolContextHandle pHandle)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (!iXbSymbolContext_Lock(pContext)) {
        return;
    }

    if (pContext->scan_stage >= SS_1_MANUAL) {
        output_message(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Manual rescan request is skip.");
        goto skipScan;
    }
    pContext->scan_stage = SS_1_MANUAL;

    for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {

        const XbSDBLibrary* pLibrary = pContext->library_input.filters + lv;
        eLibraryType i_LibraryType = internal_GetLibraryType(pLibrary->flag);

        if (i_LibraryType >= LT_UNKNOWN) {
            continue;
        }

        iXbSymbolLibrarySession libSession;
        libSession.pLibrary = pLibrary;
        libSession.iLibraryType = i_LibraryType;

        if ((pLibrary->flag & (XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG)) > 0) {
            // TODO: Do we need to check twice?
            // Initialize a matching specific section is currently pair with library in order to scan specific section only.
            // By doing this method will reduce false detection dramatically. If it had happened before.
            manual_scan_library_custom(pContext, manual_scan_section_dx8, &libSession);
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
    }

    pContext->scan_stage = SS_2_SCAN_LIBS;

    skipScan:;
#ifdef MULTI_THREAD_SAFE
    (void)mtx_unlock(&pContext->mutex);
#endif
}

unsigned int XbSymbolContext_ScanLibrary(XbSymbolContextHandle pHandle,
                                  const XbSDBLibrary* pLibrary,
                                  bool xref_first_pass)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;
    eLibraryType iLibraryType = internal_GetLibraryType(pLibrary->flag);

    if (iLibraryType >= LT_UNKNOWN) {
        return 0;
    }

    iXbSymbolLibrarySession librarySession;
    librarySession.pLibrary = pLibrary;
    librarySession.iLibraryType = iLibraryType;

    unsigned int xref_count = pContext->library_contexts[iLibraryType].xref_registered;

    if (!iXbSymbolContext_AllowScanLibrary(pContext)) {
        return 0;
    }

    // If library type is active, do nothing.
    if (!internal_SetLibraryTypeStart(pContext, iLibraryType)) {
        return 0;
    }

    for (unsigned int d2 = 0; d2 < SymbolDBListCount; d2++) {

        if ((pLibrary->flag & SymbolDBList[d2].LibSec.library) > 0) {
            for (unsigned int s = 0; s < pContext->section_input.count; s++) {

                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                // By doing this method will reduce false detection dramatically. If it had happened before.
                for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                    if (SymbolDBList[d2].LibSec.section[d3] != NULL &&
                        strncmp(pContext->section_input.filters[s].name, SymbolDBList[d2].LibSec.section[d3], 8) == 0) {

                        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section",
                                              pLibrary->name, SymbolDBList[d2].LibSec.section[d3]);

                        internal_OOVPA_scan(pContext, SymbolDBList[d2].OovpaTable, SymbolDBList[d2].OovpaTableCount,
                                            &librarySession, pContext->section_input.filters + s, xref_first_pass);
                        break;
                    }
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

    uint32_t library_filter = pContext->library_filter;

    bool xref_first_pass = true; // Set to true for search speed optimization

    unsigned int LastUnResolvedXRefs = 0;
    unsigned int CurrentUnResolvedXRefs = 0;

    if (!iXbSymbolContext_AllowScanLibrary(pContext)) {
        return;
    }

    do {
        LastUnResolvedXRefs = CurrentUnResolvedXRefs;

        for (unsigned int lv = 0; lv < pContext->library_input.count; lv++) {
            const XbSDBLibrary* library = pContext->library_input.filters + lv;

            do {
                // Temporary placeholder until v2.0 API's section scan function is ready or may be permanent in here.
                // Skip specific library if third-party set to specific library.
                if (!(library_filter == 0 || (library_filter & library->flag) > 0)) {
                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Skipping %.8s (%hu) scan.", library->name, library->build_version);
                }
                else {

                    // Start library scan against symbol database we want to search for address of symbols and xreferences.
                    CurrentUnResolvedXRefs += XbSymbolContext_ScanLibrary(pHandle, library, xref_first_pass);
                }

                break;
            } while (true);
        }

        xref_first_pass = false;
    } while (LastUnResolvedXRefs < CurrentUnResolvedXRefs);
}

// Does individual registration of derived XRef's that are useful but not yet registered.
// Called after entire scan.
void XbSymbolContext_RegisterXRefs(XbSymbolContextHandle pHandle)
{
    iXbSymbolContext* pContext = (iXbSymbolContext*)pHandle;

    if (pContext->register_func == NULL) return;

    if (!iXbSymbolContext_Lock(pContext)) {
        return;
    }

    xbaddr xD3D_pDeviceAddr = pContext->xref_database[XREF_D3DDEVICE];
    if (internal_IsXRefAddrValid(xD3D_pDeviceAddr)) {
        // Register offset of D3DDevice__m_VertexShader
        internal_RegisterValidXRefAddr(pContext, Lib_D3D8, XbSymbolLib_D3D8, XREF_OFFSET_D3DDEVICE_M_VERTEXSHADER, 0, "D3DDevice__m_VertexShader_OFFSET");
    }

    // Here, others could be registered

    iXbSymbolContext_Unlock(pContext);
}

// Aka the basic example to handle the scan process.
bool XbSymbolScan(const void* xb_header_addr,
                  xb_symbol_register_t register_func,
                  bool is_raw)
{
    bool bCheckJVS = false;

    XbSymbolContextHandle pHandle;
    iXbSymbolContext* iContext;
    XbSDBLibraryHeader library_input;
    XbSDBSectionHeader section_input;

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

    //SectionCleanup:
    free(section_input.filters);

    LibraryCleanup:
    free(library_input.filters);

    return false;
}

// ******************************************************************
// * XbSymbolDatabase_LibraryVersion
// ******************************************************************

// Adapted from https://gist.github.com/underscorediscovery/81308642d0325fd386237cfa3b44785c
#define fnv1aprime 0x1000193;
void hash_fnv1a(unsigned int* hash, const void* key, const size_t len)
{
    const char* data = (char*)key;
    for (unsigned int i = 0; i < len; ++i) {
        unsigned char value = data[i];
        *hash ^= value;
        *hash *= fnv1aprime;
    }
}

void HashAssumedLOOVPA(unsigned int* Hash, const OOVPA* pAssumedLOOVPA)
{
    // Number of offset-value pairs in the "Header" LOOVPA structure
    unsigned int Size = pAssumedLOOVPA->Count * sizeof(LOVP);

    // Size of "Header" structure
    Size += sizeof(OOVPA);

    // Part 1: The array of OOVPA::LOVP items
    hash_fnv1a(Hash, pAssumedLOOVPA, Size);
}

void HashOOVPATable(unsigned int* Hash, const OOVPATable* pTable)
{
    // Part 1: function name string
    if (pTable->szFuncName != NULL) {
        hash_fnv1a(Hash, pTable->szFuncName, strlen(pTable->szFuncName));
    }

    // Part 2: version number
    hash_fnv1a(Hash, &pTable->Version, sizeof(pTable->Version));

    // Part 3: LOOVPA
    if (pTable->Oovpa) {
        HashAssumedLOOVPA(Hash, pTable->Oovpa);
    }
}

void HashSymbolData(unsigned int* Hash, SymbolDatabaseList* pData)
{
    for (unsigned int i = 0; i < pData->OovpaTableCount; ++i) {
        HashOOVPATable(Hash, &pData->OovpaTable[i]);
    }
}

const unsigned int HashSymbolDataArray(SymbolDatabaseList* pDataArray, unsigned int Count)
{
    unsigned int Hash = 0x811c9dc5;
    for (unsigned int i = 0; i < Count; ++i) {
        HashSymbolData(&Hash, pDataArray + i);
    }
    return Hash;
}

unsigned int XbSymbolDatabase_LibraryVersion()
{
    // Calculate this just once
    static unsigned int CalculatedHash = 0;
    if (CalculatedHash == 0) {
        CalculatedHash = HashSymbolDataArray(SymbolDBList, SymbolDBListCount);
    }
    return CalculatedHash;
}


// ******************************************************************
// * XbSymbolDatabase_TestOOVPAs
// ******************************************************************

typedef struct _SymbolDatabaseVerifyContext {
    SymbolDatabaseList* main_data;
    OOVPA* oovpa,* against;
    SymbolDatabaseList* against_data;
    uint32_t main_index, against_index;
    OutputHandler output;
} SymbolDatabaseVerifyContext;

static int OOVPAErrorString(char* bufferTemp, SymbolDatabaseList* data, uint32_t index)
{
    // Convert active data pointer to an index base on starting point of SymbolDBList.
    unsigned int db_index = (unsigned int)(data - SymbolDBList);

    return sprintf(bufferTemp, "OOVPATable db=%2u, b=%4hu, i=[%4u] s=%s", db_index, data->OovpaTable[index].Version, index, data->OovpaTable[index].szFuncName);
}

static void SymbolDatabaseVerifyContext_OOVPAError(SymbolDatabaseVerifyContext* context, char* format, ...)
{
    char buffer[2048] = { 0 };
    static char bufferTemp[400] = { 0 };
    int ret_str_count;

    if (context->main_data != NULL) {

        ret_str_count = OOVPAErrorString(bufferTemp, context->main_data, context->main_index);
        (void)strncat(buffer, bufferTemp, ret_str_count);
    }

    if (context->against != NULL && context->against_data != NULL) {
        (void)strcat(buffer, ", comparing against ");

        ret_str_count = OOVPAErrorString(bufferTemp, context->against_data, context->against_index);
        (void)strncat(buffer, bufferTemp, ret_str_count);
    }

    // format specific error message
    va_list args;
    va_start(args, format);
    ret_str_count = vsprintf(bufferTemp, format, args);
    va_end(args);


    (void)strcat(buffer, " : ");
    (void)strncat(buffer, bufferTemp, ret_str_count);

    output_message(&context->output, XB_OUTPUT_MESSAGE_ERROR, buffer);
}

static unsigned int SymbolDatabaseVerifyContext_VerifyDatabaseList(SymbolDatabaseVerifyContext* context); // forward

static unsigned int SymbolDatabaseVerifyContext_VerifyOOVPA(SymbolDatabaseVerifyContext* context, OOVPA* oovpa)
{
    unsigned int error_count = 0;

    if (context->against == NULL) {
        // TODO : verify XRefSaveIndex and XRef's (how?)

        // verify offsets are in increasing order
        uint32_t prev_offset;
        uint8_t dummy_value;
        GetOovpaEntry(oovpa, oovpa->XRefCount, &prev_offset, &dummy_value);
        for (int p = oovpa->XRefCount + 1; p < oovpa->Count; p++) {
            uint32_t curr_offset;
            GetOovpaEntry(oovpa, p, &curr_offset, &dummy_value);

            if (!(curr_offset > prev_offset)) {
                error_count++;
                SymbolDatabaseVerifyContext_OOVPAError(context, "Lovp[%2u] : Offset (0x%03x) must be larger then previous offset (0x%03x)",
                         p, curr_offset, prev_offset);
            }
            prev_offset = curr_offset;
        }

        // find duplicate OOVPA's across all other data-table-oovpa's
        context->oovpa = oovpa;
        context->against = oovpa;
        error_count += SymbolDatabaseVerifyContext_VerifyDatabaseList(context);
        context->against = NULL; // reset scanning state
        return error_count;
    }

    // prevent checking an oovpa against itself
    if ((context->main_data + context->main_index) == (context->against_data + context->against_index)) {
        return error_count;
    }

    // compare {Offset, Value}-pairs between two OOVPA's
    OOVPA* left = context->against,* right = oovpa;
    int l = 0, r = 0;
    uint32_t left_offset, right_offset;
    uint8_t left_value, right_value;
    GetOovpaEntry(left, l, &left_offset, &left_value);
    GetOovpaEntry(right, r, &right_offset, &right_value);
    int unique_offset_left = 0;
    int unique_offset_right = 0;
    int equal_offset_value = 0;
    int equal_offset_different_value = 0;

    while (true) {
        bool left_next = true;
        bool right_next = true;

        if (left_offset < right_offset) {
            unique_offset_left++;
            right_next = false;
        } else if (left_offset > right_offset) {
            unique_offset_right++;
            left_next = false;
        } else if (left_value == right_value) {
            equal_offset_value++;
        } else {
            equal_offset_different_value++;
        }

        // increment r before use (in left_next)
        if (right_next) {
            r++;
        }

        if (left_next) {
            l++;
            if (l >= left->Count) {
                unique_offset_right += right->Count - r;
                break;
            }

            GetOovpaEntry(left, l, &left_offset, &left_value);
        }

        if (right_next) {
            if (r >= right->Count) {
                unique_offset_left += left->Count - l;
                break;
            }

            GetOovpaEntry(right, r, &right_offset, &right_value);
        }
    }

    bool unique_detect_select;
    // First, let's make sure DetectSelect is the same
    if ((left->DetectSelect == right->DetectSelect) ||
        // Or left OOVPA is set to default detect and is different than right detect select.
        (left->DetectSelect == 0 && left->DetectSelect != right->DetectSelect) ||
        // Or right OOVPA is set to default detect and is different than left detect select.
        (right->DetectSelect == 0 && left->DetectSelect != right->DetectSelect)) {
        unique_detect_select = false;
    }
    // When above checks are not found, then we know the detected selection is unique.
    // Therefore ignore the OOVPA identical error.
    else {
        unique_detect_select = true;
    }

    // no mismatching values on identical offsets?
    if (equal_offset_different_value == 0) {
        // enough matching OV-pairs?
        if (equal_offset_value > 4) {
            // no unique OV-pairs on either side?
            if (unique_offset_left + unique_offset_right == 0) {
                // If detect selection is not unique, then make an error report.
                if (!unique_detect_select) {
                    error_count++;
                    SymbolDatabaseVerifyContext_OOVPAError(context, "OOVPA's are identical",
                               unique_offset_left,
                               unique_offset_right);
                }
            } else {
                // not too many new OV-pairs on the left side?
                if (unique_offset_left < 6) {
                    // not too many new OV-pairs on the right side?
                    if (unique_offset_right < 6) {
                        error_count++;
                        SymbolDatabaseVerifyContext_OOVPAError(context, "OOVPA's are expanded (left +%d, right +%d)",
                                   unique_offset_left,
                                   unique_offset_right);
                    }
                }
            }
        }
    }
    return error_count;
}

static unsigned int SymbolDatabaseVerifyContext_VerifyEntry(SymbolDatabaseVerifyContext* context, const OOVPATable* table, uint32_t index)
{
    if (context->against == NULL) {
        context->main_index = index;
    } else {
        context->against_index = index;
    }

    // verify the OOVPA of this entry
    if (table[index].Oovpa != NULL) {
        return SymbolDatabaseVerifyContext_VerifyOOVPA(context, table[index].Oovpa);
    }
    return 0;
}

static unsigned int SymbolDatabaseVerifyContext_VerifyDatabase(SymbolDatabaseVerifyContext* context, SymbolDatabaseList* data)
{
    unsigned int error_count = 0;
    if (context->against == NULL) {
        context->main_data = data;
    } else {
        context->against_data = data;
    }

    // Verify each entry in data's OOVPA table.
    for (uint32_t e = 0; e < data->OovpaTableCount; e++) {
        error_count += SymbolDatabaseVerifyContext_VerifyEntry(context, data->OovpaTable, e);
    }
    return error_count;
}

static unsigned int SymbolDatabaseVerifyContext_VerifyDatabaseList(SymbolDatabaseVerifyContext* context)
{
    unsigned int error_count = 0;
    // verify all SymbolDatabaseList's
    for (uint32_t d = 0; d < SymbolDBListCount; d++) {
        error_count += SymbolDatabaseVerifyContext_VerifyDatabase(context, &SymbolDBList[d]);
    }
    return error_count;
}

unsigned int XbSymbolDatabase_TestOOVPAs()
{
    SymbolDatabaseVerifyContext context = { 0 };
    context.output.func = g_output_func;
    context.output.verbose_level = g_output_verbose_level;
    return SymbolDatabaseVerifyContext_VerifyDatabaseList(&context);
}

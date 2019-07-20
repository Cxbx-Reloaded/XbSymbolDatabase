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
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
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

#include "XbSymbolDatabase.h"
#include "Xbe.h"

// ******************************************************************
// * Xbox Symbol OOVPA Database
// ******************************************************************

#include "OOVPADatabase/Xapi_OOVPA.inl"
#include "OOVPADatabase/D3D8_OOVPA.inl"
#include "OOVPADatabase/D3D8LTCG_OOVPA.inl"
#include "OOVPADatabase/DSound_OOVPA.inl"
#include "OOVPADatabase/JVS_OOVPA.inl"
#include "OOVPADatabase/XGraphic_OOVPA.inl"
#include "OOVPADatabase/XNet_OOVPA.inl"
#include "OOVPADatabase/XOnline_OOVPA.inl"
#include "OOVPADatabase/XActEng_OOVPA.inl"

#define PAIRSCANSEC_MAX 4

typedef uint8_t* memptr_t;

typedef bool (*custom_scan_func_t)(uint32_t LibraryFlag,
                                   const xbe_section_header* pSectionHeader,
                                   unsigned short BuildVersion,
                                   const char* LibraryStr,
                                   xb_symbol_register_t register_func,
                                   memptr_t xb_start_virt_addr);

typedef const struct _PairScanLibSec {
    uint32_t library;
    const char *section[PAIRSCANSEC_MAX];
} PairScanLibSec;

typedef const struct _SymbolDatabaseList {

    PairScanLibSec LibSec;

    OOVPATable     *OovpaTable;
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
    // TODO: Need to find out which function is only part of XOnlines.
    { XbSymbolLib_XONLINE,{ Sec_text, Sec_XONLINE, Sec_XNET, Sec_FLASHROM }, XONLINES_OOVPA, XONLINES_OOVPA_COUNT },

    // Fun fact, XONLINES are split into 2 header sections.
    { XbSymbolLib_XONLINES,{ Sec_text, Sec_XONLINE, Sec_XNET, Sec_FLASHROM }, XONLINES_OOVPA, XONLINES_OOVPA_COUNT },

    // Added Sec_text just in case.
    // TODO: Need to find out which function is only part of XNets.
    { XbSymbolLib_XNET,{ Sec_text, Sec_XNET, Sec_FLASHROM }, XNET_OOVPA, XNET_OOVPA_COUNT },

    // XNETS only has XNET, might be true.
    { XbSymbolLib_XNETS,{ Sec_text, Sec_XNET, Sec_FLASHROM }, XNET_OOVPA, XNET_OOVPA_COUNT },

    // test case: Stake
    { XbSymbolLib_XNETN,{ Sec_text, Sec_XNET, Sec_FLASHROM }, XNET_OOVPA, XNET_OOVPA_COUNT },
};

// ******************************************************************
// * SymbolDBListCount
// ******************************************************************
const unsigned int SymbolDBListCount = XBSDB_ARRAY_SIZE(SymbolDBList);

// ******************************************************************
// * XRefDataBase
// ******************************************************************
xbaddr XRefDataBase[XREF_COUNT] = { 0 }; // Reset and populated by EmuHLEIntercept

bool bXRefFirstPass; // For search speed optimization, set in XbSymbolScan, read in XbSymbolLocateFunction
unsigned int UnResolvedXRefs = XREF_COUNT;
bool bStrictBuildVersionLimit = true;
#if _DEBUG
xb_output_message output_verbose_level = XB_OUTPUT_MESSAGE_DEBUG;
#else
xb_output_message output_verbose_level = XB_OUTPUT_MESSAGE_INFO;
#endif
bool bOneTimeScan = true;
bool bScanFirstDetect = false;

// ported from Dxbx's XbeExplorer
static xb_xbe_type GetXbeType(const xbe_header *pXbeHeader)
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

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

uint32_t g_library_flag = 0;
bool XbSymbolRegisterLibrary(uint32_t library_flag) {

    // Check to make sure all flags are acceptable before set.
    if ((library_flag & ~XbSymbolLib_ALL) > 0) {
        return 0;
    }

    g_library_flag = library_flag;
    return 1;
}

xb_output_message_t output_func = NULL;
void XbSymbolSetOutputMessage(xb_output_message_t message_func)
{
    output_func = message_func;
}

bool XbSymbolSetOutputVerbosity(xb_output_message verbose_level)
{
    if (verbose_level < XB_OUTPUT_MESSAGE_MAX) {
        output_verbose_level = verbose_level;
        return true;
    }
    // Return false only when requested level is invalid.
    return false;
}

void XbSymbolBypassBuildVersionLimit(bool bypass_limit)
{
    bStrictBuildVersionLimit = !bypass_limit;
}

void XbSymbolContinuousSigScan(bool enable)
{
    bOneTimeScan = !enable;
}

void XbSymbolFirstDetectAddressOnly(bool enable)
{
    bScanFirstDetect = enable;
}

// Intended for send the message as-is without formating.
// (To avoid corrupted string when perform a bad coding.
//  Plus certain message need special character without format.)
void XbSymbolOutputMessage(xb_output_message mLevel, const char* message)
{
    // Check if output function is set.
    // Plus if pass minimum verbose level to output.
    if (output_func != NULL && mLevel >= output_verbose_level) {
        output_func(mLevel, message);
    }
}

// Intended to format the message with given extra parameters.
void XbSymbolOutputMessageFormat(xb_output_message mLevel, const char* format, ...)
{
    char bufferTemp[2048];

    // Check if output function is set.
    // Plus if pass minimum verbose level to output.
    if (output_func != NULL && mLevel >= output_verbose_level) {
        va_list args;
        va_start(args, format);
        (void)vsprintf(bufferTemp, format, args);
        va_end(args);

        output_func(mLevel, bufferTemp);
    }
}

const char* XbSymbolLibraryToString(uint32_t library_flag)
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
//       Otherwise, internal scan and XbSymbolLibraryToString will not function correctly.
uint32_t XbSymbolLibrayToFlag(const char* library_name)
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

// NOTE: PatrickvL state the arguments are named differently and the function does something that has another meaning,
//       the implementation could be changed if the need ever arises.
static inline void GetXRefEntry(OOVPA *oovpa, int index, uint32_t* xref_out, uint16_t* offset_out) 
{
    *xref_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].xref.index;
    *offset_out = ((LOOVPA*)oovpa)->Lovp[index].offset;
}

static inline void GetOovpaEntry(OOVPA *oovpa, int index, uint32_t* offset_out, uint8_t* value_out)
{
    *offset_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].offset;
    *value_out = (uint8_t)((LOOVPA*)oovpa)->Lovp[index].value;
}

bool CompareOOVPAToAddress(OOVPA *Oovpa, memptr_t cur, uintptr_t xb_start_virt_addr)
{
    uint32_t v = 0; // verification counter

    // Check all XRefs, stop if any does not match
    for (; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint16_t Offset;

        // get currently registered (un)known address
        GetXRefEntry(Oovpa, v, &XRef, &Offset);
        xbaddr XRefAddr = XRefDataBase[XRef];
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

// locate the given function, searching within lower and upper bounds
void* XbSymbolLocateFunction(const char* szFuncName,
                             uint16_t version,
                             OOVPA *Oovpa,
                             memptr_t lower,
                             memptr_t upper,
                             uintptr_t xb_start_virtual_addr)
{

    // skip out if this is an unnecessary search
    if (!bXRefFirstPass && Oovpa->XRefCount == XRefZero && Oovpa->XRefSaveIndex == XRefNoSaveIndex)
        return 0;

    uint32_t derive_indices = 0;
    void* symbol_address = NULL;

    // Check all XRefs are known (if not, don't do a useless scan) :
    for (unsigned int v = 0; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint16_t Offset;

        // get currently registered (un)known address
        GetXRefEntry(Oovpa, v, &XRef, &Offset);
        xbaddr XRefAddr = XRefDataBase[XRef];
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
        upper -= Offset;
    }

    // 
    unsigned int detect_selection = Oovpa->DetectSelect;
    unsigned int counter = 0;

    // search all of the buffer memory range
    for (memptr_t cur = lower; cur < upper; cur++) {
        if (CompareOOVPAToAddress(Oovpa, cur, xb_start_virtual_addr)) {

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
                    XRefDataBase[XRef] = XRefAddr;
                }*/

                // Check if selection is default (zero) then perform the standard procedure.
                if (detect_selection == 0) {
                    if (!bScanFirstDetect || (bScanFirstDetect && symbol_address == NULL)) {
                        XRefDataBase[XRef] = XRefAddr;
                    }
                }
                // Otherwise, perform a detected selection procedure.
                else {
                    // If counter match the target selection, then save the ref address.
                    if (detect_selection == counter) {
                        XRefDataBase[XRef] = XRefAddr;
                    }
                }
            }

            // Check if selection is default (zero) then perform the standard procedure.
            if (detect_selection == 0) {

                if (symbol_address != NULL) {
                    XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_WARN,
                        "Duplicate symbol detection found for %s (%hu), 0x%08x vs 0x%08x",
                        szFuncName, version, symbol_address, cur - xb_start_virtual_addr);
                }

                if (!bScanFirstDetect || (bScanFirstDetect && symbol_address == NULL)) {
                    symbol_address = cur - xb_start_virtual_addr;
                }

                if (bOneTimeScan) {
                    break;
                }
            }
            // Otherwise, perform a detected selection procedure.
            else {
                // If counter match the detected selection, then perform a force break here
                // with address set.
                if (detect_selection == counter) {
                    symbol_address = cur - xb_start_virtual_addr;

                    if (bOneTimeScan) {
                        break;
                    }
                }
                // Otherwise, let's log debug info about what is skipped address detection.
                else {
                    XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_DEBUG,
                        "Skipped symbol detection found for %s (%hu), 0x%08x",
                        szFuncName, version, cur - xb_start_virtual_addr);
                }
            }
        }
    }

    return symbol_address;
}

#define XbSymbolLocateFunctionCast(szFuncName, version, Oovpa, lower, upper, xb_start_virtual_addr) \
        XbSymbolLocateFunction(szFuncName, version, (OOVPA*)Oovpa, lower, upper, (uintptr_t)xb_start_virtual_addr)

static inline void XbSymbolRegisterXRef(const char* LibraryName,
                                        uint32_t LibraryFlag,
                                        uint32_t XRefIndex,
                                        uint16_t version,
                                        const char* symbol_name,
                                        uint32_t symbol_addr,
                                        xb_symbol_register_t register_func)
{
    if (XRefDataBase[XRefIndex] != XREF_ADDR_UNDETERMINED && XRefDataBase[XRefIndex] != XREF_ADDR_DERIVE) {

        if (XRefDataBase[XRefIndex] != symbol_addr) {
            XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_WARN, "Duplicate XREF address found for %s (%hu), %08X vs %08X!",
                symbol_name, version, XRefDataBase[XRefIndex], symbol_addr);
        }

        if (bScanFirstDetect) {
            return;
        }
    }

    XRefDataBase[XRefIndex] = symbol_addr;
    if (register_func != NULL) {
        register_func(LibraryName, LibraryFlag, symbol_name, symbol_addr, version);
    }
}

static inline void XbSymbolRegisterSymbol(const char* LibraryName,
                                          uint32_t LibraryFlag,
                                          uint32_t XRefIndex,
                                          uint16_t version,
                                          const char* symbol_name,
                                          uint32_t symbol_addr,
                                          xb_symbol_register_t register_func)
{
    // do we need to save the found address?
    if (XRefIndex != XRefNoSaveIndex) {
        // If XRef is not found, save it then register once.
        if (XRefDataBase[XRefIndex] == XREF_ADDR_UNDETERMINED) {
            UnResolvedXRefs--;
            XRefDataBase[XRefIndex] = symbol_addr;
            if (register_func != NULL) {
                register_func(LibraryName, LibraryFlag, symbol_name, symbol_addr, version);
            }
        }
    }
    else if (register_func != NULL) {
        register_func(LibraryName, LibraryFlag, symbol_name, symbol_addr, version);
    }
}


void XbSymbolRegisterOOVPA(OOVPATable* OovpaTable,
                            const char* LibraryName,
                            uint32_t    LibraryFlag,
                            xbaddr address,
                            xb_symbol_register_t register_func)
{
    if (OovpaTable != NULL) {

        OOVPA* Oovpa = OovpaTable->Oovpa;

        XbSymbolRegisterSymbol(LibraryName, LibraryFlag, Oovpa->XRefSaveIndex, OovpaTable->Version,
            OovpaTable->szFuncName, address, register_func);
    }
}

void XbSymbolScanOOVPA(OOVPATable *OovpaTable,
                       unsigned int OovpaTableCount,
                       const char* LibraryName,
                       uint32_t    LibraryFlag,
                       xbe_section_header *pSectionHeader,
                       uint16_t buildVersion,
                       xb_symbol_register_t register_func,
                       memptr_t xb_start_virt_addr)
{
    memptr_t lower = xb_start_virt_addr + pSectionHeader->dwVirtualAddr;

    // Find the highest address contained within an executable segment
    memptr_t upper = xb_start_virt_addr + pSectionHeader->dwVirtualAddr + pSectionHeader->dwVirtualSize;

    // traverse the full OOVPA table
    OOVPATable *pLoopEnd = &OovpaTable[OovpaTableCount];
    OOVPATable *pLoop = OovpaTable;
    OOVPATable *pLastKnownSymbol = NULL;
    uint32_t pLastKnownFunc = 0;
    const char *SymbolName = NULL;

    for (; pLoop < pLoopEnd; pLoop++) {

        if (SymbolName == NULL) {
            SymbolName = pLoop->szFuncName;
        } else if (strcmp(SymbolName, pLoop->szFuncName) != 0) {
            SymbolName = pLoop->szFuncName;
            if (pLastKnownSymbol != NULL) {
                // Now that we found the address, store it (regardless if we patch it or not)
                XbSymbolRegisterOOVPA(pLastKnownSymbol, LibraryName, LibraryFlag, pLastKnownFunc, register_func);
                pLastKnownSymbol = NULL;
                pLastKnownFunc = 0;
            }
        }

        // Skip higher build version
        if (bStrictBuildVersionLimit && buildVersion < pLoop->Version)
            continue;

        // Search for each function's location using the OOVPA
        xbaddr pFunc = (xbaddr)(uintptr_t)XbSymbolLocateFunction(pLoop->szFuncName, pLoop->Version, pLoop->Oovpa, lower, upper, (uintptr_t)xb_start_virt_addr);
        if (pFunc == 0) {
            continue;
        }

        if (pFunc == pLastKnownFunc && pLastKnownSymbol == pLoop - 1) {
            //if (g_SymbolAddresses[pLastKnownSymbol->szFuncName] == 0) {
                XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_WARN, "Duplicate OOVPA signature found for %s, %hu vs %hu!", pLastKnownSymbol->szFuncName, pLastKnownSymbol->Version, pLoop->Version);
            //}
        }

        if (buildVersion < pLoop->Version) {
            XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_WARN, "OOVPA signature is too high for [%hu] %s!", pLoop->Version, pLoop->szFuncName);
        }

        pLastKnownFunc = pFunc;
        pLastKnownSymbol = pLoop;
    }

    if (pLastKnownSymbol != NULL) {
        XbSymbolRegisterOOVPA(pLastKnownSymbol, LibraryName, LibraryFlag, pLastKnownFunc, register_func);
    }
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

            const char* LibraryName = XbSymbolLibraryToString(SymbolDBList[d2].LibSec.library);

            //Initialize a matching specific section is currently pair with library in order to scan specific section only.
            //By doing this method will reduce false detection dramatically. If it had happened before.
            for (uint32_t d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                if (SymbolDBList[d2].LibSec.section[d3] != NULL && strcmp(section_name, SymbolDBList[d2].LibSec.section[d3]) == 0) {

                    // traverse the full OOVPA table
                    OOVPATable *pLoopEnd = &SymbolDBList[d2].OovpaTable[SymbolDBList[d2].OovpaTableCount];
                    OOVPATable *pLoop = SymbolDBList[d2].OovpaTable;
                    OOVPATable *pLastKnownSymbol = NULL;
                    uint32_t pLastKnownFunc = 0;
                    const char *SymbolName = NULL;
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

bool XbSymbolInit(const void* xb_header_addr,
                  xb_symbol_register_t register_func,
                  xb_xbe_type* xbe_type,
                  bool* pbDSoundLibHeader)
{
    if (xb_header_addr == NULL || register_func == NULL) {
        return 0;
    }

    const xbe_header* pXbeHeader = xb_header_addr;
    memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    xbe_library_version* pLibraryVersion = (xbe_library_version*)(xb_start_addr + pXbeHeader->pLibraryVersionsAddr);

    //
    // initialize Microsoft XDK scan
    //
    if (pLibraryVersion == NULL) {
        return 0;
    }
    else {

        UnResolvedXRefs = XREF_COUNT;

        bXRefFirstPass = true; // Set to false for search speed optimization

                               // Mark all Xrefs initially as undetermined
        memset((void*)XRefDataBase, XREF_ADDR_UNDETERMINED, sizeof(XRefDataBase));

        // Request a few fundamental XRefs to be derived instead of checked
        XRefDataBase[XREF_D3DDEVICE] = XREF_ADDR_DERIVE;                            //In use
        XRefDataBase[XREF_D3DRS_CULLMODE] = XREF_ADDR_DERIVE;                       //In use
        XRefDataBase[XREF_D3DRS_MULTISAMPLERENDERTARGETMODE] = XREF_ADDR_DERIVE;    //In use
        XRefDataBase[XREF_D3DRS_ROPZCMPALWAYSREAD] = XREF_ADDR_DERIVE;              //In use
        XRefDataBase[XREF_D3DRS_ROPZREAD] = XREF_ADDR_DERIVE;                       //In use
        XRefDataBase[XREF_D3DRS_DONOTCULLUNCOMPRESSED] = XREF_ADDR_DERIVE;          //In use
        XRefDataBase[XREF_D3DRS_STENCILCULLENABLE] = XREF_ADDR_DERIVE;              //In use
        XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] = XREF_ADDR_DERIVE;                 //In use
        XRefDataBase[XREF_G_STREAM] = XREF_ADDR_DERIVE;                             //In use
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_PIXELSHADER] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_TEXTURES] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_PALETTES] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_RENDERTARGET] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_DEPTHSTENCIL] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_EVENTHANDLE] = XREF_ADDR_DERIVE;       //In use
        //XRefDataBase[XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK] = XREF_ADDR_UNDETERMINED;   //In use // Manual check only.
        //XRefDataBase[XREF_OFFSET_D3DDEVICE_M_VBLANKCALLBACK] = XREF_ADDR_UNDETERMINED; //In use // Manual check only.

        xbe_section_header* pSectionHeaders = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
        const char* SectionName;
        *pbDSoundLibHeader = false;

        // Verify if title do contain DirectSound library section.
        for (unsigned int v = 0; v < pXbeHeader->dwSections; v++) {
            SectionName = (const char*)(xb_start_addr + pSectionHeaders[v].SectionNameAddr);

            if (strncmp(SectionName, Lib_DSOUND, 8) == 0) {
                *pbDSoundLibHeader = true;
                break;
            }
        }

        // Detect xbe type
        *xbe_type = GetXbeType(pXbeHeader);
    }
    return 1;
}

void XbSymbolDX8SectionRefs(uint32_t BuildVersion,
                            const char* LibraryStr,
                            uint32_t LibraryFlag,
                            xb_symbol_register_t register_func,
                            memptr_t pFunc,
                            xbaddr DerivedAddr_D3DRS_CULLMODE,
                            uint32_t patchOffset,
                            uint32_t Increment,
                            uint32_t Decrement)
{
    if (pFunc == NULL) {
        return;
    }
    // Temporary verification - is XREF_D3DDEVICE derived correctly?
    xbaddr DerivedAddr_D3DDevice = *(xbaddr*)(pFunc + 0x03);
    if (XRefDataBase[XREF_D3DDEVICE] != DerivedAddr_D3DDevice) {

        if (XRefDataBase[XREF_D3DDEVICE] != XREF_ADDR_DERIVE) {
            XbSymbolOutputMessage(XB_OUTPUT_MESSAGE_INFO, "Second derived XREF_D3DDEVICE differs from first!");
        }

        XRefDataBase[XREF_D3DDEVICE] = DerivedAddr_D3DDevice;
    }
    register_func(LibraryStr, LibraryFlag, "D3DDEVICE", DerivedAddr_D3DDevice, 0);

    // Temporary verification - is XREF_D3D_RenderState_CullMode derived correctly?
    if (XRefDataBase[XREF_D3DRS_CULLMODE] != DerivedAddr_D3DRS_CULLMODE) {

        if (XRefDataBase[XREF_D3DRS_CULLMODE] != XREF_ADDR_DERIVE) {
            XbSymbolOutputMessage(XB_OUTPUT_MESSAGE_WARN, "Second derived XREF_D3D_RenderState_CullMode differs from first!");
        }

        XRefDataBase[XREF_D3DRS_CULLMODE] = DerivedAddr_D3DRS_CULLMODE;
    }
    // Register the offset of D3DRS_CULLMODE, this can be used to programatically locate other render-states in the calling program
    register_func(LibraryStr, LibraryFlag, "D3DRS_CULLMODE", DerivedAddr_D3DRS_CULLMODE, 0);

    // Derive address of EmuD3DDeferredRenderState from D3DRS_CULLMODE
    xbaddr EmuD3DDeferredRenderState = DerivedAddr_D3DRS_CULLMODE - Decrement + Increment;
    patchOffset -= Increment;

    // Derive address of a few other deferred render state slots (to help xref-based function location)
    // XRefDataBase[XREF_D3DRS_PSTEXTUREMODES]          = DerivedAddr_D3DRS_CULLMODE - 11*4;
    // XRefDataBase[XREF_D3DRS_VERTEXBLEND]             = DerivedAddr_D3DRS_CULLMODE - 10*4;
    // XRefDataBase[XREF_D3DRS_FOGCOLOR]             = DerivedAddr_D3DRS_CULLMODE - 9*4;
    XRefDataBase[XREF_D3DRS_FILLMODE] = DerivedAddr_D3DRS_CULLMODE - 8 * 4;
    XRefDataBase[XREF_D3DRS_BACKFILLMODE] = DerivedAddr_D3DRS_CULLMODE - 7 * 4;
    XRefDataBase[XREF_D3DRS_TWOSIDEDLIGHTING] = DerivedAddr_D3DRS_CULLMODE - 6 * 4;
    // XRefDataBase[XREF_D3DRS_NORMALIZENORMALS]        = DerivedAddr_D3DRS_CULLMODE - 5*4;
    // XRefDataBase[XREF_D3DRS_ZENABLE]             = DerivedAddr_D3DRS_CULLMODE - 4*4;
    // XRefDataBase[XREF_D3DRS_STENCILENABLE]           = DerivedAddr_D3DRS_CULLMODE - 3*4;
    // XRefDataBase[XREF_D3DRS_STENCILFAIL]             = DerivedAddr_D3DRS_CULLMODE - 2*4;
    // XRefDataBase[XREF_D3DRS_FRONTFACE]             = DerivedAddr_D3DRS_CULLMODE - 1*4;
    // XRefDataBase[XREF_D3DRS_CULLMODE]          = DerivedAddr_D3DRS_CULLMODE - 0*4;
    // XRefDataBase[XREF_D3DRS_TEXTUREFACTOR]         = DerivedAddr_D3DRS_CULLMODE + 1*4;
    XRefDataBase[XREF_D3DRS_ZBIAS] = DerivedAddr_D3DRS_CULLMODE + 2 * 4;
    XRefDataBase[XREF_D3DRS_LOGICOP] = DerivedAddr_D3DRS_CULLMODE + 3 * 4;
    // XRefDataBase[XREF_D3DRS_EDGEANTIALIAS]         = DerivedAddr_D3DRS_CULLMODE + 4*4;
    XRefDataBase[XREF_D3DRS_MULTISAMPLEANTIALIAS] = DerivedAddr_D3DRS_CULLMODE + 5 * 4;
    XRefDataBase[XREF_D3DRS_MULTISAMPLEMASK] = DerivedAddr_D3DRS_CULLMODE + 6 * 4;
    XRefDataBase[XREF_D3DRS_MULTISAMPLEMODE] = DerivedAddr_D3DRS_CULLMODE + 7 * 4;
    XRefDataBase[XREF_D3DRS_MULTISAMPLERENDERTARGETMODE] = DerivedAddr_D3DRS_CULLMODE + 8 * 4;
    // XRefDataBase[XREF_D3DRS_SHADOWFUNC]            = DerivedAddr_D3DRS_CULLMODE + 9*4;
    // XRefDataBase[XREF_D3DRS_LINEWIDTH]             = DerivedAddr_D3DRS_CULLMODE + 10*4;

    if (BuildVersion >= 4627 && BuildVersion <= 5933) {// Add XDK 4627
        XRefDataBase[XREF_D3DRS_SAMPLEALPHA] = DerivedAddr_D3DRS_CULLMODE + 11 * 4;
    }

    XRefDataBase[XREF_D3DRS_DXT1NOISEENABLE] = EmuD3DDeferredRenderState + patchOffset - 3 * 4;
    XRefDataBase[XREF_D3DRS_YUVENABLE] = EmuD3DDeferredRenderState + patchOffset - 2 * 4;
    XRefDataBase[XREF_D3DRS_OCCLUSIONCULLENABLE] = EmuD3DDeferredRenderState + patchOffset - 1 * 4;
    XRefDataBase[XREF_D3DRS_STENCILCULLENABLE] = EmuD3DDeferredRenderState + patchOffset + 0 * 4;
    XRefDataBase[XREF_D3DRS_ROPZCMPALWAYSREAD] = EmuD3DDeferredRenderState + patchOffset + 1 * 4;
    XRefDataBase[XREF_D3DRS_ROPZREAD] = EmuD3DDeferredRenderState + patchOffset + 2 * 4;
    XRefDataBase[XREF_D3DRS_DONOTCULLUNCOMPRESSED] = EmuD3DDeferredRenderState + patchOffset + 3 * 4;

    register_func(LibraryStr, LibraryFlag, "D3DDeferredRenderState", EmuD3DDeferredRenderState, 0);
}

void XbSymbolDX8RegisterD3DTSS(uint32_t LibraryFlag,
                               const char* LibraryStr,
                               xb_symbol_register_t register_func,
                               memptr_t pFunc,
                               uint32_t pXRefOffset)
{
    if (pFunc == NULL) {
        return;
    }
    xbaddr DerivedAddr_D3DTSS_TEXCOORDINDEX = 0;
    int Decrement = 0x70; // TODO : Rename into something understandable

    // TODO : Remove this when XREF_D3D_TextureState_TexCoordIndex derivation is deemed stable
    {
        DerivedAddr_D3DTSS_TEXCOORDINDEX = *(xbaddr*)(pFunc + pXRefOffset);

        // Temporary verification - is XREF_D3DTSS_TEXCOORDINDEX derived correctly?
        if (XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] != DerivedAddr_D3DTSS_TEXCOORDINDEX) {

            if (XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] != XREF_ADDR_DERIVE) {
                XbSymbolOutputMessage(XB_OUTPUT_MESSAGE_WARN, "Second derived XREF_D3DTSS_TEXCOORDINDEX differs from first!");
            }

            //XRefDataBase[XREF_D3DTSS_BUMPENV] = DerivedAddr_D3DTSS_TEXCOORDINDEX - 28*4;
            XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] = DerivedAddr_D3DTSS_TEXCOORDINDEX;
            //XRefDataBase[XREF_D3DTSS_BORDERCOLOR] = DerivedAddr_D3DTSS_TEXCOORDINDEX + 1*4;
            //XRefDataBase[XREF_D3DTSS_COLORKEYCOLOR] = DerivedAddr_D3DTSS_TEXCOORDINDEX + 2*4;
        }
    }

    uint32_t EmuD3DDeferredTextureState = DerivedAddr_D3DTSS_TEXCOORDINDEX - Decrement;

    register_func(LibraryStr, LibraryFlag, "D3DDeferredTextureState", EmuD3DDeferredTextureState, 0);
}


void XbSymbolDX8RegisterStream(uint32_t LibraryFlag,
                               const char* LibraryStr,
                               xb_symbol_register_t register_func,
                               memptr_t pFunc,
                               uint32_t iCodeOffsetFor_g_Stream)
{
    if (pFunc == NULL) {
        return;
    }
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
    register_func(LibraryStr, LibraryFlag, "g_Stream", Derived_g_Stream, 0);
}

bool XbSymbolDX8SectionScan(uint32_t LibraryFlag,
                            const xbe_section_header* pSectionHeader,
                            unsigned short BuildVersion,
                            const char* LibraryStr,
                            xb_symbol_register_t register_func,
                            memptr_t xb_start_virt_addr)
{
    // Generic usage
    memptr_t lower = xb_start_virt_addr + pSectionHeader->dwVirtualAddr;
    memptr_t upper = xb_start_virt_addr + pSectionHeader->dwVirtualAddr + pSectionHeader->dwVirtualSize;;
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

    // TODO: Why do we need this? Also, can we just scan library versions for this only?
    // Save D3D8 build version
    //g_BuildVersion = BuildVersion;

    if (LibraryFlag == XbSymbolLib_D3D8) {

        // locate D3DDevice_SetRenderState_CullMode first
        if (BuildVersion < 3911) {
            // Not supported, currently ignored.
        }
        else if (BuildVersion < 4034) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetRenderState_CullMode", 3911,
                &D3DDevice_SetRenderState_CullMode_3911, lower, upper, xb_start_virt_addr);
        }
        else {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetRenderState_CullMode", 4034,
                &D3DDevice_SetRenderState_CullMode_4034, lower, upper, xb_start_virt_addr);
        }

        // then locate D3DDeferredRenderState
        if (pFunc != 0) {
            // NOTE: Is a requirement to align properly.
            pFunc += (uintptr_t)xb_start_virt_addr;

            // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
            // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
            if (BuildVersion < 3911) {
                // Not supported, currently ignored.
            }
            else if (BuildVersion < 4034) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x25);
                Decrement = 0x1FC;  // TODO: Clean up (?)
                Increment = 82 * 4;
                patchOffset = 140 * 4; // Verified 3925 and 3948

                //Decrement = 0x19F;  // TODO: Clean up (?)
                //Increment = 72 * 4;
                //patchOffset = 142*4; // TODO: Verify
            }
            else if (BuildVersion <= 4361) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x200;
                Increment = 82 * 4;
                patchOffset = 142 * 4;
            }
            else if (BuildVersion < 4627) {
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
        pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetRenderState_CullMode", 1045,
            &D3DDevice_SetRenderState_CullMode_1045, lower, upper, xb_start_virt_addr);
        pXRefOffset = 0x2D; // verified for 3925
        if (pFunc == 0) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetRenderState_CullMode", 1049,
                &D3DDevice_SetRenderState_CullMode_1049, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x31; // verified for 4039
        }

        if (pFunc == 0) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetRenderState_CullMode", 1052,
                &D3DDevice_SetRenderState_CullMode_1052, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x34;
        }

        if (pFunc == 0) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetRenderState_CullMode", 1053,
                &D3DDevice_SetRenderState_CullMode_1053, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x35;
        }

        // then locate D3DDeferredRenderState
        if (pFunc != 0) {
            // NOTE: Is a requirement to align properly.
            pFunc += (uintptr_t)xb_start_virt_addr;

            // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
            // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
            if (BuildVersion < 3911) {
                // Not supported, currently ignored.
            }
            else if (BuildVersion < 4034) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x1FC;  // TODO: Clean up (?)
                Increment = 82 * 4;
                patchOffset = 140 * 4; // Verified 3925 and 3948

                //Decrement = 0x19F;  // TODO: Clean up (?)
                //Increment = 72 * 4;
                //patchOffset = 142*4; // TODO: Verify
            }
            else if (BuildVersion <= 4361) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x200;
                Increment = 82 * 4;
                patchOffset = 142 * 4;
            }
            else if (BuildVersion < 4627) {
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
    XbSymbolDX8SectionRefs(BuildVersion, LibraryStr, LibraryFlag, register_func, pFunc, DerivedAddr_D3DRS_CULLMODE, patchOffset, Increment, Decrement);

    // then locate D3DDeferredTextureState
    if (LibraryFlag == XbSymbolLib_D3D8) {

        if (BuildVersion < 3911) {
            // Not supported, currently ignored.
            pFunc = 0;
        }
        else if (BuildVersion < 4034) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex", 3911,
                &D3DDevice_SetTextureState_TexCoordIndex_3911, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x11;
        }
        else if (BuildVersion < 4242) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex", 4034,
                &D3DDevice_SetTextureState_TexCoordIndex_4034, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x18;
        }
        else if (BuildVersion < 4627) {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex", 4242,
                &D3DDevice_SetTextureState_TexCoordIndex_4242, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x19;
        }
        else {
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex", 4627,
                &D3DDevice_SetTextureState_TexCoordIndex_4627, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x19;
        }
    }
    else { // D3D8LTCG
        // verified for 3925
        pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex_0", 2039,
            &D3DDevice_SetTextureState_TexCoordIndex_0_2039, lower, upper, xb_start_virt_addr);
        pXRefOffset = 0x08;

        if (pFunc == 0) { // verified for 4039
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex_4", 2040,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2040, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4432
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex", 1944,
                &D3DDevice_SetTextureState_TexCoordIndex_1944, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x19;
        }

        if (pFunc == 0) { // verified for 4531
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex_4", 2045,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2045, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4627 and higher
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex_4", 2058,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2058, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4627 and higher
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex", 1958,
                &D3DDevice_SetTextureState_TexCoordIndex_1958, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x19;
        }

        if (pFunc == 0) { // verified for World Series Baseball 2K3
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex_4", 2052,
                &D3DDevice_SetTextureState_TexCoordIndex_4_2052, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x15;
        }

        if (pFunc == 0) { // verified for Ski Racing 2006
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetTextureState_TexCoordIndex_0", 2058,
                &D3DDevice_SetTextureState_TexCoordIndex_0_2058, lower, upper, xb_start_virt_addr);
            pXRefOffset = 0x15;
        }
    }

    if (pFunc != 0) {
        // NOTE: Is a requirement to align properly.
        pFunc += (uintptr_t)xb_start_virt_addr;
        XbSymbolDX8RegisterD3DTSS(LibraryFlag, LibraryStr, register_func, pFunc, pXRefOffset);
    }

    // Locate Xbox symbol "g_Stream" and store it's address
    pFunc = 0;
    // verified for D3D8 with 4361, 4627, 5344, 5558, 5659, 5788, 5849, 5933
    // and verified for LTCG with 4432, 4627, 5344, 5558, 5849
    iCodeOffsetFor_g_Stream = 0x22;

    if (LibraryFlag == XbSymbolLib_D3D8) {
        if (BuildVersion >= 4034) {
            OOVPA_version = 4034;
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetStreamSource", 4034,
                &D3DDevice_SetStreamSource_4034, lower, upper, xb_start_virt_addr);
        }
        else {
            OOVPA_version = 3911;
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetStreamSource", 3911,
                &D3DDevice_SetStreamSource_3911, lower, upper, xb_start_virt_addr);
            iCodeOffsetFor_g_Stream = 0x23; // verified for 3911
        }
    }
    else { // D3D8LTCG
        if (BuildVersion > 4039) {
            OOVPA_version = 4034; // TODO Verify
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetStreamSource", 1044,
                &D3DDevice_SetStreamSource_1044, lower, upper, xb_start_virt_addr);
        }

        if (pFunc == 0) { // LTCG specific
            OOVPA_version = 4034; // TODO Verify
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetStreamSource_4", 2058,
                &D3DDevice_SetStreamSource_4_2058, lower, upper, xb_start_virt_addr);
            iCodeOffsetFor_g_Stream = 0x1E;
        }

        if (pFunc == 0) { // verified for 4039
            OOVPA_version = 4034;
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetStreamSource_8", 2040,
                &D3DDevice_SetStreamSource_8_2040, lower, upper, xb_start_virt_addr);
            iCodeOffsetFor_g_Stream = 0x23;
        }

        if (pFunc == 0) { // verified for 3925
            OOVPA_version = 3911;
            pFunc = XbSymbolLocateFunctionCast("D3DDevice_SetStreamSource", 1039,
                &D3DDevice_SetStreamSource_1039, lower, upper, xb_start_virt_addr);
            iCodeOffsetFor_g_Stream = 0x47;
        }
    }

    if (pFunc != 0) {
        // NOTE: Is a requirement to align properly.
        pFunc += (uintptr_t)xb_start_virt_addr;

        XbSymbolDX8RegisterStream(LibraryFlag, LibraryStr, register_func, pFunc, iCodeOffsetFor_g_Stream);
    }

    // Manual check require for able to self-register these symbols:
    // * D3DDevice_SetSwapCallback
    // * D3DDevice_SetVerticalBlankCallback

    // First, check if D3D__PDEVICE is found.
    if (XRefDataBase[XREF_D3DDEVICE] != XREF_ADDR_DERIVE &&
        // Then, check at least one of symbol's member variable is not found.
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK] == XREF_ADDR_UNDETERMINED) {

        // Scan if event handle variable is not yet derived.
        if (XRefDataBase[XREF_OFFSET_D3DDEVICE_M_EVENTHANDLE] == XREF_ADDR_DERIVE) {
            xSymbolAddr = (xbaddr)(uintptr_t)XbSymbolLocateFunctionCast("D3DDevice__ManualFindEventHandleGeneric_3911", 3911,
                &D3DDevice__ManualFindEventHandleGeneric_3911, lower, upper, xb_start_virt_addr);
        }

        // We are not registering the D3DDevice__ManualFindEventHandleGeneric as it is NOT a symbol.


        // If not found, skip manual register.
        if (XRefDataBase[XREF_OFFSET_D3DDEVICE_M_EVENTHANDLE] == XREF_ADDR_DERIVE) {
            return false;
        }

        // Finally, manual register the symbol variables.
        xSymbolAddr = XRefDataBase[XREF_OFFSET_D3DDEVICE_M_EVENTHANDLE];
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK] = xSymbolAddr - 8;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_VBLANKCALLBACK] = xSymbolAddr - 4;
    }
    // If D3D__PDEVICE is not found, the scan is not complete
    // and will continue scan to next given section.
    else {
        return false;
    }

    return true;
}

bool XbSymbolDSoundSectionScan(uint32_t LibraryFlag,
                               const xbe_section_header* pSectionHeader,
                               unsigned short BuildVersion,
                               const char* LibraryStr,
                               xb_symbol_register_t register_func,
                               memptr_t xb_start_virt_addr)
{
    // Generic usage
    xbaddr xblower = pSectionHeader->dwVirtualAddr;
    xbaddr xbupper = pSectionHeader->dwVirtualAddr + pSectionHeader->dwVirtualSize;
    xbaddr xFuncAddr = 0;
    memptr_t lower = xb_start_virt_addr + pSectionHeader->dwVirtualAddr;
    memptr_t upper = xb_start_virt_addr + pSectionHeader->dwVirtualAddr + pSectionHeader->dwVirtualSize;
    memptr_t pFuncAddr = 0;

    /*
    bool testRun = 1;
    while (testRun) {
    }//*/

    // Scan for DirectSoundStream's contructor function.
    if (XRefDataBase[XREF_CDirectSoundStream_Constructor] == XREF_ADDR_UNDETERMINED) {
        xFuncAddr = (xbaddr)(uintptr_t)XbSymbolLocateFunctionCast("CDirectSoundStream_Constructor", 3911,
            &CDirectSoundStream_Constructor_3911, lower, upper, xb_start_virt_addr);

        // If not found, skip the rest of the scan.
        if (xFuncAddr == 0) {
            return false;
        }

        XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XREF_CDirectSoundStream_Constructor, 3911,
            "CDirectSoundStream_Constructor", xFuncAddr, register_func);

        // TODO: If possible, integrate into the OOVPA structure.
        XbSymbolRegisterXRef(LibraryStr, LibraryFlag, XREF_DSS_VOICE_VTABLE, 3911,
            NULL, *(xbaddr*)(xb_start_virt_addr + xFuncAddr + 0x14), NULL);
        XbSymbolRegisterXRef(LibraryStr, LibraryFlag, XREF_DSS_STREAM_VTABLE, 3911,
            NULL, *(xbaddr*)(xb_start_virt_addr + xFuncAddr + 0x1B), NULL);
    }

    // Verify both variables are already set from the scan function above.
    if (XRefDataBase[XREF_DSS_STREAM_VTABLE] == XREF_ADDR_DERIVE ||
        XRefDataBase[XREF_DSS_VOICE_VTABLE] == XREF_ADDR_DERIVE) {

        XbSymbolOutputMessage(XB_OUTPUT_MESSAGE_ERROR, "Something went wrong with finding DSS' vtables...");
        return false;
    }

    // Finally, manually add CDirectSoundStream's AddRef and Release functions.
    if (XRefDataBase[XREF_CDirectSoundStream_AddRef] == XREF_ADDR_UNDETERMINED) {
        xbaddr vtable = XRefDataBase[XREF_DSS_STREAM_VTABLE];

        if (xblower <= vtable && vtable < xbupper) {
            pFuncAddr = xb_start_virt_addr + vtable;

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XREF_CDirectSoundStream_AddRef, 3911,
                "CDirectSoundStream_AddRef", *(uint32_t*)(pFuncAddr + 0 * 4), register_func);

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XREF_CDirectSoundStream_Release, 3911,
                "CDirectSoundStream_Release", *(uint32_t*)(pFuncAddr + 1 * 4), register_func);

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_GetInfo", *(uint32_t*)(pFuncAddr + 2 * 4), register_func);

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_GetStatus", *(uint32_t*)(pFuncAddr + 3 * 4), register_func);

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_Process", *(uint32_t*)(pFuncAddr + 4 * 4), register_func);

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_Discontinuity", *(uint32_t*)(pFuncAddr + 5 * 4), register_func);

            XbSymbolRegisterSymbol(LibraryStr, LibraryFlag, XRefNoSaveIndex, 3911,
                "CDirectSoundStream_Flush", *(uint32_t*)(pFuncAddr + 6 * 4), register_func);

            // NOTE: it is possible to manual add GetInfo, GetStatus, Process, Discontinuity,
            // and Flush functions.
        }
        else {
            return false;
        }

    }

    return true;
}

bool XbLibraryScan(custom_scan_func_t custom_scan_func,
                   const void* xb_header_addr,
                   xb_symbol_register_t register_func,
                   bool is_raw,
                   uint16_t BuildVersion,
                   uint32_t LibraryFlag,
                   const char* LibraryStr)
{
    const char* SectionName;
    bool scan_ret = false;

    const xbe_header* pXbeHeader = xb_header_addr;
    memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    memptr_t xb_start_virt_addr = xb_start_addr;

    xbe_section_header* pSectionHeaders = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    xbe_section_header* pSectionScan;

    for (unsigned int d2 = 0; d2 < SymbolDBListCount; d2++) {

        if ((LibraryFlag & SymbolDBList[d2].LibSec.library) > 0) {
            for (unsigned int s = 0; s < pXbeHeader->dwSections; s++) {
                SectionName = (const char*)(xb_start_addr + pSectionHeaders[s].SectionNameAddr);

                if (!is_raw) {
                    // if an emulator did not load a section, then skip the section scan.
                    if (pSectionHeaders[s].dwSectionRefCount == 0) {
                        continue;
                    }
                }
                else {
                    xb_start_virt_addr = (((memptr_t)xb_header_addr + pSectionHeaders[s].dwRawAddr) - pSectionHeaders[s].dwVirtualAddr);
                }

                //Initialize a matching specific section is currently pair with library in order to scan specific section only.
                //By doing this method will reduce false detection dramatically. If it had happened before.
                for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                    if (SymbolDBList[d2].LibSec.section[d3] != NULL && strncmp(SectionName, SymbolDBList[d2].LibSec.section[d3], 8) == 0) {
                        pSectionScan = pSectionHeaders + s;

                        XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section", LibraryStr, SectionName);

                        scan_ret = custom_scan_func(LibraryFlag, pSectionScan, BuildVersion, LibraryStr, register_func, xb_start_virt_addr);

                        if (scan_ret) {
                            // let's return true here instead of waste the loops for nothing.
                            return scan_ret;
                        }
                    }
                }
            }
            // Use the break if there are 2+ bit flags set such as include LTCG flag in std flag's oovpa database like D3D8.
            if ((SymbolDBList[d2].LibSec.library & ~LibraryFlag) == 0) {
                break;
            }
        }
    }
    return scan_ret;
}

bool XbSymbolScan(const void* xb_header_addr,
                  xb_symbol_register_t register_func,
                  bool is_raw)
{

    bool bDSoundLibHeader;
    xb_xbe_type xbe_type;
    bool bCheckJVS = false;

    if (!XbSymbolInit(xb_header_addr, register_func, &xbe_type, &bDSoundLibHeader)) {
        return 0;
    }

    XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_DEBUG, "xbe type is %s", xbe_type_str[xbe_type]);

    const xbe_header* pXbeHeader = xb_header_addr;
    memptr_t xb_start_addr = (memptr_t)xb_header_addr - pXbeHeader->dwBaseAddr;
    memptr_t xb_start_virt_addr = xb_start_addr;
    xbe_library_version* pLibraryVersion = (xbe_library_version*)(xb_start_addr + pXbeHeader->pLibraryVersionsAddr);

    uint32_t dwLibraryVersions = pXbeHeader->dwLibraryVersions;
    unsigned int LastUnResolvedXRefs = UnResolvedXRefs + 1;
    unsigned int OrigUnResolvedXRefs = UnResolvedXRefs;
    xbe_section_header* pSectionHeaders = (xbe_section_header*)(xb_start_addr + pXbeHeader->pSectionHeadersAddr);
    xbe_section_header* pSectionScan;
    const char* SectionName;

    for (unsigned int p = 0; UnResolvedXRefs < LastUnResolvedXRefs; p++) {

        LastUnResolvedXRefs = UnResolvedXRefs;

        bool bDSoundLibSection = false;
        uint16_t preserveVersion = 0;

        for (unsigned int lv = 0; lv < dwLibraryVersions; lv++) {
            uint16_t BuildVersion = pLibraryVersion[lv].wBuildVersion;
            uint16_t QFEVersion = pLibraryVersion[lv].wFlags.QFEVersion;

            if (preserveVersion < BuildVersion) {
                preserveVersion = BuildVersion;
            }

            const char* LibraryStr = pLibraryVersion[lv].szName;
            uint32_t LibraryFlag = XbSymbolLibrayToFlag(LibraryStr);

            do {

                // Temporary placeholder until v2.0 API's section scan function is ready or may be permanent in here.
                // Skip specific library if third-party set to specific library.
                if (!(g_library_flag == 0 || (g_library_flag & LibraryFlag) > 0)) {
                    XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_DEBUG, "Skipping %.8s (%hu) scan.", LibraryStr, BuildVersion);
                }
                else {

                    pSectionScan = NULL;

                    if ((LibraryFlag & (XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG)) > 0) {

                        // Functions in this library were updated by June 2003 XDK (5558) with Integrated Hotfixes,
                        // However August 2003 XDK (5659) still uses the old function.
                        // Please use updated 5788 instead.
                        if (BuildVersion >= 5558 && BuildVersion <= 5659 && QFEVersion > 1) {
                            XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_WARN, "D3D8 version 1.0.%d.%d Title Detected: This game uses an alias version 1.0.5788", BuildVersion, QFEVersion);
                            BuildVersion = 5788;
                        }
                    }

                    if (LibraryFlag == XbSymbolLib_DSOUND) {
                        bDSoundLibSection = true;
                    }

                    if (bXRefFirstPass) {
                        if ((LibraryFlag & (XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG)) > 0) {
                            // TODO: Do we need to check twice?
                            // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                            // By doing this method will reduce false detection dramatically. If it had happened before.
                            XbLibraryScan(XbSymbolDX8SectionScan, xb_header_addr, register_func, is_raw, BuildVersion, LibraryFlag, LibraryStr);
                        }
                        else if ((LibraryFlag & XbSymbolLib_DSOUND) > 0) {
                            // Perform check twice, since sections can be in different order.
                            for (unsigned int loop = 0; loop < 2; loop++) {
                                // Initialize a matching specific section is currently pair with library in order to scan specific section only.
                                // By doing this method will reduce false detection dramatically. If it had happened before.
                                if (!XbLibraryScan(XbSymbolDSoundSectionScan, xb_header_addr, register_func, is_raw, BuildVersion, LibraryFlag, LibraryStr)) {
                                    continue;
                                }
                                break;
                            }
                        }
                    }

                    //Initialize library scan against symbol database we want to search for address of patches and xreferences.
                    for (unsigned int d2 = 0; d2 < SymbolDBListCount; d2++) {

                        if ((LibraryFlag & SymbolDBList[d2].LibSec.library) > 0) {
                            for (unsigned int s = 0; s < pXbeHeader->dwSections; s++) {
                                SectionName = (const char*)(xb_start_addr + pSectionHeaders[s].SectionNameAddr);

                                if (!is_raw) {
                                    // if an emulator did not load a section, then skip the section scan.
                                    if (pSectionHeaders[s].dwSectionRefCount == 0) {
                                        continue;
                                    }
                                }
                                else {
                                    xb_start_virt_addr = (((memptr_t)xb_header_addr + pSectionHeaders[s].dwRawAddr) - pSectionHeaders[s].dwVirtualAddr);
                                }

                                //Initialize a matching specific section is currently pair with library in order to scan specific section only.
                                //By doing this method will reduce false detection dramatically. If it had happened before.
                                for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                                    if (SymbolDBList[d2].LibSec.section[d3] != NULL && strncmp(SectionName, SymbolDBList[d2].LibSec.section[d3], 8) == 0) {
                                        pSectionScan = pSectionHeaders + s;

                                        XbSymbolOutputMessageFormat(XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section", LibraryStr, SectionName);

                                        XbSymbolScanOOVPA(SymbolDBList[d2].OovpaTable, SymbolDBList[d2].OovpaTableCount, LibraryStr, LibraryFlag,
                                            pSectionScan, BuildVersion, register_func, xb_start_virt_addr);
                                        break;
                                    }
                                }
                            }
                            // Use the break if there are 2+ bit flags set such as include LTCG flag in std flag's oovpa database like D3D8.
                            if ((SymbolDBList[d2].LibSec.library & ~LibraryFlag) == 0) {
                                break;
                            }
                        }
                    }
                }

                // Perform extra check in case of xbe's library headers fail to provide details.
                if (lv == dwLibraryVersions - 1) {

                    // Verify if DSOUND library exist or not.
                    if (bDSoundLibSection == false && bDSoundLibHeader == true) {
                        LibraryStr = Lib_DSOUND;
                        LibraryFlag = XbSymbolLib_DSOUND;
                        BuildVersion = preserveVersion;
                        bDSoundLibSection = true; // In case if third-party application exclude scan for DSOUND library.
                        continue;
                    }

                    // Verify if xbe type is not a retail for Chihiro applications.
                    // NOTE: segaboots does report as Chihiro except others report as debug.
                    if (xbe_type != XB_XBE_TYPE_RETAIL && bCheckJVS == false) {
                        LibraryStr = Lib_JVS;
                        LibraryFlag = XbSymbolLib_JVS;
                        BuildVersion = preserveVersion;
                        bCheckJVS = true;
                        continue;
                    }
                }

                break;
            } while (true);
        }

        bXRefFirstPass = false;
    }
    return 1;
}

// ******************************************************************
// * XbSymbolLibraryVersion
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

unsigned int XbSymbolLibraryVersion()
{
    // Calculate this just once
    static unsigned int CalculatedHash = 0;
    if (CalculatedHash == 0) {
        CalculatedHash = HashSymbolDataArray(SymbolDBList, SymbolDBListCount);
    }
    return CalculatedHash;
}


// ******************************************************************
// * XbSymbolDataBaseTestOOVPAs
// ******************************************************************

typedef struct _SymbolDatabaseVerifyContext {
    SymbolDatabaseList *main_data;
    OOVPA *oovpa, *against;
    SymbolDatabaseList *against_data;
    uint32_t main_index, against_index;
} SymbolDatabaseVerifyContext;

int OOVPAErrorString(char *bufferTemp, SymbolDatabaseList *data, uint32_t index)
{
    return sprintf(bufferTemp, "OOVPATable %2u %4hu [%4u] %s", data->LibSec.library, data->OovpaTable[index].Version, index, data->OovpaTable[index].szFuncName);
}

void OOVPAError(SymbolDatabaseVerifyContext *context, char *format, ...)
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

    XbSymbolOutputMessage(XB_OUTPUT_MESSAGE_ERROR, buffer);
}

unsigned int XbSymbolDataBaseVerifyDataBaseList(SymbolDatabaseVerifyContext *context); // forward

unsigned int XbSymbolDataBaseVerifyOOVPA(SymbolDatabaseVerifyContext *context, OOVPA *oovpa)
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
                OOVPAError(context, "Lovp[%2u] : Offset (0x%03x) must be larger then previous offset (0x%03x)",
                         p, curr_offset, prev_offset);
            }
        }

        // find duplicate OOVPA's across all other data-table-oovpa's
        context->oovpa = oovpa;
        context->against = oovpa;
        error_count += XbSymbolDataBaseVerifyDataBaseList(context);
        context->against = NULL; // reset scanning state
        return error_count;
    }

    // prevent checking an oovpa against itself
    if (context->against == oovpa) {
        return error_count;
    }

    // compare {Offset, Value}-pairs between two OOVPA's
    OOVPA *left = context->against, *right = oovpa;
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
                    OOVPAError(context, "OOVPA's are identical",
                               unique_offset_left,
                               unique_offset_right);
                }
            } else {
                // not too many new OV-pairs on the left side?
                if (unique_offset_left < 6) {
                    // not too many new OV-pairs on the right side?
                    if (unique_offset_right < 6) {
                        error_count++;
                        OOVPAError(context, "OOVPA's are expanded (left +%d, right +%d)",
                                   unique_offset_left,
                                   unique_offset_right);
                    }
                }
            }
        }
    }
    return error_count;
}

unsigned int XbSymbolDataBaseVerifyEntry(SymbolDatabaseVerifyContext *context, const OOVPATable *table, uint32_t index)
{
    if (context->against == NULL) {
        context->main_index = index;
    } else {
        context->against_index = index;
    }

    // verify the OOVPA of this entry
    if (table[index].Oovpa != NULL) {
        return XbSymbolDataBaseVerifyOOVPA(context, table[index].Oovpa);
    }
    return 0;
}

unsigned int XbSymbolDataBaseVerifyDatabase(SymbolDatabaseVerifyContext *context, SymbolDatabaseList *data)
{
    unsigned int error_count = 0;
    if (context->against == NULL) {
        context->main_data = data;
    } else {
        context->against_data = data;
    }

    // Don't check a database against itself :
    if (context->main_data == context->against_data) {
        return error_count;
    }

    // verify each entry in this SymbolDatabaseList
    for (uint32_t e = 0; e < data->OovpaTableCount; e++) {
        error_count += XbSymbolDataBaseVerifyEntry(context, data->OovpaTable, e);
    }
    return error_count;
}

unsigned int XbSymbolDataBaseVerifyDataBaseList(SymbolDatabaseVerifyContext *context)
{
    unsigned int error_count = 0;
    // verify all SymbolDatabaseList's
    for (uint32_t d = 0; d < SymbolDBListCount; d++) {
        error_count += XbSymbolDataBaseVerifyDatabase(context, &SymbolDBList[d]);
    }
    return error_count;
}

unsigned int XbSymbolDataBaseTestOOVPAs()
{
    SymbolDatabaseVerifyContext context = { 0 };
    return XbSymbolDataBaseVerifyDataBaseList(&context);
}

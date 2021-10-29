// ******************************************************************
// *
// *   XbSymbolDatabase.h
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
// *  (c) 2016-2017 PatrickvL
// *  (c) 2017-2018 Luke Usher
// *  (c) 2018-2019 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#pragma once

#include <stdlib.h> // for size_t
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************************************
// * Library strings
// ******************************************************************
// clang-format off
#define Lib_UNKNOWN  "UNKNOWN"
// clang-format on
// Group of sections since most libraries are compiled inside the
// section(s) below.
#define Sec_text     ".text"
#define Sec_FLASHROM "FLASHROM"
// DSOUND has a vtable store in .rdata section.
// clang-format off
#define Sec_rdata    ".rdata"
// clang-format on
// Individual library (yet do include group sections above)
#define Lib_D3D8     "D3D8"
#define Sec_D3D      "D3D"
#define Lib_D3D8LTCG "D3D8LTCG"
#define Lib_D3DX8    "D3DX8"
#define Sec_D3DX     "D3DX"
#define Lib_DSOUND   "DSOUND"
#define Sec_DSOUND   Lib_DSOUND
#define Lib_JVS      "JVS"
#define Lib_XACTENG  "XACTENG"
#define Sec_XACTENG  Lib_XACTENG
#define Lib_XAPILIB  "XAPILIB"
#define Sec_XPP      "XPP"
#define Lib_XGRAPHC  "XGRAPHC"
#define Sec_XGRPH    "XGRPH"
#define Lib_XNET     "XNET"
#define Lib_XNETN    "XNETN"
#define Lib_XNETS    "XNETS"
#define Lib_XONLINE  "XONLINE"
#define Sec_XONLINE  Lib_XONLINE
#define Lib_XONLINES "XONLINES"
#define Sec_XNET     "XNET"

#define XbSymbolLib_D3D8     (1 << 0)
#define XbSymbolLib_D3D8LTCG (1 << 1)
#define XbSymbolLib_D3DX8    (1 << 2)
#define XbSymbolLib_DSOUND   (1 << 3)
#define XbSymbolLib_JVS      (1 << 4)
#define XbSymbolLib_XACTENG  (1 << 5)
#define XbSymbolLib_XAPILIB  (1 << 6)
#define XbSymbolLib_XGRAPHC  (1 << 7)
#define XbSymbolLib_XNET     (1 << 8)
#define XbSymbolLib_XNETN    (1 << 9)
#define XbSymbolLib_XNETS    (1 << 10)
#define XbSymbolLib_XONLINE  (1 << 11)
#define XbSymbolLib_XONLINES (1 << 12)

// clang-format off
// TODO: Need to find a way keep below intact.
#define XbSymbolLib_ALL ( XbSymbolLib_D3D8 | XbSymbolLib_D3D8LTCG | XbSymbolLib_D3DX8 | XbSymbolLib_DSOUND \
                        | XbSymbolLib_JVS | XbSymbolLib_XACTENG | XbSymbolLib_XAPILIB | XbSymbolLib_XGRAPHC \
                        | XbSymbolLib_XNET | XbSymbolLib_XNETN | XbSymbolLib_XNETS | XbSymbolLib_XONLINE \
                        | XbSymbolLib_XONLINES)
// clang-format on

typedef enum _xb_output_message {
    XB_OUTPUT_MESSAGE_DEBUG = 0,
    XB_OUTPUT_MESSAGE_INFO,
    XB_OUTPUT_MESSAGE_WARN,
    XB_OUTPUT_MESSAGE_ERROR,
    // Only for internal usage.
    XB_OUTPUT_MESSAGE_MAX
} xb_output_message;

typedef enum _xb_xbe_type {
    XB_XBE_TYPE_RETAIL = 0,
    XB_XBE_TYPE_DEBUG,
    XB_XBE_TYPE_CHIHIRO,
    // Only for internal usage.
    XB_XBE_TYPE_MAX
} xb_xbe_type;

static const uint32_t XB_XOR_KT[] = {
    0x5B6D40B6, // Kernel Thunk (Retail)
    0xEFB1F152, // Kernel Thunk (Debug)
    0x2290059D  // Kernel Thunk (Chihiro)
};

static const char* xbe_type_str[XB_XBE_TYPE_MAX] = {
    "RETAIL",
    "DEBUG",
    "CHIHIRO"
};

#ifndef xbaddr
typedef uint32_t xbaddr;
#endif

typedef struct _XbSDBLibrary {
    uint16_t build_version;
    uint16_t qfe_version;
    uint32_t flag;
    char name[8];
} XbSDBLibrary;

typedef struct _XbSDBLibraryHeader {
    unsigned int count;
    XbSDBLibrary* filters;
} XbSDBLibraryHeader;

typedef struct _XbSDBSection {
    // These three variables must be fixed info.
    char name[8];
    uint32_t xb_virt_addr;
    uint32_t buffer_size;
    void* buffer_lower;
} XbSDBSection;

typedef struct _XbSDBSectionHeader {
    unsigned int count;
    XbSDBSection* filters;
} XbSDBSectionHeader;

typedef void* XbSymbolContextHandle;

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

/// <summary>
/// Return value is only useful to prevent re-cache the file every time. It does not taken existing functions into account.
/// </summary>
/// <returns>Return a version of current library database.</returns>
unsigned int XbSymbolDatabase_LibraryVersion();

/// <summary>
/// Total symbols return give ability to support for progress bar from third-party software. Not all symbols will be detected in every titles.
/// <param name="library_filter">See defined prefix of XbSymbolLib_ above to choose one or more library you wish to obtain total symbols.</param>
/// </summary>
/// <returns>Return total symbols in current database system.</returns>
unsigned XbSymbolDatabase_GetTotalSymbols(uint32_t library_filter);

/// <summary>
/// Register one or more library to be scan instead of whole database for optimize performance.
/// <param name="library_filter">See defined prefix of XbSymbolLib_ above to choose one or more library you wish to scan.</param>
/// </summary>
/// <returns>Return true if success, or else will return false for invalid parameter.</returns>
bool XbSymbolContext_RegisterLibrary(XbSymbolContextHandle pHandle, uint32_t library_filter);

/// <summary>
/// To register any detected symbol name with address and build version back to third-party program.
/// NOTE: Be aware of library name will be varity since some libraries are detecting in other sections as well.
/// </summary>
/// <param name="library_str">Name of the library in string.</param>
typedef void (*xb_output_message_t)(xb_output_message message_flag, const char* message_str);

/// <summary>
/// For output a message to a program when have information to be output.
/// </summary>
/// <param name="message_func">Set output message to a function.</param>
void XbSymbolDatabase_SetOutputMessage(xb_output_message_t message_func);

/// <summary>
/// To register any detected symbol name with address and build version back to third-party program.
/// NOTE: Be aware of library name will be varity since some libraries are detecting in other sections as well.
/// </summary>
/// <param name="library_str">Name of the library in string.</param>
/// <param name="library_flag">Name of the library in flag.</param>
/// <param name="symbol_str">Name of the library in symbol string.</param>
/// <param name="address">Return xbox's virtual address.</param>
/// <param name="build_verison">Found with specific build verison.</param>
typedef void (*xb_symbol_register_t)(const char* library_str, uint32_t library_flag, const char* symbol_str, xbaddr address, uint32_t build_verison);

/// <summary>
/// DEPRECATED: To scan symbols in memory of raw xbe or host's virtual xbox environment.
/// </summary>
/// <param name="xb_header_addr">Starting point of xbox header address.</param>
/// <param name="register_func">Callback register function to be call for any detected symbols.</param>
/// <param name="is_raw">True: Full scan of raw xbe; False: Scan only loaded sections.</param>
/// <returns>Only return false if something is not valid.</returns>
bool XbSymbolScan(const void* xb_header_addr, xb_symbol_register_t register_func, bool is_raw);

/// <summary>
/// To convert library name string into flag format.
/// </summary>
/// <param name="library_name">Input library name string.</param>
/// <returns>Return 0 if does not in the database. Otherwise will return flag value.</returns>
uint32_t XbSymbolDatabase_LibraryToFlag(const char* library_name);

/// <summary>
/// (Debug feature) By calling it will perform a self test for duplicate OOVPAs. (May will change at any time.)
/// </summary>
/// <returns>Return total count of errors.</returns>
unsigned int XbSymbolDatabase_TestOOVPAs();

/// <summary>
/// (Debug feature) Set to true will perform full range of OOVPAs registered in current database.
/// Or stop at xbe's build version detected.
/// </summary>
/// <param name="bypass_limit">Input boolean to either bypass or enable the build version limit.</param>
void XbSymbolContext_SetBypassBuildVersionLimit(XbSymbolContextHandle pHandle, bool bypass_limit);

/// <summary>
/// To set verbose level can be output message.
/// By default, release build is set to info+ level and debug build is set to debug+ level.
/// </summary>
/// <param name="verbose_level">See xb_output_message enum for list of options.</param>
/// <returns>True: Successful set. False: Invalid input value.</returns>
bool XbSymbolDatabase_SetOutputVerbosity(xb_output_message verbose_level);

/// <summary>
/// (Debug feature) Set to true will continue the same signature scan after first detected.
/// </summary>
/// <param name="enable">Input boolean to either continue with the signature scan after first symbol found or not.</param>
void XbSymbolContext_SetContinuousSigScan(XbSymbolContextHandle pHandle, bool enable);

/// <summary>
/// (Debug feature) Set to true will register first detected address only.
/// This function can be used if XbSymbolContext_SetContinuousSigScan is set to true.
/// </summary>
/// <param name="enable">Input boolean to use first symbol address only or not.</param>
void XbSymbolContext_SetFirstDetectAddressOnly(XbSymbolContextHandle pHandle, bool enable);

/// <summary>
/// Step 1: Generate library array for LibraryHeader input.
/// First call with <paramref name="library_out"/> as null pointer will return total count. Then second call will insert information to <paramref name="library_out"/>.filters field.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <param name="library_out">Input null pointer will provide the count to allocate memory for library_out.filters field. Otherwise, information will be input to library_out.filters field.</param>
/// <returns>Return total library found can be use in scan process.</returns>
unsigned int XbSymbolDatabase_GenerateLibraryFilter(const void* xb_header_addr, XbSDBLibraryHeader* library_out);

/// <summary>
/// Step 2: Generate section array for SectionHeader input.
/// First call with <paramref name="section_out"/> as null pointer will return total count. Then second call will insert information to <paramref name="section_out"/>.filters field.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <param name="section_out">Input null pointer will provide the count to allocate memory, then allocate memory to section_out.filters field.</param>
/// <param name="is_raw">True: Convert array to use raw xbe's relative address; False: Convert array to use xbox virtual memory relative address.</param>
/// <returns>Return total sections found can be use in scan process.</returns>
unsigned int XbSymbolDatabase_GenerateSectionFilter(const void* xb_header_addr, XbSDBSectionHeader* section_out, bool is_raw);

/// <summary>
/// Step 3: Get Xbox kernel thunk address.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <returns>Return kernel thunk address. NOTE: This function may not return valid address.</returns>
xbaddr XbSymbolDatabase_GetKernelThunkAddress(const void* xb_header_addr);

/// <summary>
/// Step 4: Create XbSymbolContextHandle context for the scan process.
/// </summary>
/// <param name="ppHandle">Output XbSymbolContextHandle handler.</param>
/// <param name="register_func">Register callback function for any detected symbols during scan process.</param>
/// <param name="library_input">See XbSymbolDatabase_GenerateLibraryFilter for details.</param>
/// <param name="section_input">See XbSymbolDatabase_GenerateSectionFilter for details.</param>
/// <param name="kernel_thunk">Input decoded virtual kernel thunk.</param>
/// <returns>Return true if context handle's creation is a success.</returns>
bool XbSymbolDatabase_CreateXbSymbolContext(XbSymbolContextHandle* ppHandle, xb_symbol_register_t register_func, XbSDBLibraryHeader library_input, XbSDBSectionHeader section_input, xbaddr kernel_thunk);

/// <summary>
/// Step 5: Perform a manual scan to set references, XRefDatabaseOffset, manually by requirement.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_ScanManual(XbSymbolContextHandle pHandle);

/// <summary>
/// Step 6a: (multi-thread safe, C11 standard) Process individual library input by third-party.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
/// <param name="pLibrary">Input pointer of a library to start a scan process.</param>
/// <param name="xref_first_pass">True: Optimized first search scan process; False: 2nd call and later will continue to return non-zero; see return for detail.</param>
/// <returns>Return total xref count found. Unless it return zero, then there's nothing left to find.</returns>
unsigned int XbSymbolContext_ScanLibrary(XbSymbolContextHandle pHandle, const XbSDBLibrary* pLibrary, bool xref_first_pass);

/// <summary>
/// Step 6b: (single-thread usage) Process all of filter libraries internally.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_ScanAllLibraryFilter(XbSymbolContextHandle pHandle);

/// <summary>
/// Step 7: Register any references, XRefDatabaseOffset, may not had been output during the scan process.
/// NOTE: Currently a stub at the moment.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_RegisterXRefs(XbSymbolContextHandle pHandle);

/// <summary>
/// Final Step: Release context.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_Release(XbSymbolContextHandle pHandle);

#ifdef __cplusplus
}
#endif

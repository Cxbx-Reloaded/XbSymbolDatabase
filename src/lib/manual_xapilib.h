// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// ******************************************************************
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
// *  All rights reserved
// *
// ******************************************************************
#pragma once

static bool manual_scan_section_xapilib(iXbSymbolContext* pContext,
                                        const iXbSymbolLibrarySession* pLibrarySession,
                                        SymbolDatabaseList* pLibraryDB,
                                        const XbSDBSection* pSection)
{
    // Generic usage
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;
    memptr_t buffer_upper = (memptr_t)pSection->buffer_lower + pSection->buffer_size;
    xbaddr xXbAddr = 0;
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;
    OOVPARevision* pOOVPARevision = NULL;
    OOVPATable* pSymbol = NULL;

    // Find XapiMapLetterToDirectory function
    if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_XapiMapLetterToDirectory])) {
        const char* sig_func_str = "XapiMapLetterToDirectory";
        const char* xref_str = "XGetSectionSize";

        xXbAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                   pLibrarySession,
                                                                   pLibraryDB,
                                                                   sig_func_str,
                                                                   pSection,
                                                                   true,
                                                                   &pSymbol,
                                                                   &pOOVPARevision);

        if (xXbAddr) {
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, pOOVPARevision->Version, xXbAddr);

            // Register XGetSectionSize function.
            if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_XGetSectionSize])) {
                // If relative address is not recorded, then signature needs a fix.
                output_message_format(&pContext->output,
                                      XB_OUTPUT_MESSAGE_ERROR,
                                      "Please verify %s (%hu) signature do contain %s's xref entry.",
                                      sig_func_str, pOOVPARevision->Version, xref_str);
                return false;
            }
            // Manually translate to virtual address from relative address.
            xXbAddr = internal_OOVPARevision_ConvertXRefRelativeAddrtToVirtAddr(pContext, pSymbol, pOOVPARevision, xref_str, XREF_XGetSectionSize);
            if (!xXbAddr) {
                // Error message is handled by above function. No extra message necessary here.
                return false;
            }
            pContext->xref_database[XREF_XGetSectionSize] = XREF_ADDR_UNDETERMINED; // Force reset to able register

            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_XGetSectionSize, pOOVPARevision->Version,
                                      xref_str, xXbAddr);
        }
    }

    // Find MU_Init function
    if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_MU_Init])) {

        xXbAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                   pLibrarySession,
                                                                   pLibraryDB,
                                                                   "MU_Init",
                                                                   pSection,
                                                                   true,
                                                                   &pSymbol,
                                                                   &pOOVPARevision);

        if (xXbAddr) {
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, pOOVPARevision->Version, xXbAddr);
        }
    }

    if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_MU_Init])) {
        // If not found, skip the rest of the scan.
        return false;
    }


    // Scan for IUsbInit::GetMaxDeviceTypeCount function.
    if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_IUsbInit_GetMaxDeviceTypeCount])) {
        xXbAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                   pLibrarySession,
                                                                   pLibraryDB,
                                                                   "IUsbInit_GetMaxDeviceTypeCount",
                                                                   pSection,
                                                                   true,
                                                                   &pSymbol,
                                                                   NULL);

        // If not found, skip the rest of the scan.
        if (xXbAddr == 0) {
            return false;
        }

        internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, xXbAddr);
    }


    xXbAddr = 0;
    // TODO: Move below into separate function.
    // search all of the buffer memory range
    for (memptr_t cur = (memptr_t)virt_start_relative + pContext->xref_database[XREF_MU_Init]; cur < buffer_upper; cur++) {
        // We are looking for "leave; ret 0x04;" for end of function then stop searching.
        if (cur[0] == 0xC9 && cur[1] == 0xC2 && cur[2] == 0x04) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Could not find g_DeviceType_MU from MU_Init!");
            return false;
        }

        // Look for possible push and call next to each other.
        if (cur[0] == 0x68 && cur[5] == 0xE8) {

            // check if call is linked to IUsbInit_GetMaxDeviceTypeCount function.
            xbaddr ActualAddr = *(xbaddr*)(cur + 6);
            if (MatchXRefAddr(cur + 6, virt_start_relative, pContext->xref_database[XREF_IUsbInit_GetMaxDeviceTypeCount])) {
                // this is where g_DeviceType_MU hardcode address reside in.
                xXbAddr = *(xbaddr*)(cur + 1);
                break;
            }
        }
    }

    // register if g_DeviceType_MU is not valid.
    if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_g_DeviceType_MU])) {

        // Register g_DeviceType_MU
        internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_g_DeviceType_MU, 3911,
                                  "g_DeviceType_MU", xXbAddr);
    }

    return true;
}

static inline void manual_register_xapilib(iXbSymbolContext* pContext)
{
    xbaddr xg_XapiMountedMUs = pContext->xref_database[XREF_g_XapiMountedMUs];
    if (internal_IsXRefAddrValid(xg_XapiMountedMUs)) {
        // Register g_XapiMountedMUs
        internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_XapiMountedMUs, 0, "g_XapiMountedMUs");
    }
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_XapiCurrentTopLevelFilter, 0, "g_XapiCurrentTopLevelFilter");
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_XAPI__tls_array, 0, "_tls_array");
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_XAPI__tls_index, 0, "_tls_index");
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_OFFSET_XapiCurrentFiber, 0, "XapiCurrentFiber_OFFSET");
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_OFFSET_XapiLastErrorCode, 0, "XapiLastErrorCode_OFFSET");
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_OFFSET_XapiThreadFiberData, 0, "XapiThreadFiberData_OFFSET");
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_XapiThreadNotifyRoutineList, 0, "XapiThreadNotifyRoutineList");
}

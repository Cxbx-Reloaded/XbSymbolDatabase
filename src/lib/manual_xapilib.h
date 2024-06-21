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

static bool internal_xapi_find_XGetSectionSize(iXbSymbolContext* pContext,
                                               const iXbSymbolLibrarySession* pLibrarySession,
                                               SymbolDatabaseList* pLibraryDB,
                                               const XbSDBSection* pSection,
                                               uintptr_t virt_start_relative)
{
    xbaddr xXbAddr = 0;
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
            // Update to use virtual address instead of relative address.
            pContext->xref_database[XREF_XGetSectionSize] = xXbAddr;

            internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_XGetSectionSize, pOOVPARevision->Version, xref_str, symbol_function, 0, NULL);
        }
    }

    return true;
}

static bool internal_xapi_find_DeviceType_MU(iXbSymbolContext* pContext,
                                             const iXbSymbolLibrarySession* pLibrarySession,
                                             SymbolDatabaseList* pLibraryDB,
                                             const XbSDBSection* pSection,
                                             uintptr_t virt_start_relative)
{
    xbaddr xXbAddr = 0;
    OOVPARevision* pOOVPARevision = NULL;
    OOVPATable* pSymbol = NULL;
    memptr_t buffer_upper = (memptr_t)pSection->buffer_lower + pSection->buffer_size;

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
                                  "g_DeviceType_MU", xXbAddr, symbol_variable, 0, NULL);
    }

    return true;
}

static bool internal_xapi_find_device_types(iXbSymbolContext* pContext,
                                            const iXbSymbolLibrarySession* pLibrarySession,
                                            SymbolDatabaseList* pLibraryDB,
                                            const XbSDBSection* pSection,
                                            uintptr_t virt_start_relative)
{
    xbaddr xXbAddr = 0;
    OOVPARevision* pOOVPARevision = NULL;
    OOVPATable* pSymbol = NULL;

    // Find GetTypeInformation_4 function
    if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_GetTypeInformation_4])) {
        xXbAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                   pLibrarySession,
                                                                   pLibraryDB,
                                                                   "GetTypeInformation_4",
                                                                   pSection,
                                                                   true,
                                                                   &pSymbol,
                                                                   &pOOVPARevision);

        // If GetTypeInformation_4 is not found, then try find GetTypeInformation_8
        if (!xXbAddr) {
            xXbAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                       pLibrarySession,
                                                                       pLibraryDB,
                                                                       "GetTypeInformation_8",
                                                                       pSection,
                                                                       true,
                                                                       &pSymbol,
                                                                       &pOOVPARevision);
        }

        // If either GetTypeInformation overload is found, start look up in DeviceTypeInfo table's entries.
        if (xXbAddr) {
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, pOOVPARevision->Version, xXbAddr);

            uint32_t* table_i = (uint32_t*)internal_section_VirtToHostAddress(pContext, pContext->xref_database[XREF_g_DeviceTypeInfoTableBegin]);
            uint32_t* table_end = (uint32_t*)internal_section_VirtToHostAddress(pContext, pContext->xref_database[XREF_g_DeviceTypeInfoTableEnd]);
            size_t type_description_table_count = ((memptr_t)table_end - (memptr_t)table_i) / sizeof(uint32_t);

            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "DeviceTypeInfoTable Entries: %u", type_description_table_count);

            // Partial extracted for ucType and XppType fields needed to get specific device type named.
            typedef struct _XID_TYPE_INFORMATION {
                uint8_t ucType;
                uint8_t bRemainingHandles;
                uint8_t ucUnknown[2]; // probably for xbox::dword_xt align
                xbaddr XppType;       // pointer to DeviceType structure.
            } XID_TYPE_INFORMATION, *PXID_TYPE_INFORMATION;

            // Iterate through the table until we find known device types.
            int i = 0;
            for (; table_i < table_end; table_i++, i++) {
                PXID_TYPE_INFORMATION DeviceTypeInfo = (PXID_TYPE_INFORMATION)internal_section_VirtToHostAddress(pContext, *table_i);
                if (!DeviceTypeInfo) {
                    // if address is nullptr, then skip it.
                    continue;
                }
                switch (DeviceTypeInfo->ucType) {
                    case 1: // Gamepad (Generic)
                        pContext->xref_database[XREF_g_DeviceType_Gamepad] = DeviceTypeInfo->XppType;
                        break;
                    case 2: // Keyboard
                        pContext->xref_database[XREF_g_DeviceType_Keyboard] = DeviceTypeInfo->XppType;
                        break;
                    case 3: // IR Dongle
                        pContext->xref_database[XREF_g_DeviceType_IRDongle] = DeviceTypeInfo->XppType;
                        break;
                    case 4: // Mouse
                        // NOTE: Possibly introduced when Phantasy Star Online (b4831) added keyboard support.
                        pContext->xref_database[XREF_g_DeviceType_Mouse] = DeviceTypeInfo->XppType;
                        break;
                    case 128: // Steel Battalion
                        pContext->xref_database[XREF_g_DeviceType_SBC] = DeviceTypeInfo->XppType;
                        break;
                    default: // Unknown
                        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Unknown device type, DeviceTypeInfoTable[%hhu]:  ucType = %hhu, XppType = %08X", i, DeviceTypeInfo->ucType, DeviceTypeInfo->XppType);
                        break;
                }
            }
        }
        else {
            // Find XInputOpen function
            if (!internal_IsXRefAddrValid(pContext->xref_database[XREF_XInputOpen])) {
                xXbAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                           pLibrarySession,
                                                                           pLibraryDB,
                                                                           "XInputOpen",
                                                                           pSection,
                                                                           true,
                                                                           &pSymbol,
                                                                           &pOOVPARevision);
                if (xXbAddr) {
                    internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, pOOVPARevision->Version, xXbAddr);
                    // No further manual action require.
                }
            }
        }
    }

    if (!xXbAddr) {
        return false;
    }

    return true;
};

static bool manual_scan_section_xapilib(iXbSymbolContext* pContext,
                                        const iXbSymbolLibrarySession* pLibrarySession,
                                        SymbolDatabaseList* pLibraryDB,
                                        const XbSDBSection* pSection)
{
    // Generic usage
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;

    bool foundXGetSectionSize = internal_xapi_find_XGetSectionSize(pContext, pLibrarySession, pLibraryDB, pSection, virt_start_relative);

    bool foundMURefs = internal_xapi_find_DeviceType_MU(pContext, pLibrarySession, pLibraryDB, pSection, virt_start_relative);

    bool foundDeviceTypes = internal_xapi_find_device_types(pContext, pLibrarySession, pLibraryDB, pSection, virt_start_relative);

    return foundXGetSectionSize && foundMURefs && foundDeviceTypes;
}

static inline void manual_register_xapilib(iXbSymbolContext* pContext)
{
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceType_Gamepad, 0, "g_DeviceType_Gamepad", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceType_IRDongle, 0, "g_DeviceType_IRDongle", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceType_Keyboard, 0, "g_DeviceType_Keyboard", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceType_Mouse, 0, "g_DeviceType_Mouse", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceType_SBC, 4242, "g_DeviceType_SBC", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceTypeInfoTableBegin, 4242, "g_DeviceTypeInfoTableBegin", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_DeviceTypeInfoTableEnd, 4242, "g_DeviceTypeInfoTableEnd", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_XapiAltLett_MU, 0, "g_XapiAltLett_MU", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_XapiMountedMUs, 0, "g_XapiMountedMUs", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_g_XapiCurrentTopLevelFilter, 0, "g_XapiCurrentTopLevelFilter", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF__tls_array, 0, "_tls_array", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF__tls_index, 0, "_tls_index", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_OFFSET_XapiCurrentFiber, 0, "XapiCurrentFiber_OFFSET", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_OFFSET_XapiLastErrorCode, 0, "XapiLastErrorCode_OFFSET", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_OFFSET_XapiThreadFiberData, 0, "XapiThreadFiberData_OFFSET", symbol_variable, 0, NULL);
    internal_RegisterValidXRefAddr_M(pContext, Lib_XAPILIB, XbSymbolLib_XAPILIB, XREF_XapiThreadNotifyRoutineList, 0, "XapiThreadNotifyRoutineList", symbol_variable, 0, NULL);
}

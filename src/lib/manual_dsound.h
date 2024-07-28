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

static bool manual_scan_section_dsound(iXbSymbolContext* pContext,
                                       const iXbSymbolLibrarySession* pLibrarySession,
                                       SymbolDatabaseList* pLibraryDB,
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
    OOVPATable* pSymbol = NULL;

    /*
    bool testRun = 1;
    while (testRun) {
    }//*/

    // Scan for DirectSoundStream's constructor function.
    if (pContext->xref_database[XREF_CDirectSoundStream_Constructor] == XREF_ADDR_UNDETERMINED) {
        xFuncAddr = (xbaddr)(uintptr_t)internal_LocateSymbolScan(pContext,
                                                                 pLibrarySession,
                                                                 pLibraryDB,
                                                                 "CDirectSoundStream_Constructor",
                                                                 pSection,
                                                                 true,
                                                                 &pSymbol,
                                                                 NULL);

        // If not found, skip the rest of the scan.
        if (xFuncAddr == 0) {
            return false;
        }

        internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, xFuncAddr);

        // TODO: If possible, integrate into the OOVPA structure.
        internal_RegisterXRef(pContext, pLibrarySession, XREF_DSS_VOICE_VTABLE, 3911,
                              NULL, *(xbaddr*)(virt_start_relative + xFuncAddr + 0x14), symbol_variable, 0, NULL, false);
        internal_RegisterXRef(pContext, pLibrarySession, XREF_DSS_STREAM_VTABLE, 3911,
                              NULL, *(xbaddr*)(virt_start_relative + xFuncAddr + 0x1B), symbol_variable, 0, NULL, false);
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
            // TODO: FIXME! BELOW ARE FUNCTIONS, TRY RETREIVE INFO SOMEHOW FOR PARAMETERS???
            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_AddRef, 3911,
                                      "CDirectSoundStream_AddRef", *(uint32_t*)(pFuncAddr + 0 * 4), symbol_function, 0, NULL);

            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_Release, 3911,
                                      "CDirectSoundStream_Release", *(uint32_t*)(pFuncAddr + 1 * 4), symbol_function, 0, NULL);

            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_GetInfo, 3911,
                                      "CDirectSoundStream_GetInfo", *(uint32_t*)(pFuncAddr + 2 * 4), symbol_function, 0, NULL);

            if (pLibrary->build_version < 4134) {
                internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_GetStatus, 3911,
                                          "CDirectSoundStream_GetStatus__r1", *(uint32_t*)(pFuncAddr + 3 * 4), symbol_function, 0, NULL);
            }
            else {
                internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_GetStatus, 4134,
                                          "CDirectSoundStream_GetStatus__r2", *(uint32_t*)(pFuncAddr + 3 * 4), symbol_function, 0, NULL);
            }

            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_Process, 3911,
                                      "CDirectSoundStream_Process", *(uint32_t*)(pFuncAddr + 4 * 4), symbol_function, 0, NULL);

            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_Discontinuity, 3911,
                                      "CDirectSoundStream_Discontinuity", *(uint32_t*)(pFuncAddr + 5 * 4), symbol_function, 0, NULL);

            internal_RegisterSymbol_M(pContext, pLibrarySession, XREF_CDirectSoundStream_Flush, 3911,
                                      "CDirectSoundStream_Flush", *(uint32_t*)(pFuncAddr + 6 * 4), symbol_function, 0, NULL);

            // NOTE: it is possible to manual add GetInfo, GetStatus, Process, Discontinuity,
            // and Flush functions.
        }
        else {
            return false;
        }
    }

    return true;
}

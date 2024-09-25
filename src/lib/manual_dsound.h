// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT

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
        // TODO: Lookup xref index instead of symbol name.
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
                              NULL, *(xbaddr*)(virt_start_relative + xFuncAddr + 0x14), symbol_variable, call_none, 0, NULL, false);
        internal_RegisterXRef(pContext, pLibrarySession, XREF_DSS_STREAM_VTABLE, 3911,
                              NULL, *(xbaddr*)(virt_start_relative + xFuncAddr + 0x1B), symbol_variable, call_none, 0, NULL, false);
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
            OOVPATable* pSymbol = NULL;
            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_AddRef);
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, *(uint32_t*)(pFuncAddr + 0 * 4));

            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_Release);
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, *(uint32_t*)(pFuncAddr + 1 * 4));

            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_GetInfo);
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, *(uint32_t*)(pFuncAddr + 2 * 4));

            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_GetStatus);
            // TODO: May need further investigation with Cxbx-Reloaded's source code for possible reasoning why this method is used.
            SYMBOL_COUNTER_VALUE; // Force increase by one symbol counter since we do not have both revisions difference in the OOVPA database.
            if (pLibrary->build_version < 4134) {
                internal_RegisterSymbolHelper(pContext, pLibrarySession, pSymbol, "CDirectSoundStream_GetStatus__r1", 3911, *(uint32_t*)(pFuncAddr + 3 * 4));
            }
            else {
                internal_RegisterSymbolHelper(pContext, pLibrarySession, pSymbol, "CDirectSoundStream_GetStatus__r2", 4134, *(uint32_t*)(pFuncAddr + 3 * 4));
            }

            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_Process);
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, *(uint32_t*)(pFuncAddr + 4 * 4));

            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_Discontinuity);
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, *(uint32_t*)(pFuncAddr + 5 * 4));

            internal_FindByReferenceHelper(pContext, pLibraryDB, pSymbol, CDirectSoundStream_Flush);
            internal_RegisterSymbol(pContext, pLibrarySession, pSymbol, 3911, *(uint32_t*)(pFuncAddr + 6 * 4));

            // NOTE: it is possible to manual add GetInfo, GetStatus, Process, Discontinuity,
            // and Flush functions.
        }
        else {
            return false;
        }
    }

    return true;
}

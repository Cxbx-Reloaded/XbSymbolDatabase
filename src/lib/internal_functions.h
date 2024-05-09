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

// ******************************************************************
// * internal functions designed for XbSymbolDatabase purpose
// ******************************************************************

static SymbolDatabaseList* internal_FindLibraryDB(uint32_t library_flag, unsigned* db_i)
{
    unsigned db = *db_i;
    for (; db < SymbolDBListCount; db++) {
        // Check if library flag match then return symbol database.
        if ((library_flag & SymbolDBList[db].LibSec.library) > 0) {
            *db_i = db;
            return &SymbolDBList[db];
        }
    }
    *db_i = db;
    return NULL;
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

static inline bool MatchXRefAddr(memptr_t cur, uintptr_t xb_start_virt_addr, xbaddr XRefAddr)
{
    xbaddr ActualAddr = *(xbaddr*)(cur);
    // check if PC-relative or direct reference matches XRef
    if ((ActualAddr + (xbaddr)((uintptr_t)cur - xb_start_virt_addr) + 4 != XRefAddr) && (ActualAddr != XRefAddr))
        return false;

    return true;
}

static bool CompareOOVPAToAddress(iXbSymbolContext* pContext, OOVPA* Oovpa, memptr_t cur, uintptr_t xb_start_virt_addr)
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

        // check if PC-relative or direct reference matches XRef
        if (!MatchXRefAddr(cur + Offset, xb_start_virt_addr, XRefAddr))
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

// Return if the given (XRef'erenced) is not set yet.
static inline bool internal_IsXRefUnset(uint16_t XRef)
{
    return (XRef == XREF_UNDETERMINED) || (XRef <= XREF_KT_COUNT);
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

static xbaddr internal_OOVPARevision_ConvertXRefRelativeAddrtToVirtAddr(iXbSymbolContext* pContext,
                                                                        const OOVPATable* pSymbol,
                                                                        const OOVPARevision* pRevision,
                                                                        const char* xref_str,
                                                                        XRefDatabase xref_target)
{
    if (pRevision->Oovpa->XRefCount == 0) {
        // Should not be triggered when there is no xref listed.
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "%s (%hu) signature cannot have zero XRefCount when calling %s!", pSymbol->szFuncName, pRevision->Version, __func__);
        return 0;
    }

    xbaddr virt_start_addr = pContext->xref_database[pSymbol->xref];

    LOVP* lovp = ((LOOVPA*)pRevision->Oovpa)->Lovp;
    int offset = -1;
    for (unsigned i = 0; i < pRevision->Oovpa->XRefCount; i++) {
        if (lovp->xref.index == xref_target) {
            offset = lovp->offset;
            break;
        }
    }

    if (offset == -1) {
        // If no match is found, then contributor need to verify both OOVPA revision and xref index are correct.
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "%s (%hu) signature does not have %s's xref entry!", pSymbol->szFuncName, pRevision->Version, xref_str);
        return 0;
    }

    virt_start_addr += offset + pContext->xref_database[xref_target] + 4 /*32 bit size of address space range */;

    return virt_start_addr;
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
static void* internal_LocateFunction(iXbSymbolContext* pContext,
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
    if (!xref_first_pass && Oovpa->XRefCount == XRefZero)
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

// NOTE: Do not use direct call to this function. Use internal_RegisterValidXRefAddr_M macro instead.
static void internal_RegisterValidXRefAddr(iXbSymbolContext* pContext,
                                           const char* library_name,
                                           uint32_t library_flag,
                                           uint32_t XRefIndex,
                                           uint16_t version,
                                           const char* symbol_name)
{
    xbaddr xSymbolAddr = pContext->xref_database[XRefIndex];

    if (internal_IsXRefAddrValid(xSymbolAddr)) {
        pContext->register_func(library_name, library_flag, XRefIndex, symbol_name, xSymbolAddr, version);
    }
}

// Always use this to be aware of manual register xrefs such as variables.
#define internal_RegisterValidXRefAddr_M(...) \
    SYMBOL_COUNTER_VALUE;                     \
    internal_RegisterValidXRefAddr(__VA_ARGS__);

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
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                  "Duplicate XREF address found for %s (%hu), %08X vs %08X!",
                                  symbol_name, version, xRefAddr, symbol_addr);
        }

        if (pContext->scan_first_detect) {
            return;
        }
    }

    internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XRefIndex, symbol_addr);
    if (do_register && pContext->register_func != NULL) {
        pContext->register_func(pLibrary->name, pLibrary->flag, XRefIndex, symbol_name, symbol_addr, version);
    }
}

// (Old / Manual) method
static void internal_RegisterSymbolManual(iXbSymbolContext* pContext,
                                          const iXbSymbolLibrarySession* pLibrarySession,
                                          const XRefDatabase xref,
                                          uint16_t version,
                                          const char* symbol_name,
                                          uint32_t symbol_addr)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // If XRef is not found, save it then register once.
    if (pContext->xref_database[xref] == XREF_ADDR_UNDETERMINED) {
        internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, xref, symbol_addr);
        if (pContext->register_func != NULL) {
            pContext->register_func(pLibrary->name, pLibrary->flag, xref, symbol_name, symbol_addr, version);
        }
    }
}

// Use _M suffix only, if OOVPA signature is not in database.
#define internal_RegisterSymbol_M(...) \
    SYMBOL_COUNTER_VALUE;              \
    internal_RegisterSymbolManual(__VA_ARGS__);

// New method
static void internal_RegisterSymbol(iXbSymbolContext* pContext,
                                    const iXbSymbolLibrarySession* pLibrarySession,
                                    const OOVPATable* pSymbol,
                                    uint16_t version,
                                    uint32_t symbol_addr)
{
    // forward to internal_RegisterSymbolManual to avoid need to copy paste between two identical functions.
    internal_RegisterSymbolManual(pContext, pLibrarySession, pSymbol->xref, version, pSymbol->szFuncName, symbol_addr);
}


static OOVPATable* internal_OOVPATable_FindSymbolFunction(SymbolDatabaseList* LibraryDB, const char* szFuncName, unsigned scan_type)
{
    for (unsigned i = 0; i < LibraryDB->SymbolsTableCount; i++) {

        // Intended for optimization purpose without need to search every single symbol's string.
        if ((scan_type & LibraryDB->SymbolsTable[i].scan_type) == 0) {
            continue;
        }

        if (strcmp(szFuncName, LibraryDB->SymbolsTable[i].szFuncName) == 0) {
            return &LibraryDB->SymbolsTable[i];
        }
    }
    return NULL;
}

static void internal_OOVPATable_scan(iXbSymbolContext* pContext,
                                     const iXbSymbolLibrarySession* pLibrarySession,
                                     const XbSDBSection* pSection,
                                     bool xref_first_pass,
                                     const OOVPATable* pSymbol,
                                     OOVPARevision** pRevisionReturn,
                                     void** pFuncReturn)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    OOVPARevision* pLastKnownRevision = NULL;
    void* pLastKnownFunc = 0;

    for (unsigned i = 0; i < pSymbol->count; i++) {
        OOVPARevision* pRevision = &pSymbol->revisions[i];

        // Skip higher build version
        if (pContext->strict_build_version_limit && pLibrary->build_version < pRevision->Version)
            continue;

        // Search for each function's location using the OOVPA
        void* pFunc = internal_LocateFunction(pContext, iLibraryType, pSymbol->szFuncName, pRevision->Version, pRevision->Oovpa, pSection, xref_first_pass);
        if (pFunc == 0) {
            continue;
        }

        if (pFunc == pLastKnownFunc && pLastKnownRevision == pRevision - 1) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                  "Duplicate OOVPA signature found for %s, %hu vs %hu!",
                                  pSymbol->szFuncName, pLastKnownRevision->Version, pRevision->Version);
        }

        if (pLibrary->build_version < pRevision->Version) {
            output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_WARN,
                                  "OOVPA signature is too high for [%hu] %s!",
                                  pRevision->Version, pSymbol->szFuncName);
        }

        pLastKnownFunc = pFunc;
        pLastKnownRevision = pRevision;
    }

    *pFuncReturn = pLastKnownFunc;
    *pRevisionReturn = pLastKnownRevision;
}

static void internal_OOVPA_register(iXbSymbolContext* pContext,
                                    const OOVPATable* Symbol,
                                    const OOVPARevision* OovpaRevision,
                                    const iXbSymbolLibrarySession* pLibrarySession,
                                    xbaddr address)
{
    if (OovpaRevision != NULL) {

        internal_RegisterSymbol(pContext, pLibrarySession, Symbol, OovpaRevision->Version, address);
    }
}

static void internal_OOVPA_scan(iXbSymbolContext* pContext,
                                OOVPATable* SymbolsTable,
                                unsigned int SymbolsTableCount,
                                const iXbSymbolLibrarySession* pLibrarySession,
                                const XbSDBSection* pSection,
                                bool xref_first_pass)
{
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    // traverse the full OOVPA table
    OOVPATable* pSymbolEnd = &SymbolsTable[SymbolsTableCount];
    OOVPATable* pSymbol = SymbolsTable;

    for (; pSymbol < pSymbolEnd; pSymbol++) {

        // We only want to do normal scan process.
        // If there's a symbol require manual scan, skip it.
        // Since manual scan is performed separately.
        if ((pSymbol->scan_type & DB_ST_AUTO) == 0) {
            continue;
        }

        OOVPARevision* pLastKnownRevision = NULL;
        void* pLastKnownFunc = 0;

        internal_OOVPATable_scan(pContext,
                                 pLibrarySession,
                                 pSection,
                                 xref_first_pass,
                                 pSymbol,
                                 &pLastKnownRevision,
                                 &pLastKnownFunc);

        if (pLastKnownRevision != NULL) {
            internal_OOVPA_register(pContext, pSymbol, pLastKnownRevision, pLibrarySession, (xbaddr)(uintptr_t)pLastKnownFunc);
        }
    }
}

// Intended design for manual scan without register. Could be expand
static void* internal_LocateSymbolFunction(iXbSymbolContext* pContext,
                                           const iXbSymbolLibrarySession* pLibrarySession,
                                           SymbolDatabaseList* pLibraryDB,
                                           const char* szFuncName,
                                           const XbSDBSection* pSection,
                                           bool xref_first_pass,
                                           OOVPATable** pSymbol,
                                           OOVPARevision** pOOVPARevision)
{
    void* pFunc = 0;
    OOVPARevision* pRevisionLocal = NULL;
    OOVPATable* pSymbolLocal = internal_OOVPATable_FindSymbolFunction(pLibraryDB, szFuncName, DB_ST_MANUAL);

    if (pSymbolLocal) {
        internal_OOVPATable_scan(pContext,
                                 pLibrarySession,
                                 pSection,
                                 xref_first_pass,
                                 pSymbolLocal,
                                 &pRevisionLocal,
                                 &pFunc);
    }

    if (pSymbol) {
        *pSymbol = pSymbolLocal;
    }

    if (pOOVPARevision) {
        *pOOVPARevision = pRevisionLocal;
    }
    return pFunc;
}

static eLibraryType internal_GetLibraryType(uint32_t library)
{
    switch (library) {
        default:
            return LT_UNKNOWN;
        case XbSymbolLib_D3D8:
        case XbSymbolLib_D3D8LTCG:
        case XbSymbolLib_D3DX8:
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
        case XbSymbolLib_XONLINLS:
        case XbSymbolLib_XNET:
        case XbSymbolLib_XNETS:
        case XbSymbolLib_XNETN:
            return LT_NETWORK;
    }
}

static bool internal_SetLibraryTypeStart(iXbSymbolContext* pContext, eLibraryType library_type)
{
    if (!iXbSymbolContext_AllowScanLibrary(pContext)) {
        return false;
    }

    // Don't accept request if library type is unknown.
    if (library_type <= LT_UNKNOWN || LT_MAX <= library_type) {
        return false;
    }

    bool ret = false;

    // Accept request if library type is inactive.
    if (!pContext->library_contexts[library_type].is_active) {
        // Then accept the scan request.
        pContext->library_contexts[library_type].is_active = true;
        ret = true;
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type active: %u", library_type);
    }

    return ret;
}

static void internal_SetLibraryTypeEnd(iXbSymbolContext* pContext, eLibraryType library_type)
{
    // If library is active, deny the scan request.
    if (!pContext->library_contexts[library_type].is_active) {
        output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_ERROR, "Attempted to set already inactive library type %u.", library_type);
    }

    pContext->library_contexts[library_type].is_active = false;
    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Library type inactive: %u", library_type);
}

static memptr_t internal_section_VirtToHostAddress(iXbSymbolContext* pContext, xbaddr virt_addr)
{
    memptr_t host_addr = NULL;
    XbSDBSection* section_filter = pContext->section_input.filters;
    for (unsigned i = 0; i < pContext->section_input.count; i++, section_filter++) {
        // Check if virt_addr match within specific section range, then convert to host address.
        if (section_filter->xb_virt_addr <= virt_addr && virt_addr <= section_filter->xb_virt_addr + section_filter->buffer_size) {
            host_addr = (memptr_t)section_filter->buffer_lower - section_filter->xb_virt_addr + virt_addr;
            break;
        }
    }
    return host_addr;
}

static xbaddr internal_section_HostToVirtAddress(iXbSymbolContext* pContext, memptr_t host_addr)
{
    xbaddr virt_addr = 0;
    XbSDBSection* section_filter = pContext->section_input.filters;
    for (unsigned i = 0; i < pContext->section_input.count; i++, section_filter++) {
        // Check if host_addr match within specific section range, then convert to virtual address.
        if ((memptr_t)section_filter->buffer_lower <= host_addr && host_addr <= (memptr_t)section_filter->buffer_lower + section_filter->buffer_size) {
            virt_addr = (xbaddr)(host_addr - (memptr_t)section_filter->buffer_lower + section_filter->xb_virt_addr);
            break;
        }
    }
    return virt_addr;
}

static bool internal_LibraryFilterPermitScan(iXbSymbolContext* pContext, uint32_t library_flag)
{
    if (pContext->library_filter == 0 || (pContext->library_filter & library_flag) > 0) {
        return true;
    }
    return false;
}

// Check & update if build version is higher than existing library flag.
static void internal_LibraryFilterUpdateVersionIfGreater(XbSDBLibrary* filters,
                                                         unsigned int count,
                                                         uint32_t library_flags,
                                                         uint16_t wBuildVersion,
                                                         uint16_t QFEVersion)
{
    for (unsigned filter_i = 0; filter_i < count; filter_i++) {
        if (filters[filter_i].flag & library_flags) {
            if (filters[filter_i].build_version < wBuildVersion) {
                filters[filter_i].build_version = wBuildVersion;
                filters[filter_i].qfe_version = QFEVersion;
            }
            else if (filters[filter_i].qfe_version < QFEVersion) {
                filters[filter_i].qfe_version = QFEVersion;
            }
        }
    }
}

// Check & update existing library flag to new library flag.
static void internal_LibraryFilterUpdateFlagIfExist(XbSDBLibrary* filters,
                                                    unsigned int count,
                                                    uint32_t library_flag_find,
                                                    uint32_t library_flag_set)
{
    for (unsigned filter_i = 0; filter_i < count; filter_i++) {
        if ((filters[filter_i].flag & library_flag_find) == library_flag_find) {
            filters[filter_i].flag = library_flag_set;
            memcpy(filters[filter_i].name, XbSymbolDatabase_LibraryToString(library_flag_set), 8);
        }
    }
}

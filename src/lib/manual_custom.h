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
// * Used for XbSymbolContext_ScanManual
// ******************************************************************

// Each include is base on library requirement to do by hand
#include "manual_d3d8__ltcg.h"
#include "manual_dsound.h"
#include "manual_xapilib.h"

static bool manual_scan_library_custom(iXbSymbolContext* pContext,
                                       custom_scan_func_t custom_scan_func,
                                       const iXbSymbolLibrarySession* pLibSession)
{
    bool scan_ret = false;

    const XbSDBSection* pSectionScan;

    SymbolDatabaseList* pLibraryDB;
    unsigned db_i = 0;
    while ((pLibraryDB = internal_FindLibraryDB(pLibSession->pLibrary->flag, &db_i))) {
        db_i++;
        for (unsigned int s = 0; s < pContext->section_input.count; s++) {

            // Initialize a matching specific section is currently pair with library in order to scan specific section only.
            // By doing this method will reduce false detection dramatically. If it had happened before.
            for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                if (pLibraryDB->LibSec.section[d3] != NULL &&
                    strncmp(pContext->section_input.filters[s].name, pLibraryDB->LibSec.section[d3], 8) == 0) {

                    pSectionScan = pContext->section_input.filters + s;

                    output_message_format(&pContext->output, XB_OUTPUT_MESSAGE_DEBUG, "Scanning %.8s library in %.8s section",
                                          pLibSession->pLibrary->name, pSectionScan->name);

                    scan_ret = custom_scan_func(pContext, pLibSession, pLibraryDB, pSectionScan);

                    if (scan_ret) {
                        // let's return true here instead of waste the loops for nothing.
                        return scan_ret;
                    }
                }
            }
        }
        // Use the break if there are 2+ bit flags set such as include LTCG flag in std flag's oovpa database like D3D8.
        if ((pLibraryDB->LibSec.library & ~pLibSession->pLibrary->flag) == 0) {
            break;
        }
    }
    return scan_ret;
}

static inline void manual_register_symbols(iXbSymbolContext* pContext)
{
    manual_register_d3d8__ltcg(pContext);
    manual_register_xapilib(pContext);
}

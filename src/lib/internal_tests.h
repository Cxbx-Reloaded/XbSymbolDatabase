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
// * Used for XbSymbolDatabase_TestOOVPAs
// ******************************************************************

typedef struct _SymbolDatabaseVerifyContextUniform {
    SymbolDatabaseList* data;
    OOVPA* oovpa;
    uint32_t symbol_index;
    uint32_t revision_index;
} SymbolDatabaseVerifyContextUniform;

typedef struct _SymbolDatabaseVerifyContext {
    SymbolDatabaseVerifyContextUniform main;
    SymbolDatabaseVerifyContextUniform against;
    OutputHandler output;
} SymbolDatabaseVerifyContext;

static int OOVPAErrorString(char* bufferTemp, SymbolDatabaseList* data, OOVPATable* symbol, uint32_t index)
{
    // Convert active data pointer to an index base on starting point of SymbolDBList.
    unsigned int db_index = (unsigned int)(data - SymbolDBList);
    // Convert active symbol pointer to an index base on starting point of SymbolsTable.
    unsigned int sym_index = (unsigned int)(symbol - data->SymbolsTable);

    return sprintf(bufferTemp, "OOVPATable db=%2u, i=[%4u], b=%4hu s=%s[%4u]", db_index, sym_index, symbol->revisions[index].Version, symbol->szFuncName, index);
}

static void SymbolDatabaseVerifyContext_OOVPAError(SymbolDatabaseVerifyContext* context, char* format, ...)
{
    char buffer[2048] = { 0 };
    static char bufferTemp[400] = { 0 };
    int ret_str_count;

    if (context->main.data != NULL) {

        ret_str_count = OOVPAErrorString(bufferTemp, context->main.data, context->main.data->SymbolsTable + context->main.symbol_index, context->main.revision_index);
        (void)strncat(buffer, bufferTemp, ret_str_count);
    }

    if (context->against.oovpa != NULL && context->against.data != NULL) {
        (void)strcat(buffer, ", comparing against ");

        ret_str_count = OOVPAErrorString(bufferTemp, context->against.data, context->against.data->SymbolsTable + context->against.symbol_index, context->against.revision_index);
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

    if (context->against.oovpa == NULL) {
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
                SymbolDatabaseVerifyContext_OOVPAError(context,
                                                       "Lovp[%2u] : Offset (0x%03x) must be larger then previous offset (0x%03x)",
                                                       p, curr_offset, prev_offset);
            }
            prev_offset = curr_offset;
        }

        // find duplicate OOVPA's across all other data-table-oovpa's
        context->main.oovpa = oovpa;
        context->against.oovpa = oovpa;
        error_count += SymbolDatabaseVerifyContext_VerifyDatabaseList(context);
        context->against.oovpa = NULL; // reset scanning state
        return error_count;
    }

    // prevent checking an oovpa against itself
    if ((&context->main.data->SymbolsTable[context->main.symbol_index].revisions + context->main.revision_index) ==
        (&context->against.data->SymbolsTable[context->against.symbol_index].revisions + context->against.revision_index)) {
        return error_count;
    }

    // compare {Offset, Value}-pairs between two OOVPA's
    OOVPA *left = context->against.oovpa, *right = oovpa;
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
        }
        else if (left_offset > right_offset) {
            unique_offset_right++;
            left_next = false;
        }
        else if (left_value == right_value) {
            equal_offset_value++;
        }
        else {
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
                    SymbolDatabaseVerifyContext_OOVPAError(context,
                                                           "OOVPA's are identical",
                                                           unique_offset_left,
                                                           unique_offset_right);
                }
            }
            else {
                // not too many new OV-pairs on the left side?
                if (unique_offset_left < 6) {
                    // not too many new OV-pairs on the right side?
                    if (unique_offset_right < 6) {
                        error_count++;
                        SymbolDatabaseVerifyContext_OOVPAError(context,
                                                               "OOVPA's are expanded (left +%d, right +%d)",
                                                               unique_offset_left,
                                                               unique_offset_right);
                    }
                }
            }
        }
    }
    return error_count;
}

static unsigned int SymbolDatabaseVerifyContext_VerifyEntry(SymbolDatabaseVerifyContext* context, const OOVPATable* table, uint32_t symbol_index, uint32_t revision_index)
{
    unsigned int error_count = 0;
    if (context->against.oovpa == NULL) {
        context->main.symbol_index = symbol_index;
        context->main.revision_index = revision_index;


    }
    else {
        context->against.symbol_index = symbol_index;
        context->against.revision_index = revision_index;
    }


    // verify the OOVPA of this entry
    if (table[symbol_index].revisions[revision_index].Oovpa != NULL) {
        error_count += SymbolDatabaseVerifyContext_VerifyOOVPA(context, table[symbol_index].revisions[revision_index].Oovpa);
    }
    return error_count;
}

static unsigned int SymbolDatabaseVerifyContext_VerifyDatabase(SymbolDatabaseVerifyContext* context, SymbolDatabaseList* data)
{
    unsigned int error_count = 0;
    if (context->against.oovpa == NULL) {
        context->main.data = data;
    }
    else {
        context->against.data = data;
    }

    // Verify each entry in data's symbol table.
    for (uint32_t s = 0; s < data->SymbolsTableCount; s++) {
        // We only need to check from main, not against.
        if (context->against.data == NULL) {
            // For safety check purpose
            if (internal_IsXRefUnset(data->SymbolsTable[s].xref)) {
                output_message_format(&context->output, XB_OUTPUT_MESSAGE_ERROR, "%s cannot have unset xref.", data->SymbolsTable[s].szFuncName);
                error_count++;
            }
        }

        // Check each revision entry in a symbol.
        for (uint32_t r = 0; r < data->SymbolsTable[s].count; r++) {
            error_count += SymbolDatabaseVerifyContext_VerifyEntry(context, data->SymbolsTable, s, r);
        }
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

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
// * Used for XbSymbolDatabase_LibraryVersion
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

    for (unsigned i = 0; i < pTable->count; i++) {
        // Part 2: version number
        hash_fnv1a(Hash, &pTable->revisions[i].Version, sizeof(pTable->revisions[i].Version));

        // Part 3: LOOVPA
        if (pTable->revisions[i].Oovpa) {
            HashAssumedLOOVPA(Hash, pTable->revisions[i].Oovpa);
        }
    }
}

void HashSymbolData(unsigned int* Hash, SymbolDatabaseList* pData)
{
    for (unsigned int i = 0; i < pData->SymbolsTableCount; ++i) {
        HashOOVPATable(Hash, &pData->SymbolsTable[i]);
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

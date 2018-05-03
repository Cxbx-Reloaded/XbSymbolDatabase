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
// *
// *  All rights reserved
// *
// ******************************************************************
#define _XBOXKRNL_DEFEXTRN_

#include "xbSymbolDatabase.h" // For PairScanLibSec

#include "OOVPADatabase/Xapi.OOVPA.inl"
#include "OOVPADatabase/D3D8.OOVPA.inl"
#include "OOVPADatabase/D3D8LTCG.OOVPA.inl"
#include "OOVPADatabase/DSound.OOVPA.inl"
#include "OOVPADatabase/XG.OOVPA.inl"
#include "OOVPADatabase/XNET.OOVPA.inl"
#include "OOVPADatabase/XOnline.OOVPA.inl"
#include "OOVPADatabase/XactEng.OOVPA.inl"


// ******************************************************************
// * Xbox Symbol Table Database
// ******************************************************************

const SymbolDatabaseList SymbolDBList[] = {
    // Support inline functions in .text section
    { Lib_D3D8,{ Sec_text, Sec_D3D }, &D3D8_OOVPAV2, D3D8_OOVPA_COUNT },

    // Cannot support LTCG in HLE
    { Lib_D3D8LTCG,{ Sec_D3D }, &D3D8LTCG_OOVPAV2, D3D8LTCG_OOVPA_COUNT },

    // Jarupxx mention this is not a requirement?
    //{ Lib_D3DX8,{ Sec_D3DX }, _OOVPAV2, _OOVPA_COUNT },

    //
    { Lib_DSOUND,{ Sec_DSOUND }, &DSound_OOVPAV2, DSound_OOVPA_COUNT },

    // DSOUNDH is just meant to define hot fix, there is no separate section
    //{ Lib_DSOUNDH,{ Sec_DSOUND }, DSound_OOVPAV2, DSound_OOVPA_COUNT },

    //
    { Lib_XACTENG, { Sec_XACTENG }, &XACTENG_OOVPAV2, XACTENG_OOVPA_COUNT },

    // test case: Power Drome (Unluckily, it use LTCG version of the library.)
    //{ Lib_XACTENLT,{ Sec_XACTENG }, XACTENG_OOVPAV2, XACTENG_OOVPA_COUNT },

    //
    { Lib_XAPILIB,{ Sec_text, Sec_XPP }, &XAPILIB_OOVPAV2, XAPILIB_OOVPA_COUNT },

    // Support inline functions in .text section
    { Lib_XGRAPHC,{ Sec_text, Sec_XGRPH }, &XGRAPHC_OOVPAV2, XGRAPHC_OOVPA_COUNT },

    // Cannot support LTCG in HLE
    //{ Lib_XGRAPHCL,{ Sec_XGRPH }, XGRAPHC_OOVPAV2, XGRAPHC_OOVPA_COUNT },

    // Added Sec_text and Sec_XNET just in case.
    // TODO: Need to find out which function is only part of XOnlines.
    { Lib_XONLINE,{ Sec_text, Sec_XONLINE, Sec_XNET }, &XONLINES_OOVPAV2, XONLINES_OOVPA_COUNT },

    // Fun fact, XONLINES are split into 2 header sections.
    { Lib_XONLINES,{ Sec_text, Sec_XONLINE, Sec_XNET }, &XONLINES_OOVPAV2, XONLINES_OOVPA_COUNT },

    // Added Sec_text just in case.
    // TODO: Need to find out which function is only part of XNets.
    { Lib_XNET,{ Sec_text, Sec_XNET }, &XNET_OOVPAV2, XNET_OOVPA_COUNT },

    // XNETS only has XNET, might be true.
    { Lib_XNETS,{ Sec_text, Sec_XNET }, &XNET_OOVPAV2, XNET_OOVPA_COUNT },

    // test case: Stake
    { Lib_XNETN,{ Sec_text, Sec_XNET }, &XNET_OOVPAV2, XNET_OOVPA_COUNT },
};

// ******************************************************************
// * SymbolDBListCount
// ******************************************************************
const unsigned int SymbolDBListCount = OOVPA_TABLE_COUNT(SymbolDBList);

// ******************************************************************
// * XRefDataBase
// ******************************************************************
unsigned int XRefDataBase[XREF_COUNT] = { 0 }; // Reset and populated by EmuHLEIntercept


// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

// NOTE: PatrickvL state the arguments are named differently and the function does something that has another meaning,
//       the implementation could be changed if the need ever arises.
inline void GetXRefEntry(OOVPA *oovpa, int index, uint32_t* xref_out, uint8_t* offset_out) {
    // Note : These are stored swapped by the XREF_ENTRY macro, hence this difference from GetOovpaEntry :
    *xref_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].Offset;
    *offset_out = ((LOOVPA*)oovpa)->Lovp[index].Value;
}

inline void GetOovpaEntry(OOVPA *oovpa, int index, uint32_t* offset_out, uint8_t* value_out) {
    *offset_out = (unsigned int)((LOOVPA*)oovpa)->Lovp[index].Offset;
    *value_out = ((LOOVPA*)oovpa)->Lovp[index].Value;
}

bool CompareOOVPAToAddress(OOVPA *Oovpa, uint32_t cur) {
    uint32_t v = 0; // verification counter

                  // Check all XRefs, stop if any does not match
    for (; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint8_t Offset;

        // get currently registered (un)known address
        GetXRefEntry(Oovpa, v, &XRef, &Offset);
        uint32_t XRefAddr = XRefDataBase[XRef];
        // Undetermined XRef cannot be checked yet
        // (EmuLocateFunction already checked this, but this check
        // is cheap enough to keep, and keep this function generic).
        if (XRefAddr == XREF_ADDR_UNDETERMINED)
            return false;

        // Don't verify an xref that has to be (but isn't yet) derived
        if (XRefAddr == XREF_ADDR_DERIVE)
            continue;

        uint32_t ActualAddr = *(uint32_t*)(cur + Offset);
        // check if PC-relative or direct reference matches XRef
        if ((ActualAddr + cur + Offset + 4 != XRefAddr) && (ActualAddr != XRefAddr))
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
extern uint32_t EmuLocateFunction(OOVPA *Oovpa, uint32_t lower, uint32_t upper) {
    // skip out if this is an unnecessary search
    if (!bXRefFirstPass && Oovpa->XRefCount == XRefZero && Oovpa->XRefSaveIndex == XRefNoSaveIndex)
        return 0;

    uint32_t derive_indices = 0;
    // Check all XRefs are known (if not, don't do a useless scan) :
    for (uint32_t v = 0; v < Oovpa->XRefCount; v++) {
        uint32_t XRef;
        uint8_t Offset;

        // get currently registered (un)known address
        GetXRefEntry(Oovpa, v, &XRef, &Offset);
        uint32_t XRefAddr = XRefDataBase[XRef];
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

    // search all of the image memory
    for (uint32_t cur = lower; cur < upper; cur++)
        if (CompareOOVPAToAddress(Oovpa, cur)) {

            while (derive_indices > 0) {
                uint32_t XRef;
                uint8_t Offset;
                uint32_t derive_index;

                // Extract an index from the indices mask :
                _BitScanReverse(&derive_index, derive_indices); // MSVC intrinsic; GCC has __builtin_clz
                derive_indices ^= (1 << derive_index);

                // get currently registered (un)known address
                GetXRefEntry(Oovpa, derive_index, &XRef, &Offset);

                // Calculate the address where the XRef resides
                uint32_t XRefAddr = cur + Offset;
                // Read the address it points to
                XRefAddr = *((uint32_t*)XRefAddr);

                // NOTE: Commented out code belows are no longer valid since we are using lower and upper passdown only.

                /* For now assume it's a direct reference;
                // TODO : Check if it's PC-relative reference?
                if (XRefAddr + cur + Offset + 4 < XBE_MAX_VA)
                XRefAddr = XRefAddr + cur + Offset + 4;
                */

                // Does the address seem valid?
                /*if (XRefAddr < XBE_MAX_VA) {
                    // save and count the derived address
                    UnResolvedXRefs--;
                    XRefDataBase[XRef] = XRefAddr;
                }*/
                UnResolvedXRefs--;
                XRefDataBase[XRef] = XRefAddr;
            }

            return cur;
        }

    // found nothing
    return 0;
}

// ******************************************************************
// * GetSymbolDataBaseHash
// ******************************************************************

// Adapted from https://gist.github.com/underscorediscovery/81308642d0325fd386237cfa3b44785c
#define fnv1aprime 0x1000193;
void hash_fnv1a(unsigned int* hash, const void* key, const unsigned int len) {
    const char* data = (char*)key;
    for (unsigned int i = 0; i < len; ++i) {
        unsigned char value = data[i];
        *hash ^= value;
        *hash *= fnv1aprime;
    }
}

void HashAssumedLOOVPA(unsigned int* Hash, const OOVPA* pAssumedLOOVPA) {
    // Number of offset-value pairs in the "Header" LOOVPA structure
    unsigned int Size = pAssumedLOOVPA->Count * sizeof(LOVP);

    // Size of "Header" structure
    Size += sizeof(OOVPA);

    // Part 1: The array of OOVPA::LOVP items
    hash_fnv1a(Hash, pAssumedLOOVPA, Size);
}

void HashOOVPATable(unsigned int* Hash, const OOVPATable* pTable) {
    // Part 1: function name string
    if (pTable->szFuncName != (void*)0) {
        hash_fnv1a(Hash, pTable->szFuncName, strlen(pTable->szFuncName));
    }

    // Part 2: version number
    hash_fnv1a(Hash, &pTable->Version, sizeof(pTable->Version));

    // Part 3: LOOVPA
    if (pTable->Oovpa) {
        HashAssumedLOOVPA(Hash, pTable->Oovpa);
    }
}

void HashSymbolData(unsigned int* Hash, const SymbolDatabaseList* pData) {
    for (unsigned int i = 0; i < pData->OovpaTableCount; ++i) {
        HashOOVPATable(Hash, &pData->OovpaTable[i]);
    }
}

const unsigned int HashSymbolDataArray(const SymbolDatabaseList* pDataArray, unsigned int Count) {
    unsigned int Hash = 0x811c9dc5;
    for (unsigned int i = 0; i < Count; ++i) {
        HashSymbolData(&Hash, pDataArray + i);
    }
    return Hash;
}

extern unsigned int GetSymbolDataBaseHash() {
    // Calculate this just once
    static unsigned int CalculatedHash = 0;
    if (CalculatedHash == 0) {
        CalculatedHash = HashSymbolDataArray(SymbolDBList, SymbolDBListCount);
    }
    return CalculatedHash;
}

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
// *  (c) 2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#define _XBOXKRNL_DEFEXTRN_

#include <string.h>

// ******************************************************************
// * Xbox Symbol Database
// ******************************************************************

#include "xbSymbolDatabase.h"
#include "Xbe.h"

// ******************************************************************
// * Xbox Symbol OOVPA Database
// ******************************************************************

#include "OOVPADatabase/Xapi.OOVPA.inl"
#include "OOVPADatabase/D3D8.OOVPA.inl"
#include "OOVPADatabase/D3D8LTCG.OOVPA.inl"
#include "OOVPADatabase/DSound.OOVPA.inl"
#include "OOVPADatabase/XG.OOVPA.inl"
#include "OOVPADatabase/XNET.OOVPA.inl"
#include "OOVPADatabase/XOnline.OOVPA.inl"
#include "OOVPADatabase/XactEng.OOVPA.inl"

#define PAIRSCANSEC_MAX 3

typedef const struct _PairScanLibSec {
    uint32_t library;
    const char *section[PAIRSCANSEC_MAX];
} PairScanLibSec;

typedef const struct _SymbolDatabaseList {

    PairScanLibSec LibSec;

    OOVPATable     *OovpaTable;
    unsigned int    OovpaTableCount;
} SymbolDatabaseList;

SymbolDatabaseList SymbolDBList[] = {
    // Support inline functions in .text section
    { XbSymbolLib_D3D8,{ Sec_text, Sec_D3D }, D3D8_OOVPAV2, D3D8_OOVPA_COUNT },

    // Cannot support LTCG in HLE
    { XbSymbolLib_D3D8LTCG,{ Sec_D3D }, D3D8LTCG_OOVPAV2, D3D8LTCG_OOVPA_COUNT },

    // Jarupxx mention this is not a requirement?
    //{ Lib_D3DX8,{ Sec_D3DX }, _OOVPAV2, _OOVPA_COUNT },

    //
    { XbSymbolLib_DSOUND,{ Sec_DSOUND }, DSound_OOVPAV2, DSound_OOVPA_COUNT },

    // DSOUNDH is just meant to define hot fix, there is no separate section
    //{ XbSymbolLib_DSOUNDH,{ Sec_DSOUND }, &DSound_OOVPAV2, DSound_OOVPA_COUNT },

    //
    { XbSymbolLib_XACTENG, { Sec_XACTENG }, XACTENG_OOVPAV2, XACTENG_OOVPA_COUNT },

    // test case: Power Drome (Unluckily, it use LTCG version of the library.)
    //{ XbSymbolLib_XACTENLT,{ Sec_XACTENG }, XACTENG_OOVPAV2, XACTENG_OOVPA_COUNT },

    //
    { XbSymbolLib_XAPILIB,{ Sec_text, Sec_XPP }, XAPILIB_OOVPAV2, XAPILIB_OOVPA_COUNT },

    // Support inline functions in .text section
    { XbSymbolLib_XGRAPHC,{ Sec_text, Sec_XGRPH }, XGRAPHC_OOVPAV2, XGRAPHC_OOVPA_COUNT },

    // Cannot support LTCG in HLE
    //{ Lib_XGRAPHCL,{ Sec_XGRPH }, XGRAPHC_OOVPAV2, XGRAPHC_OOVPA_COUNT },

    // Added Sec_text and Sec_XNET just in case.
    // TODO: Need to find out which function is only part of XOnlines.
    { XbSymbolLib_XONLINE,{ Sec_text, Sec_XONLINE, Sec_XNET }, XONLINES_OOVPAV2, XONLINES_OOVPA_COUNT },

    // Fun fact, XONLINES are split into 2 header sections.
    { XbSymbolLib_XONLINES,{ Sec_text, Sec_XONLINE, Sec_XNET }, XONLINES_OOVPAV2, XONLINES_OOVPA_COUNT },

    // Added Sec_text just in case.
    // TODO: Need to find out which function is only part of XNets.
    { XbSymbolLib_XNET,{ Sec_text, Sec_XNET }, XNET_OOVPAV2, XNET_OOVPA_COUNT },

    // XNETS only has XNET, might be true.
    { XbSymbolLib_XNETS,{ Sec_text, Sec_XNET }, XNET_OOVPAV2, XNET_OOVPA_COUNT },

    // test case: Stake
    { XbSymbolLib_XNETN,{ Sec_text, Sec_XNET }, XNET_OOVPAV2, XNET_OOVPA_COUNT },
};

// ******************************************************************
// * SymbolDBListCount
// ******************************************************************
const unsigned int SymbolDBListCount = OOVPA_TABLE_COUNT(SymbolDBList);

// ******************************************************************
// * XRefDataBase
// ******************************************************************
unsigned int XRefDataBase[XREF_COUNT] = { 0 }; // Reset and populated by EmuHLEIntercept

bool bXRefFirstPass; // For search speed optimization, set in XbSymbolScan, read in XbSymbolLocateFunction
unsigned int UnResolvedXRefs = XREF_COUNT;


// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

uint32_t g_library_flag = 0;
bool XbSymbolRegisterLibrary(uint32_t library_flag) {

    // Check to make sure all flags are acceptable before set.
    if ((library_flag & ~XbSymbolLib_ALL) > 0) {
        return 0;
    }

    g_library_flag = library_flag;
    return 1;
}

const char* XbSymbolLibraryToString(uint32_t library_flag) {
    switch (library_flag) {
        case XbSymbolLib_D3D8: {
            return Lib_D3D8;
        }
        case XbSymbolLib_D3D8LTCG: {
            return Lib_D3D8LTCG;
        }
        case XbSymbolLib_D3DX8: {
            return Lib_D3DX8;
        }
        case XbSymbolLib_DSOUND: {
            return Lib_DSOUND;
        }
        case XbSymbolLib_XACTENG: {
            return Lib_XACTENG;
        }
        case XbSymbolLib_XAPILIB: {
            return Lib_XAPILIB;
        }
        case XbSymbolLib_XGRAPHC: {
            return Lib_XGRAPHC;
        }
        case XbSymbolLib_XNET: {
            return Lib_XNET;
        }
        case XbSymbolLib_XNETN: {
            return Lib_XNETN;
        }
        case XbSymbolLib_XNETS: {
            return Lib_XNETS;
        }
        case XbSymbolLib_XONLINE: {
            return Lib_XONLINE;
        }
        case XbSymbolLib_XONLINES: {
            return Lib_XONLINES;
        }
        default: {
            return Lib_UNKNOWN;
        }
    }
}

inline uint32_t XbSymbolLibrayToFlag(const char* library_name) {
    if (strncmp(library_name, Lib_D3D8, 8) == 0) {
        return XbSymbolLib_D3D8;
    }
    if (strncmp(library_name, Lib_D3D8LTCG, 8) == 0) {
        return XbSymbolLib_D3D8LTCG;
    }
    if (strncmp(library_name, Lib_D3DX8, 8) == 0) {
        return XbSymbolLib_D3DX8;
    }
    if (strncmp(library_name, Lib_DSOUND, 8) == 0) {
        return XbSymbolLib_DSOUND;
    }
    if (strncmp(library_name, Lib_XACTENG, 8) == 0) {
        return XbSymbolLib_XACTENG;
    }
    if (strncmp(library_name, Lib_XAPILIB, 8) == 0) {
        return XbSymbolLib_XAPILIB;
    }
    if (strncmp(library_name, Lib_XGRAPHC, 8) == 0) {
        return XbSymbolLib_XGRAPHC;
    }
    if (strncmp(library_name, Lib_XNET, 8) == 0) {
        return XbSymbolLib_XNET;
    }
    if (strncmp(library_name, Lib_XNETN, 8) == 0) {
        return XbSymbolLib_XNETN;
    }
    if (strncmp(library_name, Lib_XNETS, 8) == 0) {
        return XbSymbolLib_XNETS;
    }
    if (strncmp(library_name, Lib_XONLINE, 8) == 0) {
        return XbSymbolLib_XONLINE;
    }
    if (strncmp(library_name, Lib_XONLINES, 8) == 0) {
        return XbSymbolLib_XONLINES;
    }
    return 0;
}

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
        // (XbSymbolLocateFunction already checked this, but this check
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
uint32_t XbSymbolLocateFunction(OOVPA *Oovpa, uint32_t lower, uint32_t upper) {

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
                    XRefDataBase[XRef] = XRefAddr;
                }*/
                XRefDataBase[XRef] = XRefAddr;
            }

            return cur;
        }

    // found nothing
    return 0;
}

void XbSymbolRegisterSymbol(OOVPATable* OovpaTable, const char * LibraryName, uint32_t address, xb_symbol_register_t register_func) {
    if (OovpaTable != (void*)0) {

        OOVPA* Oovpa = OovpaTable->Oovpa;

        // do we need to save the found address?
        if (Oovpa->XRefSaveIndex != XRefNoSaveIndex) {
            // If XRef is not found, save it then register once.
            if (XRefDataBase[Oovpa->XRefSaveIndex] == XREF_ADDR_UNDETERMINED) {
                UnResolvedXRefs--;
                XRefDataBase[Oovpa->XRefSaveIndex] = address;
                register_func(LibraryName, OovpaTable->szFuncName, address, OovpaTable->Version);
            }
        } else {
            register_func(LibraryName, OovpaTable->szFuncName, address, OovpaTable->Version);
        }
    }
}

void XbSymbolScanOOVPA(OOVPATable *OovpaTable, unsigned int OovpaTableCount, const char* LibraryName, xbe_section_header *pSectionHeader, uint16_t buildVersion, xb_symbol_register_t register_func) {
    unsigned int lower = pSectionHeader->dwVirtualAddr;

    // Find the highest address contained within an executable segment
    unsigned int upper = pSectionHeader->dwVirtualAddr + pSectionHeader->dwVirtualSize;

    // traverse the full OOVPA table
    OOVPATable *pLoopEnd = &OovpaTable[OovpaTableCount];
    OOVPATable *pLoop = OovpaTable;
    OOVPATable *pLastKnownSymbol = (void*)0;
    unsigned int pLastKnownFunc = 0;
    const char *SymbolName = (void*)0;
    for (; pLoop < pLoopEnd; pLoop++) {

        if (SymbolName == (void*)0) {
            SymbolName = pLoop->szFuncName;
        } else if (strcmp(SymbolName, pLoop->szFuncName) != 0) {
            SymbolName = pLoop->szFuncName;
            if (pLastKnownSymbol != (void*)0) {
                // Now that we found the address, store it (regardless if we patch it or not)
                XbSymbolRegisterSymbol(pLastKnownSymbol, LibraryName, pLastKnownFunc, register_func);
                pLastKnownSymbol = (void*)0;
                pLastKnownFunc = 0;
            }
        }

        // Skip higher build version
        if (buildVersion < pLoop->Version)
            continue;

        // Search for each function's location using the OOVPA
        uint32_t pFunc = XbSymbolLocateFunction(pLoop->Oovpa, lower, upper);
        if (pFunc == 0)
            continue;

#if 0 // TODO: Find a way to support this.
        if (pFunc == pLastKnownFunc && pLastKnownSymbol == pLoop - 1) {
            if (g_SymbolAddresses[pLastKnownSymbol->szFuncName] == 0) {
                printf("HLE: Duplicate OOVPA signature found for %s, %d vs %d!\n", pLastKnownSymbol->szFuncName, pLastKnownSymbol->Version, pLoop->Version);
            }
        }
#endif

        pLastKnownFunc = pFunc;
        pLastKnownSymbol = pLoop;
    }
    if (pLastKnownSymbol != (void*)0) {
        XbSymbolRegisterSymbol(pLastKnownSymbol, LibraryName, pLastKnownFunc, register_func);
    }
}

bool XbSymbolScanSection(uint32_t xbe_base_address, uint32_t xbe_size, const char* section_name, uint32_t section_virtual_address, uint32_t section_size, uint16_t revision, xb_symbol_register_t register_func) {

    // Invalid argument
    if (section_name == NULL || xbe_size == 0 || section_size == 0 || register_func == 0) {
        return 0;
    }

    for (uint32_t d2 = 0; d2 < SymbolDBListCount; d2++) {

        if (g_library_flag == 0 || (SymbolDBList[d2].LibSec.library & g_library_flag) > 0) {

            const char* LibraryName = XbSymbolLibraryToString(SymbolDBList[d2].LibSec.library);

            //Initialize a matching specific section is currently pair with library in order to scan specific section only.
            //By doing this method will reduce false detection dramatically. If it had happened before.
            for (uint32_t d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                if (SymbolDBList[d2].LibSec.section[d3] != NULL && strcmp(section_name, SymbolDBList[d2].LibSec.section[d3]) == 0) {

                    // traverse the full OOVPA table
                    OOVPATable *pLoopEnd = &SymbolDBList[d2].OovpaTable[SymbolDBList[d2].OovpaTableCount];
                    OOVPATable *pLoop = SymbolDBList[d2].OovpaTable;
                    OOVPATable *pLastKnownSymbol = (void*)0;
                    uint32_t pLastKnownFunc = 0;
                    const char *SymbolName = (void*)0;
                    for (; pLoop < pLoopEnd; pLoop++) {

                        if (SymbolName == (void*)0) {
                            SymbolName = pLoop->szFuncName;
                        } else if (strcmp(SymbolName, pLoop->szFuncName) != 0) {
                            XbSymbolRegisterSymbol(pLastKnownSymbol, LibraryName, pLastKnownFunc, register_func);

                            SymbolName = pLoop->szFuncName;
                            pLastKnownSymbol = (void*)0;
                            pLastKnownFunc = 0;
                        }

                        //* NOTE: For time being, let's preserve this code in case we need to re-enable it with updated argument.
                        // Skip higher build version
                        if (revision < pLoop->Version) {
                            continue;
                        }
                        //*/

                        // Search for each function's location using the OOVPA
                        uint32_t pFunc = XbSymbolLocateFunction(pLoop->Oovpa, section_virtual_address, section_virtual_address+section_size);
                        if (pFunc == 0)
                            continue;

                        pLastKnownFunc = pFunc;
                        pLastKnownSymbol = pLoop;
                    }
                    XbSymbolRegisterSymbol(pLastKnownSymbol, LibraryName, pLastKnownFunc, register_func);
                    break;
                }
            }
        }
    }
    return 1;
}

bool XbSymbolScan(void* xbeData, xb_symbol_register_t register_func)
{
    if (xbeData == (void*)0 || register_func == 0) {
        return 0;
    }

    xbe_header* pXbeHeader = xbeData;
    xbe_library_version* pLibraryVersion = pXbeHeader->pLibraryVersionsAddr;

    //
    // initialize Microsoft XDK scan
    //
    if (pLibraryVersion == NULL) {
        return 0;
    } else {

        UnResolvedXRefs = XREF_COUNT;

        unsigned int dwLibraryVersions = pXbeHeader->dwLibraryVersions;
        unsigned int LastUnResolvedXRefs = UnResolvedXRefs + 1;
        unsigned int OrigUnResolvedXRefs = UnResolvedXRefs;

        bXRefFirstPass = true; // Set to false for search speed optimization

                               // Mark all Xrefs initially as undetermined
        memset((void*)XRefDataBase, XREF_ADDR_UNDETERMINED, sizeof(XRefDataBase));

        // Request a few fundamental XRefs to be derived instead of checked
        XRefDataBase[XREF_D3DDEVICE] = XREF_ADDR_DERIVE;                            //In use
        XRefDataBase[XREF_D3DRS_CULLMODE] = XREF_ADDR_DERIVE;                       //In use
        XRefDataBase[XREF_D3DRS_MULTISAMPLERENDERTARGETMODE] = XREF_ADDR_DERIVE;    //In use
        XRefDataBase[XREF_D3DRS_ROPZCMPALWAYSREAD] = XREF_ADDR_DERIVE;              //In use
        XRefDataBase[XREF_D3DRS_ROPZREAD] = XREF_ADDR_DERIVE;                       //In use
        XRefDataBase[XREF_D3DRS_DONOTCULLUNCOMPRESSED] = XREF_ADDR_DERIVE;          //In use
        XRefDataBase[XREF_D3DRS_STENCILCULLENABLE] = XREF_ADDR_DERIVE;              //In use
        XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] = XREF_ADDR_DERIVE;                 //In use
        XRefDataBase[XREF_G_STREAM] = XREF_ADDR_DERIVE;                             //In use
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_PIXELSHADER] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_TEXTURES] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_PALETTES] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_RENDERTARGET] = XREF_ADDR_DERIVE;
        XRefDataBase[XREF_OFFSET_D3DDEVICE_M_DEPTHSTENCIL] = XREF_ADDR_DERIVE;

        for (int p = 0; UnResolvedXRefs < LastUnResolvedXRefs; p++) {

            LastUnResolvedXRefs = UnResolvedXRefs;

            bool bDSoundLibSection = false;
            unsigned short preserveVersion = 0;

            for (unsigned int v = 0; v<dwLibraryVersions; v++) {
                unsigned short BuildVersion = pLibraryVersion[v].wBuildVersion;
                unsigned short QFEVersion = pLibraryVersion[v].wFlags.QFEVersion;

                if (preserveVersion < BuildVersion) {
                    preserveVersion = BuildVersion;
                }

                const char* LibraryStr = pLibraryVersion[v].szName;
                uint32_t LibraryFlag = XbSymbolLibrayToFlag(LibraryStr);


                xbe_section_header* pSectionHeaders;
                xbe_section_header* pSectionScan;
                const char* SectionName;

            reProcessScan:

                pSectionHeaders = pXbeHeader->pSectionHeadersAddr;
                pSectionScan = NULL;

                if (LibraryFlag == XbSymbolLib_D3D8LTCG || LibraryFlag == XbSymbolLib_D3D8) {

                    // Functions in this library were updated by June 2003 XDK (5558) with Integrated Hotfixes,
                    // However August 2003 XDK (5659) still uses the old function.
                    // Please use updated 5788 instead.
                    if (BuildVersion >= 5558 && BuildVersion <= 5659 && QFEVersion > 1) {
#if 0  // TODO: Move this to Cxbx or some other way.
                        EmuWarning("D3D8 version 1.0.%d.%d Title Detected: This game uses an alias version 1.0.5788", BuildVersion, QFEVersion);
#endif
                        BuildVersion = 5788;
                    }
                }
                if (LibraryFlag == XbSymbolLib_DSOUND) {
                    bDSoundLibSection = true;
                }

                if (bXRefFirstPass) {
                    if (LibraryFlag == XbSymbolLib_D3D8) {

                        // TODO: Why do we need this? Also, can we just scan library versions for this only?
                        // Save D3D8 build version
                        //g_BuildVersion = BuildVersion;

                        unsigned int lower = pXbeHeader->dwBaseAddr;
                        unsigned int upper = pXbeHeader->dwBaseAddr + pXbeHeader->dwSizeofImage;
                        unsigned int pFunc = 0;

                        if (BuildVersion >= 3911 && BuildVersion < 4034) {
                            pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetRenderState_CullMode_3911, lower, upper);
                        } else {
                            pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetRenderState_CullMode_4034, lower, upper);
                        }

                        // locate D3DDeferredRenderState
                        if (pFunc != 0) {
                            // offset for stencil cull enable render state in the deferred render state buffer
                            unsigned int DerivedAddr_D3DRS_CULLMODE = 0;
                            int Decrement = 0; // TODO : Rename into something understandable
                            int Increment = 0; // TODO : Rename into something understandable
                            int patchOffset = 0; // TODO : Rename into something understandable

                                                 // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
                                                 // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
                            {
                                if (BuildVersion < 4034) {
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + 0x25);
                                    Decrement = 0x1FC;  // TODO: Clean up (?)
                                    Increment = 82 * 4;
                                    patchOffset = 140 * 4; // Verified 3925 and 3948

                                                           //Decrement = 0x19F;  // TODO: Clean up (?)
                                                           //Increment = 72 * 4;
                                                           //patchOffset = 142*4; // TODO: Verify
                                } else if (BuildVersion <= 4361) {
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + 0x2B);
                                    Decrement = 0x200;
                                    Increment = 82 * 4;
                                    patchOffset = 142 * 4;
                                } else if (BuildVersion < 4627) {
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + 0x2B);
                                    Decrement = 0x204;
                                    Increment = 83 * 4;
                                    patchOffset = 143 * 4;
                                } else { // 4627-5933
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + 0x2B);
                                    Decrement = 0x24C;
                                    Increment = 92 * 4;
                                    patchOffset = 162 * 4;
                                }

                                // Temporary verification - is XREF_D3DDEVICE derived correctly?
                                unsigned int DerivedAddr_D3DDevice = *(unsigned int*)(pFunc + 0x03);
                                if (XRefDataBase[XREF_D3DDEVICE] != DerivedAddr_D3DDevice) {
#if 0  // TODO: How can we enforce it for callback?
                                    if (XRefDataBase[XREF_D3DDEVICE] != XREF_ADDR_DERIVE)
                                        CxbxPopupMessage("Second derived XREF_D3DDEVICE differs from first!");
#endif

                                    XRefDataBase[XREF_D3DDEVICE] = DerivedAddr_D3DDevice;
                                }
                                register_func(LibraryStr, "D3DDEVICE", DerivedAddr_D3DDevice, 0);

                                // Temporary verification - is XREF_D3D_RenderState_CullMode derived correctly?
                                if (XRefDataBase[XREF_D3DRS_CULLMODE] != DerivedAddr_D3DRS_CULLMODE) {
#if 0  // TODO: How can we enforce it for callback?
                                    if (XRefDataBase[XREF_D3DRS_CULLMODE] != XREF_ADDR_DERIVE)
                                        CxbxPopupMessage("Second derived XREF_D3D_RenderState_CullMode differs from first!");
#endif

                                    XRefDataBase[XREF_D3DRS_CULLMODE] = DerivedAddr_D3DRS_CULLMODE;
                                }
                            }

                            // Derive address of EmuD3DDeferredRenderState from D3DRS_CULLMODE
                            unsigned int EmuD3DDeferredRenderState = DerivedAddr_D3DRS_CULLMODE - Decrement + Increment;
                            patchOffset -= Increment;

                            // Derive address of a few other deferred render state slots (to help xref-based function location)
                            XRefDataBase[XREF_D3DRS_MULTISAMPLERENDERTARGETMODE] = DerivedAddr_D3DRS_CULLMODE + 8 * 4;
                            XRefDataBase[XREF_D3DRS_STENCILCULLENABLE] = EmuD3DDeferredRenderState + patchOffset + 0 * 4;
                            XRefDataBase[XREF_D3DRS_ROPZCMPALWAYSREAD] = EmuD3DDeferredRenderState + patchOffset + 1 * 4;
                            XRefDataBase[XREF_D3DRS_ROPZREAD] = EmuD3DDeferredRenderState + patchOffset + 2 * 4;
                            XRefDataBase[XREF_D3DRS_DONOTCULLUNCOMPRESSED] = EmuD3DDeferredRenderState + patchOffset + 3 * 4;

#if 0 // TODO: Need to apply in Cxbx, not in XbSymbolDatabase.
                            for (int v = 0; v<44; v++) {
                                XTL::EmuD3DDeferredRenderState[v] = XTL::X_D3DRS_UNK;
                            }
#endif
                            register_func(LibraryStr, "D3DDeferredRenderState", EmuD3DDeferredRenderState, 0);
                        }

                        // locate D3DDeferredTextureState
                        {
                            pFunc = 0;

                            if (BuildVersion >= 3911 && BuildVersion < 4034)
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_3911, lower, upper);
                            else if (BuildVersion >= 4034 && BuildVersion < 4242)
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_4034, lower, upper);
                            else if (BuildVersion >= 4242 && BuildVersion < 4627)
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_4242, lower, upper);
                            else if (BuildVersion >= 4627)
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_4627, lower, upper);

                            if (pFunc != 0) {
                                unsigned int DerivedAddr_D3DTSS_TEXCOORDINDEX = 0;
                                int Decrement = 0x70; // TODO : Rename into something understandable

                                                      // TODO : Remove this when XREF_D3D_TextureState_TexCoordIndex derivation is deemed stable
                                {
                                    if (BuildVersion >= 3911 && BuildVersion < 4034) // 0x18F180
                                        DerivedAddr_D3DTSS_TEXCOORDINDEX = *(unsigned int*)(pFunc + 0x11);
                                    else if (BuildVersion >= 4034 && BuildVersion < 4242)
                                        DerivedAddr_D3DTSS_TEXCOORDINDEX = *(unsigned int*)(pFunc + 0x18);
                                    else
                                        DerivedAddr_D3DTSS_TEXCOORDINDEX = *(unsigned int*)(pFunc + 0x19);

                                    // Temporary verification - is XREF_D3D_TextureState_TexCoordIndex derived correctly?
                                    if (XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] != DerivedAddr_D3DTSS_TEXCOORDINDEX) {
#if 0  // TODO: How can we enforce it for callback?
                                        if (XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] != XREF_ADDR_DERIVE) {
                                            CxbxPopupMessage("Second derived XREF_D3D_TextureState_TexCoordIndex differs from first!");
                                        }
#endif

                                        XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] = DerivedAddr_D3DTSS_TEXCOORDINDEX;
                                    }
                                }

                                unsigned int EmuD3DDeferredTextureState = DerivedAddr_D3DTSS_TEXCOORDINDEX - Decrement;

#if 0 // TODO: Need to apply in Cxbx, not in XbSymbolDatabase.
                                for (int s = 0; s < 4; s++) {
                                    for (int v = 0; v < 32; v++) {
                                        XTL::EmuD3DDeferredTextureState[v + s * 32] = X_D3DTSS_UNK;
                                    }
                                }
#endif

                                register_func(LibraryStr, "D3DDeferredTextureState", EmuD3DDeferredTextureState, 0);
                            }
                        }

                        // Locate Xbox symbol "g_Stream" and store it's address
                        {
                            unsigned int pFunc = 0;
                            int OOVPA_version;
                            int iCodeOffsetFor_g_Stream = 0x22; // verified for 4361, 4627, 5344, 5558, 5659, 5788, 5849, 5933

                            if (BuildVersion >= 4034) {
                                OOVPA_version = 4034;
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetStreamSource_4034, lower, upper);
                            } else {
                                OOVPA_version = 3911;
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetStreamSource_3911, lower, upper);
                                iCodeOffsetFor_g_Stream = 0x23; // verified for 3911
                            }

                            if (pFunc != 0) {

                                // Read address of Xbox_g_Stream from D3DDevice_SetStreamSource
                                unsigned int Derived_g_Stream = *((unsigned int*)(pFunc + iCodeOffsetFor_g_Stream));

                                // Temporary verification - is XREF_G_STREAM derived correctly?
                                // TODO : Remove this when XREF_G_STREAM derivation is deemed stable
#if 0  // TODO: What to do with this?
                                VerifySymbolAddressAgainstXRef("g_Stream", Derived_g_Stream, XREF_G_STREAM);
#endif

                                // Now that both Derived XREF and OOVPA-based function-contents match,
                                // correct base-address (because "g_Stream" is actually "g_Stream"+8") :
                                Derived_g_Stream -= 8;
                                register_func(LibraryStr, "g_Stream", Derived_g_Stream, 0);
                            }
                        }
                    } else if (LibraryFlag == XbSymbolLib_D3D8LTCG) {
                        int pXRefOffset = 0; // TODO : Rename into something understandable

                        // TODO: Why do we need this? Also, can we just scan library versions for this only?
                        // Save D3D8 build version
                        //g_BuildVersion = BuildVersion;

                        unsigned int lower = pXbeHeader->dwBaseAddr;
                        unsigned int upper = pXbeHeader->dwBaseAddr + pXbeHeader->dwSizeofImage;
                        unsigned int pFunc = 0;

                        {
                            pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetRenderState_CullMode_1045, lower, upper);
                            pXRefOffset = 0x2D; // verified for 3925
                            if (pFunc == 0) {
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetRenderState_CullMode_1049, lower, upper);
                                pXRefOffset = 0x31; // verified for 4039
                            }
                            if (pFunc == 0) {
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetRenderState_CullMode_1052, lower, upper);
                                pXRefOffset = 0x34;
                            }
                            if (pFunc == 0) {
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetRenderState_CullMode_1053, lower, upper);
                                pXRefOffset = 0x35;
                            }
                        }
                        // locate D3DDeferredRenderState
                        if (pFunc != 0) {
                            // offset for stencil cull enable render state in the deferred render state buffer
                            unsigned int DerivedAddr_D3DRS_CULLMODE = 0;
                            int Decrement = 0; // TODO : Rename into something understandable
                            int Increment = 0; // TODO : Rename into something understandable
                            int patchOffset = 0; // TODO : Rename into something understandable

                                                 // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
                                                 // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
                            {
                                if (BuildVersion < 4034) {
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + pXRefOffset);
                                    Decrement = 0x1FC;  // TODO: Clean up (?)
                                    Increment = 82 * 4;
                                    patchOffset = 140 * 4; // Verified 3925 and 3948

                                                           //Decrement = 0x19F;  // TODO: Clean up (?)
                                                           //Increment = 72 * 4;
                                                           //patchOffset = 142*4; // TODO: Verify
                                } else if (BuildVersion <= 4361) {
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + pXRefOffset);
                                    Decrement = 0x200;
                                    Increment = 82 * 4;
                                    patchOffset = 142 * 4;
                                } else if (BuildVersion < 4627) {
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + pXRefOffset);
                                    Decrement = 0x204;
                                    Increment = 83 * 4;
                                    patchOffset = 143 * 4;
                                } else { // 4627-5933
                                         // NOTE: Burnout 3 is (pFunc + 0x34), Black is (pFunc + 0x35)
                                    DerivedAddr_D3DRS_CULLMODE = *(unsigned int*)(pFunc + pXRefOffset);
                                    Decrement = 0x24C;
                                    Increment = 92 * 4;
                                    patchOffset = 162 * 4;
                                }

                                // Temporary verification - is XREF_D3DDEVICE derived correctly?
                                unsigned int DerivedAddr_D3DDevice = *(unsigned int*)(pFunc + 0x03);
                                if (XRefDataBase[XREF_D3DDEVICE] != DerivedAddr_D3DDevice) {
#if 0  // TODO: How can we enforce it for callback?
                                    if (XRefDataBase[XREF_D3DDEVICE] != XREF_ADDR_DERIVE)
                                        EmuWarning("Second derived XREF_D3DDEVICE differs from first!");
#endif
                                    XRefDataBase[XREF_D3DDEVICE] = DerivedAddr_D3DDevice;
                                }
                                register_func(LibraryStr, "D3DDEVICE", DerivedAddr_D3DDevice, 0);

                                // Temporary verification - is XREF_D3DRS_CULLMODE derived correctly?
                                if (XRefDataBase[XREF_D3DRS_CULLMODE] != DerivedAddr_D3DRS_CULLMODE) {
#if 0  // TODO: How can we enforce it for callback?
                                    if (XRefDataBase[XREF_D3DRS_CULLMODE] != XREF_ADDR_DERIVE)
                                        CxbxPopupMessage("Second derived XREF_D3DRS_CULLMODE differs from first!");
#endif

                                    XRefDataBase[XREF_D3DRS_CULLMODE] = DerivedAddr_D3DRS_CULLMODE;
                                }
                            }

                            // Derive address of EmuD3DDeferredRenderState from D3DRS_CULLMODE
                            unsigned int EmuD3DDeferredRenderState = DerivedAddr_D3DRS_CULLMODE - Decrement + Increment;
                            patchOffset -= Increment;

                            // Derive address of a few other deferred render state slots (to help xref-based function location)
                            // XRefDataBase[XREF_D3DRS_PSTEXTUREMODES]          = DerivedAddr_D3DRS_CULLMODE - 11*4;
                            // XRefDataBase[XREF_D3DRS_VERTEXBLEND]             = DerivedAddr_D3DRS_CULLMODE - 10*4;
                            // XRefDataBase[XREF_D3DRS_FOGCOLOR]             = DerivedAddr_D3DRS_CULLMODE - 9*4;
                            XRefDataBase[XREF_D3DRS_FILLMODE] = DerivedAddr_D3DRS_CULLMODE - 8 * 4;
                            XRefDataBase[XREF_D3DRS_BACKFILLMODE] = DerivedAddr_D3DRS_CULLMODE - 7 * 4;
                            XRefDataBase[XREF_D3DRS_TWOSIDEDLIGHTING] = DerivedAddr_D3DRS_CULLMODE - 6 * 4;
                            // XRefDataBase[XREF_D3DRS_NORMALIZENORMALS]        = DerivedAddr_D3DRS_CULLMODE - 5*4;
                            // XRefDataBase[XREF_D3DRS_ZENABLE]             = DerivedAddr_D3DRS_CULLMODE - 4*4;
                            // XRefDataBase[XREF_D3DRS_STENCILENABLE]           = DerivedAddr_D3DRS_CULLMODE - 3*4;
                            // XRefDataBase[XREF_D3DRS_STENCILFAIL]             = DerivedAddr_D3DRS_CULLMODE - 2*4;
                            // XRefDataBase[XREF_D3DRS_FRONTFACE]             = DerivedAddr_D3DRS_CULLMODE - 1*4;
                            // XRefDataBase[XREF_D3DRS_CULLMODE]          = DerivedAddr_D3DRS_CULLMODE - 0*4;
                            // XRefDataBase[XREF_D3DRS_TEXTUREFACTOR]         = DerivedAddr_D3DRS_CULLMODE + 1*4;
                            XRefDataBase[XREF_D3DRS_ZBIAS] = DerivedAddr_D3DRS_CULLMODE + 2 * 4;
                            XRefDataBase[XREF_D3DRS_LOGICOP] = DerivedAddr_D3DRS_CULLMODE + 3 * 4;
                            // XRefDataBase[XREF_D3DRS_EDGEANTIALIAS]         = DerivedAddr_D3DRS_CULLMODE + 4*4;
                            XRefDataBase[XREF_D3DRS_MULTISAMPLEANTIALIAS] = DerivedAddr_D3DRS_CULLMODE + 5 * 4;
                            XRefDataBase[XREF_D3DRS_MULTISAMPLEMASK] = DerivedAddr_D3DRS_CULLMODE + 6 * 4;
                            XRefDataBase[XREF_D3DRS_MULTISAMPLEMODE] = DerivedAddr_D3DRS_CULLMODE + 7 * 4;
                            XRefDataBase[XREF_D3DRS_MULTISAMPLERENDERTARGETMODE] = DerivedAddr_D3DRS_CULLMODE + 8 * 4;
                            // XRefDataBase[XREF_D3DRS_SHADOWFUNC]            = DerivedAddr_D3DRS_CULLMODE + 9*4;
                            // XRefDataBase[XREF_D3DRS_LINEWIDTH]             = DerivedAddr_D3DRS_CULLMODE + 10*4;

                            if (BuildVersion >= 4627 && BuildVersion <= 5933) // Add XDK 4627
                                XRefDataBase[XREF_D3DRS_SAMPLEALPHA] = DerivedAddr_D3DRS_CULLMODE + 11 * 4;

                            XRefDataBase[XREF_D3DRS_DXT1NOISEENABLE] = EmuD3DDeferredRenderState + patchOffset - 3 * 4;
                            XRefDataBase[XREF_D3DRS_YUVENABLE] = EmuD3DDeferredRenderState + patchOffset - 2 * 4;
                            XRefDataBase[XREF_D3DRS_OCCLUSIONCULLENABLE] = EmuD3DDeferredRenderState + patchOffset - 1 * 4;
                            XRefDataBase[XREF_D3DRS_STENCILCULLENABLE] = EmuD3DDeferredRenderState + patchOffset + 0 * 4;
                            XRefDataBase[XREF_D3DRS_ROPZCMPALWAYSREAD] = EmuD3DDeferredRenderState + patchOffset + 1 * 4;
                            XRefDataBase[XREF_D3DRS_ROPZREAD] = EmuD3DDeferredRenderState + patchOffset + 2 * 4;
                            XRefDataBase[XREF_D3DRS_DONOTCULLUNCOMPRESSED] = EmuD3DDeferredRenderState + patchOffset + 3 * 4;

#if 0 // TODO: Need to apply in Cxbx, not in XbSymbolDatabase.
                            for (int v = 0; v<44; v++) {
                                XTL::EmuD3DDeferredRenderState[v] = XTL::X_D3DRS_UNK;
                            }
#endif

                            register_func(LibraryStr, "D3DDeferredRenderState", EmuD3DDeferredRenderState, 0);
                        }

                        // locate D3DDeferredTextureState
                        {
                            pFunc = 0;

                            { // verified for 3925
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_0_2039, lower, upper);
                                pXRefOffset = 0x08;
                                if (pFunc == 0) { // verified for 4039
                                    pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_4_2040, lower, upper);
                                    pXRefOffset = 0x14;
                                }
                                if (pFunc == 0) { // verified for 4432
                                    pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_1944, lower, upper);
                                    pXRefOffset = 0x19;
                                }
                                if (pFunc == 0) { // verified for 4531
                                    pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_4_2045, lower, upper);
                                    pXRefOffset = 0x14;
                                }
                                if (pFunc == 0) { // verified for 4627 and higher
                                    pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_4_2058, lower, upper);
                                    pXRefOffset = 0x14;
                                }
                                if (pFunc == 0) { // verified for 4627 and higher
                                    pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetTextureState_TexCoordIndex_1958, lower, upper);
                                    pXRefOffset = 0x19;
                                }
                            }

                            if (pFunc != 0) {
                                unsigned int DerivedAddr_D3DTSS_TEXCOORDINDEX = 0;
                                int Decrement = 0x70; // TODO : Rename into something understandable

                                                      // TODO : Remove this when XREF_D3D_TextureState_TexCoordIndex derivation is deemed stable
                                {
                                    DerivedAddr_D3DTSS_TEXCOORDINDEX = *(unsigned int*)(pFunc + pXRefOffset);

                                    // Temporary verification - is XREF_D3DTSS_TEXCOORDINDEX derived correctly?
                                    if (XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] != DerivedAddr_D3DTSS_TEXCOORDINDEX) {
#if 0  // TODO: How can we enforce it for callback?
                                        if (XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] != XREF_ADDR_DERIVE)
                                            CxbxPopupMessage("Second derived XREF_D3DTSS_TEXCOORDINDEX differs from first!");
#endif

                                        //	XRefDataBase[XREF_D3DTSS_BUMPENV] = DerivedAddr_D3DTSS_TEXCOORDINDEX - 28*4;
                                        XRefDataBase[XREF_D3DTSS_TEXCOORDINDEX] = DerivedAddr_D3DTSS_TEXCOORDINDEX;
                                        //	XRefDataBase[XREF_D3DTSS_BORDERCOLOR] = DerivedAddr_D3DTSS_TEXCOORDINDEX + 1*4;
                                        //	XRefDataBase[XREF_D3DTSS_COLORKEYCOLOR] = DerivedAddr_D3DTSS_TEXCOORDINDEX + 2*4;
                                    }
                                }

                                unsigned int EmuD3DDeferredTextureState = DerivedAddr_D3DTSS_TEXCOORDINDEX - Decrement;

#if 0 // TODO: Need to apply in Cxbx, not in XbSymbolDatabase.
                                for (int s = 0; s<4; s++) {
                                    for (int v = 0; v<32; v++) {
                                        XTL::EmuD3DDeferredTextureState[v + s * 32] = X_D3DTSS_UNK;
                                    }
                                }
#endif
                                register_func(LibraryStr, "D3DDeferredTextureState", EmuD3DDeferredTextureState, 0);
                            }
                        }

                        // Locate Xbox symbol "g_Stream" and store it's address
                        {
                            unsigned int pFunc = 0;
                            int OOVPA_version;
                            int iCodeOffsetFor_g_Stream = 0x22; // verified for 4432, 4627, 5344, 5558, 5849

                            if (BuildVersion > 4039) {
                                OOVPA_version = 4034; // TODO Verify
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetStreamSource_1044, lower, upper);
                            }
                            if (pFunc == 0) { // LTCG specific
                                OOVPA_version = 4034; // TODO Verify
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetStreamSource_4_2058, lower, upper);
                                iCodeOffsetFor_g_Stream = 0x1E;
                            }
                            if (pFunc == 0) { // verified for 4039
                                OOVPA_version = 4034;
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetStreamSource_1040, lower, upper);
                                iCodeOffsetFor_g_Stream = 0x23;
                            }
                            if (pFunc == 0) { // verified for 3925
                                OOVPA_version = 3911;
                                pFunc = XbSymbolLocateFunction((OOVPA*)&D3DDevice_SetStreamSource_1039, lower, upper);
                                iCodeOffsetFor_g_Stream = 0x47;
                            }

                            if (pFunc != 0) {

                                // Read address of Xbox_g_Stream from D3DDevice_SetStreamSource
                                unsigned int Derived_g_Stream = *((unsigned int*)(pFunc + iCodeOffsetFor_g_Stream));

                                // Temporary verification - is XREF_G_STREAM derived correctly?
                                // TODO : Remove this when XREF_G_STREAM derivation is deemed stable
#if 0  // TODO: How can we enforce it for callback?
                                VerifySymbolAddressAgainstXRef("g_Stream", Derived_g_Stream, XREF_G_STREAM);
#endif

                                // Now that both Derived XREF and OOVPA-based function-contents match,
                                // correct base-address (because "g_Stream" is actually "g_Stream"+8") :
                                Derived_g_Stream -= 8;
                                register_func(LibraryStr, "g_Stream", Derived_g_Stream, 0);
                            }
                        }
                    }
                }

                //Initialize library scan against HLE database we want to search for address of patches and xreferences.
                bool bPrintSkip = true;
                for (unsigned int d2 = 0; d2 < SymbolDBListCount; d2++) {
                    if (LibraryFlag == SymbolDBList[d2].LibSec.library) {
                        for (unsigned int v = 0; v < pXbeHeader->dwSections; v++) {
                            SectionName = pSectionHeaders[v].SectionNameAddr;

                            //Initialize a matching specific section is currently pair with library in order to scan specific section only.
                            //By doing this method will reduce false detection dramatically. If it had happened before.
                            for (unsigned int d3 = 0; d3 < PAIRSCANSEC_MAX; d3++) {
                                if (SymbolDBList[d2].LibSec.section[d3] != NULL && strncmp(SectionName, SymbolDBList[d2].LibSec.section[d3], 8) == 0) {
                                    pSectionScan = pSectionHeaders + v;

                                    bPrintSkip = false;

                                    XbSymbolScanOOVPA(SymbolDBList[d2].OovpaTable, SymbolDBList[d2].OovpaTableCount, LibraryStr, pSectionScan, BuildVersion, register_func);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }

                if (v == dwLibraryVersions - 1 && bDSoundLibSection == false) {
                    LibraryStr = Lib_DSOUND;
                    LibraryFlag = XbSymbolLib_DSOUND;
                    BuildVersion = preserveVersion;
                    goto reProcessScan;
                }
            }

            bXRefFirstPass = false;
        }
    }
    return 1;
}

// ******************************************************************
// * XbSymbolLibraryVersion
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

void HashSymbolData(unsigned int* Hash, SymbolDatabaseList* pData) {
    for (unsigned int i = 0; i < pData->OovpaTableCount; ++i) {
        HashOOVPATable(Hash, &pData->OovpaTable[i]);
    }
}

const unsigned int HashSymbolDataArray(SymbolDatabaseList* pDataArray, unsigned int Count) {
    unsigned int Hash = 0x811c9dc5;
    for (unsigned int i = 0; i < Count; ++i) {
        HashSymbolData(&Hash, pDataArray + i);
    }
    return Hash;
}

unsigned int XbSymbolLibraryVersion() {
    // Calculate this just once
    static unsigned int CalculatedHash = 0;
    if (CalculatedHash == 0) {
        CalculatedHash = HashSymbolDataArray(SymbolDBList, SymbolDBListCount);
    }
    return CalculatedHash;
}

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

static void manual_scan_section_dx8_register_xrefs(iXbSymbolContext* pContext,
                                                   const iXbSymbolLibrarySession* pLibrarySession,
                                                   memptr_t pFunc,
                                                   xbaddr DerivedAddr_D3DRS_CULLMODE,
                                                   uint32_t patchOffset,
                                                   uint32_t Increment,
                                                   uint32_t Decrement)
{
    if (pFunc == NULL) {
        return;
    }
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    // Temporary verification - is XREF_D3D_g_pDevice derived correctly?
    xbaddr DerivedAddr_D3DDevice = *(xbaddr*)(pFunc + 0x03);
    if (pContext->xref_database[XREF_D3D_g_pDevice] != DerivedAddr_D3DDevice) {

        if (pContext->xref_database[XREF_D3D_g_pDevice] != XREF_ADDR_DERIVE) {
            output_message(&pContext->output, XB_OUTPUT_MESSAGE_INFO, "Second derived XREF_D3D_g_pDevice differs from first!");
        }

        internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XREF_D3D_g_pDevice, DerivedAddr_D3DDevice);
    }
    pContext->register_func(pLibrary->name, pLibrary->flag, XREF_D3D_g_pDevice, "D3D_g_pDevice", DerivedAddr_D3DDevice, 0);

    // Temporary verification - is XREF_D3D_RenderState_CullMode derived correctly?
    if (pContext->xref_database[XREF_D3DRS_CULLMODE] != DerivedAddr_D3DRS_CULLMODE) {

        if (pContext->xref_database[XREF_D3DRS_CULLMODE] != XREF_ADDR_DERIVE) {
            output_message(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Second derived XREF_D3D_RenderState_CullMode differs from first!");
        }

        internal_SetXRefDatabase(pContext, pLibrarySession->iLibraryType, XREF_D3DRS_CULLMODE, DerivedAddr_D3DRS_CULLMODE);
    }
    // Register the offset of D3DRS_CULLMODE, this can be used to programatically locate other render-states in the calling program
    pContext->register_func(pLibrary->name, pLibrary->flag, XREF_D3DRS_CULLMODE, "D3DRS_CULLMODE", DerivedAddr_D3DRS_CULLMODE, 0);

    // Derive address of EmuD3DDeferredRenderState from D3DRS_CULLMODE
    xbaddr EmuD3DDeferredRenderState = DerivedAddr_D3DRS_CULLMODE - Decrement + Increment;
    patchOffset -= Increment;

    // Derive address of a few other deferred render state slots (to help xref-based function location)
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_PSTEXTUREMODES, DerivedAddr_D3DRS_CULLMODE - 11*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_VERTEXBLEND, DerivedAddr_D3DRS_CULLMODE - 10*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_FOGCOLOR, DerivedAddr_D3DRS_CULLMODE - 9*4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_FILLMODE, DerivedAddr_D3DRS_CULLMODE - 8 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_BACKFILLMODE, DerivedAddr_D3DRS_CULLMODE - 7 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_TWOSIDEDLIGHTING, DerivedAddr_D3DRS_CULLMODE - 6 * 4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_NORMALIZENORMALS, DerivedAddr_D3DRS_CULLMODE - 5*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_ZENABLE, DerivedAddr_D3DRS_CULLMODE - 4*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_STENCILENABLE, DerivedAddr_D3DRS_CULLMODE - 3*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_STENCILFAIL, DerivedAddr_D3DRS_CULLMODE - 2*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_FRONTFACE, DerivedAddr_D3DRS_CULLMODE - 1*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_CULLMODE, DerivedAddr_D3DRS_CULLMODE - 0*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_TEXTUREFACTOR, DerivedAddr_D3DRS_CULLMODE + 1*4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_ZBIAS, DerivedAddr_D3DRS_CULLMODE + 2 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_LOGICOP, DerivedAddr_D3DRS_CULLMODE + 3 * 4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_EDGEANTIALIAS, DerivedAddr_D3DRS_CULLMODE + 4*4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLEANTIALIAS, DerivedAddr_D3DRS_CULLMODE + 5 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLEMASK, DerivedAddr_D3DRS_CULLMODE + 6 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLEMODE, DerivedAddr_D3DRS_CULLMODE + 7 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_MULTISAMPLERENDERTARGETMODE, DerivedAddr_D3DRS_CULLMODE + 8 * 4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_SHADOWFUNC, DerivedAddr_D3DRS_CULLMODE + 9*4);
    // SetXRefDataBase(pContext, iLibraryType, XREF_D3DRS_LINEWIDTH, DerivedAddr_D3DRS_CULLMODE + 10*4);

    if (pLibrary->build_version >= 4627 && pLibrary->build_version <= 5933) { // Add XDK 4627
        internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_SAMPLEALPHA, DerivedAddr_D3DRS_CULLMODE + 11 * 4);
    }

    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_DXT1NOISEENABLE, EmuD3DDeferredRenderState + patchOffset - 3 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_YUVENABLE, EmuD3DDeferredRenderState + patchOffset - 2 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_OCCLUSIONCULLENABLE, EmuD3DDeferredRenderState + patchOffset - 1 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_STENCILCULLENABLE, EmuD3DDeferredRenderState + patchOffset + 0 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_ROPZCMPALWAYSREAD, EmuD3DDeferredRenderState + patchOffset + 1 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_ROPZREAD, EmuD3DDeferredRenderState + patchOffset + 2 * 4);
    internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DRS_DONOTCULLUNCOMPRESSED, EmuD3DDeferredRenderState + patchOffset + 3 * 4);

    pContext->register_func(pLibrary->name, pLibrary->flag, XREF_D3D_g_DeferredRenderState, "D3D_g_DeferredRenderState", EmuD3DDeferredRenderState, 0);
}

static void manual_scan_section_dx8_register_D3DTSS(iXbSymbolContext* pContext,
                                                    const iXbSymbolLibrarySession* pLibrarySession,
                                                    memptr_t pFunc,
                                                    uint32_t pXRefOffset)
{
    if (pFunc == NULL) {
        return;
    }
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    xbaddr DerivedAddr_D3DTSS_TEXCOORDINDEX = 0;
    int Decrement = 0x70; // TODO : Rename into something understandable

    // TODO : Remove this when XREF_D3D_TextureState_TexCoordIndex derivation is deemed stable
    {
        DerivedAddr_D3DTSS_TEXCOORDINDEX = *(xbaddr*)(pFunc + pXRefOffset);

        // Temporary verification - is XREF_D3DTSS_TEXCOORDINDEX derived correctly?
        if (pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] != DerivedAddr_D3DTSS_TEXCOORDINDEX) {

            if (pContext->xref_database[XREF_D3DTSS_TEXCOORDINDEX] != XREF_ADDR_DERIVE) {
                output_message(&pContext->output, XB_OUTPUT_MESSAGE_WARN, "Second derived XREF_D3DTSS_TEXCOORDINDEX differs from first!");
            }

            //SetXRefDataBase(pContext, iLibraryType, XREF_D3DTSS_BUMPENV, DerivedAddr_D3DTSS_TEXCOORDINDEX - 28*4);
            internal_SetXRefDatabase(pContext, iLibraryType, XREF_D3DTSS_TEXCOORDINDEX, DerivedAddr_D3DTSS_TEXCOORDINDEX);
            //SetXRefDataBase(pContext, iLibraryType, XREF_D3DTSS_BORDERCOLOR, DerivedAddr_D3DTSS_TEXCOORDINDEX + 1*4);
            //SetXRefDataBase(pContext, iLibraryType, XREF_D3DTSS_COLORKEYCOLOR, DerivedAddr_D3DTSS_TEXCOORDINDEX + 2*4);
        }
    }

    uint32_t EmuD3DDeferredTextureState = DerivedAddr_D3DTSS_TEXCOORDINDEX - Decrement;

    pContext->register_func(pLibrary->name, pLibrary->flag, XREF_D3D_g_DeferredTextureState, "D3D_g_DeferredTextureState", EmuD3DDeferredTextureState, 0);
}

static void manual_scan_section_dx8_register_stream(iXbSymbolContext* pContext,
                                                    const iXbSymbolLibrarySession* pLibrarySession,
                                                    memptr_t pFunc,
                                                    uint32_t iCodeOffsetFor_g_Stream)
{
    if (pFunc == NULL) {
        return;
    }
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;

    // Read address of Xbox_g_Stream from D3DDevice_SetStreamSource
    uint32_t Derived_g_Stream = *((uint32_t*)(pFunc + iCodeOffsetFor_g_Stream));

    // Temporary verification - is XREF_D3D_g_Stream derived correctly?
    // TODO : Remove this when XREF_D3D_g_Stream derivation is deemed stable
#if 0 // TODO: How can we enforce it for callback?
    VerifySymbolAddressAgainstXRef("g_Stream", Derived_g_Stream, XREF_D3D_g_Stream);
#endif

    // Now that both Derived XREF and OOVPA-based function-contents match,
    // correct base-address (because "g_Stream" is actually "g_Stream"+8") :
    Derived_g_Stream -= 8;
    pContext->register_func(pLibrary->name, pLibrary->flag, XREF_D3D_g_Stream, "D3D_g_Stream", Derived_g_Stream, 0);
}

static bool manual_scan_section_dx8(iXbSymbolContext* pContext,
                                    const iXbSymbolLibrarySession* pLibrarySession,
                                    SymbolDatabaseList* pLibraryDB,
                                    const XbSDBSection* pSection)
{
    // Generic usage
    memptr_t pFunc = 0;
    xbaddr xSymbolAddr = 0;
    // offset for stencil cull enable render state in the deferred render state buffer
    uint32_t DerivedAddr_D3DRS_CULLMODE = 0;
    int Decrement = 0;   // TODO : Rename into something understandable
    int Increment = 0;   // TODO : Rename into something understandable
    int patchOffset = 0; // TODO : Rename into something understandable
    int OOVPA_version;
    int iCodeOffsetFor_g_Stream;
    int pXRefOffset = 0; // TODO : Rename into something understandable
    uintptr_t virt_start_relative = (uintptr_t)pSection->buffer_lower - pSection->xb_virt_addr;
    const XbSDBLibrary* pLibrary = pLibrarySession->pLibrary;
    const eLibraryType iLibraryType = pLibrarySession->iLibraryType;

    OOVPARevision* pOOVPARevision = NULL;

    if (pLibrary->flag == XbSymbolLib_D3D8) {

        // locate D3DDevice_SetRenderState_CullMode first
        if (pLibrary->build_version < 3911) {
            // Not supported, currently ignored.
        }
        else {
            pFunc = internal_LocateSymbolFunction(pContext,
                                                  pLibrarySession,
                                                  pLibraryDB,
                                                  "D3DDevice_SetRenderState_CullMode",
                                                  pSection,
                                                  true,
                                                  NULL,
                                                  NULL);
        }

        // then locate D3DDeferredRenderState
        if (pFunc != 0) {
            // NOTE: Is a requirement to align properly.
            pFunc += virt_start_relative;

            // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
            // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
            if (pLibrary->build_version < 3911) {
                // Not supported, currently ignored.
            }
            else if (pLibrary->build_version < 4034) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x25);
                Decrement = 0x1FC; // TODO: Clean up (?)
                Increment = 82 * 4;
                patchOffset = 140 * 4; // Verified 3925 and 3948

                //Decrement = 0x19F; // TODO: Clean up (?)
                //Increment = 72 * 4;
                //patchOffset = 142*4; // TODO: Verify
            }
            else if (pLibrary->build_version <= 4361) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x200;
                Increment = 82 * 4;
                patchOffset = 142 * 4;
            }
            else if (pLibrary->build_version < 4627) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x204;
                Increment = 83 * 4;
                patchOffset = 143 * 4;
            }
            else { // 4627-5933
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + 0x2B);
                Decrement = 0x24C;
                Increment = 92 * 4;
                patchOffset = 162 * 4;
            }
        }
    }
    else { // D3D8LTCG
        // locate D3DDevice_SetRenderState_CullMode first
        pFunc = internal_LocateSymbolFunction(pContext,
                                              pLibrarySession,
                                              pLibraryDB,
                                              "D3DDevice_SetRenderState_CullMode",
                                              pSection,
                                              true,
                                              NULL,
                                              &pOOVPARevision);

        if (pFunc != 0) {

            // D3DDevice_SetRenderState_CullMode assign pXRefOffset for D3DDeferredRenderState
            switch (pOOVPARevision->Version) {
                case 1045:
                default:
                    pXRefOffset = 0x2D; // verified for 3925
                    break;
                case 1049:
                    pXRefOffset = 0x31; // verified for 4039
                    break;
                case 1052:
                    pXRefOffset = 0x34;
                    break;
                case 1053:
                    pXRefOffset = 0x35;
                    break;
            }

            // then locate D3DDeferredRenderState

            // NOTE: Is a requirement to align properly.
            pFunc += virt_start_relative;

            // Read address of D3DRS_CULLMODE from D3DDevice_SetRenderState_CullMode
            // TODO : Simplify this when XREF_D3D_RenderState_CullMode derivation is deemed stable
            if (pLibrary->build_version < 3911) {
                // Not supported, currently ignored.
            }
            else if (pLibrary->build_version < 4034) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x1FC; // TODO: Clean up (?)
                Increment = 82 * 4;
                patchOffset = 140 * 4; // Verified 3925 and 3948

                //Decrement = 0x19F; // TODO: Clean up (?)
                //Increment = 72 * 4;
                //patchOffset = 142*4; // TODO: Verify
            }
            else if (pLibrary->build_version <= 4361) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x200;
                Increment = 82 * 4;
                patchOffset = 142 * 4;
            }
            else if (pLibrary->build_version < 4627) {
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x204;
                Increment = 83 * 4;
                patchOffset = 143 * 4;
            }
            else { // 4627-5933
                // NOTE: Burnout 3 is (pFunc + 0x34), Black is (pFunc + 0x35)
                DerivedAddr_D3DRS_CULLMODE = *(uint32_t*)(pFunc + pXRefOffset);
                Decrement = 0x24C;
                Increment = 92 * 4;
                patchOffset = 162 * 4;
            }
        }
    }
    manual_scan_section_dx8_register_xrefs(pContext, pLibrarySession, pFunc, DerivedAddr_D3DRS_CULLMODE, patchOffset, Increment, Decrement);

    // then locate D3DDeferredTextureState
    if (pLibrary->flag == XbSymbolLib_D3D8) {

        if (pLibrary->build_version < 3911) {
            // Not supported, currently ignored.
            pFunc = 0;
        }
        else {
            pFunc = internal_LocateSymbolFunction(pContext,
                                                  pLibrarySession,
                                                  pLibraryDB,
                                                  "D3DDevice_SetTextureState_TexCoordIndex",
                                                  pSection,
                                                  true,
                                                  NULL,
                                                  NULL);

            // TODO: Can we integrate below into XRef?
            if (pLibrary->build_version < 4034) {
                pXRefOffset = 0x11;
            }
            else if (pLibrary->build_version < 4242) {
                pXRefOffset = 0x18;
            }
            else {
                pXRefOffset = 0x19;
            }
        }
    }
    else { // D3D8LTCG

        /*
        // TODO: Need some reform work for this portion. Since there are mixture of suffix involved.
        // Current listing are:
        // - D3DDevice_SetTextureState_TexCoordIndex   (1944, 1958)
        // - D3DDevice_SetTextureState_TexCoordIndex_0 (2039, 2058)
        // - D3DDevice_SetTextureState_TexCoordIndex_4 (2040, 2045, 2058, 2052)
        pFunc = internal_LocateSymbolFunction(pContext,
                                              pLibrarySession,
                                              pLibraryDB,
                                              "",
                                              pSection,
                                              false,
                                              pOOVPARevision);
        //*/

        // verified for 3925
        pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_0", 2039,
                                   &D3DDevice_SetTextureState_TexCoordIndex_0_2039, pSection);
        pXRefOffset = 0x08;

        if (pFunc == 0) { // verified for 4039
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2040,
                                       &D3DDevice_SetTextureState_TexCoordIndex_4_2040, pSection);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4432
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 1944,
                                       &D3DDevice_SetTextureState_TexCoordIndex_1944, pSection);
            pXRefOffset = 0x19;
        }

        if (pFunc == 0) { // verified for 4531
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2045,
                                       &D3DDevice_SetTextureState_TexCoordIndex_4_2045, pSection);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4627 and higher
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2058,
                                       &D3DDevice_SetTextureState_TexCoordIndex_4_2058, pSection);
            pXRefOffset = 0x14;
        }

        if (pFunc == 0) { // verified for 4627 and higher
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex", 1958,
                                       &D3DDevice_SetTextureState_TexCoordIndex_1958, pSection);
            pXRefOffset = 0x19;
        }

        if (pFunc == 0) { // verified for World Series Baseball 2K3
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_4", 2052,
                                       &D3DDevice_SetTextureState_TexCoordIndex_4_2052, pSection);
            pXRefOffset = 0x15;
        }

        if (pFunc == 0) { // verified for Ski Racing 2006
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetTextureState_TexCoordIndex_0", 2058,
                                       &D3DDevice_SetTextureState_TexCoordIndex_0_2058, pSection);
            pXRefOffset = 0x15;
        }
    }

    if (pFunc != 0) {
        // NOTE: Is a requirement to align properly.
        pFunc += virt_start_relative;
        manual_scan_section_dx8_register_D3DTSS(pContext, pLibrarySession, pFunc, pXRefOffset);
    }

    // Locate Xbox symbol "g_Stream" and store it's address
    pFunc = 0;
    // verified for D3D8 with 4361, 4627, 5344, 5558, 5659, 5788, 5849, 5933
    // and verified for LTCG with 4432, 4627, 5344, 5558, 5849
    iCodeOffsetFor_g_Stream = 0x22;

    // TODO: Need investigate reason for going with higher number first then lower last.
    if (pLibrary->flag == XbSymbolLib_D3D8) {
        if (pLibrary->build_version >= 4034) {
            OOVPA_version = 4034;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 4034,
                                       &D3DDevice_SetStreamSource_4034, pSection);
        }
        else {
            OOVPA_version = 3911;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 3911,
                                       &D3DDevice_SetStreamSource_3911, pSection);
            iCodeOffsetFor_g_Stream = 0x23; // verified for 3911
        }
    }
    else { // D3D8LTCG
        if (pLibrary->build_version > 4039) {
            OOVPA_version = 4034; // TODO Verify
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource", 1044,
                                       &D3DDevice_SetStreamSource_1044, pSection);
        }

        if (pFunc == 0) { // LTCG specific

            OOVPA_version = 4034; // TODO Verify
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource_4", 2058,
                                       &D3DDevice_SetStreamSource_4_2058, pSection);
            iCodeOffsetFor_g_Stream = 0x1E;
        }

        if (pFunc == 0) { // verified for 4039
            OOVPA_version = 4034;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource_8", 2040,
                                       &D3DDevice_SetStreamSource_8_2040, pSection);
            iCodeOffsetFor_g_Stream = 0x23;
        }

        if (pFunc == 0) { // verified for 3925
            OOVPA_version = 3911;
            pFunc = LocateFunctionCast(pContext, iLibraryType, "D3DDevice_SetStreamSource_8__LTCG_edx_StreamNumber", 1039,
                                       &D3DDevice_SetStreamSource_8__LTCG_edx_StreamNumber_1039, pSection);
            iCodeOffsetFor_g_Stream = 0x47;
        }
    }

    if (pFunc != 0) {
        // NOTE: Is a requirement to align properly.
        pFunc += virt_start_relative;

        manual_scan_section_dx8_register_stream(pContext, pLibrarySession, pFunc, iCodeOffsetFor_g_Stream);
    }

    // Manual check require for able to self-register these symbols:
    // * D3DDevice_SetSwapCallback
    // * D3DDevice_SetVerticalBlankCallback

    // First, check if D3D__PDEVICE is found.
    if (pContext->xref_database[XREF_D3D_g_pDevice] != XREF_ADDR_DERIVE &&
        // Then, check at least one of symbol's member variable is not found.
        pContext->xref_database[XREF_OFFSET_D3DDevice__m_SwapCallback] == XREF_ADDR_UNDETERMINED) {

        // Scan if event handle variable is not yet derived.
        if (pContext->xref_database[XREF_OFFSET_D3DDevice__m_VerticalBlankEvent] == XREF_ADDR_DERIVE) {
            xSymbolAddr = (xbaddr)(uintptr_t)internal_LocateSymbolFunction(pContext,
                                                                           pLibrarySession,
                                                                           pLibraryDB,
                                                                           "D3DDevice__m_VerticalBlankEvent__ManualFindGeneric",
                                                                           pSection,
                                                                           true,
                                                                           NULL,
                                                                           NULL);
        }

        // We are not registering D3DDevice__m_VerticalBlankEvent__ManualFindGeneric itself, as it is NOT a symbol.


        // If not found, skip manual register.
        if (pContext->xref_database[XREF_OFFSET_D3DDevice__m_VerticalBlankEvent] == XREF_ADDR_DERIVE) {
            return false;
        }

        // Finally, manual register the symbol variables.
        xSymbolAddr = pContext->xref_database[XREF_OFFSET_D3DDevice__m_VerticalBlankEvent];
        internal_SetXRefDatabase(pContext, iLibraryType, XREF_OFFSET_D3DDevice__m_SwapCallback, xSymbolAddr - 8);
        internal_SetXRefDatabase(pContext, iLibraryType, XREF_OFFSET_D3DDevice__m_VBlankCallback, xSymbolAddr - 4);
    }
    // If D3D__PDEVICE is not found, the scan is not complete
    // and will continue scan to next given section.
    else {
        return false;
    }

    return true;
}

static inline void manual_register_d3d8__ltcg(iXbSymbolContext* pContext)
{
    xbaddr xD3D_pDeviceAddr = pContext->xref_database[XREF_D3D_g_pDevice];
    if (internal_IsXRefAddrValid(xD3D_pDeviceAddr)) {
        // Register offsets of D3DDevice's members
        internal_RegisterValidXRefAddr_M(pContext, Lib_D3D8, XbSymbolLib_D3D8, XREF_OFFSET_D3DDevice__m_SwapCallback, 0, "D3DDevice__m_SwapCallback_OFFSET");
        internal_RegisterValidXRefAddr_M(pContext, Lib_D3D8, XbSymbolLib_D3D8, XREF_OFFSET_D3DDevice__m_VBlankCallback, 0, "D3DDevice__m_VBlankCallback_OFFSET");
        internal_RegisterValidXRefAddr_M(pContext, Lib_D3D8, XbSymbolLib_D3D8, XREF_OFFSET_D3DDevice__m_VertexShader, 0, "D3DDevice__m_VertexShader_OFFSET");
        internal_RegisterValidXRefAddr_M(pContext, Lib_D3D8, XbSymbolLib_D3D8, XREF_OFFSET_D3DDevice__m_VerticalBlankEvent, 0, "D3DDevice__m_VerticalBlankEvent_OFFSET");
    }
}

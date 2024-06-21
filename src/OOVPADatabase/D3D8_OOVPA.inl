// ******************************************************************
// *
// *   OOVPADatabase->D3D8_OOVPA.inl
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
// *  (c) 2017 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// Titles which did compiled with full library version
//   [LibV] Title Name                       |  Verify   |   Comments
//-----------------------------------------------------------------------
// * [3925] Azurik                           |   100%    | Missing D3D_SetPushBufferSize due locate in BINK section, have 182/196 library.
// * [3948] Shikigami no Shiro               |   100%    | have 178/196 library.
// * [4034] Dark Summit                      |   100%    | have 113/195 library.
// * [4039] New Legends                      |   100%    | have 117/195 library.
// * [4134] Double-S.T.E.A.L                 |   100%    | have 195/202 library.
// * [4242] NFL Blitz 2002                   |   100%    | have 180/202 library.
// * [4361] Hunter The Reckoning             |   100%    | have 117/204 library.
// * [4432] RedCard 2003                     |   100%    | have 184/206 library.
// * [4531] NHL HITZ 2003                    |   100%    | have 196/206 library.
// * [4627] MLB SlugFest 2003                |   100%    | have 216/227 library.
// * [4721] Terminator - Dawn of Fate        |   100%    | have 202/227 library.
// * [4831] Frogger Beyond                   |   100%    | have 200/227 library.
// * [4928] Drihoo                           |   100%    | have 201/228 library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | have 201/229 library.
// * [5120] N.U.D.E.@                        |   100%    | have 211/229 library.
// * [5233] Evil Dead                        |   100%    | have 208/230 library.
// * [5344] Gladius DEMO                     |   100%    | have 202/229 library.
// * [5455] Dinosaur Hunting                 |   100%    | have 207/229 library.
// * [5558] NHL HITZ Pro 2004                |   100%    | have 218/230 library.
// * [5558] XIII                             |   100%    | With Intergrated Hotfixes. have 209/230 library.
// * [5659] NFL Blitz Pro                    |   100%    | have 208/230 library.
// * [5659] Midway Arcade Treasures Paperboy |   100%    | With Intergrated Hotfixes. have 212/230 library.
// * [5788] Digimon Battle Chronicle         |   100%    | have 210/230 library.
// * [5849] Nickelodeon Tak 2                |   100%    | have 210/229 library.

// TODO: Known D3D8 OOVPA issue list
//   * CMiniport_IsFlipPending is XREF in v1 database, any reason for this?
// * Verification needed: Function Name ( Revision )
//   * D3D_AllocContiguousMemory (4034, 4242)
//   * D3D_ClearStateBlockFlags (4034, 4039, 4721, 5028, 5120)
//   * D3D_GetAdapterIdentifier (4034)
//   * D3D_RecordStateBlock (4034, 4039, 4721, 5028, 5120)
//   * D3D_SetPushBufferSize (4034)
//   * D3DBaseTexture_GetLevelCount (4034)
//   * D3DCubeTexture_GetCubeMapSurface (5233)
//   * D3DDevice_AddRef (4034)
//   * D3DDevice_ApplyStateBlock (4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_Begin (4034)
//   * D3DDevice_BeginPushBuffer (3950, 4034, 4242, 4831, 5028)
//   * D3DDevice_BeginStateBlock (3950, 4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_BlockOnFence (4034)
//   * D3DDevice_CaptureStateBlock (4034, 4039, 4432, 4721, 4831, 5028, 5120)
//   * D3DDevice_CreateCubeTexture (4721, 5028, 5233)
//   * D3DDevice_CreateImageSurface (4721, 5028, 5120)
//   * D3DDevice_CreateIndexBuffer (4721, 4928)
//   * D3DDevice_CreatePalette (4721, 4831, 4928, 5120, 5233, 5455)
//   * D3DDevice_CreateStateBlock (4034, 4039, 4242, 4432, 4721, 4928, 5028, 5120)
//   * D3DDevice_CreateVolumeTexture (5028, 5120, 5233, 5455)
//   * D3DDevice_DeletePatch (3950, 4134, 4242, 4432, 4721, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_DeleteStateBlock (3950, 4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_DeleteVertexShader (4034)
//   * D3DDevice_DrawIndexedVerticesUP (4034)
//   * D3DDevice_DrawRectPatch (3950, 4242, 4432, 4721, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_DrawTriPatch (3950, 4034, 4039, 4242, 4432, 4721, 4831, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_DrawVerticesUP (4034)
//   * D3DDevice_EnableOverlay (3950, 4034, 4039)
//   * D3DDevice_End (4034)
//   * D3DDevice_EndPushBuffer (3950, 4034, 4242, 4831, 5028)
//   * D3DDevice_EndStateBlock (3950, 4034, 4039, 4721, 4831, 5028, 5120)
//   * D3DDevice_FlushVertexCache (4034, 4039)
//   * D3DDevice_GetBackBuffer (4721, 4831, 4928, 5028, 5120, 5233, 5455)
//   * D3DDevice_GetBackMaterial (4034)
//   * D3DDevice_GetDepthStencilSurface (4034)
//   * D3DDevice_GetDisplayFieldStatus (4034)
//   * D3DDevice_GetDisplayMode (4034)
//   * D3DDevice_GetLightEnable (4034)
//   * D3DDevice_GetMaterial (4034)
//   * D3DDevice_GetModelView (4034)
//   * D3DDevice_GetOverlayUpdateStatus (3950, 4034, 4039, 4134, 4242, 4432, 4531)
//   * D3DDevice_GetPixelShader (4034)
//   * D3DDevice_GetProjectionViewportMatrix (4034, 4039)
//   * D3DDevice_GetPushBufferOffset (3950, 4034, 4242, 4831, 5028)
//   * D3DDevice_GetRenderTarget (4034, 5028)
//   * D3DDevice_GetScissors (4034)
//   * D3DDevice_GetShaderConstantMode (4034, 4039)
//   * D3DDevice_GetTexture2 (4034, 4039)
//   * D3DDevice_GetTile (4034)
//   * D3DDevice_GetVertexShader (4034)
//   * D3DDevice_GetVertexShaderConstant (4034)
//   * D3DDevice_GetVertexShaderDeclaration (4034)
//   * D3DDevice_GetVertexShaderFunction (4034)
//   * D3DDevice_GetVertexShaderInput (4034)
//   * D3DDevice_GetVertexShaderSize (4034)
//   * D3DDevice_GetVertexShaderType (4034)
//   * D3DDevice_InsertCallback (4034, 4039)
//   * D3DDevice_InsertFence (4034)
//   * D3DDevice_IsFencePending (4034)
//   * D3D_CDevice_KickOff (5455,5849)
//   * D3DDevice_KickPushBuffer (4034)
//   * D3DDevice_LoadVertexShaderProgram (4034)
//   * D3DDevice_PersistDisplay (4034)
//   * D3DDevice_PrimeVertexCache (4034)
//   * D3DDevice_RunPushBuffer (4034, 4831, 5028)
//   * D3DDevice_RunVertexStateShader (4034)
//   * D3DDevice_SetBackMaterial (4034)
//   * D3DDevice_SetModelView (4034)
//   * D3DDevice_SetPixelShaderConstant (4034)
//   * D3DDevice_SetPixelShaderProgram (4034)
//   * D3DDevice_SetVertexData2f (4034)
//   * D3DDevice_SetVertexData2s (4034)
//   * D3DDevice_SetVertexData4f (4034)
//   * D3DDevice_SetVertexData4s (4034)
//   * D3DDevice_SetVertexData4ub (4034)
//   * D3DDevice_SetVertexDataColor (4034)
//   * D3DDevice_SetVertexShaderInput (4034)
//   * D3DDevice_SetVerticalBlankCallback (4034)
//   * D3DDevice_SwitchTexture (4034)
//   * D3DDevice_UpdateOverlay (3950, 4034, 4039)
//   * D3DPalette_Lock (4721, 4831, 4928, 5120)
//   * D3DResource_BlockUntilNotBusy (4034)
//   * D3DResource_IsBusy (4034)
//   * D3DResource_Register (4034)
//   * D3DVertexBuffer_GetDesc (4034)
//   * D3DVertexBuffer_Lock (4721, 4831, 4928, 5120, 5233, 5455)
//   * Direct3D_CheckDeviceMultiSampleType (4034)
//   * CMiniport_IsFlipPending (4034, 4039, 4134, 4928, 5028, 5120, 5233, 5455)
//   * D3D_EnumAdapterModes (4034)
//   * D3D_GetAdapterDisplayMode (4034)
//   * D3D_GetAdapterModeCount (4034)
//   * IDirect3DVertexBuffer8_Lock (4721, 5028, 5120, 5233)
// * List of functions might be D3D8LTCG library: (Verifying with Sega GT 2002 title)
//   * D3D_CreateDeviceX (4627)
//   * D3D_KickOffAndWaitForIdle2 (4627)
//   * D3D_CommonSetRenderTargetB (4627)

#ifndef D3D8_OOVPA_INL
#define D3D8_OOVPA_INL

#include "OOVPA.h"

#include "D3D8/3911.inl"
#include "D3D8/3925.inl"
#include "D3D8/3947.inl"
#include "D3D8/4034.inl"
#include "D3D8/4039.inl"
#include "D3D8/4134.inl"
#include "D3D8/4242.inl"
#include "D3D8/4361.inl"
#include "D3D8/4432.inl"
#include "D3D8/4531.inl"
#include "D3D8/4627.inl"
#include "D3D8/4831.inl"
#include "D3D8/4928.inl"
#include "D3D8/5028.inl"
#include "D3D8/5120.inl"
#include "D3D8/5233.inl"
#include "D3D8/5344.inl"
#include "D3D8/5455.inl"
#include "D3D8/5558.inl"
#include "D3D8/5788.inl"
#include "D3D8/5849.inl"

#define REGISTER_OOVPAS_D3D(Symbol, ...)  REGISTER_OOVPAS_PREFIX(D3D, Symbol, __VA_ARGS__)
#define REGISTER_OOVPAS_D3D8(Symbol, ...) REGISTER_OOVPAS_PREFIX(D3D8, Symbol, __VA_ARGS__)

// ******************************************************************
// * D3D8_OOVPA
// ******************************************************************
OOVPATable D3D8_OOVPA[] = {
    REGISTER_OOVPAS_M(SYM_INT(D3DDevice__m_VerticalBlankEvent__GenericFragment),
                      SYM_SIG(3911)), // This OOVPA signature is not a symbol. Read its note for more details.
    REGISTER_OOVPAS_M(SYM_INT(D3DRS_Stencils_and_Occlusion__GenericFragment),
                      SYM_SIG(3911)), // This OOVPA signature is not a symbol. Read its note for more details.

    REGISTER_OOVPAS(SYM_FUN(D3D_UpdateProjectionViewportTransform, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3900, 3901)), // Final generic OOVPA: 4034; Removed: 0 // NOTE: 3901 is 4034 signature, except LTCG title been detected in 3925.

    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_InitializeFrameBuffers, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // thiscall
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_FreeFrameBuffers, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4034, 5455)), // Final generic OOVPA: 5455; Removed: 0 // thiscall
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_SetStateUP, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0 // thiscall
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_SetStateVB, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0 // thiscall

    REGISTER_OOVPAS(SYM_FUN(D3D_CreateTexture, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_MakeSpace, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911)), // NOTE: has multiple rets.
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_CreateCtxDmaObject, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_InitHardware, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4034, 5455)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_IsFlipPending, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4242, 4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(D3DBaseTexture_GetLevelCount, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_GetCubeMapSurface2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_GetCubeMapSurface, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_LockRect, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Just calls Lock2DSurface (from 4134, 4432's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_AddRef, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4134, 4242, 4627, 5028, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_ApplyStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Begin, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPush, STACK(8), PARAMS(/*unknown*/)),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPush, STACK(4), PARAMS(/*unknown*/)),
                    SYM_SIG(4531, 4627, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPushBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)), // Not implemented yet. (from 5788's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginStateBig, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginVisibilityTest, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BlockOnFence, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BlockUntilVerticalBlank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CaptureStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Clear, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CopyRects, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627, 5120)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateCubeTexture, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateImageSurface, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627)), // TODO 4721,4928 (from 4627's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateIndexBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // TODO: This needs to be verified on 4361
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateIndexBuffer2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePalette, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Called D3DDevice_CreatePalette2 (from 4627's comment) NOTE: Use D3DDevice_CreatePalette2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePalette2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5344, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePixelShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateTexture2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4831)), // Was 4627 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateTexture, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Called D3DDevice_CreateTexture2 (from 4627's comment) NOTE: Use D3DDevice_CreateTexture2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexBuffer2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5344, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVolumeTexture, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeletePatch, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // (TODO) (from 4034's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeletePixelShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeleteStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeleteVertexShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawIndexedVertices, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawIndexedVerticesUP, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5028, 5344)), // Final generic OOVPA: 5344; Removed: 0 // TODO: Need verify title with 4034 version.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawRectPatch, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // TODO: Unused? (from 4034's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawTriPatch, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawVertices, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawVerticesUP, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 5344)), // Final generic OOVPA: 5344; Removed: 0 // TODO: Need verify title with 4034 version.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EnableOverlay, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_End, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndPush, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4039)), // Was 4627 (from 5233's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndPushBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndVisibilityTest, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_FlushVertexCache, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134, 4627)), // Called D3DDevice_GetBackBuffer2 (from 4627's comment) NOTE: Use D3DDevice_GetBackBuffer2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackBuffer2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackMaterial, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetCreationParameters, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDepthStencilSurface, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Called D3DDevice_GetDepthStencilSurface2 (from 4627's comment) NOTE: Use D3DDevice_GetDepthStencilSurface2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDepthStencilSurface2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDeviceCaps, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDisplayFieldStatus, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDisplayMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetGammaRamp, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetLight, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetLightEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetMaterial, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetModelView, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetOverlayUpdateStatus, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetPersistedSurface2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4928)), // For only on Unreal Championship (from 4627's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetPixelShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4134, 5028, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetProjectionViewportMatrix, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134, 4627, 5344, 5558)), // For 5455 (from 5558's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetPushBufferOffset, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // TODO 4831 (from 4627's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetRenderTarget2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetRenderTarget, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0 // NOTE: Use D3DDevice_GetRenderTarget2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetScissors, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetShaderConstantMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134, 4627, 5028, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetStreamSource2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTexture2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTile, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTransform, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4134, 5028, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderConstant, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderDeclaration, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderFunction, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderInput, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderSize, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVertexShaderType, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetViewport, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5455)), // Was 4627 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetViewportOffsetAndScale, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetVisibilityTestResult, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_InsertCallback, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4134, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_InsertFence, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_IsBusy, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_IsFencePending, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 5028)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_KickOff, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911, 4034, 4531, 5028, 5455)), // Final generic OOVPA: 5455; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_KickPushBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LightEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LoadVertexShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LoadVertexShaderProgram, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_MakeSpace, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4034, 4134)), // NOTE: LTCG has duplicate functions, need to find out how to resolve this issue with cross referencing.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_PersistDisplay, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4627, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Present, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_PrimeVertexCache, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Release, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Reset, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_RunPushBuffer, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4627, 5120, 5558)), // for 5455 (from 5558's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_RunVertexStateShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SelectVertexShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SelectVertexShaderDirect, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetBackBufferScale, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetBackMaterial, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344, 5558, 5788)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetDepthClipPlanes, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetFlickerFilter, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetGammaRamp, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetIndices, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetLight, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetMaterial, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134, 4627, 5344, 5558, 5788)), // Was 4627 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetModelView, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPalette, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShaderConstant, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShaderProgram, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderState_Simple, STACK(/*default*/), PARAMS(/*unknown*/)),
                      SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderStateNotInline, STACK(/*default*/), PARAMS(/*unknown*/)),
                      SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: Must be after D3DDevice_SetRenderState_Simple.
    // NOTE: Some or most of render state signatures below must be after D3DDevice_SetRenderStateNotInline.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: There is a verified duplicate function.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_BackFillMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_C(SYM_FUN(D3DDevice_SetRenderState_CullMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                      SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_Deferred, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_DoNotCullUncompressed, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_Dxt1NoiseEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_EdgeAntiAlias, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderState_FillMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                      SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_FogColor, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_FrontFace, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_LineWidth, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_LogicOp, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleAntiAlias, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleMask, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleRenderTargetMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleType, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 3925)), // Final generic OOVPA: 3925 Removed: 4034
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_NormalizeNormals, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_OcclusionCullEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 1024)), // Final generic OOVPA: 3911 (LTCG) / 4034 (non-LTCG); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_PSTextureModes, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_RopZCmpAlwaysRead, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_RopZRead, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_SampleAlpha, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ShadowFunc, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilCullEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 1024)), // Final generic OOVPA: 3911 (LTCG) / 4034 (non-LTCG); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 5849)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilFail, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 5849)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_TextureFactor, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_TwoSidedLighting, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_VertexBlend, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_YuvEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 1024)), // Final generic OOVPA: 3911 (LTCG) / 4034 (non-LTCG); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ZBias, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ZEnable, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134, 4432)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderTarget, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 3947, 4034, 4039, 4627, 5344, 5455)), // Final generic OOVPA: 5344/5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderTargetFast, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetScissors, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5344, 5558)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetScreenSpaceOffset, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4034, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetShaderConstantMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetSoftDisplayFilter, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetStipple, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetStreamSource, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetSwapCallback, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTexture, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4361, 4831)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureStageStateNotInline, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_BorderColor, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_BumpEnv, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_ColorKeyColor, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS_C(SYM_FUN(D3DDevice_SetTextureState_TexCoordIndex, STACK(/*default*/), PARAMS(/*unknown*/)),
                      SYM_SIG(3911, 4034, 4242, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTile, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627)), // Then it has changed calls ?SetTileNoWait@D3D@@YGXKPBU_D3DTILE@@@Z in XDK 4627 and higher.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTransform, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_MultiplyTransform, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // TODO: Verify 4034 is correct
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData2f, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)), // Was 4627 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData2s, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4f, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4s, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4ub, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexDataColor, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShader, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134, 5028, 5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant1, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant1Fast, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant4, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstantNotInline, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5028, 5558)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstantNotInlineFast, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderInput, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderInputDirect, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVerticalBlankCallback, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetViewport, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 5344, 5455)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Suspend, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Swap, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4034, 4531, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SwitchTexture, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_UpdateOverlay, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4531, 5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DPalette_Lock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4531, 4627)), // Called D3DPalette_Lock2 (from 4627's comment) NOTE: Use D3DPalette_Lock2 for 4627 and above
    REGISTER_OOVPAS(SYM_FUN(D3DPalette_Lock2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_AddRef, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_BlockUntilNotBusy, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_GetType, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)), // Probably not even necessary... (from 3925's comment) // I forget why I had this in here... (from 5028's comment)
    REGISTER_OOVPAS(SYM_FUN(D3DResource_IsBusy, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_Register, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_Release, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DSurface_GetDesc, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DSurface_LockRect, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_GetSurfaceLevel, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_GetSurfaceLevel2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_LockRect, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_GetDesc, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_Lock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_Lock2, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DVolumeTexture_LockBox, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Just calls Lock3DSurface (from 4134, 4432's comment)
    REGISTER_OOVPAS(SYM_FUN(D3D_AllocContiguousMemory, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5455)), // Final generic OOVPA: 5455; Removed: 0 // Just calls MmAllocateContiguousMemory.
    REGISTER_OOVPAS(SYM_FUN(D3D_BlockOnResource, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3D_BlockOnTime, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627, 5028, 5558)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_GetDisplayCapabilities, STACK(/*default*/), PARAMS(/*unknown*/)),
                        SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_CheckDeviceFormat, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_ClearStateBlockFlags, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS_M(SYM_FUN(D3D_CommonSetDebugRegisters, STACK(/*default*/), PARAMS(/*unknown*/)),
                      SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3D_CommonSetRenderTarget, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5028)), // Final generic OOVPA: 4627; Removed: 5344
    REGISTER_OOVPAS(SYM_FUN(D3D_CommonSetMultiSampleModeAndScale, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 // fastcall (2 params)
    REGISTER_OOVPAS(SYM_FUN(D3D_CreateStandAloneSurface, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4034)),
    REGISTER_OOVPAS(SYM_FUN(D3D_DestroyResource, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_EnumAdapterModes, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetAdapterDisplayMode, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetAdapterIdentifier, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetAdapterModeCount, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_GetDeviceCaps, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_KickOffAndWaitForIdle, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4627, 5028)),
    REGISTER_OOVPAS(SYM_FUN(D3D_LazySetPointParams, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034)),
    REGISTER_OOVPAS(SYM_FUN(D3D_RecordStateBlock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetFence, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 4034, 4134, 5028, 5558)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetPushBufferSize, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetTileNoWait, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(Direct3D_CheckDeviceMultiSampleType, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(Direct3D_CreateDevice, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911, 5028)),
    REGISTER_OOVPAS_D3D8(SYM_FUN(Get2DSurfaceDesc, STACK(/*default*/), PARAMS(/*unknown*/)),
                         SYM_SIG(3911, 4034)), // Was 5233 (from 5344's comment)
    REGISTER_OOVPAS_D3D8(SYM_FUN(Lock2DSurface, STACK(/*default*/), PARAMS(/*unknown*/)),
                         SYM_SIG(3911)),
    REGISTER_OOVPAS_D3D8(SYM_FUN(Lock3DSurface, STACK(/*default*/), PARAMS(/*unknown*/)),
                         SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_MakeRequestedSpace, STACK(4), PARAMS(/*unknown*/)),
                    SYM_SIG(4034)), // Final generic OOVPA: 4034??; Removed: 4134 // NOTE: has multiple rets.
    REGISTER_OOVPAS(SYM_FUN(D3D_MakeRequestedSpace, STACK(8), PARAMS(/*unknown*/)),
                    SYM_SIG(4134, 5558)), // Final generic OOVPA: 5558; Removed: 0 // NOTE: has multiple rets.
    REGISTER_OOVPAS(SYM_FUN(XMETAL_StartPush, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4034??
    REGISTER_OOVPAS(SYM_FUN(IDirect3DVertexBuffer8_Lock, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
};


// ******************************************************************
// * D3D8_OOVPA_COUNT
// ******************************************************************
#define D3D8_OOVPA_COUNT XBSDB_ARRAY_SIZE(D3D8_OOVPA)

#endif

// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG_OOVPA.inl
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

// Titles which did compiled with full libary version
//   [LibV] Title Name                       |  Verify   |   Comments
//-----------------------------------------------------------------------
// * [3925] NASCAR Heat 2002                 |    20%    | Only verified an actually used library.
// * [4039] NBA 2K2                          |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4432] Bruce Lee                        |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4627] Battle Engine Aquila             |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4928] Shin Megami Tensei - Nine        |   100%    | Only has 80% of the library compiled with xbe build.
// * [5233] Midtown Madness 3                |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [5455] Freaky Flyers                    |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [5659] Ninja Gaiden                     |   100%    | With Integrated Hotfixes. Only has a few library.
// * [5849] Grand Theft Auto - San Andreas   |   100%    | Only has 50%-ish of the library compiled with xbe build.

// * About the number of OOVPA
//   * 1024 and 1xxx - Compatible with known functions probably.
//   * 2028 and 2xxx - Remade by Link-time Code Generation, will not work with known functions.

// TODO: Known D3D8LTCG OOVPA issue list
// * Verification needed: Function Name ( Revision )
//   * CDevice_FreeFrameBuffers_4 (4034 ... < 4432) // NOTE: CDevice_FreeFrameBuffers_4 4433 signature is the same except off by one offset near start of the body.
//   * CDevice_InitializeFrameBuffers_8 (4034 ... < 4627) // NOTE: Haven't found any titles below 4627 that match with the 4627's signature.
//   * CDevice_InitializeFrameBuffers_4__LTCG_esi1 (3911 ... 4034) // NOTE: Unknown if it needs to be lowered to 4034 or below. Plus only found in one title, NBA 2K2.
//   * CDevice_InitializeFrameBuffers_4__LTCG_ebx1 (3911 ... < 4432) // NOTE: Haven't found any titles below 4432 to match signatures.
//   * CDevice_InitializeFrameBuffers_4__LTCG_edi1 (3911 ... < 5455) // NOTE: Likely caused by newer compiler yet haven't found any titles below 5455 to match signature.
//   * D3DDevice_Reset (4034 ... < 4432) // NOTE: Unknown if any signatures need to be lower.
//   * D3DDevice_Reset_0__LTCG_edi1 (4034 ... < 4039) // NOTE: Unknown if 4039 signature needs to be lower.
//   * D3DDevice_Reset_0__LTCG_ebx1 (... < 5344) // NOTE: Unknown if signature needs to be lower, and may have appeared at the same time when CDevice_InitializeFrameBuffers_4__LTCG_edi1 was introduced.

#ifndef D3D8LTCG_OOVPA_INL
#define D3D8LTCG_OOVPA_INL

#include "OOVPA.h"

#include "D3D8LTCG/3911.inl"
#include "D3D8LTCG/4034.inl"
#include "D3D8LTCG/4039.inl"
#include "D3D8LTCG/4134.inl"
#include "D3D8LTCG/4432.inl"
#include "D3D8LTCG/4531.inl"
#include "D3D8LTCG/4627.inl"
#include "D3D8LTCG/4721.inl"
#include "D3D8LTCG/4928.inl"
#include "D3D8LTCG/5028.inl"
#include "D3D8LTCG/5120.inl"
#include "D3D8LTCG/5233.inl"
#include "D3D8LTCG/5344.inl"
#include "D3D8LTCG/5455.inl"
#include "D3D8LTCG/5788.inl"
#include "D3D8LTCG/5849.inl"

// ******************************************************************
// * D3D8LTCG_OOVPA
// ******************************************************************
OOVPATable D3D8LTCG_OOVPA[] = {

    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_CreateTexture, CALL(unk), STACK(28), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Depth), PARAM(stk, Levels), PARAM(stk, Usage), PARAM(stk, Format), PARAM(stk, isCube), PARAM(_dl, isVolume), PARAM(edi, ppTexture))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 4627 // See note for details.
    REGISTER_OOVPAS(SYM_FUN(D3D_MakeRequestedSpace, CALL(std), STACK(8), PARAMS(PARAM(stk, MinimumSpace), PARAM(stk, RequestedSpace))),
                    SYM_SIG(1036)), // NOTE: OOVPA is in 5849. In used by (5849) Manhunt title
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_MakeRequestedSpace, CALL(unk), STACK(4), PARAMS(PARAM(stk, MinimumSpace), PARAM(eax, RequestedSpace))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN(D3D_SetFence, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Flags))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3D_BlockOnTime, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Time), PARAM(stk, MakeSpace))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_BlockOnTime, CALL(unk), STACK(4), PARAMS(PARAM(eax, Time), PARAM(stk, MakeSpace))),
                    SYM_SIG(2048, 2060)),

    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_FreeFrameBuffers, CALL(unk), STACK(0), PARAMS(PARAM(ebx, this))),
                        SYM_SIG(3911, 4034)), // Final generic OOVPA: 4034; Removed: 0
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_FreeFrameBuffers, CALL(std), STACK(4), PARAMS(PARAM(stk, this))),
                        SYM_SIG(4432, 4433)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_InitializeFrameBuffers, CALL(std), STACK(8), PARAMS(PARAM(stk, this), PARAM(stk, pPresentationParams))),
                        SYM_SIG(3911, 4627)),
    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_InitializeFrameBuffers, CALL(unk), STACK(4), PARAMS(PARAM(esi, this), PARAM(stk, pPresentationParams))),
                        SYM_SIG(4039)),
    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_InitializeFrameBuffers, CALL(unk), STACK(4), PARAMS(PARAM(ebx, this), PARAM(stk, pPresentationParams))),
                        SYM_SIG(4432, 4433, 4531)),
    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_InitializeFrameBuffers, CALL(unk), STACK(4), PARAMS(PARAM(edi, this), PARAM(stk, pPresentationParams))),
                        SYM_SIG(5455)),

    REGISTER_OOVPAS_D3D(SYM_FUN(CMiniport_InitHardware, CALL(std), STACK(4), PARAMS(PARAM(stk, this))),
                        SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_GetCubeMapSurface2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, FaceType), PARAM(stk, Level))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DCubeTexture_GetCubeMapSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, FaceType), PARAM(stk, Level), PARAM(stk, ppCubeMapSurface))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Begin, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, PrimitiveType))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPush, CALL(std), STACK(4), PARAMS(PARAM(stk, Count))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pPushBuffer))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_BeginPushBuffer, CALL(unk), STACK(0), PARAMS(PARAM(edi, pPushBuffer))),
                    SYM_SIG(2048, 2060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BeginVisibilityTest, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_BlockUntilVerticalBlank, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024)), // NOTE: NASCAR Heat 2002 reveal this function is inlined, need some sort of indicator which is inline or not.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Clear, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Count), PARAM(stk, pRects), PARAM(stk, Flags), PARAM(stk, Color), PARAM(stk, Z), PARAM(stk, Stencil))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CopyRects, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pSourceSurface), PARAM(stk, pSourceRectsArray), PARAM(stk, cRects), PARAM(stk, pDestinationSurface), PARAM(stk, pDestPointsArray))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateCubeTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, EdgeLength), PARAM(stk, Levels), PARAM(stk, Usage), PARAM(stk, Format), PARAM(stk, Pool), PARAM(stk, ppCubeTexture))),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_CreateCubeTexture, CALL(unk), STACK(4), PARAMS(PARAM(eax, EdgeLength), PARAM(stk, Levels), PARAM(edx, Usage), PARAM(ecx, Format), PARAM(stk, Pool), PARAM(edi, ppCubeTexture))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreatePixelShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pPSDef), PARAM(stk, pHandle))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Levels), PARAM(stk, Usage), PARAM(stk, Format), PARAM(stk, Pool), PARAM(stk, ppTexture))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_CreateTexture, CALL(unk), STACK(8), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(edx, Levels), PARAM(ecx, Usage), PARAM(eax, Format), PARAM(stk, Pool), PARAM(edi, ppTexture))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateTexture2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Levels), PARAM(stk, Usage), PARAM(stk, Format), PARAM(stk, D3DResource))),
                    SYM_SIG(1024, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_CreateVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pDeclaration), PARAM(stk, pFunction), PARAM(stk, pHandle), PARAM(stk, Usage))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_CreateVolumeTexture, CALL(unk), STACK(12), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Depth), PARAM(edx, Levels), PARAM(ecx, Usage), PARAM(eax, Format), PARAM(stk, Pool), PARAM(edi, ppVolumeTexture))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_DeletePixelShader, CALL(unk), STACK(0), PARAMS(PARAM(eax, Handle))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DeleteStateBlock, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Token))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_DeleteVertexShader, CALL(unk), STACK(0), PARAMS(PARAM(eax, Handle))),
                    SYM_SIG(3911, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawIndexedVertices, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, PrimitiveType), PARAM(eax, VertexCount), PARAM(stk, pIndexData))),
                    SYM_SIG(1024, 1036, 1037)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawIndexedVerticesUP, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, PrimitiveType), PARAM(eax, VertexCount), PARAM(stk, pIndexData), PARAM(stk, pVertexStreamZeroData), PARAM(stk, VertexStreamZeroStride))),
                    SYM_SIG(1024, 1036, 1048)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawVertices, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, PrimitiveType), PARAM(stk, StartVertex), PARAM(stk, VertexCount))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_DrawVertices, CALL(unk), STACK(4), PARAMS(PARAM(stk, PrimitiveType), PARAM(ecx, StartVertex), PARAM(eax, VertexCount))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_DrawVertices, CALL(unk), STACK(8), PARAMS(PARAM(stk, PrimitiveType), PARAM(stk, StartVertex), PARAM(eax, VertexCount))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_DrawVerticesUP, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, PrimitiveType), PARAM(stk, VertexCount), PARAM(stk, pVertexStreamZeroData), PARAM(stk, VertextStreamZeroStride))),
                    SYM_SIG(1024, 1048)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_DrawVerticesUP, CALL(unk), STACK(12), PARAMS(PARAM(stk, PrimitiveType), PARAM(stk, VertexCount), PARAM(ebx, pVertexStreamZeroData), PARAM(stk, VertextStreamZeroStride))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_EnableOverlay, CALL(std), STACK(0), PARAMS(PARAM1(void /*, Enable*/))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_End, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024)), // Final generic OOVPA: 4432?; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_EndVisibilityTest, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Index))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_EndVisibilityTest, CALL(unk), STACK(0), PARAMS(PARAM(eax, Index))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetBackBuffer2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, BackBuffer))),
                    SYM_SIG(4626)), // Due to non-LTCG signature conflict, lowered down by one number.
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_GetBackBuffer, CALL(unk), STACK(8), PARAMS(PARAM(eax, BackBuffer), PARAM(stk, Type), PARAM(stk, ppBackBuffer))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_GetBackBuffer2, CALL(unk), STACK(0), PARAMS(PARAM(eax, BackBuffer))),
                    SYM_SIG(4627, 5233)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDepthStencilSurface, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, ppZStencilSurface))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDepthStencilSurface2, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetDisplayMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pModes))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetRenderTarget2, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetTransform, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, State), PARAM(stk, pMatrix))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_GetViewportOffsetAndScale, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pOffset), PARAM(stk, pScale))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_GetViewportOffsetAndScale, CALL(unk), STACK(0), PARAMS(PARAM(edx, pOffset), PARAM(ecx, pScale))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_IsBusy, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_IsFencePending, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Fence))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LightEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Index), PARAM(stk, bEnable))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_LightEnable, CALL(unk), STACK(4), PARAMS(PARAM(eax, Index), PARAM(stk, bEnable))),
                    SYM_SIG(2024, 2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_LoadVertexShaderProgram, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pFunction), PARAM(stk, Address))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_LoadVertexShader, CALL(unk), STACK(0), PARAMS(PARAM(ecx, Handle), PARAM(eax, Address))),
                    SYM_SIG(2024, 2036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_LoadVertexShader, CALL(unk), STACK(0), PARAMS(PARAM(edx, Handle), PARAM(eax, Address))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_LoadVertexShader, CALL(unk), STACK(4), PARAMS(PARAM(eax, Handle), PARAM(stk, Address))),
                    SYM_SIG(2024, 2036, 2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_MultiplyTransform, CALL(unk), STACK(0), PARAMS(PARAM(ebx, State), PARAM(eax, pMatrix))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_PersistDisplay, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1024, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Present, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pSourceRect), PARAM(stk, pDestRect), PARAM(stk, pDummy1), PARAM(stk, pDummy2))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Reset, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pPresentationParameters))),
                    SYM_SIG(4432, 4627, 5120)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_Reset, CALL(unk), STACK(0), PARAMS(PARAM(edi, pPresentationParameters))),
                    SYM_SIG(3911, 4039, 4040, 4041)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_Reset, CALL(unk), STACK(0), PARAMS(PARAM(ebx, pPresentationParameters))),
                    SYM_SIG(5344)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_RunPushBuffer, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pPushBuffer), PARAM(stk, pFixup))),
                    SYM_SIG(1024, 1048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_RunPushBuffer, CALL(unk), STACK(4), PARAMS(PARAM(stk, pPushBuffer), PARAM(eax, pFixup))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_RunVertexStateShader, CALL(unk), STACK(4), PARAMS(PARAM(stk, Address), PARAM(esi, pData))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SelectVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Handle), PARAM(stk, Address))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SelectVertexShader, CALL(unk), STACK(0), PARAMS(PARAM(eax, Handle), PARAM(ebx, Address))),
                    SYM_SIG(2024, 2048, 2060, 2061, 2062, 2072, 2084)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SelectVertexShader, CALL(unk), STACK(4), PARAMS(PARAM(eax, Handle), PARAM(stk, Address))),
                    SYM_SIG(3911, 4039, 4531, 4627)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SelectVertexShaderDirect, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pVAF), PARAM(stk, Address))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SelectVertexShaderDirect, CALL(unk), STACK(0), PARAMS(PARAM(eax, pVAF), PARAM(ebx, Address))),
                    SYM_SIG(2024, 2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetFlickerFilter, CALL(unk), STACK(0), PARAMS(PARAM(esi, Filter))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetGammaRamp, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Flags), PARAM(stk, pRamp))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetIndices, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pIndexData), PARAM(stk, BaseVertexIndex))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetIndices, CALL(unk), STACK(4), PARAMS(PARAM(ebx, pIndexData), PARAM(stk, BaseVertexIndex))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetLight, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Index), PARAM(stk, pLight))),
                    SYM_SIG(1024, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPalette, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Stage), PARAM(stk, pPalette))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetPalette, CALL(unk), STACK(4), PARAMS(PARAM(eax, Stage), PARAM(stk, pPalette))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Handle))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShaderConstant, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, pConstantData), PARAM(stk, ConstantCount))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetPixelShaderConstant, CALL(unk), STACK(4), PARAMS(PARAM(ecx, Register), PARAM(stk, pConstantData), PARAM(eax, ConstantCount))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetPixelShaderProgram, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pPSDef))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetPixelShader, CALL(unk), STACK(0), PARAMS(PARAM(eax, Handle))),
                    SYM_SIG(2024, 2036, 2048, 2060, 2072)),
    REGISTER_OOVPAS_M(SYM_INT(D3DDevice_SetRenderStateInline__GenericFragment),
                      SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039?; Removed: 0 // NOTE: see notes from 4039 sig.
    // REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetRenderStateNotInline, CALL(unk), STACK(0), PARAMS(PARAM(esi, Value), PARAM(edi, Value))),
    //                 SYM_SIG(2048)), // NOTE: Signature is unlikely correct and need correction or removal (maybe)
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_BackFillMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS_C(SYM_FUN(D3DDevice_SetRenderState_CullMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                      SYM_SIG(1045, 1049, 1052, 1053)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_EdgeAntiAlias, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS_M(SYM_FUN(D3DDevice_SetRenderState_FillMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                      SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_FogColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_FrontFace, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_LineWidth, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_LogicOp, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleAntiAlias, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1060)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_MultiSampleMask, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1060)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_NormalizeNormals, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_SampleAlpha, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024)), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ShadowFunc, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_StencilFail, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_TextureFactor, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_TwoSidedLighting, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1060, 1061, 1084)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_VertexBlend, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ZBias, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderState_ZEnable, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Value))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderTarget, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pRenderTarget), PARAM(stk, pNewZStencil))),
                    SYM_SIG(1024, 1036, 1048, 1072, 1084)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetRenderTarget, CALL(unk), STACK(0), PARAMS(PARAM(ecx, pRenderTarget), PARAM(eax, pNewZStencil))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetRenderTargetFast, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pRenderTarget), PARAM(stk, pNewZStencil), PARAM(stk, Flags))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetScissors, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Count), PARAM(stk, Exclusive), PARAM(stk, pRects))),
                    SYM_SIG(1024, 1036, 1048, 1060, 1072)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetScreenSpaceOffset, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, x), PARAM(stk, y))),
                    SYM_SIG(1024)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetShaderConstantMode, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Mode))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetShaderConstantMode, CALL(unk), STACK(0), PARAMS(PARAM(eax, Mode))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetSoftDisplayFilter, CALL(unk), STACK(0), PARAMS(PARAM(unk, Enable))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_SetStateUP, CALL(std), STACK(4), PARAMS(PARAM(stk, this))),
                        SYM_SIG(3911)),
    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_SetStateUP, CALL(unk), STACK(0), PARAMS(PARAM(esi, this))),
                        SYM_SIG(4039, 4040)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_SetStateVB, CALL(std), STACK(8), PARAMS(PARAM(stk, this), PARAM(stk, unknown2))),
                        SYM_SIG(3911, 4039)), // TODO: Update unknown parameter name(s) if able.
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetStreamSource, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, StreamNumber), PARAM(stk, pStreamData), PARAM(stk, Stride))),
                    SYM_SIG(1044)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetStreamSource, CALL(unk), STACK(0), PARAMS(PARAM(eax, StreamNumber), PARAM(edi, pStreamData), PARAM(ebx, Stride))),
                    SYM_SIG(2058)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetStreamSource, CALL(unk), STACK(8), PARAMS(PARAM(edx, StreamNumber), PARAM(stk, pStreamData), PARAM(stk, Stride))),
                    SYM_SIG(2039)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetStreamSource, CALL(unk), STACK(4), PARAMS(PARAM(eax, StreamNumber), PARAM(ebx, pStreamData), PARAM(stk, Stride))),
                    SYM_SIG(2058)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetStreamSource, CALL(unk), STACK(8), PARAMS(PARAM(eax, StreamNumber), PARAM(stk, pStreamData), PARAM(stk, Stride))),
                    SYM_SIG(2040)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTexture, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Stage), PARAM(stk, pTexture))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureStageStateNotInline, CALL(unk), STACK(0), PARAMS(PARAM(ecx, Stage), PARAM(edx, Type), PARAM(eax, Value))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureStageStateNotInline, CALL(unk), STACK(0), PARAMS(PARAM(eax, Stage), PARAM(edx, Type), PARAM(ecx, Value))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureStageStateNotInline2, CALL(unk), STACK(0), PARAMS(PARAM(eax, Stage), PARAM(edx, Type), PARAM(ecx, Value))),
                    SYM_SIG(4039)), // TODO: fix bug to include counter from previous sections?
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_CDevice_SetTextureStageStateNotInline, CALL(unk), STACK(0), PARAMS(PARAM(eax, Stage), PARAM(edx, Type), PARAM(ecx, Value))),
                    SYM_SIG(4039)), // NOTE: has return 0 (xor eax)
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureStageStateNotInline, CALL(unk), STACK(0), PARAMS(PARAM(ecx, Stage), PARAM(eax, Type), PARAM(edx, Value))),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureStageStateNotInline, CALL(unk), STACK(0), PARAMS(PARAM(eax, Stage), PARAM(edx, Type), PARAM(esi, Value))),
                    SYM_SIG(4531)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_BorderColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Stage), PARAM(stk, Value))),
                    SYM_SIG(1024, 1048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureState_BorderColor, CALL(unk), STACK(0), PARAMS(PARAM(eax, Stage), PARAM(ebx, Value))),
                    SYM_SIG(2024, 2036, 2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureState_BorderColor, CALL(unk), STACK(4), PARAMS(PARAM(eax, Stage), PARAM(stk, Value))),
                    SYM_SIG(2048, 2060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_BumpEnv, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Stage), PARAM(stk, Type), PARAM(stk, Value))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureState_BumpEnv, CALL(unk), STACK(8), PARAMS(PARAM(eax, Stage), PARAM(stk, Type), PARAM(stk, Value))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetTextureState_ColorKeyColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Stage), PARAM(stk, Value))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureState_ColorKeyColor, CALL(unk), STACK(0), PARAMS(PARAM(esi, Stage), PARAM(ebx, Value))),
                    SYM_SIG(2024, 2036, 2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTextureState_ColorKeyColor, CALL(unk), STACK(4), PARAMS(PARAM(eax, Stage), PARAM(stk, Value))),
                    SYM_SIG(2048, 2060)),
    REGISTER_OOVPAS_C(SYM_FUN(D3DDevice_SetTextureState_TexCoordIndex, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Stage), PARAM(stk, Value))),
                      SYM_SIG(1944, 1958)),
    REGISTER_OOVPAS_C(SYM_FUN_LTCG(D3DDevice_SetTextureState_TexCoordIndex, CALL(unk), STACK(0), PARAMS(PARAM(edi, Stage), PARAM(eax, Value))),
                      SYM_SIG(2039, 2058)),
    REGISTER_OOVPAS_C(SYM_FUN_LTCG(D3DDevice_SetTextureState_TexCoordIndex, CALL(unk), STACK(4), PARAMS(PARAM(esi, Stage), PARAM(stk, Value))),
                      SYM_SIG(2040, 2045, 2052, 2058)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTexture, CALL(unk), STACK(4), PARAMS(PARAM(stk, Stage), PARAM(eax, pTexture))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTexture, CALL(unk), STACK(4), PARAMS(PARAM(eax, Stage), PARAM(stk, pTexture))),
                    SYM_SIG(2036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTile, CALL(unk), STACK(0), PARAMS(PARAM(eax, Index), PARAM(ecx, pTile))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTile, CALL(unk), STACK(0), PARAMS(PARAM(ebx, Index), PARAM(eax, pTile))),
                    SYM_SIG(4039)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTile, CALL(unk), STACK(0), PARAMS(PARAM(ecx, Index), PARAM(eax, pTile))),
                    SYM_SIG(4432)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_SetTileNoWait, CALL(unk), STACK(0), PARAMS(PARAM(eax, Index), PARAM(ecx, pTile))),
                    SYM_SIG(2024, 2048, 5455, 5659)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_SetTileNoWait, CALL(unk), STACK(0), PARAMS(PARAM(ecx, Index), PARAM(eax, pTile))),
                    SYM_SIG(4721, 5849)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetTransform, CALL(unk), STACK(0), PARAMS(PARAM(eax, State), PARAM(edx, pMatrix))),
                    SYM_SIG(3911, 4034, 5344, 5455, 5558)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData2f, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, a), PARAM(stk, b))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData2s, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, a), PARAM(stk, b))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4f, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, a), PARAM(stk, b), PARAM(stk, c), PARAM(stk, d))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetVertexData4f, CALL(unk), STACK(16), PARAMS(PARAM(edi, Register), PARAM(stk, a), PARAM(stk, b), PARAM(stk, c), PARAM(stk, d))),
                    SYM_SIG(2024, 2036, 2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4s, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, a), PARAM(stk, b), PARAM(stk, c), PARAM(stk, d))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexData4ub, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, a), PARAM(stk, b), PARAM(stk, c), PARAM(stk, d))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexDataColor, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, Color))),
                    SYM_SIG(4038)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShader, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Handle))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderConstant, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Register), PARAM(stk, pConstantData), PARAM(stk, ConstantCount))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetVertexShaderConstantNotInline, CALL(unk), STACK(0), PARAMS(PARAM(ebx, Register), PARAM(eax, pConstantData), PARAM(edx, ConstantCount))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetVertexShaderConstant, CALL(unk), STACK(8), PARAMS(PARAM(stk, Register), PARAM(stk, pConstantData), PARAM(edx, ConstantCount))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetVertexShaderInput, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Handle), PARAM(stk, StreamCount), PARAM(stk, pStreamInputs))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_SetVertexShader, CALL(unk), STACK(0), PARAMS(PARAM(ebx, Handle))),
                    SYM_SIG(2024, 2036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_SetViewport, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pViewport))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_Swap, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Flags))),
                    SYM_SIG(1024, 1036, 1048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_Swap, CALL(unk), STACK(0), PARAMS(PARAM(eax, Flags))),
                    SYM_SIG(2024, 2036)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_UpdateOverlay, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pSurface), PARAM(stk, SrcRect), PARAM(stk, DstRect), PARAM(stk, EnableColorKey), PARAM(stk, ColorKey))),
                    SYM_SIG(1024, 1036, 1048, 1060)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DDevice_UpdateOverlay, CALL(unk), STACK(16), PARAMS(PARAM(stk, pSurface), PARAM(eax, SrcRect), PARAM(stk, DstRect), PARAM(stk, EnableColorKey), PARAM(stk, ColorKey))),
                    SYM_SIG(2048)),
    REGISTER_OOVPAS(SYM_FUN(D3DPalette_Lock2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, Flags))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_GetType, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3DResource_GetType, CALL(fas), STACK(0), PARAMS(PARAM(ecx, pThis))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN(D3DResource_Release, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN(D3DSurface_GetDesc, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pDesc))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_GetSurfaceLevel2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, Level))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DTexture_LockRect, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, Level), PARAM(stk, pLockedRect), PARAM(stk, pRect), PARAM(stk, Flags))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN(D3DVertexBuffer_Lock2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pVertexBuffer), PARAM(stk, Flags))),
                    SYM_SIG(1024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_BlockOnResource, CALL(unk), STACK(0), PARAMS(PARAM(eax, pResource))),
                    SYM_SIG(2024, 2036, 2048, 2060)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_DestroyResource, CALL(unk), STACK(0), PARAMS(PARAM(edi, pResource))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(D3D_CommonSetRenderTarget, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pRenderTarget), PARAM(stk, pNewZStencil), PARAM(stk, unknown3))),
                    SYM_SIG(1024, 1036, 1048, 1060)), // TODO: Update unknown parameter name(s) if able.
    REGISTER_OOVPAS(SYM_FUN_LTCG(D3D_CommonSetMultiSampleModeAndScale, CALL(unk), STACK(4), PARAMS(PARAM(eax, this), PARAM(stk, pViewport))),
                    SYM_SIG(5344)),
    REGISTER_OOVPAS(SYM_FUN(D3D_KickOffAndWaitForIdle2, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2))),
                    SYM_SIG(1024, 1036, 1048)), // TODO: Update unknown parameter name(s) if able.
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_KickOff, CALL(thi), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                        SYM_SIG(1048)),
    REGISTER_OOVPAS_D3D(SYM_FUN(CDevice_KickOff, CALL(std), STACK(4), PARAMS(PARAM(stk, this))),
                        SYM_SIG(4432, 4531, 5028)),
    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_KickOff, CALL(unk), STACK(0), PARAMS(PARAM(edx, this))),
                        SYM_SIG(3911, 4039, 5028)), // Final generic OOVPA: 5028; Removed: 0
    REGISTER_OOVPAS_D3D(SYM_FUN_LTCG(CDevice_KickOff, CALL(unk), STACK(0), PARAMS(PARAM(eax, this))),
                        SYM_SIG(5455)),
    REGISTER_OOVPAS(SYM_FUN(D3DDevice_MakeSpace, CALL(std), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(1036)), // Almost identical to generic 4134 signature.
    REGISTER_OOVPAS(SYM_FUN(Direct3D_CreateDevice, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, Adapter), PARAM(stk, DeviceType), PARAM(stk, hFocusWindow), PARAM(stk, BehaviorFlags), PARAM(stk, pPresentationParameters), PARAM(stk, ppReturnedDeviceInterface))),
                    SYM_SIG(1024, 1036)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(Direct3D_CreateDevice, CALL(unk), STACK(16), PARAMS(PARAM(stk, Adapter), PARAM(stk, DeviceType), PARAM(stk, hFocusWindow), PARAM(eax, BehaviorFlags), PARAM(stk, pPresentationParameters), PARAM(ebx, ppReturnedDeviceInterface))),
                    SYM_SIG(2024)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(Direct3D_CreateDevice, CALL(unk), STACK(16), PARAMS(PARAM(stk, Adapter), PARAM(stk, DeviceType), PARAM(stk, hFocusWindow), PARAM(eax, BehaviorFlags), PARAM(stk, pPresentationParameters), PARAM(ecx, ppReturnedDeviceInterface))),
                    SYM_SIG(2036, 2048)),
    REGISTER_OOVPAS(SYM_FUN_LTCG(Direct3D_CreateDevice, CALL(unk), STACK(4), PARAMS(PARAM(eax, BehaviorFlags), PARAM(stk, pPresentationParameters), PARAM(ecx, ppReturnedDeviceInterface))),
                    SYM_SIG(2048, 2060)),
    REGISTER_OOVPAS_D3D8(SYM_FUN(Get2DSurfaceDesc, CALL(std), STACK(/*default*/), PARAMS(PARAM(stk, pPixelContainer), PARAM(stk, Level), PARAM(stk, pDesc))),
                         SYM_SIG(1024)),
    REGISTER_OOVPAS_D3D8(SYM_FUN_LTCG(Get2DSurfaceDesc, CALL(unk), STACK(0), PARAMS(PARAM(edi, pPixelContainer), PARAM(ebx, Level), PARAM(esi, pDesc))),
                         SYM_SIG(2024, 2036)),
    REGISTER_OOVPAS_D3D8(SYM_FUN_LTCG(Get2DSurfaceDesc, CALL(unk), STACK(4), PARAMS(PARAM(edi, pPixelContainer), PARAM(stk, Level), PARAM(esi, pDesc))),
                         SYM_SIG(2048)),
    REGISTER_OOVPAS_D3D8(SYM_FUN_LTCG(Lock3DSurface, CALL(unk), STACK(16), PARAMS(PARAM(stk, pPixelContainer), PARAM(stk, Level), PARAM(stk, pLockedVolume), PARAM(eax, pBox), PARAM(stk, Flags))),
                         SYM_SIG(2048)),
    REGISTER_OOVPAS_D3D8(SYM_FUN_LTCG(Lock2DSurface, CALL(unk), STACK(16), PARAMS(PARAM(stk, pPixelContainer), PARAM(stk, FaceType), PARAM(stk, Level), PARAM(esi, pLockedRect), PARAM(eax, pRect), PARAM(stk, Flags))),
                         SYM_SIG(2048)),
};

// ******************************************************************
// * D3D8LTCG_OOVPA_COUNT
// ******************************************************************
#define D3D8LTCG_OOVPA_COUNT XBSDB_ARRAY_SIZE(D3D8LTCG_OOVPA)

#endif

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
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2017 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// Titles which did compiled with full libary version
//   [LibV] Title Name                       |  Verify   |   Comments
//-----------------------------------------------------------------------
// * [3925] Nascar Heat 2002                 |    20%    | Only verified an actually used library.
// * [4039] NBA 2K2                          |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4432] Bruce Lee                        |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4627] Battle Engine Aquila             |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4928] Shin Megami Tensei - Nine        |   100%    | Only has 80% of the library compiled with xbe build.
// * [5233] Midtown Madness 3                |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [5455] Freaky Flyers                    |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [5659] Ninja Gaiden                     |   100%    | With Intergrated Hotfixes. Only has a few library.
// * [5849] Grand Theft Auto - San Andreas   |   100%    | Only has 50%-ish of the library compiled with xbe build.

// * About the number of OOVPA
//   * 1024 and 1xxx - Cmpatible with known functions probably.
//   * 2028 and 2xxx - Remade by Link-time Code Generation, will not work with known functions.

#ifndef D3D8LTCG_OOVPA_INL
#define D3D8LTCG_OOVPA_INL

#include "../OOVPA.h"

#include "D3D8LTCG/3911.inl"
#include "D3D8LTCG/4039.inl"
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

    REGISTER_OOVPAS(D3D_MakeRequestedSpace_8, 1036), // NOTE: OOVPA is in 5849. In used by (5849) Manhunt title
    REGISTER_OOVPAS(D3D_MakeRequestedSpace, 2048),
    REGISTER_OOVPAS(D3D_SetFence, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3D_BlockOnTime, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3D_BlockOnTime_4, 2048, 2060),
    REGISTER_OOVPAS(D3DResource_AddRef, 3911),

    REGISTER_OOVPAS(CMiniport_InitHardware, 1024),
    REGISTER_OOVPAS(D3DCubeTexture_GetCubeMapSurface2, 1024),
    REGISTER_OOVPAS(D3DDevice_Begin, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_BeginPush, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_BeginPushBuffer, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_BeginPushBuffer_0, 2048, 2060),
    REGISTER_OOVPAS(D3DDevice_BeginVisibilityTest, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_BlockUntilVerticalBlank, 1024),
    REGISTER_OOVPAS(D3DDevice_Clear, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_CopyRects, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_CreatePixelShader, 1024),
    REGISTER_OOVPAS(D3DDevice_CreateTexture, 1024),
    REGISTER_OOVPAS(D3DDevice_CreateTexture2, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_CreateVertexShader, 1024),
    REGISTER_OOVPAS(D3DDevice_DeletePixelShader_0, 2024),
    REGISTER_OOVPAS(D3DDevice_DeleteStateBlock, 1024),
    REGISTER_OOVPAS(D3DDevice_DeleteVertexShader_0, 2024, 2036),
    REGISTER_OOVPAS(D3DDevice_DrawIndexedVertices, 1024),
    REGISTER_OOVPAS(D3DDevice_DrawIndexedVerticesUP, 1024, 1036, 1048, 1060, 1072),
    REGISTER_OOVPAS(D3DDevice_DrawVertices, 1024),
    REGISTER_OOVPAS(D3DDevice_DrawVertices_4, 2048),
    REGISTER_OOVPAS(D3DDevice_DrawVertices_8, 2024, 2048),
    REGISTER_OOVPAS(D3DDevice_DrawVerticesUP, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_DrawVerticesUP_12, 2024),
    REGISTER_OOVPAS(D3DDevice_EnableOverlay_0, 2048),
    REGISTER_OOVPAS(D3DDevice_End, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_EndPushBuffer, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_EndVisibilityTest, 1024),
    REGISTER_OOVPAS(D3DDevice_EndVisibilityTest_0, 2048),
    REGISTER_OOVPAS(D3DDevice_GetBackBuffer2, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_GetBackBuffer2_0, 2024, 2048),
    REGISTER_OOVPAS(D3DDevice_GetBackBuffer_8, 2048),
    REGISTER_OOVPAS(D3DDevice_GetDepthStencilSurface, 1024),
    REGISTER_OOVPAS(D3DDevice_GetDepthStencilSurface2, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_GetDisplayMode, 1024),
    REGISTER_OOVPAS(D3DDevice_GetRenderTarget2, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_GetTransform, 1024),
    REGISTER_OOVPAS(D3DDevice_GetViewportOffsetAndScale, 1024),
    REGISTER_OOVPAS(D3DDevice_GetViewportOffsetAndScale_0, 2024),
    REGISTER_OOVPAS(D3DDevice_IsBusy, 1024),
    REGISTER_OOVPAS(D3DDevice_IsFencePending, 1024),
    REGISTER_OOVPAS(D3DDevice_LightEnable, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_LightEnable_4, 2024, 2048),
    REGISTER_OOVPAS(D3DDevice_LoadVertexShaderProgram, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_LoadVertexShader_0, 2024, 2036, 2048),
    REGISTER_OOVPAS(D3DDevice_LoadVertexShader_4, 2024, 2036, 2048),
    REGISTER_OOVPAS(D3DDevice_MultiplyTransform_0, 2024),
    REGISTER_OOVPAS(D3DDevice_PersistDisplay, 1024, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_Present, 1024),
    REGISTER_OOVPAS(D3DDevice_Release, 1024),
    REGISTER_OOVPAS(D3DDevice_Reset, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_Reset_0, 2024),
    REGISTER_OOVPAS(D3DDevice_RunPushBuffer, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_RunPushBuffer_4, 2048),
    REGISTER_OOVPAS(D3DDevice_RunVertexStateShader_4, 2048),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShader, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShader_0, 2024, 2048, 2060, 2072, 2084),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShader_4, 2024, 2048, 2060),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShaderDirect, 1024),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShaderDirect_0, 2024, 2048),
    REGISTER_OOVPAS(D3DDevice_SetFlickerFilter_0, 2024),
    REGISTER_OOVPAS(D3DDevice_SetGammaRamp, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetIndices, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetIndices_4, 2024),
    REGISTER_OOVPAS(D3DDevice_SetLight, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_SetPalette, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetPalette_4, 2024),
    REGISTER_OOVPAS(D3DDevice_SetPixelShader, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetPixelShaderConstant, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetPixelShaderConstant_4, 2024),
    REGISTER_OOVPAS(D3DDevice_SetPixelShaderProgram, 1024),
    REGISTER_OOVPAS(D3DDevice_SetPixelShader_0, 2024, 2036, 2048, 2060, 2072),
    REGISTER_OOVPAS(D3DDevice_SetRenderStateNotInline, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderStateNotInline_0, 2048),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_BackFillMode, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_CullMode, 1045, 1049, 1052, 1053),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_EdgeAntiAlias, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_FillMode, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_FogColor, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_FrontFace, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_LineWidth, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_LogicOp, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleAntiAlias, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleMask, 1024, 1036, 1048, 1060, 1072),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleMode, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleRenderTargetMode, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_NormalizeNormals, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_OcclusionCullEnable, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_SampleAlpha, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_ShadowFunc, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilCullEnable, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilEnable, 1024, 1036, 1048, 1060, 1072, 1084),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilFail, 1024, 1036, 1048, 1060, 1072, 1084),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_TextureFactor, 1036),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_TwoSidedLighting, 1024, 1036, 1048, 1060, 1072, 1084),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_VertexBlend, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_YuvEnable, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_ZBias, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_ZEnable, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderTarget, 1024, 1036, 1048, 1072, 1084),
    REGISTER_OOVPAS(D3DDevice_SetRenderTarget_0, 2048),
    REGISTER_OOVPAS(D3DDevice_SetRenderTargetFast, 1024),
    REGISTER_OOVPAS(D3DDevice_SetScissors, 1024, 1036, 1048, 1060, 1072),
    REGISTER_OOVPAS(D3DDevice_SetScreenSpaceOffset, 1024),
    REGISTER_OOVPAS(D3DDevice_SetShaderConstantMode, 1024),
    REGISTER_OOVPAS(D3DDevice_SetShaderConstantMode_0, 2024, 2036, 2048, 2060, 2072, 2084, 2096, 2108, 2120, 2132, 2144, 2156),
    REGISTER_OOVPAS(D3DDevice_SetSoftDisplayFilter_0, 2048),
    REGISTER_OOVPAS(D3DDevice_SetStreamSource, 1039, 1044),
    REGISTER_OOVPAS(D3DDevice_SetStreamSource_4, 2058),
    REGISTER_OOVPAS(D3DDevice_SetStreamSource_8, 2040),
    REGISTER_OOVPAS(D3DDevice_SetTexture, 1024),
    REGISTER_OOVPAS(D3DDevice_SetTextureStageStateNotInline, 1024),
    REGISTER_OOVPAS(D3DDevice_SetTextureStageStateNotInline_0, 2024),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BorderColor, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BorderColor_0, 2024, 2036, 2048),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BorderColor_4, 2048, 2060),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BumpEnv, 1024),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BumpEnv_8, 2024),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_ColorKeyColor, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_ColorKeyColor_0, 2024, 2036, 2048),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_ColorKeyColor_4, 2048, 2060),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_TexCoordIndex, 1944, 1958),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_TexCoordIndex_0, 2039, 2058),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_TexCoordIndex_4, 2040, 2045, 2052, 2058),
    REGISTER_OOVPAS(D3DDevice_SetTexture_4, 2024, 2036),
    REGISTER_OOVPAS(D3DDevice_SetTile_0, 2024, 2036, 2048, 2060, 2072),
    REGISTER_OOVPAS(D3DDevice_SetTransform, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_SetTransform_0, 2024, 2048, 2060, 2072, 2084),
    REGISTER_OOVPAS(D3DDevice_SetVertexData2f, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData2s, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4f, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4f_16, 2024, 2036, 2048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4s, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4ub, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexDataColor, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetVertexShader, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant, 1024),
    REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstantNotInline_0, 2048),
    REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant_8, 2024),
    REGISTER_OOVPAS(D3DDevice_SetVertexShaderInput, 1024),
    REGISTER_OOVPAS(D3DDevice_SetVertexShader_0, 2024, 2036),
    REGISTER_OOVPAS(D3DDevice_SetViewport, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_Swap, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_Swap_0, 2024, 2036),
    REGISTER_OOVPAS(D3DDevice_UpdateOverlay, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_UpdateOverlay_16, 2048),
    REGISTER_OOVPAS(D3DPalette_Lock2, 1024),
    REGISTER_OOVPAS(D3DResource_GetType, 1024),
    REGISTER_OOVPAS(D3DResource_GetType_0, 2024),
    REGISTER_OOVPAS(D3DResource_Release, 1024, 1036),
    REGISTER_OOVPAS(D3DSurface_GetDesc, 1024),
    REGISTER_OOVPAS(D3DTexture_GetSurfaceLevel2, 1024),
    REGISTER_OOVPAS(D3DTexture_LockRect, 1024),
    REGISTER_OOVPAS(D3DVertexBuffer_Lock2, 1024),
    REGISTER_OOVPAS(D3D_BlockOnResource_0, 2024, 2036, 2048, 2060),
    REGISTER_OOVPAS(D3D_CommonSetRenderTarget, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3D_KickOffAndWaitForIdle2, 1024, 1036, 1048),
    REGISTER_OOVPAS(Direct3D_CreateDevice, 1024, 1036),
    REGISTER_OOVPAS(Direct3D_CreateDevice_16, 2024, 2036, 2048),
    REGISTER_OOVPAS(Direct3D_CreateDevice_4, 2048, 2060),
    REGISTER_OOVPAS(Get2DSurfaceDesc, 1024),
    REGISTER_OOVPAS(Get2DSurfaceDesc_0, 2024, 2036),
    REGISTER_OOVPAS(Get2DSurfaceDesc_4, 2048),
    REGISTER_OOVPAS(Lock3DSurface_16, 2048),
    REGISTER_OOVPAS(Lock2DSurface_16, 2048),
};

// ******************************************************************
// * D3D8LTCG_OOVPA_COUNT
// ******************************************************************
#define D3D8LTCG_OOVPA_COUNT XBSDB_ARRAY_SIZE(D3D8LTCG_OOVPA)

#endif

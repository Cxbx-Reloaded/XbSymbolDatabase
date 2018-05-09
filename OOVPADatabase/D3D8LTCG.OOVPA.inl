// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG.OOVPA.inl
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

#include "D3D8LTCG.1.0.3911.inl"
#include "D3D8LTCG.1.0.4039.inl"
#include "D3D8LTCG.1.0.4432.inl"
#include "D3D8LTCG.1.0.4531.inl"
#include "D3D8LTCG.1.0.4627.inl"
#include "D3D8LTCG.1.0.4721.inl"
#include "D3D8LTCG.1.0.4928.inl"
#include "D3D8LTCG.1.0.5028.inl"
#include "D3D8LTCG.1.0.5120.inl"
#include "D3D8LTCG.1.0.5233.inl"
#include "D3D8LTCG.1.0.5344.inl"
#include "D3D8LTCG.1.0.5455.inl"
#include "D3D8LTCG.1.0.5788.inl"
#include "D3D8LTCG.1.0.5849.inl"

// ******************************************************************
// * D3D8LTCG_OOVPA
// ******************************************************************
OOVPATable D3D8LTCG_OOVPAV2[] = {

	REGISTER_OOVPAS(D3D_MakeRequestedSpace, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3D_MakeRequestedSpace, 2048),
	REGISTER_OOVPAS(D3D_SetFence, 1024, 1036, 1048, 1060),
	REGISTER_OOVPAS(D3D_BlockOnTime, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3D_BlockOnTime_4, 2048, 2060),
	REGISTER_OOVPAS(D3DResource_AddRef, 3911),

	REGISTER_OOVPAS(CMiniport_InitHardware, 1024),
	REGISTER_OOVPAS(D3DCubeTexture_GetCubeMapSurface2, 1024),
	REGISTER_OOVPAS(D3DDevice_Begin, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3DDevice_BeginPush, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3DDevice_BeginPushBuffer, 1024),
	REGISTER_OOVPAS(D3DDevice_BeginVisibilityTest, 1024, 1048),
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
	REGISTER_OOVPAS(D3DDevice_LoadVertexShaderProgram, 1024, 1036),
	REGISTER_OOVPAS(D3DDevice_LoadVertexShaderProgram_4, 2048),
	REGISTER_OOVPAS(D3DDevice_LoadVertexShader_0, 2024, 2036),
	REGISTER_OOVPAS(D3DDevice_LoadVertexShader_4, 2024, 2048),
	REGISTER_OOVPAS(D3DDevice_MultiplyTransform_0, 2024),
	REGISTER_OOVPAS(D3DDevice_PersistDisplay, 1024, 1048, 1060),
	REGISTER_OOVPAS(D3DDevice_Present, 1024),
	REGISTER_OOVPAS(D3DDevice_Release, 1024),
	REGISTER_OOVPAS(D3DDevice_Reset, 1024, 1036),
	REGISTER_OOVPAS(D3DDevice_Reset_0, 2024),
	REGISTER_OOVPAS(D3DDevice_RunPushBuffer, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3DDevice_RunVertexStateShader_4, 2048),
	REGISTER_OOVPAS(D3DDevice_SelectVertexShader, 1024, 1036),
	REGISTER_OOVPAS(D3DDevice_SelectVertexShader_0, 2024, 2048, 2060),
	REGISTER_OOVPAS(D3DDevice_SelectVertexShader_4, 2024, 2048, 2060),
	REGISTER_OOVPAS(D3DDevice_SelectVertexShaderDirect_0, 2048),
	REGISTER_OOVPAS(D3DDevice_SetFlickerFilter_0, 2024),
	REGISTER_OOVPAS(D3DDevice_SetGammaRamp, 1024),
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
	REGISTER_OOVPAS(D3DDevice_SetRenderState_DoNotCullUncompressed, 1024),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_Dxt1NoiseEnable, 1024, 1036),
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
	REGISTER_OOVPAS(D3DDevice_SetRenderState_RopZCmpAlwaysRead, 1024),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_RopZRead, 1024),
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
	REGISTER_OOVPAS(D3DDevice_SetRenderTarget, 1024, 1036, 1048, 1060, 1072, 1084),
	REGISTER_OOVPAS(D3DDevice_SetRenderTargetFast, 1024, 1036),
	REGISTER_OOVPAS(D3DDevice_SetScissors, 1024, 1036, 1048, 1060, 1072),
	REGISTER_OOVPAS(D3DDevice_SetScreenSpaceOffset, 1024),
	REGISTER_OOVPAS(D3DDevice_SetShaderConstantMode, 1024),
	REGISTER_OOVPAS(D3DDevice_SetShaderConstantMode_0, 2048),
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
	REGISTER_OOVPAS(D3DDevice_SetVertexData4f_16, 2024, 2036),
	REGISTER_OOVPAS(D3DDevice_SetVertexData4s, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3DDevice_SetVertexData4ub, 1024, 1036, 1048),
	REGISTER_OOVPAS(D3DDevice_SetVertexShader, 1024, 1036),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant, 1024),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstantNotInline_0, 2048),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant_8, 2024),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderInput, 1024),
	REGISTER_OOVPAS(D3DDevice_SetVertexShader_0, 2024, 2036),
	REGISTER_OOVPAS(D3DDevice_SetViewport, 1024, 1036, 1048, 1060),
	REGISTER_OOVPAS(D3DDevice_Swap, 1024, 1036),
	REGISTER_OOVPAS(D3DDevice_Swap_0, 2024, 2036),
	REGISTER_OOVPAS(D3DDevice_UpdateOverlay, 1024, 1036, 1048),
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
	REGISTER_OOVPAS(D3D_CommonSetRenderTarget, 1024),
	REGISTER_OOVPAS(D3D_KickOffAndWaitForIdle2, 1024, 1036, 1048),
	REGISTER_OOVPAS(Direct3D_CreateDevice, 1024, 1036),
	REGISTER_OOVPAS(Direct3D_CreateDevice_16, 2024, 2036, 2048),
	REGISTER_OOVPAS(Direct3D_CreateDevice_4, 2048, 2060),
	REGISTER_OOVPAS(Get2DSurfaceDesc, 1024),
	REGISTER_OOVPAS(Get2DSurfaceDesc_0, 2024, 2036),
	REGISTER_OOVPAS(Get2DSurfaceDesc_4, 2048),
	REGISTER_OOVPAS(Lock3DSurface_16, 2048),
	REGISTER_OOVPAS(Lock2DSurface_16, 2048),

// *********************** Copy from D3D8.OOVPA.inl *****************
	REGISTER_OOVPAS(CMiniport_CreateCtxDmaObject, 3911, 4034),
	REGISTER_OOVPAS(CMiniport_InitHardware, 3911, 4034, 5455),
	REGISTER_OOVPAS(CMiniport_IsFlipPending, 3911, 4242, 4627, 4928),
	REGISTER_OOVPAS(D3DBaseTexture_GetLevelCount, 3911),
	REGISTER_OOVPAS(D3DCubeTexture_GetCubeMapSurface, 3911, 4627), // Called D3DCubeTexture_GetCubeMapSurface2 (from 4627's comment) NOTE: Use D3DCubeTexture_GetCubeMapSurface2 for 4627 and above
	REGISTER_OOVPAS(D3DCubeTexture_GetCubeMapSurface2, 4627),
	REGISTER_OOVPAS(D3DCubeTexture_LockRect, 3911), // Just calls Lock2DSurface (from 4134, 4432's comment)
	REGISTER_OOVPAS(D3DDevice_AddRef, 3911, 4039, 4134, 4242, 4627, 5028, 5344, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_ApplyStateBlock, 3911, 4627),
	REGISTER_OOVPAS(D3DDevice_Begin, 3911, 4039),
	REGISTER_OOVPAS(D3DDevice_BeginPush, 4531,4627, 5028),
	REGISTER_OOVPAS(D3DDevice_BeginPush2, 4134),
	REGISTER_OOVPAS(D3DDevice_BeginPushBuffer, 3911, 4134), // Not implemented yet. (from 5788's comment)
	REGISTER_OOVPAS(D3DDevice_BeginStateBig, 5028),
	REGISTER_OOVPAS(D3DDevice_BeginStateBlock, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_BeginVisibilityTest, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_BlockOnFence, 3911),
	REGISTER_OOVPAS(D3DDevice_BlockUntilVerticalBlank, 3911, 4034, 4134, 4242, 4432, 4627, 5028, 5233, 5344, 5455, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_CaptureStateBlock, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_Clear, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_CopyRects, 3911, 4034, 4627, 5120),
	REGISTER_OOVPAS(D3DDevice_CreateCubeTexture, 3911, 4627),
	REGISTER_OOVPAS(D3DDevice_CreateImageSurface, 3911, 4034, 4627),//TODO 4721,4928 (from 4627's comment)
	REGISTER_OOVPAS(D3DDevice_CreateIndexBuffer, 3911, 4627), // TODO: This needs to be verified on 4361
	REGISTER_OOVPAS(D3DDevice_CreateIndexBuffer2, 4627, 5344),
	REGISTER_OOVPAS(D3DDevice_CreatePalette, 3911, 4627), // Called D3DDevice_CreatePalette2 (from 4627's comment) NOTE: Use D3DDevice_CreatePalette2 for 4627 and above
	REGISTER_OOVPAS(D3DDevice_CreatePalette2, 4627, 5344, 5455),
	REGISTER_OOVPAS(D3DDevice_CreatePixelShader, 3911, 5344),
	REGISTER_OOVPAS(D3DDevice_CreateStateBlock, 3911),
	REGISTER_OOVPAS(D3DDevice_CreateTexture, 3911, 4627),// Called D3DDevice_CreateTexture2 (from 4627's comment) NOTE: Use D3DDevice_CreateTexture2 for 4627 and above
	REGISTER_OOVPAS(D3DDevice_CreateTexture2, 4627, 4831), // Was 4627 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_CreateVertexBuffer, 3911, 4627),
	REGISTER_OOVPAS(D3DDevice_CreateVertexBuffer2, 4627, 5344, 5455),
	REGISTER_OOVPAS(D3DDevice_CreateVertexShader, 3911),
	REGISTER_OOVPAS(D3DDevice_CreateVolumeTexture, 3911, 4627),
	REGISTER_OOVPAS(D3DDevice_DeletePatch, 3911), // (TODO) (from 4034's comment)
	REGISTER_OOVPAS(D3DDevice_DeletePixelShader, 3911, 5344),
	REGISTER_OOVPAS(D3DDevice_DeleteStateBlock, 3911),
	REGISTER_OOVPAS(D3DDevice_DeleteVertexShader, 3911, 5344),
	REGISTER_OOVPAS(D3DDevice_DrawIndexedVertices, 3911, 4034, 4627, 5028),
	REGISTER_OOVPAS(D3DDevice_DrawIndexedVerticesUP, 3911, 4039, 5028, 5344),
	REGISTER_OOVPAS(D3DDevice_DrawRectPatch, 3911), // TODO: Unused? (from 4034's comment)
	REGISTER_OOVPAS(D3DDevice_DrawTriPatch, 3911),
	REGISTER_OOVPAS(D3DDevice_DrawVertices, 3911),
	REGISTER_OOVPAS(D3DDevice_DrawVerticesUP, 3911, 4039, 5344),
	REGISTER_OOVPAS(D3DDevice_EnableOverlay, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_End, 3911, 4039, 5344),
	REGISTER_OOVPAS(D3DDevice_EndPush, 4134), // Was 4627 (from 5233's comment)
	REGISTER_OOVPAS(D3DDevice_EndPushBuffer, 3911), // Not implemented yet. (from 5788's comment)
	REGISTER_OOVPAS(D3DDevice_EndStateBlock, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_EndVisibilityTest, 3911),
	REGISTER_OOVPAS(D3DDevice_FlushVertexCache, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_GetBackBuffer, 3911, 4034, 4134, 4627), // Called D3DDevice_GetBackBuffer2 (from 4627's comment) NOTE: Use D3DDevice_GetBackBuffer2 for 4627 and above
	REGISTER_OOVPAS(D3DDevice_GetBackBuffer2, 4627), // 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_GetBackMaterial, 3911, 4134, 4627, 5344, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_GetCreationParameters, 3911),
	REGISTER_OOVPAS(D3DDevice_GetDepthStencilSurface, 3911, 4627), // Called D3DDevice_GetDepthStencilSurface2 (from 4627's comment) NOTE: Use D3DDevice_GetDepthStencilSurface2 for 4627 and above
	REGISTER_OOVPAS(D3DDevice_GetDepthStencilSurface2, 4627),
	REGISTER_OOVPAS(D3DDevice_GetDeviceCaps, 3911),
	REGISTER_OOVPAS(D3DDevice_GetDisplayFieldStatus, 3911),
	REGISTER_OOVPAS(D3DDevice_GetDisplayMode, 3911, 4039),
	REGISTER_OOVPAS(D3DDevice_GetGammaRamp, 3911),
	REGISTER_OOVPAS(D3DDevice_GetLight, 3911),
	REGISTER_OOVPAS(D3DDevice_GetLightEnable, 3911, 5344),
	REGISTER_OOVPAS(D3DDevice_GetMaterial, 3911, 4134, 4627, 5344, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_GetModelView, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_GetOverlayUpdateStatus, 3911),
	REGISTER_OOVPAS(D3DDevice_GetPersistedSurface2, 4928), // For only on Unreal Championship (from 4627's comment)
	REGISTER_OOVPAS(D3DDevice_GetPixelShader, 3911, 4039, 4134, 5028, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_GetProjectionViewportMatrix, 3911, 4134, 4627, 5344, 5558), // For 5455 (from 5558's comment)
	REGISTER_OOVPAS(D3DDevice_GetPushBufferOffset, 3911, 4627),//TODO 4831 (from 4627's comment)
	REGISTER_OOVPAS(D3DDevice_GetRenderTarget, 3911, 4627), // Called D3DDevice_GetRenderTarget2 (from 4627's comment) NOTE: Use D3DDevice_GetRenderTarget2 for 4627 and above
	REGISTER_OOVPAS(D3DDevice_GetRenderTarget2, 4627),
	REGISTER_OOVPAS(D3DDevice_GetScissors, 3911),
	REGISTER_OOVPAS(D3DDevice_GetShaderConstantMode, 3911, 4134, 4627, 5028, 5344, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_GetStreamSource2, 4627),
	REGISTER_OOVPAS(D3DDevice_GetTexture2, 3911, 4134, 4627, 5344, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_GetTile, 3911, 5455),
	REGISTER_OOVPAS(D3DDevice_GetTransform, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_GetVertexShader, 3911, 4039, 4134, 5028, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_GetVertexShaderConstant, 3911, 4039, 5028),
	REGISTER_OOVPAS(D3DDevice_GetVertexShaderDeclaration, 3911),
	REGISTER_OOVPAS(D3DDevice_GetVertexShaderFunction, 3911),
	REGISTER_OOVPAS(D3DDevice_GetVertexShaderInput, 3911),
	REGISTER_OOVPAS(D3DDevice_GetVertexShaderSize, 3911),
	REGISTER_OOVPAS(D3DDevice_GetVertexShaderType, 3911),
	REGISTER_OOVPAS(D3DDevice_GetViewport, 3911, 5455), // Was 4627 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_GetViewportOffsetAndScale, 4432),
	REGISTER_OOVPAS(D3DDevice_GetVisibilityTestResult, 3911, 5233),
	REGISTER_OOVPAS(D3DDevice_InsertCallback, 3911, 4134, 5028),
	REGISTER_OOVPAS(D3DDevice_InsertFence, 3911),
	REGISTER_OOVPAS(D3DDevice_IsBusy, 3911, 5028),
	REGISTER_OOVPAS(D3DDevice_IsFencePending, 3911, 4039, 5028),
	REGISTER_OOVPAS(D3DDevice_KickOff, 3911, 4034, 4531, 5028, 5455),
	REGISTER_OOVPAS(D3DDevice_KickPushBuffer, 3911),
	REGISTER_OOVPAS(D3DDevice_LazySetStateVB, 5028, 5558),
	REGISTER_OOVPAS(D3DDevice_LazySetStateUP, 5028, 5558),
	REGISTER_OOVPAS(D3DDevice_LightEnable, 3911, 5344), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_LoadVertexShader, 3911, 4034, 4627, 5028),
	REGISTER_OOVPAS(D3DDevice_LoadVertexShaderProgram, 3911),
	REGISTER_OOVPAS(D3DDevice_MakeSpace, 4134),
	REGISTER_OOVPAS(D3DDevice_PersistDisplay, 3911, 4039, 4627, 4831, 5455, 5558),
	REGISTER_OOVPAS(D3DDevice_Present, 3911),
	REGISTER_OOVPAS(D3DDevice_PrimeVertexCache, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_Release, 3911),
	REGISTER_OOVPAS(D3DDevice_Reset, 3911),
	REGISTER_OOVPAS(D3DDevice_RunPushBuffer, 3911, 4039, 4627, 5120, 5558), // for 5455 (from 5558's comment)
	REGISTER_OOVPAS(D3DDevice_RunVertexStateShader, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_SelectVertexShader, 3911, 4034, 5455),
	REGISTER_OOVPAS(D3DDevice_SelectVertexShaderDirect, 4361),
	REGISTER_OOVPAS(D3DDevice_SetBackBufferScale, 4134),
	REGISTER_OOVPAS(D3DDevice_SetBackMaterial, 3911, 4134, 4627, 5344, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_SetDepthClipPlanes, 4432),
	REGISTER_OOVPAS(D3DDevice_SetFlickerFilter, 3911, 4034, 4134),
	REGISTER_OOVPAS(D3DDevice_SetGammaRamp, 3911, 4627),
	REGISTER_OOVPAS(D3DDevice_SetIndices, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetLight, 3911, 5344),
	REGISTER_OOVPAS(D3DDevice_SetMaterial, 3911, 4034, 4134, 4627, 5344, 5558, 5788), // Was 4627 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetModelView, 3911, 4134, 4627),
	REGISTER_OOVPAS(D3DDevice_SetPalette, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetPixelShader, 3911, 4034, 4627),
	REGISTER_OOVPAS(D3DDevice_SetPixelShaderConstant, 3911, 4831),
	REGISTER_OOVPAS(D3DDevice_SetPixelShaderProgram, 3911),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_BackFillMode, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_CullMode, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_Deferred, 3911),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_DoNotCullUncompressed, 3911),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_Dxt1NoiseEnable, 3911, 4034, 4627), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetRenderState_EdgeAntiAlias, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_FillMode, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_FogColor, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_FrontFace, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_LineWidth, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_LogicOp, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleAntiAlias, 3911, 4034, 4627),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleMask, 3911, 4034, 4627),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleMode, 3925, 4034, 4134, 4627, 5233),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleRenderTargetMode, 4034), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetRenderState_NormalizeNormals, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_OcclusionCullEnable, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_PSTextureModes, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_RopZCmpAlwaysRead, 3911),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_RopZRead, 3911),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_SampleAlpha, 4627),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_ShadowFunc, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_Simple, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilCullEnable, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilEnable, 3911, 4034, 5849),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilFail, 3911, 4034, 5849),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_TextureFactor, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_TwoSidedLighting, 3911, 4034, 5344), // Beware of the typo... (from 4627's comment)
	REGISTER_OOVPAS(D3DDevice_SetRenderState_VertexBlend, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_YuvEnable, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_ZBias, 3911),
	REGISTER_OOVPAS(D3DDevice_SetRenderState_ZEnable, 3911, 4034, 4134, 4432),
	REGISTER_OOVPAS(D3DDevice_SetRenderTarget, 3911, 3948, 4039, 4627, 5344, 5455),
	REGISTER_OOVPAS(D3DDevice_SetRenderTargetFast, 5233),
	REGISTER_OOVPAS(D3DDevice_SetScissors, 3911, 5344, 5558), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetScreenSpaceOffset, 4034, 5455), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetShaderConstantMode, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetSoftDisplayFilter, 3911, 4034, 4134),
	REGISTER_OOVPAS(D3DDevice_SetStateUP, 3911, 4034, 4134),
	REGISTER_OOVPAS(D3DDevice_SetStateVB, 3911, 4034, 4134),
	REGISTER_OOVPAS(D3DDevice_SetStipple, 4627),
	REGISTER_OOVPAS(D3DDevice_SetStreamSource, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetSwapCallback, 4134, 4242, 4432, 4627, 5028, 5233, 5344, 5455, 5558, 5788),
	REGISTER_OOVPAS(D3DDevice_SetTexture, 3911, 4034, 4361, 4831),
	REGISTER_OOVPAS(D3DDevice_SetTextureState_BorderColor, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetTextureState_BumpEnv, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetTextureState_ColorKeyColor, 3911, 4034),
	REGISTER_OOVPAS(D3DDevice_SetTextureState_TexCoordIndex, 3911, 4034, 4242, 4627),
	REGISTER_OOVPAS(D3DDevice_SetTile, 3911, 4034, 4627), // Then it has changed calls ?SetTileNoWait@D3D@@YGXKPBU_D3DTILE@@@Z in XDK 4627 and higher.
	REGISTER_OOVPAS(D3DDevice_SetTransform, 3911, 4034, 5344, 5558), // Was 4134 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_MultiplyTransform, 3911, 4034), // TODO: Verify 4034 is correct
	REGISTER_OOVPAS(D3DDevice_SetVertexData2f, 3911, 4039), // Was 4627 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetVertexData2s, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_SetVertexData4f, 3911, 4039),
	REGISTER_OOVPAS(D3DDevice_SetVertexData4s, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_SetVertexData4ub, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_SetVertexDataColor, 3911, 4039),
	REGISTER_OOVPAS(D3DDevice_SetVertexShader, 3911, 4034, 4134, 5028, 5455),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant, 3911, 4034, 4627),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant1, 4627),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant1Fast, 4627),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant4, 4627),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstantNotInline, 4627, 5028, 5558),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstantNotInlineFast, 4627),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderInput, 3911, 4134),
	REGISTER_OOVPAS(D3DDevice_SetVertexShaderInputDirect, 4361),
	REGISTER_OOVPAS(D3DDevice_SetVerticalBlankCallback, 3911, 4039, 4134, 4242, 4432, 4627, 5028, 5233, 5344, 5455, 5558, 5788), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_SetViewport, 3911, 4034, 5344, 5455), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3DDevice_Swap, 4034, 4531, 4627),
	REGISTER_OOVPAS(D3DDevice_SwitchTexture, 3911),
	REGISTER_OOVPAS(D3DDevice_UpdateOverlay, 3911, 4531, 5233),
	REGISTER_OOVPAS(D3DPalette_Lock, 3911, 4531, 4627), // Called D3DPalette_Lock2 (from 4627's comment) NOTE: Use D3DPalette_Lock2 for 4627 and above
	REGISTER_OOVPAS(D3DPalette_Lock2, 4627),
	REGISTER_OOVPAS(D3DResource_AddRef, 3911),
	REGISTER_OOVPAS(D3DResource_BlockUntilNotBusy, 3911),
	REGISTER_OOVPAS(D3DResource_GetType, 3911, 4034), // Probably not even necessary... (from 3925's comment) // I forget why I had this in here... (from 5028's comment)
	REGISTER_OOVPAS(D3DResource_IsBusy, 3911, 4039),
	REGISTER_OOVPAS(D3DResource_Register, 3911),
	REGISTER_OOVPAS(D3DResource_Release, 3911),
	REGISTER_OOVPAS(D3DSurface_GetDesc, 3911),
	REGISTER_OOVPAS(D3DSurface_LockRect, 3911),
	REGISTER_OOVPAS(D3DTexture_GetSurfaceLevel, 3911, 4627),
	REGISTER_OOVPAS(D3DTexture_GetSurfaceLevel2, 4627),
	REGISTER_OOVPAS(D3DTexture_LockRect, 3911),
	REGISTER_OOVPAS(D3DVertexBuffer_GetDesc, 3911),
	REGISTER_OOVPAS(D3DVertexBuffer_Lock, 3911, 4034, 4531, 4627),
	REGISTER_OOVPAS(D3DVertexBuffer_Lock2, 4627),
	REGISTER_OOVPAS(D3DVolumeTexture_LockBox, 3911), // Just calls Lock3DSurface (from 4134, 4432's comment)
	REGISTER_OOVPAS(D3D_AllocContiguousMemory, 3911, 5455), // Just calls MmAllocateContiguousMemory. Was PATCH (from 3925, 5788's comment)
	REGISTER_OOVPAS(D3D_BlockOnResource, 3911, 4034),
	REGISTER_OOVPAS(D3D_BlockOnTime, 3911, 4034, 4627, 5028, 5558),
	REGISTER_OOVPAS(D3D_CMiniport_GetDisplayCapabilities, 3911),
	REGISTER_OOVPAS(D3D_CheckDeviceFormat, 3911),
	REGISTER_OOVPAS(D3D_ClearStateBlockFlags, 3911),
	REGISTER_OOVPAS(D3D_CommonSetRenderTarget, 4627, 5028), // Used between 4627 to 5233 (from 5344's comment)
	REGISTER_OOVPAS(D3D_CreateStandAloneSurface, 4034),
	REGISTER_OOVPAS(D3D_EnumAdapterModes, 3911),
	REGISTER_OOVPAS(D3D_GetAdapterDisplayMode, 3911, 4627),
	REGISTER_OOVPAS(D3D_GetAdapterIdentifier, 3911),
	REGISTER_OOVPAS(D3D_GetAdapterModeCount, 3911),
	REGISTER_OOVPAS(D3D_GetDeviceCaps, 3911),
	REGISTER_OOVPAS(D3D_KickOffAndWaitForIdle, 3911, 4034, 4627, 5028),
	REGISTER_OOVPAS(D3D_LazySetPointParams, 3911, 4034),
	REGISTER_OOVPAS(D3D_RecordStateBlock, 3911),
	REGISTER_OOVPAS(D3D_SetCommonDebugRegisters, 3911),
	REGISTER_OOVPAS(D3D_SetFence, 3911, 4034, 4134, 5028, 5558),
	REGISTER_OOVPAS(D3D_SetPushBufferSize, 3911),
	REGISTER_OOVPAS(D3D_SetTileNoWait, 4627, 5455),
	REGISTER_OOVPAS(Direct3D_CheckDeviceMultiSampleType, 3911),
	REGISTER_OOVPAS(Direct3D_CreateDevice, 3911, 5028),
	REGISTER_OOVPAS(Get2DSurfaceDesc, 3911, 4034), // Was 5233 (from 5344's comment)
	REGISTER_OOVPAS(Lock2DSurface, 3911),
	REGISTER_OOVPAS(Lock3DSurface, 3911),
	REGISTER_OOVPAS(D3D_MakeRequestedSpace, 4134, 5028, 5558),
	REGISTER_OOVPAS(XMETAL_StartPush, 3911),
	REGISTER_OOVPAS(IDirect3DVertexBuffer8_Lock, 4627),
};

// ******************************************************************
// * D3D8LTCG_OOVPA_COUNT
// ******************************************************************
#define D3D8LTCG_OOVPA_COUNT OOVPA_TABLE_COUNT(D3D8LTCG_OOVPAV2)

#endif

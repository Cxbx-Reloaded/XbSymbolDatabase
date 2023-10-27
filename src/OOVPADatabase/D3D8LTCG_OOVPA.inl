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

    REGISTER_OOVPAS_BIND_XREF(D3D_CreateTexture_28__LTCG_edx8_edi9, D3D_CreateTexture, 4039), // Final generic OOVPA: 4039; Removed: 4627 // See note for details.
    REGISTER_OOVPAS_BIND_XREF(D3D_MakeRequestedSpace_8, D3D_MakeRequestedSpace, 1036), // NOTE: OOVPA is in 5849. In used by (5849) Manhunt title
    REGISTER_OOVPAS_BIND_XREF(D3D_MakeRequestedSpace_4__LTCG_eax_RequestedSpace, D3D_MakeRequestedSpace, 2048),
    REGISTER_OOVPAS(D3D_SetFence, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3D_BlockOnTime, 1024, 1036, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3D_BlockOnTime_4, D3D_BlockOnTime, 2048, 2060),

    REGISTER_OOVPAS_D3D(CMiniport_InitHardware, 1024),
    REGISTER_OOVPAS(D3DCubeTexture_GetCubeMapSurface2, 1024),
    REGISTER_OOVPAS(D3DCubeTexture_GetCubeMapSurface, 1024),
    REGISTER_OOVPAS(D3DDevice_Begin, 1024, 1036, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_BeginPush_4, D3DDevice_BeginPush, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_BeginPushBuffer, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_BeginPushBuffer_0, D3DDevice_BeginPushBuffer, 2048, 2060),
    REGISTER_OOVPAS(D3DDevice_BeginVisibilityTest, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_BlockUntilVerticalBlank, 1024), // NOTE: NASCAR Heat 2002 reveal this function is inlined, need some sort of indicator which is inline or not.
    REGISTER_OOVPAS(D3DDevice_Clear, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_CopyRects, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_CreateCubeTexture, 4432),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_CreateCubeTexture_4__LTCG_eax1_edx3_ecx4_edi6, D3DDevice_CreateCubeTexture, 4039),
    REGISTER_OOVPAS(D3DDevice_CreatePixelShader, 1024),
    REGISTER_OOVPAS(D3DDevice_CreateTexture, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_CreateTexture_8__LTCG_edx3_ecx4_eax5_edi7, D3DDevice_CreateTexture, 4039),
    REGISTER_OOVPAS(D3DDevice_CreateTexture2, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_CreateVertexShader, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_CreateVolumeTexture_12__LTCG_edx4_ecx5_eax6_edi8, D3DDevice_CreateVolumeTexture, 4039),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_DeletePixelShader_0, D3DDevice_DeletePixelShader, 2024),
    REGISTER_OOVPAS(D3DDevice_DeleteStateBlock, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_DeleteVertexShader_0, D3DDevice_DeleteVertexShader, 3911, 5344), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(D3DDevice_DrawIndexedVertices, 1024, 1036, 1037),
    REGISTER_OOVPAS(D3DDevice_DrawIndexedVerticesUP, 1024, 1036, 1048), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(D3DDevice_DrawVertices, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_DrawVertices_4__LTCG_ecx2_eax3, D3DDevice_DrawVertices, 2024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_DrawVertices_8__LTCG_eax3, D3DDevice_DrawVertices, 4039),
    REGISTER_OOVPAS(D3DDevice_DrawVerticesUP, 1024, 1048), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_DrawVerticesUP_12__LTCG_ebx3, D3DDevice_DrawVerticesUP, 2024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_EnableOverlay_0, D3DDevice_EnableOverlay, 2048),
    REGISTER_OOVPAS(D3DDevice_End, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_EndPushBuffer, 1024), // Final generic OOVPA: 4432?; Removed: 0
    REGISTER_OOVPAS(D3DDevice_EndVisibilityTest, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_EndVisibilityTest_0, D3DDevice_EndVisibilityTest, 2048),
    REGISTER_OOVPAS(D3DDevice_GetBackBuffer2, 4626), // Due to non-LTCG signature conflict, lowered down by one number.
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_GetBackBuffer_8, D3DDevice_GetBackBuffer, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_GetBackBuffer2_0__LTCG_eax1, D3DDevice_GetBackBuffer2, 4627, 5233),
    REGISTER_OOVPAS(D3DDevice_GetDepthStencilSurface, 1024),
    REGISTER_OOVPAS(D3DDevice_GetDepthStencilSurface2, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_GetDisplayMode, 1024),
    REGISTER_OOVPAS(D3DDevice_GetRenderTarget2, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_GetTransform, 1024),
    REGISTER_OOVPAS(D3DDevice_GetViewportOffsetAndScale, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_GetViewportOffsetAndScale_0, D3DDevice_GetViewportOffsetAndScale, 2024),
    REGISTER_OOVPAS(D3DDevice_IsBusy, 1024),
    REGISTER_OOVPAS(D3DDevice_IsFencePending, 1024),
    REGISTER_OOVPAS(D3DDevice_LightEnable, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_LightEnable_4, D3DDevice_LightEnable, 2024, 2048),
    REGISTER_OOVPAS(D3DDevice_LoadVertexShaderProgram, 1024, 1036, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_LoadVertexShader_0__LTCG_eax_Address_ecx_Handle, D3DDevice_LoadVertexShader, 2024, 2036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_LoadVertexShader_0__LTCG_eax_Address_edx_Handle, D3DDevice_LoadVertexShader, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_LoadVertexShader_4, D3DDevice_LoadVertexShader, 2024, 2036, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_MultiplyTransform_0, D3DDevice_MultiplyTransform, 2024),
    REGISTER_OOVPAS(D3DDevice_PersistDisplay, 1024, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_Present, 1024),
    REGISTER_OOVPAS(D3DDevice_Reset, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_Reset_0__LTCG_edi1, D3DDevice_Reset, 2024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_Reset_0__LTCG_ebx1, D3DDevice_Reset, 2024),
    REGISTER_OOVPAS(D3DDevice_RunPushBuffer, 1024, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_RunPushBuffer_4, D3DDevice_RunPushBuffer, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_RunVertexStateShader_4, D3DDevice_RunVertexStateShader, 2048),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShader, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SelectVertexShader_0__LTCG_eax1_ebx2, D3DDevice_SelectVertexShader, 2024, 2048, 2060, 2061, 2062, 2072, 2084),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SelectVertexShader_4__LTCG_eax1, D3DDevice_SelectVertexShader, 3911, 4039, 4531, 4627),
    REGISTER_OOVPAS(D3DDevice_SelectVertexShaderDirect, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SelectVertexShaderDirect_0, D3DDevice_SelectVertexShaderDirect, 2024, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetFlickerFilter_0, D3DDevice_SetFlickerFilter, 2024),
    REGISTER_OOVPAS(D3DDevice_SetGammaRamp, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetIndices, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetIndices_4, D3DDevice_SetIndices, 2024),
    REGISTER_OOVPAS(D3DDevice_SetLight, 1024, 1048),
    REGISTER_OOVPAS(D3DDevice_SetPalette, 1024, 1036, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetPalette_4, D3DDevice_SetPalette, 2024),
    REGISTER_OOVPAS(D3DDevice_SetPixelShader, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetPixelShaderConstant, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetPixelShaderConstant_4, D3DDevice_SetPixelShaderConstant, 2024),
    REGISTER_OOVPAS(D3DDevice_SetPixelShaderProgram, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetPixelShader_0__LTCG_eax_handle, D3DDevice_SetPixelShader, 2024, 2036, 2048, 2060, 2072),
    REGISTER_OOVPAS_M(D3DDevice_SetRenderStateInline__GenericFragment, 3911, 4039), // Final generic OOVPA: 4039?; Removed: 0 // NOTE: see notes from 4039 sig.
    //REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetRenderStateNotInline_0__LTCG_esi1_edi2, D3DDevice_SetRenderStateNotInline, 2048), // NOTE: Signature is unlikely correct and need correction or removal (maybe)
    REGISTER_OOVPAS(D3DDevice_SetRenderState_BackFillMode, 1024, 1036),
    REGISTER_OOVPAS_C(D3DDevice_SetRenderState_CullMode, 1045, 1049, 1052, 1053),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_EdgeAntiAlias, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS_M(D3DDevice_SetRenderState_FillMode, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_FogColor, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_FrontFace, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_LineWidth, 1024),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_LogicOp, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleAntiAlias, 1024, 1060), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(D3DDevice_SetRenderState_MultiSampleMask, 1024, 1060), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(D3DDevice_SetRenderState_NormalizeNormals, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_SampleAlpha, 1024), // Final generic OOVPA: 4627; Removed: 0
    REGISTER_OOVPAS(D3DDevice_SetRenderState_ShadowFunc, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilEnable, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_StencilFail, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_TextureFactor, 1036),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_TwoSidedLighting, 1024, 1036, 1060, 1061, 1084),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_VertexBlend, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_ZBias, 1024, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderState_ZEnable, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_SetRenderTarget, 1024, 1036, 1048, 1072, 1084),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetRenderTarget_0, D3DDevice_SetRenderTarget, 2048),
    REGISTER_OOVPAS(D3DDevice_SetRenderTargetFast, 1024),
    REGISTER_OOVPAS(D3DDevice_SetScissors, 1024, 1036, 1048, 1060, 1072),
    REGISTER_OOVPAS(D3DDevice_SetScreenSpaceOffset, 1024), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(D3DDevice_SetShaderConstantMode, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetShaderConstantMode_0__LTCG_eax1, D3DDevice_SetShaderConstantMode, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetSoftDisplayFilter_0, D3DDevice_SetSoftDisplayFilter, 2048),
    REGISTER_OOVPAS_BIND_XREF(CDevice_SetStateUP_4, D3D_CDevice_SetStateUP, 3911), // stdcall
    REGISTER_OOVPAS_BIND_XREF(CDevice_SetStateUP_0__LTCG_esi1, D3D_CDevice_SetStateUP, 4039, 4040),
    REGISTER_OOVPAS_BIND_XREF(CDevice_SetStateVB_8, D3D_CDevice_SetStateVB, 3911, 4039), // stdcall
    REGISTER_OOVPAS(D3DDevice_SetStreamSource, 1044),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetStreamSource_0__LTCG_eax_StreamNumber_edi_pStreamData_ebx_Stride, D3DDevice_SetStreamSource, 2058),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetStreamSource_8__LTCG_edx_StreamNumber, D3DDevice_SetStreamSource, 1039),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetStreamSource_4, D3DDevice_SetStreamSource, 2058),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetStreamSource_8, D3DDevice_SetStreamSource, 2040),
    REGISTER_OOVPAS(D3DDevice_SetTexture, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_ecx1_edx2_eax3, D3DDevice_SetTextureStageStateNotInline, 3911),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_ecx3, D3DDevice_SetTextureStageStateNotInline, 4039),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureStageStateNotInline2_0__LTCG_eax1_edx2_ecx3, D3DDevice_SetTextureStageStateNotInline2, 4039), // TODO: fix bug to include counter from previous sections?
    REGISTER_OOVPAS_BIND_XREF(D3D_CDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_ecx3, D3D_CDevice_SetTextureStageStateNotInline, 4039), // NOTE: has return 0 (xor eax)
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_ecx1_eax2_edx3, D3DDevice_SetTextureStageStateNotInline, 4432),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_esi3, D3DDevice_SetTextureStageStateNotInline, 4531),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BorderColor, 1024, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureState_BorderColor_0, D3DDevice_SetTextureState_BorderColor, 2024, 2036, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureState_BorderColor_4, D3DDevice_SetTextureState_BorderColor, 2048, 2060),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_BumpEnv, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureState_BumpEnv_8, D3DDevice_SetTextureState_BumpEnv, 2024),
    REGISTER_OOVPAS(D3DDevice_SetTextureState_ColorKeyColor, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureState_ColorKeyColor_0, D3DDevice_SetTextureState_ColorKeyColor, 2024, 2036, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTextureState_ColorKeyColor_4, D3DDevice_SetTextureState_ColorKeyColor, 2048, 2060),
    REGISTER_OOVPAS_C(D3DDevice_SetTextureState_TexCoordIndex, 1944, 1958),
    REGISTER_OOVPAS_C_BIND_XREF(D3DDevice_SetTextureState_TexCoordIndex_0, D3DDevice_SetTextureState_TexCoordIndex, 2039, 2058),
    REGISTER_OOVPAS_C_BIND_XREF(D3DDevice_SetTextureState_TexCoordIndex_4, D3DDevice_SetTextureState_TexCoordIndex, 2040, 2045, 2052, 2058),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTexture_4__LTCG_eax_pTexture, D3DDevice_SetTexture, 2024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTexture_4__LTCG_eax_Stage, D3DDevice_SetTexture, 2036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTile_0__LTCG_eax1_ecx2, D3DDevice_SetTile, 3911),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTile_0__LTCG_ebx1_eax2, D3DDevice_SetTile, 4039),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTile_0__LTCG_ecx1_eax2, D3DDevice_SetTile, 4432),
    REGISTER_OOVPAS_BIND_XREF(D3D_SetTileNoWait_0__LTCG_eax1_ecx2, D3D_SetTileNoWait, 2024, 2048, 5455, 5659),
    REGISTER_OOVPAS_BIND_XREF(D3D_SetTileNoWait_0__LTCG_ecx1_eax2, D3D_SetTileNoWait, 4721, 5849),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2, D3DDevice_SetTransform, 3911, 4034, 5344, 5455, 5558),
    REGISTER_OOVPAS(D3DDevice_SetVertexData2f, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData2s, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4f, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetVertexData4f_16, D3DDevice_SetVertexData4f, 2024, 2036, 2048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4s, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexData4ub, 1024, 1036, 1048),
    REGISTER_OOVPAS(D3DDevice_SetVertexDataColor, 4038),
    REGISTER_OOVPAS(D3DDevice_SetVertexShader, 1024, 1036),
    REGISTER_OOVPAS(D3DDevice_SetVertexShaderConstant, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetVertexShaderConstantNotInline_0, D3DDevice_SetVertexShaderConstantNotInline, 2048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetVertexShaderConstant_8, D3DDevice_SetVertexShaderConstant, 2024),
    REGISTER_OOVPAS(D3DDevice_SetVertexShaderInput, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_SetVertexShader_0, D3DDevice_SetVertexShader, 2024, 2036),
    REGISTER_OOVPAS(D3DDevice_SetViewport, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS(D3DDevice_Swap, 1024, 1036, 1048),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_Swap_0, D3DDevice_Swap, 2024, 2036),
    REGISTER_OOVPAS(D3DDevice_UpdateOverlay, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS_BIND_XREF(D3DDevice_UpdateOverlay_16, D3DDevice_UpdateOverlay, 2048),
    REGISTER_OOVPAS(D3DPalette_Lock2, 1024),
    REGISTER_OOVPAS(D3DResource_GetType, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3DResource_GetType_0, D3DResource_GetType, 2024),
    REGISTER_OOVPAS(D3DResource_Release, 1024, 1036),
    REGISTER_OOVPAS(D3DSurface_GetDesc, 1024),
    REGISTER_OOVPAS(D3DTexture_GetSurfaceLevel2, 1024),
    REGISTER_OOVPAS(D3DTexture_LockRect, 1024),
    REGISTER_OOVPAS(D3DVertexBuffer_Lock2, 1024),
    REGISTER_OOVPAS_BIND_XREF(D3D_BlockOnResource_0, D3D_BlockOnResource, 2024, 2036, 2048, 2060),
    REGISTER_OOVPAS_BIND_XREF(D3D_DestroyResource__LTCG, D3D_DestroyResource, 3911),
    REGISTER_OOVPAS(D3D_CommonSetRenderTarget, 1024, 1036, 1048, 1060),
    REGISTER_OOVPAS_BIND_XREF(D3D_CommonSetMultiSampleModeAndScale_4__LTCG_eax1, D3D_CommonSetMultiSampleModeAndScale, 5344),
    REGISTER_OOVPAS(D3D_KickOffAndWaitForIdle2, 1024, 1036, 1048),
    REGISTER_OOVPAS_D3D(CDevice_KickOff, 1048), // thiscall
    REGISTER_OOVPAS_BIND_XREF(CDevice_KickOff_4, D3D_CDevice_KickOff, 4432, 4531, 5028), // stdcall (LTCG)
    REGISTER_OOVPAS_BIND_XREF(CDevice_KickOff_0__LTCG_edx1, D3D_CDevice_KickOff, 3911, 4039, 5028), // Final generic OOVPA: 5028; Removed: 0
    REGISTER_OOVPAS_BIND_XREF(CDevice_KickOff_0__LTCG_eax1, D3D_CDevice_KickOff, 5455),
    REGISTER_OOVPAS(D3DDevice_MakeSpace, 1036), // Almost identical to generic 4134 signature.
    REGISTER_OOVPAS(Direct3D_CreateDevice, 1024, 1036),
    REGISTER_OOVPAS_BIND_XREF(Direct3D_CreateDevice_16__LTCG_eax_BehaviorFlags_ebx_ppReturnedDeviceInterface, Direct3D_CreateDevice, 2024),
    REGISTER_OOVPAS_BIND_XREF(Direct3D_CreateDevice_16__LTCG_eax_BehaviorFlags_ecx_ppReturnedDeviceInterface, Direct3D_CreateDevice, 2036, 2048),
    REGISTER_OOVPAS_BIND_XREF(Direct3D_CreateDevice_4, Direct3D_CreateDevice, 2048, 2060),
    REGISTER_OOVPAS_D3D8(Get2DSurfaceDesc, 1024),
    REGISTER_OOVPAS_BIND_XREF(Get2DSurfaceDesc_0, D3D8_Get2DSurfaceDesc, 2024, 2036),
    REGISTER_OOVPAS_BIND_XREF(Get2DSurfaceDesc_4, D3D8_Get2DSurfaceDesc, 2048),
    REGISTER_OOVPAS_BIND_XREF(Lock3DSurface_16, D3D8_Lock3DSurface, 2048),
    REGISTER_OOVPAS_BIND_XREF(Lock2DSurface_16, D3D8_Lock2DSurface, 2048),
};

// ******************************************************************
// * D3D8LTCG_OOVPA_COUNT
// ******************************************************************
#define D3D8LTCG_OOVPA_COUNT XBSDB_ARRAY_SIZE(D3D8LTCG_OOVPA)

#endif

// SPDX-License-Identifier: ODbL-1.0

#include "unittest.hpp"

static const library_list database_optional = {
    REGISTER_SYMBOLS(D3DDevice_SetTextureStageStateNotInline2,
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline2_0__LTCG_eax1_edx2_ecx3, VER_RANGE(4039))),
    REGISTER_SYMBOLS(D3D_CDevice_SetTextureStageStateNotInline,
                     REGISTER_SYMBOL(D3D_CDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_ecx3, VER_RANGE(4039))),
};

static const library_list database_full = {
    // derived xrefs (variables)
    REGISTER_SYMBOL_INLINE(D3D_g_RenderState, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3D_g_ComplexRenderState, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3D_g_DeferredRenderState, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3D_g_DeferredTextureState, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3D_g_pDevice, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3D_g_Stream, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_BackFillMode, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_CullMode, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_DoNotCullUncompressed, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_Dxt1NoiseEnable, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_FillMode, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_FogEnable, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_FrontFace, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_LogicOp, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_MultiSampleAntiAlias, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_MultiSampleMask, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_MultiSampleMode, VER_RANGE(4034)),
    REGISTER_SYMBOL_INLINE(D3DRS_MultiSampleRenderTargetMode, VER_RANGE(4034)),
    REGISTER_SYMBOL_INLINE(D3DRS_MultiSampleType, VER_RANGE(0, 4034)),
    REGISTER_SYMBOL_INLINE(D3DRS_OcclusionCullEnable, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_PSTextureModes, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_RopZCmpAlwaysRead, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_RopZRead, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_SampleAlpha, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DRS_StencilCullEnable, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_StencilEnable, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_StencilFail, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_TwoSidedLighting, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_YuvEnable, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE(D3DRS_ZBias, VER_RANGE(0)),

    // derived xrefs (offsets)
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(D3DDevice__m_SwapCallback, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(D3DDevice__m_VBlankCallback, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(D3DDevice__m_VertexShader, VER_RANGE(0)),
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(D3DDevice__m_VerticalBlankEvent, VER_RANGE(0)),

    REGISTER_SYMBOLS(D3D_CreateTexture,
                     REGISTER_SYMBOL(D3D_CreateTexture, VER_RANGE(3911, 4627)),
                     REGISTER_SYMBOL(D3D_CreateTexture_28__LTCG_edx8_edi9, VER_RANGE(3911, 4627))),
    REGISTER_SYMBOL_INLINE_D3D(CDevice_MakeSpace, VER_RANGE(3911, 4034)),
    REGISTER_SYMBOL_INLINE_D3D(CMiniport_CreateCtxDmaObject, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE_D3D(CMiniport_InitHardware, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE_D3D(CMiniport_IsFlipPending, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DBaseTexture_GetLevelCount, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DCubeTexture_GetCubeMapSurface, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DCubeTexture_GetCubeMapSurface2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DCubeTexture_LockRect, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_AddRef, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_ApplyStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_Begin, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_BeginPush,
                     REGISTER_SYMBOL(D3DDevice_BeginPush_8, VER_RANGE(4039)),
                     REGISTER_SYMBOL(D3DDevice_BeginPush_4, VER_RANGE(4531))),
    REGISTER_SYMBOLS(D3DDevice_BeginPushBuffer,
                     REGISTER_SYMBOL(D3DDevice_BeginPushBuffer, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_BeginPushBuffer_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_BeginStateBig, VER_RANGE(5028)),
    REGISTER_SYMBOL_INLINE(D3DDevice_BeginStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_BeginVisibilityTest, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_BlockOnFence, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_BlockUntilVerticalBlank, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CaptureStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_Clear, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CopyRects, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_CreateCubeTexture,
                     REGISTER_SYMBOL(D3DDevice_CreateCubeTexture, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_CreateCubeTexture_4__LTCG_eax1_edx3_ecx4_edi6, VER_RANGE(3911))),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateImageSurface, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateIndexBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateIndexBuffer2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreatePalette, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreatePalette2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreatePixelShader, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_CreateTexture,
                     REGISTER_SYMBOL(D3DDevice_CreateTexture, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_CreateTexture_8__LTCG_edx3_ecx4_eax5_edi7, VER_RANGE(3911))),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateTexture2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateVertexBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateVertexBuffer2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_CreateVertexShader, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_CreateVolumeTexture,
                     REGISTER_SYMBOL(D3DDevice_CreateVolumeTexture, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_CreateVolumeTexture_12__LTCG_edx4_ecx5_eax6_edi8, VER_RANGE(3911))),
    REGISTER_SYMBOL_INLINE(D3DDevice_DeletePatch, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_DeletePixelShader,
                     REGISTER_SYMBOL(D3DDevice_DeletePixelShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_DeletePixelShader_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_DeleteStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_DeleteVertexShader,
                     REGISTER_SYMBOL(D3DDevice_DeleteVertexShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_DeleteVertexShader_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_DrawIndexedVertices, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_DrawIndexedVerticesUP, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_DrawRectPatch, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_DrawTriPatch, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_DrawVertices,
                     REGISTER_SYMBOL(D3DDevice_DrawVertices, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_DrawVertices_4__LTCG_ecx2_eax3, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_DrawVertices_8__LTCG_eax3, VER_RANGE(4039))),
    REGISTER_SYMBOLS(D3DDevice_DrawVerticesUP,
                     REGISTER_SYMBOL(D3DDevice_DrawVerticesUP, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_DrawVerticesUP_12__LTCG_ebx3, VER_RANGE(3911))),
    REGISTER_SYMBOLS(D3DDevice_EnableOverlay,
                     REGISTER_SYMBOL(D3DDevice_EnableOverlay, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_EnableOverlay_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_End, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_EndPush, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(D3DDevice_EndPushBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_EndStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_EndVisibilityTest,
                     REGISTER_SYMBOL(D3DDevice_EndVisibilityTest, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_EndVisibilityTest_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_FlushVertexCache, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_GetBackBuffer,
                     REGISTER_SYMBOL(D3DDevice_GetBackBuffer, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_GetBackBuffer_8, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_GetBackBuffer2,
                     REGISTER_SYMBOL(D3DDevice_GetBackBuffer2, VER_RANGE(4627)),
                     REGISTER_SYMBOL(D3DDevice_GetBackBuffer2_0__LTCG_eax1, VER_RANGE(4627))),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetBackMaterial, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetCreationParameters, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetDepthStencilSurface, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetDepthStencilSurface2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetDeviceCaps, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetDisplayFieldStatus, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetDisplayMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetGammaRamp, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetLight, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetLightEnable, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetMaterial, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetModelView, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetOverlayUpdateStatus, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetPersistedSurface2, VER_RANGE(4928)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetPixelShader, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetProjectionViewportMatrix, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetPushBufferOffset, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetRenderTarget, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetRenderTarget2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetScissors, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetShaderConstantMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetStreamSource2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetTexture2, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetTile, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetTransform, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShader, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShaderConstant, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShaderDeclaration, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShaderFunction, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShaderInput, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShaderSize, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVertexShaderType, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_GetViewport, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_GetViewportOffsetAndScale,
                     REGISTER_SYMBOL(D3DDevice_GetViewportOffsetAndScale, VER_RANGE(4432)),
                     REGISTER_SYMBOL(D3DDevice_GetViewportOffsetAndScale_0, VER_RANGE(4432))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_GetVisibilityTestResult, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_InsertCallback, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_InsertFence, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_IsBusy, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_IsFencePending, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3D_CDevice_KickOff, // thiscall
                     REGISTER_SYMBOL(CDevice_KickOff, VER_RANGE(3911)),
                     REGISTER_SYMBOL(CDevice_KickOff_4, VER_RANGE(4432)), // stdcall (LTCG)
                     REGISTER_SYMBOL(CDevice_KickOff_0__LTCG_edx1, VER_RANGE(3911)),
                     REGISTER_SYMBOL(CDevice_KickOff_0__LTCG_eax1, VER_RANGE(5455))),
    REGISTER_SYMBOL_INLINE(D3DDevice_KickPushBuffer, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_LightEnable,
                     REGISTER_SYMBOL(D3DDevice_LightEnable, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_LightEnable_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_LoadVertexShader,
                     REGISTER_SYMBOL(D3DDevice_LoadVertexShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_LoadVertexShader_0__LTCG_eax_Address_ecx_Handle, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_LoadVertexShader_0__LTCG_eax_Address_edx_Handle, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_LoadVertexShader_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_LoadVertexShaderProgram, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_MakeSpace, VER_RANGE(4034)),
    REGISTER_SYMBOL_INLINE(D3DDevice_PersistDisplay, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_Present, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_PrimeVertexCache, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_Release, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_Reset,
                     REGISTER_SYMBOL(D3DDevice_Reset, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_Reset_0__LTCG_edi1, VER_RANGE(4627)),
                     REGISTER_SYMBOL(D3DDevice_Reset_0__LTCG_ebx1, VER_RANGE(5344))),
    REGISTER_SYMBOLS(D3DDevice_RunPushBuffer,
                     REGISTER_SYMBOL(D3DDevice_RunPushBuffer, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_RunPushBuffer_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_RunVertexStateShader,
                     REGISTER_SYMBOL(D3DDevice_RunVertexStateShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_RunVertexStateShader_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SelectVertexShader,
                     REGISTER_SYMBOL(D3DDevice_SelectVertexShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SelectVertexShader_0__LTCG_eax1_ebx2, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SelectVertexShader_4__LTCG_eax1, VER_RANGE(3911))),
    REGISTER_SYMBOLS(D3DDevice_SelectVertexShaderDirect,
                     REGISTER_SYMBOL(D3DDevice_SelectVertexShaderDirect, VER_RANGE(4361)),
                     REGISTER_SYMBOL(D3DDevice_SelectVertexShaderDirect_0, VER_RANGE(4361))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetBackBufferScale, VER_RANGE(4039)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetBackMaterial, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetDepthClipPlanes, VER_RANGE(4432)),
    REGISTER_SYMBOLS(D3DDevice_SetFlickerFilter,
                     REGISTER_SYMBOL(D3DDevice_SetFlickerFilter, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetFlickerFilter_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetGammaRamp, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_SetIndices,
                     REGISTER_SYMBOL(D3DDevice_SetIndices, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetIndices_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetLight, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetMaterial, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetModelView, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_SetPalette,
                     REGISTER_SYMBOL(D3DDevice_SetPalette, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetPalette_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SetPixelShader,
                     REGISTER_SYMBOL(D3DDevice_SetPixelShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetPixelShader_0__LTCG_eax_handle, VER_RANGE(3911))),
    REGISTER_SYMBOLS(D3DDevice_SetPixelShaderConstant,
                     REGISTER_SYMBOL(D3DDevice_SetPixelShaderConstant, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetPixelShaderConstant_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetPixelShaderProgram, VER_RANGE(3911)),

    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState2, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_SetRenderStateNotInline,
                     REGISTER_SYMBOL(D3DDevice_SetRenderStateNotInline, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetRenderStateNotInline_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_BackFillMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_CullMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_Deferred, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_DoNotCullUncompressed, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_Dxt1NoiseEnable, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_EdgeAntiAlias, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_FillMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_FogColor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_FrontFace, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_LineWidth, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_LogicOp, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_MultiSampleAntiAlias, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_MultiSampleMask, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_MultiSampleMode, VER_RANGE(4034)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_MultiSampleRenderTargetMode, VER_RANGE(4034)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_MultiSampleType, VER_RANGE(3911, 4034)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_NormalizeNormals, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_OcclusionCullEnable, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_PSTextureModes, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_RopZCmpAlwaysRead, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_RopZRead, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_SampleAlpha, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_ShadowFunc, VER_RANGE(3911)),

    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_Simple, VER_RANGE(3911)),

    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_StencilCullEnable, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_StencilEnable, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_StencilFail, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_TextureFactor, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_TwoSidedLighting, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_VertexBlend, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_YuvEnable, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_ZBias, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderState_ZEnable, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_SetRenderTarget,
                     REGISTER_SYMBOL(D3DDevice_SetRenderTarget, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetRenderTarget_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetRenderTargetFast, VER_RANGE(5233)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetScissors, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetScreenSpaceOffset, VER_RANGE(4034)),
    REGISTER_SYMBOLS(D3DDevice_SetShaderConstantMode,
                     REGISTER_SYMBOL(D3DDevice_SetShaderConstantMode, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetShaderConstantMode_0__LTCG_eax1, VER_RANGE(3911))),
    REGISTER_SYMBOLS(D3DDevice_SetSoftDisplayFilter,
                     REGISTER_SYMBOL(D3DDevice_SetSoftDisplayFilter, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetSoftDisplayFilter_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3D_CDevice_SetStateUP,
                     REGISTER_SYMBOL(CDevice_SetStateUP, VER_RANGE(3911)), // thiscall
                     REGISTER_SYMBOL(CDevice_SetStateUP_4, VER_RANGE(3911)), // stdcall
                     REGISTER_SYMBOL(CDevice_SetStateUP_0__LTCG_esi1, VER_RANGE(3911))),
    REGISTER_SYMBOLS(D3D_CDevice_SetStateVB,
                     REGISTER_SYMBOL(CDevice_SetStateVB, VER_RANGE(3911)), // thiscall
                     REGISTER_SYMBOL(CDevice_SetStateVB_8, VER_RANGE(3911))), // stdcall
    REGISTER_SYMBOL_INLINE(D3DDevice_SetStipple, VER_RANGE(4627)),
    REGISTER_SYMBOLS(D3DDevice_SetStreamSource,
                     REGISTER_SYMBOL(D3DDevice_SetStreamSource, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetStreamSource_0__LTCG_eax_StreamNumber_edi_pStreamData_ebx_Stride, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetStreamSource_8__LTCG_edx_StreamNumber, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetStreamSource_4, VER_RANGE(3911)),  // NOTE: LTCG usage
                     REGISTER_SYMBOL(D3DDevice_SetStreamSource_8, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetSwapCallback, VER_RANGE(4039)),
    REGISTER_SYMBOLS(D3DDevice_SetTexture,
                     REGISTER_SYMBOL(D3DDevice_SetTexture, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTexture_4__LTCG_eax_pTexture, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTexture_4__LTCG_eax_Stage, VER_RANGE(4721))),
    REGISTER_SYMBOLS(D3DDevice_SetTextureState_BorderColor,
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_BorderColor, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_BorderColor_0, VER_RANGE(3911)),  // NOTE: LTCG usage
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_BorderColor_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SetTextureState_BumpEnv,
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_BumpEnv, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_BumpEnv_8, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SetTextureState_ColorKeyColor,
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_ColorKeyColor, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_ColorKeyColor_0, VER_RANGE(3911)),  // NOTE: LTCG usage
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_ColorKeyColor_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SetTextureState_TexCoordIndex,
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_TexCoordIndex, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_TexCoordIndex_0, VER_RANGE(3911)),  // NOTE: LTCG usage
                     REGISTER_SYMBOL(D3DDevice_SetTextureState_TexCoordIndex_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SetTile,
                     REGISTER_SYMBOL(D3DDevice_SetTile, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTile_0__LTCG_eax1_ecx2, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTile_0__LTCG_ecx1_eax2, VER_RANGE(4039)),
                     REGISTER_SYMBOL(D3DDevice_SetTile_0__LTCG_ebx1_eax2, VER_RANGE(4432))),
    REGISTER_SYMBOLS(D3DDevice_SetTransform,
                     REGISTER_SYMBOL(D3DDevice_SetTransform, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTransform_0__LTCG_eax1_edx2, VER_RANGE(3911))),
    REGISTER_SYMBOLS(D3DDevice_MultiplyTransform,
                     REGISTER_SYMBOL(D3DDevice_MultiplyTransform, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_MultiplyTransform_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexData2f, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexData2s, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_SetVertexData4f,
                     REGISTER_SYMBOL(D3DDevice_SetVertexData4f, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetVertexData4f_16, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexData4s, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexData4ub, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexDataColor, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_SetVertexShader,
                     REGISTER_SYMBOL(D3DDevice_SetVertexShader, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetVertexShader_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3DDevice_SetVertexShaderConstant,
                     REGISTER_SYMBOL(D3DDevice_SetVertexShaderConstant, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetVertexShaderConstant_8, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexShaderConstant1, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexShaderConstant1Fast, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexShaderConstant4, VER_RANGE(4627)),
    REGISTER_SYMBOLS(D3DDevice_SetVertexShaderConstantNotInline,
                     REGISTER_SYMBOL(D3DDevice_SetVertexShaderConstantNotInline, VER_RANGE(4627)),
                     REGISTER_SYMBOL(D3DDevice_SetVertexShaderConstantNotInline_0, VER_RANGE(4627))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexShaderConstantNotInlineFast, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexShaderInput, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVertexShaderInputDirect, VER_RANGE(4361)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetVerticalBlankCallback, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_SetViewport, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DDevice_Suspend, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_Swap,
                     REGISTER_SYMBOL(D3DDevice_Swap, VER_RANGE(4034)),
                     REGISTER_SYMBOL(D3DDevice_Swap_0, VER_RANGE(4034))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DDevice_SwitchTexture, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DDevice_UpdateOverlay,
                     REGISTER_SYMBOL(D3DDevice_UpdateOverlay, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_UpdateOverlay_16, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DPalette_Lock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DPalette_Lock2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DResource_AddRef, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DResource_BlockUntilNotBusy, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3DResource_GetType,
                     REGISTER_SYMBOL(D3DResource_GetType, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DResource_GetType_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE(D3DResource_IsBusy, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DResource_Register, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DResource_Release, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DSurface_GetDesc, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DSurface_LockRect, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DTexture_GetSurfaceLevel, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DTexture_GetSurfaceLevel2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DTexture_LockRect, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DVertexBuffer_GetDesc, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DVertexBuffer_Lock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3DVertexBuffer_Lock2, VER_RANGE(4627)),
    REGISTER_SYMBOL_INLINE(D3DVolumeTexture_LockBox, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_AllocContiguousMemory, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3D_BlockOnResource,
                     REGISTER_SYMBOL(D3D_BlockOnResource, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3D_BlockOnResource_0, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3D_BlockOnTime,
                     REGISTER_SYMBOL(D3D_BlockOnTime, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3D_BlockOnTime_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOL_INLINE_D3D(CMiniport_GetDisplayCapabilities, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_CheckDeviceFormat, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_ClearStateBlockFlags, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_CommonSetDebugRegisters, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3D_CommonSetMultiSampleModeAndScale,
                     REGISTER_SYMBOL(D3D_CommonSetMultiSampleModeAndScale, VER_RANGE(5344)),
                     REGISTER_SYMBOL(D3D_CommonSetMultiSampleModeAndScale_4__LTCG_eax1, VER_RANGE(5344))),
    REGISTER_SYMBOL_INLINE(D3D_CommonSetRenderTarget, VER_RANGE(4627, 5344)),
    REGISTER_SYMBOL_INLINE(D3D_CreateStandAloneSurface, VER_RANGE(4034)),
    REGISTER_SYMBOLS(D3D_DestroyResource,
                     REGISTER_SYMBOL(D3D_DestroyResource, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3D_DestroyResource__LTCG, VER_RANGE(3911))), // NOTE: missing param usage
    REGISTER_SYMBOL_INLINE(D3D_EnumAdapterModes, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_GetAdapterDisplayMode, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_GetAdapterIdentifier, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_GetAdapterModeCount, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_GetDeviceCaps, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_KickOffAndWaitForIdle, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_LazySetPointParams, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_RecordStateBlock, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_SetFence, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(D3D_SetPushBufferSize, VER_RANGE(3911)),
    REGISTER_SYMBOLS(D3D_SetTileNoWait,
                     REGISTER_SYMBOL(D3D_SetTileNoWait, VER_RANGE(4627)),
                     REGISTER_SYMBOL(D3D_SetTileNoWait_0__LTCG_eax1_ecx2, VER_RANGE(4627)),
                     REGISTER_SYMBOL(D3D_SetTileNoWait_0__LTCG_ecx1_eax2, VER_RANGE(4627))),
    REGISTER_SYMBOL_INLINE(D3D_UpdateProjectionViewportTransform, VER_RANGE(3911)),
    REGISTER_SYMBOL_INLINE(Direct3D_CheckDeviceMultiSampleType, VER_RANGE(3911)),
    REGISTER_SYMBOLS(Direct3D_CreateDevice,
                     REGISTER_SYMBOL(Direct3D_CreateDevice, VER_RANGE(3911)),
                     REGISTER_SYMBOL(Direct3D_CreateDevice_16__LTCG_eax_BehaviorFlags_ebx_ppReturnedDeviceInterface, VER_RANGE(3911)),
                     REGISTER_SYMBOL(Direct3D_CreateDevice_16__LTCG_eax_BehaviorFlags_ecx_ppReturnedDeviceInterface, VER_RANGE(3911)),
                     REGISTER_SYMBOL(Direct3D_CreateDevice_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3D8_Get2DSurfaceDesc,
                     REGISTER_SYMBOL(Get2DSurfaceDesc, VER_RANGE(3911)),
                     REGISTER_SYMBOL(Get2DSurfaceDesc_0, VER_RANGE(3911)),  // NOTE: LTCG usage
                     REGISTER_SYMBOL(Get2DSurfaceDesc_4, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3D8_Lock2DSurface,
                     REGISTER_SYMBOL(Lock2DSurface, VER_RANGE(3911)),
                     REGISTER_SYMBOL(Lock2DSurface_16, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3D8_Lock3DSurface,
                     REGISTER_SYMBOL(Lock3DSurface, VER_RANGE(3911)),
                     REGISTER_SYMBOL(Lock3DSurface_16, VER_RANGE(3911))), // NOTE: LTCG usage
    REGISTER_SYMBOLS(D3D_MakeRequestedSpace,
                     REGISTER_SYMBOL(D3D_MakeRequestedSpace_4, VER_RANGE(4034, 4134)),
                     REGISTER_SYMBOL(D3D_MakeRequestedSpace_8, VER_RANGE(4134)),
                     REGISTER_SYMBOL(D3D_MakeRequestedSpace_4__LTCG_eax_RequestedSpace, VER_RANGE(5788))),
    REGISTER_SYMBOL_INLINE(XMETAL_StartPush, VER_RANGE(3911, 4034)),
    REGISTER_SYMBOL_INLINE(IDirect3DVertexBuffer8_Lock, VER_RANGE(4627)),

    REGISTER_SYMBOLS(D3DDevice_SetTextureStageStateNotInline,
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline_0__LTCG_ecx1_edx2_eax3, VER_RANGE(3911)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_ecx3, VER_RANGE(4039)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline2_0__LTCG_eax1_edx2_ecx3, VER_RANGE(4039)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline3_0__LTCG_eax1_edx2_ecx3, VER_RANGE(4039)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline_0__LTCG_ecx1_eax2_edx3, VER_RANGE(4432)),
                     REGISTER_SYMBOL(D3DDevice_SetTextureStageStateNotInline_0__LTCG_eax1_edx2_esi3, VER_RANGE(4531))),
    // Listed only in LTCG database:
    REGISTER_SYMBOL_INLINE(D3D_KickOffAndWaitForIdle2, VER_RANGE(4627)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/d3d8.def>
#include <xref/d3d8ltcg.def>
#undef XREF_SYMBOL
    LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(D3DDevice__m_VerticalBlankEvent__GenericFragment)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

static const subcategory_db d3d8_db = {
    .name = "general",
    .optional = &database_optional,
    .min = nullptr,
    .full = &database_full,
};

void getLibraryD3D8(library_db& lib_db)
{
    lib_db.subcategories = { &d3d8_db };
    lib_db.xref_offset = XREF_OFFSET;
    lib_db.xref_total = LOCAL_COUNT;
    // TODO: database is incomplete + 3 internal reference need to be exclude.
    // Excluding:
    // -  3 internal manual scan reference
    // -  1 variables
    // -  5 internal offsets
    lib_db.xref_exclude = 9;
}

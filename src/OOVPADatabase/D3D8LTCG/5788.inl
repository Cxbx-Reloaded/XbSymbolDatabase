// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5788.inl
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

// ******************************************************************
// * D3DDevice_SetPalette
// ******************************************************************
//85C05774258B4E2C8948088BBC
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPalette,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x13, 0x85 },
    { 0x14, 0xC0 },
    { 0x15, 0x57 },
    { 0x16, 0x74 },
    { 0x17, 0x25 },
    { 0x18, 0x8B },
    { 0x19, 0x4E },
    { 0x1A, 0x2C },
    { 0x1B, 0x89 },
    { 0x1C, 0x48 },
    { 0x1D, 0x08 },
    { 0x1E, 0x8B },
    { 0x1F, 0xBC },
    //
);

// ******************************************************************
// * D3DDevice_SetPalette
// ******************************************************************
//000085C05774258B4E ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPalette_4,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },

    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0x85 },
    { 0x17, 0xC0 },
    { 0x18, 0x57 },
    { 0x19, 0x74 },
    { 0x1A, 0x25 },
    { 0x1B, 0x8B },
    { 0x1C, 0x4E },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x53 },

    { 0x77, 0xC7 },
    { 0x78, 0x40 },
    { 0x79, 0x04 },
    { 0x7A, 0x00 },
    { 0x7B, 0x00 },
    { 0x7C, 0x21 },
    { 0x7D, 0x00 },
    { 0x7E, 0x83 },
    { 0x7F, 0xC0 },
    { 0x80, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader_0__LTCG_eax_handle,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x85 },

    { 0x73, 0xC7 },
    { 0x74, 0x40 },
    { 0x75, 0x04 },
    { 0x76, 0x00 },
    { 0x77, 0x00 },
    { 0x78, 0x21 },
    { 0x79, 0x00 },
    { 0x7A, 0x83 },
    { 0x7B, 0xC0 },
    { 0x7C, 0x08 },

    { 0x81, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShaderConstant
// ******************************************************************
//F30F2DC0C1E0100FC6C039 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShaderConstant_4,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x04, 0xEC },

    { 0x4C, 0xF3 },
    { 0x4D, 0x0F },
    { 0x4E, 0x2D },
    { 0x4F, 0xC0 },
    { 0x50, 0xC1 },
    { 0x51, 0xE0 },
    { 0x52, 0x10 },
    { 0x53, 0x0F },
    { 0x54, 0xC6 },
    { 0x55, 0xC0 },
    { 0x56, 0x39 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShaderProgram
// ******************************************************************
//C780280900
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShaderProgram,
                         1024)
OOVPA_SIG_MATCH(

    { 0x06, 0xA1 },
    { 0x0B, 0x74 },

    { 0x19, 0xC7 },
    { 0x1A, 0x80 },
    { 0x1B, 0x28 },
    { 0x1C, 0x09 },
    { 0x1D, 0x00 },
    { 0x1E, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
//C7000803040075
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      1053,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_CullMode],e??
    XREF_ENTRY(0x35, XREF_D3DRS_CullMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // unique
    // mov [eax],0x40308
    OV_MATCH(0x23, 0xC7, 0x00, 0x08, 0x03, 0x04, 0x00),
    // jnz +0x??
    OV_MATCH(0x29, 0x75),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
//0020030800894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         1060)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x1E, 0x4C },

    { 0x22, 0x00 },
    { 0x23, 0x20 },
    { 0x24, 0x03 },
    { 0x25, 0x08 },
    { 0x26, 0x00 },
    { 0x27, 0x89 },
    { 0x28, 0x48 },
    { 0x29, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FillMode,
                      1060,
                      XRefThree)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1F, XREF_D3DRS_TwoSidedLighting),
    XREF_ENTRY(0x25, XREF_D3DRS_BackFillMode),
    XREF_ENTRY(0x46, XREF_D3DRS_FillMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    OV_MATCH(0x1D, 0x8B),

    // mov edx,ptr [D3DRS_BackFillMode]
    OV_MATCH(0x23, 0x8B),

    // mov ptr [eax],0x008038C
    OV_MATCH(0x33, 0xC7, 0x00, 0x8C, 0x03, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x3F, 0x83, 0xC0, 0x0C),

    // mov ptr [D3DRS_FillMode],ecx
    OV_MATCH(0x44, 0x89),

    // retn 0x04
    OV_MATCH(0x4B, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
//54240E8BF981
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x24, 0x54 },
    { 0x25, 0x24 },
    { 0x26, 0x0E },
    { 0x27, 0x8B },
    { 0x28, 0xF9 },
    { 0x29, 0x81 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
//00a0A0304008948
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FrontFace,
                         1060)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x22, 0x00 },
    { 0x23, 0xA0 },
    { 0x24, 0x03 },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x89 },
    { 0x28, 0x48 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_LogicOp,
                      1060,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // mov [D3DRS_LogicOp],e??
    XREF_ENTRY(0x35, XREF_D3DRS_LogicOp),

    // push esi
    OV_MATCH(0x00, 0x56),

    // jnz +0x??
    OV_MATCH(0x23, 0x75),
    // unique
    // mov [eax],0x417bc
    OV_MATCH(0x25, 0xC7, 0x00, 0xBC, 0x17, 0x04, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
//A4030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x23, 0xA4 },
    { 0x24, 0x03 },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x89 },
    { 0x28, 0x48 },
    { 0x29, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
//6C1E04008D91
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },

    { 0x23, 0x6C },
    { 0x24, 0x1E },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x8D },
    { 0x28, 0x91 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
//018b54240885d2c700
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilEnable,
                         1060)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x50, 0x01 },
    { 0x51, 0x8B },
    { 0x52, 0x54 },
    { 0x53, 0x24 },
    { 0x54, 0x08 },
    { 0x55, 0x85 },
    { 0x56, 0xD2 },
    { 0x57, 0xC7 },
    { 0x58, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
//7003040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilFail,
                         1060)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x23, 0x33 },

    { 0x61, 0x70 },
    { 0x62, 0x03 },
    { 0x63, 0x04 },
    { 0x64, 0x00 },
    { 0x65, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
//C9C7000C0304008948048B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x37, 0xC9 },
    { 0x38, 0xC7 },
    { 0x39, 0x00 },
    { 0x3A, 0x0C },
    { 0x3B, 0x03 },
    { 0x3C, 0x04 },
    { 0x3D, 0x00 },
    { 0x3E, 0x89 },
    { 0x3F, 0x48 },
    { 0x40, 0x04 },
    { 0x41, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//088BD1C1E20681C2241B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x20, 0x08 },
    { 0x21, 0x8B },
    { 0x22, 0xD1 },
    { 0x23, 0xC1 },
    { 0x24, 0xE2 },
    { 0x25, 0x06 },
    { 0x26, 0x81 },
    { 0x27, 0xC2 },
    { 0x28, 0x24 },
    { 0x29, 0x1B },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//891089580483 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor_0,
                         2048)
OOVPA_SIG_MATCH(

    { 0x01, 0x57 },

    { 0x2D, 0x89 },
    { 0x2E, 0x10 },
    { 0x2F, 0x89 },
    { 0x30, 0x58 },
    { 0x31, 0x04 },
    { 0x32, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
//E00A040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x18, 0xE8 },
    { 0x1E, 0x4C },

    { 0x24, 0xE0 },
    { 0x25, 0x0A },
    { 0x26, 0x04 },
    { 0x27, 0x00 },
    { 0x28, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
//E00A040089 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_0,
                         2048)
OOVPA_SIG_MATCH(

    { 0x01, 0x57 },
    { 0x0B, 0x8B },
    { 0x1D, 0xE8 },

    { 0x25, 0xE0 },
    { 0x26, 0x0A },
    { 0x27, 0x04 },
    { 0x28, 0x00 },
    { 0x29, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTargetFast
// ******************************************************************
//A900007800578B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTargetFast,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x07, 0xA9 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0x78 },
    { 0x0B, 0x00 },
    { 0x0C, 0x57 },
    { 0x0D, 0x8B },
    //
);

// ******************************************************************
// * D3D_BlockOnTime
// ******************************************************************
//C747101001040089
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0xB4, 0xC7 },
    { 0xB5, 0x47 },
    { 0xB6, 0x10 },
    { 0xB7, 0x10 },
    { 0xB8, 0x01 },
    { 0xB9, 0x04 },
    { 0xBA, 0x00 },
    { 0xBB, 0x89 },
    //
);

// ******************************************************************
// * D3D_BlockOnTime
// ******************************************************************
//C747101001040089 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime_4,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0xB8, 0xC7 },
    { 0xB9, 0x47 },
    { 0xBA, 0x10 },
    { 0xBB, 0x10 },
    { 0xBC, 0x01 },
    { 0xBD, 0x04 },
    { 0xBE, 0x00 },
    { 0xBF, 0x89 },
    //
);

// ******************************************************************
// * D3D_MakeRequestedSpace
// ******************************************************************
//81C5004000003BE9 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3D_MakeRequestedSpace_4__LTCG_eax_RequestedSpace,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x5A, 0x81 },
    { 0x5B, 0xC5 },
    { 0x5C, 0x00 },
    { 0x5D, 0x40 },
    { 0x5E, 0x00 },
    { 0x5F, 0x00 },
    { 0x60, 0x3B },
    { 0x61, 0xE9 },
    //
);

// ******************************************************************
// * D3D_SetFence
// ******************************************************************
//C70010A304008BCF
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x21, 0xC7 },
    { 0x22, 0x00 },
    { 0x23, 0x10 },
    { 0x24, 0xA3 },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x8B },
    { 0x28, 0xCF },
    //
);

// ******************************************************************
// * D3D_SetFence
// ******************************************************************
//C70010A304008B
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8A },

    { 0x25, 0xC7 },
    { 0x26, 0x00 },
    { 0x27, 0x10 },
    { 0x28, 0xA3 },
    { 0x29, 0x04 },
    { 0x2A, 0x00 },
    { 0x2B, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
//558BEC83EC1453568B35 ...C700FC17040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVerticesUP,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x14 },
    { 0x06, 0x53 },
    { 0x07, 0x56 },
    { 0x08, 0x8B },
    { 0x09, 0x35 },

    { 0x30, 0xC7 },
    { 0x31, 0x00 },
    { 0x32, 0xFC },
    { 0x33, 0x17 },
    { 0x34, 0x04 },
    { 0x35, 0x00 },
    { 0x36, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      5558,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    XREF_ENTRY(0xFF, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // shl ecx,0x6
    OV_MATCH(0x0A, 0xC1, 0xE1, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x15, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xFE, 0xE8),

    // ret
    OV_MATCH(0x10D, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
//C7442410000000208B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x4B, 0xC7 },
    { 0x4C, 0x44 },
    { 0x4D, 0x24 },
    { 0x4E, 0x10 },
    { 0x4F, 0x00 },
    { 0x50, 0x00 },
    { 0x51, 0x00 },
    { 0x52, 0x20 },
    { 0x53, 0x8B },
    //
);

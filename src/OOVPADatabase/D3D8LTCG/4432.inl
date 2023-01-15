// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->4432.inl
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
// * D3D_SetFence
// ******************************************************************
//460457720EA1
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x0D, 0x8B },

    { 0x10, 0x46 },
    { 0x11, 0x04 },
    { 0x12, 0x57 },
    { 0x13, 0x72 },
    { 0x14, 0x0E },
    { 0x15, 0xA1 },
    //
);

// ******************************************************************
// * Direct3D_CreateDevice
// ******************************************************************
//00000800A1
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x06, 0xC0 },

    { 0x0F, 0x00 },
    { 0x10, 0x00 },
    { 0x11, 0x08 },
    { 0x12, 0x00 },
    { 0x13, 0xA1 },
    //
);

// ******************************************************************
// * D3DDevice_SetStreamSource
// ******************************************************************
//7406810300000800
OOVPA_SIG_HEADER_XREF(D3DDevice_SetStreamSource,
                      1044,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x22, XREF_D3D_g_Stream), // Derived

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x0E, 0x74 },
    { 0x0F, 0x06 },
    { 0x10, 0x81 },
    { 0x11, 0x03 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x08 },
    { 0x15, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//8BC3C1E007578B3D
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex,
                      1944,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x53 },
    { 0x02, 0x5C },

    { 0x0B, 0x8B },
    { 0x0C, 0xC3 },
    { 0x0D, 0xC1 },
    { 0x0E, 0xE0 },
    { 0x0F, 0x07 },
    { 0x10, 0x57 },
    { 0x11, 0x8B },
    { 0x12, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
//C7000803040075
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      1052,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived
    XREF_ENTRY(0x34, XREF_D3DRS_CullMode), // Derived

    { 0x00, 0x56 },

    { 0x22, 0xC7 },
    { 0x23, 0x00 },
    { 0x24, 0x08 },
    { 0x25, 0x03 },
    { 0x26, 0x04 },
    { 0x27, 0x00 },
    { 0x28, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
//A4030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x22, 0xA4 },
    { 0x23, 0x03 },
    { 0x24, 0x04 },
    { 0x25, 0x00 },
    { 0x26, 0x89 },
    { 0x27, 0x48 },
    { 0x28, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
//C9C7000C0304008948048B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x36, 0xC9 },
    { 0x37, 0xC7 },
    { 0x38, 0x00 },
    { 0x39, 0x0C },
    { 0x3A, 0x03 },
    { 0x3B, 0x04 },
    { 0x3C, 0x00 },
    { 0x3D, 0x89 },
    { 0x3E, 0x48 },
    { 0x3F, 0x04 },
    { 0x40, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
//018b54240885d2c700
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilEnable,
                         1048)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x4F, 0x01 },
    { 0x50, 0x8B },
    { 0x51, 0x54 },
    { 0x52, 0x24 },
    { 0x53, 0x08 },
    { 0x54, 0x85 },
    { 0x55, 0xD2 },
    { 0x56, 0xC7 },
    { 0x57, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FillMode,
                      1048,
                      XRefThree)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1E, XREF_D3DRS_TwoSidedLighting),
    XREF_ENTRY(0x24, XREF_D3DRS_BackFillMode),
    XREF_ENTRY(0x45, XREF_D3DRS_FillMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    OV_MATCH(0x1C, 0x8B),

    // mov edx,ptr [D3DRS_BackFillMode]
    OV_MATCH(0x22, 0x8B),

    // mov ptr [eax],0x008038C
    OV_MATCH(0x32, 0xC7, 0x00, 0x8C, 0x03, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x3E, 0x83, 0xC0, 0x0C),

    // mov ptr [D3DRS_FillMode],ecx
    OV_MATCH(0x43, 0x89),

    // retn 0x04
    OV_MATCH(0x4A, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
//54240E8BF981
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x23, 0x54 },
    { 0x24, 0x24 },
    { 0x25, 0x0E },
    { 0x26, 0x8B },
    { 0x27, 0xF9 },
    { 0x28, 0x81 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
//6C1E04008D91
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },

    { 0x22, 0x6C },
    { 0x23, 0x1E },
    { 0x24, 0x04 },
    { 0x25, 0x00 },
    { 0x26, 0x8D },
    { 0x27, 0x91 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
//0020030800894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x1D, 0x4C },

    { 0x21, 0x00 },
    { 0x22, 0x20 },
    { 0x23, 0x03 },
    { 0x24, 0x08 },
    { 0x25, 0x00 },
    { 0x26, 0x89 },
    { 0x27, 0x48 },
    { 0x28, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
//E00A040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor,
                         1036)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x1D, 0x4C },

    { 0x23, 0xE0 },
    { 0x24, 0x0A },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_VertexBlend
// ******************************************************************
//81CA00020000568B35
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_VertexBlend,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x06, 0x81 },
    { 0x07, 0xCA },
    { 0x08, 0x00 },
    { 0x09, 0x02 },
    { 0x0A, 0x00 },
    { 0x0B, 0x00 },
    { 0x0C, 0x56 },
    { 0x0D, 0x8B },
    { 0x0E, 0x35 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
//18C700BC1704
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_LogicOp,
                         1048)
OOVPA_SIG_MATCH(

    // XREF_ENTRY( 0x34, XREF_D3DRS_LogicOp ),

    { 0x01, 0x8B },

    { 0x23, 0x18 },
    { 0x24, 0xC7 },
    { 0x25, 0x00 },
    { 0x26, 0xBC },
    { 0x27, 0x17 },
    { 0x28, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
//7003040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilFail,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x22, 0x33 },

    { 0x60, 0x70 },
    { 0x61, 0x03 },
    { 0x62, 0x04 },
    { 0x63, 0x00 },
    { 0x64, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
//00A00304008948
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FrontFace,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x21, 0x00 },
    { 0x22, 0xA0 },
    { 0x23, 0x03 },
    { 0x24, 0x04 },
    { 0x25, 0x00 },
    { 0x26, 0x89 },
    { 0x27, 0x48 },
    //
);

// ******************************************************************
// * D3DDevice_CreateTexture
// ******************************************************************
//206A00508B44241451
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateTexture,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x10, 0x20 },
    { 0x11, 0x6A },
    { 0x12, 0x00 },
    { 0x13, 0x50 },
    { 0x14, 0x8B },
    { 0x15, 0x44 },
    { 0x16, 0x24 },
    { 0x17, 0x14 },
    { 0x18, 0x51 },

    { 0x29, 0x5F },
    { 0x2A, 0xC2 },
    { 0x2B, 0x1C },
    //
);

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
//816608FFE7FFFF5EC3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_End,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x3D, 0x81 },
    { 0x3E, 0x66 },
    { 0x3F, 0x08 },
    { 0x40, 0xFF },
    { 0x41, 0xE7 },
    { 0x42, 0xFF },
    { 0x43, 0xFF },
    { 0x44, 0x5E },
    { 0x45, 0xC3 },
    //
);

// ******************************************************************
// * D3DTexture_GetLevelDesc
// ******************************************************************
// * NOTE: We are actually intercepting Get2DSurfaceDesc, because
// *       GetLevelDesc Simply redirects to that function
// ******************************************************************
//7909C74608010000 ...C3
OOVPA_SIG_HEADER_NO_XREF(Get2DSurfaceDesc_0,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x0F },
    { 0x01, 0xB6 },

    { 0x29, 0x79 },
    { 0x2A, 0x09 },
    { 0x2B, 0xC7 },
    { 0x2C, 0x46 },
    { 0x2D, 0x08 },
    { 0x2E, 0x01 },
    { 0x2F, 0x00 },
    { 0x30, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetShaderConstantMode
// ******************************************************************
//8B442404A810538B1D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetShaderConstantMode,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0xA8 },
    { 0x05, 0x10 },
    { 0x06, 0x53 },
    { 0x07, 0x8B },
    { 0x08, 0x1D },

    { 0x1F, 0xFF },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
//F6C30155568B35
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_OFFSET_D3DDevice__m_VertexShader), // Derived (OK, yet unverified)

    { 0x00, 0x51 },
    { 0x01, 0x53 },
    { 0x02, 0x8B },
    { 0x03, 0x5C },
    { 0x04, 0x24 },
    { 0x05, 0x0C },
    { 0x06, 0xF6 },
    { 0x07, 0xC3 },
    { 0x08, 0x01 },
    { 0x09, 0x55 },
    { 0x0A, 0x56 },
    { 0x0B, 0x8B },
    { 0x0C, 0x35 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant
// ******************************************************************
//83C160C1E202A810
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x14, 0x83 },
    { 0x15, 0xC1 },
    { 0x16, 0x60 },
    { 0x17, 0xC1 },
    { 0x18, 0xE2 },
    { 0x19, 0x02 },
    { 0x1A, 0xA8 },
    { 0x1B, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVertices
// ******************************************************************
//56576A0053E8
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawVertices,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x07, 0x56 },
    { 0x08, 0x57 },
    { 0x09, 0x6A },
    { 0x0A, 0x00 },
    { 0x0B, 0x53 },
    { 0x0C, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_Clear
// ******************************************************************
//FFFDFFFF8944
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Clear,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x40, 0xFF },
    { 0x41, 0xFD },
    { 0x42, 0xFF },
    { 0x43, 0xFF },
    { 0x44, 0x89 },
    { 0x45, 0x44 },
    //
);

// ******************************************************************
// * D3DDevice_GetDepthStencilSurface
// ******************************************************************
//B866087688..C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetDepthStencilSurface,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x40, 0xB8 },
    { 0x41, 0x66 },
    { 0x42, 0x08 },
    { 0x43, 0x76 },
    { 0x44, 0x88 },

    { 0x46, 0xC2 },
    { 0x47, 0x04 },
    { 0x48, 0x00 },
    //
);

//******************************************************************
//* D3DDevice_SetTile
//******************************************************************
//B9060000008D7C2410F3 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTile_0,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x1C, 0xB9 },
    { 0x1D, 0x06 },
    { 0x1E, 0x00 },
    { 0x1F, 0x00 },
    { 0x20, 0x00 },
    { 0x21, 0x8D },
    { 0x22, 0x7C },
    { 0x23, 0x24 },
    { 0x24, 0x10 },
    { 0x25, 0xF3 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//5533ED3BD5565775
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTarget,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x54 },

    { 0x0E, 0x55 },
    { 0x0F, 0x33 },
    { 0x10, 0xED },
    { 0x11, 0x3B },
    { 0x12, 0xD5 },
    { 0x13, 0x56 },
    { 0x14, 0x57 },
    { 0x15, 0x75 },
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShader
//******************************************************************
//C7009C1E040089 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_0__LTCG_eax_Address_ecx_Handle,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },

    { 0x59, 0xC7 },
    { 0x5A, 0x00 },
    { 0x5B, 0x9C },
    { 0x5C, 0x1E },
    { 0x5D, 0x04 },
    { 0x5E, 0x00 },
    { 0x5F, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData2f
// ******************************************************************
//8D....801808008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData2f,
                         1036)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x20, 0x8D },

    { 0x23, 0x80 },
    { 0x24, 0x18 },
    { 0x25, 0x08 },
    { 0x26, 0x00 },
    { 0x27, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexData4f
// ******************************************************************
//B918150000EB09
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexData4f,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x25, 0xB9 },
    { 0x26, 0x18 },
    { 0x27, 0x15 },
    { 0x28, 0x00 },
    { 0x29, 0x00 },
    { 0x2A, 0xEB },
    { 0x2B, 0x09 },
    //
);

// ******************************************************************
// * D3DCubeTexture_GetCubeMapSurface2
// ******************************************************************
//83EC08578B7C24108D
OOVPA_SIG_HEADER_NO_XREF(D3DCubeTexture_GetCubeMapSurface2,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x57 },
    { 0x04, 0x8B },
    { 0x05, 0x7C },
    { 0x06, 0x24 },
    { 0x07, 0x10 },
    { 0x08, 0x8D },
    //
);

// ******************************************************************
// * D3DResource_GetType
// ******************************************************************
//7728741E85C0
OOVPA_SIG_HEADER_NO_XREF(D3DResource_GetType,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x4C },

    { 0x10, 0x77 },
    { 0x11, 0x28 },
    { 0x12, 0x74 },
    { 0x13, 0x1E },
    { 0x14, 0x85 },
    { 0x15, 0xC0 },
    //
);

// ******************************************************************
// * D3DDevice_Begin
// ******************************************************************
//814E08000800005EC204
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Begin,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x33, 0x81 },
    { 0x34, 0x4E },
    { 0x35, 0x08 },
    { 0x36, 0x00 },
    { 0x37, 0x08 },
    { 0x38, 0x00 },
    { 0x39, 0x00 },
    { 0x3A, 0x5E },
    { 0x3B, 0xC2 },
    { 0x3C, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShaderConstant
// ******************************************************************
//44242085C08974240C894C24
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShaderConstant,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x14, 0x44 },
    { 0x15, 0x24 },
    { 0x16, 0x20 },
    { 0x17, 0x85 },
    { 0x18, 0xC0 },
    { 0x19, 0x89 },
    { 0x1A, 0x74 },
    { 0x1B, 0x24 },
    { 0x1C, 0x0C },
    { 0x1D, 0x89 },
    { 0x1E, 0x4C },
    { 0x1F, 0x24 },
    //
);

// ******************************************************************
// * D3DDevice_GetViewportOffsetAndScale_0
// ******************************************************************
//000085F6577D06D805 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetViewportOffsetAndScale_0,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0xDB },

    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x85 },
    { 0x16, 0xF6 },
    { 0x17, 0x57 },
    { 0x18, 0x7D },
    { 0x19, 0x06 },
    { 0x1A, 0xD8 },
    { 0x1B, 0x05 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
//8B4D08C700FC17040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawVerticesUP,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x2A, 0x8B },
    { 0x2B, 0x4D },
    { 0x2C, 0x08 },
    { 0x2D, 0xC7 },
    { 0x2E, 0x00 },
    { 0x2F, 0xFC },
    { 0x30, 0x17 },
    { 0x31, 0x04 },
    { 0x32, 0x00 },
    { 0x33, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//C700B402040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1072)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x74, 0xC7 },
    { 0x75, 0x00 },
    { 0x76, 0xB4 },
    { 0x77, 0x02 },
    { 0x78, 0x04 },
    { 0x79, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
//04C700941E080083 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x3C, 0x04 },
    { 0x3D, 0xC7 },
    { 0x3E, 0x00 },
    { 0x3F, 0x94 },
    { 0x40, 0x1E },
    { 0x41, 0x08 },
    { 0x42, 0x00 },
    { 0x43, 0x83 },

    { 0x84, 0x5E },
    { 0x85, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
//008107000008008B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginPushBuffer,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x48, 0x00 },
    { 0x49, 0x81 },
    { 0x4A, 0x07 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },
    { 0x4D, 0x08 },
    { 0x4E, 0x00 },
    { 0x4F, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_EndPushBuffer
// ******************************************************************
//B82908768859
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_EndPushBuffer,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x56 },

    { 0x09, 0x6A },
    { 0x0A, 0x00 },

    { 0x4E, 0x7B },
    { 0x4F, 0xFF },
    { 0x50, 0xFF },
    { 0x51, 0xFF },
    { 0x52, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
//81E1FFFFFF0F4189 ...C20800
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x90, 0x81 },
    { 0x91, 0xE1 },
    { 0x92, 0xFF },
    { 0x93, 0xFF },
    { 0x94, 0xFF },
    { 0x95, 0x0F },
    { 0x96, 0x41 },
    { 0x97, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
//85C0740F50FF15
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_PersistDisplay,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x01, 0x53 },

    { 0x2F, 0xB8 },
    { 0x30, 0x05 },
    { 0x31, 0x40 },
    { 0x32, 0x00 },
    { 0x33, 0x80 },
    { 0x34, 0x5B },
    { 0x35, 0x59 },
    { 0x36, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetGammaRamp
// ******************************************************************
//C78498DC07000001000000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetGammaRamp,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x2E, 0x8B },
    { 0x2F, 0xFB },
    { 0x30, 0xF3 },
    { 0x31, 0xA5 },
    { 0x32, 0xF6 },
    { 0x33, 0x44 },
    { 0x34, 0x24 },
    { 0x35, 0x10 },
    { 0x36, 0x02 },
    { 0x37, 0x89 },
    //
);

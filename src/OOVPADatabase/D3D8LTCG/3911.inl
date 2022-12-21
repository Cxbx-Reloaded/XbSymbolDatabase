// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->3911.inl
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
// * Direct3D_CreateDevice
// ******************************************************************
//85C9750AC705 ...C21000
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice_16__LTCG_eax_BehaviorFlags_ebx_ppReturnedDeviceInterface,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    { 0x06, 0x85 },
    { 0x07, 0xC9 },
    { 0x08, 0x75 },
    { 0x09, 0x0A },
    { 0x0A, 0xC7 },
    { 0x0B, 0x05 },

    { 0x28, 0x56 },
    { 0x29, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
//C7000803040075
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      1045,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived
    XREF_ENTRY(0x2D, XREF_D3DRS_CullMode), // Derived

    { 0x00, 0x56 },

    { 0x1B, 0xC7 },
    { 0x1C, 0x00 },
    { 0x1D, 0x08 },
    { 0x1E, 0x03 },
    { 0x1F, 0x04 },
    { 0x20, 0x00 },
    { 0x21, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_VertexBlend
// ******************************************************************
//C70028030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_VertexBlend,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x24, 0xC7 },
    { 0x25, 0x00 },
    { 0x26, 0x28 },
    { 0x27, 0x03 },
    { 0x28, 0x04 },
    { 0x29, 0x00 },
    { 0x2A, 0x89 },
    { 0x2B, 0x48 },
    { 0x2C, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BumpEnv
// ******************************************************************
//000085C08BDF75 ...C20800
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BumpEnv_8,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0x85 },
    { 0x17, 0xC0 },
    { 0x18, 0x8B },
    { 0x19, 0xDF },
    { 0x1A, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
//C9C7000C03040089480483
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x2F, 0xC9 },
    { 0x30, 0xC7 },
    { 0x31, 0x00 },
    { 0x32, 0x0C },
    { 0x33, 0x03 },
    { 0x34, 0x04 },
    { 0x35, 0x00 },
    { 0x36, 0x89 },
    { 0x37, 0x48 },
    { 0x38, 0x04 },
    { 0x39, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TextureFactor
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TextureFactor,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x08, 0x86 },
    //{ 0x09, 0x84 },
    //{ 0x0A, 0x07 },
    { 0x0B, 0x00 },
    { 0x0C, 0x00 },
    { 0x0D, 0x85 },
    { 0x0E, 0xC0 },
    { 0x0F, 0x75 },

    { 0x11, 0x8B },
    { 0x12, 0x06 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_YuvEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_YuvEnable,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_D3DRS_YuvEnable),

    { 0x01, 0x44 },
    { 0x04, 0x56 },
    { 0x05, 0x8B },
    { 0x06, 0x35 },
    { 0x0B, 0xA3 },
    { 0x11, 0x06 },
    { 0x15, 0x72 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_OcclusionCullEnable
// ******************************************************************
//568BD0E8
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_OcclusionCullEnable,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_D3DRS_OcclusionCullEnable),

    { 0x00, 0x8B },
    { 0x06, 0x35 },

    //{ 0x26, 0x56 },
    //{ 0x27, 0x8B },
    //{ 0x28, 0xD0 },
    //{ 0x29, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//538BD9C1E107 ...C3
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_0,
                      2039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x08, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x53 },
    { 0x01, 0x8B },
    { 0x02, 0xD9 },
    { 0x03, 0xC1 },
    { 0x04, 0xE1 },
    { 0x05, 0x07 },

    { 0x13, 0x25 },
    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0xFF },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//C1..0681..241B040089 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor_0,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x1C, 0xC1 },
    { 0x1D, 0xE1 },
    { 0x1E, 0x06 },
    { 0x1F, 0x81 },
    { 0x20, 0xC1 },
    { 0x21, 0x24 },
    { 0x22, 0x1B },
    { 0x23, 0x04 },
    { 0x24, 0x00 },
    { 0x25, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
//83C008C1E707890689 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_0,
                         2024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x26, 0x83 },
    { 0x27, 0xC0 },
    { 0x28, 0x08 },
    { 0x29, 0xC1 },
    { 0x2A, 0xE7 },
    { 0x2B, 0x07 },
    { 0x2C, 0x89 },
    { 0x2D, 0x06 },
    { 0x2E, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZBias
// ******************************************************************
//24..8BF07D06D805
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZBias,
                         1048)
OOVPA_SIG_MATCH(

    // XREF_ENTRY( 0x6A, XREF_D3DRS_ZBias ),

    { 0x00, 0x51 },
    { 0x01, 0x53 },

    { 0x17, 0x24 },
    //{ 0x18, 0x10 },
    { 0x19, 0x8B },
    { 0x1A, 0xF0 },
    { 0x1B, 0x7D },
    { 0x1C, 0x06 },
    { 0x1D, 0xD8 },
    { 0x1E, 0x05 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LineWidth
// ******************************************************************
//44240C57D88E
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_LineWidth,
                         1024)
OOVPA_SIG_MATCH(


    // XREF_ENTRY( 0x5B, XREF_D3DRS_LineWidth ),

    { 0x02, 0x5C },

    { 0x11, 0x44 },
    { 0x12, 0x24 },
    { 0x13, 0x0C },
    { 0x14, 0x57 },
    { 0x15, 0xD8 },
    { 0x16, 0x8E },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilCullEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilCullEnable,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_D3DRS_StencilCullEnable),

    { 0x01, 0x44 },
    { 0x04, 0x56 },
    { 0x05, 0x8B },
    { 0x06, 0x35 },
    { 0x0B, 0xA3 },
    { 0x11, 0x06 },
    { 0x15, 0x72 },
    //
);

//******************************************************************
//* D3DDevice_SetRenderState_BackFillMode
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_BackFillMode,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x06, XREF_D3DRS_FillMode),
    XREF_ENTRY(0x0B, XREF_D3DRS_BackFillMode),

    { 0x01, 0x44 },
    { 0x0F, 0x89 },
    { 0x10, 0x4C },
    { 0x11, 0x24 },
    { 0x12, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
//0020030800894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x12, 0x4C },

    { 0x1A, 0x00 },
    { 0x1B, 0x20 },
    { 0x1C, 0x03 },
    { 0x1D, 0x08 },
    { 0x1E, 0x00 },
    { 0x1F, 0x89 },
    { 0x20, 0x48 },
    { 0x21, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
//C98B4C24087502
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FillMode,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x08, 0x06 },

    { 0x22, 0xC9 },
    { 0x23, 0x8B },
    { 0x24, 0x4C },
    { 0x25, 0x24 },
    { 0x26, 0x08 },
    { 0x27, 0x75 },
    { 0x28, 0x02 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
//54240E8BF981
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x1C, 0x54 },
    { 0x1D, 0x24 },
    { 0x1E, 0x0E },
    { 0x1F, 0x8B },
    { 0x20, 0xF9 },
    { 0x21, 0x81 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleAntiAlias
// ******************************************************************
//C1E11083E20F
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleAntiAlias,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_D3DRS_MultiSampleAntiAlias),

    { 0x00, 0x8B },

    { 0x36, 0xC1 },
    { 0x37, 0xE1 },
    { 0x38, 0x10 },
    { 0x39, 0x83 },
    { 0x3A, 0xE2 },
    { 0x3B, 0x0F },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleMask
// ******************************************************************
//83E10FC1E210
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleMask,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_D3DRS_MultiSampleMask),

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x36, 0x83 },
    { 0x37, 0xE1 },
    { 0x38, 0x0F },
    { 0x39, 0xC1 },
    { 0x3A, 0xE2 },
    { 0x3B, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
//18C700BC1704
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_LogicOp,
                         1024)
OOVPA_SIG_MATCH(

    // XREF_ENTRY( 0x2D, XREF_D3DRS_LogicOp ),

    { 0x01, 0x8B },

    { 0x1C, 0x18 },
    { 0x1D, 0xC7 },
    { 0x1E, 0x00 },
    { 0x1F, 0xBC },
    { 0x20, 0x17 },
    { 0x21, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
//A4030400894804
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x1B, 0xA4 },
    { 0x1C, 0x03 },
    { 0x1D, 0x04 },
    { 0x1E, 0x00 },
    { 0x1F, 0x89 },
    { 0x20, 0x48 },
    { 0x21, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
//7003040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilFail,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x1B, 0x33 },

    { 0x59, 0x70 },
    { 0x5A, 0x03 },
    { 0x5B, 0x04 },
    { 0x5C, 0x00 },
    { 0x5D, 0x89 },
    //
);

//******************************************************************
//* D3DDevice_SetRenderState_TwoSidedLighting
//******************************************************************
//834808208B
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_D3DRS_TwoSidedLighting),

    { 0x00, 0xA1 },

    { 0x05, 0x83 },
    { 0x06, 0x48 },
    { 0x07, 0x08 },
    { 0x08, 0x20 },
    { 0x09, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
//00A00304008948
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FrontFace,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x1A, 0x00 },
    { 0x1B, 0xA0 },
    { 0x1C, 0x03 },
    { 0x1D, 0x04 },
    { 0x1E, 0x00 },
    { 0x1F, 0x89 },
    { 0x20, 0x48 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
//6C1E04008D91
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },

    { 0x1B, 0x6C },
    { 0x1C, 0x1E },
    { 0x1D, 0x04 },
    { 0x1E, 0x00 },
    { 0x1F, 0x8D },
    { 0x20, 0x91 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
//018b54240885d2c700
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilEnable,
                         1024)
OOVPA_SIG_MATCH(

    { 0x02, 0x35 },

    { 0x48, 0x01 },
    { 0x49, 0x8B },
    { 0x4A, 0x54 },
    { 0x4B, 0x24 },
    { 0x4C, 0x08 },
    { 0x4D, 0x85 },
    { 0x4E, 0xD2 },
    { 0x4F, 0xC7 },
    { 0x50, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexShader
// ******************************************************************
//241833f685ed
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateVertexShader,
                         1024)
OOVPA_SIG_MATCH(

    { 0x04, 0x6C },
    { 0x0C, 0x0F },
    { 0x1A, 0x24 },
    { 0x1B, 0x18 },
    { 0x1C, 0x33 },
    { 0x1D, 0xF6 },
    { 0x1E, 0x85 },
    { 0x1F, 0xED },
    //
);

// ******************************************************************
// * D3DDevice_SetShaderConstantMode
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetShaderConstantMode_0__LTCG_eax1,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x05, XREF_D3D_g_pDevice),

    // test al,0x10
    OV_MATCH(0x00, 0xA8, 0x10),

    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x03, 0x8B, 0x1D),

    // or ecx,0x200
    OV_MATCH(0x0E, 0x81, 0xC9, 0x00, 0x02, 0x00, 0x00),

    // mov ???,???
    OV_MATCH(0x2E, 0x8B), // Unique OV to determine if function is LTCG.
    // Offset 0x2F and later had change over time.
);

// ******************************************************************
// * D3DDevice_Clear
// ******************************************************************
//FFFDFFFF8944
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Clear,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x42, 0xFF },
    { 0x43, 0xFD },
    { 0x44, 0xFF },
    { 0x45, 0xFF },
    { 0x46, 0x89 },
    { 0x47, 0x44 },
    //
);

// ******************************************************************
// * D3DResource_Release
// ******************************************************************
//578B7C24088B078BC881E1FFFF0000
OOVPA_SIG_HEADER_NO_XREF(D3DResource_Release,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x57 },
    { 0x01, 0x8B },
    { 0x02, 0x7C },
    { 0x03, 0x24 },
    { 0x04, 0x08 },
    { 0x05, 0x8B },
    { 0x06, 0x07 },
    { 0x07, 0x8B },
    { 0x08, 0xC8 },
    { 0x09, 0x81 },
    { 0x0A, 0xE1 },
    { 0x0B, 0xFF },
    { 0x0C, 0xFF },
    { 0x0D, 0x00 },
    { 0x0E, 0x00 },
    //
);

//******************************************************************
//* D3DDevice_SetTile
//******************************************************************
//C744242000000000C744241C ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTile_0,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x2C, 0xC7 },
    { 0x2D, 0x44 },
    { 0x2E, 0x24 },
    { 0x2F, 0x20 },
    { 0x30, 0x00 },
    { 0x31, 0x00 },
    { 0x32, 0x00 },
    { 0x33, 0x00 },
    { 0x34, 0xC7 },
    { 0x35, 0x44 },
    { 0x36, 0x24 },
    { 0x37, 0x1C },
    //
);

// ******************************************************************
// * D3DDevice_Present
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Present,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x56 },
    { 0x04, 0x8B },
    { 0x05, 0x35 },

    { 0x0B, 0x6A },
    { 0x0C, 0x02 },
    { 0x0D, 0xE8 },
    { 0x12, 0x8B },
    { 0x13, 0x86 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x8B },
    { 0x19, 0x8E },
    { 0x1C, 0x00 },
    { 0x1D, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
//C700FC1704008B57
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVerticesUP,
                         1024)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x05, 0x14 },

    { 0x2F, 0xC7 },
    { 0x30, 0x00 },
    { 0x31, 0xFC },
    { 0x32, 0x17 },
    { 0x33, 0x04 },
    { 0x34, 0x00 },
    { 0x35, 0x8B },
    { 0x36, 0x57 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVertices
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVertices,
                         1024)
OOVPA_SIG_MATCH(

    // push ebp
    OV_MATCH(0x00, 0x55),

    // mov eax, [esi+0x0478]
    OV_MATCH(0x0D, 0x8B, 0x86, 0x78, 0x04, 0x00, 0x00),

    // mov dword ptr [eax], 000417FC
    OV_MATCH(0x51, 0xC7, 0x00, 0xFC, 0x17, 0x04, 0x00),

    // lea ebx, [ebx+0]
    OV_MATCH(0x15A, 0x8D, 0x9B),
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
//F6C30155568B35 ...C3
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader_0,
                      2024,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0D, XREF_OFFSET_D3DDevice__m_VertexShader), // Derived (confirmed)

    { 0x00, 0xF6 },
    { 0x01, 0xC3 },
    { 0x02, 0x01 },
    { 0x03, 0x55 },
    { 0x04, 0x56 },
    { 0x05, 0x8B },
    { 0x06, 0x35 },

    { 0x15, 0x74 },
    { 0x16, 0x05 },
    { 0x17, 0x8D },
    { 0x18, 0x7B },
    { 0x19, 0xFF },
    { 0x1A, 0xEB },
    { 0x1B, 0x0E },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//75448B..000B00008B..080B00008B..040B0000
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x13, 0x75 },
    { 0x14, 0x44 },
    { 0x15, 0x8B },
    { 0x17, 0x00 },
    { 0x18, 0x0B },
    { 0x19, 0x00 },
    { 0x1A, 0x00 },
    { 0x1B, 0x8B },
    { 0x1D, 0x08 },
    { 0x1E, 0x0B },
    { 0x1F, 0x00 },
    { 0x20, 0x00 },
    { 0x21, 0x8B },
    { 0x23, 0x04 },
    { 0x24, 0x0B },
    { 0x25, 0x00 },
    { 0x26, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      3911,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    // TODO: Need to fix 3925 to able detect function below
    XREF_ENTRY(0xEB, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // lea edi, [param_1 + 0x22]
    OV_MATCH(0x09, 0x8D, 0x78, 0x22), // 3911 0x22 vs 5344 0x21 value
    // shl edi,0x6
    OV_MATCH(0x0C, 0xC1, 0xE7, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x11, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xEA, 0xE8),

    // ret
    OV_MATCH(0xF9, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant
// ******************************************************************
//83C160C1E202A810 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant_8,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x13, 0x83 },
    { 0x14, 0xC1 },
    { 0x15, 0x60 },
    { 0x16, 0xC1 },
    { 0x17, 0xE2 },
    { 0x18, 0x02 },
    { 0x19, 0xA8 },
    { 0x1A, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
//894804C700FC1704008B ...C20C00
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawVerticesUP_12,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x2B, 0x89 },
    { 0x2C, 0x48 },
    { 0x2D, 0x04 },
    { 0x2E, 0xC7 },
    { 0x2F, 0x00 },
    { 0x30, 0xFC },
    { 0x31, 0x17 },
    { 0x32, 0x04 },
    { 0x33, 0x00 },
    { 0x34, 0x8B },
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShader
//******************************************************************
//C7009C1E04008B ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_0__LTCG_eax_Address_ecx_Handle,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x3F, 0xC7 },
    { 0x40, 0x00 },
    { 0x41, 0x9C },
    { 0x42, 0x1E },
    { 0x43, 0x04 },
    { 0x44, 0x00 },
    { 0x45, 0x8B },
    //
);

//******************************************************************
//* D3DDevice_SelectVertexShader
//******************************************************************
//C740040600000083 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_4,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x03, 0x8B },

    { 0x46, 0xC7 },
    { 0x47, 0x40 },
    { 0x48, 0x04 },
    { 0x49, 0x06 },
    { 0x4A, 0x00 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },
    { 0x4D, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_DeleteVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeleteVertexShader_0,
                         3911)
OOVPA_SIG_MATCH(

    // mov ecx,[eax + -0x1]
    OV_MATCH(0x00, 0x8B, 0x48, 0xFF),
    // dec eax
    // dec ecx
    OV_MATCH(0x03, 0x48, 0x49),
    // mov [eax],ecx
    OV_MATCH(0x05, 0x89, 0x08),
    // jnz
    OV_MATCH(0x07, 0x75, 0x06),

    // call LocalFree
    OV_MATCH(0x0A, 0xE8),

    OV_MATCH(0x0F, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 1024, 11)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget,
           1024,
           1 + 11,
           XRefOne)
{

    XREF_ENTRY(0x17, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0x20
        OV_MATCH(0x00, 0x83, 0xEC),

            // D3DDevice_SetRenderTarget+0x4A : mov eax, 0x00000001
            OV_MATCH(0x4A, 0xB8, 0x01, 0x00),

            // D3DDevice_SetRenderTarget+0x4F : and ecx, 0x0F
            OV_MATCH(0x4F, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0x56 : shr eax,0x0C
            OV_MATCH(0x56, 0xC1, 0xE8, 0x0C),
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//EB06894424088BF8
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x25, 0xEB },
    { 0x26, 0x06 },
    { 0x27, 0x89 },
    { 0x28, 0x44 },
    { 0x29, 0x24 },
    { 0x2A, 0x08 },
    { 0x2B, 0x8B },
    { 0x2C, 0xF8 },
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
//81C10000F8FF89 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTexture_4__LTCG_eax_pTexture,
                         2024)
OOVPA_SIG_MATCH(

    // sub esp, ...
    OV_MATCH(0x00, 0x83, 0xEC),

    // mov esi, eax
    OV_MATCH(0x1A, 0x8B, 0xF0),

    // add ecx, 0FFF80000h; mov ...
    OV_MATCH(0x27, 0x81, 0xC1, 0x00, 0x00, 0xF8, 0xFF, 0x89),
    //
);

// ******************************************************************
// * D3D_BlockOnResource
// ******************************************************************
//00007800750C85 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource_0,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x15 },

    { 0x28, 0xF7 },
    { 0x29, 0xC1 },
    { 0x2A, 0x00 },
    { 0x2B, 0x00 },
    { 0x2C, 0x78 },
    { 0x2D, 0x00 },
    { 0x2E, 0x75 },
    { 0x2F, 0x0C },
    { 0x30, 0x85 },
    //
);

// ******************************************************************
// * D3DDevice_SetStreamSource
// ******************************************************************
//7406810300000800
OOVPA_SIG_HEADER_XREF(D3DDevice_SetStreamSource_8__LTCG_edx_StreamNumber,
                      1039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x47, XREF_D3D_g_Stream), // Derived

    { 0x00, 0x53 },
    { 0x01, 0x8B },
    { 0x02, 0x1D },

    { 0x38, 0x81 },
    { 0x39, 0x45 },
    { 0x3A, 0x00 },
    { 0x3B, 0x00 },
    { 0x3C, 0x00 },
    { 0x3D, 0x08 },
    { 0x3E, 0x00 },
    { 0x3F, 0x8D },
    //
);

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPixelShader_0__LTCG_eax_handle,
                         2060)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x5C, 0xC7 },
    { 0x5D, 0x40 },
    { 0x5E, 0x04 },
    { 0x5F, 0x00 },
    { 0x60, 0x00 },
    { 0x61, 0x21 },
    { 0x62, 0x00 },
    { 0x63, 0x83 },
    { 0x64, 0xC0 },
    { 0x65, 0x08 },

    { 0x6A, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_BlockUntilVerticalBlank
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
// NOTE: Later XDK version start to use std signature.
// NOTE: NASCAR Heat 2002 reveal this function is inlined, need some sort of indicator which is inline or not.
OOVPA_SIG_HEADER_XREF(D3DDevice_BlockUntilVerticalBlank,
                      1024,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // D3DDevice_BlockUntilVerticalBlank+0x00 : mov eax, [D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // D3DDevice_BlockUntilVerticalBlank+0x17 : add eax, OFFSET_D3DDevice__m_VerticalBlankEvent
    XREF_ENTRY(0x18, XREF_OFFSET_D3DDevice__m_VerticalBlankEvent),

    // D3DDevice_BlockUntilVerticalBlank+0x00 : mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // D3DDevice_BlockUntilVerticalBlank+0x05 : push 0; push 0; push 1
    OV_MATCH(0x05, 0x6A, 0x00, 0x6A, 0x00, 0x6A, 0x01),

    // D3DDevice_BlockUntilVerticalBlank+0x0B : mov dword ptr [eax+OFFSET_D3DDEVICE_M_???],
    OV_MATCH(0x0B, 0xC7, 0x80),

    // D3DDevice_BlockUntilVerticalBlank+0x15 : push 6
    OV_MATCH(0x15, 0x6A, 0x06),

    // D3DDevice_BlockUntilVerticalBlank+0x17 : add eax, OFFSET_D3DDevice__m_VerticalBlankEvent
    OV_MATCH(0x17, 0x05),

    // D3DDevice_BlockUntilVerticalBlank+0x1D : call [KeWaitForSingleObject]
    OV_MATCH(0x1D, 0xFF, 0x15),

    // D3DDevice_BlockUntilVerticalBlank+0x23 : mov eax,[addr]
    OV_MATCH(0x23, 0xA1), // NOTE: std has a ret here and isn't a extended function.

    //
);

// ******************************************************************
// * D3D_DestroyResource
// ******************************************************************
// Generic OOVPA as of 3911 and newer.
OOVPA_SIG_HEADER_XREF(D3D_DestroyResource__LTCG,
                      3911,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3D_DestroyResource+0x19 : D3D_BlockOnResource
    XREF_ENTRY(0x1A, XREF_D3D_BlockOnResource),

    // D3D_DestroyResource+0x00 : mov eax, [edi]
    OV_MATCH(0x00, 0x8B, 0x07), // LTCG offset 0x00 vs STD offset 0x06

    // D3D_DestroyResource+0x05 : and esi, $70000
    OV_MATCH(0x05, 0x81, 0xE6, 0x00, 0x00, 0x07, 0x00),

    // D3D_DestroyResource+0x0B : cmp esi, $50000
    OV_MATCH(0x0B, 0x81, 0xFE, 0x00, 0x00, 0x05, 0x00),

    // D3D_DestroyResource+0x17 : mov e__,e__
    OV_MATCH(0x17, 0x8B), // LTCG mov e__,e__ vs STD push edi

    // relative to 0x00; LTCG offset 0x24 vs STD offset 0x22
    // D3D_DestroyResource+0x24 : cmp esi, $50000
    OV_MATCH(0x24, 0x81, 0xFE, 0x00, 0x00, 0x05, 0x00),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderStateInline__ManualFindGeneric
// ******************************************************************
// NOTE: This signature will find any generic match with D3D_g_RenderState
//       Currently, this is the best method if
//       D3DDevice_SetRenderStateNotInline detection is absent.
//       This OOVPA itself is not a symbol.
OOVPA_SIG_HEADER_XREF_DETECT(D3DDevice_SetRenderStateInline__ManualFindGeneric,
                             3911,
                             XRefTwo,
                             DetectFirst)
OOVPA_SIG_MATCH(
    // call D3DDevice_SetRenderState_Simple
    XREF_ENTRY(0x15, XREF_D3DDevice_SetRenderState_Simple),
    XREF_ENTRY(0x1C, XREF_D3D_g_RenderState),

    // cmp esi,0x?? // Up until < 4039 is 0x52
    OV_MATCH(0x00, 0x83, 0xFE),

    // mov edi,ptr [ebx + ????]
    OV_MATCH(0x03, 0x8B, 0xBB),

    // jge +0x??
    OV_MATCH(0x09, 0x7D),

    // mov ecx,ptr [esi * 4 + ????]
    OV_MATCH(0x0B, 0x8B, 0x0C, 0xB5),

    // mov edx,edi
    OV_MATCH(0x12, 0x8B, 0xD7),
    // call D3DDevice_SetRenderState_Simple
    OV_MATCH(0x14, 0xE8),

    // mov ptr [esi * 4 + D3D_g_RenderState],edi
    OV_MATCH(0x19, 0x89, 0x3C, 0xB5),
    //
);

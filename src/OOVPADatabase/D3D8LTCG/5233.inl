// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5233.inl
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
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush,
                      1036,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x01, XREF_D3D_g_pDevice),

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x10, XREF_D3D_g_pDevice),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x00, 0xA1),

    // push 0x00
    OV_MATCH(0x06, 0x6A, 0x00),

    // mov e??,[esp + param_1]
    OV_MATCH(0x16, 0x8B),
    OV_MATCH(0x18, 0x24, 0x08),
    // mov ecx,[ecx + 0x4]
    OV_MATCH(0x1A, 0x8B, 0x49, 0x04),

    // lea ????
    OV_MATCH(0x1D, 0x8D),
    //
);

// ******************************************************************
// * D3DDevice_GetBackBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetBackBuffer2_0__LTCG_eax1,
                      5233,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov e?x,[D3D_g_pDevice]
    XREF_ENTRY(0x05, XREF_D3D_g_pDevice),

    // call D3DResource::AddRef
    XREF_ENTRY(0x3E, XREF_D3DResource_AddRef),

    // cmp eax,-0x1
    OV_MATCH(0x00, 0x83, 0xF8, 0xFF),

    // jnz +0x07
    OV_MATCH(0x09, 0x75, 0x07),
    // mov eax,0x1
    OV_MATCH(0x0B, 0xB8, 0x01, 0x00, 0x00, 0x00),
    // jmp +0x07
    OV_MATCH(0x10, 0xEB, 0x07),
    // neg e?x
    OV_MATCH(0x12, 0xF7),

    // ret
    OV_MATCH(0x46, 0xC3), // 0x46 vs 4627 0x48 offset
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//81E30000FFFFB901 ...C20400
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_4,
                      2052,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x51 },
    { 0x01, 0x53 },

    { 0x40, 0x81 },
    { 0x41, 0xE3 },
    { 0x42, 0x00 },
    { 0x43, 0x00 },
    { 0x44, 0xFF },
    { 0x45, 0xFF },
    { 0x46, 0xB9 },
    { 0x47, 0x01 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//8BCEC1E10681C1241B04 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor_0,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x21, 0x8B },
    { 0x22, 0xCE },
    { 0x23, 0xC1 },
    { 0x24, 0xE1 },
    { 0x25, 0x06 },
    { 0x26, 0x81 },
    { 0x27, 0xC1 },
    { 0x28, 0x24 },

    { 0x41, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
//8D0CB5E00A0400 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_0,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x21, 0x8D },
    { 0x22, 0x0C },
    { 0x23, 0xB5 },
    { 0x24, 0xE0 },
    { 0x25, 0x0A },
    { 0x26, 0x04 },
    { 0x27, 0x00 },

    { 0x3D, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
//F6C30155568B35 ...C3
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader_0,
                      2036,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0E, XREF_OFFSET_D3DDevice__m_VertexShader), // Derived (unverified, yet should be align base on existing 4 bytes in signatures)

    { 0x00, 0x51 },

    { 0x01, 0xF6 },
    { 0x02, 0xC3 },
    { 0x03, 0x01 },
    { 0x04, 0x55 },
    { 0x05, 0x56 },
    { 0x06, 0x8B },
    { 0x07, 0x35 },

    { 0x1D, 0x74 },
    { 0x1E, 0x05 },
    { 0x1F, 0x8D },
    { 0x20, 0x7B },
    { 0x21, 0xFF },
    { 0x22, 0xEB },
    { 0x23, 0x0E },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstantNotInline
// ******************************************************************
//56578BFBC1E704 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstantNotInline_0,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0xF6 },
    { 0x01, 0x05 },

    { 0x09, 0x56 },
    { 0x0A, 0x57 },
    { 0x0B, 0x8B },
    { 0x0C, 0xFB },
    { 0x0D, 0xC1 },
    { 0x0E, 0xE7 },
    { 0x0F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetPalette
// ******************************************************************
//000085C05774258B4E
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPalette,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x85 },
    { 0x19, 0xC0 },
    { 0x1A, 0x57 },
    { 0x1B, 0x74 },
    { 0x1C, 0x25 },
    { 0x1D, 0x8B },
    { 0x1E, 0x4E },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
//04C700941E080083 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x46, 0x04 },
    { 0x47, 0xC7 },
    { 0x48, 0x00 },
    { 0x49, 0x94 },
    { 0x4A, 0x1E },
    { 0x4B, 0x08 },
    { 0x4C, 0x00 },
    { 0x4D, 0x83 },

    { 0x8E, 0x5E },
    { 0x8F, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShaderDirect
// ******************************************************************
//53568BF185F68BD8741E57B8 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShaderDirect_0,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x56 },
    { 0x02, 0x8B },
    { 0x03, 0xF1 },
    { 0x04, 0x85 },
    { 0x05, 0xF6 },
    { 0x06, 0x8B },
    { 0x07, 0xD8 },
    { 0x08, 0x74 },
    { 0x09, 0x1E },
    { 0x0A, 0x57 },
    { 0x0B, 0xB8 },
    //
);

// ******************************************************************
// * D3D_CommonSetRenderTarget
// ******************************************************************
//8B490CC1E91483E10FB801
OOVPA_SIG_HEADER_NO_XREF(D3D_CommonSetRenderTarget,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x5A, 0x8B },
    { 0x5B, 0x49 },
    { 0x5C, 0x0C },
    { 0x5D, 0xC1 },
    { 0x5E, 0xE9 },
    { 0x5F, 0x14 },
    { 0x60, 0x83 },
    { 0x61, 0xE1 },
    { 0x62, 0x0F },
    { 0x63, 0xB8 },
    { 0x64, 0x01 },
    //
);

//******************************************************************
//* D3DDevice_SetRenderTarget
//******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderTarget_0,
                      2048,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x08, XREF_D3D_CommonSetRenderTarget),

    { 0x00, 0x68 },
    { 0x05, 0x50 },
    { 0x06, 0x51 },
    { 0x07, 0xE8 },
    { 0x0C, 0xC3 },
    //
);

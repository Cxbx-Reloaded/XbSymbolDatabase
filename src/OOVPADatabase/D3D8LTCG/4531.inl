// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->4531.inl
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
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
//51538B5C240C8BC6C1E0 ...C20400
OOVPA_XREF(D3DDevice_SetTextureState_TexCoordIndex_4, 2045, 1 + 10,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x14, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x00, 0x51 },
    { 0x01, 0x53 },
    { 0x02, 0x8B },
    { 0x03, 0x1D },

    { 0x0D, 0x8B },
    { 0x0E, 0xC7 },
    { 0x0F, 0xC1 },
    { 0x10, 0xE0 },
    { 0x11, 0x07 },
    { 0x12, 0x89 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
//8BCEC1E10681C1241B04 ...C20400
OOVPA_NO_XREF(D3DDevice_SetTextureState_BorderColor_4, 2060, 10)
{

    { 0x00, 0x53 },

    { 0x26, 0x8B },
    { 0x27, 0xCE },
    { 0x28, 0xC1 },
    { 0x29, 0xE1 },
    { 0x2A, 0x06 },
    { 0x2B, 0x81 },
    { 0x2C, 0xC1 },
    { 0x2D, 0x24 },

    { 0x47, 0xC2 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
//8D0CB5E00A0400 ...C20400
OOVPA_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor_4, 2060, 9)
{

    { 0x00, 0x53 },

    { 0x26, 0x8D },
    { 0x27, 0x0C },
    { 0x28, 0xB5 },
    { 0x29, 0xE0 },
    { 0x2A, 0x0A },
    { 0x2B, 0x04 },
    { 0x2C, 0x00 },

    { 0x43, 0xC2 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetRenderState_ZBias
// ******************************************************************
//24..8BF07D06D805
OOVPA_NO_XREF(D3DDevice_SetRenderState_ZBias, 1036, 9)
{

    // XREF_ENTRY( 0x6A, XREF_D3DRS_ZBIAS ),

    { 0x00, 0x51 },
    { 0x01, 0x56 },

    { 0x16, 0x24 },
    //{ 0x17, 0x10 },
    { 0x18, 0x8B },
    { 0x19, 0xF0 },
    { 0x1A, 0x7D },
    { 0x1B, 0x06 },
    { 0x1C, 0xD8 },
    { 0x1D, 0x05 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
//7505BB050000008B ...C3
OOVPA_NO_XREF(D3DDevice_Swap_0, 2024, 9)
{

    { 0x01, 0x8B },

    { 0x0C, 0x75 },
    { 0x0D, 0x05 },
    { 0x0E, 0xBB },
    { 0x0F, 0x05 },
    { 0x10, 0x00 },
    { 0x11, 0x00 },
    { 0x12, 0x00 },
    { 0x13, 0x8B },
} OOVPA_END;

//******************************************************************
//* D3DDevice_SelectVertexShader
//******************************************************************
//04C700941E080083 ...C20400
OOVPA_NO_XREF(D3DDevice_SelectVertexShader_4, 2048, 12)
{

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x4B, 0x04 },
    { 0x4C, 0xC7 },
    { 0x4D, 0x00 },
    { 0x4E, 0x94 },
    { 0x4F, 0x1E },
    { 0x50, 0x08 },
    { 0x51, 0x00 },
    { 0x52, 0x83 },

    { 0x95, 0xC2 },
    { 0x96, 0x04 },
} OOVPA_END;

// ******************************************************************
// * CMiniport_InitHardware
// ******************************************************************
//558BEC83EC1053578BF85768
OOVPA_NO_XREF(CMiniport_InitHardware, 1024, 12)
{

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x10 },
    { 0x06, 0x53 },
    { 0x07, 0x57 },
    { 0x08, 0x8B },
    { 0x09, 0xF8 },
    { 0x0A, 0x57 },
    { 0x0B, 0x68 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetFlickerFilter
// ******************************************************************
//6A00566A0B50FF15 ...C3
OOVPA_NO_XREF(D3DDevice_SetFlickerFilter_0, 2024, 10)
{

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x1D, 0x6A },
    { 0x1E, 0x00 },
    { 0x1F, 0x56 },
    { 0x20, 0x6A },
    { 0x21, 0x0B },
    { 0x22, 0x50 },
    { 0x23, 0xFF },
    { 0x24, 0x15 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
//C740040000210083C008 ...C3
OOVPA_NO_XREF(D3DDevice_SetPixelShader_0, 2024, 13)
{

    { 0x00, 0x85 },
    { 0x01, 0xC0 },

    { 0x6D, 0xC7 },
    { 0x6E, 0x40 },
    { 0x6F, 0x04 },
    { 0x70, 0x00 },
    { 0x71, 0x00 },
    { 0x72, 0x21 },
    { 0x73, 0x00 },
    { 0x74, 0x83 },
    { 0x75, 0xC0 },
    { 0x76, 0x08 },

    { 0x7B, 0xC3 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
//008107000008008B
OOVPA_NO_XREF(D3DDevice_BeginPushBuffer_0, 2048, 10)
{

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x43, 0x00 },
    { 0x44, 0x81 },
    { 0x45, 0x07 },
    { 0x46, 0x00 },
    { 0x47, 0x00 },
    { 0x48, 0x08 },
    { 0x49, 0x00 },
    { 0x4A, 0x8B },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
//00576A00568BF8E8 ...C20400
OOVPA_NO_XREF(D3DDevice_RunPushBuffer_4, 2048, 10)
{

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x0A, 0x00 },
    { 0x0B, 0x57 },
    { 0x0C, 0x6A },
    { 0x0D, 0x00 },
    { 0x0E, 0x56 },
    { 0x0F, 0x8B },
    { 0x10, 0xF8 },
    { 0x11, 0xE8 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_DrawVertices
// ******************************************************************
//81C2000200003BCA7223A1 ...C20800
OOVPA_NO_XREF(D3DDevice_DrawVertices_8, 2048, 13)
{

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x29, 0x81 },
    { 0x2A, 0xC2 },
    { 0x2B, 0x00 },
    { 0x2C, 0x02 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0x3B },
    { 0x30, 0xCA },
    { 0x31, 0x72 },
    { 0x32, 0x23 },
    { 0x33, 0xA1 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexDataColor
// ******************************************************************
//0C8D....40190400
OOVPA_NO_XREF(D3DDevice_SetVertexDataColor, 1036, 8)
{

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x24, 0x0C },
    { 0x25, 0x8D },
    { 0x28, 0x40 },
    { 0x29, 0x19 },
    { 0x2A, 0x04 },
    { 0x2B, 0x00 },
} OOVPA_END;

// ******************************************************************
// * D3DDevice_SetShaderConstantMode
// ******************************************************************
//A810538B1D ...C3
OOVPA_NO_XREF(D3DDevice_SetShaderConstantMode_0, 2048, 13)
{

    { 0x00, 0xA8 },
    { 0x01, 0x10 },
    { 0x02, 0x53 },
    { 0x03, 0x8B },
    { 0x04, 0x1D },

    { 0x10, 0x00 },
    { 0x11, 0x02 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0xEB },
    { 0x15, 0x06 },

    { 0xFE, 0x5B },
    { 0xFF, 0xC3 },
} OOVPA_END;

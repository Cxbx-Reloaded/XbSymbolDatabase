// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5455.inl
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
// * D3DDevice_CopyRects
// ******************************************************************
//83EC345355568B7424440F
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x34 },
    { 0x03, 0x53 },
    { 0x04, 0x55 },
    { 0x05, 0x56 },
    { 0x06, 0x8B },
    { 0x07, 0x74 },
    { 0x08, 0x24 },
    { 0x09, 0x44 },
    { 0x0A, 0x0F },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
//00008B4904578D ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader_0,
                         2060)
OOVPA_SIG_MATCH(

    { 0x00, 0x85 },
    { 0x02, 0x56 },

    { 0x5B, 0x04 },
    { 0x5C, 0xC7 },
    { 0x5D, 0x00 },
    { 0x5E, 0x94 },
    { 0x5F, 0x1E },
    { 0x60, 0x08 },
    { 0x61, 0x00 },
    { 0x62, 0x83 },

    { 0x9E, 0x5E },
    { 0x9F, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetScreenSpaceOffset
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScreenSpaceOffset,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0xD9 },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x56 },
    { 0x05, 0xD8 },
    //
);

// ******************************************************************
// * D3DDevice_SetTile
// ******************************************************************
//85C9538B1D ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTile_0,
                         2060)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x03, 0x85 },
    { 0x04, 0xC9 },
    { 0x05, 0x53 },
    { 0x06, 0x8B },
    { 0x07, 0x1D },

    { 0x0B, 0x00 },
    { 0x0C, 0x56 },
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//8B4C240483EC0C85C9568B
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x83 },
    { 0x05, 0xEC },
    { 0x06, 0x0C },
    { 0x07, 0x85 },
    { 0x08, 0xC9 },
    { 0x09, 0x56 },
    { 0x0A, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_UpdateOverlay
// ******************************************************************
//7707B800001000EB
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_UpdateOverlay,
                         1024)
OOVPA_SIG_MATCH(

    { 0x02, 0x08 },

    { 0xCB, 0x77 },
    { 0xCC, 0x07 },
    { 0xCD, 0xB8 },
    { 0xCE, 0x00 },
    { 0xCF, 0x00 },
    { 0xD0, 0x10 },
    { 0xD1, 0x00 },
    { 0xD2, 0xEB },
    //
);

// ******************************************************************
// * D3D_BlockOnResource
// ******************************************************************
//F7C20000780075 ...C3
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource_0,
                         2060)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },
    { 0x02, 0x35 },

    { 0x28, 0xF7 },
    { 0x29, 0xC2 },
    { 0x2A, 0x00 },
    { 0x2B, 0x00 },
    { 0x2C, 0x78 },
    { 0x2D, 0x00 },
    { 0x2E, 0x75 },
    //
);

// ******************************************************************
// * D3D_KickOffAndWaitForIdle
// ******************************************************************
//8B4C24088B442404E8
OOVPA_SIG_HEADER_NO_XREF(D3D_KickOffAndWaitForIdle2,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x13, 0x8B },
    { 0x14, 0x4C },
    { 0x15, 0x24 },
    { 0x16, 0x08 },
    { 0x17, 0x8B },
    { 0x18, 0x44 },
    { 0x19, 0x24 },
    { 0x1A, 0x04 },
    { 0x1B, 0xE8 },

    { 0x20, 0xC2 },
    { 0x21, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//A900007800751925000007003D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTarget,
                         1084)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x25, 0xA9 },
    { 0x26, 0x00 },
    { 0x27, 0x00 },
    { 0x28, 0x78 },
    { 0x29, 0x00 },
    { 0x2A, 0x75 },
    { 0x2B, 0x19 },
    { 0x2C, 0x25 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0x07 },
    { 0x30, 0x00 },
    { 0x31, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
//F64401680175
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LightEnable,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x24, 0xF6 },
    { 0x25, 0x44 },
    { 0x26, 0x01 },
    { 0x27, 0x68 },
    { 0x28, 0x01 },
    { 0x29, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      5455,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    XREF_ENTRY(0xFB, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // lea edi,[param_1 + 0x21]
    OV_MATCH(0x09, 0x8D, 0x78, 0x21),
    // shl edi,0x6
    OV_MATCH(0x0C, 0xC1, 0xE7, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x11, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xFA, 0xE8),

    // ret
    OV_MATCH(0x109, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

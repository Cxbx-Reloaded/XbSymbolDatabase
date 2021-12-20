// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5344.inl
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
// * D3DDevice_DeleteVertexShader
// ******************************************************************
//Generic OOVPA as of 5344 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DeleteVertexShader_0,
                         5344)
OOVPA_SIG_MATCH(

    // mov ecx,[eax + -0x1]
    OV_MATCH(0x00, 0x8B, 0x48, 0xFF),
    // dec eax
    // dec ecx
    OV_MATCH(0x03, 0x48, 0x49),
    // mov [eax],ecx
    OV_MATCH(0x05, 0x89, 0x08),
    // JNZ +0xB
    OV_MATCH(0x07, 0x75, 0x0B),

    // call XMemFree
    OV_MATCH(0x0F, 0xE8),

    OV_MATCH(0x14, 0xC3),
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShaderDirect
// ******************************************************************
//B940000000BF
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShaderDirect,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },

    { 0x13, 0x00 },
    { 0x14, 0xB9 },
    { 0x15, 0x40 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x00 },
    { 0x19, 0xBF },

    { 0x2B, 0xC2 },
    { 0x2C, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
//558BEC83EC1453568B35 ...C700FC17040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVerticesUP,
                         1048)
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

    { 0x2F, 0xC7 },
    { 0x30, 0x00 },
    { 0x31, 0xFC },
    { 0x32, 0x17 },
    { 0x33, 0x04 },
    { 0x34, 0x00 },
    { 0x35, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawVerticesUP,
                      1024,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_DrawVerticesUP+0x08 : mov esi,[D3D__PDEVICE]
    XREF_ENTRY(0x0A, XREF_D3DDEVICE),

    // D3DDevice_DrawVerticesUP+0x00 : push ebp
    OV_MATCH(0x00, 0x55),

    // D3DDevice_DrawVerticesUP+0x03 : sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // D3DDevice_DrawVerticesUP+0x08 : mov esi,[D3D__PDEVICE]
    OV_MATCH(0x08, 0x8B, 0x35),

    // D3DDevice_DrawVerticesUP+0x0E : push edi
    OV_MATCH(0x0E, 0x57),

    // D3DDevice_DrawVerticesUP+0x0F : mov [ebp-0x14],e__
    OV_MATCH(0x0F, 0x89),
    OV_MATCH(0x11, 0xEC),

    //
);

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_End,
                         1048)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x13, 0x50 },
    { 0x1C, 0xC7 },
    { 0x22, 0xC7 },
    { 0x2B, 0x08 },
    { 0x34, 0xE1 },
    { 0x49, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetLight
// ******************************************************************
//83E0F0894424108D04C0
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetLight,
                         1024)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x44 },

    { 0x22, 0x83 },
    { 0x23, 0xE0 },
    { 0x24, 0xF0 },
    { 0x25, 0x89 },
    { 0x26, 0x44 },
    { 0x27, 0x24 },
    { 0x28, 0x10 },
    { 0x29, 0x8D },
    { 0x2A, 0x04 },
    { 0x2B, 0xC0 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TwoSidedLighting
// ******************************************************************
//C700C417040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                         1060)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x20, 0xC7 },
    { 0x21, 0x00 },
    { 0x22, 0xC4 },
    { 0x23, 0x17 },
    { 0x24, 0x04 },
    { 0x25, 0x00 },
    { 0x26, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TwoSidedLighting
// ******************************************************************
//C700C417040089
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                         1072)
OOVPA_SIG_MATCH(

    { 0x01, 0x8B },

    { 0x21, 0xC7 },
    { 0x22, 0x00 },
    { 0x23, 0xC4 },
    { 0x24, 0x17 },
    { 0x25, 0x04 },
    { 0x26, 0x00 },
    { 0x27, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
//A900007800751925000007003D
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderTarget,
                         1072)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x26, 0xA9 },
    { 0x27, 0x00 },
    { 0x28, 0x00 },
    { 0x29, 0x78 },
    { 0x2A, 0x00 },
    { 0x2B, 0x75 },
    { 0x2C, 0x19 },
    { 0x2D, 0x25 },
    { 0x2E, 0x00 },
    { 0x2F, 0x00 },
    { 0x30, 0x07 },
    { 0x31, 0x00 },
    { 0x32, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_SetScissors
// ******************************************************************
//55894424088B430489
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScissors,
                         1048)
OOVPA_SIG_MATCH(

    { 0x01, 0xEC },

    { 0x16, 0x55 },
    { 0x17, 0x89 },
    { 0x18, 0x44 },
    { 0x19, 0x24 },
    { 0x1A, 0x08 },
    { 0x1B, 0x8B },
    { 0x1C, 0x43 },
    { 0x1D, 0x04 },
    { 0x1E, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      5344,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3DDEVICE]
    XREF_ENTRY(0x03, XREF_D3DDEVICE), // Derived

    // call D3D::UpdateProjectionViewportTransform
    XREF_ENTRY(0xF1, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3DDEVICE]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // lea edi,[param_1 + 0x21]
    OV_MATCH(0x09, 0x8D, 0x78, 0x21),
    // shl edi,0x6
    OV_MATCH(0x0C, 0xC1, 0xE7, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x11, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xF0, 0xE8),

    // ret
    OV_MATCH(0xFF, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3DDevice_LightEnable
// ******************************************************************
//F64401680175 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LightEnable_4,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x22, 0xF6 },
    { 0x23, 0x44 },
    { 0x24, 0x01 },
    { 0x25, 0x68 },
    { 0x26, 0x01 },
    { 0x27, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
//005D6A006A006A00E8
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         1060)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x13C, 0x00 },
    { 0x13D, 0x5D },
    { 0x13E, 0x6A },
    { 0x13F, 0x00 },
    { 0x140, 0x6A },
    { 0x141, 0x00 },
    { 0x142, 0x6A },
    { 0x143, 0x00 },
    { 0x144, 0xE8 },
    //
);

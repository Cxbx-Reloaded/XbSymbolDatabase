// ******************************************************************
// *
// *   OOVPADatabase->D3D8->4034.inl
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
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * CMiniport::InitHardware
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMiniport_InitHardware,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x10 },
    { 0x06, 0x53 },
    { 0x07, 0x56 },
    { 0x08, 0x8B },
    { 0x09, 0xF1 },
    { 0x0A, 0x56 },
    { 0x0B, 0x68 },

    { 0x10, 0x8D },
    { 0x11, 0x86 },
    { 0x12, 0x84 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x00 },
    { 0x16, 0x50 },
    { 0x17, 0xFF },
    { 0x18, 0x15 },

    { 0x1D, 0x80 },
    { 0x1E, 0xA6 },
    //{ 0x1F, 0xD8 }, // 4034 0xD8 vs 4242 0xDC
    //
);

// ******************************************************************
// * CMiniport::CreateCtxDmaObject
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMiniport_CreateCtxDmaObject,
                         4034) // Also for 4361, 4627, 5344, 5558, 5659, 5788, 5849, 5933
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x51 },
    { 0x04, 0x51 },
    { 0x05, 0x53 },
    { 0x06, 0x56 },
    { 0x07, 0x57 },
    { 0x08, 0x33 },
    { 0x09, 0xC0 },
    { 0x0A, 0x50 },
    { 0x0B, 0x89 },
    { 0x0C, 0x45 },
    { 0x0D, 0xF8 },
    { 0x0E, 0x89 },
    { 0x0F, 0x45 },
    { 0x10, 0xFC },
    { 0x11, 0x8D },
    { 0x12, 0x45 },
    { 0x13, 0xFC },
    { 0x14, 0x50 },
    { 0x15, 0x8D },
    { 0x16, 0x45 },
    { 0x17, 0xF8 },
    { 0x18, 0x50 },
    { 0x19, 0xFF },
    { 0x1A, 0x75 },
    { 0x1B, 0x10 },
    { 0x1C, 0x8B },
    { 0x1D, 0xD1 },
    { 0x1E, 0x8B },
    { 0x1F, 0x3A },
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetViewport+0x00 : sub esp, 0x08
    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },

    // D3DDevice_SetViewport+0x2D : mov ebx, [esp+0x14]
    { 0x2D, 0x8B },
    { 0x2E, 0x5C },
    { 0x2F, 0x24 },
    { 0x30, 0x14 },

    // D3DDevice_SetViewport+0x53 : jnz +0x12
    { 0x53, 0x75 },
    { 0x54, 0x12 },

    // D3DDevice_SetViewport+0x9B : inc edx
    { 0x9B, 0x42 },
    //
);

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
// Generic OOVPA as of 4034 and newer
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform,
                      4034,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x0B, XREF_D3D_g_pDevice), // Derived

    // mov eax, [esp + param_1]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // mov edx, [esp + param_2]
    OV_MATCH(0x04, 0x8B, 0x54, 0x24, 0x08),

    // Anything after offset 0x0F changed over time.

    // shl e??,0x6 // 4034 edi vs 5558 ecx
    OV_MATCH(0x12, 0xC1 /*, 0xE7*/), // 3911 0xE7 vs 5558 0xE1 value
    OV_MATCH(0x14, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x1D, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),
    //
);

// ******************************************************************
// * D3D::UpdateProjectionViewportTransform
// ******************************************************************
// NOTE: NASACAR Heat 2002 (LTCG) has reconigized by this OOVPA signature.
// Except non-LTCG titles with 4034 build and later are 100% confirmed as earlier build are using 3911 signature.
// For now, use 39XX as signature revision for this symbol.
// Generic OOVPA as of 4034 and newer
OOVPA_SIG_HEADER_XREF(D3D_UpdateProjectionViewportTransform,
                      3901,
                      XRefOne)
OOVPA_SIG_MATCH(
    // mov e??, XREF_D3D_g_pDevice
    XREF_ENTRY(0x0B, XREF_D3D_g_pDevice), // Derived

    // and  esp, 0FFFFFFF0h
    // sub  esp, 58h
    OV_MATCH(0x03, 0x83, 0xE4, 0xF0, 0x83, 0xEC, 0x5C),

    // Start of assembly code group since anything afterward does change over time.
    // mov e??,
    OV_MATCH(0x09, 0x8B),
    // mov eax, [e?? + 0x?]
    OV_MATCH(0x0F, 0x8B),
    // fild [ e?? + 0x?]
    OV_MATCH(0x15, 0xDB),

    // jge +0x06
    OV_MATCH(0x1E, 0x7D, 0x06),
    //
);

// ******************************************************************
// * D3DDevice_MultiplyTransform
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_MultiplyTransform,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xE4 },
    { 0x05, 0xF0 },

    { 0x0C, 0x56 },
    { 0x0D, 0x8B },
    { 0x0E, 0x75 },
    { 0x0F, 0x0C },
    { 0x10, 0x57 },
    { 0x11, 0xB9 },
    { 0x12, 0x10 },

    { 0x51, 0xC2 },
    { 0x52, 0x08 },
    { 0x53, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_CullMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_CullMode,
                      4034,
                      XRefTwo)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    XREF_ENTRY(0x2B, XREF_D3DRS_CullMode), // Derived

    // D3DDevice_SetRenderState_CullMode+0x00 : push esi
    { 0x00, 0x56 },

    // D3DDevice_SetRenderState_CullMode+0x19 : mov dword ptr [eax], 0x40308
    { 0x19, 0xC7 },
    { 0x1B, 0x08 },
    { 0x1C, 0x03 },
    { 0x1D, 0x04 },

    // D3DDevice_SetRenderState_CullMode+0x24 : add eax, 8
    { 0x24, 0x83 },
    { 0x25, 0xC0 },
    { 0x26, 0x08 },

    // D3DDevice_SetRenderState_CullMode+0x30 : retn 4
    { 0x30, 0xC2 },
    { 0x31, 0x04 },

    // D3DDevice_SetRenderState_CullMode+0x53 : add edx, 0x404
    { 0x53, 0x81 },
    { 0x54, 0xC2 },
    { 0x55, 0x04 },
    { 0x56, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_BeginVisibilityTest
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginVisibilityTest,
                         4034)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x0A, 0x46 },
    { 0x13, 0xC7 },
    { 0x16, 0x17 },
    { 0x1C, 0x00 },
    { 0x22, 0x48 },
    { 0x28, 0x06 },
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         4034)
OOVPA_SIG_MATCH(

    { 0x1E, 0x57 },
    { 0x3E, 0xF6 },
    { 0x5E, 0xEB },
    { 0x7E, 0x00 },
    { 0x9E, 0x10 },
    { 0xBE, 0x24 },
    { 0xDE, 0x22 },
    { 0xFE, 0x14 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVertices
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVertices,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_DrawIndexedVertices+0x0E : mov eax, [esi+0x1C]
    { 0x0E, 0x8B },
    { 0x0F, 0x46 },
    { 0x10, 0x1C },

    // D3DDevice_DrawIndexedVertices+0x20 : push 0x0209
    { 0x20, 0x68 },
    { 0x21, 0x09 },
    { 0x22, 0x02 },

    // D3DDevice_DrawIndexedVertices+0x64 : dec eax
    { 0x64, 0x48 },

    // D3DDevice_DrawIndexedVertices+0xF1 : prefetchnta byte ptr [esi+0x3C]
    { 0xF1, 0x0F },
    { 0xF2, 0x18 },
    { 0xF3, 0x46 },
    { 0xF4, 0x3C },
    //
);

// ******************************************************************
// * D3DDevice_SetStreamSource
// ******************************************************************
OOVPA_XREF(D3DDevice_SetStreamSource, 4034, 1 + 14, // 1+28
           XRefOne)
    {

        XREF_ENTRY(0x22, XREF_D3D_g_Stream), // Derived

#if 0
        { 0x00, 0x8B },
        { 0x01, 0x0D },

        { 0x06, 0x56 },
        { 0x07, 0x57 },
#endif

            // D3DDevice_SetStreamSource+0x08 : mov edi, [esp+8+0x04]
            { 0x08, 0x8B },
            { 0x09, 0x7C },
            { 0x0A, 0x24 },
            { 0x0B, 0x10 },

#if 0
        { 0x0C, 0x85 },
        { 0x0D, 0xFF },
        { 0x0E, 0x74 },
        { 0x0F, 0x06 },
        { 0x10, 0x81 },
        { 0x11, 0x07 },
        { 0x12, 0x00 },
        { 0x13, 0x00 },
        { 0x14, 0x08 },
        { 0x15, 0x00 },
        { 0x16, 0x8B },
        { 0x17, 0x44 },
        { 0x18, 0x24 },
        { 0x19, 0x0C },
        { 0x1A, 0x8D },
        { 0x1B, 0x34 },
        { 0x1C, 0x40 },
        { 0x1D, 0xC1 },
        { 0x1E, 0xE6 },
        { 0x1F, 0x02 },
#endif

            // D3DDevice_SetStreamSource+0x28 : jz +0x26
            { 0x28, 0x74 },
            { 0x29, 0x26 },

            // D3DDevice_SetStreamSource+0x70 : or ecx, 0x40
            { 0x70, 0x83 },
            { 0x71, 0xC9 },
            { 0x72, 0x40 },

            // D3DDevice_SetStreamSource+0x7E : or ecx, 0x70
            { 0x7E, 0x83 },
            { 0x7F, 0xC9 },
            { 0x80, 0x70 },

            // D3DDevice_SetStreamSource+0x89 : retn 0x0C
            { 0x89, 0xC2 },
            { 0x8A, 0x0C },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetTextureState_BorderColor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BorderColor,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x0E, 0xE8 },
    { 0x16, 0x08 },
    { 0x1E, 0x24 },
    { 0x26, 0x24 },
    { 0x2E, 0x89 },
    { 0x39, 0x5E },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_ColorKeyColor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_ColorKeyColor,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x0E, 0xE8 },
    { 0x16, 0x08 },
    { 0x1E, 0x89 },
    { 0x26, 0x04 },
    { 0x2E, 0x07 },
    { 0x36, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_LoadVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_LoadVertexShader+0x07 : mov al, [ebx+0x08]
    { 0x07, 0x8A },
    { 0x08, 0x43 },
    { 0x09, 0x08 },

    // D3DDevice_LoadVertexShader+0x32 : mov dword ptr [eax], 0x00041E9C
    { 0x32, 0xC7 },
    { 0x33, 0x00 },
    { 0x34, 0x9C },
    { 0x35, 0x1E },
    { 0x36, 0x04 },

    // D3DDevice_LoadVertexShader+0x4E : mov [ebx], ebx
    { 0x4E, 0x89 },
    { 0x4F, 0x13 },
    //
);

// ******************************************************************
// * D3DDevice_SetIndices
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetIndices,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x02, 0x35 },

    { 0x10, 0x81 },
    { 0x11, 0x07 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x08 },
    { 0x15, 0x00 },
    { 0x16, 0x8B },
    { 0x17, 0x47 },
    { 0x18, 0x04 },
    { 0x19, 0xA3 },

    { 0x48, 0x50 },
    { 0x49, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_EdgeAntiAlias
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_EdgeAntiAlias,
                         4034)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x0C, 0x72 },
    { 0x13, 0x8B },
    { 0x1A, 0x03 },
    { 0x21, 0x48 },
    { 0x28, 0x89 },
    { 0x2F, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_FillMode,
                      4034,
                      XRefThree)
OOVPA_SIG_MATCH(

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    XREF_ENTRY(0x15, XREF_D3DRS_TwoSidedLighting),
    // mov edx,ptr [D3DRS_BackFillMode]
    XREF_ENTRY(0x1B, XREF_D3DRS_BackFillMode),
    // mov ptr [D3DRS_FillMode],ecx
    XREF_ENTRY(0x3C, XREF_D3DRS_FillMode),

    // push esi
    OV_MATCH(0x00, 0x56),

    // mov ecx,ptr [D3DRS_TwoSidedLighting]
    OV_MATCH(0x13, 0x8B),

    // mov edx,ptr [D3DRS_BackFillMode]
    OV_MATCH(0x19, 0x8B),

    // mov ptr [eax],0x008038C
    OV_MATCH(0x29, 0xC7, 0x00, 0x8C, 0x03, 0x08, 0x00),

    // add eax,0x0C
    OV_MATCH(0x35, 0x83, 0xC0, 0x0C),

    // mov ptr [D3DRS_FillMode],ecx
    OV_MATCH(0x3A, 0x89),

    // retn 0x04
    OV_MATCH(0x41, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_BackFillMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_BackFillMode,
                      4034,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov [D3DRS_BackFillMode],eax
    XREF_ENTRY(0x0C, XREF_D3DRS_BackFillMode),
    // mov ecx,ptr [D3DRS_FillMode]
    XREF_ENTRY(0x18, XREF_D3DRS_FillMode),

    // mov [D3DRS_BackFillMode],eax
    OV_MATCH(0x0B, 0xA3),

    // mov esi,ptr [D3DRS_FillMode]
    OV_MATCH(0x16, 0x8B),

    // add eax, 0x0C
    OV_MATCH(0x41, 0x83, 0xC0, 0x0C),

    // retn 0x04
    OV_MATCH(0x4E, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FogColor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FogColor,
                         4034)
OOVPA_SIG_MATCH(

    { 0x08, 0x06 },
    { 0x14, 0x8B },
    { 0x1C, 0x0E },
    { 0x26, 0xE7 },
    { 0x30, 0x00 },
    { 0x3A, 0x89 },
    { 0x44, 0x0D },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_FrontFace
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_FrontFace,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x0E, 0xE8 },
    { 0x16, 0x08 },
    { 0x1E, 0x48 },
    { 0x2A, 0x89 },
    { 0x30, 0x5E },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_LogicOp
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_LogicOp,
                         4034)
OOVPA_SIG_MATCH(

    { 0x09, 0x3B },
    { 0x14, 0x4C },
    { 0x1F, 0x04 },
    { 0x2A, 0x0D },
    { 0x35, 0xBC },
    { 0x40, 0x89 },
    { 0x4E, 0x5E },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleAntiAlias
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_MultiSampleAntiAlias,
                         4034)
OOVPA_SIG_MATCH(

    { 0x0B, 0x8B },
    { 0x17, 0x8B },
    { 0x23, 0x8B },
    { 0x2C, 0x8B },
    { 0x38, 0xC1 },
    { 0x40, 0x7C },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleMask
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_MultiSampleMask,
                         4034)
OOVPA_SIG_MATCH(

    { 0x0B, 0x8B },
    { 0x17, 0x8B },
    { 0x23, 0x8B },
    { 0x2C, 0x8B },
    { 0x38, 0x83 },
    { 0x40, 0x7C },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_NormalizeNormals
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_NormalizeNormals,
                         4034)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x0E, 0xE8 },
    { 0x16, 0x08 },
    { 0x1E, 0x48 },
    { 0x26, 0x0D },
    { 0x2E, 0x00 },
    { 0x36, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ShadowFunc
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ShadowFunc,
                         4034)
OOVPA_SIG_MATCH(

    { 0x07, 0x8B },
    { 0x0C, 0x72 },
    { 0x13, 0x8B },
    { 0x1A, 0x1E },
    { 0x21, 0xFF },
    { 0x28, 0x08 },
    { 0x31, 0x5E },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilEnable,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x13, 0x8B },
    { 0x20, 0x02 },
    { 0x34, 0x85 },
    { 0x42, 0x75 },
    { 0x53, 0x89 },
    { 0x64, 0x00 },
    { 0x75, 0x83 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilFail,
                         4034)
OOVPA_SIG_MATCH(

    { 0x0C, 0x72 },
    { 0x1A, 0xC9 },
    { 0x2A, 0x85 },
    { 0x36, 0x74 },
    { 0x44, 0x83 },
    { 0x52, 0x24 },
    { 0x60, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_YuvEnable
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_YuvEnable,
                         4034)
OOVPA_SIG_MATCH(

    { 0x04, 0x56 },
    { 0x0B, 0xA3 },
    { 0x10, 0x8B },
    { 0x16, 0x05 },
    { 0x1C, 0x8B },
    { 0x25, 0x89 },
    { 0x28, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TwoSidedLighting
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_TwoSidedLighting,
                         4034)
OOVPA_SIG_MATCH(

    { 0x0B, 0x8B },
    { 0x18, 0x15 },
    { 0x25, 0x46 },
    { 0x35, 0x8B },
    { 0x43, 0x75 },
    { 0x4C, 0x00 },
    { 0x59, 0x3D },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_VertexBlend
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_VertexBlend,
                         4034)
OOVPA_SIG_MATCH(

    { 0x07, 0xCA },
    { 0x13, 0x89 },
    { 0x19, 0x8B },
    { 0x25, 0x8B },
    { 0x2B, 0x28 },
    { 0x34, 0x08 },
    { 0x3D, 0x5E },
    //
);

// ******************************************************************
// * Get2DSurfaceDesc
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(Get2DSurfaceDesc,
                         4034)
OOVPA_SIG_MATCH(

    { 0x10, 0x0D },
    { 0x48, 0x08 },
    { 0x49, 0x02 },
    { 0x4A, 0x00 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },
    { 0x4D, 0xA1 },
    { 0x58, 0x53 },
    { 0x63, 0x80 },
    { 0xAE, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetRenderState_ZEnable+0x0C : jb +0x05
    { 0x0C, 0x72 },
    { 0x0D, 0x05 },

    // D3DDevice_SetRenderState_ZEnable+0x1B : mov edx, [esi+0x2074h]
    { 0x1B, 0x8B },
    { 0x1C, 0x96 },
    { 0x1D, 0xF4 },
    { 0x1E, 0x21 },

    // D3DDevice_SetRenderState_ZEnable+0x31 : mov dword ptr [eax], 0x4030C
    { 0x31, 0xC7 },
    { 0x32, 0x00 },
    { 0x33, 0x0C },
    { 0x34, 0x03 },
    { 0x35, 0x04 },

    // D3DDevice_SetRenderState_ZEnable+0x98 : retn 0x04
    { 0x98, 0xC2 },
    { 0x99, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_TextureFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_TextureFactor,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x07, 0x8B },
    { 0x08, 0x86 },
    { 0x2F, 0x90 },

    { 0x40, 0x5E },
    { 0x41, 0xC2 },
    { 0x42, 0x04 },
    { 0x43, 0x00 },
    { 0x44, 0x8B },
    { 0x45, 0x44 },
    { 0x46, 0x24 },
    { 0x47, 0x08 },
    { 0x48, 0xA3 },

    { 0x4E, 0xC2 },
    { 0x4F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_Clear
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Clear,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x23, 0x33 },
    { 0x24, 0xF6 },
    { 0x25, 0xF6 },
    { 0x26, 0xC1 },
    { 0x27, 0x01 },
    { 0x28, 0x89 },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0x89 },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },

    { 0x54, 0x05 },
    { 0x81, 0xB6 },
    //
);

// ******************************************************************
// * D3DVertexBuffer_Lock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DVertexBuffer_Lock,
                      4034,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DVertexBuffer_Lock+0x0B : mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x0D, XREF_D3D_g_pDevice),

    // D3DVertexBuffer_Lock+0x18 : call D3DDevice_MakeSpace
    //XREF_ENTRY(0x19, XREF_D3DDevice_MakeSpace),

    // D3DVertexBuffer_Lock+0x01 : mov bl, [esp+0x18]
    OV_MATCH(0x01, 0x8A, 0x5C, 0x24, 0x18), // 4034 0x18 vs D3DVertexBuffer_Lock2 (4627) 0x0C

    // D3DVertexBuffer_Lock+0x09 : jnz +0x24
    OV_MATCH(0x09, 0x75, 0x24),

    // D3DVertexBuffer_Lock+0x2F : test bl, 0xA0
    OV_MATCH(0x2F, 0xF6, 0xC3, 0xA0),

    // 4034 0x50 vs 4531 0x54 : retn 0x14

    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetTexture, 4034, 10) // TODO : Alias 3911 instead ?
    {
#else
OOVPA_XREF(D3DDevice_SetTexture, 4034, 1 + 10, // TODO : Alias 3911 instead ?
           XRefOne)
{

    XREF_ENTRY(0x13, XREF_OFFSET_D3DDevice__m_Textures), // Derived - verified for 4432 DolphinClassic 0x00021D10(SetTexture)+0x10=00021D20 : 8B 84 B7 78 0A 00 00 mov eax,[edi+esi*4+$00000A78]
#endif
        // D3DDevice_SetTexture+0x09 : push edi
        { 0x09, 0x57 },

            // D3DDevice_SetTexture+0x21 : jz +0x20
            { 0x21, 0x74 },
            { 0x22, 0x20 },

            // D3DDevice_SetTexture+0x33 : test ecx, 0x78FFFF
            { 0x33, 0xF7 },
            { 0x34, 0xC1 },
            { 0x37, 0x78 },

            // D3DDevice_SetTexture+0x39 : mov [eax], edx
            { 0x39, 0x89 },
            { 0x3A, 0x10 },

            // D3DDevice_SetTexture+0xC9 : jz +0x4D
            { 0xC9, 0x74 },
            { 0xCA, 0x4D },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetPalette
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetPalette, 4034, 12)
    {
#else
OOVPA_XREF(D3DDevice_SetPalette,
           4034,
           1 + 12,
           XRefOne)
{

    XREF_ENTRY(0x10, XREF_OFFSET_D3DDevice__m_Palettes), // Derived
#endif
        { 0x00, 0x53 },
            { 0x08, 0x57 },
            { 0x1B, 0x89 },
            { 0x1C, 0x48 },

            { 0x4D, 0x39 },
            { 0x4E, 0x55 },
            { 0x4F, 0x8B },
            { 0x50, 0x2B },
            { 0x51, 0x81 },
            { 0x52, 0xC5 },
            { 0x53, 0x00 },
            { 0x54, 0x00 },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex,
                      4034,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x18, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    // D3DDevice_SetTextureState_TexCoordIndex+0x13 : shl eax, 0x07
    { 0x13, 0xC1 },
    { 0x14, 0xE0 },
    { 0x15, 0x07 },

    // D3DDevice_SetTextureState_TexCoordIndex+0x25 : cmp eax, ecx
    { 0x25, 0x3B },
    { 0x26, 0xC1 },

    // D3DDevice_SetTextureState_TexCoordIndex+0x6C : mov edi, 0x2400
    { 0x6C, 0xBF },
    { 0x6E, 0x24 },

    // D3DDevice_SetTextureState_TexCoordIndex+0xB4 : shl edx, 0x04
    { 0xB4, 0xC1 },
    { 0xB5, 0xE2 },
    { 0xB6, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetMaterial
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetMaterial,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetMaterial+0x0C : add edi, 0x0B70
    { 0x0C, 0x81 },
    { 0x0D, 0xC7 },
    { 0x0E, 0x70 },
    { 0x0F, 0x0B },

    // D3DDevice_SetMaterial+0x12 : mov ecx, 0x11
    { 0x12, 0xB9 },
    { 0x13, 0x11 },

    // D3DDevice_SetMaterial+0x1F : or ecx, 0x1000
    { 0x1F, 0x81 },
    { 0x20, 0xC9 },
    { 0x21, 0x00 },
    { 0x22, 0x10 },

    // D3DDevice_SetMaterial+0x2D : retn 0x04
    { 0x2D, 0xC2 },
    { 0x2E, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      4034,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_OFFSET_D3DDevice__m_VertexShader), // Derived

    // D3DDevice_SetVertexShader+0x06 : test bl, 1
    { 0x06, 0xF6 },
    { 0x07, 0xC3 },
    { 0x08, 0x01 },

    // D3DDevice_SetVertexShader+0x11 : mov eax, [esi+0x04F8]
    { 0x11, 0x8B },
    { 0x12, 0x86 },
    { 0x13, 0xF8 },
    { 0x14, 0x04 },

    // D3DDevice_SetVertexShader+0x90 : retn 0x04
    { 0x90, 0xC2 },
    { 0x91, 0x04 },

    // D3DDevice_SetVertexShader+0xB0 : mov dword ptr [eax], 0x4194C
    { 0xB0, 0xC7 },
    { 0xB1, 0x00 },
    { 0xB2, 0x4C },
    { 0xB3, 0x19 },
    { 0xB4, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_Swap
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap,
                         4034) // Up to 4432
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x0E, 0x75 },
    { 0x0F, 0x05 },
    { 0x10, 0xBB },
    { 0x11, 0x05 },
    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x00 },
    { 0x15, 0x8B },
    { 0x16, 0x46 },
    { 0x17, 0x08 },
    { 0x18, 0xF6 },
    { 0x19, 0xC4 },
    { 0x1A, 0x40 },
    { 0x1B, 0x74 },
    { 0x1C, 0x4E },
    { 0x1D, 0xF6 },
    { 0x1E, 0xC3 },
    { 0x1F, 0x03 },

    { 0x29, 0x8B },
    //
);

// ******************************************************************
// * D3D_KickOffAndWaitForIdle
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_KickOffAndWaitForIdle,
                         4034)
OOVPA_SIG_MATCH(

    // D3D_KickOffAndWaitForIdle+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3D_KickOffAndWaitForIdle+0x05 : mov ecx, [eax+0x30]
    { 0x05, 0x8B },
    { 0x06, 0x48 },
    { 0x07, 0x30 },

    // D3D_KickOffAndWaitForIdle+0x08 : push 0
    { 0x08, 0x6A },
    { 0x09, 0x00 },

    // D3D_KickOffAndWaitForIdle+0x0A : push ecx
    { 0x0A, 0x51 },

    // D3D_KickOffAndWaitForIdle+0x0B : call [addr]
    { 0x0B, 0xE8 },

    // D3D_KickOffAndWaitForIdle+0x10 : retn
    { 0x10, 0xC3 },
    //
);

// ******************************************************************
// * D3D::CreateStandAloneSurface
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_CreateStandAloneSurface,
                         4034)
OOVPA_SIG_MATCH(

    { 0x01, 0x54 },

    { 0x17, 0x14 },
    { 0x18, 0x6A },
    { 0x19, 0x00 },
    { 0x1A, 0x6A },
    { 0x1B, 0x00 },
    { 0x1C, 0x6A },
    { 0x1D, 0x00 },
    { 0x1E, 0x52 },
    { 0x1F, 0x6A },

    { 0x36, 0xF0 },
    { 0x4B, 0x15 },
    //
);

// ******************************************************************
// * D3DDevice_CreateImageSurface
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_CreateImageSurface,
                      4034,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x01, XREF_D3D_CreateStandAloneSurface),

    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * D3DDevice_GetBackBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetBackBuffer,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_GetBackBuffer+0x04 : cmp eax, 0xFFFFFFFF
    { 0x04, 0x83 },
    { 0x05, 0xF8 },
    { 0x06, 0xFF },

    // D3DDevice_GetBackBuffer+0x0D : jnz +0x07
    { 0x0D, 0x75 },
    { 0x0E, 0x07 },

    // D3DDevice_GetBackBuffer+0x18 : sbb eax, eax
    { 0x18, 0x1B },
    { 0x19, 0xC0 },

    // D3DDevice_GetBackBuffer+0x1D : mov eax, [ecx+eax*4+0x21FC]
    { 0x1D, 0x8B },
    { 0x1E, 0x84 },
    { 0x1F, 0x81 },
    { 0x20, 0xFC },
    { 0x21, 0x21 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstant
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstant,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetVertexShaderConstant+0x11 : mov cl, [ebx+0x08]
    { 0x11, 0x8A },
    { 0x12, 0x4B },
    { 0x13, 0x08 },

    // D3DDevice_SetVertexShaderConstant+0x1A : test cl, 0x10
    { 0x1A, 0xF6 },
    { 0x1B, 0xC1 },
    { 0x1C, 0x10 },

    // D3DDevice_SetVertexShaderConstant+0x60 : jle +0x19
    { 0x60, 0x7E },
    { 0x61, 0x19 },

    // D3DDevice_SetVertexShaderConstant+0x98 : retn 0x0C
    { 0x98, 0xC2 },
    { 0x99, 0x0C },
    //
);

// ******************************************************************
// * D3DDevice_GetTransform
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetTransform,
                         4034) // Also for 4134
OOVPA_SIG_MATCH(

    // D3DDevice_GetTransform+0x0A : shl ecx, 0x06
    { 0x0A, 0xC1 },
    { 0x0B, 0xE1 },
    { 0x0C, 0x06 },

    // D3DDevice_GetTransform+0x12 : lea esi, [ecx+eax+*numb*]
    { 0x12, 0x8D },
    { 0x13, 0xB4 },
    { 0x14, 0x01 },

    // D3DDevice_GetTransform+0x19 : mov ecx, 0x10
    { 0x19, 0xB9 },
    { 0x1A, 0x10 },

    // D3DDevice_GetTransform+0x20 : pop edi, pop esi
    { 0x20, 0x5F },
    { 0x21, 0x5E },

    // D3DDevice_GetTransform+0x22 : retn 0x08
    { 0x22, 0xC2 },
    { 0x23, 0x08 },
    //
);

// ******************************************************************
// * D3DDevice_SelectVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SelectVertexShader+0x00 : mov eax, [esp+4]
    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // D3DDevice_SelectVertexShader+0x3B : mov dword ptr [eax], 0x00081E94
    { 0x3B, 0xC7 },
    { 0x3C, 0x00 },
    { 0x3D, 0x94 },
    { 0x3E, 0x1E },
    { 0x3F, 0x08 },
    { 0x40, 0x00 },

    // D3DDevice_SelectVertexShader+0x55 : mov [esi], eax
    { 0x55, 0x89 },
    { 0x56, 0x06 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 4034, 10)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget, 4034, 1 + 10, XRefOne)
{

    XREF_ENTRY(0x17, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived TODO : Verify offset
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0xXX
        OV_MATCH(0x00, 0x83, 0xEC),
            //OV_MATCH(0x02, 0x30),

            // D3DDevice_SetRenderTarget+0x73 : shr ecx,0x14
            OV_MATCH(0x73, 0xC1, 0xE9, 0x14),

            // D3DDevice_SetRenderTarget+0x76 : and ecx, 0x0F
            OV_MATCH(0x76, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0x7E : shl eax,cl
            OV_MATCH(0x7E, 0xD3, 0xE0),
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetPixelShader
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetPixelShader, 4034, 12)
    {
#else
OOVPA_XREF(D3DDevice_SetPixelShader,
           4034,
           1 + 12,
           XRefOne)
{

    XREF_ENTRY(0x10, XREF_OFFSET_D3DDevice__m_PixelShader), // Derived
#endif
        { 0x00, 0x8B },
            { 0x01, 0x44 },
            { 0x02, 0x24 },
            { 0x03, 0x04 },
            { 0x04, 0x85 },
            { 0x05, 0xC0 },
            { 0x06, 0x53 },
            { 0x07, 0x8B },
            { 0x08, 0x1D },
            //{ 0x09, 0xA0 }, // disabled: part of an offset
            { 0x18, 0x00 },
            { 0x1D, 0x0D },
            { 0x3F, 0xA3 },
    }
OOVPA_END;

// ******************************************************************
// * D3D::BlockOnResource
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnResource,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x05, 0x85 },
    { 0x18, 0x00 },
    { 0x19, 0x05 },
    { 0x1A, 0x00 },
    { 0x1B, 0x56 },
    { 0x1C, 0x75 },
    { 0x1D, 0x28 },
    { 0x1E, 0x8B },
    { 0x1F, 0x70 },
    { 0x40, 0x5E },
    { 0x4A, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_SetFlickerFilter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetFlickerFilter,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetFlickerFilter+0x0A : mov edx, [ecx+0x23E8]
    { 0x0A, 0x8B },
    { 0x0B, 0x91 },
    { 0x0C, 0xE8 },
    { 0x0D, 0x23 },

    // D3DDevice_SetFlickerFilter+0x10 : push 0; push eax; push 0x0B; push edx
    { 0x10, 0x6A },
    { 0x11, 0x00 },
    { 0x12, 0x50 },
    { 0x13, 0x6A },
    { 0x14, 0x0B },
    { 0x15, 0x52 },

    // D3DDevice_SetFlickerFilter+0x1C : retn 0x08
    { 0x1C, 0xC2 },
    { 0x1D, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetSoftDisplayFilter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetSoftDisplayFilter,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetSoftDisplayFilter+0x0A : mov edx, [ecx+0x23E8]
    { 0x0A, 0x8B },
    { 0x0B, 0x91 },
    { 0x0C, 0xE8 },
    { 0x0D, 0x23 },

    // D3DDevice_SetSoftDisplayFilter+0x10 : push 0; push eax; push 0x0E; push edx
    { 0x10, 0x6A },
    { 0x11, 0x00 },
    { 0x12, 0x50 },
    { 0x13, 0x6A },
    { 0x14, 0x0E },
    { 0x15, 0x52 },

    // D3DDevice_SetSoftDisplayFilter+0x1C : retn 0x08
    { 0x1C, 0xC2 },
    { 0x1D, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_PSTextureModes
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_PSTextureModes,
                         4034)
OOVPA_SIG_MATCH(

    { 0x0A, 0x89 },
    { 0x0B, 0x81 },
    { 0x0E, 0x00 },
    { 0x0F, 0x00 },
    { 0x10, 0x81 },
    { 0x11, 0x0D },
    { 0x16, 0x00 },
    { 0x17, 0x40 },
    { 0x1A, 0xA3 },
    { 0x1F, 0xC2 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleMode
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderState_MultiSampleMode, 4034, 12)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderState_MultiSampleMode,
           4034,
           1 + 8,
           XRefOne)
{

    XREF_ENTRY(0x11, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif
        // D3DDevice_SetRenderState_MultiSampleMode+0x0F : mov ecx, [eax+0x21F0]
        { 0x0F, 0x8B },
            { 0x10, 0x88 },
#ifndef WIP_LessVertexPatching
            { 0x11, 0xF0 }, // disabled. part of an offset
            { 0x12, 0x21 },
#endif

            // D3DDevice_SetRenderState_MultiSampleMode+0x15 : cmp ecx, [eax+0x21FC]
            { 0x15, 0x3B },
            { 0x16, 0x88 },
#ifndef WIP_LessVertexPatching
            { 0x17, 0xFC }, // disabled. part of an offset
            { 0x18, 0x21 },
#endif

            // D3DDevice_SetRenderState_MultiSampleMode+0x1B : jnz +0x0D
            { 0x1B, 0x75 },
            { 0x1C, 0x0D },

            // D3DDevice_SetRenderState_MultiSampleMode+0x2A : retn 0x04
            { 0x2A, 0xC2 },
            { 0x2B, 0x04 },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetRenderState_MultiSampleRenderTargetMode
// ******************************************************************
// Generic OOVPA as of 4034 and newer.
#ifndef WIP_LessVertexPatching
OOVPA_XREF(D3DDevice_SetRenderState_MultiSampleRenderTargetMode,
           4034,
           1 + 10,
           XRefOne)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderState_MultiSampleRenderTargetMode,
           4034,
           2 + 10,
           XRefTwo)
{
#endif
        XREF_ENTRY(0x0B, XREF_D3DRS_MultiSampleRenderTargetMode), // Derived

#ifdef WIP_LessVertexPatching
            XREF_ENTRY(0x11, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived
#endif

            { 0x00, 0x8B },
            //{ 0x01, 0x4C },
            { 0x02, 0x24 },
            { 0x03, 0x04 },

            { 0x0F, 0x8B },
            //{ 0x10, 0x88 },
            //{ 0x11, 0x70 },
            //{ 0x12, 0x20 },
            { 0x13, 0x00 },
            { 0x14, 0x00 },
            { 0x15, 0x3B },
            //{ 0x16, 0x88 },
            //{ 0x17, 0x7C },
            //{ 0x18, 0x20 },
            { 0x19, 0x00 },
            { 0x1A, 0x00 },
            { 0x1B, 0x74 }, // MultiSampleRenderTargetMode 0x74 vs MultiSampleMode 0x75
        //{ 0x1C, 0x0D },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetRenderState_LineWidth
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_LineWidth,
                         4034)
OOVPA_SIG_MATCH(

    { 0x0C, 0x89 },

    { 0x30, 0x8B },
    { 0x46, 0xE8 },

    { 0x4B, 0xC7 },
    { 0x53, 0x04 },
    { 0x54, 0x83 },
    { 0x55, 0xC0 },
    { 0x56, 0x08 },
    { 0x57, 0x5F },
    { 0x58, 0x89 },
    { 0x59, 0x06 },
    { 0x5A, 0x5E },
    { 0x5B, 0x89 },
    { 0x5C, 0x1D },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_OcclusionCullEnable
// ******************************************************************
// Generic OOVPA as of 4034 and newer.
// NOTE: asm codes are the same as D3DDevice_SetRenderState_StencilCullEnable
//       except for the offset references.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_OcclusionCullEnable,
                      4034,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // D3DDevice_SetRenderState_StencilCullEnable+0x05 : mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // D3DDevice_SetRenderState_OcclusionCullEnable+0x0B : [D3DRS_OcclusionCullEnable]
    XREF_ENTRY(0x0C, XREF_D3DRS_OcclusionCullEnable), // Derived

    // D3DDevice_SetRenderState_OcclusionCullEnable+0x17 : call D3DDevice_MakeSpace
    //XREF_ENTRY(0x18, XREF_D3DDevice_MakeSpace),

    // D3DDevice_SetRenderState_StencilCullEnable+0x00 : mov eax, [esp+arg_0]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // D3DDevice_SetRenderState_OcclusionCullEnable+0x41 : cmp [abs], 0x1E00
    OV_MATCH(0x41, 0x81),
    OV_MATCH(0x47, 0x00, 0x1E),

    // D3DDevice_SetRenderState_OcclusionCullEnable+0x50 : mov dword ptr [eax], 0x41D84
    OV_MATCH(0x50, 0xC7, 0x00, 0x84, 0x1D, 0x04),

    // D3DDevice_SetRenderState_OcclusionCullEnable+0x5F : retn 0x04
    OV_MATCH(0x5F, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilCullEnable
// ******************************************************************
// Generic OOVPA as of 4034 and newer.
// NOTE: asm codes are the same as D3DDevice_SetRenderState_OcclusionCullEnable
//       except for the offset references.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilCullEnable,
                      4034,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // D3DDevice_SetRenderState_StencilCullEnable+0x05 : mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x07, XREF_D3D_g_pDevice),

    // D3DDevice_SetRenderState_StencilCullEnable+0x0B : [D3DRS_StencilCullEnable]
    XREF_ENTRY(0x0C, XREF_D3DRS_StencilCullEnable), // Derived

    // D3DDevice_SetRenderState_StencilCullEnable+0x17 : call D3DDevice_MakeSpace
    //XREF_ENTRY(0x18, XREF_D3DDevice_MakeSpace),

    // D3DDevice_SetRenderState_StencilCullEnable+0x00 : mov eax, [esp+arg_0]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    // D3DDevice_SetRenderState_StencilCullEnable+0x41 : cmp [abs], 0x1E00
    OV_MATCH(0x41, 0x81),
    OV_MATCH(0x47, 0x00, 0x1E),

    // D3DDevice_SetRenderState_StencilCullEnable+0x50 : mov dword ptr [eax], 0x41D84
    OV_MATCH(0x50, 0xC7, 0x00, 0x84, 0x1D, 0x04),

    // D3DDevice_SetRenderState_StencilCullEnable+0x5F : retn 0x04
    OV_MATCH(0x5F, 0xC2, 0x04),
    //
);

// ******************************************************************
// * D3DResource_GetType
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DResource_GetType,
                         4034)
OOVPA_SIG_MATCH(

    { 0x10, 0x77 },
    { 0x22, 0x83 },
    { 0x34, 0x00 },
    { 0x46, 0x74 },
    { 0x58, 0x00 },
    { 0x6A, 0x74 },
    { 0x7C, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_BumpEnv
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTextureState_BumpEnv,
                         4034)
OOVPA_SIG_MATCH(

    // D3DDevice_SetTextureState_BumpEnv+0x18 : jnz +0x03
    { 0x18, 0x75 },
    { 0x19, 0x03 },

    // D3DDevice_SetTextureState_BumpEnv+0x1D : test bl, 3
    { 0x1D, 0xF6 },
    { 0x1E, 0xC3 },
    { 0x1F, 0x03 },

    // D3DDevice_SetTextureState_BumpEnv+0x32 : mov ecx, [esp+0x14]
    { 0x32, 0x8B },
    { 0x33, 0x4C },
    { 0x34, 0x24 },
    { 0x35, 0x18 },

    // D3DDevice_SetTextureState_BumpEnv+0x50 : shl esi, 5
    { 0x50, 0xC1 },
    { 0x51, 0xE6 },
    { 0x52, 0x05 },
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x0E, 0x04 },
    { 0x0F, 0x74 },
    { 0x10, 0x08 },
    { 0x11, 0x8B },
    { 0x12, 0x89 },
    { 0x1B, 0xA1 },

    { 0x80, 0x08 },
    { 0x81, 0x00 },
    { 0x82, 0x20 },
    { 0x83, 0x00 },
    { 0x84, 0x00 },
    { 0x85, 0x59 },
    { 0x86, 0xC3 },
    { 0x87, 0xB8 },
    //
);

// ******************************************************************
// * D3D::SetFence
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x02, 0x35 },

    { 0x07, 0x8B },
    { 0x0D, 0x72 },

    { 0x50, 0x8A },
    { 0x51, 0x5C },
    { 0x52, 0x24 },
    { 0x53, 0x10 },
    { 0x54, 0xF6 },
    { 0x55, 0xC3 },
    { 0x56, 0x01 },
    { 0x57, 0x8D },
    //
);

// ******************************************************************
// * D3D::BlockOnTime
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime,
                         4034)
OOVPA_SIG_MATCH(

    { 0x07, 0x3D },

    { 0x18, 0x8B },
    { 0x19, 0xC8 },
    { 0x1A, 0x2B },
    { 0x1B, 0xCE },
    { 0x1C, 0x3B },
    { 0x1D, 0xCA },
    { 0x1E, 0x0F },
    { 0x1F, 0x83 },

    { 0x2F, 0x53 },
    //
);

// ******************************************************************
// * D3DDevice_SetTile
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTile,
                         4034)
OOVPA_SIG_MATCH(

    { 0x05, 0x1D },

    { 0x17, 0x46 },
    { 0x18, 0x04 },
    { 0x19, 0x74 },
    { 0x1A, 0x69 },
    { 0x1B, 0xB9 },
    { 0x1C, 0x06 },
    { 0x1D, 0x00 },
    { 0x1E, 0x00 },
    { 0x1F, 0x00 },

    { 0x7B, 0x5F },
    { 0x8A, 0x76 },
    //
);

// ******************************************************************
// * D3DDevice_SetScreenSpaceOffset
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetScreenSpaceOffset,
                         4034) // Up to 5344
OOVPA_SIG_MATCH(

    { 0x06, 0x56 },
    { 0x07, 0xD8 },
    { 0x08, 0x44 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },
    { 0x0B, 0x8B },
    { 0x0C, 0x35 },

    { 0x2E, 0x8B },
    { 0x2F, 0x06 },
    { 0x46, 0xC2 },
    { 0x47, 0x08 },
    //
);

// ******************************************************************
// * D3D::LazySetPointParams
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_LazySetPointParams,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x14 },
    { 0x4E, 0xE0 },
    { 0x73, 0xF6 },
    { 0x74, 0xC4 },
    { 0x75, 0x41 },
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateVB
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateVB,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x0C },

    { 0x41, 0x0F },
    { 0x42, 0x84 },
    { 0x43, 0x41 },
    { 0x44, 0x01 },
    { 0x45, 0x00 },
    { 0x46, 0x00 },
    { 0x47, 0x8B },
    { 0x48, 0x86 },
    { 0x49, 0xF8 },
    { 0x4A, 0x04 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },

    { 0x66, 0x3B },
    { 0x67, 0xC1 },
    //
);

// ******************************************************************
// * D3D::CDevice::SetStateUP
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_SetStateUP,
                         4034)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x2F, 0x8B },
    { 0x30, 0x86 },
    { 0x31, 0xF8 },
    { 0x32, 0x04 },
    { 0x33, 0x00 },
    { 0x34, 0x00 },
    { 0x35, 0x8B },
    { 0x36, 0x4E },
    { 0x37, 0x04 },
    { 0x38, 0x53 },
    { 0x39, 0x8B },
    { 0x3A, 0x58 },

    { 0x4F, 0x3B },
    { 0x50, 0xC1 },
    //
);

// ******************************************************************
// * D3D::MakeRequestedSpace
// ******************************************************************
// Generic OOVPA as of 4034 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3D_MakeRequestedSpace_4,
                         4034)
OOVPA_SIG_MATCH(

    // D3D::MakeRequestedSpace+0x00 : push ecx; push esi
    OV_MATCH(0x00, 0x51, 0x56),

    // D3D::MakeRequestedSpace+0x08 : test [esi+0x08],0x04
    OV_MATCH(0x08, 0xF6, 0x46, 0x08, 0x04),

    // D3D::MakeRequestedSpace+0x20 : sub ecx,edi; add edx,ecx
    OV_MATCH(0x20, 0x2B, 0xCF, 0x03, 0xD1),

    // D3D::MakeRequestedSpace+0x32 : ret 0x0004
    OV_MATCH(0x32, 0xC2, 0x04),

    //
);

// ******************************************************************
// * D3DDevice_MakeSpace
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_MakeSpace,
                      4034,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_MakeSpace+0x06 : call D3D::MakeRequestedSpace
    XREF_ENTRY(0x07, XREF_D3D_MakeRequestedSpace),

    // D3DDevice_MakeSpace+0x00 : mov eax,[addr]
    OV_MATCH(0x00, 0xA1),

    // D3DDevice_MakeSpace+0x05 : push eax
    OV_MATCH(0x05, 0x50),

    // D3DDevice_MakeSpace+0x06 : call D3D::MakeRequestedSpace
    OV_MATCH(0x06, 0xE8),

    // D3DDevice_MakeSpace+0x0B : ret
    OV_MATCH(0x0B, 0xC3),

    //
);

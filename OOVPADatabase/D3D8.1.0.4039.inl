// ******************************************************************
// *
// *   OOVPADatabase->D3D8.1.0.4039.inl
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
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2018 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * D3DDevice_GetMaterial
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetMaterial, 4039, 9)

        { 0x00, 0xA1 },
        { 0x05, 0x56 },
        { 0x06, 0x57 },
        { 0x0A, 0x0C },
        { 0x0D, 0x70 },
        { 0x0E, 0x0B },
        { 0x12, 0x11 },
        { 0x16, 0xF3 },
        { 0x1A, 0xC2 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetBackMaterial
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetBackMaterial, 4039, 12)

        { 0x00, 0x56 },
        { 0x04, 0x08 },

        { 0x0C, 0x81 },
        { 0x0D, 0xC7 },
        { 0x0E, 0xB4 },
        { 0x0F, 0x0B },
        { 0x10, 0x00 },

        { 0x16, 0x00 },
        { 0x1F, 0x81 },
        { 0x22, 0x10 },
        { 0x2C, 0x5E },
        { 0x2E, 0x04 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetBackMaterial
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetBackMaterial, 4039, 9)

        { 0x00, 0xA1 },
        { 0x05, 0x56 },
        { 0x06, 0x57 },
        { 0x0A, 0x0C },
        { 0x0D, 0xB4 },
        { 0x0E, 0x0B },
        { 0x12, 0x11 },
        { 0x16, 0xF3 },
        { 0x1A, 0xC2 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 4039, 10)
#else
OOVPA_XREF(D3DDevice_SetRenderTarget, 4039, 1+9,

    XRefNoSaveIndex,
    XRefOne)

        XREF_ENTRY( 0x17, XREF_OFFSET_D3DDEVICE_M_RENDERTARGET ), // Derived TODO : Verify offset
#endif
        { 0x06, 0x35 },
        { 0x12, 0x3B },
        { 0x13, 0xFB },
        { 0x14, 0x75 },
        { 0x15, 0x0C },
        { 0x16, 0x8B },
        { 0x1A, 0x00 },
        { 0x1F, 0x4C },
        { 0x32, 0x74 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_Begin
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_Begin, 4039, 13)

        { 0x07, 0xE8 },

        { 0x18, 0x8B },
        { 0x19, 0x4C },
        { 0x1A, 0x24 },
        { 0x1B, 0x08 },
        { 0x1C, 0xC7 },
        { 0x1D, 0x00 },
        { 0x1E, 0xFC },
        { 0x1F, 0x17 },
        { 0x20, 0x04 },
        { 0x21, 0x00 },

        { 0x32, 0xC2 },
        { 0x33, 0x04 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVerticalBlankCallback
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVerticalBlankCallback, 4039, 12)

        // D3DDevice_SetVerticalBlankCallback+0x00 : mov eax, [esp+0x04]
        { 0x00, 0x8B },
        { 0x01, 0x44 },
        { 0x02, 0x24 },
        { 0x03, 0x04 },

        // D3DDevice_SetVerticalBlankCallback+0x0A : mov [ecx+0x25AC], eax
        { 0x0A, 0x89 },
        { 0x0B, 0x81 },
        { 0x0C, 0xAC }, // SetSwapCallback A8 vs SetVerticalBlankCallback AC
        { 0x0D, 0x25 },
        { 0x0E, 0x00 },

        // D3DDevice_SetVerticalBlankCallback+0x10 : retn 0x04
        { 0x10, 0xC2 },
        { 0x11, 0x04 },
        { 0x12, 0x00 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetSwapCallback
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetSwapCallback, 4039, 12)

        // D3DDevice_SetSwapCallback+0x00 : mov eax, [esp+0x04]
        { 0x00, 0x8B },
        { 0x01, 0x44 },
        { 0x02, 0x24 },
        { 0x03, 0x04 },

        // D3DDevice_SetSwapCallback+0x04 : mov ecx, [addr]
        { 0x04, 0x8B },
        { 0x05, 0x0D },

        // D3DDevice_SetSwapCallback+0x0A : mov [ecx+0x25A8], eax
        { 0x0A, 0x89 },
        { 0x0B, 0x81 },
        { 0x0C, 0xA8 }, // SetSwapCallback A8 vs SetVerticalBlankCallback AC
        { 0x0D, 0x25 },

        // D3DDevice_SetSwapCallback+0x10 : retn 0x04
        { 0x10, 0xC2 },
        { 0x11, 0x04 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexData2f
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexData2f, 4039, 14)

        { 0x00, 0x56 },
        { 0x01, 0x8B },
        { 0x02, 0x35 },
        { 0x07, 0x8B },
        { 0x18, 0x14 },
        { 0x19, 0xCD },
        { 0x1A, 0x80 },
        { 0x1B, 0x18 },
        { 0x1C, 0x08 },
        { 0x1D, 0x00 },
        { 0x1E, 0x8B },
        { 0x1F, 0x4C },
        { 0x34, 0xC2 },
        { 0x35, 0x0C },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexData2s
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexData2s, 4039, 12)

        { 0x00, 0x56 },
        { 0x02, 0x35 },

        { 0x17, 0x8D },
        { 0x18, 0x14 },
        { 0x19, 0x8D },
        { 0x1A, 0x00 },
        { 0x1B, 0x19 },
        { 0x1C, 0x04 },
        { 0x1D, 0x00 },
        { 0x1E, 0x0F },
        { 0x1F, 0xBF },
        { 0x25, 0x0F },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexData4f
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexData4f, 4039, 11)

        { 0x00, 0x56 },
        { 0x07, 0x8B },
        { 0x18, 0xF9 },
        { 0x19, 0xFF },
        { 0x1A, 0x75 },
        { 0x1B, 0x07 },
        { 0x1C, 0xB9 },
        { 0x1D, 0x18 },
        { 0x1E, 0x15 },
        { 0x1F, 0x00 },
        { 0x56, 0xC2 },
/*
        { 0x0A, 0x46 },
        { 0x16, 0x08 },
        { 0x22, 0x09 },
        { 0x2E, 0x24 },
        { 0x3A, 0x24 },
        { 0x46, 0x8B },
        { 0x52, 0x14 },*/
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexData4s
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexData4s, 4039, 10)

        { 0x00, 0x56 },
        { 0x08, 0x06 },

        { 0x15, 0x24 },
        { 0x16, 0x08 },
        { 0x17, 0x8D },
        { 0x18, 0x14 },
        { 0x19, 0xCD },
        { 0x1A, 0x80 },
        { 0x1B, 0x19 },
        { 0x1F, 0xBF },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexData4ub
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexData4ub, 4039, 8)

        { 0x00, 0x56 },
        { 0x08, 0x06 },
        { 0x13, 0x8B },
        { 0x1C, 0x04 },
        { 0x26, 0x0F },
        { 0x30, 0x24 },
        { 0x3A, 0x24 },
        { 0x44, 0x89 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexDataColor
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexDataColor, 4039, 13)

        { 0x02, 0x35 },

        { 0x14, 0x8B },
        { 0x15, 0x4C },
        { 0x16, 0x24 },
        { 0x17, 0x0C },
        { 0x18, 0x8D },
        { 0x19, 0x14 },
        { 0x1A, 0x8D },
        { 0x1B, 0x40 },
        { 0x1C, 0x19 },
        { 0x1D, 0x04 },
        { 0x1E, 0x00 },
        { 0x25, 0x0F },
OOVPA_END;

// ******************************************************************
// * D3DDevice_End
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_End, 4039, 16) // Up to 5233

        { 0x01, 0x8B },
        { 0x07, 0x8B },
        { 0x0E, 0xE8 },
        { 0x16, 0x17 },
        { 0x1E, 0x00 },

        { 0x22, 0x08 },
        { 0x23, 0x89 },
        { 0x24, 0x06 },
        { 0x25, 0x8B },
        { 0x26, 0x46 },
        { 0x27, 0x08 },
        { 0x28, 0xF6 },
        { 0x29, 0xC4 },

        { 0x2E, 0x01 },
        { 0x36, 0x08 },
        { 0x3C, 0xC3 },
OOVPA_END;

// ******************************************************************
// * D3DResource_IsBusy
// ******************************************************************
OOVPA_NO_XREF(D3DResource_IsBusy, 4039, 11)

        // D3DResource_IsBusy+0x24 : test eax, 0x780000
        { 0x24, 0xA9 },
        { 0x25, 0x00 },
        { 0x26, 0x00 },
        { 0x27, 0x78 },

        // D3DResource_IsBusy+0x35 : jnz +0x41
        { 0x35, 0x75 },
        { 0x36, 0x41 },

        // D3DResource_IsBusy+0x4E : mov eax, [ecx+0x14]
        { 0x4E, 0x8B },
        { 0x4F, 0x41 },
        { 0x50, 0x14 },

        // D3DResource_IsBusy+0x76 : jnb +0x09
        { 0x76, 0x73 },
        { 0x77, 0x09 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_PersistDisplay
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_PersistDisplay, 4039, 17)

        { 0x01, 0xEC },
        { 0x02, 0x08 },
        { 0x03, 0x57 },
        { 0x04, 0x8B },
        { 0x05, 0x3D },

        { 0x11, 0xC0 },
        { 0x12, 0x89 },
        { 0x13, 0x44 },
        { 0x14, 0x24 },
        { 0x15, 0x04 },
        { 0x16, 0x74 },
        { 0x17, 0x0F },
        { 0x18, 0x50 },
        { 0x19, 0xFF },
        { 0x1A, 0x15 },

        { 0x1F, 0x6A },

        { 0x3F, 0xAF },
OOVPA_END;

// ******************************************************************
// * D3DDevice_DrawVerticesUP
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_DrawVerticesUP, 4039, 13)

        { 0x00, 0x55 },
        { 0x01, 0x8B },
        { 0x02, 0xEC },
        { 0x03, 0x83 },
        { 0x04, 0xEC },
        { 0x05, 0x14 },
        { 0x06, 0x57 },
        { 0x07, 0x8B },
        { 0x08, 0x3D },

        { 0x24, 0x4D },
        { 0x30, 0x97 },

        { 0x62, 0x00 },
        { 0x85, 0xB7 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_DrawIndexedVerticesUP, 4039, 15)

        { 0x00, 0x55 },
        { 0x01, 0x8B },
        { 0x02, 0xEC },
        { 0x03, 0x83 },
        { 0x04, 0xEC },
        { 0x05, 0x14 },
        { 0x06, 0x53 },
        { 0x07, 0x56 },
        { 0x08, 0x57 },
        { 0x09, 0x8B },
        { 0x0A, 0x3D },

        { 0x25, 0x8B },
        { 0x3D, 0x87 },

        { 0x48, 0x00 },
        { 0x5C, 0x8D },
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetDisplayMode
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetDisplayMode, 4039, 24)

        { 0x00, 0x56 },

        { 0x0B, 0x00 },
        { 0x0C, 0x00 },
        { 0x0D, 0x8B },
        { 0x0E, 0x41 },
        { 0x0F, 0x10 },
        { 0x10, 0x85 },
        { 0x11, 0xC0 },
        { 0x12, 0x57 },
        { 0x13, 0x75 },
        { 0x14, 0x12 },
        { 0x15, 0x8B },
        { 0x16, 0x49 },
        { 0x17, 0x0C },
        { 0x18, 0xC1 },
        { 0x19, 0xE9 },
        { 0x1A, 0x14 },
        { 0x1B, 0x83 },
        { 0x1C, 0xE1 },
        { 0x1D, 0x0F },
        { 0x1E, 0xB8 },
        { 0x1F, 0x01 },

        { 0x4C, 0xD3 },
        { 0x4D, 0xE0 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_BeginPushBuffer
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_BeginPushBuffer, 4039, 11)

        { 0x00, 0x56 },
        { 0x07, 0x57 },
        { 0x1C, 0xBE },

        { 0x50, 0xFC },
        { 0x51, 0xFD },
        { 0x52, 0xFF },
        { 0x53, 0xFF },
        { 0x54, 0x8B },
        { 0x55, 0x46 },
        { 0x56, 0x08 },
        { 0x57, 0x83 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_RunPushBuffer
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_RunPushBuffer, 4039, 8)

        { 0x1E, 0x07 },
        { 0x3E, 0x00 },
        { 0x5E, 0x46 },
        { 0x7E, 0x24 },
        { 0x9E, 0x18 },
        { 0xBE, 0x74 },
        { 0xE2, 0x8B },
        { 0xFE, 0x24 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetVertexShader
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetVertexShader, 4039, 16)

        { 0x00, 0xA1 },

        { 0x05, 0x8B },
        { 0x06, 0x88 },
        { 0x07, 0xFC }, // D3DDevice_GetVertexShader 0xFC vs D3DDevice_GetPixelShader 0xE8
        { 0x08, 0x04 },
        { 0x09, 0x00 },
        { 0x0A, 0x00 },
        { 0x0B, 0x8B },
        { 0x0C, 0x54 },
        { 0x0D, 0x24 },
        { 0x0E, 0x04 },
        { 0x0F, 0x89 },
        { 0x10, 0x0A },
        { 0x11, 0xC2 },
        { 0x12, 0x04 },
        { 0x13, 0x00 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetPixelShader
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetPixelShader, 4039, 16)

        { 0x00, 0xA1 },

        { 0x05, 0x8B },
        { 0x06, 0x88 },
        { 0x07, 0xE8 }, // D3DDevice_GetVertexShader 0xFC vs D3DDevice_GetPixelShader 0xE8
        { 0x08, 0x04 },
        { 0x09, 0x00 },
        { 0x0A, 0x00 },
        { 0x0B, 0x8B },
        { 0x0C, 0x54 },
        { 0x0D, 0x24 },
        { 0x0E, 0x04 },
        { 0x0F, 0x89 },
        { 0x10, 0x0A },
        { 0x11, 0xC2 },
        { 0x12, 0x04 },
        { 0x13, 0x00 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetVertexShaderConstant
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetVertexShaderConstant, 4039, 12)

        { 0x00, 0x8B },
        { 0x0C, 0x24 },

        { 0x15, 0x57 },
        { 0x16, 0x8B },
        { 0x17, 0x7C },
        { 0x18, 0x24 },
        { 0x19, 0x10 },
        { 0x1A, 0x8D },
        { 0x1B, 0xB4 },
        { 0x1C, 0x10 },

        { 0x28, 0x8B },
        { 0x2F, 0x5F },
OOVPA_END;

// ******************************************************************
// * D3DDevice_IsFencePending
// ******************************************************************
OOVPA_XREF(D3DDevice_IsFencePending, 4039, 1+5,

    XRefNoSaveIndex,
    XRefOne)

        XREF_ENTRY( 0x01, XREF_D3DDEVICE ), // Derived

        { 0x07, 0x34 },
        { 0x0A, 0x30 },
        { 0x10, 0xD1 },
        { 0x17, 0x1B },
        { 0x1C, 0x04 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_AddRef, 4039, 10)

        // D3DDevice_AddRef+0x00 : mov eax, [addr]
        { 0x00, 0xA1 },

        // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x05B4]
        { 0x05, 0x8B },
        { 0x06, 0x88 },
        { 0x07, 0xB4 },
        { 0x08, 0x05 },

        // D3DDevice_AddRef+0x0B : inc ecx
        { 0x0B, 0x41 },

        // D3DDevice_AddRef+0x05 : mov [eax+0x05B4], ecx
        { 0x0C, 0x89 },
        { 0x0D, 0x88 },
        { 0x0E, 0xB4 },
        { 0x0F, 0x05 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetModelView
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetModelView, 4039, 8)

        { 0x00, 0x53 },
        { 0x15, 0x25 },
        { 0x2F, 0x81 },
        { 0x43, 0x43 },
        { 0x5A, 0x04 },
        { 0x72, 0x8D },
        { 0x88, 0x00 },
        { 0x9F, 0x75 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_GetModelView
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_GetModelView, 4039, 7)

        { 0x05, 0x57 },
        { 0x0A, 0x85 },
        { 0x10, 0xB0 },
        { 0x16, 0x10 },
        { 0x1C, 0x5E },
        { 0x22, 0xC1 },
        { 0x28, 0xE0 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetVertexShaderInput
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetVertexShaderInput, 4039, 16)

        { 0x03, 0x04 },
        { 0x04, 0x83 },
        { 0x05, 0xEC },
        { 0x06, 0x40 },
        { 0x07, 0x85 },
        { 0x08, 0xC0 },
        { 0x09, 0x53 },
        { 0x0A, 0x8B },
        { 0x0B, 0x1D },

        { 0x19, 0x25 },
        { 0x1A, 0xFF },
        { 0x1B, 0xFF },
        { 0x1C, 0xFF },
        { 0x1D, 0xBF },
        { 0x1E, 0x83 },
        { 0x1F, 0xC8 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_RunVertexStateShader
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_RunVertexStateShader, 4039, 8)

        { 0x00, 0x56 },
        { 0x09, 0x3B },
        { 0x14, 0x4C },
        { 0x1F, 0xC0 },
        { 0x2A, 0x40 },
        { 0x35, 0xF4 },
        { 0x40, 0xC7 },
        { 0x4B, 0x08 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_BeginPush2
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_BeginPush2, 4039, 12)

        { 0x00, 0x56 },
        { 0x07, 0x6A },

        { 0x10, 0x8B },
        { 0x11, 0x44 },
        { 0x12, 0x24 },
        { 0x13, 0x08 },
        { 0x14, 0x40 },
        { 0x15, 0x50 },
        { 0x16, 0x56 },
        { 0x17, 0xE8 },
        { 0x23, 0xC2 },
        { 0x24, 0x08 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_EndPush
// ******************************************************************
OOVPA_XREF(D3DDevice_EndPush, 4039, 1+11,

    XRefNoSaveIndex,
    XRefOne)

        XREF_ENTRY( 0x06, XREF_D3DDEVICE ), // Derived

        { 0x00, 0x8B },
        { 0x01, 0x44 },
        { 0x02, 0x24 },
        { 0x03, 0x04 },
        { 0x04, 0x8B },
        { 0x05, 0x0D },
        { 0x0A, 0x89 },
        { 0x0B, 0x01 },
        { 0x0C, 0xC2 },
        { 0x0D, 0x04 },
        { 0x0E, 0x00 },
OOVPA_END;

// ******************************************************************
// * D3DDevice_PrimeVertexCache
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_PrimeVertexCache, 4039, 15)

        { 0x02, 0x2D },

        { 0x07, 0x8B },
        { 0x08, 0x45 },
        { 0x09, 0x1C },
        { 0x0A, 0x56 },
        { 0x0B, 0x50 },
        { 0x0C, 0x8B },
        { 0x0D, 0xCD },

        { 0x19, 0x00 },
        { 0x1A, 0x8B },
        { 0x1B, 0x4D },
        { 0x1C, 0x04 },
        { 0x1D, 0xD1 },
        { 0x1E, 0xEE },
        { 0x1F, 0x3B },
OOVPA_END;

// ******************************************************************
// * D3DDevice_SetBackBufferScale
// ******************************************************************
OOVPA_NO_XREF(D3DDevice_SetBackBufferScale, 4039, 16)

        { 0x09, 0x86 },

        { 0x10, 0xC1 },
        { 0x11, 0xE9 },
        { 0x12, 0x04 },
        { 0x13, 0x83 },
        { 0x14, 0xE1 },
        { 0x15, 0x0F },
        { 0x16, 0x85 },
        { 0x17, 0xC9 },

        { 0x28, 0xD8 },
        { 0x29, 0x4C },
        { 0x2A, 0x24 },
        { 0x2B, 0x0C },
        { 0x2C, 0x83 },
        { 0x2D, 0xE0 },
        { 0x2E, 0x0F },
OOVPA_END;

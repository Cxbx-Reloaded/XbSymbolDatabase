// ******************************************************************
// *
// *   OOVPADatabase->D3D8->5028.inl
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
// * Direct3D_CreateDevice
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice,
                         5028) // Also for 5120, 5233, 5344 (5455 and later use generic 3911 version)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0xA1 },

    { 0x08, 0x85 },
    { 0x09, 0xC0 },
    { 0x0A, 0x75 },
    { 0x0B, 0x0A },
    { 0x0C, 0xC7 },
    { 0x0D, 0x05 },

    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x08 },
    { 0x15, 0x00 },
    { 0x16, 0xA1 },

    { 0x1B, 0x85 },
    { 0x1C, 0xC0 },
    { 0x1D, 0x75 },
    { 0x1E, 0x0A },
    { 0x1F, 0xC7 },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVertices
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawIndexedVertices,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x1E, 0x5E },
    { 0x3E, 0x17 },
    { 0x5E, 0x00 },
    { 0x7E, 0x8B },
    { 0x9E, 0x89 },
    { 0xBE, 0x2B },
    { 0xDE, 0x00 },
    { 0xFE, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_LoadVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader,
                         5028)
OOVPA_SIG_MATCH(

    { 0x09, 0x45 },
    { 0x14, 0x75 },
    { 0x21, 0x8B },
    { 0x2D, 0x8B },
    { 0x35, 0x04 },
    { 0x40, 0x00 },
    { 0x4B, 0x5E },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_OFFSET_D3DDEVICE_M_VERTEXSHADER), // Derived

    // D3DDevice_SetVertexShader+0x06 : test bl, 1
    { 0x06, 0xF6 },
    { 0x07, 0xC3 },
    { 0x08, 0x01 },

    // D3DDevice_SetVertexShader+0x11 : mov eax, [esi+0x037C]
    { 0x11, 0x8B },
    { 0x12, 0x86 },
    { 0x13, 0x7C },
    { 0x14, 0x03 },

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
// * D3D::SetFence
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         5028)
OOVPA_SIG_MATCH(

    { 0x0E, 0x05 },
    { 0x18, 0xC9 },

    { 0x28, 0xBA },
    { 0x29, 0x90 },
    { 0x2A, 0x1D },
    { 0x2B, 0x04 },
    { 0x2C, 0x00 },

    { 0x3C, 0x83 },
    { 0x3D, 0xE1 },
    { 0x3E, 0x3F },

    { 0x5E, 0x28 },
    { 0x86, 0x5D },
    { 0x98, 0xE8 },
    { 0xA2, 0x04 },
    //
);

// ******************************************************************
// * D3D::BlockOnTime
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_BlockOnTime,
                         5028)
OOVPA_SIG_MATCH(

    { 0x09, 0x30 },
    { 0x27, 0x07 },
    { 0x55, 0x7E },
    { 0x7B, 0x58 },
    { 0xE3, 0x80 },
    { 0xF5, 0x2C },
    //
);

// ******************************************************************
// * D3D_KickOffAndWaitForIdle
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_KickOffAndWaitForIdle,
                         5028)
OOVPA_SIG_MATCH(

    // D3D_KickOffAndWaitForIdle+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3D_KickOffAndWaitForIdle+0x05 : mov ecx, [eax+0x2C]
    { 0x05, 0x8B },
    { 0x06, 0x48 },
    { 0x07, 0x2C },

    // D3D_KickOffAndWaitForIdle+0x08 : push 2
    { 0x08, 0x6A },
    { 0x09, 0x02 },

    // D3D_KickOffAndWaitForIdle+0x0A : push ecx
    { 0x0A, 0x51 },

    // D3D_KickOffAndWaitForIdle+0x0B : call [addr]
    { 0x0B, 0xE8 },

    // D3D_KickOffAndWaitForIdle+0x10 : retn
    { 0x10, 0xC3 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShaderConstantNotInline
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetVertexShaderConstantNotInline,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0B, 0x10 },

    { 0x10, 0x75 },
    { 0x11, 0x15 },
    { 0x12, 0x56 },
    { 0x13, 0x57 },
    { 0x14, 0x8B },

    { 0x1A, 0xC7 },
    { 0x31, 0xC2 },
    { 0x32, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_AddRef
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_AddRef,
                         5028)
OOVPA_SIG_MATCH(

    // D3DDevice_AddRef+0x00 : mov eax, [addr]
    { 0x00, 0xA1 },

    // D3DDevice_AddRef+0x05 : mov ecx, [eax+0x04FC]
    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xFC },
    { 0x08, 0x04 },

    // D3DDevice_AddRef+0x0B : inc ecx
    { 0x0B, 0x41 },

    // D3DDevice_AddRef+0x0C : mov [eax+0x04FC], ecx
    { 0x0C, 0x89 },
    { 0x0D, 0x88 },
    { 0x0E, 0xFC },
    { 0x0F, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_InsertCallback
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_InsertCallback,
                         5028)
OOVPA_SIG_MATCH(

    { 0x0C, 0x72 },
    { 0x1A, 0x10 },
    { 0x28, 0x85 },
    { 0x36, 0xC7 },
    { 0x44, 0x0C },
    { 0x52, 0x00 },
    { 0x60, 0x00 },
    //
);

// ******************************************************************
// * D3DDevice_GetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShader,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x80 },
    { 0x08, 0x03 },
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
    //
);

// ******************************************************************
// * D3DDevice_GetVertexShaderConstant
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetVertexShaderConstant,
                         5028)
OOVPA_SIG_MATCH(

    { 0x07, 0x24 },
    { 0x08, 0x08 },
    { 0x09, 0xC1 },
    { 0x0A, 0xE1 },
    { 0x0B, 0x04 },
    { 0x10, 0x7C },
    { 0x14, 0xE6 },
    { 0x18, 0x02 },
    //
);

// ******************************************************************
// * D3DDevice_GetPixelShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetPixelShader,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0x6C },
    { 0x08, 0x03 },
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
    //
);

// ******************************************************************
// * D3D::CommonSetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3D_CommonSetRenderTarget, 5028, 12)
    {
#else
OOVPA_XREF(D3D_CommonSetRenderTarget, 5028, 1 + 12,
           XRefOne)
{

    XREF_ENTRY(0x18, XREF_OFFSET_D3DDEVICE_M_RENDERTARGET), // Derived TODO : Verify offset
#endif
        { 0x02, 0x1C },
            { 0x1A, 0x15 },

            { 0x3D, 0x28 },
            { 0x3E, 0x05 },
            { 0x3F, 0x00 },
            { 0x40, 0x00 },
            { 0x41, 0x89 },
            { 0x42, 0x4C },
            { 0x43, 0x24 },
            { 0x44, 0x24 },

            { 0x7E, 0xD8 },
            { 0x7F, 0x05 },
    }
OOVPA_END;

// ******************************************************************
// * D3DDevice_LazySetStateVB
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LazySetStateVB,
                         5028)
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
    { 0x49, 0x7C },
    { 0x4A, 0x03 },
    { 0x4B, 0x00 },
    { 0x4C, 0x00 },

    { 0x66, 0x3B },
    { 0x67, 0xC1 },
    //
);

// ******************************************************************
// * D3D::CDevice::LazySetStateUP
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_LazySetStateUP,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x2F, 0x8B },
    { 0x30, 0x86 },
    { 0x31, 0x7C },
    { 0x32, 0x03 },
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
// * D3DDevice_BeginPush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_BeginPush,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x09, XREF_D3DDevice_LazySetStateVB),

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x06, 0x6A },
    { 0x07, 0x00 },

    { 0x11, 0x40 },

    { 0x12, 0x89 },
    { 0x13, 0x44 },
    { 0x14, 0x24 },
    { 0x15, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_IsFencePending
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_IsFencePending,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x01, XREF_D3DDEVICE), // Derived

    { 0x07, 0x30 },
    { 0x0A, 0x2C },
    { 0x10, 0xD1 },
    { 0x17, 0x1B },
    { 0x1C, 0x04 },
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff,
                         5028)
OOVPA_SIG_MATCH(

    { 0x07, 0x08 },
    { 0x17, 0xC4 },
    { 0x18, 0x20 },
    { 0x19, 0x75 },
    { 0x1A, 0x63 },
    { 0x1B, 0xA1 },
    { 0x6D, 0x85 },
    { 0x7E, 0xBA },
    //
);

// ******************************************************************
// * D3DDevice_BeginStateBig
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_BeginStateBig,
                         5028)
OOVPA_SIG_MATCH(

    { 0x01, 0x0D },
    { 0x07, 0x01 },
    { 0x10, 0x8D },

    { 0x16, 0x02 },
    { 0x17, 0x00 },
    { 0x18, 0x00 },
    { 0x19, 0x3B },
    { 0x1A, 0xD1 },
    { 0x1B, 0x72 },
    { 0x1C, 0x23 },
    { 0x1D, 0xA1 },

    { 0x22, 0x8B },
    { 0x2B, 0x00 },
    { 0x34, 0xCA },
    { 0x40, 0x5E },
    //
);

// ******************************************************************
// * D3DDevice_IsBusy
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_IsBusy,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x06, 0x80 },

    { 0x13, 0x44 },
    { 0x14, 0x32 },
    { 0x15, 0x00 },
    { 0x16, 0x00 },
    { 0x17, 0x74 },
    { 0x18, 0x06 },
    { 0x19, 0xB8 },
    { 0x1A, 0x01 },
    { 0x1B, 0x00 },

    { 0x1F, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_DrawIndexedVerticesUP
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_DrawIndexedVerticesUP,
                      5028,
                      XRefOne)
OOVPA_SIG_MATCH(

    // D3DDevice_DrawIndexedVerticesUP+0x07 : mov esi,[D3D__PDEVICE]
    XREF_ENTRY(0x09, XREF_D3DDEVICE),

    // D3DDevice_DrawIndexedVerticesUP+0x00 : push ebp
    OV_MATCH(0x00, 0x55),

    // D3DDevice_DrawIndexedVerticesUP+0x03 : sub esp,0x14
    OV_MATCH(0x03, 0x83, 0xEC, 0x14),

    // D3DDevice_DrawIndexedVerticesUP+0x07 : mov esi,[D3D__PDEVICE]
    OV_MATCH(0x07, 0x8B, 0x35),

    // D3DDevice_DrawIndexedVerticesUP+0x0D : mov ecx,esi
    OV_MATCH(0x0D, 0x8B, 0xCE),

    // D3DDevice_DrawIndexedVerticesUP+0x0F : mov [ebp-0x8],e__
    OV_MATCH(0x0F, 0x89),
    OV_MATCH(0x11, 0xF8), // D3DDevice_DrawIndexedVerticesUP 5028 0xF8 vs D3DDevice_DrawVerticesUP 4039 0xEC

    //
);

// ******************************************************************
// * D3DDevice_GetShaderConstantMode
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetShaderConstantMode,
                         5028)
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x88 },
    { 0x07, 0xD8 },
    { 0x08, 0x14 },
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
    //
);

// ******************************************************************
// * Rollback support signature(s)
// ******************************************************************
#define D3DDevice_Begin_5028 D3DDevice_Begin_4361

// ******************************************************************
// *
// *   OOVPADatabase->D3D8->5455.inl
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
// * D3DDevice_SelectVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SelectVertexShader,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x1D, 0xBE },

    { 0x3F, 0x00 },
    { 0x40, 0x10 },
    { 0x41, 0x00 },
    { 0x42, 0x00 },
    { 0x43, 0x8B },
    { 0x44, 0x06 },
    { 0x45, 0x3B },
    { 0x46, 0x46 },

    { 0x58, 0x8B },
    { 0x7B, 0xE8 },
    //
);

// ******************************************************************
// * D3DDevice_SetViewport
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetViewport,
                         5455)
OOVPA_SIG_MATCH(

    { 0x1E, 0x86 },
    { 0x3E, 0x1B },
    { 0x5E, 0x8B },
    { 0x7E, 0x6D },
    { 0x9E, 0x81 },
    { 0xBE, 0x0C },
    { 0xDE, 0x75 },
    { 0xFE, 0x85 },
    //
);

// ******************************************************************
// * D3DDevice_CreateVertexBuffer2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreateVertexBuffer2,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x08, 0xE8 },

    { 0x16, 0x08 },
    { 0x17, 0x68 },
    { 0x18, 0x00 },
    { 0x19, 0x00 },
    { 0x1A, 0x80 },
    { 0x1B, 0xB2 },
    { 0x1C, 0x50 },
    { 0x1D, 0xE8 },

    { 0x26, 0x68 },
    { 0x31, 0x33 },
    { 0x3A, 0xFF },
    { 0x44, 0x01 },
    //
);

// ******************************************************************
// * D3DDevice_CreatePalette2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CreatePalette2,
                         5455)
OOVPA_SIG_MATCH(

    { 0x0D, 0x8B },
    { 0x16, 0x00 },
    { 0x23, 0x68 },
    { 0x2E, 0x85 },
    { 0x3D, 0x5E },
    { 0x46, 0x1E },
    { 0x52, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_SetVertexShader
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetVertexShader,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_OFFSET_D3DDevice__m_VertexShader), // Derived (confirmed)

    { 0x1E, 0x89 },
    { 0x3E, 0x5F },
    { 0x61, 0x3B },
    { 0x81, 0x00 },
    { 0x9E, 0x00 },
    { 0xBE, 0x8B },
    { 0xDE, 0x04 },
    { 0xFE, 0xC1 },
    //
);

// ******************************************************************
// * D3DDevice_GetViewport
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_GetViewport,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x01, XREF_D3D_g_pDevice), // Derived

    { 0x00, 0xA1 },

    { 0x05, 0x8B },
    { 0x06, 0x4C },
    { 0x07, 0x24 },
    { 0x08, 0x04 },
    { 0x09, 0x05 },

    { 0x0C, 0x00 },
    { 0x0D, 0x00 },
    { 0x0E, 0x8B },

    { 0x2A, 0x8B },
    { 0x2B, 0x40 },
    { 0x2C, 0x14 },
    { 0x2D, 0x89 },
    { 0x2E, 0x41 },
    { 0x2F, 0x14 },
    { 0x30, 0xC2 },
    { 0x31, 0x04 },
    //
);

// ******************************************************************
// * D3DDevice_SetScreenSpaceOffset
// ******************************************************************
// Generic OOVPA as of 5455 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetScreenSpaceOffset,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov e??,[D3D_g_pDevice]
    XREF_ENTRY(0x0D, XREF_D3D_g_pDevice),

    // fld [esp + param_1]
    OV_MATCH(0x00, 0xD9, 0x44, 0x24, 0x04),

    // fadd [0x????????]
    OV_MATCH(0x05, 0xD8, 0x05),
    // mov e??,[D3D_g_pDevice]
    OV_MATCH(0x0B, 0x8B),

    // fld [esp + param_2]
    OV_MATCH(0x19, 0xD9, 0x44, 0x24, 0x0C),
    //
);

// ******************************************************************
// * D3D::SetTileNoWait
// ******************************************************************
// Generic OOVPA as of 5455 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3D_SetTileNoWait,
                         5455)
OOVPA_SIG_MATCH(
    // sub esp,0x1C
    OV_MATCH(0x00, 0x83, 0xEC, 0x1C),
    // eax,[esp + param_2]
    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x24),
    // test eax,eax
    OV_MATCH(0x07, 0x85, 0xC0),

    // js +0x04
    // xor eax,eax
    // xor esi,esi
    OV_MATCH(0x36, 0x78, 0x04, 0x33, 0xC0, 0x33, 0xF6),

    // and e??,0x0FFFFFFF
    OV_MATCH(0x70, 0x81),
    // OV_MATCH(0x69, 0xE1), // Sometimes changed over builds.
    OV_MATCH(0x72, 0xFF, 0xFF, 0xFF, 0x0F) // 0x0F vs 0x03 from D3DDevice_SetTile
    //
);

// ******************************************************************
// * CMiniport::InitHardware
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMiniport_InitHardware,
                         5455) // Also for 5558, 5659, 5788, 5849, 5933
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

    { 0x1D, 0x8D },
    { 0x1E, 0x86 },
    { 0x1F, 0xAC },
    //
);

// ******************************************************************
// * D3DDevice_GetTile
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetTile,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x0D },

    { 0x13, 0x00 },
    { 0x14, 0x8B },
    { 0x15, 0x0A },
    { 0x16, 0x8B },
    { 0x17, 0x44 },
    { 0x18, 0x24 },
    { 0x19, 0x08 },
    { 0x1A, 0x89 },

    { 0x3A, 0xC2 },
    { 0x3B, 0x08 },
    //
);

// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDevice_KickOff,
                      5455,
                      XRefOne)
OOVPA_SIG_MATCH(
    // mov eax, XREF_D3D_g_pDevice
    XREF_ENTRY(0x1A, XREF_D3D_g_pDevice), // Derived

    // push esi
    // mov esi, ecx
    OV_MATCH(0x00, 0x56, 0x8B, 0xF1),
    // mov eax, [esi + 8]
    // test al, 0x04
    OV_MATCH(0x03, 0x8B, 0x46, 0x08, 0xA8, 0x04),

    // test ah, 0x20
    OV_MATCH(0x14, 0xF6, 0xC4, 0x20),

    // mov eax, XREF_D3D_g_pDevice
    OV_MATCH(0x19, 0xA1),

    //
);

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
// Generic as of OOVPA 5344/5455 and newer.
// The only difference between 5344/5455 is the offset shift for
// D3DDevice__m_RenderTarget's asm code.
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 5455, 13)
    {
#else
OOVPA_XREF(D3DDevice_SetRenderTarget,
           5455,
           1 + 13,
           XRefOne)
{

    // D3DDevice_SetRenderTarget+0x17 : mov eax,[edi+0x________]
    XREF_ENTRY(0x19, XREF_OFFSET_D3DDevice__m_RenderTarget), // Derived // NOTE 5344 is at offset 0x18
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0x0C
        OV_MATCH(0x00, 0x83, 0xEC, 0x0C),

            // D3DDevice_SetRenderTarget+0x17 : mov eax,[edi+0x________]
            OV_MATCH(0x17, 0x8B, 0x87), // Offset 5455+ 0x17 vs 5344 0x16

            // D3DDevice_SetRenderTarget+0xF1 : shr ecx,0x14
            OV_MATCH(0xF1, 0xC1, 0xE9, 0x14),

            // D3DDevice_SetRenderTarget+0xF4 : and ecx, 0x0F
            OV_MATCH(0xF4, 0x83, 0xE1, 0x0F),

            // D3DDevice_SetRenderTarget+0xFC : shl eax,cl
            OV_MATCH(0xFC, 0xD3, 0xE0),
    }
OOVPA_END;

// ******************************************************************
// * D3D_AllocContiguousMemory
// ******************************************************************
// Generic OOVPA as of 5455 and newer.
OOVPA_SIG_HEADER_NO_XREF(D3D_AllocContiguousMemory,
                         5455)
OOVPA_SIG_MATCH(

    // D3D_AllocContiguousMemory+0x00 : cmp [esp+0x08],0x00001000
    OV_MATCH(0x00, 0x81, 0x7C), //, 0x24, 0x08
    OV_MATCH(0x04, 0x00, 0x10, 0x00),

    // D3D_AllocContiguousMemory+0x0F : shl eax,0x18
    OV_MATCH(0x0F, 0xC1, 0xE0, 0x18),

    // D3D_AllocContiguousMemory+0x12 : or eax,0xB0800000
    OV_MATCH(0x12, 0x0D, 0x00, 0x00, 0x80, 0xB0),

    // D3D_AllocContiguousMemory+0x31 : jmp XMemAlloc
    OV_MATCH(0x31, 0xE9),

    //
);

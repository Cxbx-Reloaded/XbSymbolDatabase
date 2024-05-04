// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->4034.inl
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
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * D3DDevice_SetTransform
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTransform_0__LTCG_eax1_edx2,
                      4034,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov ebx,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice), // Derived

    // call D3D::UpdateProjectionViewportTransform
    XREF_ENTRY(0xF5, XREF_D3D_UpdateProjectionViewportTransform),

    // push ebx
    // mov ebx,[D3D_g_pDevice]
    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x01, 0x8B, 0x1D),

    // mov ecx,param_1
    OV_MATCH(0x08, 0x8B, 0xC8),
    // shl ecx,0x6
    OV_MATCH(0x0A, 0xC1, 0xE1, 0x06),

    // mov ecx,0x10
    OV_MATCH(0x15, 0xB9, 0x10, 0x00 /*, 0x00, 0x00*/),

    // call D3D::UpdateProjectionViewportTransform
    OV_MATCH(0xF4, 0xE8),

    // ret
    OV_MATCH(0x103, 0xC3), // LTCG 0xC3 vs non-LTCG 0xC2
    //
);

// ******************************************************************
// * D3D::CDevice::FreeFrameBuffers
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDevice_FreeFrameBuffers_0__LTCG_ebx1,
                      4034,
                      XRefTwo)
OOVPA_SIG_MATCH(
    // call [AvGetSavedDataAddress]
    XREF_ENTRY(0x02, XREF_KT_FUNC_AvGetSavedDataAddress),
    // call [AvSendTVEncoderOption]
    XREF_ENTRY(0x18, XREF_KT_FUNC_AvSendTVEncoderOption),

    // call [AvGetSavedDataAddress]
    OV_MATCH(0x00, 0xFF, 0x15),

    // call [AvSendTVEncoderOption]
    OV_MATCH(0x16, 0xFF, 0x15),

    // This is a requirement to separate detection vs CDevice_FreeFrameBuffers_4 (4432)
    // push ebp
    OV_MATCH(0x22, 0x55),

    // mov esi, [ebx + 0x????]
    OV_MATCH(0x63, 0x8B, 0xB3),

    // call ????
    OV_MATCH(0x69, 0xE8),
    // mov [ebx + 0x????], e??
    OV_MATCH(0x6E, 0x89),

    // cmp [ebx + 0x????], e??
    OV_MATCH(0x74, 0x39),
    //
);

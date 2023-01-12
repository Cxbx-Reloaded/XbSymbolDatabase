// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->4721.inl
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
// * D3DDevice_Swap
// ******************************************************************
//7505BB050000008B ...C3
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_Swap_0,
                         2036)
OOVPA_SIG_MATCH(

    { 0x01, 0x56 },

    { 0x26, 0x75 },
    { 0x27, 0x05 },
    { 0x28, 0xBB },
    { 0x29, 0x05 },
    { 0x2A, 0x00 },
    { 0x2B, 0x00 },
    { 0x2C, 0x00 },
    { 0x2D, 0x8B },
    //
);

// ******************************************************************
// * D3D::SetTileNoWait
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3D_SetTileNoWait_0__LTCG_ecx1_eax2,
                      4721,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov eax,[D3D_g_pDevice]
    XREF_ENTRY(0x0A, XREF_D3D_g_pDevice),

    // sub esp,0x18
    OV_MATCH(0x00, 0x83, 0xEC, 0x18),

    // mov esi,eax(param_2)
    OV_MATCH(0x05, 0x8B, 0xF0),

    // mov eax,[D3D_g_pDevice]
    OV_MATCH(0x09, 0xA1),

    // mov ebx,ecx(param_1)
    OV_MATCH(0x0F, 0x8B, 0xD9),

    // mov [esp + 0x20],0
    OV_MATCH(0x2D, 0xC7, 0x44, 0x24, 0x20, 0x00, 0x00, 0x00, 0x00),
    // mov [esp + 0x1C],0
    OV_MATCH(0x35, 0xC7, 0x44, 0x24, 0x1C),
    //
);

// ******************************************************************
// * D3DDevice_SetTexture
// ******************************************************************
//81C10000F8FF89 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetTexture_4__LTCG_eax_Stage,
                         2036)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x2B, 0x81 },
    { 0x2C, 0xC1 },
    { 0x2D, 0x00 },
    { 0x2E, 0x00 },
    { 0x2F, 0xF8 },
    { 0x30, 0xFF },
    { 0x31, 0x89 },
    //
);

// ******************************************************************
// * D3DDevice_DrawVertices
// ******************************************************************
//0056576A00558B ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_DrawVertices_4,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },
    { 0x02, 0x8B },

    { 0x07, 0x00 },
    { 0x08, 0x56 },
    { 0x09, 0x57 },
    { 0x0A, 0x6A },
    { 0x0B, 0x00 },
    { 0x0C, 0x55 },
    { 0x0D, 0x8B },
    //
);

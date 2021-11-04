// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5028.inl
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
// * Direct3D_CreateDevice
// ******************************************************************
//85C9750AC705 ...C21000
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice_16__LTCG_eax_BehaviorFlags_ecx_ppReturnedDeviceInterface,
                         2048)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    { 0x0D, 0x85 },
    { 0x0E, 0xC9 },
    { 0x0F, 0x75 },
    { 0x10, 0x0A },
    { 0x11, 0xC7 },
    { 0x12, 0x05 },

    { 0x1B, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_SetTextureState_TexCoordIndex
// ******************************************************************
// ...C20400
OOVPA_SIG_HEADER_XREF(D3DDevice_SetTextureState_TexCoordIndex_4,
                      2058,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x14, XREF_D3DTSS_TEXCOORDINDEX), // Derived

    { 0x01, 0x53 },
    { 0x02, 0x8B },

    { 0x08, 0x55 },
    { 0x09, 0x8B },

    { 0x0C, 0x10 },
    { 0x0D, 0x8B },
    { 0x0E, 0xC6 },
    { 0x0F, 0xC1 },
    { 0x10, 0xE0 },
    { 0x11, 0x07 },
    //
);

//******************************************************************
//* D3DDevice_LoadVertexShader
//******************************************************************
//C7009C1E040089 ...C20400
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_LoadVertexShader_4,
                         2024)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x55 },

    { 0x5E, 0xC7 },
    { 0x5F, 0x00 },
    { 0x60, 0x9C },
    { 0x61, 0x1E },
    { 0x62, 0x04 },
    { 0x63, 0x00 },
    { 0x64, 0x89 },
    //
);

// ******************************************************************
// * D3D_CommonSetRenderTarget
// ******************************************************************
//8B490CC1E91483E10FB801
OOVPA_SIG_HEADER_NO_XREF(D3D_CommonSetRenderTarget,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x83 },
    { 0x01, 0xEC },

    { 0x57, 0x8B },
    { 0x58, 0x49 },
    { 0x59, 0x0C },
    { 0x5A, 0xC1 },
    { 0x5B, 0xE9 },
    { 0x5C, 0x14 },
    { 0x5D, 0x83 },
    { 0x5E, 0xE1 },
    { 0x5F, 0x0F },
    { 0x60, 0xB8 },
    { 0x61, 0x01 },
    //
);

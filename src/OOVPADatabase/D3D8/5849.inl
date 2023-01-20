// ******************************************************************
// *
// *   OOVPADatabase->D3D8->5849.inl
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
// * D3DDevice_SetRenderState_StencilEnable
// ******************************************************************
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_StencilEnable,
                      5849,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov esi,[D3D_g_pDevice]
    XREF_ENTRY(0x03, XREF_D3D_g_pDevice),
    // [D3DRS_StencilEnable],e??
    XREF_ENTRY(0x0E, XREF_D3DRS_StencilEnable),

    // push esi
    OV_MATCH(0x00, 0x56),
    // mov esi,[D3D_g_pDevice]
    OV_MATCH(0x01, 0x8B, 0x35),

    // mov e??,[esp + param_1]
    OV_MATCH(0x08, 0x8B),
    OV_MATCH(0x0A, 0x24, 0x0C),

    // [D3DRS_StencilEnable],e??
    OV_MATCH(0x0C, 0x89),
    // Do NOT use any offsets after 0x1D
);

// ******************************************************************
// * D3D::SetFence
// * SOURCE: Spiderman 2
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3D_SetFence,
                         5849)
OOVPA_SIG_MATCH(

    { 0x0E, 0x05 },
    { 0x17, 0xC7 },
    { 0x3E, 0x40 },
    { 0x5E, 0x00 },
    { 0x87, 0x4E },
    { 0x98, 0x83 },
    { 0xA8, 0x75 },
    //
);

// ******************************************************************
// * D3DDevice_SetRenderState_StencilFail
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_StencilFail,
                         5849)
OOVPA_SIG_MATCH(

    { 0x0C, 0x89 },
    { 0x1E, 0x8B },
    { 0x28, 0x74 },
    { 0x36, 0xD2 },
    { 0x44, 0x3D },
    { 0x52, 0xC7 },
    { 0x60, 0x04 },
    { 0x6E, 0x00 },
    //
);

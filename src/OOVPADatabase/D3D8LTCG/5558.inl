// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5849.inl
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

//test case: OddWorld Stranger's Wrath
// ******************************************************************
// * D3D::CDevice::KickOff
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDevice_KickOff_0_ecx,
                      5558,
                      XRefOne)
OOVPA_SIG_MATCH(
    // mov eax, XREF_D3D_g_pDevice
    XREF_ENTRY(0x1E, XREF_D3D_g_pDevice), // Derived

    // mov eax, [ecx+8]
    OV_MATCH(0x00, 0x8B, 0x41, 0x08),
    // test al, 4
    // push esi
    // jz EIP+8
    OV_MATCH(0x03, 0xA8, 0x04, 0x56, 0x74, 0x08),

    // test ah, 0x20
    OV_MATCH(0x12, 0xF6, 0xC4, 0x20),

    // mov edi, XREF_D3D_g_pDevice
    OV_MATCH(0x1C, 0x8B, 0x3D),

    //
);

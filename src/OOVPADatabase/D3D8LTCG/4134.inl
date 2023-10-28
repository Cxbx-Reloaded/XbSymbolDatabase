// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->4134.inl
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
// * D3DDevice::MakeSpace
// ******************************************************************
// Almost identical to generic 4134 signature.
// Earliest found is in titles with 5659 build.
OOVPA_SIG_HEADER_XREF(D3DDevice_MakeSpace,
                      1036,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call D3D::MakeRequestedSpace
    XREF_ENTRY(0x0B, XREF_D3D_MakeRequestedSpace),

    // mov eax, [addr]
    OV_MATCH(0x00, 0xA1),

    // push ecx
    OV_MATCH(0x09, 0x51),
    // call D3D::MakeRequestedSpace
    OV_MATCH(0x0A, 0xE8),
    // ret
    OV_MATCH(0x0F, 0xC3), // required to separate this detection from inlined function
    //
);

// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->3911.inl
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

// test case: NASCAR Heat 2002
//  ******************************************************************
//  * D3D::CDevice::KickOff
//  ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDevice_KickOff_0_edx,
                      3925)
OOVPA_SIG_MATCH(

    // test eax, eax
    // jz EIP+8
    OV_MATCH(0x05, 0x85, 0xC0, 0x75, 0x2B),
    // test byte ptr [edx+0Ch], 4
    OV_MATCH(0x09, 0xF6, 0x42, 0x0C, 0x04),
    // push esi
    // jz EIP+8
    OV_MATCH(0x0D, 0x56, 0x74, 0x08),

    //
);
// ******************************************************************
// *
// *   OOVPADatabase->D3D8LTCG->5120.inl
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
//00000800A1
OOVPA_SIG_HEADER_NO_XREF(Direct3D_CreateDevice,
                         1036)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x09, 0xC0 },

    { 0x12, 0x00 },
    { 0x13, 0x00 },
    { 0x14, 0x08 },
    { 0x15, 0x00 },
    { 0x16, 0xA1 },
    //
);

// ******************************************************************
// * D3DDevice_Reset
// ******************************************************************
// Generic OOVPA as of 5120 and newer
OOVPA_SIG_HEADER_XREF(D3DDevice_Reset,
                      5120,
                      XRefOne)
OOVPA_SIG_MATCH(
    // call CDevice::FreeFrameBuffers
    XREF_ENTRY(0x37, XREF_D3D_CDevice_FreeFrameBuffers),

    // push ebx
    OV_MATCH(0x00, 0x53),

    // jnz +0x??
    OV_MATCH(0x33, 0x75),

    // call CDevice::FreeFrameBuffers
    OV_MATCH(0x36, 0xE8),
    // mov e??, [esp + param_1]
    OV_MATCH(0x3B, 0x8B),
    OV_MATCH(0x3D, 0x24, 0x14),
    //
);

// ******************************************************************
// * D3DDevice_SetPalette
// ******************************************************************
//000085C05774258B4E
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetPalette,
                         1048)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x01, 0x8B },

    { 0x11, 0x00 },
    { 0x12, 0x00 },
    { 0x13, 0x85 },
    { 0x14, 0xC0 },
    { 0x15, 0x57 },
    { 0x16, 0x74 },
    { 0x17, 0x25 },
    { 0x18, 0x8B },
    { 0x19, 0x4E },
    //
);

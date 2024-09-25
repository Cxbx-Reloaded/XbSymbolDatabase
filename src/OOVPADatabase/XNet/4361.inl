// ******************************************************************
// *
// *   OOVPADatabase->XNet->4361.inl
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
// * XnInit
// ******************************************************************
//Generic OOVPA as of 4361 and newer.
OOVPA_SIG_HEADER_NO_XREF(XnInit_24,
                         4361)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0F, 0xB9 },

    { 0x14, 0xBA },
    { 0x15, 0x01 },
    { 0x16, 0x00 },
    { 0x17, 0x00 },
    { 0x18, 0x00 },

    { 0x19, 0x0F },
    { 0x1A, 0xB1 },
    { 0x1B, 0x11 },

    { 0x1C, 0x33 },
    //{ 0x1D, 0xF6 },
    { 0x1E, 0x3B },
    //{ 0x1F, 0xC6 },

    { 0x23, 0xE8 },
    { 0x28, 0xEB },
    { 0x3F, 0x54 },
    //
);

// ******************************************************************
// * WSAStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(WSAStartup,
                      4361,
                      XRefOne)
OOVPA_SIG_MATCH(

    // WSAStartup+0x0F : call [XnInit]
    XREF_ENTRY(0x14, XREF_XnInit),

    // WSAStartup+0x00 : push [esp+0x08]
    { 0x00, 0xFF },
    { 0x01, 0x74 },
    { 0x02, 0x24 },
    { 0x03, 0x08 },

    // WSAStartup+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },
    //
);

// ******************************************************************
// * XNetStartup
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XNetStartup,
                      4361,
                      XRefOne)
OOVPA_SIG_MATCH(

    // XNetStartup+0x0F : call [XnInit]
    XREF_ENTRY(0x10, XREF_XnInit),

    // XNetStartup+0x00 : xor eax, eax
    { 0x00, 0x33 },
    { 0x01, 0xC0 },

    // XNetStartup+0x02 : push eax
    { 0x02, 0x50 },

    // XNetStartup+0x03 : push eax
    { 0x03, 0x50 },

    // XNetStartup+0x04 : push eax
    { 0x04, 0x50 },

    // XNetStartup+0x14 : retn 0x04
    { 0x14, 0xC2 },
    { 0x15, 0x04 },
    //
);

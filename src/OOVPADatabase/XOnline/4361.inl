// ******************************************************************
// *
// *   OOVPADatabase->XOnline->4361.inl
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
// * CXo::XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CXo_XOnlineLogon,
                         4361)
OOVPA_SIG_MATCH(

    { 0x02, 0xEC },

    { 0x0D, 0xFC },
    { 0x0E, 0x75 },
    { 0x0F, 0x07 },
    { 0x10, 0xB8 },
    { 0x11, 0x05 },
    { 0x12, 0x00 },
    { 0x13, 0x15 },
    { 0x14, 0x80 },
    { 0x15, 0xEB },

    { 0x24, 0xA8 },
    { 0x32, 0x33 },
    //
);

// ******************************************************************
// * XOnlineLogon
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XOnlineLogon,
                      4361,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0B, XREF_CXo_XOnlineLogon),

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x0A, 0xE9 },
    //
);

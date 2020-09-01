// ******************************************************************
// *
// *   OOVPADatabase->XOnline->4831.inl
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
// * CXo::XOnlineLogon
// ******************************************************************
OOVPA_XREF(CXo_XOnlineLogon, 4831, 15,

    XREF_CXo_XOnlineLogon,
    XRefZero)

        { 0x02, 0xEC },

        { 0x15, 0x00 },
        { 0x1C, 0xE8 },

        { 0x21, 0xA8 },
        { 0x22, 0x01 },
        { 0x23, 0x75 },
        { 0x24, 0x0C },
        { 0x25, 0xC7 },
        { 0x26, 0x45 },
        { 0x27, 0xF8 },
        { 0x28, 0x00 },
        { 0x29, 0x10 },
        { 0x2A, 0x15 },
        { 0x2B, 0x80 },
        { 0x2C, 0xE9 },
OOVPA_END;

// ******************************************************************
// * CXo::XOnlineMatchSearch
// ******************************************************************
OOVPA_XREF(CXo_XOnlineMatchSearch, 4831, 13,

    XREF_CXo_XOnlineMatchSearch,
    XRefZero)

        // push ebp
        // mov ebp, esp
        // test ecx, ecx
        // jnz eip + $09h
        OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x85, 0xC9, 0x75, 0x09),

        // pop ebp
        // ret $1Ch
        // pop ebp
        // jmp ...
        OV_MATCH(0x0C, 0x5D, 0xC2, 0x1C, 0x00, 0x5D, 0xE9),
OOVPA_END;

// ******************************************************************
// * XOnlineMatchSearch
// ******************************************************************
OOVPA_XREF(XOnlineMatchSearch, 4831, 1+4,

    XRefNoSaveIndex,
    XRefOne)

        XREF_ENTRY(0x0B, XREF_CXo_XOnlineMatchSearch),

        // push ebp
        // mov ebp, esp
        OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

        // jmp ...
        OV_MATCH(0x0A, 0xE9),
OOVPA_END;

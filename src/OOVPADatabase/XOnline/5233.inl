// ******************************************************************
// *
// *   OOVPADatabase->XOnline->5233.inl
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
// *  You should have received a copy of the GNU General Public License
// *  along with this program; see the file COPYING.
// *  If not, write to the Free Software Foundation, Inc.,
// *  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// *
// *  (c) 2020 Stefan Schmidt
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * CXo::XOnlineMatchSessionUpdate
// ******************************************************************
OOVPA_XREF(CXo_XOnlineMatchSessionUpdate, 5233, 19,

           XREF_CXo_XOnlineMatchSessionUpdate,
           XRefZero)
{

    // push ebp
    // mov ebp, esp
    // push esi
    // mov esi, ecx
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x56, 0x8B, 0xF1),
    // test esi, esi
    // jnz eip + $07h
    OV_MATCH(0x06, 0x85, 0xF6, 0x75),

    // push 0
    // push dword ptr [ebp + param_2]
    // mov ecx, esi
    OV_MATCH(0x11, 0x6A, 0x00, 0xFF, 0x75, 0x0C, 0x8B, 0xCE),
    // push dword ptr [ebp + param_1]
    OV_MATCH(0x18, 0xFF, 0x75, 0x08),
} OOVPA_END;

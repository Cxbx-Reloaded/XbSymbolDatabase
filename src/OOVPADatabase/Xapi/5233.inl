// ******************************************************************
// *
// *   OOVPADatabase->Xapi->5233.inl
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
// * MU_Init
// ******************************************************************
// Generic OOVPA as of 5233 and newer.
OOVPA_SIG_HEADER_XREF(MU_Init,
                      5233,

                      XREF_MU_Init,
                      XRefZero)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    // sub esp, 0x0C
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C),

    // push eax
    // push 0x00
    // push 0x3A
    // lea eax, [ebp-0x0C]
    OV_MATCH(0x8E, 0x50, 0x6A, 0x00, 0x6A, 0x3A, 0x8D, 0x45, 0xF4), // Was 5233 offset 0x8A

    //
);

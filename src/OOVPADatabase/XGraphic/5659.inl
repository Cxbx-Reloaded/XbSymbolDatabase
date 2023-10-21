// ******************************************************************
// *
// *   OOVPADatabase->XGraphic->4361.inl
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
// * XGSetSurfaceHeader
// ******************************************************************
// Generic OOVPA as of 5659 and newer.
OOVPA_SIG_HEADER_NO_XREF(XGSetSurfaceHeader,
                         5659)
OOVPA_SIG_MATCH(

    // XGSetSurfaceHeader+0x00 : push ebp, mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

        OV_MATCH(0x15, 0x14),
    
        // XGSetSurfaceHeader+0x0F : push 0x00, push 0x00
        OV_MATCH(0x0A, 0x6A, 0x00, 0x6A, 0x00),

        OV_MATCH(0x18, 0x10),
        
);

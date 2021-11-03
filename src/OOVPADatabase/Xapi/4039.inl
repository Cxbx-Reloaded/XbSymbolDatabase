// ******************************************************************
// *
// *   OOVPADatabase->Xapi->4039.inl
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
// * XCalculateSignatureBegin
// ******************************************************************
// TODO: Need to find out if XCalculateSignatureBegin had been changed
//       in 3950 and lower.
// Generic OOVPA as of 4034? and newer.
OOVPA_SIG_HEADER_NO_XREF(XCalculateSignatureBegin,
                         4034)
OOVPA_SIG_MATCH(

    // mov eax,ds:[0x00010118]
    OV_MATCH(0x00, 0xA1, 0x18, 0x01, 0x01, 0x00),

    // push [eax+0x08]
    OV_MATCH(0x05, 0xFF, 0x70, 0x08),

    // push [esp+0x08]
    OV_MATCH(0x08, 0xFF, 0x74, 0x24, 0x08),

    // call XCalculateSignatureBeginEx
    OV_MATCH(0x0C, 0xE8),

    // ret 0x0004
    OV_MATCH(0x11, 0xC2, 0x04, 0x00),
    //
);

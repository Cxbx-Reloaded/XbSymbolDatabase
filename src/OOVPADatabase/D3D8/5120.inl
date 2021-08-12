// ******************************************************************
// *
// *   OOVPADatabase->D3D8->5120.inl
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
// * D3DDevice_RunPushBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_RunPushBuffer,
                         5120)
OOVPA_SIG_MATCH(

    { 0x0B, 0x57 },
    { 0x10, 0xE8 },

    { 0x15, 0x8B },
    { 0x1F, 0x01 },

    { 0x8D, 0x8B },
    { 0x8E, 0x4E },
    { 0x8F, 0x30 },
    { 0x90, 0x8B },
    { 0x91, 0x11 },
    { 0x92, 0x8B },
    { 0x93, 0x4E },
    { 0x94, 0x2C },
    { 0x95, 0x8B },
    //
);

// ******************************************************************
// * D3DDevice_CopyRects
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_CopyRects,
                         5120)
OOVPA_SIG_MATCH(

    { 0x1E, 0xE1 },
    { 0x42, 0x84 },
    { 0x5E, 0x24 },
    { 0x7E, 0x8B },
    { 0x9E, 0x1C },
    { 0xBE, 0x00 },
    { 0xDE, 0xBD },
    { 0xFE, 0x4C },
    //
);

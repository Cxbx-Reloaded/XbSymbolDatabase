// ******************************************************************
// *
// *   OOVPADatabase->D3D8->4432.inl
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
// * D3DDevice_SetRenderState_ZEnable
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetRenderState_ZEnable,
                         4432)
OOVPA_SIG_MATCH(

    { 0x08, 0x06 },
    { 0x0E, 0xE8 },

    { 0x45, 0x48 },
    { 0x46, 0x0C },
    { 0x47, 0x83 },
    { 0x48, 0xC0 },
    { 0x49, 0x10 },
    { 0x4A, 0x89 },
    { 0x4B, 0x06 },
    { 0x4C, 0xA1 },

    { 0x5A, 0x74 },
    { 0x60, 0x2A },
    //
);

// ******************************************************************
// * D3DDevice_GetViewportOffsetAndScale
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_GetViewportOffsetAndScale,
                         4432) // Up to 5849
OOVPA_SIG_MATCH(

    { 0x00, 0xA1 },
    { 0x19, 0x05 },

    { 0x45, 0x00 },
    { 0x46, 0x8B },
    { 0x47, 0x50 },
    { 0x48, 0x08 },
    { 0x49, 0x33 },
    { 0x4A, 0xC9 },
    { 0x4B, 0x84 },
    { 0x4C, 0xF6 },

    { 0x5B, 0x74 },
    { 0x5C, 0x10 },
    //
);

// ******************************************************************
// * D3DDevice_SetDepthClipPlanes
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(D3DDevice_SetDepthClipPlanes,
                         4432)
OOVPA_SIG_MATCH(

    { 0x03, 0x0C },
    { 0x04, 0x48 },
    { 0x05, 0x83 },
    { 0x06, 0xF8 },
    { 0x07, 0x03 },
    { 0x08, 0x56 },
    { 0x09, 0x8B },
    { 0x0A, 0x35 },

    { 0x0F, 0x77 },
    { 0x10, 0x5F },
    { 0x11, 0xFF },
    { 0x12, 0x24 },
    { 0x13, 0x85 },

    { 0x18, 0x8B },
    { 0x1F, 0x0C },
    //
);

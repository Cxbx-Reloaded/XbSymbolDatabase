// ******************************************************************
// *
// *   OOVPADatabase->DSound->3936.inl
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
// * CSensaura3d::GetFullHRTFFilterPair
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CSensaura3d_GetFullHRTFFilterPair,
                         3936)
OOVPA_SIG_MATCH(

    { 0x05, 0x0C },
    { 0x0E, 0xD9 },
    { 0x20, 0xEB },
    { 0x28, 0xD9 },
    { 0x30, 0x6A },
    { 0xAA, 0xEB },
    { 0xAB, 0x17 },
    { 0xAC, 0xD8 },
    { 0xAD, 0x05 },
    //
);

// ******************************************************************
// * CMcpxStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Flush,
                         3936)
OOVPA_SIG_MATCH(

    { 0x08, 0xF6 },
    { 0x12, 0xF6 },

    { 0x22, 0x33 },
    { 0x24, 0x33 },

    { 0x2F, 0x83 },
    { 0x30, 0xFF },
    { 0x31, 0x03 },

    { 0x4D, 0xE8 },

    //CMcpxStream_Flush+0x54  : e__,0x80004004 (unique value)
    { 0x55, 0x04 },
    { 0x56, 0x40 },
    { 0x57, 0x00 },
    { 0x58, 0x80 },

    { 0x5F, 0xE8 },

    { 0xA1, 0xC9 },
    { 0xA2, 0xC3 },
    //
);

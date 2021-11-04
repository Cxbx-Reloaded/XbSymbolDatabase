// ******************************************************************
// *
// *   OOVPADatabase->DSound->4531.inl
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
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Discontinuity,
                      4531,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x24, XREF_CMcpxStream_Stop_Ex),

    // CMcpxStream_Discontinuity+0x00 : push esi; push edi
    { 0x00, 0x56 },
    { 0x01, 0x57 },

    // CMcpxStream_Discontinuity+0x12 : mov dx,0x800
    { 0x12, 0x66 },
    { 0x13, 0xBA },
    { 0x14, 0x00 },
    { 0x15, 0x08 },

    // CMcpxStream_Discontinuity+0x23 : call Stop@CMcpxStream@DirectSound@@QAEJ_JK@Z
    { 0x23, 0xE8 },

    // CMcpxStream_Discontinuity+0x2D : pop esi; ret
    { 0x2D, 0x5E },
    { 0x2E, 0xC3 },
    //
);

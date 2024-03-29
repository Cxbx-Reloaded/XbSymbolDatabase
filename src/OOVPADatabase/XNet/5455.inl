// ******************************************************************
// *
// *   OOVPADatabase->XNet->5455.inl
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
// * CXnSock::socket
// ******************************************************************
//Generic OOVPA as of 5455 and newer.
OOVPA_SIG_HEADER_NO_XREF(socket,
                         5455)
OOVPA_SIG_MATCH(

    { 0x00, 0x51 },
    { 0x0A, 0xB9 },

    { 0xB8, 0x83 },
    { 0xB9, 0xC8 },
    { 0xBA, 0xFF },
    { 0xBB, 0xEB },
    { 0xBC, 0x73 },
    { 0xBD, 0x53 },
    { 0xBE, 0xFF },
    { 0xBF, 0x15 },
    //
);

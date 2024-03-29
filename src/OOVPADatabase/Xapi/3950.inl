// ******************************************************************
// *
// *   OOVPADatabase->Xapi->3950.inl
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
// * XapiInitProcess
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiInitProcess,
                         3950)
OOVPA_SIG_MATCH(

    // XapiInitProcess+0x03 : sub esp, 30h
    { 0x05, 0x30 },

    // XapiInitProcess+0x0F : push 0x0C
    { 0x10, 0x6A },
    { 0x11, 0x0C },

    // XapiInitProcess+0x17 : repe stosd
    { 0x18, 0xF3 },
    { 0x19, 0xAB },

    // XapiInitProcess+0x42 : jnz +0x0A
    { 0x43, 0x75 },
    { 0x44, 0x0A },
    //
);

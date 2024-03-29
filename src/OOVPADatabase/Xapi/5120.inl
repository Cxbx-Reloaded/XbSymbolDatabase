// ******************************************************************
// *
// *   OOVPADatabase->Xapi->5120.inl
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
// * XInitDevices
// ******************************************************************
// * NOTE: We are actually intercepting USBD_Init, because
// *       XInitDevices Simply redirects to that function
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInitDevices,
                         5120)
OOVPA_SIG_MATCH(

    { 0x0E, 0x75 },
    { 0x20, 0xBE },
    { 0x2E, 0xC0 },
    { 0x3E, 0xEC },
    { 0x50, 0x0F },
    { 0x5F, 0xE8 },
    { 0x70, 0x5F },
    //
);

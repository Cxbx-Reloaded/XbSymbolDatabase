// ******************************************************************
// *
// *   OOVPADatabase->D3D8->3947.inl
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
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2017 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * D3DDevice_SetRenderTarget
// ******************************************************************
#ifndef WIP_LessVertexPatching
OOVPA_NO_XREF(D3DDevice_SetRenderTarget, 3947, 9)
#else
OOVPA_XREF(D3DDevice_SetRenderTarget, 3947, 1+9,

    XRefNoSaveIndex,
    XRefOne)

        XREF_ENTRY( 0x1D, XREF_OFFSET_D3DDEVICE_M_RENDERTARGET ), // Derived
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0xXX
        { 0x00, 0x83 },
        { 0x01, 0xEC },
        //{ 0x02, 0x30 }, // 3947 0x2C vs 3948 0x30

        // D3DDevice_SetRenderTarget+0x32 : and ecx, 0x0F
        { 0x32, 0x83 },
        { 0x33, 0xE1 },
        { 0x34, 0x0F },

        // D3DDevice_SetRenderTarget+0x35 : mov edi, 1
        { 0x35, 0xBF },
        { 0x36, 0x01 },

        // D3DDevice_SetRenderTarget+0x68 : inc eax
        { 0x68, 0x40 },

        // D3DDevice_SetRenderTarget+0xDA : push edx
        { 0xDA, 0x52 },
OOVPA_END;

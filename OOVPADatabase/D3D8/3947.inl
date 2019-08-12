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
// *  59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
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
OOVPA_XREF(D3DDevice_SetRenderTarget, 3947, 11,

    XREF_D3DDevice_SetRenderTarget,
    XRefZero)
#else
OOVPA_XREF(D3DDevice_SetRenderTarget, 3947, 1+11,

    XREF_D3DDevice_SetRenderTarget,
    XRefOne)

        XREF_ENTRY( 0x1D, XREF_OFFSET_D3DDEVICE_M_RENDERTARGET ), // Derived
#endif
        // D3DDevice_SetRenderTarget+0x00 : sub esp, 0xXX
        OV_MATCH(0x00, 0x83, 0xEC),
        //OV_MATCH(0x02, 0x30), // 3947 0x2C vs 3948 0x30

        // D3DDevice_SetRenderTarget+0x54 : mov eax, 0x00000001
        OV_MATCH(0x54, 0xB8, 0x01, 0x00),

        // D3DDevice_SetRenderTarget+0x59 : and ecx, 0x0F
        OV_MATCH(0x59, 0x83, 0xE1, 0x0F),

        // D3DDevice_SetRenderTarget+0x60 : shr eax,0x0C
        OV_MATCH(0x60, 0xC1, 0xE8, 0x0C),

OOVPA_END;

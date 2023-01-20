// ******************************************************************
// *
// *   OOVPADatabase->D3D8->3925.inl
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
// * D3DDevice_SetRenderState_MultiSampleType
// ******************************************************************
// Generic OOVPA as of 3925 and newer.
OOVPA_SIG_HEADER_XREF(D3DDevice_SetRenderState_MultiSampleType,
                      3925,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // mov [D3DRS_MultiSampleType],e??
    XREF_ENTRY(0x0B, XREF_D3DRS_MultiSampleType),

    // call D3DDevice_SetRenderTarget
    XREF_ENTRY(0x1E, XREF_D3DDevice_SetRenderTarget),

    // mov ecx,[esp + param_1]
    OV_MATCH(0x05, 0x8B, 0x4C, 0x24, 0x04),

    // call D3DDevice_SetRenderTarget
    OV_MATCH(0x1D, 0xE8),

    // retn 0x04
    OV_MATCH(0x22, 0xC2, 0x04),
    //
);

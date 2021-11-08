// ******************************************************************
// *
// *   OOVPADatabase->XActEng->5233.inl
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
// * XACT::CEngine::RegisterStreamedWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_RegisterStreamedWaveBank,
                         5233)
OOVPA_SIG_MATCH(

    { 0x04, 0x10 }, //RegisterStreamedWaveBank 0x10 vs RegisterWaveBank 0x14
    { 0x25, 0x8B },

    { 0x3A, 0x2E }, //RegisterStreamedWaveBank 0x2E vs RegisterWaveBank 0x32
    { 0x3B, 0xFF },
    { 0x3C, 0x74 },
    { 0x3D, 0x24 },
    { 0x3E, 0x14 },
    { 0x3F, 0x8B },
    { 0x40, 0xCE },
    { 0x41, 0xE8 },

    { 0x67, 0xEB },
    //
);

// ******************************************************************
// * XACT::CEngine::RegisterWaveBank
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XACT_CEngine_RegisterWaveBank,
                         5233)
OOVPA_SIG_MATCH(

    { 0x04, 0x14 }, //RegisterStreamedWaveBank 0x10 vs RegisterWaveBank 0x14
    { 0x1A, 0x3B },

    { 0x3A, 0x32 },
    { 0x3B, 0xFF },
    { 0x3C, 0x74 },
    { 0x3D, 0x24 },
    { 0x3E, 0x18 },
    { 0x3F, 0x8B },
    { 0x40, 0xCE },
    { 0x41, 0xFF },

    { 0x7C, 0xC2 },
    { 0x7D, 0x10 },
    //
);

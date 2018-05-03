// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// ******************************************************************
// *
// *   SymbolTableDB.c
// *
// *  xbSymbolTable is free software; you can redistribute them
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
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *
// *  All rights reserved
// *
// ******************************************************************
#define _XBOXKRNL_DEFEXTRN_

#include "xbSymbolDatabase.h" // For PairScanLibSec

#include "OOVPADatabase/Xapi.OOVPA.inl"
#include "OOVPADatabase/D3D8.OOVPA.inl"
#include "OOVPADatabase/D3D8LTCG.OOVPA.inl"
#include "OOVPADatabase/DSound.OOVPA.inl"
#include "OOVPADatabase/XG.OOVPA.inl"
#include "OOVPADatabase/XNET.OOVPA.inl"
#include "OOVPADatabase/XOnline.OOVPA.inl"
#include "OOVPADatabase/XactEng.OOVPA.inl"


// ******************************************************************
// * Xbox Symbol Table Database
// ******************************************************************

const SymbolTableList symbolTableList[] = {
    // Support inline functions in .text section
    { Lib_D3D8,{ Sec_text, Sec_D3D }, &D3D8_OOVPAV2, D3D8_OOVPA_COUNT },

    // Cannot support LTCG in HLE
    { Lib_D3D8LTCG,{ Sec_D3D }, &D3D8LTCG_OOVPAV2, D3D8LTCG_OOVPA_COUNT },

    // Jarupxx mention this is not a requirement?
    //{ Lib_D3DX8,{ Sec_D3DX }, _OOVPAV2, _OOVPA_COUNT },

    //
    { Lib_DSOUND,{ Sec_DSOUND }, &DSound_OOVPAV2, DSound_OOVPA_COUNT },

    // DSOUNDH is just meant to define hot fix, there is no separate section
    //{ Lib_DSOUNDH,{ Sec_DSOUND }, DSound_OOVPAV2, DSound_OOVPA_COUNT },

    //
    { Lib_XACTENG, { Sec_XACTENG }, &XACTENG_OOVPAV2, XACTENG_OOVPA_COUNT },

    // test case: Power Drome (Unluckily, it use LTCG version of the library.)
    //{ Lib_XACTENLT,{ Sec_XACTENG }, XACTENG_OOVPAV2, XACTENG_OOVPA_COUNT },

    //
    { Lib_XAPILIB,{ Sec_text, Sec_XPP }, &XAPILIB_OOVPAV2, XAPILIB_OOVPA_COUNT },

    // Support inline functions in .text section
    { Lib_XGRAPHC,{ Sec_text, Sec_XGRPH }, &XGRAPHC_OOVPAV2, XGRAPHC_OOVPA_COUNT },

    // Cannot support LTCG in HLE
    //{ Lib_XGRAPHCL,{ Sec_XGRPH }, XGRAPHC_OOVPAV2, XGRAPHC_OOVPA_COUNT },

    // Added Sec_text and Sec_XNET just in case.
    // TODO: Need to find out which function is only part of XOnlines.
    { Lib_XONLINE,{ Sec_text, Sec_XONLINE, Sec_XNET }, &XONLINES_OOVPAV2, XONLINES_OOVPA_COUNT },

    // Fun fact, XONLINES are split into 2 header sections.
    { Lib_XONLINES,{ Sec_text, Sec_XONLINE, Sec_XNET }, &XONLINES_OOVPAV2, XONLINES_OOVPA_COUNT },

    // Added Sec_text just in case.
    // TODO: Need to find out which function is only part of XNets.
    { Lib_XNET,{ Sec_text, Sec_XNET }, &XNET_OOVPAV2, XNET_OOVPA_COUNT },

    // XNETS only has XNET, might be true.
    { Lib_XNETS,{ Sec_text, Sec_XNET }, &XNET_OOVPAV2, XNET_OOVPA_COUNT },

    // test case: Stake
    { Lib_XNETN,{ Sec_text, Sec_XNET }, &XNET_OOVPAV2, XNET_OOVPA_COUNT },
};

// ******************************************************************
// * symbolTableListCount
// ******************************************************************
const unsigned int symbolTableListCount = OOVPA_TABLE_COUNT(symbolTableList);

// ******************************************************************
// * XRefDataBase
// ******************************************************************
unsigned int XRefDataBase[XREF_COUNT] = { 0 }; // Reset and populated by EmuHLEIntercept

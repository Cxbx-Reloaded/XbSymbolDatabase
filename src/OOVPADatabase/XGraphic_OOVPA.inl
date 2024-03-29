// ******************************************************************
// *
// *   OOVPADatabase->XGraphic_OOVPA.inl
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

// Titles which did compiled with full library
//   [LibV] Title Name                       |  Verify   |  Comments
//-------------------------------------------------------------------
// * [3911] Cel Damage                       |   100%    | Contain full library.
// * [4034] Dark Summit                      |   100%    | have 3/10 library.
// * [4039] New Legends                      |   100%    | have 6/10 library.
// * [4134] Double-S.T.E.A.L                 |   100%    | have 9/10 library.
// * [4242] Legends of Wrestling             |   100%    | have 4/10 library.
// * [4361] Umezawa Yukari no Igo Seminar    |   100%    | have 6/11 library.
// * [4432] Sega Soccer Slam                 |   100%    | have 9/11 library.
// * [4531] NHL HITZ 2003                    |   100%    | have 9/11 library.
// * [4627] Rayman Arena                     |   100%    | have 6/11 library.
// * [4721] Terminator - Dawn of Fate        |   100%    | have 10/11 library.
// * [4831] Whacked                          |   100%    | have 9/11 library.
// * [4928] Drihoo                           |   100%    | have 8/11 library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | have 5/11 library.
// * [5120] N.U.D.E.@                        |   100%    | have 8/11 library.
// * [5233] Rayman 3                         |   100%    | have 8/11 library.
// * [5344] Starsky & Hutch                  |   100%    | have 8/11 library.
// * [5455] Dinosaur Hunting                 |   100%    | have 10/11 library.
// * [5558] XIII                             |   100%    | have 9/11 library.
// * [5659] LMA Manager 2004                 |   100%    | have 9/11 library.
// * [5788] All-Star Baseball 2005           |   100%    | have 9/11 library.
// * [5849] Nickelodeon Tak 2                |   100%    | have 9/11 library.

// TODO: Known Xgraphics OOVPA issue list
// * 3911 XGCompressRect is XREF in v1 database, any reason for this?
// * Verification needed: Function Name ( Revision )
//   * XFONT_OpenBitmapFontFromMemory (4432, 4531, 4831, 5120)
//   * XGCompressRect (4034, 4242, 4721, 5028, 5120)
//   * XGIsSwizzledFormat (4034)
//   * XGSetIndexBufferHeader (4034)
//   * XGSetTextureHeader (4034)
//   * XGSetVertexBufferHeader (4034)
//   * XGSwizzleBox (4242)
//   * XGUnswizzleBox (4034, 4134, 4242)
//   * XGWriteSurfaceOrTextureToXPR (4034, 4242, 5028)
// NOTE: Known Xgraphics OOVPA not included in initial revision.
//   * XFONT_OpenBitmapFontFromMemory (4361)

#ifndef XGRAPHC_OOVPA_INL
#define XGRAPHC_OOVPA_INL

#include "OOVPA.h"

#include "XGraphic/3911.inl"
#include "XGraphic/4134.inl"
#include "XGraphic/4361.inl"

// ******************************************************************
// * XGRAPHC_OOVPA
// ******************************************************************
OOVPATable XGRAPHC_OOVPA[] = {

    REGISTER_OOVPAS(XFONT_OpenBitmapFontFromMemory, 4361),
    REGISTER_OOVPAS(XGCompressRect, 3911), // TODO: Do we need to patch this?
    REGISTER_OOVPAS(XGIsSwizzledFormat, 3911),
    REGISTER_OOVPAS(XGSetIndexBufferHeader, 3911, 4134),
    REGISTER_OOVPAS(XGSetSurfaceHeader, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XGSetTextureHeader, 3911),
    REGISTER_OOVPAS(XGSetVertexBufferHeader, 3911, 4134),
    REGISTER_OOVPAS(XGSwizzleBox, 3911),
    REGISTER_OOVPAS(XGSwizzleRect, 3911),
    REGISTER_OOVPAS(XGUnswizzleBox, 3911),
    REGISTER_OOVPAS(XGUnswizzleRect, 3911),
    REGISTER_OOVPAS(XGWriteSurfaceOrTextureToXPR, 3911),
};

// ******************************************************************
// * XGRAPHC_OOVPA_COUNT
// ******************************************************************
#define XGRAPHC_OOVPA_COUNT XBSDB_ARRAY_SIZE(XGRAPHC_OOVPA)

#endif

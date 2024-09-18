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

    REGISTER_OOVPAS(SYM_FUN(XFONT_OpenBitmapFontFromMemory, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pFontData), PARAM(stk, uFontDataSize), PARAM(stk, ppFont))),
                    SYM_SIG(4361)),
    REGISTER_OOVPAS(SYM_FUN(XGCompressRect, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pDestBuf), PARAM(stk, DestFormat), PARAM(stk, DestPitch), PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, pSrcData), PARAM(stk, SrcFormat), PARAM(stk, SrcPitch), PARAM(stk, fAlphaRef), PARAM(stk, Flags))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGIsSwizzledFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, Format))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGSetIndexBufferHeader, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, Length), PARAM(stk, Usage), PARAM(stk, Format), PARAM(stk, Pool), PARAM(stk, pBuffer), PARAM(stk, Data))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(XGSetSurfaceHeader, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Format), PARAM(stk, pSurface), PARAM(stk, Data), PARAM(stk, Pitch))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(XGSetTextureHeader, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Levels), PARAM(stk, Usage), PARAM(stk, Format), PARAM(stk, Pool), PARAM(stk, pTexture), PARAM(stk, Data), PARAM(stk, Pitch))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGSetVertexBufferHeader, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, Length), PARAM(stk, Usage), PARAM(stk, FVF), PARAM(stk, Pool), PARAM(stk, pBuffer), PARAM(stk, Data))),
                    SYM_SIG(3911, 4134)),
    REGISTER_OOVPAS(SYM_FUN(XGSwizzleBox, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pSource), PARAM(stk, RowPitch), PARAM(stk, SlicePitch), PARAM(stk, pBox), PARAM(stk, pDest), PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Depth), PARAM(stk, pPoint), PARAM(stk, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGSwizzleRect, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pSource), PARAM(stk, Pitch), PARAM(stk, pRect), PARAM(stk, pDest), PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, pPoint), PARAM(stk, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGUnswizzleBox, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pSource), PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, Depth), PARAM(stk, pBox), PARAM(stk, pDest), PARAM(stk, RowPitch), PARAM(stk, SlicePitch), PARAM(stk, pPoint), PARAM(stk, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGUnswizzleRect, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pSource), PARAM(stk, Width), PARAM(stk, Height), PARAM(stk, pRect), PARAM(stk, pDest), PARAM(stk, Pitch), PARAM(stk, pPoint), PARAM(stk, BytesPerPixel))),
                    SYM_SIG(3911)),
    REGISTER_OOVPAS(SYM_FUN(XGWriteSurfaceOrTextureToXPR, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pResource), PARAM(stk, cPath), PARAM(stk, bWriteSurfaceAsTexture))),
                    SYM_SIG(3911)),
};

// ******************************************************************
// * XGRAPHC_OOVPA_COUNT
// ******************************************************************
#define XGRAPHC_OOVPA_COUNT XBSDB_ARRAY_SIZE(XGRAPHC_OOVPA)

#endif

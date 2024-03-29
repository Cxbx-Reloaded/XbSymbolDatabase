// ******************************************************************
// *
// *   OOVPADatabase->XOnline_OOVPA.inl
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

// Titles which did compiled with full library version
//   [LibV] Title Name                        | Verify  |   Comments
//-------------------------------------------------------------------
// * [4831] NBA2K3                            |  100%   | Contain full library.
// * [4831] Whacked Demo                      |  100%   | Contain full library.
// * [4928] Unreal Championship               |  100%   | Contain full library.
// * [5028] Capcom vs. SNK 2 EO               |  100%   | Contain full library.
// * [5120] Muzzle Flash                      |  100%   | have 11/14 library.
// * [5233] MotoGP 2                          |  100%   | have 11/14 library.
// * [5344] Burnout 2                         |  100%   | have 11/14 library.
// * [5344] Wolfentein                        |  100%   | May contain full library.
// * [5455] Ghost Recon Island Thunder        |  100%   | Contain full library.
// * [5558] XIII                              |  100%   | Contain full library.
// * [5659] Crimson Skies                     |  100%   | Contain full library.
// * [5659] Plus Plum 2                       |  100%   | Contain full library.
// * [5788] All-Star Baseball '05             |  100%   | Contain full library.
// * [5788] Splinter Cell: Pandora Tomorrow   |  100%   | Contain full library.
// * [5849] Call of Duty Finest Hour          |  100%   | Contain full library.
// * [5849] Kingdom Under Fire: The Crusaders |  100%   | Contain full library.
// * [5849] Splinter Cell: Chaos Theory       |  100%   | Contain full library.

// TODO: Known XOnlines OOVPA issue list
// * Following OOVPA revision are not verified
//   * listen (5120, 5233)
//   * recv (5120, 5233)
//   * send (5120, 5233)

#ifndef XONLINES_OOVPA_INL
#define XONLINES_OOVPA_INL

#include "OOVPA.h"

#include "XOnline/4361.inl"
#include "XOnline/4627.inl"
#include "XOnline/4721.inl"
#include "XOnline/5028.inl"
#include "XOnline/5233.inl"
#include "XOnline/5455.inl"
#include "XOnline/5558.inl"
#include "XOnline/5659.inl"
#include "XOnline/5788.inl"
#include "XOnline/5849.inl"

// ******************************************************************
// * XONLINE_OOVPA
// ******************************************************************
OOVPATable XONLINE_OOVPA[] = {

    // XOnline section
    REGISTER_OOVPAS(CXo_XOnlineLogon, 4361, 4627, 4721, 5455, 5558, 5849),
    REGISTER_OOVPAS(XOnlineLogon, 4361),
    REGISTER_OOVPAS(CXo_XOnlineMatchSearch, 4721),
    REGISTER_OOVPAS(XOnlineMatchSearch, 4721),
    REGISTER_OOVPAS(CXo_XOnlineMatchSearchResultsLen, 4721),
    REGISTER_OOVPAS(XOnlineMatchSearchResultsLen, 4721),
    REGISTER_OOVPAS(CXo_XOnlineMatchSearchGetResults, 4721),
    REGISTER_OOVPAS(XOnlineMatchSearchGetResults, 4721),
    REGISTER_OOVPAS(CXo_XOnlineMatchSessionUpdate, 4721, 5233),
    REGISTER_OOVPAS(XOnlineMatchSessionUpdate, 4721),
    REGISTER_OOVPAS(CXo_XOnlineMatchSessionCreate, 4721, 5849),
    REGISTER_OOVPAS(XOnlineMatchSessionCreate, 4721),
    REGISTER_OOVPAS(XoUpdateLaunchNewImageInternal, 4627, 5659, 5788),
};

// ******************************************************************
// * XONLINE_OOVPA_COUNT
// ******************************************************************
#define XONLINE_OOVPA_COUNT XBSDB_ARRAY_SIZE(XONLINE_OOVPA)

#endif

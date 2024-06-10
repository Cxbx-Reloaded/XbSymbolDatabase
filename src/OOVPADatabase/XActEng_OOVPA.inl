// ******************************************************************
// *
// *   OOVPADatabase->XActEng_OOVPA.inl
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
//   [LibV] Title Name                       |  Verify   |   Comments
//-----------------------------------------------------------------------
// * [4928] Lord of the Rings The Two Towers |   100%    | have 16/21 library.
// * [5028] ???                              |     0%    | revision 5028 is obscure.
// * [5120] Super Bubble Pop                 |   100%    | have 14/21 library.
// * [5233] Cyber Attack Team                |   100%    | have 16/21 library.
// * [5344] Syberia                          |   100%    | have 20/23 library.
// * [5455] IndyCar Series                   |   100%    | have 12/23 library.
// * [5558] Top Spin                         |   100%    | have 20/24 library.
// * [5659] Ghoulies Demo                    |   100%    | have 18/24 library.
// * [5788] Steel Battalion                  |   100%    | have 20/24 library.
// * [5849] Forza Motorsport                 |   100%    | have 20/24 library.

// TODO: Known XactEng OOVPA issue list
// * 4627 and 5028 are not verified each OOVPA. (Last known revision found is 4928. revision 5028 is obscure)
// * Verification needed: Function Name ( Revision )
//   * XACT_CEngine_CreateSoundSource (5455)
//   * XACT_CEngine_DownloadEffectsImage (4928, 5120, 5233, 5455)
//   * XACT_CEngine_RegisterWaveBank (4928, 5455)
//   * XACT_CSoundBank_GetSoundCueIndexFromFriendlyName (5455)
//   * XACT_CSoundBank_Play (5455)
//   * IXACTEngine_CreateSoundSource (5455)
//   * IXACTEngine_DownloadEffectsImage (4928, 5120, 5233, 5455)
//   * IXACTEngine_RegisterWaveBank (4928, 5455)
//   * IXACTSoundBank_GetSoundCueIndexFromFriendlyName (5455)
//   * IXACTSoundBank_PlayEx (5455)
//   * IXACTSoundBank_Play (4928 to 5849)

#ifndef XACTENG_OOVPA_INL
#define XACTENG_OOVPA_INL

#include "OOVPA.h"

#include "XActEng/4627.inl"
#include "XActEng/4928.inl"
#include "XActEng/5120.inl"
#include "XActEng/5233.inl"
#include "XActEng/5344.inl"
#include "XActEng/5558.inl"


// ******************************************************************
// * XACTENG_OOVPA
// ******************************************************************
OOVPATable XACTENG_OOVPA[] = {

    REGISTER_OOVPAS(SYM_FUN(XACTEngineCreate, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928, 5120)),
    REGISTER_OOVPAS(SYM_FUN(XACTEngineDoWork, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_CreateSoundBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_CreateSoundSource, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_DownloadEffectsImage, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5344)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_GetNotification, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_RegisterNotification, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_RegisterStreamedWaveBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928, 5233)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_RegisterWaveBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5120, 5233)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CEngine_UnRegisterWaveBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928, 5120)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CSoundBank_GetSoundCueIndexFromFriendlyName, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(XACT_CSoundBank_Play, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(5344, 5558)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_CreateSoundBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_CreateSoundSource, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_DownloadEffectsImage, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5344)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_GetNotification, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_RegisterNotification, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_RegisterStreamedWaveBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_RegisterWaveBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 5120)),
    REGISTER_OOVPAS(SYM_FUN(IXACTEngine_UnRegisterWaveBank, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTSoundBank_GetSoundCueIndexFromFriendlyName, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627, 4928)),
    REGISTER_OOVPAS(SYM_FUN(IXACTSoundBank_Play, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(4627)),
    REGISTER_OOVPAS(SYM_FUN(IXACTSoundBank_PlayEx, STACK(/*default*/), PARAMS(/*unknown*/)),
                    SYM_SIG(5344)), // Not Implemented yet.
};

// ******************************************************************
// * XACTENG_OOVPA_COUNT
// ******************************************************************
#define XACTENG_OOVPA_COUNT XBSDB_ARRAY_SIZE(XACTENG_OOVPA)

#endif

// ******************************************************************
// *
// *   OOVPADatabase->DSound_OOVPA.inl
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
// *  (c) 2017-2019 RadWolfie
// *  (c) 2017 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// Titles which did compiled with full library version
//   [LibV] Title Name                       |  Verify   |   Comments
//-------------------------------------------------------------------
// * [3925] Cel Damage                       |   100%    | Contain full library.
// * [3936] Silent Hill 2                    |   100%    | Contain 99% library.**
// * [4039] Nightcaster                      |   100%    | Only has 90% of the library compiled with xbe build.
// * [4039] Azurik PAL                       |   100%    | Contain full library.
// * [4134] RaceX (Demo)                     |     -%    | Only has a few library.
// * [4134] Blood Omen 2                     |    80%    | Does not have full library.
// * [4134] JSRF                             |     1%    | Does not have Stream class. DS and Buffer might be full.
// * [4134] Double-S.T.E.A.L                 |   100%    | Contain full library.
// * [4242] NFL Blitz 2002                   |   100%    | Contain full library.
// * [4361] Flight Academy                   |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4432] RedCard 2003                     |   100%    | Contain full library.
// * [4432] Madden NFL 2003                  |   100%    | Contain full library.
// * [4627] MLB SlugFest 2003                |   100%    | Contain full library.
// * [4721] Terminator Dawn of Fate          |   100%    | Contain full library.
// * [4831] Whacked!                         |   100%    | Contain full library.
// * [4928] Drihoo                           |   100%    | Contain full library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | Contain full library.
// * [5120] N.U.D.E.@                        |   100%    | Contain full library.
// * [5233] Evil Dead                        |   100%    | Contain full library.
// * [5344] Gladius OXM Demo Disc 20         |   100%    | Contain full library.
// * [5344] The Hulk                         |   100%    | Contain full library.
// * [5455] NCAA Football 2004               |   100%    | Contain full library.
// * [5455] Dinosaur Hunting                 |   100%    | Contain full library.
// * [5558] Dino Crisis 3                    |   100%    | Contain full library.
// * [5659] Midway Arcade Treasures Paperboy |   100%    | Contain full library.
// * [5788] Digimon Battle Chronicle         |   100%    | Contain full library.
// * [5788] Splinter Cell: Pandora Tomorrow  |   100%    | Contain full library.
// * [5849] Nickelodeon Tak 2                |   100%    | Contain full library.
// * [5849] Def Jam Fight for NY             |   100%    | Contain full library.

// Note records:
// ** Did not compile with XFileCreateMediaObject and XWaveFileCreateMediaObject
//   * Might need further investigation.


// TODO: Known DSound OOVPA issue list
// * 3911 to 5933: Cannot make OOVPAs
//   * IDirectSound_SetCooperativeLevel     (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSound_Compact                 (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSoundBuffer_Restore           (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSoundBuffer_Unlock            (Xbox doesn't use it, however can make OOVPA; NOTE: OOVPA is registered for it)
//   * IDirectSoundStream_AddRef            (Using IUnknown_AddRef)
//   * IDirectSoundStream_Release           (Using IUnknown_Release)
// * 3911 to ????: These functions does not exist until newer XDK revision
//   * IDirectSoundBuffer_Pause                 (Lowest found was 4721)
//   * IDirectSoundBuffer_PauseEx               (Lowest found was 4721)
//   * IDirectSoundStream_FlushEx               (Lowest found was 4134)
//   * DirectSoundDumpMemoryUsage               (Lowest found was 4361)
//   * DirectSoundGetSampleTime                 (Need verify in 4134)
//   * XGetAudioFlags                           (Lowest found was 3911, XAudioGetSpeakerConfig introduced later as alias, is part of Xapi section)
//   * XAudioSetEffectData                      (Lowest found was 5120, likely lowest found will be in 5028)
//     * Except newer segaboot report to have full except for XAudioSetEffectData is not include.
// * 3911 to 3936: Following separater functions has exact asm codes as whole function are...
//   * IDirectSoundStream_SetVolume     & CDirectSoundStream_SetVolume
//   * IDirectSoundStream_SetPitch      & CDirectSoundStream_SetPitch
//   * IDirectSoundStream_SetLFO        & CDirectSoundStream_SetLFO
//   * IDirectSoundStream_SetEG         & CDirectSoundStream_SetEG
//   * IDirectSoundStream_SetFilter     & CDirectSoundStream_SetFilter
//   * IDirectSoundStream_SetHeadroom   & CDirectSoundStream_SetHeadroom
//   * IDirectSoundStream_SetFrequency  & CDirectSoundStream_SetFrequency
//   * IDirectSoundStream_SetMixBins    & CDirectSoundStream_SetMixBins
// * 3911 - Not part of API, yet is a non-member function : (might be useful)
//   * GetFormatSize
//   * CopyFormat
//   * CompareFormats
//   * CalculateXboxAdpcmAlignment
//   * IsValidPcmFormat
//   * IsValidXboxAdpcmFormat
//   * CopyFormatAlloc
// * List of functions might need to be register:
//   * IDirectSoundBuffer_QueryInterface
//   * IDirectSoundBuffer_QueryInterfaceC
// * List of internal functions are not register:
//   * CDirectSoundBuffer_Release   (Is unique, however need multiple OOVPAs to register all revisions)
//     * Using XREF_DSound_CRefCount_Release
//   * CDirectSound_Release         (Is unique, however need multiple OOVPAs to register all revisions)
//     * Using XREF_DSound_CRefCount_Release
// * 4039 verification needed:
//   * DirectSoundUseLightHRTF
//   * CDirectSoundStream_SetRolloffCurve (IDirectSoundStream_SetRolloffCurve is a jmp)
//   * CDirectSoundStream_SetRolloffFactor
// * 4134 verification needed: (Verifying with Double-S.T.E.A.L title is done, need different title to find the remaining...)
//   * DirectSoundUseLightHRTF
//   * XAudioCreateAdpcmFormat
// * 4039 CDirectSoundVoice_SetPitch need to be strengthen by using XREF to CMcpxVoiceClient_SetPitch function.
// * List of OOVPAs may could be lower to include support older titles.
//   * CDirectSoundVoice_SetI3DL2Source (5344)
//   * CDirectSound_SetDopplerFactor (5344)
//   * CDirectSound_SetRolloffFactor (5344)
//   * CDirectSound_SetDistanceFactor (5344)
//   * CDirectSound_SetI3DL2Listener (5344)
//   * CMcpxBuffer_Pause_Ex (4721)
//   * IDirectSoundBuffer_PauseEx (4721)
//   * CDirectSoundBuffer_PauseEx (4721)
// * Missing OOVPAs
//   * DirectSoundUseLightHRTF (4134)
//   * CHRTFSource_SetLightHRTF5Channel (4134)
//   * XAudioCreateAdpcmFormat (4134)
//   * XFileCreateMediaObject (3936 - 4134)
//     * Somehow is excluded?
//   * XWaveFileCreateMediaObject (3936 - 4134)
//     * Somehow is excluded?
// * 4134 & 4361 CDirectSoundVoice_SetMaxDistance + CDirectSoundVoice_SetMinDistance
//   * With XREF, RadWolfie think is possible to remove 0x1F offset for ability to remove 4361 OOVPAs.
// * 4039 (TODO)
//   * CDirectSoundVoice_SetI3DL2Source, need to reduce pairs and at least use an XREF.
//     * Most likely has a call to CDirectSoundVoice_CommitDeferredSettings.
//   * CDirectSoundVoice_SetMixBins
//     * Maybe able to reduce pairs and include another XREF.
//   * CDirectSoundVoice_SetMixBinVolumes
//     * Should be able to reduce pairs since there are two XREFs.
// * (TODO) CDirectSoundBuffer_SetNotificationPositions, add XREF supports.


#ifndef DSOUND_OOVPA_INL
#define DSOUND_OOVPA_INL

#include "OOVPA.h"

#include "DSound/3911.inl"
#include "DSound/3936.inl"
#include "DSound/4039.inl"
#include "DSound/4134.inl"
#include "DSound/4242.inl"
#include "DSound/4361.inl"
#include "DSound/4432.inl"
#include "DSound/4531.inl"
#include "DSound/4627.inl"
#include "DSound/4721.inl"
#include "DSound/4831.inl"
#include "DSound/5028.inl"
#include "DSound/5344.inl"
#include "DSound/5455.inl"
#include "DSound/5558.inl"

// ******************************************************************
// * DSOUND_OOVPA_manual
// ******************************************************************
OOVPATable DSound_OOVPA_manual[] = {

    // Without xrefs dependency
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_AddRef, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature // NOTE: The function and CAc97MediaObject::AddRef are the same asm code.
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Discontinuity, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Flush, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_GetInfo, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInfo))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_GetStatus, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwStatus))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Process, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInputBuffer), PARAM(stk, pOutputBuffer))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Release, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Constructor, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdssd))),
                      SYM_SIG(3911)), // NOTE: Does not need to be register in db. Using manual work instead, like D3D8 did.
};
#define DSound_OOVPA_manual_COUNT XBSDB_ARRAY_SIZE(DSound_OOVPA_manual)

// ******************************************************************
// * DSOUND_OOVPA
// ******************************************************************
OOVPATable DSound_OOVPA[] = {

    REGISTER_OOVPAS(SYM_FUN(XAudioCalculatePitch, STACK(/*default*/), PARAMS(PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundEnterCriticalSection, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(DSound_CRefCount_AddRef, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DSound_CRefCount_Release, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911, 4039, 5455)), // Final generic OOVPA: 5455; Removed: 0

    REGISTER_OOVPAS(SYM_FUN(DSound_CMemoryManager_PoolAlloc, STACK(/*default*/), PARAMS(PARAM(stk, PoolTag), PARAM(stk, Size), PARAM(stk, ZeroInitialize))),
                    SYM_SIG(4134, 4361)), // For reference purpose only, does not have XREF value.

    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Commit3dSettings, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_ServiceDeferredCommandsLow, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4134, 5455)), // Final generic OOVPA: 5455; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dDistanceFactor, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, fDistanceFactor), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dDopplerFactor, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, fDopplerFactor), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dParameters, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pDS3DListenerParameters), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dPosition, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pPosition), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dRolloffFactor, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, fRolloffFactor), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dVelocity, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pVelocity), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetI3DL2Listener, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pds3dl), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetMixBinHeadroom, STACK(8), PARAMS(PARAM(ecx, this), PARAM(stk, dwMixBinMask), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetMixBinHeadroom, STACK(4), PARAMS(PARAM(ecx, this), PARAM(stk, dwMixBinMask))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SynchPlayback, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4831) // thiscall

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_Calculate3D, STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetMixBinVolumes, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, pUnknown3))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetPanData, STACK(/*default*/), PARAMS(PARAM(stk, flUnknown1), PARAM(stk, flUnknown2), PARAM(stk, unknown3), PARAM(stk, pflUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2), PARAM(stk, pUnknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_GetVoiceProperties, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dConeOrientation, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pConeOrientation), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dConeOutsideVolume, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, lConeOutsideVolume), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMaxDistance, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, flMaxDistance), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMinDistance, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, flMinDistance), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMode, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwMode), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dPosition, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pPosition), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dVelocity, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pVelocity), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetEG, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetFilter, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetI3DL2Source, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pds3db), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetLFO, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetMixBins, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetPitch, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetVolume, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Commit3dSettings, STACK(4), PARAMS(PARAM(ecx, this), PARAM(stk, dwParamMask))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall // NOTE: Must be after CMcpxVoiceClient_SetVolume for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Commit3dSettings, STACK(0), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(4039, 4134, 4242, 4627, 5028, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0 // thiscall // NOTE: Must be after CMcpxVoiceClient_SetVolume for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dParameters, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pc3DBufferParameters), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall // NOTE: Must be after CMcpxVoiceClient_Commit3dSettings for one time scan.

    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoiceSettings_SetMixBinVolumes, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039) // thiscall

    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_CommitDeferredSettings, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_GetVoiceProperties, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_Set3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeAngles, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeOrientation, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeOutsideVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134, 4361, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134, 4361, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetEG, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFilter, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFormat, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039, 4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetI3DL2Source, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetLFO, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMaxDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMinDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBins, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBinVolumes, STACK(12), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBinVolumes, STACK(8), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMode, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetOutputBuffer, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetPitch, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFrequency, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0 // NOTE: Must be after CDirectSoundVoice_SetPitch for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetRolloffCurve, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0 // s+ (from 4134's comment)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_Use3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBufferSettings_SetBufferData, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall

    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_GetCurrentPosition, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdwCurrentPlayCursor), PARAM(stk, pdwCurrentWriteCursor))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_GetStatus, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdwStatus))),
                    SYM_SIG(3911, 4039, 4134, 4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Pause, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwPause))),
                    SYM_SIG(4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4721) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Pause_Ex, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Play, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134, 4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Play_Ex, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_SetBufferData, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_SetCurrentPosition, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwNewPosition))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Stop, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Stop_Ex, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134) // thiscall

    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Stop, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwFlags))),
                    SYM_SIG(4134, 5028)), // Final generic OOVPA: 5233?; Removed: 0 (introduced in 4134) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Stop_Ex, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Flush, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 3936, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Discontinuity, STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134, 4531, 5455)), // thiscall // NOTE: Must be after CMcpxStream_Flush for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_GetStatus, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdwStatus))),
                    SYM_SIG(4134, 4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4134) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Pause, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwPause))),
                    SYM_SIG(3911, 4039, 4134, 4831)), // Final generic OOVPA: 4831; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Pause_Ex, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361) // thiscall

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetCurrentPosition, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdwCurrentPlayCursor), PARAM(stk, pdwCurrentWriteCursor))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetStatus, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdwStatus))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetVoiceProperties, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Lock, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwOffset), PARAM(stk, dwBytes), PARAM(stk, ppvAudioPtr1), PARAM(stk, pdwAudioBytes1), PARAM(stk, ppvAudioPtr2), PARAM(stk, pdwAudioBytes2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Pause, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_PauseEx, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_PlayEx, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Play, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwReserved1), PARAM(stk, dwReserved2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: Must be after CDirectSoundBuffer_PlayEx for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Set3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetBufferData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeAngles, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeOrientation, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeOutsideVolume, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetCurrentPosition, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwNewPosition))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetEG, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFilter, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFormat, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFrequency, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetI3DL2Source, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetLFO, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetLoopRegion, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwLoopStart), PARAM(stk, dwLoopLength))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMaxDistance, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMinDistance, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBins, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, mixBins))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBinVolumes, STACK(12), PARAMS(PARAM(stk, this), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBinVolumes, STACK(8), PARAMS(PARAM(stk, this), PARAM(stk, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMode, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetNotificationPositions, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwNotifyCount), PARAM(stk, paNotifies))),
                    SYM_SIG(3911, 4039, 4242)), // Uncommenting these fixes dashboard 4920 (from 4627 comment)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetOutputBuffer, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPitch, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPlayRegion, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwPlayStart), PARAM(stk, dwPlayLength))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetRolloffCurve, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetVolume, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_StopEx, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Stop, STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: Must be after CDirectSoundBuffer_StopEx for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Use3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pUnknown2))),
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

#if 0
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Constructor, STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdssd))),
                      SYM_SIG(3911)), // NOTE: Does not need to be register in db. Using manual work instead, like D3D8 did.
#endif
#if 0 // These signatures are no longer in use, yet preserved as documented signatures for future research usage. \
    //   Instead of these signatures below, using CDirectSoundStream_Constructor signature plus manual work allow us to reduce the scan process.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_AddRef, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: The function and CAc97MediaObject::AddRef are the same asm code.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Discontinuity, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Flush, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134, 5028)), // Final generic OOVPA: 5028; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetInfo, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInfo))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetStatus, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwStatus))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Process, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInputBuffer), PARAM(stk, pOutputBuffer))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Release, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
#endif
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_FlushEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetVoiceProperties, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Pause, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPause))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_PauseEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Set3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeAngles, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeOrientation, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeOutsideVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetEG, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFilter, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFormat, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFrequency, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetI3DL2Source, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetLFO, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMaxDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMinDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBins, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBinVolumes_12, STACK(/*embed*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in XDK 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBinVolumes_8, STACK(/*embed*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // Then it has changed in XDK 4039 and newer.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMode, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetOutputBuffer, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetPitch, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetRolloffCurve, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Use3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CommitDeferredSettings, STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(3911, 4039, 4134, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CommitEffectData, STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CreateSoundBuffer, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdsbd), PARAM(stk, ppBuffer), PARAM(stk, pUnused4))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CreateSoundStream, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdssd), PARAM(stk, ppStream), PARAM(stk, pUnused4))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_DownloadEffectsImage, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pvImageBuffer), PARAM(stk, dwImageSize), PARAM(stk, pImageLoc), PARAM(stk, ppImageDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_DoWork, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_EnableHeadphones, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fEnabled))),
                    SYM_SIG(3911, 4039, 4134, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetCaps, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pDSCaps))),
                    SYM_SIG(3911, 4039, 4134, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetEffectData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetOutputLevels, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pOutputLevels), PARAM(stk, bResetPeakValues))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetSpeakerConfig, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdwSpeakerConfig))),
                    SYM_SIG(3911, 4242, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetTime, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, prtCurrent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_MapBufferData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes), PARAM(stk, ppUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pDS3DListenerParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetEffectData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetI3DL2Listener, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pds3dl), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetMixBinHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwMixBinMask), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetOrientation, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, xFront), PARAM(stk, yFront), PARAM(stk, zFront), PARAM(stk, xTop), PARAM(stk, yTop), PARAM(stk, zTop), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SynchPlayback, STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(4831, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4831)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_UnmapBufferData, STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_Calculate3D, STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetMixBinVolumes, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, pUnknown3))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetPanData, STACK(/*default*/), PARAMS(PARAM(stk, flUnknown1), PARAM(stk, flUnknown2), PARAM(stk, unknown3), PARAM(stk, pflUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2), PARAM(stk, pUnknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_AddRef, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetCurrentPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwCurrentPlayCursor), PARAM(stk, pdwCurrentWriteCursor))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetStatus, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwStatus))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetVoiceProperties, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Lock, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwOffset), PARAM(stk, dwBytes), PARAM(stk, ppvAudioPtr1), PARAM(stk, pdwAudioBytes1), PARAM(stk, ppvAudioPtr2), PARAM(stk, pdwAudioBytes2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Pause, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_PauseEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Play, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwReserved1), PARAM(stk, dwReserved2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_PlayEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Release, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Restore, STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Set3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5455)), // undocument // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetBufferData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeAngles, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeOrientation, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeOutsideVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetCurrentPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwNewPosition))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetEG, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFilter, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFormat, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFrequency, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetI3DL2Source, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetLFO, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetLoopRegion, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwLoopStart), PARAM(stk, dwLoopLength))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMaxDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMinDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBins, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, mixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBinVolumes, STACK(12), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBinVolumes, STACK(8), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // Then it has changed in 4039 and higher.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMode, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetNotificationPositions, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwNotifyCount), PARAM(stk, paNotifies))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetOutputBuffer, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPitch, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPlayRegion, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPlayStart), PARAM(stk, dwPlayLength))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetRolloffCurve, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Stop, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_StopEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Unlock, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, ppvAudioPtr1), PARAM(stk, pdwAudioBytes1), PARAM(stk, ppvAudioPtr2), PARAM(stk, pdwAudioBytes2))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Use3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // undocument // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_GetVoiceProperties, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_FlushEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Pause, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPause))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_PauseEx, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Set3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeAngles, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeOrientation, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeOutsideVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetEG, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetLFO, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFilter, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFormat, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFrequency, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetI3DL2Source, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMaxDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMinDistance, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBins, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBinVolumes, STACK(12), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBinVolumes, STACK(8), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // Then it has changed in 4039 and higher.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMode, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetOutputBuffer, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetPitch, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetRolloffCurve, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetVolume, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Use3DVoiceData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // jmp only // Final generic OOVPA: 5558 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(IDirectSound_AddRef, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CommitDeferredSettings, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CommitEffectData, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSound_Compact, STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CreateSoundBuffer, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdsbd), PARAM(stk, ppBuffer), PARAM(stk, pUnused4))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CreateSoundStream, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdssd), PARAM(stk, ppStream), PARAM(stk, pUnused4))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_DownloadEffectsImage, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pvImageBuffer), PARAM(stk, dwImageSize), PARAM(stk, pImageLoc), PARAM(stk, ppImageDesc))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_EnableHeadphones, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fEnabled))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetCaps, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pDSCaps))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetEffectData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetOutputLevels, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputLevels), PARAM(stk, bResetPeakValues))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetSpeakerConfig, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwSpeakerConfig))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetTime, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, prtCurrent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_MapBufferData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes), PARAM(stk, ppUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_Release, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetAllParameters, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pDS3DListenerParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetCooperativeLevel, STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetDistanceFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetDopplerFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetEffectData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetI3DL2Listener, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3dl), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetMixBinHeadroom, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetOrientation, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, xFront), PARAM(stk, yFront), PARAM(stk, zFront), PARAM(stk, xTop), PARAM(stk, yTop), PARAM(stk, zTop), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetPosition, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetRolloffFactor, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetVelocity, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SynchPlayback, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4831)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_UnmapBufferData, STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(CSensaura3d_GetFullHRTFFilterPair, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911, 3936)), // Final generic OOVPA: 3936; Removed: 4134+ // NOTE: 4039 revert back to 3911
    REGISTER_OOVPAS(SYM_FUN(CSensaura3d_GetLiteHRTFFilterPair, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4134+
    REGISTER_OOVPAS(SYM_FUN(CFullHRTFSource_GetCenterVolume, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CLightHRTFSource_GetCenterVolume, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4039, /*4134,*/ 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetFullHRTF5Channel, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4039, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetLightHRTF5Channel, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4039, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetFullHRTF4Channel, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetLightHRTF4Channel, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CFullHrtfSource_GetHrtfFilterPair, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CLightHrtfSource_GetHrtfFilterPair, STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CHrtfSource_SetAlgorithm_FullHrtf, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CHrtfSource_SetAlgorithm_LightHrtf, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)

    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreate, STACK(/*default*/), PARAMS(PARAM(stk, pguidDeviceId), PARAM(stk, ppDirectSound), PARAM(stk, pUnused3))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreateBuffer, STACK(/*default*/), PARAMS(PARAM(stk, pdsbd), PARAM(stk, ppBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreateStream, STACK(/*default*/), PARAMS(PARAM(stk, pdssd), PARAM(stk, ppStream))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundDoWork, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundGetSampleTime, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundOverrideSpeakerConfig, STACK(/*default*/), PARAMS(PARAM(stk, dwSpeakerConfig))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseFullHRTF, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134, 4242 /*, 5344=revert to 4134*/)), // Final generic OOVPA: 5344 (revert to 4134); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseLightHRTF, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, /*4134?,*/ 4242, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseFullHRTF4Channel, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseLightHRTF4Channel, STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(IsValidFormat, STACK(/*default*/), PARAMS(PARAM(stk, pwfx))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 4361+ // NOTE: 4361+ is replace into a class function

    REGISTER_OOVPAS(SYM_FUN(XAudioDownloadEffectsImage, STACK(/*default*/), PARAMS(PARAM(stk, pszImageName), PARAM(stk, pImageLoc), PARAM(stk, dwFlags), PARAM(stk, ppImageDesc))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(XAudioSetEffectData, STACK(/*default*/), PARAMS(PARAM(stk, dwEffectIndex), PARAM(stk, pDesc), PARAM(stk, pRawDesc))),
                    SYM_SIG(5028, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in ??5028 or 5120??)
    REGISTER_OOVPAS(SYM_FUN(XAudioCreatePcmFormat, STACK(/*default*/), PARAMS(PARAM(stk, nChannels), PARAM(stk, nSamplesPerSec), PARAM(stk, wBitsPerSample), PARAM(stk, pwfx))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: later revision changed to a jmp, and convert into class function
    REGISTER_OOVPAS(SYM_FUN(XAudioCreateAdpcmFormat, STACK(/*default*/), PARAMS(PARAM(stk, nChannels), PARAM(stk, nSamplesPerSec), PARAM(stk, pwfx))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0 // NOTE: later revision changed to a jmp, and convert into class function

    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObject, STACK(/*default*/), PARAMS(PARAM(stk, pszFileName), PARAM(stk, dwDesiredAccess), PARAM(stk, dwShareMode), PARAM(stk, dwCreationDisposition), PARAM(stk, dwFlagsAndAttributes), PARAM(stk, ppMediaObject))),
                    SYM_SIG(3911, 4242, 4361)), // TODO: Need investigation on 3936-4039
    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObjectAsync, STACK(/*default*/), PARAMS(PARAM(stk, hFile), PARAM(stk, dwMaxPackets), PARAM(stk, ppMediaObject))),
                    SYM_SIG(4432)), // TODO: Need investigation (confirmed does not exist in 4242)
    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObjectEx, STACK(/*default*/), PARAMS(PARAM(stk, hFile), PARAM(stk, ppMediaObject))),
                    SYM_SIG(4242, 4361)), // TODO: Need investigation on 3936-4039

    REGISTER_OOVPAS(SYM_FUN(XWaveFileCreateMediaObject, STACK(/*default*/), PARAMS(PARAM(stk, pszFileName), PARAM(stk, ppwfxFormat), PARAM(stk, ppMediaObject))),
                    SYM_SIG(3911, 4242, 4361)), // TODO: Need investigation on 3936-4039
    REGISTER_OOVPAS(SYM_FUN(XWaveFileCreateMediaObjectEx, STACK(/*default*/), PARAMS(PARAM(stk, pszFileName), PARAM(stk, hFile), PARAM(stk, ppMediaObject))),
                    SYM_SIG(4242, 4361)), // TODO: Need investigation on 3936?-4039
};

// ******************************************************************
// * DSound_OOVPA_COUNT
// ******************************************************************
#define DSound_OOVPA_COUNT XBSDB_ARRAY_SIZE(DSound_OOVPA)

#endif

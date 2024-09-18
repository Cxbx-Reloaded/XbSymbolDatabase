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
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_AddRef, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature // NOTE: The function and CAc97MediaObject::AddRef are the same asm code.
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Discontinuity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Flush, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_GetInfo, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInfo))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_GetStatus, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwStatus))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Process, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInputBuffer), PARAM(stk, pOutputBuffer))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Release, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                      SYM_SIG(0)), // dummy signature
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Constructor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdssd))),
                      SYM_SIG(3911)), // NOTE: Does not need to be register in db. Using manual work instead, like D3D8 did.
};
#define DSound_OOVPA_manual_COUNT XBSDB_ARRAY_SIZE(DSound_OOVPA_manual)

// ******************************************************************
// * DSOUND_OOVPA
// ******************************************************************
OOVPATable DSound_OOVPA[] = {

    REGISTER_OOVPAS(SYM_FUN(XAudioCalculatePitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundEnterCriticalSection, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(DSound_CRefCount_AddRef, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DSound_CRefCount_Release, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911, 4039, 5455)), // Final generic OOVPA: 5455; Removed: 0

    REGISTER_OOVPAS(SYM_FUN(DSound_CMemoryManager_PoolAlloc, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, PoolTag), PARAM(stk, Size), PARAM(stk, ZeroInitialize))),
                    SYM_SIG(4134, 4361)), // For reference purpose only, does not have XREF value.

    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Commit3dSettings, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_ServiceDeferredCommandsLow, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4134, 5455)), // Final generic OOVPA: 5455; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, fDistanceFactor), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, fDopplerFactor), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pDS3DListenerParameters), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pPosition), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, fRolloffFactor), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_Set3dVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pVelocity), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetI3DL2Listener, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pds3dl), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetMixBinHeadroom, CALL(unk), STACK(8), PARAMS(PARAM(ecx, this), PARAM(stk, dwMixBinMask), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SetMixBinHeadroom, CALL(unk), STACK(4), PARAMS(PARAM(ecx, this), PARAM(stk, dwMixBinMask))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxAPU_SynchPlayback, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4831) // thiscall

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_Calculate3D, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetMixBinVolumes, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, pUnknown3))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetPanData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, flUnknown1), PARAM(stk, flUnknown2), PARAM(stk, unknown3), PARAM(stk, pflUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound3DCalculator_GetVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2), PARAM(stk, pUnknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_GetVoiceProperties, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dConeOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pConeOrientation), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dConeOutsideVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, lConeOutsideVolume), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMaxDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, flMaxDistance), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMinDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, flMinDistance), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dMode, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwMode), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pPosition), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pVelocity), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetEG, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetFilter, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetI3DL2Source, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pds3db), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetLFO, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetMixBins, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetPitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_SetVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Commit3dSettings, CALL(unk), STACK(4), PARAMS(PARAM(ecx, this), PARAM(stk, dwParamMask))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall // NOTE: Must be after CMcpxVoiceClient_SetVolume for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Commit3dSettings, CALL(unk), STACK(0), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(4039, 4134, 4242, 4627, 5028, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0 // thiscall // NOTE: Must be after CMcpxVoiceClient_SetVolume for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxVoiceClient_Set3dParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pc3DBufferParameters), PARAM(stk, bApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // thiscall // NOTE: Must be after CMcpxVoiceClient_Commit3dSettings for one time scan.

    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoiceSettings_SetMixBinVolumes, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039) // thiscall

    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_CommitDeferredSettings, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_GetVoiceProperties, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_Set3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeAngles, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetConeOutsideVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134, 4361, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134, 4361, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetEG, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFilter, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039, 4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetI3DL2Source, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetLFO, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMaxDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMinDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBins, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBinVolumes, CALL(unk), STACK(12), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMixBinVolumes, CALL(unk), STACK(8), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetMode, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetOutputBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetPitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetFrequency, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0 // NOTE: Must be after CDirectSoundVoice_SetPitch for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetRolloffCurve, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134, 4361, 5344)), // Final generic OOVPA: 5344; Removed: 0 // s+ (from 4134's comment)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_SetVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundVoice_Use3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBufferSettings_SetBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall

    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_GetCurrentPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdwCurrentPlayCursor), PARAM(stk, pdwCurrentWriteCursor))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_GetStatus, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdwStatus))),
                    SYM_SIG(3911, 4039, 4134, 4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Pause, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwPause))),
                    SYM_SIG(4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4721) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Pause_Ex, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Play, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134, 4721, 4831)), // Final generic OOVPA: 4831; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Play_Ex, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_SetBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_SetCurrentPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwNewPosition))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Stop, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4134, 4242)), // Final generic OOVPA: 4242; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxBuffer_Stop_Ex, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134) // thiscall

    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Stop, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwFlags))),
                    SYM_SIG(4134, 5028)), // Final generic OOVPA: 5233?; Removed: 0 (introduced in 4134) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Stop_Ex, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Flush, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 3936, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Discontinuity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this))),
                    SYM_SIG(3911, 4039, 4134, 4531, 5455)), // thiscall // NOTE: Must be after CMcpxStream_Flush for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_GetStatus, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdwStatus))),
                    SYM_SIG(4134, 4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4134) // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Pause, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, dwPause))),
                    SYM_SIG(3911, 4039, 4134, 4831)), // Final generic OOVPA: 4831; Removed: 0 // thiscall
    REGISTER_OOVPAS(SYM_FUN(CMcpxStream_Pause_Ex, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361) // thiscall

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetCurrentPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdwCurrentPlayCursor), PARAM(stk, pdwCurrentWriteCursor))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetStatus, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdwStatus))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_GetVoiceProperties, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Lock, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwOffset), PARAM(stk, dwBytes), PARAM(stk, ppvAudioPtr1), PARAM(stk, pdwAudioBytes1), PARAM(stk, ppvAudioPtr2), PARAM(stk, pdwAudioBytes2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Pause, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_PauseEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 4721; Removed: 0 (introduced in 4721)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_PlayEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Play, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwReserved1), PARAM(stk, dwReserved2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: Must be after CDirectSoundBuffer_PlayEx for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Set3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeAngles, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetConeOutsideVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetCurrentPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwNewPosition))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetEG, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFilter, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetFrequency, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetI3DL2Source, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetLFO, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetLoopRegion, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwLoopStart), PARAM(stk, dwLoopLength))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMaxDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMinDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, flMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBins, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, mixBins))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBinVolumes, CALL(unk), STACK(12), PARAMS(PARAM(stk, this), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMixBinVolumes, CALL(unk), STACK(8), PARAMS(PARAM(stk, this), PARAM(stk, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetMode, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetNotificationPositions, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwNotifyCount), PARAM(stk, paNotifies))),
                    SYM_SIG(3911, 4039, 4242)), // Uncommenting these fixes dashboard 4920 (from 4627 comment)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetOutputBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPlayRegion, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwPlayStart), PARAM(stk, dwPlayLength))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetRolloffCurve, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_SetVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_StopEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Stop, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: Must be after CDirectSoundBuffer_StopEx for one time scan.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundBuffer_Use3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pUnknown2))),
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

#if 0
    REGISTER_OOVPAS_M(SYM_FUN(CDirectSoundStream_Constructor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(ecx, this), PARAM(stk, pdssd))),
                      SYM_SIG(3911)), // NOTE: Does not need to be register in db. Using manual work instead, like D3D8 did.
#endif
#if 0 // These signatures are no longer in use, yet preserved as documented signatures for future research usage. \
    //   Instead of these signatures below, using CDirectSoundStream_Constructor signature plus manual work allow us to reduce the scan process.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_AddRef, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // NOTE: The function and CAc97MediaObject::AddRef are the same asm code.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Discontinuity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Flush, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134, 5028)), // Final generic OOVPA: 5028; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetInfo, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInfo))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetStatus, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwStatus))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Process, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pInputBuffer), PARAM(stk, pOutputBuffer))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Release, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                               SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
#endif
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_FlushEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_GetVoiceProperties, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Pause, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPause))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_PauseEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Set3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeAngles, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetConeOutsideVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetEG, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFilter, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetFrequency, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetI3DL2Source, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetLFO, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMaxDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMinDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBins, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBinVolumes_12, CALL(unk), STACK(/*embed*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in XDK 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMixBinVolumes_8, CALL(unk), STACK(/*embed*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 // Then it has changed in XDK 4039 and newer.
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetMode, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetOutputBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetPitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetRolloffCurve, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_SetVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSoundStream_Use3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CommitDeferredSettings, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(3911, 4039, 4134, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CommitEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CreateSoundBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdsbd), PARAM(stk, ppBuffer), PARAM(stk, pUnused4))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_CreateSoundStream, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdssd), PARAM(stk, ppStream), PARAM(stk, pUnused4))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_DownloadEffectsImage, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pvImageBuffer), PARAM(stk, dwImageSize), PARAM(stk, pImageLoc), PARAM(stk, ppImageDesc))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_DoWork, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_EnableHeadphones, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fEnabled))),
                    SYM_SIG(3911, 4039, 4134, 5344, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetCaps, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pDSCaps))),
                    SYM_SIG(3911, 4039, 4134, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetOutputLevels, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pOutputLevels), PARAM(stk, bResetPeakValues))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetSpeakerConfig, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pdwSpeakerConfig))),
                    SYM_SIG(3911, 4242, 5455)), // Final generic OOVPA: 5455; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_GetTime, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, prtCurrent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_MapBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes), PARAM(stk, ppUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pDS3DListenerParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetI3DL2Listener, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pds3dl), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetMixBinHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, dwMixBinMask), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, xFront), PARAM(stk, yFront), PARAM(stk, zFront), PARAM(stk, xTop), PARAM(stk, yTop), PARAM(stk, zTop), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039, 4134, 4627, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_SynchPlayback, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this))),
                    SYM_SIG(4831, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 4831)
    REGISTER_OOVPAS(SYM_FUN(CDirectSound_UnmapBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, this), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    //========================================================
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_Calculate3D, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetMixBinVolumes, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, pUnknown3))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetPanData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, flUnknown1), PARAM(stk, flUnknown2), PARAM(stk, unknown3), PARAM(stk, pflUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound3DCalculator_GetVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pUnknown1), PARAM(stk, pUnknown2), PARAM(stk, pUnknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_AddRef, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetCurrentPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwCurrentPlayCursor), PARAM(stk, pdwCurrentWriteCursor))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetStatus, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwStatus))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_GetVoiceProperties, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Lock, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwOffset), PARAM(stk, dwBytes), PARAM(stk, ppvAudioPtr1), PARAM(stk, pdwAudioBytes1), PARAM(stk, ppvAudioPtr2), PARAM(stk, pdwAudioBytes2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Pause, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_PauseEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4721)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Play, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwReserved1), PARAM(stk, dwReserved2), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_PlayEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Release, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Restore, CALL(unk), STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Set3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5455)), // undocument // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeAngles, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetConeOutsideVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetCurrentPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwNewPosition))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetEG, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFilter, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetFrequency, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetI3DL2Source, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetLFO, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetLoopRegion, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwLoopStart), PARAM(stk, dwLoopLength))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMaxDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMinDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBins, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, mixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBinVolumes, CALL(unk), STACK(12), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMixBinVolumes, CALL(unk), STACK(8), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // Then it has changed in 4039 and higher.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetMode, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetNotificationPositions, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwNotifyCount), PARAM(stk, paNotifies))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetOutputBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPlayRegion, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPlayStart), PARAM(stk, dwPlayLength))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetRolloffCurve, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_SetVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Stop, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_StopEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Unlock, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, ppvAudioPtr1), PARAM(stk, pdwAudioBytes1), PARAM(stk, ppvAudioPtr2), PARAM(stk, pdwAudioBytes2))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundBuffer_Use3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // undocument // Final generic OOVPA: 5558; Removed: 0 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_GetVoiceProperties, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pVoiceProps))),
                    SYM_SIG(5028)), // Final generic OOVPA: 5028; Removed: 0 (introduced in 5028) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_FlushEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwFlags))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Pause, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwPause))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_PauseEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk2, rtTimeStamp), PARAM(stk, dwPause))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Set3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, unknown2))),
                    SYM_SIG(5455)), // Final generic OOVPA: 5455; Removed: 0 (introduced in 5455) // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pc3DBufferParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeAngles, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwInsideConeAngle), PARAM(stk, dwOutsideConeAngle), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetConeOutsideVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lConeOutsideVolume), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // jmp only
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, flDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetEG, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pEnvelopeDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetLFO, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pLFODesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFilter, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pFilterDesc))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pwfxFormat))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetFrequency, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwFrequency))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetI3DL2Source, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3db), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMaxDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMaxDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMinDistance, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fMinDistance), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBins, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBinVolumes, CALL(unk), STACK(12), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, alVolumes))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4039+ // This revision is only used in 3911 to 3936.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMixBinVolumes, CALL(unk), STACK(8), PARAMS(PARAM(stk, pThis), PARAM(stk, pMixBins))),
                    SYM_SIG(4039)), // Final generic OOVPA: 4039; Removed: 0 // Then it has changed in 4039 and higher.
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetMode, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMode), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetOutputBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputBuffer))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetPitch, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lPitch))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetRolloffCurve, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pflPoints), PARAM(stk, dwPointCount), PARAM(stk, dwApply))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4134)
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_SetVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, lVolume))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSoundStream_Use3DVoiceData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5558)), // jmp only // Final generic OOVPA: 5558 (introduced in 5558)

    REGISTER_OOVPAS(SYM_FUN(IDirectSound_AddRef, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CommitDeferredSettings, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CommitEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSound_Compact, CALL(unk), STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CreateSoundBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdsbd), PARAM(stk, ppBuffer), PARAM(stk, pUnused4))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_CreateSoundStream, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdssd), PARAM(stk, ppStream), PARAM(stk, pUnused4))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_DownloadEffectsImage, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pvImageBuffer), PARAM(stk, dwImageSize), PARAM(stk, pImageLoc), PARAM(stk, ppImageDesc))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_EnableHeadphones, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fEnabled))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetCaps, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pDSCaps))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetOutputLevels, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pOutputLevels), PARAM(stk, bResetPeakValues))),
                    SYM_SIG(4361)), // Final generic OOVPA: 4361; Removed: 0 (introduced in 4361)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetSpeakerConfig, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pdwSpeakerConfig))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_GetTime, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, prtCurrent))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_MapBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pvBufferData), PARAM(stk, dwBufferBytes), PARAM(stk, ppUnknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_Release, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetAllParameters, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pDS3DListenerParameters), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    // REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetCooperativeLevel, CALL(unk), STACK(/*default*/), PARAMS(/*unknown*/)),
    //                 SYM_SIG(3911)), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetDistanceFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fDistanceFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetDopplerFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fDopplerFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwEffectIndex), PARAM(stk, dwOffset), PARAM(stk, pvData), PARAM(stk, dwDataSize), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetI3DL2Listener, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pds3dl), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetMixBinHeadroom, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, dwMixBinMask), PARAM(stk, dwHeadroom))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetOrientation, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, xFront), PARAM(stk, yFront), PARAM(stk, zFront), PARAM(stk, xTop), PARAM(stk, yTop), PARAM(stk, zTop), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetPosition, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetRolloffFactor, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, fRolloffFactor), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SetVelocity, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, x), PARAM(stk, y), PARAM(stk, z), PARAM(stk, dwApply))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_SynchPlayback, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4831)), // Final generic OOVPA: 4831; Removed: 0 (introduced in 4831)
    REGISTER_OOVPAS(SYM_FUN(IDirectSound_UnmapBufferData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis), PARAM(stk, pUnknown2))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(CSensaura3d_GetFullHRTFFilterPair, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911, 3936)), // Final generic OOVPA: 3936; Removed: 4134+ // NOTE: 4039 revert back to 3911
    REGISTER_OOVPAS(SYM_FUN(CSensaura3d_GetLiteHRTFFilterPair, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, pUnknown4), PARAM(stk, pUnknown5))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 4134+
    REGISTER_OOVPAS(SYM_FUN(CFullHRTFSource_GetCenterVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4039, 4134, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CLightHRTFSource_GetCenterVolume, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3), PARAM(stk, unknown4))), // TODO: Update unknown parameter name(s) if able.
                    SYM_SIG(4039, /*4134,*/ 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetFullHRTF5Channel, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4039, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetLightHRTF5Channel, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4039, 5344)), // Final generic OOVPA: 5344; Removed: 4242-5233 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetFullHRTF4Channel, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CHRTFSource_SetLightHRTF4Channel, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(CFullHrtfSource_GetHrtfFilterPair, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CLightHrtfSource_GetHrtfFilterPair, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pThis))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CHrtfSource_SetAlgorithm_FullHrtf, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)
    REGISTER_OOVPAS(SYM_FUN(CHrtfSource_SetAlgorithm_LightHrtf, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(4242)), // Final generic OOVPA: 4242; Removed: 5344+ (introduced in 4242)

    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreate, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pguidDeviceId), PARAM(stk, ppDirectSound), PARAM(stk, pUnused3))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreateBuffer, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pdsbd), PARAM(stk, ppBuffer))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundCreateStream, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pdssd), PARAM(stk, ppStream))),
                    SYM_SIG(3911, 4039, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundDoWork, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4134)), // Final generic OOVPA: 4134; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundGetSampleTime, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4361)), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundOverrideSpeakerConfig, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, dwSpeakerConfig))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseFullHRTF, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, 4134, 4242 /*, 5344=revert to 4134*/)), // Final generic OOVPA: 5344 (revert to 4134); Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseLightHRTF, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(3911, 4039, /*4134?,*/ 4242, 5344)), // Final generic OOVPA: 5344; Removed: 0
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseFullHRTF4Channel, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)
    REGISTER_OOVPAS(SYM_FUN(DirectSoundUseLightHRTF4Channel, CALL(unk), STACK(/*default*/), PARAMS(PARAM1(void))),
                    SYM_SIG(5344)), // undocument // Final generic OOVPA: 5344; Removed: 0 (introduced in 5344)

    REGISTER_OOVPAS(SYM_FUN(IsValidFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pwfx))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 4361+ // NOTE: 4361+ is replace into a class function

    REGISTER_OOVPAS(SYM_FUN(XAudioDownloadEffectsImage, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pszImageName), PARAM(stk, pImageLoc), PARAM(stk, dwFlags), PARAM(stk, ppImageDesc))),
                    SYM_SIG(4039, 4134)), // Final generic OOVPA: 4134; Removed: 0 (introduced in 4039)
    REGISTER_OOVPAS(SYM_FUN(XAudioSetEffectData, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, dwEffectIndex), PARAM(stk, pDesc), PARAM(stk, pRawDesc))),
                    SYM_SIG(5028, 5344)), // Final generic OOVPA: 5344; Removed: 0 (introduced in ??5028 or 5120??)
    REGISTER_OOVPAS(SYM_FUN(XAudioCreatePcmFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, nChannels), PARAM(stk, nSamplesPerSec), PARAM(stk, wBitsPerSample), PARAM(stk, pwfx))),
                    SYM_SIG(3911)), // Final generic OOVPA: 3911; Removed: 0 // NOTE: later revision changed to a jmp, and convert into class function
    REGISTER_OOVPAS(SYM_FUN(XAudioCreateAdpcmFormat, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, nChannels), PARAM(stk, nSamplesPerSec), PARAM(stk, pwfx))),
                    SYM_SIG(3911, 4039)), // Final generic OOVPA: 4039; Removed: 0 // NOTE: later revision changed to a jmp, and convert into class function

    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObject, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pszFileName), PARAM(stk, dwDesiredAccess), PARAM(stk, dwShareMode), PARAM(stk, dwCreationDisposition), PARAM(stk, dwFlagsAndAttributes), PARAM(stk, ppMediaObject))),
                    SYM_SIG(3911, 4242, 4361)), // TODO: Need investigation on 3936-4039
    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObjectAsync, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, hFile), PARAM(stk, dwMaxPackets), PARAM(stk, ppMediaObject))),
                    SYM_SIG(4432)), // TODO: Need investigation (confirmed does not exist in 4242)
    REGISTER_OOVPAS(SYM_FUN(XFileCreateMediaObjectEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, hFile), PARAM(stk, ppMediaObject))),
                    SYM_SIG(4242, 4361)), // TODO: Need investigation on 3936-4039

    REGISTER_OOVPAS(SYM_FUN(XWaveFileCreateMediaObject, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pszFileName), PARAM(stk, ppwfxFormat), PARAM(stk, ppMediaObject))),
                    SYM_SIG(3911, 4242, 4361)), // TODO: Need investigation on 3936-4039
    REGISTER_OOVPAS(SYM_FUN(XWaveFileCreateMediaObjectEx, CALL(unk), STACK(/*default*/), PARAMS(PARAM(stk, pszFileName), PARAM(stk, hFile), PARAM(stk, ppMediaObject))),
                    SYM_SIG(4242, 4361)), // TODO: Need investigation on 3936?-4039
};

// ******************************************************************
// * DSound_OOVPA_COUNT
// ******************************************************************
#define DSound_OOVPA_COUNT XBSDB_ARRAY_SIZE(DSound_OOVPA)

#endif

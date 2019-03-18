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
// *  59 Temple Place - Suite 330, Bostom, MA 02111-1307, USA.
// *
// *  (c) 2017 RadWolfie
// *  (c) 2017 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// Titles which did compiled with full library version
//   [LibV] Title Name                       |  Verify   |   Comments
//-------------------------------------------------------------------
// * [3925] Cel Damage                       |   100%    | Contain full library.
// * [3936] Silent Hill 2                    |   100%    | Contain full library.
// * [4039] Nightcaster                      |   100%    | Only has 90% of the library compiled with xbe build.
// * [4039] Azurik PAL                       |   100%    | Contain full library.
// * [4134] RaceX (Demo)                     |     -%    | Only has a few library.
// * [4134] Blood Omen 2                     |    80%    | Does not have full library.
// * [4134] JSRF                             |     1%    | Does not have Stream class. DS and Buffer might be full.
// * [4134] Double-S.T.E.A.L                 |   100%    | Contain full library.
// * [4242] NFL Blitz 2002                   |   100%    | Contain full library.
// * [4361] Flight Academy                   |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [4432] RedCard 2003                     |   100%    | Contain full library.
// * [4627] MLB SlugFest 2003                |   100%    | Contain full library.
// * [4721] Terminator Dawn of Fate          |   100%    | Contain full library.
// * [4831] Whacked!                         |   100%    | Contain full library.
// * [4928] Drihoo                           |   100%    | Contain full library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | Contain full library.
// * [5120] N.U.D.E.@                        |   100%    | Contain full library.
// * [5233] Evil Dead                        |   100%    | Contain full library.
// * [5344] Gladius OXM Demo Disc 20         |   100%    | Contain full library.
// * [5455] GR: Island Thunder               |   100%    | Only has 50%-ish of the library compiled with xbe build.
// * [5455] Dinosaur Hunting                 |   100%    | Contain full library.
// * [5558] Dino Crisis 3                    |   100%    | Contain full library.
// * [5659] Midway Arcade Treasures Paperboy |   100%    | Contain full library.
// * [5788] Digimon Battle Chronicle         |   100%    | Contain full library.
// * [5849] Nickelodeon Tak 2                |   100%    | Contain full library.


// TODO: Known DSound OOVPA issue list
// * 3911 to 5933: Cannot make OOVPAs
//   * IDirectSound_SetCooperativeLevel     (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSound_Compact                 (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSoundBuffer_Restore           (Xbox doesn't use it, can't make OOVPA for it)
//   * IDirectSoundBuffer_Unlock            (Xbox doesn't use it, however can make OOVPA; NOTE: OOVPA is registered for it)
//   * IDirectSoundStream_AddRef            (Using IUnknown_AddRef)
//   * IDirectSoundStream_Release           (Using IUnknown_Release)
// * 3911 to ????: These functions does not exist until newer XDK revision
//   * IDirectSound_GetOutputLevels             (Lowest found was 4361)
//   * IDirectSound_SynchPlayback               (Lowest found was 4831)
//   * IDirectSoundBuffer_GetVoiceProperties    (Lowest found was 5028)
//   * IDirectSoundBuffer_SetFormat             (Lowest found was 4039)
//   * IDirectSoundBuffer_SetDistanceFactor     (Lowest found was 4134)
//   * IDirectSoundBuffer_SetDopplerFactor      (Lowest found was 4134)
//   * IDirectSoundBuffer_SetRolloffFactor      (Lowest found was 4134)
//   * IDirectSoundBuffer_SetRolloffCurve       (Lowest found was 4361)
//   * IDirectSoundBuffer_Pause                 (Lowest found was 4721)
//   * IDirectSoundBuffer_PauseEx               (Lowest found was 4721)
//   * IDirectSoundBuffer_SetPlayRegion         (Introduce in 4039, last known earliest revision)
//   * IDirectSoundStream_FlushEx               (Lowest found was 4134)
//   * IDirectSoundStream_GetVoiceProperties    (Lowest found was 5028)
//   * IDirectSoundStream_PauseEx               (Lowest found was 4361)
//   * IDirectSoundStream_SetDistanceFactor     (Lowest found was 4134)
//   * IDirectSoundStream_SetDopplerFactor      (Lowest found was 4134)
//   * IDirectSoundStream_SetFormat             (Lowest found was 4039)
//   * IDirectSoundStream_SetRolloffCurve       (Lowest found was 4361)
//   * IDirectSoundStream_SetRolloffFactor      (Lowest found was 4134)
//   * DirectSoundDumpMemoryUsage               (Lowest found was 4361)
//   * DirectSoundGetSampleTime                 (Need verify between 4039 to 4361)
//   * DirectSoundOverrideSpeakerConfig         (Lowest found was 4361)
//   * XAudioDownloadEffectsImage               (Lowest found was 4134)
//   * XGetAudioFlags                           (Lowest found was 3911, XAudioGetSpeakerConfig introduced later as alias, is part of Xapi section)
//   * XAudioSetEffectData                      (Lowest found was 5344)
//   * DirectSoundUseFullHRTF4Channel           (Lowest found was 5344)
//   * DirectSoundUseLightHRTF4Channel          (Lowest found was 5344)
// * 3911 to 3936: Following separater functions has exact asm codes as whole function are...
//   * IDirectSoundStream_SetVolume     & CDirectSoundStream_SetVolume
//   * IDirectSoundStream_SetPitch      & CDirectSoundStream_SetPitch
//   * IDirectSoundStream_SetLFO        & CDirectSoundStream_SetLFO
//   * IDirectSoundStream_SetEG         & CDirectSoundStream_SetEG
//   * IDirectSoundStream_SetFilter     & CDirectSoundStream_SetFilter
//   * IDirectSoundStream_SetHeadroom   & CDirectSoundStream_SetHeadroom
//   * IDirectSoundStream_SetFrequency  & CDirectSoundStream_SetFrequency
//   * IDirectSoundStream_SetMixBins    & CDirectSoundStream_SetMixBins
// * Need to include func export support for IDirectSoundStream_Setxxxxx from above.
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
// * CDirectSound_SetAllParameters and CDirectSound_SetAllParametersA currently separated
//   * Need to review what's the difference and why is it necessary to be separated.
//   * It also have various revisions, we should be able to narrow it down to remove duplicates.
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
//   * DirectSoundUseLightHRTF (4039 - 4134)
//   * DirectSoundUseFullHRTF4Channel (4242 - 5233)
//   * DirectSoundUseLightHRTF4Channel (4242 - 5233)
//   * XAudioCreateAdpcmFormat (4039 - 4134)
//   * XFileCreateMediaObject (4039 - 4242)
//   * XWaveFileCreateMediaObject (4039 - 4242)


#ifndef DSOUND_OOVPA_INL
#define DSOUND_OOVPA_INL

#include "../OOVPA.h"

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
#include "DSound/5233.inl"
#include "DSound/5344.inl"
#include "DSound/5455.inl"
#include "DSound/5558.inl"


// ******************************************************************
// * DSOUND_OOVPA
// ******************************************************************
OOVPATable DSound_OOVPAV2[] = {

    REGISTER_OOVPAS(XAudioCalculatePitch, 3911, 4039),
    REGISTER_OOVPAS(DirectSoundEnterCriticalSection, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Commit3dSettings, 3911),
    REGISTER_OOVPAS(CMcpxAPU_ServiceDeferredCommandsLow, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Set3dDistanceFactor, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Set3dDopplerFactor, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Set3dParameters, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Set3dPosition, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Set3dRolloffFactor, 3911),
    REGISTER_OOVPAS(CMcpxAPU_Set3dVelocity, 3911),
    REGISTER_OOVPAS(CMcpxAPU_SetI3DL2Listener, 3911),
    REGISTER_OOVPAS(CMcpxAPU_SetMixBinHeadroom, 3911),
    REGISTER_OOVPAS(CMcpxAPU_SynchPlayback, 4831),
    REGISTER_OOVPAS(CMcpxBuffer_GetCurrentPosition, 3911, 4039, 4134),
    REGISTER_OOVPAS(CMcpxBuffer_GetStatus, 3911, 4039, 4134, 4721, 4831),
    REGISTER_OOVPAS(CMcpxBuffer_Pause, 4721, 4831), // NOTE: ?Pause@CMcpxBuffer@DirectSound@@QAEJK@Z
    REGISTER_OOVPAS(CMcpxBuffer_Pause_Ex, 4721), // NOTE: ?Pause@CMcpxBuffer@DirectSound@@QAEJ_JK@Z
    REGISTER_OOVPAS(CMcpxBuffer_Play, 3911, 4039, 4134, 4721, 4831), // NOTE: ?Play@CMcpxBuffer@DirectSound@@QAEJK@Z
    REGISTER_OOVPAS(CMcpxBuffer_Play_Ex, 4039), // NOTE: ?Play@CMcpxBuffer@DirectSound@@QAEJ_JK@Z
    REGISTER_OOVPAS(CMcpxBuffer_SetBufferData, 4134, 5455),
    REGISTER_OOVPAS(CMcpxBuffer_SetCurrentPosition, 3911, 4039, 4134),
    REGISTER_OOVPAS(CMcpxBuffer_Stop, 3911, 4134, 4242), // NOTE: ?Stop@CMcpxBuffer@DirectSound@@QAEJK@Z
    REGISTER_OOVPAS(CMcpxBuffer_Stop_Ex, 4134), // NOTE: ?Stop@CMcpxBuffer@DirectSound@@QAEJ_JK@Z
    REGISTER_OOVPAS(CMcpxStream_Discontinuity, 3911, 4039, 4134, 4531, 5455),
    REGISTER_OOVPAS(CMcpxStream_Flush, 3911, 3936, 4039, 4134, 5455),
    REGISTER_OOVPAS(CMcpxStream_GetStatus, 4134, 4721),
    REGISTER_OOVPAS(CMcpxStream_Pause, 3911, 4039, 4134, 4831),
    REGISTER_OOVPAS(CMcpxStream_Pause_Ex, 4361),
    REGISTER_OOVPAS(CSensaura3d_GetFullHRTFFilterPair, 3911, 3936),
    REGISTER_OOVPAS(CSensaura3d_GetLiteHRTFFilterPair, 3911, 3936),
    REGISTER_OOVPAS(CMcpxVoiceClient_Commit3dSettings, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_GetVoiceProperties, 5028),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dConeOrientation, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dConeOutsideVolume, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dMaxDistance, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dMinDistance, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dMode, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dParameters, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dPosition, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_Set3dVelocity, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetEG, 3911, 4039, 4134, 4242),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetFilter, 3911, 4039, 4134),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetI3DL2Source, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetLFO, 3911, 4039, 4134, 4242),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetMixBins, 3911, 4039, 4134),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetPitch, 3911),
    REGISTER_OOVPAS(CMcpxVoiceClient_SetVolume, 3911, 4039, 4134),
    REGISTER_OOVPAS(DSound_CRefCount_AddRef, 3911, 4039),
    REGISTER_OOVPAS(DSound_CRefCount_Release, 3911, 4039, 5455),
    REGISTER_OOVPAS(CDirectSoundVoiceSettings_SetMixBinVolumes, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundVoice_CommitDeferredSettings, 5455),
    REGISTER_OOVPAS(CDirectSoundVoice_GetVoiceProperties, 5028),
    REGISTER_OOVPAS(CDirectSoundVoice_Set3DVoiceData, 5455),
    REGISTER_OOVPAS(CDirectSoundVoice_SetAllParameters, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundVoice_SetConeAngles, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetConeOrientation, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetConeOutsideVolume, 3911, 4039, 4134, 4361, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetDistanceFactor, 4134, 4361, 4627, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetDopplerFactor, 4134, 4361, 4627, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetEG, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetFilter, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetFormat, 4039, 4721),
    REGISTER_OOVPAS(CDirectSoundVoice_SetFrequency, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundVoice_SetHeadroom, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundVoice_SetI3DL2Source, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetLFO, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetMaxDistance, 3911, 4039, 4134, 4361, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetMinDistance, 3911, 4039, 4134, 4361, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetMixBins, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetMixBinVolumes, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetMode, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetOutputBuffer, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetPitch, 3911, 4039),
    REGISTER_OOVPAS(CDirectSoundVoice_SetPosition, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetRolloffCurve, 4361, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetRolloffFactor, 4134, 4361, 5344), // s+ (from 4134's comment)
    REGISTER_OOVPAS(CDirectSoundVoice_SetVelocity, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSoundVoice_SetVolume, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundVoice_Use3DVoiceData, 5558),
    REGISTER_OOVPAS(CDirectSound3DCalculator_Calculate3D, 5344),
    REGISTER_OOVPAS(CDirectSound3DCalculator_GetMixBinVolumes, 5344),
    REGISTER_OOVPAS(CDirectSound3DCalculator_GetPanData, 5344),
    REGISTER_OOVPAS(CDirectSound3DCalculator_GetVoiceData, 5344),
    REGISTER_OOVPAS(CDirectSoundBuffer_GetCurrentPosition, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_GetStatus, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_GetVoiceProperties, 5028),
    REGISTER_OOVPAS(CDirectSoundBuffer_Lock, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_Pause, 4721),
    REGISTER_OOVPAS(CDirectSoundBuffer_PauseEx, 4721),
    REGISTER_OOVPAS(CDirectSoundBuffer_Play, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_PlayEx, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_Set3DVoiceData, 5455),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetAllParameters, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetBufferData, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetConeAngles, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetConeOrientation, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetConeOutsideVolume, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetCurrentPosition, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetDistanceFactor, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetDopplerFactor, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetEG, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetFilter, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetFormat, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetFrequency, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetHeadroom, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetI3DL2Source, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetLFO, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetLoopRegion, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetMaxDistance, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetMinDistance, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetMixBins, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetMixBinVolumes, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetMode, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetNotificationPositions, 3911, 4039, 4242), // Uncommenting these fixes dashboard 4920 (from 4627 comment)
    REGISTER_OOVPAS(CDirectSoundBuffer_SetOutputBuffer, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetPitch, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetPlayRegion, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetPosition, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetRolloffCurve, 4361),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetRolloffFactor, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetVelocity, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_SetVolume, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_Stop, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_StopEx, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundBuffer_Use3DVoiceData, 5558),
    REGISTER_OOVPAS(CDirectSoundStream_AddRef, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_Discontinuity, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_Flush, 3911, 4039, 4134, 5028),
    REGISTER_OOVPAS(CDirectSoundStream_FlushEx, 4134, 5028),
    REGISTER_OOVPAS(CDirectSoundStream_GetInfo, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_GetStatus, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_GetVoiceProperties, 5028),
    REGISTER_OOVPAS(CDirectSoundStream_Pause, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_PauseEx, 4361),
    REGISTER_OOVPAS(CDirectSoundStream_Process, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_Release, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_Set3DVoiceData, 5455),
    REGISTER_OOVPAS(CDirectSoundStream_SetAllParameters, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetConeAngles, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetConeOrientation, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetConeOutsideVolume, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetDistanceFactor, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetDopplerFactor, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetEG, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetFilter, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetFormat, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetFrequency, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetHeadroom, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetI3DL2Source, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetLFO, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetMaxDistance, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetMinDistance, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetMixBins, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetMixBinVolumes_12, 3911), //This revision is only used in XDK 3911 to 3936.
    REGISTER_OOVPAS(CDirectSoundStream_SetMixBinVolumes_8, 4039, 4134), //Then it has changed in XDK 4039 and higher.
    REGISTER_OOVPAS(CDirectSoundStream_SetMode, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetOutputBuffer, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetPitch, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetPosition, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetRolloffCurve, 4361),
    REGISTER_OOVPAS(CDirectSoundStream_SetRolloffFactor, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetVelocity, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_SetVolume, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSoundStream_Use3DVoiceData, 5558),
    REGISTER_OOVPAS(CDirectSound_CommitDeferredSettings, 3911, 4039, 4134, 5344, 5455),
    REGISTER_OOVPAS(CDirectSound_CommitEffectData, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_CreateSoundBuffer, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_CreateSoundStream, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_DownloadEffectsImage, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_DoWork, 3911, 4039),
    REGISTER_OOVPAS(CDirectSound_EnableHeadphones, 3911, 4039, 4134, 5344, 5455),
    REGISTER_OOVPAS(CDirectSound_GetCaps, 3911, 4039, 4134, 4361),
    REGISTER_OOVPAS(CDirectSound_GetEffectData, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_GetOutputLevels, 4361),
    REGISTER_OOVPAS(CDirectSound_GetSpeakerConfig, 3911, 4242, 4627, 5455),
    REGISTER_OOVPAS(CDirectSound_GetTime, 3911),
    REGISTER_OOVPAS(CDirectSound_MapBufferData, 5344),
    REGISTER_OOVPAS(CDirectSound_SetAllParameters, 3911, 4039, 4134), //TODO: Need to improvise after 4134
    REGISTER_OOVPAS(CDirectSound_SetAllParametersA, 4627, 4721, 4831), //TODO: Need to improvise after 4134 then move in CDirectSound_SetAllParameters
    REGISTER_OOVPAS(CDirectSound_SetDistanceFactor, 3911, 4039, 4134, 4627, 5344),
    REGISTER_OOVPAS(CDirectSound_SetDopplerFactor, 3911, 4039, 4134, 4627, 5344),
    REGISTER_OOVPAS(CDirectSound_SetEffectData, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_SetI3DL2Listener, 3911, 4039, 4134, 5344, 5455),
    REGISTER_OOVPAS(CDirectSound_SetMixBinHeadroom, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_SetOrientation, 3911, 4039, 4134),
    REGISTER_OOVPAS(CDirectSound_SetPosition, 3911, 4039, 4134, 4627, 5344),
    REGISTER_OOVPAS(CDirectSound_SetRolloffFactor, 3911, 4039, 4134, 5344),
    REGISTER_OOVPAS(CDirectSound_SetVelocity, 3911, 4039, 4134, 4627, 5344),
    REGISTER_OOVPAS(CDirectSound_SynchPlayback, 4831, 5344),
    REGISTER_OOVPAS(CDirectSound_UnmapBufferData, 5344),
    REGISTER_OOVPAS(IDirectSound3DCalculator_Calculate3D, 5344), // jmp only
    REGISTER_OOVPAS(IDirectSound3DCalculator_GetMixBinVolumes, 5344), // jmp only
    REGISTER_OOVPAS(IDirectSound3DCalculator_GetPanData, 5344),
    REGISTER_OOVPAS(IDirectSound3DCalculator_GetVoiceData, 5344),
    REGISTER_OOVPAS(IDirectSoundBuffer_AddRef, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_GetCurrentPosition, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_GetStatus, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_GetVoiceProperties, 5028),
    REGISTER_OOVPAS(IDirectSoundBuffer_Lock, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_Pause, 4721),
    REGISTER_OOVPAS(IDirectSoundBuffer_PauseEx, 4721),
    REGISTER_OOVPAS(IDirectSoundBuffer_Play, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_PlayEx, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_Release, 3911),
    //REGISTER_OOVPAS(IDirectSoundBuffer_Restore, 3911), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(IDirectSoundBuffer_Set3DVoiceData, 5455), // undocument
    REGISTER_OOVPAS(IDirectSoundBuffer_SetAllParameters, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetBufferData, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetConeAngles, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetConeOrientation, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetConeOutsideVolume, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetCurrentPosition, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetDistanceFactor, 4134),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetDopplerFactor, 4134),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetEG, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetFilter, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetFormat, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetFrequency, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetHeadroom, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetI3DL2Source, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetLFO, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetLoopRegion, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetMaxDistance, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetMinDistance, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetMixBins, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetMixBinVolumes_12, 3911), //This revision is only used in XDK 3911 to 3936.
    REGISTER_OOVPAS(IDirectSoundBuffer_SetMixBinVolumes_8, 4039), //Then it has changed in XDK 4039 and higher.
    REGISTER_OOVPAS(IDirectSoundBuffer_SetMode, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetNotificationPositions, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetOutputBuffer, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetPitch, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetPlayRegion, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetPosition, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetRolloffCurve, 4361),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetRolloffFactor, 4134),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetVelocity, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_SetVolume, 3911, 4039),
    REGISTER_OOVPAS(IDirectSoundBuffer_Stop, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_StopEx, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_Unlock, 3911),
    REGISTER_OOVPAS(IDirectSoundBuffer_Use3DVoiceData, 5558), // undocument
    REGISTER_OOVPAS(IDirectSoundStream_GetVoiceProperties, 5028), // jmp only
    REGISTER_OOVPAS(IDirectSoundStream_FlushEx, 4134),
    REGISTER_OOVPAS(IDirectSoundStream_Pause, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_PauseEx, 4361),
    REGISTER_OOVPAS(IDirectSoundStream_Set3DVoiceData, 5455), // jmp only
    REGISTER_OOVPAS(IDirectSoundStream_SetAllParameters, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_SetConeAngles, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_SetConeOrientation, 3911),
    REGISTER_OOVPAS(IDirectSoundStream_SetConeOutsideVolume, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_SetDistanceFactor, 4134),
    REGISTER_OOVPAS(IDirectSoundStream_SetDopplerFactor, 4134),
    REGISTER_OOVPAS(IDirectSoundStream_SetEG, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetLFO, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetFilter, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetFormat, 4039),
    REGISTER_OOVPAS(IDirectSoundStream_SetFrequency, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetHeadroom, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetI3DL2Source, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_SetMaxDistance, 3911),
    REGISTER_OOVPAS(IDirectSoundStream_SetMinDistance, 3911),
    REGISTER_OOVPAS(IDirectSoundStream_SetMixBins, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetMixBinVolumes_12, 3911), //NOTE: 3911 only perform a jmp, see more note for CDirectSoundStream_SetMixBinVolumes_12
    REGISTER_OOVPAS(IDirectSoundStream_SetMixBinVolumes_8, 4039), //NOTE: 4039 and newer only perform a jmp.
    REGISTER_OOVPAS(IDirectSoundStream_SetMode, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_SetOutputBuffer, 3911), //NOTE: 3911 only perform a jmp, later XDK revision may need a patch?
    REGISTER_OOVPAS(IDirectSoundStream_SetPitch, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_SetPosition, 3911),
    REGISTER_OOVPAS(IDirectSoundStream_SetRolloffCurve, 4361),
    REGISTER_OOVPAS(IDirectSoundStream_SetRolloffFactor, 4134),
    REGISTER_OOVPAS(IDirectSoundStream_SetVelocity, 3911),
    REGISTER_OOVPAS(IDirectSoundStream_SetVolume, 3911, 4039), //NOTE: Is require to be patch since its' calling to voice class.
    REGISTER_OOVPAS(IDirectSoundStream_Use3DVoiceData, 5558), // jmp only
    REGISTER_OOVPAS(IDirectSound_AddRef, 3911),
    REGISTER_OOVPAS(IDirectSound_CommitDeferredSettings, 3911),
    REGISTER_OOVPAS(IDirectSound_CommitEffectData, 3911),
    //REGISTER_OOVPAS(IDirectSound_Compact, 3911), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(IDirectSound_CreateSoundBuffer, 3911 /*3936, 4134, 4361*/),
    REGISTER_OOVPAS(IDirectSound_CreateSoundStream, 3911 /*5558*/),
    REGISTER_OOVPAS(IDirectSound_DownloadEffectsImage, 3911),
    REGISTER_OOVPAS(IDirectSound_EnableHeadphones, 3911),
    REGISTER_OOVPAS(IDirectSound_GetCaps, 3911),
    REGISTER_OOVPAS(IDirectSound_GetEffectData, 3911),
    REGISTER_OOVPAS(IDirectSound_GetOutputLevels, 4361),
    REGISTER_OOVPAS(IDirectSound_GetSpeakerConfig, 3911),
    REGISTER_OOVPAS(IDirectSound_GetTime, 3911),
    REGISTER_OOVPAS(IDirectSound_MapBufferData, 5344), // undocument
    REGISTER_OOVPAS(IDirectSound_Release, 3911),
    REGISTER_OOVPAS(IDirectSound_SetAllParameters, 3911),
    //REGISTER_OOVPAS(IDirectSound_SetCooperativeLevel, 3911), // Xbox does not use it plus can't create OOVPA for it.
    REGISTER_OOVPAS(IDirectSound_SetDistanceFactor, 3911),
    REGISTER_OOVPAS(IDirectSound_SetDopplerFactor, 3911),
    REGISTER_OOVPAS(IDirectSound_SetEffectData, 3911),
    REGISTER_OOVPAS(IDirectSound_SetI3DL2Listener, 3911),
    REGISTER_OOVPAS(IDirectSound_SetMixBinHeadroom, 3911),
    REGISTER_OOVPAS(IDirectSound_SetOrientation, 3911),
    REGISTER_OOVPAS(IDirectSound_SetPosition, 3911),
    REGISTER_OOVPAS(IDirectSound_SetRolloffFactor, 3911),
    REGISTER_OOVPAS(IDirectSound_SetVelocity, 3911),
    REGISTER_OOVPAS(IDirectSound_SynchPlayback, 4831),
    REGISTER_OOVPAS(IDirectSound_UnmapBufferData, 5344), // undocument

    REGISTER_OOVPAS(CFullHRTFSource_GetCenterVolume, 4039, 4134, 5344),
    REGISTER_OOVPAS(CHRTFSource_SetFullHRTF5Channel, 4039, 5344 /*5558*/), // 5558 is currently not in used since OOVPA 5344 is generic.
    REGISTER_OOVPAS(CHRTFSource_SetLightHRTF5Channel, 5344),
    REGISTER_OOVPAS(CHRTFSource_SetFullHRTF4Channel, 5344),
    REGISTER_OOVPAS(CHRTFSource_SetLightHRTF4Channel, 5344),
    REGISTER_OOVPAS(CFullHrtfSource_GetHrtfFilterPair, 4242),
    REGISTER_OOVPAS(CLightHrtfSource_GetHrtfFilterPair, 4242),
    REGISTER_OOVPAS(CHrtfSource_SetAlgorithm_FullHrtf, 4242),
    REGISTER_OOVPAS(CHrtfSource_SetAlgorithm_LightHrtf, 4242),

    REGISTER_OOVPAS(DirectSoundCreate, 3911, 4039, 4134),
    REGISTER_OOVPAS(DirectSoundCreateBuffer, 3911, 4039, 4134),
    REGISTER_OOVPAS(DirectSoundCreateStream, 3911, 4039, 4134),
    REGISTER_OOVPAS(DirectSoundDoWork, 3911, 4134),
    REGISTER_OOVPAS(DirectSoundGetSampleTime, 3911, 4361),
    REGISTER_OOVPAS(DirectSoundUseFullHRTF, 3911, 4039, 4134, 4242, 5344),
    REGISTER_OOVPAS(DirectSoundUseLightHRTF, 3911, 4242, 5344),
    REGISTER_OOVPAS(DirectSoundUseFullHRTF4Channel, 5344), // undocument
    REGISTER_OOVPAS(DirectSoundUseLightHRTF4Channel, 5344), // undocument

    REGISTER_OOVPAS(WaveFormat_CreateXboxAdpcmFormat, 4039),
    REGISTER_OOVPAS(XAudioDownloadEffectsImage, 4134),
    REGISTER_OOVPAS(XAudioSetEffectData, 5344),
    REGISTER_OOVPAS(IsValidFormat, 3911, 4039),
    REGISTER_OOVPAS(XAudioCreatePcmFormat, 3911),
    REGISTER_OOVPAS(XAudioCreateAdpcmFormat, 3911, 4039),
    REGISTER_OOVPAS(XFileCreateMediaObject, 3911, 4361),
    REGISTER_OOVPAS(XFileCreateMediaObjectAsync, 4432),
    REGISTER_OOVPAS(XFileCreateMediaObjectEx, 4361),
    REGISTER_OOVPAS(XWaveFileCreateMediaObject, 3911, 4361),
    REGISTER_OOVPAS(XWaveFileCreateMediaObjectEx, 4361),

    REGISTER_OOVPAS(DSound_CMemoryManager_PoolAlloc, 4134, 4361), // For reference purpose only, does not have XREF value.
};

// ******************************************************************
// * DSound_OOVPA_COUNT
// ******************************************************************
#define DSound_OOVPA_COUNT OOVPA_TABLE_COUNT(DSound_OOVPAV2)

#endif

// ******************************************************************
// *
// *   OOVPADatabase->DSound->4242.inl
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
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * CMcpxVoiceClient::SetLFO
// ******************************************************************
// Generic OOVPA as of 4242 and newer
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_SetLFO,
                      4242,

                      XREF_CMcpxVoiceClient_SetLFO,
                      XRefZero)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x14, 0x8B },

    { 0x18, 0x08 },
    { 0x19, 0x85 },
    { 0x1A, 0xC9 },
    { 0x1B, 0x75 },
    { 0x1C, 0x4A },
    { 0x1D, 0x39 },
    { 0x1E, 0x48 },
    { 0x1F, 0x04 },

    { 0x50, 0x31 },
    { 0x51, 0x4E },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetEG
// ******************************************************************
// Generic OOVPA as of 4242 and newer
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_SetEG,
                      4242,

                      XREF_CMcpxVoiceClient_SetEG,
                      XRefZero)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x16, 0x8B },
    { 0x17, 0x45 },
    { 0x18, 0x08 },
    { 0x19, 0x8B },
    { 0x1A, 0x08 },
    { 0x1B, 0x85 },
    { 0x1C, 0xC9 },
    { 0x1D, 0x75 },
    { 0x1E, 0x75 },
    { 0x1F, 0x8B },

    { 0x50, 0x56 },
    { 0x51, 0x24 },
    //
);

// ******************************************************************
// * CMcpxBuffer_Stop
// ******************************************************************
//Generic OOVPA as of 4242 and newer.
OOVPA_SIG_HEADER_XREF(CMcpxBuffer_Stop,
                      4242,

                      XREF_CMcpxBuffer_Stop,
                      XRefZero)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Stop+0x0E : cmp al, 3
    { 0x0E, 0x3C },
    { 0x0F, 0x03 },

    // CMcpxBuffer_Stop+0x17 : jne +0x2A
    { 0x17, 0x74 },
    { 0x18, 0x2A },

    // CMcpxBuffer_Stop+0x19 : test [esp+10h], 2
    { 0x19, 0xF6 },
    { 0x1A, 0x44 },
    { 0x1B, 0x24 },
    { 0x1C, 0x10 },
    { 0x1D, 0x02 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundBuffer::SetNotificationPositions
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetNotificationPositions,
                      4242,

                      XREF_CDirectSoundBuffer_SetNotificationPositions,
                      XRefZero)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetNotificationPositions+0x00 : push ebx
    { 0x00, 0x53 },

    { 0x0C, 0x00 },
    { 0x1B, 0xFF },
    { 0x25, 0x80 },

    { 0x2C, 0x0C },
    { 0x2D, 0x8B },
    { 0x2E, 0x4E },
    { 0x2F, 0x1C },

    { 0x30, 0x57 },

    { 0x47, 0xE8 },
    { 0x5D, 0x8B },
    //
);

// ******************************************************************
// * CDirectSound_GetSpeakerConfig
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_GetSpeakerConfig,
                      4242,

                      XREF_CDirectSound_GetSpeakerConfig,
                      XRefOne)
OOVPA_SIG_MATCH(

    // call DirectSoundEnterCriticalSection
    XREF_ENTRY(0x01, XREF_DirectSoundEnterCriticalSection),

    // call DirectSoundEnterCriticalSection
    OV_MATCH(0x00, 0xE8),
    // cmp dword ptr [...], 0
    OV_MATCH(0x05, 0x83, 0x3D),

    // mov ecx, [esp+0x04]
    OV_MATCH(0x27, 0x8B, 0x4C, 0x24, 0x04),
    // mov ecx, [ecx+0x08]
    // mov ecx, [ecx+0x08]
    OV_MATCH(0x2B, 0x8B, 0x49, 0x08, 0x8B),

    // and ..., 0x7FFFFFFF
    OV_MATCH(0x35, 0x81),
    //OV_MATCH(0x36, 0xE1), (This value has changed, commented out to expand support for later revisions.)
    OV_MATCH(0x37, 0xFF, 0xFF, 0xFF, 0x7F),

    // ret 0x0008
    OV_MATCH(0x4E, 0xC2, 0x08, 0x00),
    //
);

// ******************************************************************
// * CFullHrtfSource_GetHrtfFilterPair
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CFullHrtfSource_GetHrtfFilterPair,
                      4242,

                      XREF_CFullHrtfSource_GetHrtfFilterPair,
                      XRefZero)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },
    { 0x02, 0x74 },
    { 0x03, 0x24 },
    { 0x04, 0x08 },
    { 0x05, 0xD9 },
    { 0x06, 0x46 },
    { 0x07, 0x14 },
    { 0x08, 0x51 },
    { 0x09, 0xD8 },
    { 0x0A, 0x1D },

    { 0x1A, 0x05 },
    { 0x1F, 0xEB },

    { 0x58, 0xD8 },
    { 0x59, 0x05 },
    //
);

// ******************************************************************
// * CHrtfSource_SetAlgorithm_FullHrtf
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CHrtfSource_SetAlgorithm_FullHrtf,
                      4242,

                      XREF_CHrtfSource_SetAlgorithm_FullHrtf,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x17, XREF_CFullHrtfSource_GetHrtfFilterPair),

    { 0x00, 0x83 },
    { 0x01, 0x25 },
    { 0x06, 0x00 },
    { 0x07, 0xC7 },
    { 0x08, 0x05 },
    { 0x11, 0xC7 },
    { 0x12, 0x05 },
    { 0x1B, 0xC3 },
    //
);

// ******************************************************************
// * DirectSoundUseFullHRTF
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundUseFullHRTF,
                      4242,

                      XRefNoSaveIndex,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_CHrtfSource_SetAlgorithm_FullHrtf),

    { 0x00, 0x56 },
    { 0x01, 0xE8 },
    { 0x06, 0x83 },
    { 0x07, 0x3D },
    { 0x0C, 0x02 },
    { 0x1A, 0x74 },
    { 0x1B, 0x0B },
    { 0x1C, 0x68 },
    //
);

// ******************************************************************
// * CLightHrtfSource_GetHrtfFilterPair
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CLightHrtfSource_GetHrtfFilterPair,
                      4242,

                      XREF_CLightHrtfSource_GetHrtfFilterPair,
                      XRefZero)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x01, 0x8B },
    { 0x02, 0x74 },
    { 0x03, 0x24 },
    { 0x04, 0x08 },
    { 0x05, 0xD9 },
    { 0x06, 0x46 },
    { 0x07, 0x10 },
    { 0x08, 0x51 },
    { 0x09, 0xD9 },
    { 0x0A, 0xE1 },
    { 0x0B, 0xD8 },
    { 0x0C, 0x05 },

    { 0x19, 0x99 },
    { 0x1A, 0x6A },

    { 0x8B, 0x89 },
    //
);

// ******************************************************************
// * CHrtfSource_SetAlgorithm_LightHrtf
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CHrtfSource_SetAlgorithm_LightHrtf,
                      4242,

                      XREF_CHrtfSource_SetAlgorithm_LightHrtf,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x1A, XREF_CLightHrtfSource_GetHrtfFilterPair),

    { 0x00, 0xC7 },
    { 0x01, 0x05 },
    { 0x06, 0x01 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },
    { 0x0A, 0xC7 },
    { 0x0B, 0x05 },
    { 0x14, 0xC7 },
    { 0x15, 0x05 },
    { 0x1E, 0xC3 },
    //
);

// ******************************************************************
// * DirectSoundUseLightHRTF
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundUseLightHRTF,
                      4242,

                      XRefNoSaveIndex,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x13, XREF_CHrtfSource_SetAlgorithm_LightHrtf),

    { 0x00, 0x56 },
    { 0x01, 0xE8 },
    { 0x06, 0x83 },
    { 0x07, 0x3D },
    { 0x0C, 0x02 },
    { 0x1A, 0x74 },
    { 0x1B, 0x0B },
    { 0x1C, 0x68 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxVoiceClient_Commit3dSettings,
                      4242,

                      XREF_CMcpxVoiceClient_Commit3dSettings,
                      XRefZero)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x43 : cmp edi, 0x02
    { 0x43, 0x83 },
    { 0x44, 0xFF },
    { 0x45, 0x02 },

    // CMcpxVoiceClient::Commit3dSettings+0x69 : mov e__,[e__+0x000000B4]
    { 0x69, 0x8B },
    //{ 0x6A, 0x__ },
    { 0x6B, 0xB4 },
    { 0x6C, 0x00 },
    //{ 0x6D, 0x00 },
    { 0x6E, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x76 : mov eax,[eax+0x000000B4]
    { 0x76, 0x8B },
    //{ 0x77, 0x80 },
    { 0x78, 0xB4 },
    { 0x79, 0x00 },
    //{ 0x7A, 0x00 },
    { 0x7B, 0x00 },

    //
);

// ******************************************************************
// * XFileCreateMediaObject
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XFileCreateMediaObject,
                      4242,

                      XRefNoSaveIndex,
                      XRefZero)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    OV_MATCH(0x3D, 0x18),
    OV_MATCH(0x40, 0x14),
    OV_MATCH(0x43, 0x10),
    OV_MATCH(0x46, 0x0C),
    OV_MATCH(0x49, 0x08),

    OV_MATCH(0x80, 0xC2, 0x18),
    //
);

// ******************************************************************
// * XFileCreateMediaObjectEx
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XFileCreateMediaObjectEx,
                         4242)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x28, 0x1B),

    OV_MATCH(0x36, 0x78, 0x1C, 0xFF, 0x74, 0x24, 0x10, 0x57, 0xE8),

    OV_MATCH(0x72, 0xC2, 0x08),
    //
);

// ******************************************************************
// * XWaveFileCreateMediaObject
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XWaveFileCreateMediaObject,
                         4242)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x53),
    OV_MATCH(0x25, 0xF7),

    OV_MATCH(0x45, 0xF6, 0x7C, 0x23, 0x83, 0x7C, 0x24, 0x14, 0x00),

    OV_MATCH(0x89, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * XWaveFileCreateMediaObjectEx
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XWaveFileCreateMediaObjectEx,
                      4242,

                      XRefNoSaveIndex,
                      XRefZero)
OOVPA_SIG_MATCH(

    OV_MATCH(0x16, 0x0B),
    OV_MATCH(0x25, 0xF7),

    OV_MATCH(0x49, 0xEB, 0x0A, 0xFF, 0x74, 0x24, 0x14, 0x57, 0xE8),

    OV_MATCH(0x85, 0xC2, 0x0C),
    //
);

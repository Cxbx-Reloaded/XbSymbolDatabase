// ******************************************************************
// *
// *   OOVPADatabase->DSound->5455.inl
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
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * CDirectSound::CommitDeferredSettings
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CDirectSound_CommitDeferredSettings, 5455, 2+8,

    XREF_CDirectSound_CommitDeferredSettings,
    XRefTwo)
    
        // CDirectSound_CommitDeferredSettings+0x45 : call [CDirectSound3DCalculator::Calculate3D]
        XREF_ENTRY( 0x46, XREF_CDirectSound3DCalculator_Calculate3D ),
    
        // CDirectSound_CommitDeferredSettings+0x5D : call [CDirectSoundVoice::CommitDeferredSettings]
        XREF_ENTRY( 0x5E, XREF_CDirectSoundVoice_CommitDeferredSettings ),

        // CDirectSound_CommitDeferredSettings+0x00 : push ebp; mov ebp,esp
        { 0x00, 0x55 },
        { 0x01, 0x8B },
        { 0x02, 0xEC },

        // CDirectSound_CommitDeferredSettings+0x27 : mov eax, 0x80004005
        { 0x27, 0xB8 },
        { 0x28, 0x05 },
        { 0x29, 0x40 },
        { 0x2B, 0x80 },

        // CDirectSound_CommitDeferredSettings+0x96 : leave
        { 0x96, 0xC9 },
OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSound::EnableHeadphones
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CDirectSound_EnableHeadphones, 5455, 17,

    XREF_CDirectSound_EnableHeadphones,
    XRefZero)

        // CDirectSound_EnableHeadphones+0x00 : push ebp
        { 0x00, 0x55 },

        // CDirectSound_EnableHeadphones+0x16 : movzx eax, al
        { 0x16, 0x0F },
        { 0x17, 0xB6 },
        { 0x18, 0xC0 },

        // CDirectSound_EnableHeadphones+0x3E : shr e__, 0x1F
        { 0x3E, 0xC1 },
        //{ 0x3F, 0xE8 }, // 5344 0xEA vs 5455 0xE8
        { 0x40, 0x1F },

        // CDirectSound_EnableHeadphones+0x53 : mov edi, 0x80000000
        { 0x53, 0xBF },
        { 0x54, 0x00 },
        { 0x55, 0x00 },
        { 0x56, 0x00 },
        { 0x57, 0x80 },

        // CDirectSound_EnableHeadphones+0xC4 : cmp dword ptr [ebp+0x0C],0
        { 0xC4, 0x83 },
        { 0xC5, 0x7D },
        { 0xC6, 0x0C },
        { 0xC7, 0x00 },

        // CDirectSound_EnableHeadphones+0x117 : leave
        //{ 0x117, 0xC9 },
        { 0x118, 0xC2 },
        { 0x119, 0x08 },
OOVPA_END;

// ******************************************************************
// * DSound_CRefCount_Release
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(DSound_CRefCount_Release, 5455, 10,

    XREF_DSound_CRefCount_Release,
    XRefZero)

        { 0x00, 0x8B },

        // DSound_CRefCount_Release+0x0B : dec eax
        { 0x0B, 0x48 },

        // DSound_CRefCount_Release+0x0E : mov dword ptr [ecx+4], eax
        { 0x0C, 0x89 },
        { 0x0D, 0x41 },
        { 0x0E, 0x04 },

        // DSound_CRefCount_Release+0x1D : mov, dword ptr [ecx+4]
        { 0x1B, 0x8B },
        { 0x1C, 0x41 },
        { 0x1D, 0x04 },

        // DSound_CRefCount_Release+0x20 : retn 0x04
        { 0x1E, 0xC2 },
        { 0x1F, 0x04 },
OOVPA_END;

// ******************************************************************
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_XREF(CMcpxStream_Discontinuity, 5455, 1+9,

    XREF_CMcpxStream_Discontinuity,
    XRefOne)

        XREF_ENTRY( 0x22, XREF_CMcpxStream_Stop ),

        // CMcpxStream_Discontinuity+0x00 : push esi; push edi
        { 0x00, 0x56 },
        { 0x01, 0x57 },

        // CMcpxStream_Discontinuity+0x12 : mov dx,0x800
        { 0x12, 0x66 },
        { 0x13, 0xBA },
        { 0x14, 0x00 },
        { 0x15, 0x08 },

        // CMcpxStream_Discontinuity+0x21 : call Stop@CMcpxStream@DirectSound@@QAEJK@Z
        { 0x21, 0xE8 },

        // CMcpxStream_Discontinuity+0x2B : pop esi; ret
        { 0x2B, 0x5E },
        { 0x2C, 0xC3 },
OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSound::SetI3DL2Listener
// ******************************************************************
OOVPA_XREF(CDirectSound_SetI3DL2Listener, 5455, 20,

    XREF_CDirectSound_SetI3DL2Listener,
    XRefZero)

        // CDirectSound_SetI3DL2Listener+0x00 : push esi
        { 0x00, 0x56 },

        // CDirectSound_SetI3DL2Listener+0x3A : mov edi,88780032h (unchanged since 3911)
        { 0x3A, 0xBF },
        //{ 0x3B, 0x32 },
        //{ 0x3C, 0x00 },
        //{ 0x3D, 0x78 },
        { 0x3E, 0x88 },

        // CDirectSound_SetI3DL2Listener+0x54 : mov ebx,dword ptr [ecx+4]
        { 0x54, 0x8B },
        { 0x55, 0x59 },
        { 0x56, 0x04 },

        // CDirectSound_SetI3DL2Listener+0x57 : mov edx,dword ptr [eax+8]
        { 0x57, 0x8B },
        { 0x58, 0x50 },
        { 0x59, 0x08 },

        // CDirectSound_SetI3DL2Listener+0x9C : mov ebx,dword ptr [ecx+1Ch]
        { 0x9C, 0x8B },
        { 0x9D, 0x59 },
        { 0x9E, 0x1C },

        // CDirectSound_SetI3DL2Listener+0xDB : or word ptr [ecx+__h],0FFFh
        { 0xDB, 0x66 },
        { 0xDC, 0x81 },
        { 0xDD, 0x89 },
        //{ 0xDE, 0x80 }, vs 5344 0x84
        { 0xDF, 0x00 },
        //{ 0xE0, 0x00 },
        //{ 0xE1, 0x00 },
        { 0xE2, 0xFF },
        { 0xE3, 0x0F },

        // CDirectSound_SetI3DL2Listener+0x105 : retn 0x0C
        { 0x105, 0xC2 },
        { 0x106, 0x0C },
OOVPA_END;

// ******************************************************************
// * CDirectSound_GetSpeakerConfig
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CDirectSound_GetSpeakerConfig, 5455, 14,

    XREF_CDirectSound_GetSpeakerConfig,
    XRefZero)

        { 0x00, 0xE8 },

        { 0x0B, 0x00 },
        { 0x14, 0x0B },
        { 0x20, 0xB8 },
        { 0x30, 0x08 },

        { 0x31, 0x81 },
        //{ 0x32, 0xE1 }, (This value has changed, commented out for generic support.)
        { 0x33, 0xFF },
        { 0x34, 0xFF },
        { 0x35, 0xFF },
        { 0x36, 0x7F },

        { 0x3C, 0x0B },

        { 0x48, 0x33 },

        { 0x4A, 0xC2 },
        { 0x4B, 0x08 },
OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSoundVoice::Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CDirectSoundVoice_Set3DVoiceData, 5455, 9,

    XREF_CDirectSoundVoice_Set3DVoiceData,
    XRefZero)

        { 0x00, 0x8B },
        { 0x04, 0x8B },

        { 0x28, 0x01 },
        { 0x3C, 0x02 },
        { 0x50, 0x04 },
        { 0x73, 0x08 },
        { 0x96, 0x10 },
        { 0xB9, 0x20 },
        { 0xCD, 0x40 },
OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSoundBuffer::Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CDirectSoundBuffer_Set3DVoiceData, 5455, 1+8,

    XREF_CDirectSoundBuffer_Set3DVoiceData,
    XRefOne)

        XREF_ENTRY( 0x32, XREF_CDirectSoundVoice_Set3DVoiceData ),

        { 0x00, 0x56 },
        { 0x11, 0x16 },
        { 0x16, 0x68 },
        { 0x36, 0x85 },
        { 0x3A, 0x74 },
        { 0x3C, 0x68 },
        { 0x4B, 0xC2 },
        { 0x4C, 0x08 },
OOVPA_END;

// ******************************************************************
// * IDirectSoundBuffer::Set3DVoiceData
// ******************************************************************
OOVPA_XREF(IDirectSoundBuffer_Set3DVoiceData, 5455, 1+8,

    XRefNoSaveIndex,
    XRefOne)

        XREF_ENTRY( 0x15, XREF_CDirectSoundBuffer_Set3DVoiceData ),

        { 0x06, 0x24 },
        { 0x08, 0x8B },
        { 0x0C, 0xE4 },
        { 0x0E, 0xD9 },
        { 0x11, 0x23 },
        { 0x14, 0xE8 },
        { 0x19, 0xC2 },
        { 0x1A, 0x08 },
OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSoundStream::Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CDirectSoundStream_Set3DVoiceData, 5455, 1+8,

    XREF_CDirectSoundStream_Set3DVoiceData,
    XRefOne)

        XREF_ENTRY( 0x36, XREF_CDirectSoundVoice_Set3DVoiceData ),

        { 0x00, 0x56 },
        { 0x11, 0x16 },
        { 0x16, 0x68 },
        { 0x35, 0xE8 },
        { 0x3E, 0x74 },
        { 0x40, 0x68 },
        { 0x4F, 0xC2 },
        { 0x50, 0x08 },
OOVPA_END;

// ******************************************************************
// * IDirectSoundStream_Set3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5455 and newer (note: is not introduced in 5344)
OOVPA_XREF(IDirectSoundStream_Set3DVoiceData, 5455, 1+1,

    XRefNoSaveIndex,
    XRefOne)

        // IDirectSoundStream_Set3DVoiceData+0x00 : jmp [CDirectSoundStream_Set3DVoiceData]
        XREF_ENTRY(0x01, XREF_CDirectSoundStream_Set3DVoiceData),

        // IDirectSoundStream_Set3DVoiceData+0x00 : jmp 0x........
        { 0x00, 0xE9 },
OOVPA_END;

// ******************************************************************
// * XAudioCalculatePitch
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(XAudioCalculatePitch, 5455, 12,

    XREF_XAudioCalculatePitch,
    XRefZero)

        { 0x00, 0x55 },

        // XAudioCalculatePitch+0x0F : cmp eax, 0xBB80
        { 0x0F, 0x3D },
        { 0x10, 0x80 },
        { 0x11, 0xBB },
        { 0x12, 0x00 },

        // XAudioCalculatePitch+0x18 : jmp +0x21
        { 0x18, 0xEB },
        { 0x19, 0x21 },

        // XAudioCalculatePitch+0x3B : lea ecx, [ebp+08]
        { 0x3B, 0x8D },
        { 0x3C, 0x4D },
        { 0x3D, 0x08 },

        // XAudioCalculatePitch+0x47 : retn 0x04
        { 0x47, 0xC2 },
        { 0x48, 0x04 },
OOVPA_END;

// ******************************************************************
// * DirectSound::CMcpxAPU::ServiceDeferredCommandsLow
// ******************************************************************
// Generic OOVPA as of 5455 and newer; whole asm had not been changed since.
OOVPA_XREF(CMcpxAPU_ServiceDeferredCommandsLow, 5455, 9,

    XREF_CMcpxAPU_ServiceDeferredCommandsLow,
    XRefZero)

        // CMcpxAPU_ServiceDeferredCommandsLow+0x00: push ebp; mov ebp,esp
        { 0x00, 0x55 },
        { 0x01, 0x8B },
        { 0x02, 0xEC },

        // CMcpxAPU_ServiceDeferredCommandsLow+0x11: lea ecx,[ebp-10]
        { 0x11, 0x8D },
        { 0x12, 0x4D },
        { 0x13, 0xF0 },

        // CMcpxAPU_ServiceDeferredCommandsLow+0x17: mov [ebp-08],eax
        { 0x17, 0x89 },
        { 0x18, 0x45 },
        { 0x19, 0xF8 },
OOVPA_END;

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
// Generic OOVPA as of 5455 and newer
OOVPA_XREF(CMcpxVoiceClient_Commit3dSettings, 5455, 2+9,

    XREF_CMcpxVoiceClient_Commit3dSettings,
    XRefTwo)

        // CMcpxVoiceClient::Commit3dSettings+0x2B : call [CDirectSound3DCalculator::Calculate3D]
        XREF_ENTRY( 0x2C, XREF_CDirectSound3DCalculator_Calculate3D ),

        // CMcpxVoiceClient::Commit3dSettings+0x55 : call [CDirectSound3DCalculator::GetVoiceData]
        XREF_ENTRY( 0x56, XREF_CDirectSound3DCalculator_GetVoiceData ),

        { 0x00, 0x55 },

        // CMcpxVoiceClient::Commit3dSettings+0x5D : mov e__,[e__+0x000000B4]
        { 0x5D, 0x8B },
        //{ 0x5E, 0x__ },
        { 0x5F, 0xB4 },
        { 0x60, 0x00 },
        //{ 0x61, 0x00 },
        { 0x62, 0x00 },

        // CMcpxVoiceClient::Commit3dSettings+0x69 : mov eax,[eax+0x000000B4]
        { 0x69, 0x8B },
        //{ 0x6A, 0x80 },
        { 0x6B, 0xB4 },
        { 0x6C, 0x00 },
        //{ 0x6D, 0x00 },
        { 0x6E, 0x00 },

OOVPA_END;

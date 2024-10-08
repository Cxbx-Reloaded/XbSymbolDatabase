// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * DirectSoundCreate
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DirectSoundCreate,
                         4039)
OOVPA_SIG_MATCH(

    // DirectSoundCreate+0x0B : mov esi, eax
    { 0x0B, 0x8B },
    { 0x0C, 0xF0 },

    // DirectSoundCreate+0x11 : call [addr]
    { 0x11, 0xE8 },

    // DirectSoundCreate+0x1A : jl +0x13
    { 0x1A, 0x7C },
    { 0x1B, 0x13 },

    // DirectSoundCreate+0x26 : sbb ecx, ecx
    { 0x26, 0x1B },
    { 0x27, 0xC9 },

    // DirectSoundCreate+0x43 : retn 0x0C
    { 0x43, 0xC2 },
    { 0x44, 0x0C },
    //
);

// ******************************************************************
// * DirectSoundCreateBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundCreateBuffer,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundCreateBuffer+0x2B : call [CDirectSound::CreateSoundBuffer]
    XREF_ENTRY(0x2C, XREF_CDirectSound_CreateSoundBuffer),

    // DirectSoundCreateBuffer+0x04 : and [ebp-0x04], 0
    { 0x04, 0x83 },
    { 0x05, 0x65 },
    { 0x06, 0xFC },

    // DirectSoundCreateBuffer+0x08 : push esi; push edi
    { 0x08, 0x56 },
    { 0x09, 0x57 },

    // DirectSoundCreateBuffer+0x32 : lea eax, [ebp-0x04]
    { 0x32, 0x8D },
    { 0x33, 0x45 },
    { 0x34, 0xFC },

    // DirectSoundCreateBuffer+0x4F : retn 0x08
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound::CreateSoundBuffer
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CreateSoundBuffer,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_CreateSoundBuffer+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_CreateSoundBuffer+0x25 : mov eax, 0x80004005
    { 0x25, 0xB8 },
    { 0x26, 0x05 },
    { 0x27, 0x40 },
    { 0x29, 0x80 },

    // CDirectSound_CreateSoundBuffer+0x2E : push 0x24
    { 0x2E, 0x6A },
    { 0x2F, 0x24 },

    // CDirectSound_CreateSoundBuffer+0x4C : add esi, 0x7FF8FFF2
    { 0x4C, 0x81 },
    { 0x4D, 0xE6 },
    { 0x4E, 0xF2 },
    { 0x4F, 0xFF },
    { 0x50, 0xF8 },
    { 0x51, 0x7F },

    // CDirectSound_CreateSoundBuffer+0x9C : retn 0x10
    { 0x9C, 0xC2 },
    { 0x9D, 0x10 },
    //
);

// ******************************************************************
// * CDirectSound_DoWork
// ******************************************************************
OOVPA_XREF(CDirectSound_DoWork,
           4039,
           1 + 9,
           XRefOne)
    {

        // CDirectSound_DoWork+0x18 : call [CMcpxAPU::ServiceDeferredCommandsLow]
        XREF_ENTRY(0x19, XREF_CMcpxAPU_ServiceDeferredCommandsLow),

            // CDirectSound_DoWork+0x0D : mov esi, eax
            { 0x0D, 0x8B },
            { 0x0E, 0xF0 },

            // CDirectSound_DoWork+0x0F : jnz +0x0C
            { 0x0F, 0x75 },
            { 0x10, 0x0C },

#if 0 // disabled to reduce scan size
    
    // CDirectSound_DoWork+0x11 : mov eax, [esp+4+arg_0]
    { 0x11, 0x8B },
    { 0x12, 0x44 },
    { 0x13, 0x24 },
    { 0x14, 0x08 },
#endif

            // CDirectSound_DoWork+0x15 : mov ecx, [eax+0Ch]
            { 0x15, 0x8B },
            { 0x16, 0x48 },
            { 0x17, 0x0C },

            // CDirectSound_DoWork+0x24 : retn 0x04
            { 0x2D, 0xC2 },
            { 0x2E, 0x04 },
    }
OOVPA_END;

// ******************************************************************
// * CDirectSoundBuffer::SetLoopRegion
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetLoopRegion,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetLoopRegion+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetLoopRegion+0x23 : mov eax, 0x80004005
    { 0x23, 0xB8 }, // Was 4134 Offset -0x01h
    { 0x24, 0x05 },
    { 0x25, 0x40 },
    { 0x26, 0x00 },
    { 0x27, 0x80 },

    // CDirectSoundBuffer_SetLoopRegion+0x3C : lea ebx, [esi+ecx]
    { 0x3C, 0x8D },
    { 0x3D, 0x1C },
    { 0x3E, 0x0E },

    // CDirectSoundBuffer_SetLoopRegion+0x3F : cmp ebx, [eax+148h]
    { 0x3F, 0x3B }, // Was 4134 Offset 0x40 cmp ebx, [eax+0C4h]
    { 0x40, 0x98 },

    // CDirectSoundBuffer_SetLoopRegion+0x5D : mov [eax+150h], ecx
    { 0x61, 0x00 },
    { 0x62, 0x00 },

    // CDirectSoundBuffer_SetLoopRegion+0x63 : mov ecx, [edx+20h]
    { 0x63, 0x8B },
    { 0x64, 0x4A },
    { 0x65, 0x20 },

    // CDirectSoundBuffer_SetLoopRegion+0x66 : call CMcpxBuffer_SetLoopRegion
    { 0x66, 0xE8 },
    //
);

// ******************************************************************
// * CDirectSound::SetDistanceFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDistanceFactor,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDistanceFactor+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSound_SetDistanceFactor+0x32 : mov [eax+48h], edx
    { 0x32, 0x89 },
    { 0x33, 0x50 },
    { 0x34, 0x48 }, // Value is CDirectSound_SetDistanceFactor +0x00h

    // CDirectSound_SetDistanceFactor+0x35 : mov eax, [ecx+8]
    { 0x35, 0x8B },
    { 0x36, 0x41 },
    { 0x37, 0x08 },

    // CDirectSound_SetDistanceFactor+0x38 : or dword ptr [eax+84h], 60h
    { 0x38, 0x83 },
    { 0x39, 0x88 },
    { 0x3A, 0x84 }, // 4039 0x84 vs 4134 0xA4
    { 0x3E, 0x60 },

    // CDirectSound_SetDistanceFactor+0x4E : jz +0x0B
    { 0x4E, 0x74 },
    { 0x4F, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::SetRolloffFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetRolloffFactor,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetRolloffFactor+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSound_SetRolloffFactor+0x33 : mov [eax+4Ch], edx
    { 0x32, 0x89 },
    { 0x33, 0x50 },
    { 0x34, 0x4C }, // Value is CDirectSound_SetDistanceFactor +0x04h

    // CDirectSound_SetRolloffFactor+0x36 : mov eax, [ecx+8]
    { 0x35, 0x8B },
    { 0x36, 0x41 },
    { 0x37, 0x08 },

    // CDirectSound_SetRolloffFactor+0x39 : or dword ptr[eax+0x84], 0x04
    { 0x38, 0x83 },
    { 0x39, 0x88 },
    { 0x3A, 0x84 }, // 4039 0x84 vs 4134 0xA4
    { 0x3E, 0x04 },

    // CDirectSound_SetRolloffFactor+0x4E : jz +0x0B
    { 0x4E, 0x74 },
    { 0x4F, 0x0B },
    //
);

// ******************************************************************
// * CDirectSound::SetDopplerFactor
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetDopplerFactor,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetDopplerFactor+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSound_SetDopplerFactor+0x32 : mov [eax+0x50], edx
    { 0x32, 0x89 },
    { 0x33, 0x50 },
    { 0x34, 0x50 }, // Value is CDirectSound_SetDistanceFactor+ 0x08

    // CDirectSound_SetDopplerFactor+0x38 : or dword ptr[eax+0x84], 0x40
    { 0x38, 0x83 },
    { 0x39, 0x88 },
    { 0x3A, 0x84 }, // 4039 0x84 vs 4134 0xA4
    { 0x3E, 0x40 },

    // CDirectSound_SetDopplerFactor+0x4E : jz +0x0B
    { 0x4E, 0x74 },
    { 0x4F, 0x0B },
    //
);

// ******************************************************************
// * CMcpxVoiceClient_SetVolume
// ******************************************************************
// Verified with Agent Under Fire title.
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetVolume,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetVolume+0x15 : test byte ptr [esi+90h], 1
    { 0x15, 0xF6 },
    { 0x16, 0x86 },
    { 0x17, 0x90 },
    { 0x18, 0x00 },
    { 0x19, 0x00 },
    { 0x1A, 0x00 },
    { 0x1B, 0x01 },

    // CMcpxVoiceClient_SetVolume+0x1C : jz +0x75
    { 0x1C, 0x74 },
    { 0x1D, 0x75 },

    // CMcpxVoiceClient_SetVolume+0x73 : mov edx, [ebp+eax*4-0x14]
    { 0x73, 0x8B }, // Was 4134 Offset -0x07h
    { 0x74, 0x54 },
    { 0x75, 0x85 },
    { 0x76, 0xEC },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetVolume
// ******************************************************************
// Verified with Agent Under Fire.
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetVolume+0x15 : call [CMcpxVoiceClient::SetVolume]
    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetVolume),

    // CDirectSoundVoice_SetVolume+0x04 : mov eax, [ecx+10h]
    { 0x04, 0x8B },
    { 0x05, 0x41 },
    { 0x06, 0x10 },

    // CDirectSoundVoice_SetVolume+0x07 : mov edx, [esp+arg_4]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },

    // CDirectSoundVoice_SetVolume+0x0B : sub edx, [eax+28h]
    { 0x0B, 0x2B },
    { 0x0C, 0x50 },
    { 0x0D, 0x28 }, // 4039 0x28 vs 4134 0x20

    // CDirectSoundVoice_SetVolume+0x19 : retn 8
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetVolume
// ******************************************************************
// Verified with Agent Under Fire.
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetVolume+0x31 : call [CMcpxVoiceClient::SetVolume]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetVolume), // Was 4134 Offset -0x01h

    // CDirectSoundBuffer_SetVolume+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetVolume+0x25 : jmp +0x22
    { 0x25, 0xEB },
    { 0x26, 0x22 },

    // CDirectSoundBuffer_SetVolume+0x2C : push [esp+0x10]
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetVolume+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer::SetVolume
// ******************************************************************
// Generic OOVPA as of 4039 and newer
// Verified with Agent Under Fire.
// Side note: It is compatible down to XDK 3911. Except 3911 is calling to CDirectSoundVoice_SetVolume directly.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetVolume),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0x83 },
    { 0x0E, 0xD9 },
    { 0x12, 0xC8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetVolume), // Was 4134 Offset -0x01h

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },
    { 0x4A, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetHeadroom
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetHeadroom,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetHeadroom+0x1A : call [CMcpxVoiceClient::SetVolume]
    XREF_ENTRY(0x1B, XREF_CMcpxVoiceClient_SetVolume),

    // CDirectSoundVoice::SetHeadroom+0x00 : mov edx,[esp+0x04]
    { 0x00, 0x8B },
    { 0x01, 0x54 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    //{ 0x13, 0x24 }, // 4039 0x24 vs 4134 0x1C

    // CDirectSoundVoice::SetHeadroom+0x14 : mov [eax+0x28],esi
    { 0x14, 0x89 },
    { 0x15, 0x70 },
    //{ 0x16, 0x28 }, // 4039 0x28 vs 4134 0x20

    // CDirectSoundVoice::SetHeadroom+0x1A : mov ecx,[edx+0x0C]
    { 0x17, 0x8B },
    { 0x18, 0x4A },
    { 0x19, 0x0C },

    // CDirectSoundVoice::SetHeadroom+0x1A : call [CMcpxVoiceClient::SetVolume]
    { 0x1A, 0xE8 },

    { 0x20, 0xC2 },
    { 0x21, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetHeadroom,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetHeadroom), // Was 4134 Offset -0x01h

    { 0x00, 0x56 },
    { 0x11, 0x85 },
    { 0x1B, 0x15 },
    { 0x25, 0xEB },
    { 0x2F, 0x10 },
    { 0x39, 0x74 },
    { 0x46, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetBufferData
// ******************************************************************
// Verified with Agent Under Fire.
OOVPA_XREF(CDirectSoundBuffer_SetBufferData,
           4039,
           2 + 11,
           XRefTwo)
    {

        // CDirectSoundBuffer::SetBufferData+0x76 : call [CDirectSoundBufferSettings::SetBufferData]
        XREF_ENTRY(0x77, XREF_CDirectSoundBufferSettings_SetBufferData),

            // CDirectSoundBuffer::SetBufferData+0x8A : call [CMcpxBuffer::SetBufferData]
            XREF_ENTRY(0x8B, XREF_CMcpxBuffer_SetBufferData),

            // CDirectSoundBuffer::SetBufferData+0x00 : push ebp
            { 0x00, 0x55 },

            // CDirectSoundBuffer::SetBufferData+0x3D : mov eax, 0x80004005
            { 0x3D, 0xB8 }, // Was 4134 Offset -0x03h
            { 0x3E, 0x05 },
            { 0x3F, 0x40 },
            { 0x40, 0x00 },
            { 0x41, 0x80 },

            // CDirectSoundBuffer::SetBufferData+0x48 : mov eax, [esi+1Ch]
            { 0x48, 0x8B },
            { 0x49, 0x46 },
            { 0x4A, 0x1C },

#if 0
        // CDirectSoundBuffer::SetBufferData+0x4B : cmp  ebx, [eax+13Ch]
        { 0x4B, 0x3B },
        { 0x4C, 0x98 },
        { 0x4D, 0x3C },
        { 0x4E, 0x01 },
        { 0x4F, 0x00 },
        { 0x50, 0x00 },
#endif

            // CDirectSoundBuffer::SetBufferData+0xA8 : retn 0xC
            { 0xA8, 0xC2 },
            { 0xA9, 0x0C },
    }
OOVPA_END;

// ******************************************************************
// * CDirectSoundVoice::SetPitch
// ******************************************************************
// Generic OOVPA as of 4039 and newer
// Verified with Agent Under Fire.
// Same as 4134
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetPitch,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetPitch+0x11 : call [CMcpxVoiceClient::SetPitch]
    XREF_ENTRY(0x12, XREF_CMcpxVoiceClient_SetPitch),

    { 0x02, 0x24 },

    { 0x06, 0x10 },

    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },

    { 0x0B, 0x89 },
    { 0x0C, 0x51 },
    //{ 0x0D, 0x18 }, // 4039 0x20 vs 4134 0x18

    { 0x0E, 0x8B },

    { 0x16, 0xC2 },
    { 0x17, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetPitch,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetPitch+0x31 : call [CDirectSoundVoice::SetPitch]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetPitch), // Was 4134 Offset -0x01h

    // CDirectSoundBuffer_SetPitch+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetPitch+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetPitch+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetPitch+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetPitch
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetPitch,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetPitch+0x15 : call [CDirectSoundBuffer_SetPitch]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetPitch),

    // IDirectSoundBuffer_SetPitch+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetPitch+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetPitch+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetFrequency
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetFrequency,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetFrequency+0x14 : call [XAudioCalcatePitch]
    XREF_ENTRY(0x15, XREF_XAudioCalculatePitch),

    // CDirectSoundVoice_SetFrequency+0x1B : call [CDirectSoundVoice::SetPitch]
    XREF_ENTRY(0x1C, XREF_CDirectSoundVoice_SetPitch),

    // CDirectSoundVoice_SetFrequency+0x00 : mov eax, [esp+0x08]
    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x08),

    // CDirectSoundVoice_SetFrequency+0x22 : retn 0x08
    OV_MATCH(0x21, 0xC2, 0x08),
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetFrequency
// ******************************************************************
// Verified with Agent Under Fire.
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFrequency,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetFrequency+0x31 : call [CDirectSoundVoice::SetFrequency]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetFrequency), // Was 4134 Offset -0x01

    // CDirectSoundBuffer_SetFrequency+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetFrequency+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetFrequency+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetFrequency+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetFrequency
// ******************************************************************
// Generic OOVPA as of 4039 and newer
// Verified with Agent Under Fire.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetFrequency,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetFrequency+0x15 : call [CDirectSound::SetFrequency]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetFrequency),

    // IDirectSoundBuffer_SetFrequency+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetFrequency0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetFrequency+0x0F : sbb ecx, ecx
    { 0x0F, 0x1B },
    { 0x10, 0xC9 },

    // IDirectSoundBuffer_SetFrequency+0x11 : and ecx, eax
    { 0x11, 0x23 },
    { 0x12, 0xC8 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Stop
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_Stop,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_Stop+0x33 : call [CMcpxBuffer::Stop]
    //XREF_ENTRY( 0x30, XREF_CMcpxBuffer_Stop), //TODO: is this CMcpxBuffer::Stop or something else?

    // CDirectSoundBuffer_Stop+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_Stop+0x2B : mov ecx,[eax+20]
    { 0x2B, 0x8B },
    { 0x2C, 0x48 },
    { 0x2D, 0x20 },

    // CDirectSoundBuffer_Stop+0x38 : jz +0x0B
    { 0x38, 0x74 },
    { 0x39, 0x0B },

    // CDirectSoundBuffer_Stop+0x49 : retn 0x04
    { 0x49, 0xC2 },
    { 0x4A, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound::CommitDeferredSettings
// ******************************************************************
// Verified with Agent Under Fire.
OOVPA_SIG_HEADER_XREF(CDirectSound_CommitDeferredSettings,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound_CommitDeferredSettings+0x44 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x45, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSound_CommitDeferredSettings+0x00 : push    ebp
    { 0x00, 0x55 },

    // CDirectSound_CommitDeferredSettings+0x24 : mov eax, 0x80004005
    { 0x24, 0xB8 }, // Was 4134 Offset -0x03h
    { 0x25, 0x05 },
    { 0x26, 0x40 },
    { 0x27, 0x00 },
    { 0x28, 0x80 },

    // CDirectSound_CommitDeferredSettings+0x52 : and dword ptr [eax+84h], 0
    { 0x52, 0x83 },
    { 0x53, 0xA0 },
    { 0x54, 0x84 },
    { 0x55, 0x00 },
    { 0x56, 0x00 },
    //{ 0x57, 0x00 },
    //{ 0x58, 0x00 },

    // CDirectSound_CommitDeferredSettings+0x78 : leave
    { 0x6F, 0xC9 },
    //
);

// ******************************************************************
// * CMcpxBuffer::Play(unsigned long)
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_Play,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Play+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxBuffer_Play+0x0E : cmp eax, ebx
    { 0x14, 0x3B },
    { 0x15, 0xC3 },

    // CMcpxBuffer_Play+0x25 : test byte ptr [eax+9], 20h
    { 0x25, 0xF6 },
    { 0x26, 0x40 },
    { 0x27, 0x09 },
    { 0x28, 0x20 },

    // CMcpxBuffer_Play+0x29 : jz +0x0C
    { 0x29, 0x74 },
    { 0x2A, 0x0C },

    // CMcpxBuffer_Play+0x3F : test [ebp+arg_0], 2
    { 0x3F, 0xF6 },
    { 0x40, 0x45 },
    { 0x41, 0x08 },
    { 0x42, 0x02 },
    //
);

// ******************************************************************
// * CMcpxBuffer::Play(__int64,unsigned long)
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(CMcpxBuffer_Play_Ex,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_Play_Ex+0x2B : call [CMcpxBuffer::Play]
    XREF_ENTRY(0x2B, XREF_CMcpxBuffer_Play),

    // CMcpxBuffer_Play_Ex+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxBuffer_Play_Ex+0x11 : push [ebp+arg_8]
    { 0x11, 0xFF },
    { 0x12, 0x75 },
    { 0x13, 0x10 },

    // CMcpxBuffer_Play_Ex+0x23 : jnz +0x0C
    { 0x23, 0x75 },
    { 0x24, 0x0C },

    // CMcpxBuffer_Play_Ex+0x36 : push esi
    { 0x36, 0xC2 },
    { 0x37, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::Play
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_Play,
                         4039)
OOVPA_SIG_MATCH(

    //CDirectSoundBuffer_Play+0x00 : push esi
    { 0x00, 0x56 },

    //CDirectSoundBuffer_Play+0x20 : mov eax, 80004005h
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    //CDirectSoundBuffer_Play+0x2F : mov ecx, dword ptr [esp+18h]
    { 0x2F, 0xFF },
    { 0x30, 0x74 },
    { 0x31, 0x24 },
    { 0x32, 0x18 },

    //CDirectSoundBuffer_Play+0x4D : ret 10h
    { 0x4D, 0xC2 },
    { 0x4E, 0x10 },
    { 0x4F, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::PlayEx
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_PlayEx,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3C, XREF_CMcpxBuffer_Play_Ex),

    { 0x00, 0x56 },
    { 0x15, 0x68 },
    { 0x20, 0xB8 },
    { 0x2D, 0x20 },
    { 0x39, 0x24 },
    { 0x45, 0x0B },
    { 0x51, 0x8B },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_GetCurrentPosition,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_GetCurrentPosition+0x16 : mov eax, [esi+0x00000090]
    { 0x16, 0x8B },
    { 0x17, 0x86 },
    { 0x18, 0x90 },
    { 0x19, 0x00 },
    //{ 0x1A, 0x00 },
    //{ 0x1B, 0x00 },

    // CMcpxBuffer_GetCurrentPosition+0x21 : jnz +0x00000088
    { 0x21, 0x0F },
    { 0x22, 0x85 },
    { 0x23, 0x88 },
    { 0x24, 0x00 },
    //{ 0x25, 0x00 },
    //{ 0x26, 0x00 },

    // CMcpxBuffer_GetCurrentPosition+0x8E : div dword ptr [ecx+0x00000140]
    { 0xA5, 0xF7 },
    { 0xA6, 0xB1 },
    { 0xA7, 0x40 },
    { 0xA8, 0x01 },
    { 0xA9, 0x00 },
    { 0xAA, 0x00 },

    // CMcpxBuffer_GetCurrentPosition+0xC8 : retn 0x08
    { 0xDB, 0xC2 },
    { 0xDC, 0x08 },
    { 0xDD, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetCurrentPosition,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_GetCurrentPosition+0x38 : call [CMcpxBuffer::GetCurrentPosition]
    XREF_ENTRY(0x38, XREF_CMcpxBuffer_GetCurrentPosition),
    // CDirectSoundBuffer_GetCurrentPosition+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_GetCurrentPosition+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_GetCurrentPosition+0x40 : jz +0x0B
    { 0x40, 0x74 },
    { 0x41, 0x0B },

    // CDirectSoundBuffer_GetCurrentPosition+0x51 : retn 0x08
    { 0x51, 0xC2 },
    { 0x52, 0x0C },
    //
);

// ******************************************************************
// * CMcpxBuffer_GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_GetStatus,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_GetStatus+0x14 : mov ecx, [ebp+0x08]
    { 0x14, 0x8B },
    { 0x15, 0x4D },
    { 0x16, 0x08 },

    // CMcpxBuffer_GetStatus+0x1A : xor edx, edx
    { 0x1A, 0x33 },
    { 0x1B, 0xD2 },

    // CMcpxBuffer_GetStatus+0x22 : inc edx
    { 0x22, 0x42 },

    // CMcpxBuffer_GetStatus+0x1C : jz +0x17
    { 0x26, 0x74 },
    { 0x27, 0x15 },

    // CMcpxBuffer_GetStatus+0x2F : mov [ecx], 5
    { 0x37, 0xC7 },
    { 0x38, 0x01 },
    { 0x39, 0x05 },

    // CMcpxBuffer_GetStatus+0x48 : retn 0x04
    { 0x48, 0xC2 },
    { 0x49, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_GetStatus,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_GetStatus+0x14 : call [CMcpxBuffer::GetStatus]
    XREF_ENTRY(0x34, XREF_CMcpxBuffer_GetStatus),

    // CDirectSoundBuffer_GetStatus+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_GetStatus+0x2B : mov ecx, [eax+0x20]
    { 0x2B, 0x8B },
    { 0x2C, 0x48 },
    { 0x2D, 0x20 },

    // CDirectSoundBuffer_GetStatus+0x2F : push [esp+0x10]
    { 0x2F, 0xFF },
    { 0x30, 0x74 },
    { 0x31, 0x24 },
    { 0x32, 0x10 },

    // CDirectSoundBuffer_GetStatus+0x4D : retn 0x08
    { 0x4D, 0xC2 },
    { 0x4E, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_Lock
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_Lock,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x45, XREF_CDirectSoundBuffer_GetCurrentPosition),

    // CDirectSoundBuffer_Lock+0x34 : test [ebp+0x24], 1
    { 0x34, 0xF6 },
    { 0x35, 0x45 },
    { 0x36, 0x24 },
    { 0x37, 0x01 },

    // CDirectSoundBuffer_Lock+0x59 : mov eax, [eax+0x140]
    { 0x59, 0x8B },
    { 0x5A, 0x80 },
    { 0x5B, 0x40 },
    { 0x5C, 0x01 },

    // CDirectSoundBuffer_Lock+0x9F : jnb +0x11; mov esi, [esi+0x1C]
    { 0x9F, 0x73 },
    { 0xA0, 0x11 },
    { 0xA1, 0x8B },
    { 0xA2, 0x76 },
    { 0xA3, 0x1C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPlayRegion
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetPlayRegion,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x18, 0x68 },
    { 0x23, 0xB8 },

    { 0x37, 0x14 },
    { 0x38, 0x8B },
    { 0x39, 0x75 },
    { 0x3A, 0x0C },
    { 0x3B, 0x03 },
    { 0x3C, 0xF0 },
    { 0x3D, 0x3B },
    { 0x3E, 0xB1 },

    { 0x7C, 0xC2 },
    { 0x7D, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetPlayRegion
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetPlayRegion,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetPlayRegion+0x19 : call [CDirectSoundBuffer_SetPlayRegion]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetPlayRegion),

    // IDirectSoundBuffer_SetPlayRegion+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetPlayRegion+0x0E : add eax, 0xFFFFFFE4
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_SetPlayRegion+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CMcpxBuffer_SetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxBuffer_SetCurrentPosition,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxBuffer_SetCurrentPosition+0x11 : lea eax, [esi+90h]
    { 0x11, 0x8D },
    { 0x12, 0x86 },
    { 0x13, 0x90 },

    // CMcpxBuffer_SetCurrentPosition+0x43 : jb +0x10
    { 0x43, 0x72 },
    { 0x44, 0x10 },

    // CMcpxBuffer_SetCurrentPosition+0x86 : mov eax, [esi+0E4h]
    { 0x6A, 0x8B },
    { 0x6B, 0x86 },
    { 0x6C, 0xE4 },
    { 0x6D, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetCurrentPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetCurrentPosition,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetCurrentPosition+0x34 : call [CMcpxBuffer::SetCurrentPosition]
    XREF_ENTRY(0x34, XREF_CMcpxBuffer_SetCurrentPosition),

    // CDirectSoundBuffer_SetCurrentPosition+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetCurrentPosition+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetCurrentPosition+0x3C : jz +0x0B
    { 0x3C, 0x74 },
    { 0x3D, 0x0B },

    // CDirectSoundBuffer_SetCurrentPosition+0x4D : retn 0x08
    { 0x4D, 0xC2 },
    { 0x4E, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CMcpxVoiceClient::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetFilter,
                         4039)
OOVPA_SIG_MATCH(

    { 0x08, 0xF8 },
    { 0x12, 0xE8 },

    { 0x20, 0x00 },
    { 0x21, 0x74 },
    { 0x22, 0x13 },
    { 0x23, 0x6A },
    { 0x24, 0x06 },
    { 0x25, 0x59 },
    { 0x26, 0x8D },
    { 0x27, 0x7D },

    { 0x47, 0x83 },
    { 0x4D, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetFilter,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_CMcpxVoiceClient_SetFilter),

    { 0x01, 0x44 },
    { 0x04, 0xFF },
    { 0x07, 0x08 },
    { 0x0A, 0x0C },
    { 0x10, 0xC2 },
    { 0x11, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFilter,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetFilter),

    { 0x00, 0x56 },
    { 0x11, 0x85 },
    { 0x1B, 0x15 },
    { 0x25, 0xEB },
    { 0x2F, 0x10 },
    { 0x39, 0x74 },
    { 0x46, 0x8B },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetFilter
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetFilter,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetFilter+0x15 : call [CDirectSoundBuffer_SetFilter]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetFilter),

    // IDirectSoundBuffer_SetFilter+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetFilter+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetFilter+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetFilter
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetFilter,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetFilter),

    { 0x00, 0x56 }, //Prevent incorrect offset difference from 4134 and later revision.

    { 0x0B, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },
    { 0x4A, 0x8B },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetMixBins
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetMixBins,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxVoiceClient_SetMixBins+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxVoiceClient_SetMixBins+0x24 : test byte ptr [esi+90h], 1
    { 0x17, 0xF6 },
    { 0x18, 0x86 },
    { 0x19, 0x90 },
    { 0x1A, 0x00 },
    { 0x1B, 0x00 },
    { 0x1C, 0x00 },
    { 0x1D, 0x01 },

    // CMcpxVoiceClient_SetMixBins+0x1E : jz
    { 0x1E, 0x0F },
    { 0x1F, 0x84 },
    { 0x20, 0x98 },
    { 0x21, 0x00 },
    { 0x22, 0x00 },
    { 0x23, 0x00 },

    // CMcpxVoiceClient_SetMixBins+0x66 : mov ds:[0xFE8202F8], eax
    { 0x66, 0xA3 },
    { 0x67, 0xF8 },
    { 0x68, 0x02 },
    { 0x69, 0x82 },
    { 0x6A, 0xFE },

    // CMcpxVoiceClient_SetMixBins+0xC8 : leave; retn
    { 0xC8, 0xC9 },
    { 0xC9, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMixBins
// ******************************************************************
// Generic OOVPA as of 4039 and newer
// TODO: Maybe able to reduce pairs and include another XREF.
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMixBins,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMixBins+0x0D : call [CDirectSoundVoiceSettings::SetMixBins]
    //XREF_ENTRY( 0x0D, XREF_CDirectSoundVoiceSettings_SetMixBins ),

    // CDirectSoundVoice_SetMixBins+0x15 : call [CMcpxVoiceClient::SetMixBins]
    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetMixBins),

    // CDirectSoundVoice_SetMixBins+0x01 : mov esi, [esp+8]
    { 0x01, 0x8B },
    { 0x02, 0x74 },
    { 0x03, 0x24 },
    { 0x04, 0x08 },

    // CDirectSoundVoice_SetMixBins+0x05 : push [esp+0x0C]
    { 0x05, 0xFF },
    { 0x06, 0x74 },
    { 0x07, 0x24 },
    { 0x08, 0x0C },

    // CDirectSoundVoice_SetMixBins+0x09 : mov ecx, [esi+0x10]
    { 0x09, 0x8B },
    { 0x0A, 0x4E },
    { 0x0B, 0x10 },

    // CDirectSoundVoice_SetMixBins+0x11 : mov ecx, [esi+0x0C]
    { 0x11, 0x8B },
    { 0x12, 0x4E },
    { 0x13, 0x0C },

    // CDirectSoundVoice_SetMixBins+0x1A : retn 0x08
    { 0x1A, 0xC2 },
    { 0x1B, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMixBins
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMixBins,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMixBins+0x31 : call [CDirectSoundVoice::SetMixBins]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetMixBins),

    // CDirectSoundBuffer_SetMixBins+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMixBins+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetMixBins+0x29 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetMixBins+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetMixBins+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMixBins
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMixBins,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetMixBins+0x14 : call [CDirectSoundVoice::SetMixBins]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetMixBins),

    // IDirectSoundBuffer_SetMixBins+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetMixBins+0x0F : sbb ecx, ecx
    { 0x0F, 0x1B },
    { 0x10, 0xC9 },

    // IDirectSoundBuffer_SetMixBins+0x11 : and ecx, eax
    { 0x11, 0x23 },
    { 0x12, 0xC8 },
    //
);

// ******************************************************************
// * CDirectSoundVoiceSettings::SetMixBinVolumes
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoiceSettings_SetMixBinVolumes,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x09 : jbe +0x16
    { 0x09, 0x76 },
    { 0x0A, 0x16 },

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x18 : mov [ecx+edi*4+0x50], eax
    { 0x18, 0x89 },
    { 0x19, 0x44 },
    { 0x1A, 0xB9 },
    { 0x1B, 0x50 }, // 4039 0x50 vs 4134 0x30

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x1E : jb +0xEC
    { 0x1E, 0x72 },
    { 0x1F, 0xEC },

    // CDirectSoundVoiceSettings_SetMixBinVolumes+0x22 : retn 0x04
    { 0x22, 0xC2 },
    { 0x23, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMixBinVolumes
// ******************************************************************
// Generic OOVPA as of 4039 and newer.
// TODO: Should be able to reduce pairs since there are two XREFs.
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMixBinVolumes_8,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMixBinVolumes+0x0D : call [CDirectSoundVoiceSettings::SetMixBinVolumes]
    XREF_ENTRY(0x0D, XREF_CDirectSoundVoiceSettings_SetMixBinVolumes),

    // CDirectSoundVoice_SetMixBinVolumes+0x14 : call [CMcpxVoiceClient::SetVolume]
    XREF_ENTRY(0x15, XREF_CMcpxVoiceClient_SetVolume),

    // CDirectSoundVoice_SetMixBinVolumes+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundVoice_SetMixBinVolumes+0x05 : push [esp+0x0C]
    { 0x05, 0xFF },
    { 0x06, 0x74 },
    { 0x07, 0x24 },
    { 0x08, 0x0C },

    // CDirectSoundVoice_SetMixBinVolumes+0x09 : mov ecx, [esi+0x10]
    { 0x09, 0x8B },
    { 0x0A, 0x4E },
    { 0x0B, 0x10 },

    // CDirectSoundVoice_SetMixBinVolumes+0x11 : mov ecx, [esi+0x0C]
    { 0x11, 0x8B },
    { 0x12, 0x4E },
    { 0x13, 0x0C },

    // CDirectSoundVoice_SetMixBinVolumes+0x1A : retn 0x08
    { 0x1A, 0xC2 },
    { 0x1B, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMixBinVolumes
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMixBinVolumes_8,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMixBinVolumes+0x31 : call [CDirectSoundVoice::SetMixBinVolumes]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetMixBinVolumes),

    // CDirectSoundBuffer_SetMixBinVolumes+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMixBinVolumes+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetMixBinVolumes+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetMixBinVolumes+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetMixBinVolumes+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMixBinVolumes_8
// ******************************************************************
//Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMixBinVolumes_8,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetMixBinVolumes_8+0x15 : call [CDirectSoundBuffer::SetMixBinVolumes]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetMixBinVolumes),

    // IDirectSoundBuffer_SetMixBinVolumes_8+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetMixBinVolumes_8+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetMixBinVolumes_8+0x0F : sbb ecx, ecx
    { 0x0F, 0x1B },
    { 0x10, 0xC9 },

    // IDirectSoundBuffer_SetMixBinVolumes_8+0x11 : and ecx, eax
    { 0x11, 0x23 },
    { 0x12, 0xC8 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMixBinVolumes_8
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMixBinVolumes_8,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetMixBinVolumes),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x0D, 0x8B },
    { 0x0E, 0xF0 },
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound::CreateSoundStream
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CreateSoundStream,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_CreateSoundStream+0x25 : mov eax, 0x80004005
    { 0x25, 0xB8 },

    // CDirectSound_CreateSoundStream+0x2A : jmp 0x62
    { 0x2A, 0xEB },
    { 0x2B, 0x62 },

    // CDirectSound_CreateSoundStream+0x2C : push 0x1
    { 0x2C, 0x6A },
    { 0x2D, 0x01 },

    // CDirectSound_CreateSoundStream+0x2E : push 0x28
    { 0x2E, 0x6A },
    { 0x2F, 0x28 },

    // CDirectSound_CreateSoundStream+0x4A : add esi, 0x7FF8FFF2
    { 0x4C, 0x81 },
    { 0x4D, 0xE6 },
    { 0x4E, 0xF2 },
    { 0x4F, 0xFF },
    { 0x50, 0xF8 },
    { 0x51, 0x7F },

    // CDirectSound_CreateSoundStream+0x91 : retn 0x10
    { 0x91, 0xC2 },
    { 0x92, 0x10 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_StopEx
// ******************************************************************
// Similar pattern of version 3911
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_StopEx,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x23, 0xB8 },

    { 0x49, 0xEB },
    { 0x4A, 0x11 },
    { 0x4B, 0xFF },
    { 0x4C, 0x75 },
    { 0x4D, 0x10 },
    { 0x4E, 0x8B },
    { 0x4F, 0x45 },
    { 0x50, 0x08 },

    { 0x72, 0xC2 },
    { 0x73, 0x10 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetLFO
// ******************************************************************
// Similar pattern of version 3911
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetLFO,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x25, 0xEB },

    { 0x57, 0x72 },
    { 0x58, 0xF3 },
    { 0x59, 0x33 },
    { 0x5A, 0xC0 },
    { 0x5B, 0x85 },
    { 0x5C, 0xC9 },
    { 0x5D, 0x76 },
    { 0x5E, 0x62 },
    { 0x5F, 0x8B },

    { 0xCD, 0xC2 },
    { 0xCE, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetLFO,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_CMcpxVoiceClient_SetLFO),

    { 0x01, 0x44 },
    { 0x04, 0xFF },
    { 0x07, 0x08 },
    { 0x0A, 0x0C },

    { 0x10, 0xC2 },
    { 0x11, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetLFO,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetLFO+0x31 : call [CDirectSoundVoice_SetLFO]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetLFO),

    // CDirectSoundBuffer_SetLFO+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetLFO+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetLFO+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetLFO+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetLFO+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetLFO
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetLFO,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetLFO),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0x83 },
    { 0x0E, 0xD9 },
    { 0x12, 0xC8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetLFO
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetLFO,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetLFO),

    { 0x00, 0x56 }, //Prevent incorrect offset difference from 4134 and later revision.

    { 0x0B, 0x00 },
    { 0x0E, 0xF0 },
    { 0x11, 0x85 },
    { 0x14, 0x0B },
    { 0x39, 0x85 },
    { 0x3C, 0xF8 },
    { 0x3F, 0x68 },
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * CMcpxVoiceClient::SetEG
// ******************************************************************
// Similar pattern of version 3911
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetEG,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x25, 0xEB },

    { 0x3C, 0x84 },
    { 0x3D, 0x86 },
    { 0x3E, 0x00 },
    { 0x3F, 0x00 },
    { 0x40, 0x00 },
    { 0x41, 0x8B },
    { 0x42, 0x86 },
    { 0x43, 0xE4 },

    { 0xD3, 0xC2 },
    { 0xD4, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetEG,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x0C, XREF_CMcpxVoiceClient_SetEG),

    { 0x01, 0x44 },
    { 0x04, 0xFF },
    { 0x07, 0x08 },
    { 0x0A, 0x0C },
    { 0x10, 0xC2 },
    { 0x11, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetEG,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetEG+0x31 : call [CDirectSoundVoice_SetEG]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetEG),

    // CDirectSoundBuffer_SetEG+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetEG+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetEG+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetEG+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetEG+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetEG,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetEG),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0x83 },
    { 0x0E, 0xD9 },
    { 0x12, 0xC8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetEG
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetEG,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetEG),

    { 0x00, 0x56 }, //Prevent incorrect offset difference from 4134 and later revision.

    { 0x0B, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },
    { 0x4A, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetOutputBuffer
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetOutputBuffer,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },

    { 0x10, 0x24 },
    { 0x11, 0x10 },

    // CDirectSoundVoice::SetOutputBuffer+0x12 : and esi,eax
    { 0x12, 0x23 },
    { 0x13, 0xF0 },

    // CDirectSoundVoice::SetOutputBuffer+0x14 : mov eax,[edi+0x10]
    { 0x14, 0x8B },
    { 0x15, 0x47 },
    { 0x16, 0x10 },

    // CDirectSoundVoice::SetOutputBuffer+0x17 : mov eax,[eax+0x________]
    { 0x17, 0x8B },
    { 0x18, 0x80 },

    // CDirectSoundVoice::SetOutputBuffer+0x45 : call [?]
    { 0x45, 0xE8 },

    // CDirectSoundVoice::SetOutputBuffer+0x51 : ret 0x0008
    { 0x51, 0xC2 },
    { 0x52, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetOutputBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetOutputBuffer,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetOutputBuffer+0x30 : call [XREF_CDirectSoundVoice_SetOutputBuffer]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetOutputBuffer),

    // CDirectSoundBuffer_SetOutputBuffer+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetOutputBuffer+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetOutputBuffer+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetOutputBuffer+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetOutputBuffer+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeOutsideVolume,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetConeOutsideVolume+0x07 : mov edx, [esp+arg_4]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x11 : mov [eax+104h], edx
    { 0x0B, 0x89 },
    { 0x0C, 0x90 },
    { 0x0D, 0x04 },
    { 0x0E, 0x01 },
    { 0x0F, 0x00 },
    { 0x10, 0x00 },

    { 0x11, 0x8B },
    { 0x14, 0x83 },
    { 0x1A, 0x10 },

    // CDirectSoundVoice_SetConeOutsideVolume+0x2A : retn 0Ch
    { 0x2A, 0xC2 },
    { 0x2B, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeOutsideVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetConeOutsideVolume+0x35 : call [CDirectSoundVoice::SetConeOutsideVolume]
    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    // CDirectSoundBuffer_SetConeOutsideVolume+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetConeOutsideVolume+0x21 : mov eax, 80004005h
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetConeOutsideVolume+0x30 : push [esp+0Ch+arg_0]
    { 0x30, 0xFF },
    { 0x31, 0x74 },
    { 0x32, 0x24 },
    { 0x33, 0x14 },

    // CDirectSoundBuffer_SetConeOutsideVolume+0x4E : retn 0Ch
    { 0x4E, 0xC2 },
    { 0x4F, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetConeOutsideVolume
// ******************************************************************
// Generic OOVPA as of 4039 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetConeOutsideVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetConeOutsideVolume+0x18 : call [CDirectSoundBuffer_SetConeOutsideVolume]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetConeOutsideVolume),

    // IDirectSoundBuffer_SetConeOutsideVolume+0x0A : push [esp+4+arg_4]
    { 0x0A, 0xFF },
    { 0x0B, 0x74 },
    { 0x0C, 0x24 },
    { 0x0D, 0x0C },

    // IDirectSoundBuffer_SetConeOutsideVolume+0x15 : and ecx, eax
    { 0x15, 0x23 },
    { 0x16, 0xC8 },

    // IDirectSoundBuffer_SetConeOutsideVolume+0x1D : retn 0Ch
    { 0x1E, 0x0C },
    { 0x1F, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetMaxDistance,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMaxDistance+0x07 : mov edx, [esp+arg_4]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },

    // CDirectSoundVoice_SetMaxDistance+0x0B : mov [eax+10Ch], edx
    { 0x0B, 0x89 },
    { 0x0C, 0x90 },
    { 0x0D, 0x0C }, // SetMaxDistance 0x0C VS SetMinDistance 0x08

    // CDirectSoundVoice_SetMaxDistance+0x14 : or dword ptr [eax+138h], 4
    { 0x14, 0x83 },
    { 0x15, 0x88 },
    { 0x18, 0x00 },
    { 0x19, 0x00 },
    { 0x1A, 0x04 },

    // CDirectSoundVoice_SetMaxDistance+0x2A : retn 0Ch
    { 0x2A, 0xC2 },
    { 0x2B, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMaxDistance,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMaxDistance+0x39 : call [CDirectSoundVoice_SetMaxDistance]
    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetMaxDistance),

    // CDirectSoundBuffer_SetMaxDistance+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMaxDistance+0x21 : mov eax, 80004005h
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetMaxDistance+0x31 : fstp [esp+0Ch+var_C]
    { 0x31, 0xD9 },
    { 0x32, 0x1C },
    { 0x33, 0x24 },

    // CDirectSoundBuffer_SetMaxDistance+0x52 : retn 0Ch
    { 0x53, 0x0C },
    { 0x54, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetMinDistance,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetMinDistance+0x07 : mov edx, [esp+arg_4]
    { 0x07, 0x8B },
    { 0x08, 0x54 },
    { 0x09, 0x24 },
    { 0x0A, 0x08 },

    // CDirectSoundVoice_SetMinDistance+0x0B : mov [eax+108h], edx
    { 0x0B, 0x89 },
    { 0x0C, 0x90 },
    { 0x0D, 0x08 }, // SetMaxDistance 0x0C VS SetMinDistance 0x08

    // CDirectSoundVoice_SetMinDistance+0x14 : or dword ptr [eax+138h], 4
    { 0x14, 0x83 },
    { 0x15, 0x88 },
    { 0x18, 0x00 },
    { 0x19, 0x00 },
    { 0x1A, 0x04 },

    // CDirectSoundVoice_SetMinDistance+0x2A : retn 0Ch
    { 0x2A, 0xC2 },
    { 0x2B, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMinDistance,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMinDistance+0x39 : call [CDirectSoundVoice_SetMinDistance]
    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetMinDistance),

    // CDirectSoundBuffer_SetMinDistance+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMinDistance+0x21 : mov eax, 80004005h
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetMinDistance+0x31 : fstp [esp+0Ch+var_C]
    { 0x31, 0xD9 },
    { 0x32, 0x1C },
    { 0x33, 0x24 },

    // CDirectSoundBuffer_SetMinDistance+0x52 : retn 0Ch
    { 0x53, 0x0C },
    { 0x54, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetMode,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetMode+0x19 : call [CDirectSoundVoice::CommitDeferredSettings]
    XREF_ENTRY(0x1A, XREF_CDirectSoundVoice_CommitDeferredSettings),

    // CDirectSoundVoice::SetMode+0x00 : test byte [esp+0x0C],0x01
    { 0x00, 0xF6 },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x0C },
    { 0x04, 0x01 },

    // CDirectSoundVoice::SetMode+0x05 : mov eax,[esp+0x__]
    { 0x05, 0x8B },
    { 0x06, 0x44 },
    { 0x07, 0x24 },

    // CDirectSoundVoice::SetMode+0x16 : jne 0x__
    { 0x16, 0x75 },

    // CDirectSoundVoice::SetMode+0x19 : call [CDirectSoundVoice::CommitDeferredSettings]
    { 0x19, 0xE8 },

    // CDirectSoundVoice::SetMode+0x20 : ret 0x000C
    { 0x20, 0xC2 },
    { 0x21, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetMode,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetMode+0x35 : call [CDirectSoundVoice::SetMode]
    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetMode),

    // CDirectSoundBuffer_SetMode+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetMode+0x21 : mov eax, 80004005h
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetMode+0x30 : push [esp+0Ch+arg_0]
    { 0x30, 0xFF },
    { 0x31, 0x74 },
    { 0x32, 0x24 },
    { 0x33, 0x14 },

    // CDirectSoundBuffer_SetMode+0x4E : retn 0Ch
    { 0x4E, 0xC2 },
    { 0x4F, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetPosition,
                         4039)
OOVPA_SIG_MATCH(

    { 0x05, 0x08 },
    { 0x1C, 0xDC },

    { 0x31, 0x00 },
    { 0x32, 0x00 },
    { 0x33, 0xFF }, // SetPosition 0xFF vs SetConeOrientation 0x40
    { 0x34, 0xF6 },
    { 0x35, 0x45 },
    { 0x36, 0x18 },
    { 0x37, 0x01 },
    { 0x38, 0x5E },

    { 0x44, 0xC2 },
    { 0x45, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetPosition,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetPosition+0x49 : call [CDirectSoundVoice::SetPosition]
    XREF_ENTRY(0x49, XREF_CDirectSoundVoice_SetPosition),

    // CDirectSoundBuffer_SetPosition+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetPosition+0x2A : fld [ebp+arg_C]
    { 0x2A, 0xD9 },
    { 0x2B, 0x45 },
    { 0x2C, 0x14 },

    // CDirectSoundBuffer_SetPosition+0x42 : fstp [esp+18h+var_18]
    { 0x42, 0xD9 },
    { 0x43, 0x1C },
    { 0x44, 0x24 },

    // CDirectSoundBuffer_SetPosition+0x63 : retn 14h
    { 0x63, 0xC2 },
    { 0x64, 0x14 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetMode
// ******************************************************************
// Generic OOVPA as of 4039 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetMode,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetMode+0x18 : call [CDirectSoundBuffer::SetMode]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetMode),

    // IDirectSoundBuffer_SetMode+0x04 : push [esp+0x0C]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetMode+0x0E : add eax, 0xFFFFFFE4
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_SetMode+0x1D : retn 0x0C
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetVelocity,
                         4039)
OOVPA_SIG_MATCH(

    { 0x05, 0x08 },
    { 0x1C, 0xE8 },

    { 0x31, 0x00 },
    { 0x32, 0x00 },
    { 0x33, 0x40 }, // SetPosition 0xFF vs SetVelocity 0x40
    { 0x34, 0xF6 },
    { 0x35, 0x45 },
    { 0x36, 0x18 },
    { 0x37, 0x01 },
    { 0x38, 0x5E },

    { 0x44, 0xC2 },
    { 0x45, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetVelocity,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetVelocity+0x49 : call [CDirectSoundVoice::SetVelocity]
    XREF_ENTRY(0x49, XREF_CDirectSoundVoice_SetVelocity),

    // CDirectSoundBuffer_SetVelocity+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetVelocity+0x2A : fld [ebp+arg_C]
    { 0x2A, 0xD9 },
    { 0x2B, 0x45 },
    { 0x2C, 0x14 },

    // CDirectSoundBuffer_SetVelocity+0x42 : fstp [esp+18h+var_18]
    { 0x42, 0xD9 },
    { 0x43, 0x1C },
    { 0x44, 0x24 },

    // CDirectSoundBuffer_SetVelocity+0x63 : retn 14h
    { 0x63, 0xC2 },
    { 0x64, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeOrientation,
                         4039)
OOVPA_SIG_MATCH(

    { 0x05, 0x08 },
    { 0x1C, 0xFC },

    { 0x31, 0x00 },
    { 0x32, 0x00 },
    { 0x33, 0x18 }, // SetPosition 0xFF vs SetConeOrientation 0x40
    { 0x34, 0xF6 },
    { 0x35, 0x45 },
    { 0x36, 0x18 },
    { 0x37, 0x01 },
    { 0x38, 0x5E },

    { 0x44, 0xC2 },
    { 0x45, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeOrientation,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetConeOrientation+0x49 : call [CDirectSoundVoice::SetConeOrientation]
    XREF_ENTRY(0x49, XREF_CDirectSoundVoice_SetConeOrientation),

    // CDirectSoundBuffer_SetConeOrientation+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBuffer_SetConeOrientation+0x2A : fld [ebp+arg_C]
    { 0x2A, 0xD9 },
    { 0x2B, 0x45 },
    { 0x2C, 0x14 },

    // CDirectSoundBuffer_SetConeOrientation+0x42 : fstp [esp+18h+var_18]
    { 0x42, 0xD9 },
    { 0x43, 0x1C },
    { 0x44, 0x24 },

    // CDirectSoundBuffer_SetConeOrientation+0x63 : retn 14h
    { 0x63, 0xC2 },
    { 0x64, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound_SetOrientation
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetOrientation,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetOrientation+0x00 : push ebp
    { 0x00, 0x55 },

    { 0x30, 0x8B },
    { 0x32, 0x0C },
    { 0x39, 0x8B },
    { 0x3B, 0x10 },
    { 0x42, 0x8B },
    { 0x44, 0x14 },
    { 0x4B, 0x8B },
    { 0x4D, 0x18 },
    { 0x54, 0x8B },
    { 0x56, 0x1C },
    { 0x5D, 0x8B },
    { 0x5F, 0x20 },
    //
);

// ******************************************************************
// * CDirectSoundStream_GetStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetStatus,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },

    { 0x27, 0x8B },
    { 0x2A, 0x08 },

    { 0x2B, 0x8B },
    { 0x2D, 0x24 },

    { 0x33, 0x8B },
    { 0x36, 0x0C },

    { 0x37, 0xF7 },
    { 0x39, 0x1B },
    { 0x3B, 0xF7 },

    //CDirectSoundStream_GetStatus+0x20 : mov dword ptr [ecx], eax
    { 0x3F, 0x89 },
    { 0x40, 0x01 },

    { 0x51, 0xC2 },
    { 0x52, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound_DownloadEffectsImage
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_DownloadEffectsImage,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_DownloadEffectsImage+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_DownloadEffectsImage+0x2B : mov esi,dword ptr [ebp+8]
    { 0x2B, 0x8B },
    { 0x2C, 0x75 },
    { 0x2D, 0x08 },

    // CDirectSound_DownloadEffectsImage+0x2E : push dword ptr [ebp+14h]
    { 0x2E, 0xFF },
    { 0x2F, 0x75 },
    { 0x30, 0x14 },

    // CDirectSound_DownloadEffectsImage+0x31 : mov ecx,dword ptr [esi+8]
    { 0x31, 0x8B },
    { 0x32, 0x4E },
    { 0x33, 0x08 },

    // CDirectSound_DownloadEffectsImage+0x39 :  push dword ptr [ebp+18h]
    { 0x39, 0xFF },
    //{ 0x3A, 0x75 },
    { 0x3B, 0x18 },

    // CDirectSound_DownloadEffectsImage+0x3F : push dword ptr [ebp+10h]
    { 0x3F, 0xFF },
    //{ 0x40, 0x75 },
    { 0x41, 0x10 },

    // CDirectSound_DownloadEffectsImage+0x42 : push dword ptr [ebp+0Ch]
    { 0x42, 0xFF },
    //{ 0x43, 0x75 },
    { 0x44, 0x0C },

    // CDirectSound_DownloadEffectsImage+0x60 : ret 14h
    { 0x60, 0xC2 },
    { 0x61, 0x14 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetHeadroom
// ******************************************************************
//Generic OOVPA as of 4039 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetHeadroom,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetHeadroom+0x15 : call [CDirectSoundBuffer_SetHeadroom]
    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetHeadroom),

    // IDirectSoundBuffer_SetHeadroom+0x04 : push [esp+0x08]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetHeadroom+0x0A : add eax, 0xFFFFFFE4
    { 0x0A, 0x83 },
    { 0x0B, 0xC0 },
    { 0x0C, 0xE4 },

    // IDirectSoundBuffer_SetHeadroom+0x19 : retn 0x08
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSound_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetPosition,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetPosition+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_SetPosition+0x2A : mov ecx, [ebp+0x08]
    { 0x2A, 0x8B },
    { 0x2B, 0x4D },
    { 0x2C, 0x08 },

    // CDirectSound_SetPosition+0x3E : mov [edx+0x1C], edi
    { 0x3E, 0x89 },
    { 0x3F, 0x7A },
    { 0x40, 0x1C },

    // CDirectSound_SetPosition+0x4B : or word ptr [eax+0x84], 0x01FF
    { 0x4B, 0x80 },
    { 0x4C, 0x88 },
    { 0x4D, 0x84 },
    { 0x4E, 0x00 },
    { 0x51, 0xFF },

    // CDirectSound_SetPosition+0x72 : retn 0x14
    { 0x72, 0xC2 },
    { 0x73, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound::SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetVelocity,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetVelocity+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_SetVelocity+0x23 : mov eax, 0x80004005
    { 0x23, 0xB8 },
    { 0x24, 0x05 },
    { 0x25, 0x40 },
    { 0x26, 0x00 },
    { 0x27, 0x80 },

    // CDirectSound_SetVelocity+0x36 : mov [edx+0x24], edi
    { 0x36, 0x89 },
    { 0x37, 0x7A },
    { 0x38, 0x24 },

    // CDirectSound_SetVelocity+0x4B : or dword ptr [eax+0x084], 0x40
    { 0x4B, 0x83 },
    { 0x4C, 0x88 },
    { 0x4D, 0x84 },
    { 0x4F, 0x00 },
    { 0x51, 0x40 },

    // CDirectSound_SetVelocity+0x72 : retn 0x14
    { 0x72, 0xC2 },
    { 0x73, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound::SetI3DL2Listener
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetI3DL2Listener,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetI3DL2Listener+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSound_SetI3DL2Listener+0x35 : mov __x,[eax+0x08]
    { 0x32, 0x8B },
    //{ 0x33, 0x },
    { 0x34, 0x08 },

    // CDirectSound_SetI3DL2Listener+0x34 : cmp [__x+0xXX],-1
    { 0x35, 0x83 },
    //{ 0x36, 0x },
    //{ 0x37, 0x },
    { 0x38, 0xFF },

    // CDirectSound_SetI3DL2Listener+0x38 : jne +0x09
    { 0x39, 0x75 },
    { 0x3A, 0x09 },

    // CDirectSound_SetI3DL2Listener+0x3B : mov [ebp-0x04], 0x88780032 (unchanged since 3911)
    { 0x3B, 0xC7 },
    { 0x3E, 0x32 },
    { 0x3F, 0x00 },
    { 0x40, 0x78 },
    { 0x41, 0x88 },
    //
);

// ******************************************************************
// * CDirectSoundVoice_SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetAllParameters,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetAllParameters+0x00 : mov edx,[esp+04]
    { 0x00, 0x8B },

    // CDirectSoundVoice_SetAllParameters+0x0D : mov edi,[edx+10]
    { 0x0D, 0x6A },
    { 0x0E, 0x10 },

    // CDirectSoundVoice_SetAllParameters+0x16 : repe movsd
    { 0x16, 0xF3 },
    { 0x17, 0xA5 },

    // CDirectSoundVoice_SetAllParameters+0x18 : mov eax,[edx+10]
    { 0x18, 0x8B },
    { 0x19, 0x42 },
    { 0x1A, 0x10 },

    { 0x21, 0xFF },
    { 0x26, 0x01 },

    // CDirectSoundVoice_SetAllParameters+0x33 : retn 0x0C
    { 0x33, 0xC2 },
    { 0x34, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetAllParameters,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetAllParameters),

    // CDirectSoundBuffer_SetAllParameters+0x00 : push esi
    { 0x00, 0x56 },

    { 0x2A, 0x24 },
    { 0x2E, 0x24 },
    { 0x32, 0x24 },
    { 0x34, 0xE8 },

    // CDirectSoundBuffer_SetAllParameters+0x4E : retn 0x0C
    { 0x4E, 0xC2 },
    { 0x4F, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetAllParameters
// ******************************************************************
//Generic OOVPA as of 4039 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetAllParameters,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetAllParameters),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0xFF },
    { 0x0E, 0x83 },
    { 0x12, 0xD9 },
    { 0x16, 0xC8 },
    { 0x1D, 0xC2 },
    { 0x1E, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetConeAngles,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x03, 0x04 },

    { 0x04, 0x8B },
    { 0x06, 0x10 },

    { 0x07, 0x8B },
    { 0x0A, 0x08 },

    { 0x0B, 0x89 },
    { 0x0C, 0x91 },

    { 0x18, 0x89 },
    { 0x19, 0x91 },

    { 0x27, 0x10 },
    { 0x2C, 0x01 },

    // CDirectSoundVoice_SetConeAngles+0x37 : retn 10h
    { 0x37, 0xC2 },
    { 0x38, 0x10 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetConeAngles,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetConeAngles+0x39 : call [CDirectSoundVoice::SetConeAngles]
    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetConeAngles),

    // CDirectSoundBuffer_SetConeAngles+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetConeAngles+0x20 : mov eax, 80004005h
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetConeAngles+0x28 : push [esp+0Ch+arg_4]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x18 },

    // CDirectSoundBuffer_SetConeAngles+0x52 : retn 10h
    { 0x52, 0xC2 },
    { 0x53, 0x10 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetConeAngles
// ******************************************************************
//Generic OOVPA as of 4039 and newer.
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetConeAngles,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetConeAngles+0x1C : call [CDirectSoundBuffer::SetConeAngles]
    XREF_ENTRY(0x1D, XREF_CDirectSoundBuffer_SetConeAngles),

    // IDirectSoundBuffer_SetConeAngles+0x04 : mov eax, [esp+4+arg_0]
    { 0x04, 0x8B },
    { 0x05, 0x44 },
    { 0x06, 0x24 },
    { 0x07, 0x08 },

    // IDirectSoundBuffer_SetConeAngles+0x12 : add eax, 0FFFFFFE4
    { 0x12, 0x83 },
    { 0x13, 0xC0 },
    { 0x14, 0xE4 },

    // IDirectSoundBuffer_SetConeAngles+0x21 : retn 10h
    { 0x21, 0xC2 },
    { 0x22, 0x10 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetVelocity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetVelocity,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4D, XREF_CDirectSoundVoice_SetVelocity),

    { 0x00, 0x55 },
    { 0x0F, 0x00 },
    { 0x16, 0x74 },
    { 0x23, 0xB8 },
    { 0x29, 0x3B },
    { 0x34, 0x83 },
    { 0x3F, 0x45 },
    { 0x62, 0x8B },

    { 0x67, 0xC2 },
    { 0x68, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetPosition
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetPosition,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4D, XREF_CDirectSoundVoice_SetPosition),

    { 0x00, 0x55 },
    { 0x0F, 0x00 },
    { 0x16, 0x74 },
    { 0x23, 0xB8 },
    { 0x29, 0x3B },
    { 0x38, 0xEC },
    { 0x57, 0x68 },
    { 0x62, 0x8B },

    { 0x67, 0xC2 },
    { 0x68, 0x14 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMode
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMode,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetMode),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x38, 0xE8 },
    { 0x43, 0x68 },
    { 0x4E, 0x8B },

    { 0x52, 0xC2 },
    { 0x53, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMaxDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMaxDistance,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3D, XREF_CDirectSoundVoice_SetMaxDistance),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x3C, 0xE8 },
    { 0x47, 0x68 },
    { 0x52, 0x8B },

    { 0x56, 0xC2 },
    { 0x57, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetMinDistance
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMinDistance,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3D, XREF_CDirectSoundVoice_SetMinDistance),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x3C, 0xE8 },
    { 0x47, 0x68 },
    { 0x52, 0x8B },

    { 0x56, 0xC2 },
    { 0x57, 0x0C },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeOutsideVolume
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeOutsideVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetConeOutsideVolume),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x20, 0xB8 },
    { 0x23, 0x00 },
    { 0x38, 0xE8 },
    { 0x3D, 0x85 },
    { 0x4E, 0x8B },
    { 0x52, 0xC2 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeOrientation
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeOrientation,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x4D, XREF_CDirectSoundVoice_SetConeOrientation),

    { 0x00, 0x55 },
    { 0x0F, 0x00 },
    { 0x16, 0x74 },
    { 0x23, 0xB8 },
    { 0x29, 0x3B },
    { 0x38, 0xEC },
    { 0x43, 0x24 },
    { 0x4C, 0xE8 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetConeAngles
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetConeAngles,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x3D, XREF_CDirectSoundVoice_SetConeAngles),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },

    { 0x2F, 0x18 },
    { 0x32, 0x04 },
    { 0x36, 0x18 },

    { 0x3C, 0xE8 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetAllParameters,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetAllParameters),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x38, 0xE8 },
    { 0x43, 0x68 },
    { 0x4E, 0x8B },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetOutputBuffer
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetOutputBuffer,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetOutputBuffer),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },
    { 0x4A, 0x8B },
    //
);

// ******************************************************************
// * CDirectSoundStream::SetFrequency
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetFrequency,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetFrequency),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },

    // je XXXXXXXX + 0x0B
    { 0x13, 0x74 },
    { 0x14, 0x0B },

    // jmp XXXXXXXX + 0x26
    { 0x25, 0xEB },
    { 0x26, 0x26 },

    { 0x29, 0x24 },

    // je XXXXXXXX + 0x0B
    { 0x3D, 0x74 },
    { 0x3E, 0x0B },

    // ret 8
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetFrequency
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetFrequency,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetFrequency+0x00 : jmp [CDirectSoundStream_SetFrequency]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetFrequency),

    // IDirectSoundStream_SetFrequency+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetVolume
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetVolume,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetVolume+0x00 : jmp [CDirectSoundStream_SetVolume]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetVolume),

    // IDirectSoundStream_SetVolume+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetPitch,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetPitch),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },
    { 0x4A, 0x8B },
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    { 0x50, 0x00 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetPitch
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetPitch,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetPitch+0x00 : jmp [CDirectSoundStream_SetPitch]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetPitch),

    // IDirectSoundStream_SetPitch+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetLFO
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetLFO,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetLFO+0x00 : jmp [CDirectSoundStream_SetLFO]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetLFO),

    // IDirectSoundStream_SetLFO+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetEG
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetEG,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetEG+0x00 : jmp [CDirectSoundStream_SetEG]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetEG),

    // IDirectSoundStream_SetEG+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetFilter
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetFilter,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetFilter+0x00 : jmp [CDirectSoundStream_SetFilter]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetFilter),

    // IDirectSoundStream_SetFilter+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMixBinVolumes
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetMixBinVolumes_8,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetMixBinVolumes+0x00 : jmp [CDirectSoundStream_SetMixBinVolumes]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetMixBinVolumes_8),

    // IDirectSoundStream_SetMixBinVolumes+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CMcpxStream_Pause
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Pause,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxStream_Pause+0x00 : push ebp
    { 0x00, 0x55 },

    // CMcpxStream_Pause+0x20 : or eax, 4
    { 0x20, 0x83 },
    { 0x21, 0xC8 },
    { 0x22, 0x04 },

    // CMcpxStream_Pause+0x23 : jmp +0x0F
    { 0x23, 0xEB },
    { 0x24, 0x0F },

    // CMcpxStream_Pause+0x2B : mov eax,[esi+00000090]
    { 0x2B, 0x8B },
    { 0x2C, 0x86 },
    { 0x2D, 0x90 },
    { 0x2E, 0x00 },

    // CMcpxStream_Pause+0x48 : retn 0x04
    { 0x48, 0xC2 },
    { 0x49, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Pause
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Pause,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream_Pause+0x33 : call [CMcpxStream::Pause]
    XREF_ENTRY(0x34, XREF_CMcpxStream_Pause),

    // CDirectSoundStream_Pause+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundStream_Pause+0x20 : mov eax, 0x80004005
    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundStream_Pause+0x2B : mov ecx, [eax+0x24]
    { 0x2B, 0x8B },
    { 0x2C, 0x48 },
    { 0x2D, 0x24 },

    // CDirectSoundStream_Pause+0x4D : retn 0x08
    { 0x4D, 0xC2 },
    { 0x4E, 0x08 },
    //
);

// ******************************************************************
// * DSound_CRefCount_AddRef
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(DSound_CRefCount_AddRef,
                         4039)
OOVPA_SIG_MATCH(

    // DSound_CRefCount_AddRef+0x00 : mov eax,dword ptr [esp+4]
    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // DSound_CRefCount_AddRef+0x04 : inc dword ptr [eax+4]
    { 0x04, 0xFF },
    { 0x05, 0x40 },
    { 0x06, 0x04 },

    // DSound_CRefCount_AddRef+0x07 : mov eax, dword ptr [eax+4]
    { 0x07, 0x8B },
    { 0x08, 0x40 },
    { 0x09, 0x04 },

    // DSound_CRefCount_AddRef+0x0A : retn 0x04
    { 0x0A, 0xC2 },
    { 0x0B, 0x04 },
    //
);

// ******************************************************************
// * DSound_CRefCount_Release
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(DSound_CRefCount_Release,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },

    // DSound_CRefCount_Release+0x0B : dec eax
    { 0x0B, 0x48 },

    // DSound_CRefCount_Release+0x0E : mov dword ptr [ecx+4], eax
    { 0x0E, 0x89 },
    { 0x0F, 0x41 },
    { 0x10, 0x04 },

    // DSound_CRefCount_Release+0x1D : mov, dword ptr [ecx+4]
    { 0x1D, 0x8B },
    { 0x1E, 0x41 },
    { 0x1F, 0x04 },

    // DSound_CRefCount_Release+0x20 : retn 0x04
    { 0x20, 0xC2 },
    { 0x21, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream::Release
// ******************************************************************
// NOTE: Has identical function to CAc97MediaObject::Release
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Release,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x31, XREF_DSound_CRefCount_Release),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },

    { 0x2C, 0x83 },
    { 0x2D, 0xC0 },
    { 0x2E, 0x04 },

    { 0x46, 0x8B },

    { 0x4A, 0xC2 },
    { 0x4B, 0x04 },
    { 0x4C, 0x00 },
    //
);

// ******************************************************************
// * CFullHRTFSource::GetCenterVolume
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CFullHRTFSource_GetCenterVolume,
                         4039)
OOVPA_SIG_MATCH(

    // CFullHRTFSource::GetCenterVolume+0x00 : push ebp; mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // CFullHRTFSource::GetCenterVolume+0x22 : fabs
    OV_MATCH(0x22, 0xD9, 0xE1),

    // CFullHRTFSource::GetCenterVolume+0xC8 : mov [e__+__],0xFFFFD8F0
    OV_MATCH(0xCB, 0xF0, 0xD8, 0xFF, 0xFF),

    // CFullHRTFSource::GetCenterVolume+0xD1 : ret 0x0004
    OV_MATCH(0xD1, 0xC2, 0x04),
    //
);

// ******************************************************************
// * CHRTFSource::SetFullHRTF5Channel
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CHRTFSource_SetFullHRTF5Channel,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CHRTFSource::SetFullHRTF5Channel+0x36 : mov [var],CFullHRTFSource::GetCenterVolume
    XREF_ENTRY(0x38, XREF_CFullHRTFSource_GetCenterVolume),

    OV_MATCH(0x00, 0xC7),

    OV_MATCH(0x14, 0xC7),
    OV_MATCH(0x1E, 0xC7),
    OV_MATCH(0x28, 0xC7),
    OV_MATCH(0x32, 0xC7),
    OV_MATCH(0x3C, 0xC7),
    OV_MATCH(0x46, 0xC7),

    OV_MATCH(0x50, 0xC3),
    //
);

// ******************************************************************
// * DirectSoundUseFullHRTF
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundUseFullHRTF,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundUseFullHRTF+0x08 : call [CHRTFSource::SetFullHRTF5Channel]
    XREF_ENTRY(0x09, XREF_CHRTFSource_SetFullHRTF5Channel),

    // DirectSoundUseFullHRTF+0x06 : mov esi,eax
    OV_MATCH(0x06, 0x8B, 0xF0),

    // DirectSoundUseFullHRTF+0x0D : test, esi,esi
    OV_MATCH(0x0D, 0x85, 0xF6),

    OV_MATCH(0x11, 0x0B),
    OV_MATCH(0x17, 0xFF),

    // DirectSoundUseFullHRTF+0x1D : ret
    OV_MATCH(0x1D, 0xC3),
    //
);

// ******************************************************************
// * XAudioCalculatePitch
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XAudioCalculatePitch,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // XAudioCalculatePitch+0x10 : cmp eax, 0xBB80
    { 0x10, 0x3D },
    { 0x11, 0x80 },
    { 0x12, 0xBB },
    { 0x13, 0x00 },

    // XAudioCalculatePitch+0x19 : jmp +0x21
    { 0x19, 0xEB },
    { 0x1A, 0x21 },

    // XAudioCalculatePitch+0x3C : lea ecx, [ebp-04]
    { 0x3C, 0x8D },
    { 0x3D, 0x4D },
    { 0x3E, 0xFC },

    // XAudioCalculatePitch+0x48 : retn 0x04
    { 0x48, 0xC2 },
    { 0x49, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound::EnableHeadphones
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_EnableHeadphones,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    { 0x42, 0x0f },
    { 0x43, 0x95 },
    { 0x44, 0xC3 },

    { 0x4F, 0x0D },
    { 0x50, 0x00 },
    { 0x51, 0x00 },
    { 0x52, 0x00 },
    { 0x53, 0x80 },

    { 0x56, 0x25 },
    { 0x57, 0xFF },
    { 0x58, 0xFF },
    { 0x59, 0xFF },
    { 0x5A, 0x7F },

    { 0x7F, 0xC2 },
    { 0x80, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Process
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_Process,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x57 },

    { 0x28, 0x8B },
    { 0x2B, 0x0C },

    { 0x2C, 0x8B },
    { 0x2E, 0x24 },

    { 0x34, 0x85 },
    { 0x35, 0xC0 },

    //CDirectSoundStream_Process+0x39 : mov eax, 88780032h
    { 0x39, 0x32 },
    { 0x3A, 0x00 },
    { 0x3B, 0x78 },
    { 0x3C, 0x88 },

    { 0x3F, 0xFF },
    { 0x42, 0x10 },

    { 0x43, 0x8B },
    { 0x45, 0x24 },

    { 0x60, 0xC2 },
    { 0x61, 0x0C },
    //
);

// ******************************************************************
// * CMcpxStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxStream_Flush,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x09, 0x33 },

    { 0x32, 0x83 },
    { 0x33, 0xFF },
    { 0x34, 0x03 },

    { 0x4A, 0xE8 },

    { 0x58, 0xE8 },

    { 0x98, 0xC9 },
    { 0x99, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Flush
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Flush,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundStream::Flush+0x2F : call [CMcpxStream::Flush]
    XREF_ENTRY(0x30, XREF_CMcpxStream_Flush),

    { 0x00, 0x56 },

    { 0x27, 0x8B },
    { 0x2A, 0x08 },

    { 0x2B, 0x8B },
    { 0x2D, 0x24 },

    // CDirectSoundStream::Flush+0x2F : call [CMcpxStream::Flush]
    { 0x2F, 0xE8 },

    //CDirectSoundStream_Flush+0x49 : ret 4
    { 0x49, 0xC2 },
    { 0x4A, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream_AddRef
// ******************************************************************
// NOTE: Has identical function to DirectSound::CAc97MediaObject::AddRef
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_AddRef,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundStream::AddRef+0x00 : call DirectSoundEnterCriticalSection
    { 0x00, 0xE8 },

    // CDirectSoundStream::AddRef+0x24 : mov ecx,[esp+0x04]
    { 0x24, 0x8B },
    { 0x25, 0x4C },

    // CDirectSoundStream::AddRef+0x28 : inc [ecx+0x08]
    { 0x28, 0xFF },
    { 0x29, 0x41 },
    { 0x2A, 0x08 },

    // CDirectSoundStream::AddRef+0x2E : mov esi,[ecx+0x08]
    { 0x2E, 0x8B },
    { 0x2F, 0x71 },
    { 0x30, 0x08 },

    // CDirectSoundStream::AddRef+0x41 : ret 4
    { 0x41, 0xC2 },
    { 0x42, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundStream_GetInfo
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundStream_GetInfo,
                         4039)
OOVPA_SIG_MATCH(

    //CDirectSoundStream_GetInfo+0x00 : push ebx
    { 0x00, 0x53 },

    //CDirectSoundStream_GetInfo+0x2D : mov edi, dword ptr [esp + 10h]
    { 0x2D, 0x8B },
    { 0x2E, 0x7C },
    { 0x2F, 0x24 },
    { 0x30, 0x10 },

    //CDirectSoundStream_GetInfo+0x37 : mov, dword ptr [edi + 24h]
    { 0x37, 0x8B },
    { 0x38, 0x4F },
    { 0x39, 0x24 },

    //CDirectSoundStream_GetInfo+0x42 : mov eax, dword ptr [edi + 20h]
    { 0x42, 0x8B },
    { 0x43, 0x47 },
    { 0x44, 0x20 },

    //CDirectSoundStream_GetInfo+0x48 : and dword ptr [esi + 8], 0
    { 0x48, 0x83 },
    { 0x49, 0x66 },
    { 0x4A, 0x08 },
    { 0x4B, 0x00 },

    //CDirectSoundStream_GetInfo+0x63 : ret 8
    { 0x63, 0xC2 },
    { 0x64, 0x08 },
    //
);

// ******************************************************************
// * CMcpxStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CMcpxStream_Discontinuity,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CMcpxStream_Discontinuity+0x17 : call [CMcpxStream_Flush]
    XREF_ENTRY(0x18, XREF_CMcpxStream_Flush),

    { 0x00, 0x56 },

    { 0x01, 0x8B },

    { 0x15, 0x8B },

    { 0x17, 0xE8 },

    { 0x1E, 0x5E },

    { 0x1F, 0xC3 },
    //
);

// ******************************************************************
// * CDirectSoundStream_Discontinuity
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_Discontinuity,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    //CDirectSoundStream_Discontinuity+0x2F : call [CMcpxStream_Discontinuity]
    XREF_ENTRY(0x30, XREF_CMcpxStream_Discontinuity),

    { 0x00, 0x56 },

    { 0x27, 0x8B },
    { 0x2A, 0x08 },

    { 0x2B, 0x8B },
    { 0x2D, 0x24 },

    //CDirectSoundStream::Discontinuity+0x2F : call [CMcpxStream_Discontinuity]
    { 0x2F, 0xE8 },

    //CDirectSoundStream_Discontinuity+0x49 : ret 4
    { 0x49, 0xC2 },
    { 0x4A, 0x04 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetMixBins
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetMixBins,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetMixBins),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },

    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },

    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetMixBins
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetMixBins,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetMixBins+0x00 : jmp [CDirectSoundStream_SetMixBins]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetMixBins),

    // IDirectSoundStream_SetMixBins+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSoundVoice::SetI3DL2Source
// ******************************************************************
// TODO: Is possible to reduce pairs with an XREF included?
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundVoice_SetI3DL2Source,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice_SetI3DL2Source+0x00 : mov edx, [esp+arg_0]
    { 0x00, 0x8B },
    { 0x01, 0x54 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    // CDirectSoundVoice_SetI3DL2Source+0x1B : or byte ptr [eax+138h], 80h
    { 0x1B, 0x80 },
    { 0x1C, 0x88 },
    { 0x1D, 0x38 },
    { 0x1E, 0x01 },
    { 0x1F, 0x00 },
    { 0x20, 0x00 },
    { 0x21, 0x80 },

    // CDirectSoundVoice_SetI3DL2Source+0x22 : test [esp+8+arg_8], 1
    { 0x22, 0xF6 },
    { 0x23, 0x44 },
    { 0x24, 0x24 },
    { 0x25, 0x14 },
    { 0x26, 0x01 },

    // CDirectSoundVoice_SetI3DL2Source+0x57 : retn 08h
    { 0x57, 0xC2 },
    { 0x58, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetI3DL2Source,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetI3DL2Source+0x35 : call [CDirectSoundVoice::SetI3DL2Source]
    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetI3DL2Source),

    // CDirectSoundBuffer_SetI3DL2Source+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetI3DL2Source+0x21 : mov eax, 80004005h
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    // CDirectSoundBuffer_SetI3DL2Source+0x31 : push [esp+0Ch+arg_0]
    { 0x30, 0xFF },
    { 0x31, 0x74 },
    { 0x32, 0x24 },
    { 0x33, 0x14 },

    // CDirectSoundBuffer_SetI3DL2Source+0x4E : retn 0Ch
    { 0x4E, 0xC2 },
    { 0x4F, 0x0C },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetI3DL2Source
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetI3DL2Source,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundBuffer_SetI3DL2Source+0x18 : call [CDirectSoundBuffer::SetI3DL2Source]
    XREF_ENTRY(0x19, XREF_CDirectSoundBuffer_SetI3DL2Source),

    // IDirectSoundBuffer_SetI3DL2Source+0x04 : push [esp+arg_8]
    { 0x04, 0xFF },
    { 0x05, 0x74 },
    { 0x06, 0x24 },
    { 0x07, 0x0C },

    // IDirectSoundBuffer_SetI3DL2Source+0x0E : add eax, 0FFFFFFE4h
    { 0x0E, 0x83 },
    { 0x0F, 0xC0 },
    { 0x10, 0xE4 },

    // IDirectSoundBuffer_SetI3DL2Source+0x1D : retn 0Ch
    { 0x1E, 0x0C },
    { 0x1F, 0x00 },
    //
);

// ******************************************************************
// * CDirectSound::GetCaps
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetCaps,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x53 },
    { 0x15, 0x68 },

    { 0x36, 0x44 },
    { 0x37, 0x24 },
    { 0x38, 0x18 },
    { 0x39, 0x8B },
    { 0x3A, 0x48 },
    { 0x3B, 0x0C },
    { 0x3C, 0x56 },
    { 0x3D, 0xE8 },

    { 0x6C, 0xC2 },
    { 0x6D, 0x08 },
    //
);

// ******************************************************************
// * DirectSoundCreateStream
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundCreateStream,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundCreateStream+0x2B : call [CDirectSound::CreateSoundStream]
    XREF_ENTRY(0x2C, XREF_CDirectSound_CreateSoundStream),

    // DirectSoundCreateStream+0x04 : and [ebp-0x04], 0
    { 0x04, 0x83 },
    { 0x05, 0x65 },
    { 0x06, 0xFC },

    // DirectSoundCreateStream+0x08 : push esi; push edi
    { 0x08, 0x56 },
    { 0x09, 0x57 },

    // DirectSoundCreateStream+0x32 : lea eax,[ebp-04]
    { 0x32, 0x8D },
    { 0x33, 0x45 },
    { 0x34, 0xFC },

    // DirectSoundCreateStream+0x4F : retn 0x08
    { 0x4F, 0xC2 },
    { 0x50, 0x08 },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundStream::SetHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetHeadroom,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetHeadroom),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x34, 0xE8 },
    { 0x3F, 0x68 },
    { 0x4A, 0x8B },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetHeadroom
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetHeadroom,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetHeadroom+0x00 : jmp [CDirectSoundStream_SetHeadroom]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetHeadroom),

    // IDirectSoundStream_SetHeadroom+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * IsValidFormat
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(IsValidFormat,
                         4039)
OOVPA_SIG_MATCH(

    // IsValidFormat+0x00 : mov ecx, [esp+4]
    { 0x00, 0x8B },

    // IsValidFormat+0x14 : jz +0x04
    { 0x14, 0x74 },
    { 0x15, 0x04 },

    // IsValidFormat+0x16 : xor eax, eax
    { 0x16, 0x33 },
    { 0x17, 0xC0 },

    // IsValidFormat+0x18 : jmp +0x16
    { 0x18, 0xEB },
    { 0x19, 0x16 },

    // IsValidFormat+0x1A : push ecx
    { 0x1A, 0x51 },

    // IsValidFormat+0x1B : Call [WaveFormat_IsValidExtensibleFormat]
    { 0x1B, 0xE8 },

    // IsValidFormat+0x30 : retn 4
    { 0x30, 0xC2 },
    { 0x31, 0x04 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer::SetNotificationPositions
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBuffer_SetNotificationPositions,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetNotificationPositions+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetNotificationPositions+0x09 : push [esp+8+arg_4]
    { 0x09, 0xFF },
    { 0x0A, 0x74 },
    { 0x0B, 0x24 },
    { 0x0C, 0x10 },

    // CDirectSoundBuffer_SetNotificationPositions+0x0D : mov ecx, [esi+1Ch]
    { 0x0D, 0x8B },
    { 0x0E, 0x4E },
    { 0x0F, 0x1C },

    // CDirectSoundBuffer_SetNotificationPositions+0x10 : Call [CDirectSoundBufferSettings::SetNotificationPositions]
    { 0x10, 0xE8 },

    // CDirectSoundBuffer_SetNotificationPositions+0x1C : Call [CMcpxBuffer::SetNotificationPositions]
    { 0x1C, 0xE8 },

    // CDirectSoundBuffer_SetNotificationPositions+0x22 : retn 0Ch
    { 0x22, 0xC2 },
    { 0x23, 0x0C },
    //
);

// ******************************************************************
// * DirectSound::CDirectSoundVoice::SetFormat
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_SetFormat,
                      4039,
                      XRefTwo)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::SetFormat+0x2C : call [CMcpxVoiceClient::SetMixBins]
    XREF_ENTRY(0x2D, XREF_CMcpxVoiceClient_SetMixBins),

    // CDirectSoundVoice::SetFormat+0x3A : call [CMcpxVoiceClient::SetPitch]
    XREF_ENTRY(0x3B, XREF_CMcpxVoiceClient_SetPitch),

    // CDirectSoundVoice::SetFormat+0x00 : push ebx; push esi
    { 0x00, 0x53 },
    { 0x01, 0x56 },

    // CDirectSoundVoice::SetFormat+0x0A : push 0x01
    { 0x0A, 0x6A },
    { 0x0B, 0x01 },

    // CDirectSoundVoice::SetFormat+0x44 : ret 0x08
    { 0x44, 0xC2 },
    { 0x45, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundBuffer_SetFormat
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundBuffer_SetFormat,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundBuffer_SetFormat+0x30 : call [CDirectSoundVoice::SetFormat]
    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_SetFormat), // Was 4134 Offset -0x01h

    // CDirectSoundBuffer_SetFormat+0x00 : push esi
    { 0x00, 0x56 },

    // CDirectSoundBuffer_SetFormat+0x28 : push [esp+0x10]; push [esp+0x10]
    { 0x28, 0xFF },
    { 0x29, 0x74 },
    { 0x2A, 0x24 },
    { 0x2B, 0x10 },
    { 0x2C, 0xFF },
    { 0x2D, 0x74 },
    { 0x2E, 0x24 },
    { 0x2F, 0x10 },

    // CDirectSoundBuffer_SetFormat+0x48 : pop edi
    { 0x48, 0x5F },

    // CDirectSoundBuffer_SetFormat+0x4A : retn 0x08
    { 0x4A, 0xC2 },
    { 0x4B, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundBuffer_SetFormat
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundBuffer_SetFormat,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_SetFormat),

    { 0x02, 0x24 },
    { 0x06, 0x24 },
    { 0x0A, 0x83 },
    { 0x0E, 0xD9 },
    { 0x12, 0xC8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetFormat
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetFormat,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_SetFormat),

    { 0x00, 0x56 },

    { 0x0C, 0x00 },

    // je XXXXXXXX + 0x0B
    { 0x13, 0x74 },
    { 0x14, 0x0B },

    // jmp XXXXXXXX + 0x26
    { 0x25, 0xEB },
    { 0x26, 0x26 },

    { 0x29, 0x24 },

    // je XXXXXXXX + 0x0B
    { 0x3D, 0x74 },
    { 0x3E, 0x0B },

    // ret 8
    { 0x4E, 0xC2 },
    { 0x4F, 0x08 },
    //
);

// ******************************************************************
// * IDirectSoundStream_SetFormat
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_XREF(IDirectSoundStream_SetFormat,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // IDirectSoundStream_SetFormat+0x00 : jmp [CDirectSoundStream_SetFormat]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_SetFormat),

    // IDirectSoundStream_SetFormat+0x00 : jmp 0x........
    { 0x00, 0xE9 },
    //
);

// ******************************************************************
// * CDirectSound_CommitEffectData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_CommitEffectData,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x56 },
    { 0x0C, 0x00 },

    { 0x20, 0xB8 },
    { 0x21, 0x05 },
    { 0x22, 0x40 },
    { 0x23, 0x00 },
    { 0x24, 0x80 },

    { 0x25, 0xEB },
    { 0x26, 0x24 },

    { 0x27, 0x8B },
    { 0x28, 0x44 },

    { 0x31, 0x6A },
    { 0x33, 0x6A },

    { 0x35, 0xE8 },

    { 0x4C, 0xC2 },
    { 0x4D, 0x04 },
    //
);

// ******************************************************************
// * CDirectSound_GetEffectData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_GetEffectData,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0F, 0x00 },

    { 0x23, 0xB8 },
    { 0x24, 0x05 },
    { 0x25, 0x40 },
    { 0x26, 0x00 },
    { 0x27, 0x80 },

    { 0x28, 0xEB },
    { 0x29, 0x2F },

    { 0x2A, 0x8B },
    { 0x2B, 0x45 },

    { 0x40, 0xE8 },

    { 0x5B, 0xC2 },
    { 0x5C, 0x14 },
    //
);

// ******************************************************************
// * CDirectSound_SetEffectData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetEffectData,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x0F, 0x00 },

    { 0x23, 0xB8 },
    { 0x24, 0x05 },
    { 0x25, 0x40 },
    { 0x26, 0x00 },
    { 0x27, 0x80 },

    { 0x28, 0xEB },
    { 0x29, 0x32 },

    { 0x2A, 0x8B },
    { 0x2B, 0x45 },

    { 0x43, 0xE8 },

    { 0x5E, 0xC2 },
    { 0x5F, 0x18 },
    //
);

// ******************************************************************
// * CDirectSoundStream_SetI3DL2Source
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundStream_SetI3DL2Source,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x39, XREF_CDirectSoundVoice_SetI3DL2Source),

    { 0x00, 0x56 },
    { 0x0C, 0x00 },
    { 0x13, 0x74 },
    { 0x20, 0xB8 },
    { 0x29, 0x24 },
    { 0x38, 0xE8 },
    { 0x43, 0x68 },
    { 0x4E, 0x8B },
    //
);

// ******************************************************************
// * CDirectSound::SetAllParameters
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSound_SetAllParameters,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSound_SetAllParameters+0x00 : push ebx
    { 0x00, 0x53 },

    // CDirectSound_SetAllParameters+0x3F : or byte ptr [eax+84h], 0FFh
    { 0x3F, 0x80 },
    { 0x40, 0x88 },
    { 0x41, 0x84 },
    { 0x42, 0x00 },
    { 0x43, 0x00 },
    { 0x44, 0x00 },
    { 0x45, 0xFF },

    // CDirectSound_SetAllParameters+0x46 : test [esp+0Ch+arg_8], 1
    { 0x46, 0xF6 },
    { 0x47, 0x44 },
    { 0x48, 0x24 },
    { 0x49, 0x18 },
    { 0x4A, 0x01 },

    // CDirectSound_SetAllParameters+0x67 : retn 0Ch
    { 0x67, 0xC2 },
    { 0x68, 0x0C },
    //
);

// ******************************************************************
// * XAudioCreateAdpcmFormat
// ******************************************************************
// NOTE: 4134 later versions changed to a jmp, then convert into
// class function.
// TODO: Either rename this to WaveFormat_CreateXboxAdpcmFormat
//       or use jmp caller as XAudioCreateAdpcmFormat_(forward/jmp)
//       Then add separate signature to include jmp to this function check.
OOVPA_SIG_HEADER_NO_XREF(XAudioCreateAdpcmFormat,
                         4039)
OOVPA_SIG_MATCH(

    OV_MATCH(0x07, 0x08),
    OV_MATCH(0x10, 0xE9),
    OV_MATCH(0x19, 0x8D),

    OV_MATCH(0x27, 0x66, 0xC7, 0x40, 0x0E, 0x04, 0x00, 0x66),

    OV_MATCH(0x34, 0x66),
    OV_MATCH(0x3D, 0x12),
    //
);

// ******************************************************************
// * CMcpxVoiceClient::Commit3dSettings
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_Commit3dSettings_0,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient::Commit3dSettings+0x42 : cmp edi, 0x02
    { 0x42, 0x83 },
    { 0x43, 0xFF },
    { 0x44, 0x02 },

    // CMcpxVoiceClient::Commit3dSettings+0x53 : mov e__,[e__+0x000000F4]
    { 0x53, 0x8B },
    //{ 0x54, 0x__ },
    { 0x55, 0xF4 },
    { 0x56, 0x00 },
    //{ 0x57, 0x00 },
    { 0x58, 0x00 },

    // CMcpxVoiceClient::Commit3dSettings+0x73 : mov eax,[eax+0x000000F4]
    { 0x73, 0x8B },
    //{ 0x74, 0x80 },
    { 0x75, 0xF4 },
    { 0x76, 0x00 },
    //{ 0x77, 0x00 },
    { 0x78, 0x00 },

    //
);

// ******************************************************************
// * CDirectSoundVoice::CommitDeferredSettings
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSoundVoice_CommitDeferredSettings,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSoundVoice::CommitDeferredSettings+0x1D : call [CMcpxVoiceClient::Commit3dSettings]
    XREF_ENTRY(0x1E, XREF_CMcpxVoiceClient_Commit3dSettings),

    { 0x00, 0x56 },

    // CDirectSoundVoice::CommitDeferredSettings+0x0E : mov ecx,[ecx+0x00000084]
    { 0x0B, 0x8B },
    { 0x0C, 0x89 },
    { 0x0D, 0x84 },
    { 0x0E, 0x00 },
    //{ 0x0F, 0x00 },
    //{ 0x10, 0x00 },

    // CDirectSoundVoice::CommitDeferredSettings+0x14 : or [eax+0x000000B4],ecx
    { 0x14, 0x09 },
    { 0x15, 0x88 },
    { 0x16, 0x38 },
    { 0x17, 0x01 },
    //{ 0x18, 0x00 },
    //{ 0x19, 0x00 },

    { 0x2F, 0xC2 },
    { 0x30, 0x04 },

    //
);

// ******************************************************************
// * CMcpxVoiceClient_SetPitch
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CMcpxVoiceClient_SetPitch,
                         4039)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },

    // CMcpxVoiceClient_SetPitch+0x25 : lea edi, [esi+0xC4]
    { 0x25, 0x8D },
    { 0x26, 0xBE },
    { 0x27, 0xC4 },
    { 0x28, 0x00 },

    // CMcpxVoiceClient_SetPitch+0x5C : lea ecx,[eax+eax]
    { 0x5C, 0x8D },
    { 0x5D, 0x0C },
    { 0x5E, 0x00 },

    // CMcpxVoiceClient_SetPitch+0x72 : lea eax,[esi+0x84]
    { 0x72, 0x8D },
    { 0x73, 0x86 },
    { 0x74, 0x84 },
    { 0x75, 0x00 },
    //
);

// ******************************************************************
// * CDirectSoundBufferSettings::SetBufferData
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CDirectSoundBufferSettings_SetBufferData,
                         4039)
OOVPA_SIG_MATCH(

    // CDirectSoundBufferSettings::SetBufferData+0x00 : push ebp
    { 0x00, 0x55 },

    // CDirectSoundBufferSettings::SetBufferData+0x0C : mov edx,0x80000000
    { 0x0C, 0xBB },
    { 0x0D, 0x00 },
    //{ 0x0E, 0x00 },
    { 0x0F, 0x00 },
    { 0x10, 0x80 },

    // CDirectSoundBufferSettings::SetBufferData+0x20 : jmp +0x06
    { 0x20, 0xEB },
    { 0x21, 0x06 },

    // This offset is unique.
    // CDirectSoundBufferSettings::SetBufferData+0x43 : and byte [esi+0x0B],0x7F
    { 0x43, 0x80 },
    { 0x44, 0x66 },
    //{ 0x45, 0x0B },
    { 0x46, 0x7F },

    // CDirectSoundBufferSettings::SetBufferData+0x78 : ret 8
    { 0x78, 0xC2 },
    { 0x79, 0x08 },
    //
);

// ******************************************************************
// * CLightHRTFSource::GetCenterVolume
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(CLightHRTFSource_GetCenterVolume,
                         4039)
OOVPA_SIG_MATCH(

    // CLightHRTFSource::GetCenterVolume+0x00 : push ebp; mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // CLightHRTFSource::GetCenterVolume+0x22 : fabs
    OV_MATCH(0x22, 0xD9, 0xE1),

    // CLightHRTFSource::GetCenterVolume+0xB0 : mov [e__+__],0xFFFFD8F0
    OV_MATCH(0xB3, 0xF0, 0xD8, 0xFF, 0xFF),

    // CLightHRTFSource::GetCenterVolume+0xB9 : ret 0x0004
    OV_MATCH(0xB9, 0xC2, 0x04),
    //
);

// ******************************************************************
// * CHRTFSource::SetLightHRTF5Channel
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CHRTFSource_SetLightHRTF5Channel,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CHRTFSource::SetLightHRTF5Channel+0x36 : mov [var],CLightHRTFSource::GetCenterVolume
    XREF_ENTRY(0x38, XREF_CLightHRTFSource_GetCenterVolume),

    OV_MATCH(0x00, 0xC7),

    OV_MATCH(0x14, 0xC7),
    OV_MATCH(0x1E, 0xC7),
    OV_MATCH(0x28, 0xC7),
    OV_MATCH(0x32, 0xC7),
    OV_MATCH(0x3C, 0xC7),
    OV_MATCH(0x46, 0xC7),

    OV_MATCH(0x50, 0xC3),
    //
);

// ******************************************************************
// * DirectSoundUseLightHRTF
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundUseLightHRTF,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundUseLightHRTF+0x08 : call [CHRTFSource::SetLightHRTF5Channel]
    XREF_ENTRY(0x09, XREF_CHRTFSource_SetLightHRTF5Channel),

    // DirectSoundUseLightHRTF+0x06 : mov esi,eax
    OV_MATCH(0x06, 0x8B, 0xF0),

    // DirectSoundUseLightHRTF+0x0D : test, esi,esi
    OV_MATCH(0x0D, 0x85, 0xF6),

    OV_MATCH(0x11, 0x0B),
    OV_MATCH(0x17, 0xFF),

    // DirectSoundUseLightHRTF+0x1D : ret
    OV_MATCH(0x1D, 0xC3),
    //
);

// ******************************************************************
// * CMcpxAPU::SetMixBinHeadroom
// ******************************************************************
// Generic OOVPA as of 4039 and newer
OOVPA_SIG_HEADER_NO_XREF(CMcpxAPU_SetMixBinHeadroom_4,
                         4039)
OOVPA_SIG_MATCH(

    // CMcpxAPU_SetMixBinHeadroom+0x00: push ebp;
    OV_MATCH(0x00, 0x55),

    // CMcpxAPU_SetMixBinHeadroom+0x14: mov eax, [0xFE820010]
    OV_MATCH(0x14, 0xA1, 0x10, 0x00, 0x82, 0xFE),

    // CMcpxAPU_SetMixBinHeadroom+0x19: and eax,-04
    OV_MATCH(0x19, 0x83, 0xE0, 0xFC),

    // CMcpxAPU_SetMixBinHeadroom+0x22: ret
    OV_MATCH(0x1C, 0x83, 0xF8, 0x04),

    // Generic support over multiple revisions end at offset 0x27
    //
);

// ******************************************************************
// * CDirectSound::SetMixBinHeadroom
// ******************************************************************
OOVPA_SIG_HEADER_XREF(CDirectSound_SetMixBinHeadroom,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // CDirectSound::SetMixBinHeadroom+0x42 : call [CMcpxAPU::SetMixBinHeadroom]
    XREF_ENTRY(0x43, XREF_CMcpxAPU_SetMixBinHeadroom),

    // CDirectSound::SetMixBinHeadroom+0x00 : push esi
    OV_MATCH(0x00, 0x56),

    // CDirectSound::SetMixBinHeadroom+0x20 : mov eax, 0x80004005
    OV_MATCH(0x20, 0xB8, 0x05, 0x40, 0x00, 0x80),

    // CDirectSound::SetMixBinHeadroom+0x33 : mov edi,[esp+14]
    OV_MATCH(0x33, 0x8B, 0x7C, 0x24, 0x14),

    // CDirectSound::SetMixBinHeadroom+0x5C : retn 0x0C
    OV_MATCH(0x5C, 0xC2, 0x0C),
    //
);

// ******************************************************************
// * DirectSoundOverrideSpeakerConfig
// ******************************************************************
OOVPA_SIG_HEADER_XREF(DirectSoundOverrideSpeakerConfig,
                      4039,
                      XRefOne)
OOVPA_SIG_MATCH(

    // DirectSoundOverrideSpeakerConfig+0x00 : call [DirectSoundEnterCriticalSection]
    XREF_ENTRY(0x01, XREF_DirectSoundEnterCriticalSection),

    // DirectSoundOverrideSpeakerConfig+0x00 : call [DirectSoundEnterCriticalSection]
    OV_MATCH(0x00, 0xE8),

    // DirectSoundOverrideSpeakerConfig+0x09 : and ecx,0x0000FFFF
    OV_MATCH(0x09, 0x81, 0xE1, 0xFF, 0xFF, 0x00, 0x00),

    // DirectSoundOverrideSpeakerConfig+0x24 : retn 0x0004
    OV_MATCH(0x24, 0xC2, 0x04),
    //
);

// ******************************************************************
// * XAudioDownloadEffectsImage
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XAudioDownloadEffectsImage,
                         4039)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x55),

    OV_MATCH(0x0A, 0x33, 0xFF, 0x89, 0x75, 0xF8, 0xE8),

    OV_MATCH(0x3C, 0x83),
    OV_MATCH(0x4E, 0xE8),
    OV_MATCH(0x65, 0x8B),
    //
);

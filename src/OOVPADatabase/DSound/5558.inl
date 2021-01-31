// ******************************************************************
// *
// *   OOVPADatabase->DSound->5558.inl
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
// *  (c) 2017 PatrickvL
// *  (c) 2017-2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************

// ******************************************************************
// * DirectSound::CDirectSoundVoice::Use3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5558 and newer
OOVPA_XREF(CDirectSoundVoice_Use3DVoiceData, 5558, 9,

           XREF_CDirectSoundVoice_Use3DVoiceData,
           XRefZero)
{

    { 0x04, 0x00 },
    { 0x07, 0x24 },
    { 0x0B, 0x10 },
    { 0x0F, 0x48 },
    { 0x12, 0xEB },
    { 0x16, 0x0B },
    { 0x18, 0x33 },
    { 0x1A, 0xC2 },
    { 0x1B, 0x08 },
} OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSoundBuffer::Use3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5558 and newer
OOVPA_XREF(CDirectSoundBuffer_Use3DVoiceData, 5558, 1 + 8,

           XREF_CDirectSoundBuffer_Use3DVoiceData,
           XRefOne)
{

    XREF_ENTRY(0x31, XREF_CDirectSoundVoice_Use3DVoiceData),

    { 0x0C, 0x0F },
    { 0x10, 0x16 },
    { 0x15, 0x68 },
    { 0x36, 0xC9 },
    { 0x39, 0x74 },
    { 0x3B, 0x68 },
    { 0x49, 0xC2 },
    { 0x4A, 0x08 },
} OOVPA_END;

// ******************************************************************
// * IDirectSoundBuffer::Use3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5558 and newer
OOVPA_XREF(IDirectSoundBuffer_Use3DVoiceData, 5558, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x15, XREF_CDirectSoundBuffer_Use3DVoiceData),

    { 0x06, 0x24 },
    { 0x08, 0x8B },
    { 0x0C, 0xE4 },
    { 0x0E, 0xD9 },
    { 0x11, 0x23 },
    { 0x14, 0xE8 },
    { 0x19, 0xC2 },
    { 0x1A, 0x08 },
} OOVPA_END;

// ******************************************************************
// * DirectSound::CDirectSoundStream::Use3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5558 and newer
OOVPA_XREF(CDirectSoundStream_Use3DVoiceData, 5558, 1 + 8,

           XREF_CDirectSoundStream_Use3DVoiceData,
           XRefOne)
{

    XREF_ENTRY(0x35, XREF_CDirectSoundVoice_Use3DVoiceData),

    { 0x0C, 0x0F },
    { 0x10, 0x16 },
    { 0x15, 0x68 },
    { 0x3A, 0xC9 },
    { 0x3D, 0x74 },
    { 0x3F, 0x68 },
    { 0x4D, 0xC2 },
    { 0x4E, 0x08 },
} OOVPA_END;

// ******************************************************************
// * IDirectSoundStream_Use3DVoiceData
// ******************************************************************
// Generic OOVPA as of 5558 and newer
OOVPA_XREF(IDirectSoundStream_Use3DVoiceData, 5558, 1 + 1,

           XRefNoSaveIndex,
           XRefOne)
{

    // IDirectSoundStream_Use3DVoiceData+0x00 : jmp [CDirectSoundStream_Use3DVoiceData]
    XREF_ENTRY(0x01, XREF_CDirectSoundStream_Use3DVoiceData),

    // IDirectSoundStream_Use3DVoiceData+0x00 : jmp 0x........
    { 0x00, 0xE9 },
} OOVPA_END;

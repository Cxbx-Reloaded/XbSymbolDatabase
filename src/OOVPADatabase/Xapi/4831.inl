// ******************************************************************
// *
// *   OOVPADatabase->Xapi->4831.inl
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

// ******************************************************************
// * XInputSetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputSetState,
                         4831)
OOVPA_SIG_MATCH(

    { 0x00, 0x8B },
    { 0x01, 0x4C },
    { 0x02, 0x24 },
    { 0x03, 0x04 },
    { 0x04, 0x8D },
    { 0x05, 0x81 },
    { 0x06, 0xA3 },
    { 0x07, 0x00 },
    { 0x08, 0x00 },
    { 0x09, 0x00 },

    { 0x21, 0x8B },
    { 0x22, 0x40 },

    { 0x30, 0xC2 },
    { 0x31, 0x08 },
    //
);

// ******************************************************************
// * XID_fCloseDevice
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XID_fCloseDevice,
                      4831,

                      XREF_XID_fCloseDevice,
                      XRefZero)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },
    { 0x02, 0xEC },
    { 0x03, 0x83 },
    { 0x04, 0xEC },
    { 0x05, 0x14 },
    { 0x06, 0x53 },
    { 0x07, 0x56 },
    { 0x08, 0x8B },
    { 0x09, 0xF1 },
    { 0x0A, 0xFF },
    { 0x0B, 0x15 },

    { 0x1E, 0x3B },
    { 0x1F, 0xC3 },

    { 0x38, 0x45 },
    { 0x39, 0xF4 },
    //
);

// ******************************************************************
// * XInputGetState
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetState,
                         4831)
OOVPA_SIG_MATCH(

    { 0x0E, 0x8B },
    { 0x0F, 0x8A },
    { 0x10, 0xA3 },

    { 0x1A, 0x6A },
    { 0x1B, 0x57 },

    { 0x1D, 0xEB },
    { 0x1E, 0x3E },

    { 0x3A, 0x8B },
    { 0x3B, 0x8A },
    { 0x3C, 0xA3 },

    { 0x69, 0xC2 },
    { 0x6A, 0x08 },
    //
);

// ******************************************************************
// * XInputGetCapabilities
// ******************************************************************
// Generic OOVPA as of 4831 and newer.
OOVPA_SIG_HEADER_NO_XREF(XInputGetCapabilities,
                         4831)
OOVPA_SIG_MATCH(

    OV_MATCH(0x00, 0x55),

    OV_MATCH(0x1F, 0x0F),

    // mov edi,edx; rep stos [edi]
    OV_MATCH(0x37, 0x8B, 0xFA, 0xF3, 0xAB),

    // stos [edi]; mov al,[esi+0x0B]
    OV_MATCH(0x3B, 0xAA, 0x8A, 0x46, 0x0B),

    OV_MATCH(0x3F, 0x88),

    OV_MATCH(0x59, 0x0F, 0xB6),
    //
);

// ******************************************************************
// * XGetDeviceEnumerationStatus
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XGetDeviceEnumerationStatus,
                         4831)
OOVPA_SIG_MATCH(

    { 0x04, 0x15 },
    { 0x0A, 0x35 },
    { 0x10, 0x09 },

    { 0x17, 0x00 },
    { 0x18, 0x74 },
    { 0x19, 0x03 },
    { 0x1A, 0x33 },
    { 0x1B, 0xF6 },
    { 0x1C, 0x46 },
    { 0x1D, 0x8A },
    { 0x1E, 0xC8 },
    { 0x1F, 0xFF },

    { 0x25, 0x8B },
    { 0x28, 0xC3 },
    //
);

// ******************************************************************
// * XapiInitProcess
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XapiInitProcess,
                         4831)
OOVPA_SIG_MATCH(

    { 0x00, 0x55 },
    { 0x01, 0x8B },

    { 0x13, 0x6A },
    { 0x14, 0x0C },
    { 0x15, 0x59 },
    { 0x16, 0x33 },
    { 0x17, 0xC0 },
    { 0x18, 0x8D },
    { 0x19, 0x7D },
    { 0x1A, 0xCC },

    { 0x1D, 0x8D },
    { 0x1E, 0x45 },
    //
);

// ******************************************************************
// * XInputGetDeviceDescription
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInputGetDeviceDescription,
                         4831)
OOVPA_SIG_MATCH(

    { 0x04, 0xEC },
    { 0x0B, 0x15 },

    { 0x13, 0x45 },
    { 0x14, 0x08 },
    { 0x15, 0x8B },
    { 0x16, 0x30 },
    { 0x17, 0x3B },
    { 0x18, 0xF3 },
    { 0x19, 0x88 },
    { 0x1A, 0x4D },
    { 0x1B, 0xFF },
    { 0x1C, 0x0F },
    { 0x1D, 0x84 },

    { 0x30, 0x45 },
    //{ 0x31, 0xF8 }, // 4831 0xF4 vs 5344 0xF8
    //
);

// ******************************************************************
// * XReadMUMetaData
// ******************************************************************
OOVPA_SIG_HEADER_XREF(XReadMUMetaData,
                      4831,

                      XRefNoSaveIndex,
                      XRefOne)
OOVPA_SIG_MATCH(

    XREF_ENTRY(0x31, XREF_g_XapiMountedMUs),

    // push ebp
    // mov ebp,esp
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC),

    // mov WORD PTR [ebp-0x0E],0x3E
    OV_MATCH(0x51, 0x66, 0xC7, 0x45, 0xF2, 0x3E, 0x00),
    //
);

// ******************************************************************
// * UnhandledExceptionFilter
// ******************************************************************
// Generic OOVPA as of 4831 and newer.
// NOTE: 3911 signature is exactly the same at start of offset 0x1F
OOVPA_SIG_HEADER_XREF(UnhandledExceptionFilter,
                      4831,

                      XREF_XAPI_UnhandledExceptionFilter,
                      XRefOne)
OOVPA_SIG_MATCH(

    // mov eax,[g_XapiCurrentTopLevelFilter]
    XREF_ENTRY(0x20, XREF_g_XapiCurrentTopLevelFilter), // derived

    // mov eax,fs:[0x20]
    OV_MATCH(0x00, 0x64, 0xA1, 0x20, 0x00),

    // mov eax,[eax+0x250]
    OV_MATCH(0x06, 0x8B, 0x80, 0x50, 0x02, 0x00),

    // mov eax,[g_XapiCurrentTopLevelFilter]
    OV_MATCH(0x1F, 0xA1),

    // push param_1
    OV_MATCH(0x28, 0xFF, 0x74, 0x24, 0x04),

    // call eax
    OV_MATCH(0x2C, 0xFF, 0xD0),

    // cmp eax,-1
    OV_MATCH(0x2E, 0x83, 0xF8, 0xFF),

    // or eax,eax
    OV_MATCH(0x33, 0x0B, 0xC0),

    // xor eax,eax
    OV_MATCH(0x37, 0x33, 0xC0),

    // ret 0x0004
    OV_MATCH(0x39, 0xC2, 0x04),
    //
);

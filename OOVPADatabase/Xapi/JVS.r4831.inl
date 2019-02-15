// ******************************************************************
// *
// *   OOVPADatabase->Xapi->JVS.r4831.inl
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
// *  (c) 2019 Luke Usher
// *
// *  All rights reserved
// *
// ******************************************************************

OOVPA_XREF(JVS_SendCommand_String, 4831, 13,
    XREF_JVS_SendCommand_String,
    XRefZero)
    
    // JVS_STATUS_ERROR_DEVICE_NOT_CONNECTED2 from JVS_SendCommand
    { 0x00, 'J' },
    { 0x01, 'V' },
    { 0x02, 'S' },
    { 0x04, 'S' },
    { 0x0B, 'E' },
    { 0x11, 'D' },
    { 0x18, 'N' },
    { 0x1C, 'C' },
    { 0x25, '2' },
    { 0x27, 'f' },
    { 0x2C, 'J' },
    { 0x30, 'S' },
    { 0x34, 'C' },
OOVPA_END;


OOVPA_XREF(JvsBACKUP_Read_String, 4831, 13,
    XREF_JvsBACKUP_Read_String,
    XRefZero)

    // Status error <JvsBACKUP_Read>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0D, '<' },
    { 0x0E, 'J' },
    { 0x11, 'B' },
    { 0x18, 'R' },
    { 0x1B, 'd' },
    { 0x1C, '>' },
OOVPA_END;

OOVPA_XREF(JvsBACKUP_Write_String, 4831, 13,
    XREF_JvsBACKUP_Write_String,
    XRefZero)

    // Status error <JvsBACKUP_Write>
    { 0x00, 'S'    },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0D, '<' },
    { 0x0E, 'J' },
    { 0x11, 'B' },
    { 0x18, 'W' },
    { 0x1C, 'e' },
    { 0x1D, '>' },
OOVPA_END;

OOVPA_XREF(JvsEEPROM_Read_String, 4831, 13,
    XREF_JvsEEPROM_Read_String,
    XRefZero)

    // Status error <JvsEEPROM_Read>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0D, '<' },
    { 0x0E, 'J' },
    { 0x11, 'E' },
    { 0x18, 'R' },
    { 0x1B, 'd' },
    { 0x1C, '>' },
OOVPA_END;

OOVPA_XREF(JvsEEPROM_Write_String, 4831, 13,
    XREF_JvsEEPROM_Write_String,
    XRefZero)

    // Status error <JvsEEPROM_Write>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0D, '<' },
    { 0x0E, 'J' },
    { 0x11, 'E' },
    { 0x18, 'W' },
    { 0x1C, 'e' },
    { 0x1D, '>' },
OOVPA_END;

OOVPA_XREF(JvsFirmwareDownload_String, 4831, 14,
    XREF_JvsFirmwareDownload_String,
    XRefZero)

    // Status error1 <JvsFirmwareDownload>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0C, '1' },
    { 0x0E, '<' },
    { 0x0F, 'J' },
    { 0x12, 'F' },
    { 0x1A, 'D' },
    { 0x21, 'd' },
    { 0x22, '>' },
OOVPA_END;

OOVPA_XREF(JvsNodeReceivePacket_String, 4831, 13,
    XREF_JvsNodeReceivePacket_String,
    XRefZero)

    // Status waiting <JvsNodeReceivePacket>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0F, '<' },
    { 0x10, 'J' },
    { 0x13, 'N' },
    { 0x17, 'R' },
    { 0x1E, 'P' },
    { 0x24, '>' },
OOVPA_END;

OOVPA_XREF(JvsRTC_Read_String, 4831, 12,
    XREF_JvsRTC_Read_String,
    XRefZero)

    // Status wait <JvsRTC_Read>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0C, '<' },
    { 0x0D, 'J' },
    { 0x10, 'R' },
    { 0x14, 'R' },
    { 0x18, '>' }
OOVPA_END;

OOVPA_XREF(JvsRTC_Write_String, 4831, 12,
    XREF_JvsRTC_Write_String,
    XRefZero)

    // Status wait <JvsRTC_Write>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0C, '<' },
    { 0x0D, 'J' },
    { 0x10, 'R' },
    { 0x14, 'W' },
    { 0x19, '>' }
OOVPA_END;

OOVPA_XREF(JvsNodeSendPacket_String, 4831, 13,
    XREF_JvsNodeSendPacket_String,
    XRefZero)

    // Status waiting <JvsNodeSendPacket>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0F, '<' },
    { 0x10, 'J' },
    { 0x13, 'N' },
    { 0x17, 'S' },
    { 0x1B, 'P' },
    { 0x21, '>' },
OOVPA_END;

OOVPA_XREF(JvsFirmwareUpload_String, 4831, 14,
    XREF_JvsFirmwareUpload_String,
    XRefZero)

    // Status error1 <JvsFirmwareUpload>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0C, '1' },
    { 0x0E, '<' },
    { 0x0F, 'J' },
    { 0x12, 'F' },
    { 0x1A, 'U' },
    { 0x1F, 'd' },
    { 0x20, '>' },
OOVPA_END;

OOVPA_XREF(JvsScFirmwareDownload_String, 4831, 15,
    XREF_JvsScFirmwareDownload_String,
    XRefZero)

    // Status error1 <JvsScFirmwareDownload>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0C, '1' },
    { 0x0E, '<' },
    { 0x0F, 'J' },
    { 0x12, 'S' },
    { 0x14, 'F' },
    { 0x1C, 'D' },
    { 0x23, 'd' },
    { 0x24, '>' },
OOVPA_END;

OOVPA_XREF(JvsScFirmwareUpload_String, 4831, 14,
    XREF_JvsScFirmwareUpload_String,
    XRefZero)

    // Status waiting <JvsScFirmwareUpload>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0F, '<' },
    { 0x10, 'J' },
    { 0x13, 'S' },
    { 0x15, 'F' },
    { 0x1D, 'U' },
    { 0x22, 'd' },
    { 0x23, '>' },
OOVPA_END;

OOVPA_XREF(JvsScReceiveMidi_String, 4831, 13,
    XREF_JvsScReceiveMidi_String,
    XRefZero)

    // Status waiting <JvsScReceiveMidi>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0F, '<' },
    { 0x10, 'J' },
    { 0x13, 'S' },
    { 0x15, 'R' },
    { 0x1C, 'M' },
    { 0x20, '>' },
OOVPA_END;

OOVPA_XREF(JvsScReceiveRs323c_String, 4831, 13,
    XREF_JvsScReceiveRs323c_String,
    XRefZero)

    // Status error <JvsScReceiveRs323c>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0D, '<' },
    { 0x0E, 'J' },
    { 0x11, 'S' },
    { 0x13, 'R' },
    { 0x1A, 'R' },
    { 0x20, '>' },
OOVPA_END;

OOVPA_XREF(JvsScSendMidi_String, 4831, 13,
    XREF_JvsScSendMidi_String,
    XRefZero)

    // Status waiting <JvsScSendMidi>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'w' },
    { 0x0F, '<' },
    { 0x10, 'J' },
    { 0x13, 'S' },
    { 0x15, 'S' },
    { 0x19, 'M' },
    { 0x1D, '>' },
OOVPA_END;


OOVPA_XREF(JvsScSendRs323c_String, 4831, 13,
    XREF_JvsScSendRs323c_String,
    XRefZero)

    // Status error <JvsScSendRs323c>
    { 0x00, 'S' },
    { 0x01, 't' },
    { 0x02, 'a' },
    { 0x03, 't' },
    { 0x04, 'u' },
    { 0x05, 's' },
    { 0x07, 'e' },
    { 0x0D, '<' },
    { 0x0E, 'J' },
    { 0x11, 'S' },
    { 0x13, 'S' },
    { 0x17, 'R' },
    { 0x1D, '>' },
OOVPA_END;

// ******************************************************************
// * JVS_SendCommand
// ******************************************************************
OOVPA_XREF(JVS_SendCommand, 4831, 12,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x250, XREF_JVS_SendCommand_String),

    { 0x00, 0x81 },
    { 0x01, 0xEC },

    { 0x0A, 0xB4 },
    { 0x0B, 0x00 },

    { 0x0E, 0x85 },
    { 0x0F, 0xED },

    { 0x10, 0x56 },
    { 0x11, 0x57 },

    { 0x31, 0x8B },
    { 0x32, 0xB4 },

    { 0x90, 0x0F },
    { 0x96, 0xA8 }
OOVPA_END;

// ******************************************************************
// * JVS_SendCommand2
// * Variation of JVS_SendCommand
// ******************************************************************
OOVPA_XREF(JVS_SendCommand2, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x2C0, XREF_JVS_SendCommand_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x58 },
    { 0x03, 0x53 },
    { 0x86, 0x88 },
    { 0x87, 0x44 },
    { 0x88, 0x24 },
    { 0x89, 0x70 },
OOVPA_END;

// ******************************************************************
// * JVS_SendCommand3
// * Variation of JVS_SendCommand
// ******************************************************************
OOVPA_XREF(JVS_SendCommand3, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x28B, XREF_JVS_SendCommand_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x58 },
    { 0x03, 0x53 },
    { 0x86, 0x88 },
    { 0x87, 0x44 },
    { 0x88, 0x24 },
    { 0x89, 0x70 },
OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Read, 4831, 9,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x6E, XREF_JvsBACKUP_Read_String),

    { 0x00, 0x8B },
    { 0x11, 0x8D },
    { 0x12, 0x54 },
    { 0x13, 0x24 },
    { 0x17, 0x18 },
    { 0x43, 0xBE },
    { 0x44, 0x00 },
    { 0x4C, 0x05 },
    { 0x4D, 0x00 },
OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read2
// * Seems to be specfic to Crazy Taxi: Same function as above
// * Very different code structure, needs different signature
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Read2, 4831, 9,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x6F, XREF_JvsBACKUP_Read_String),

    { 0x00, 0x53 },
    { 0x10, 0x6A },
    { 0x12, 0x0F },
    { 0x13, 0x83 },
    { 0x18, 0x8B },
    { 0x43, 0x55 },
    { 0x44, 0x52 },
    { 0x4C, 0x8D },
    { 0x4D, 0x87 },
OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read3
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Read3, 4831, 5,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x5E, XREF_JvsBACKUP_Read_String),

    { 0x00, 0x8B },
    { 0x43, 0xBE },
    { 0x44, 0x00 },
    { 0x4C, 0x05 },
    { 0x4D, 0x00 },
OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Write
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Write, 4831, 15,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x6E, XREF_JvsBACKUP_Write_String),

    { 0x00, 0x8B },
    { 0x01, 0x44 },
    { 0x02, 0x24 },
    { 0x03, 0x04 },

    { 0x0A, 0x55 },
    { 0x0B, 0x56 },

    { 0x0E, 0x00 },
    { 0x0F, 0x6A },

    { 0x11, 0x8D },
    { 0x12, 0x54 },

    { 0x17, 0x1F },

    { 0x31, 0x51 },
    { 0x32, 0x6A },

    { 0x90, 0x0C },
    { 0x91, 0x2E }
OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Write2
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Write2, 4831, 5,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x5E, XREF_JvsBACKUP_Write_String),

    { 0x00, 0x8B },
    { 0x43, 0xBE },
    { 0x44, 0x00 },
    { 0x4C, 0x05 },
    { 0x4D, 0x00 },
OOVPA_END;


// ******************************************************************
// * JvsEEPROM_Read
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Read, 4831, 9,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x188, XREF_JvsEEPROM_Read_String),

    { 0x00, 0x51 },
    { 0x13, 0x40 },
    { 0x21, 0x74 },
    { 0x22, 0x24 },
    { 0x23, 0x18 },
    { 0x43, 0x6A },
    { 0x44, 0x17 },
    { 0x4C, 0x6A },
    { 0x4D, 0x40 },
OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Read2
// * Almost identical to JvsEEPROM_Read, but some bytes are shifted
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Read2, 4831, 9,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x1B0, XREF_JvsEEPROM_Read_String),

    { 0x00, 0x51 },
    { 0x12, 0x40 },
    { 0x21, 0x74 },
    { 0x22, 0x24 },
    { 0x23, 0x18 },
    { 0x43, 0x6A },
    { 0x44, 0x17 },
    { 0x4C, 0x6A },
    { 0x4D, 0x40 },
OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Read3
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Read3, 4831, 5,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x199, XREF_JvsEEPROM_Read_String),

    { 0x00, 0x83 },
    { 0x14, 0x40 },
    { 0x46, 0x6A },
    { 0x48, 0x6A },
    { 0x4A, 0x8D },
OOVPA_END;


// ******************************************************************
// * JvsEEPROM_Write
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Write, 4831, 10,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x18E, XREF_JvsEEPROM_Write_String),

    { 0x13, 0x08 },
    { 0x3E, 0x8D },
    { 0x3F, 0x44 },
    { 0x40, 0x24 },
    { 0x42, 0x50 },
    { 0x43, 0x6A },
    { 0x6B, 0xE1 },
    { 0x6C, 0xFF },
    { 0x70, 0x81 },
    { 0x71, 0xFA },
OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Write2
// * Almost identical to JvsEEPROM_Write2, but some bytes are shifted
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Write2, 4831, 10,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x1B6, XREF_JvsEEPROM_Write_String),
    { 0x12, 0x08 },

    { 0x3E, 0x8D },
    { 0x3F, 0x44 },
    { 0x40, 0x24 },
    { 0x42, 0x50 },
    { 0x43, 0x6A },
    { 0x6B, 0xE1 },
    { 0x6C, 0xFF },
    { 0x70, 0x81 },
    { 0x71, 0xFA },
OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Write3
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Write3, 4831, 3,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x199, XREF_JvsEEPROM_Write_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x34, 0x8B }
OOVPA_END;

// ******************************************************************
// * JvsFirmwareDownload
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload, 4831, 8,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1D4, XREF_JvsFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x4C },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 },
    { 0x0F, 0x83 },
    { 0x58, 0x6A },
    { 0x59, 0x20 },
OOVPA_END;

// ******************************************************************
// * JvsFirmwareDownload2
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload2, 4831, 8,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x203, XREF_JvsFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x4C },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 },
    { 0x0F, 0x83 },
    { 0x58, 0x6A },
    { 0x59, 0x20 },
OOVPA_END;

// ******************************************************************
// * JvsFirmwareDownload3
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload3, 4831, 5,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1E3, XREF_JvsFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x44 },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 }
OOVPA_END;


// ******************************************************************
// * JvsFirmwareDownload4
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload4, 4831, 5,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1CF, XREF_JvsFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x44 },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsFirmwareUpload
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x1B7, XREF_JvsFirmwareUpload_String),

    { 0x00, 0x83 },
    { 0x12, 0x83 },
    { 0x13, 0xF9 },
    { 0x14, 0x20 },
    { 0x40, 0x8D },
    { 0x41, 0x44 },
    { 0x42, 0x24 },
    { 0x43, 0x4C },
OOVPA_END;

// ******************************************************************
// * JvsFirmwareUpload2
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload2, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x1DE, XREF_JvsFirmwareUpload_String),

    { 0x00, 0x83 },
    { 0x12, 0x83 },
    { 0x13, 0xF9 },
    { 0x14, 0x20 },
    { 0x40, 0x8D },
    { 0x41, 0x44 },
    { 0x42, 0x24 },
    { 0x43, 0x4C },
OOVPA_END;


// ******************************************************************
// * JvsFirmwareUpload3
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload3, 4831, 5,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1DA, XREF_JvsFirmwareUpload_String),

    { 0x03, 0x8B },
    { 0x04, 0x44 },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 }
OOVPA_END;


// ******************************************************************
// * JvsFirmwareUpload4
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload4, 4831, 5,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1BF, XREF_JvsFirmwareUpload_String),

    { 0x03, 0x8B },
    { 0x04, 0x44 },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsNodeReceivePacket
// ******************************************************************
OOVPA_XREF(JvsNodeReceivePacket, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x6D, XREF_JvsNodeReceivePacket_String),

    { 0x28, 0x6A },
    { 0x29, 0x19 },
    { 0x2B, 0x6A },
    { 0x2C, 0x03 },
    { 0x54, 0xF6 },
    { 0x55, 0xC3 },
    { 0x56, 0x01 },
    { 0xC9, 0xC2 },
OOVPA_END;

// ******************************************************************
// * JvsNodeReceivePacket2
// ******************************************************************
OOVPA_XREF(JvsNodeReceivePacket2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x55, XREF_JvsNodeReceivePacket_String),

    { 0x00, 0x53 },
    { 0x01, 0x55 },
    { 0x02, 0x56 },
    { 0x03, 0x57 },
OOVPA_END;

// ******************************************************************
// * JvsNodeSendPacket
// ******************************************************************
OOVPA_XREF(JvsNodeSendPacket, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x6D, XREF_JvsNodeSendPacket_String),

    { 0x23, 0x6A },
    { 0x24, 0x20 },
    { 0x26, 0x6A },
    { 0x27, 0x0B },
    { 0x54, 0xF6 },
    { 0x55, 0xC3 },
    { 0x56, 0x01 },
    { 0xC9, 0xC2 },
OOVPA_END;

// ******************************************************************
// * JvsNodeSendPacket2
// ******************************************************************
OOVPA_XREF(JvsNodeSendPacket2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x55, XREF_JvsNodeSendPacket_String),

    { 0x00, 0x53 },
    { 0x01, 0x55 },
    { 0x02, 0x56 },
    { 0x03, 0x57 },
OOVPA_END;

// ******************************************************************
// * JvsRTC_Read
// ******************************************************************
OOVPA_XREF(JvsRTC_Read, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x81, XREF_JvsRTC_Read_String),

    { 0x05, 0x00 },
    { 0x06, 0x53 },
    { 0x10, 0x1C },
    { 0x11, 0x8B },
    { 0x12, 0x6C },
    { 0x13, 0x24 },
    { 0x2B, 0x55 },
    { 0x2C, 0xE8 },
OOVPA_END;

// ******************************************************************
// * JvsRTC_Read2
// ******************************************************************
OOVPA_XREF(JvsRTC_Read2, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x96, XREF_JvsRTC_Read_String),

    { 0x05, 0x00 },
    { 0x06, 0x53 },
    { 0x10, 0x1C },
    { 0x11, 0x8B },
    { 0x12, 0x6C },
    { 0x13, 0x24 },
    { 0x2B, 0x55 },
    { 0x2C, 0xE8 },
OOVPA_END;

// ******************************************************************
// * JvsRTC_Read3
// ******************************************************************
OOVPA_XREF(JvsRTC_Read3, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x68, XREF_JvsRTC_Read_String),

    { 0x00, 0x8B },
    { 0x10, 0x8B },
    { 0x14, 0x56 },
    { 0x15, 0x57 },
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload, 4831, 8,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1D4, XREF_JvsScFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x4C },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 },
    { 0x0F, 0x83 },
    { 0x58, 0x6A },
    { 0x59, 0x20 },
OOVPA_END;

// ******************************************************************
// * JvsRTC_Write
// ******************************************************************
OOVPA_XREF(JvsRTC_Write, 4831, 8,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x96, XREF_JvsRTC_Write_String),

    { 0x05, 0x00 },
    { 0x06, 0x53 },
    { 0x10, 0x1C },
    { 0x11, 0x8B },
    { 0x12, 0x6C },
    { 0x13, 0x24 },
    { 0x2B, 0x55 },
    { 0x2C, 0xE8 },
OOVPA_END;

// ******************************************************************
// * JvsRTC_Write2
// ******************************************************************
OOVPA_XREF(JvsRTC_Write2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x68, XREF_JvsRTC_Write_String),

    { 0x00, 0x8B },
    { 0x10, 0x8B },
    { 0x14, 0x56 },
    { 0x15, 0x57 },
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload2
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload2, 4831, 8,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x203, XREF_JvsScFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x4C },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 },
    { 0x0F, 0x83 },
    { 0x58, 0x6A },
    { 0x59, 0x20 },
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload3
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload3, 4831, 5,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1E3, XREF_JvsScFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x44 },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload4
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload4, 4831, 5,
    XRefNoSaveIndex,
    XRefOne)

    XREF_ENTRY(0x1CF, XREF_JvsScFirmwareDownload_String),

    { 0x03, 0x8B },
    { 0x04, 0x44 },
    { 0x05, 0x24 },
    { 0x06, 0x30 },
    { 0x07, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload
// ******************************************************************
OOVPA_XREF(JvsScFirmwareUpload, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0xA9, XREF_JvsScFirmwareUpload_String),

    { 0x00, 0x51 },
    { 0x01, 0x8B },
    { 0x05, 0x53 },
    { 0x06, 0x8B }
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload2
// ******************************************************************
OOVPA_XREF(JvsScFirmwareUpload2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0xBE, XREF_JvsScFirmwareUpload_String),

    { 0x00, 0x51 },
    { 0x01, 0x8B },
    { 0x05, 0x53 },
    { 0x06, 0x8B }
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload3
// ******************************************************************
OOVPA_XREF(JvsScFirmwareUpload3, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x9E, XREF_JvsScFirmwareUpload_String),

    { 0x00, 0x83 },
    { 0x03, 0x8B },
    { 0x07, 0x53 },
    { 0x08, 0x55 }
OOVPA_END;

// ******************************************************************
// * JvsScReceiveMidi
// ******************************************************************
OOVPA_XREF(JvsScReceiveMidi, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x7D, XREF_JvsScReceiveMidi_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsScReceiveMidi2
// ******************************************************************
OOVPA_XREF(JvsScReceiveMidi2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x65, XREF_JvsScReceiveMidi_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_XREF(JvsScReceiveRs323c, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x63, XREF_JvsScReceiveRs323c_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x56 }
OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c2
// ******************************************************************
OOVPA_XREF(JvsScReceiveRs323c2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x4F, XREF_JvsScReceiveRs323c_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x56 }
OOVPA_END;

// ******************************************************************
// * JvsScSendMidi
// ******************************************************************
OOVPA_XREF(JvsScSendMidi, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x7D, XREF_JvsScSendMidi_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsScSendMidi2
// ******************************************************************
OOVPA_XREF(JvsScSendMidi2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x5D, XREF_JvsScSendMidi_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x53 }
OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_XREF(JvsScSendRs323c, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x5E, XREF_JvsScSendRs323c_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0xC7 }
OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c2
// ******************************************************************
OOVPA_XREF(JvsScSendRs323c2, 4831, 4,
    XRefNoSaveIndex, XRefOne)

    XREF_ENTRY(0x4D, XREF_JvsScSendRs323c_String),

    { 0x00, 0x83 },
    { 0x01, 0xEC },
    { 0x02, 0x08 },
    { 0x03, 0x56 }
OOVPA_END;

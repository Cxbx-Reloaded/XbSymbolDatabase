// ******************************************************************
// *
// *   OOVPADatabase->JVS->4831.inl
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
// *  (c) 2019 Luke Usher
// *
// *  All rights reserved
// *
// ******************************************************************

OOVPA_XREF(JVS_SendCommand_String, 4831, 13,

           XREF_JVS_SendCommand_String,
           XRefZero)
{

    // JVS_STATUS_ERROR_DEVICE_NOT_CONNECTED2 from JVS_SendCommand
    OV_MATCH(0x00, 'J', 'V', 'S'),
    OV_MATCH(0x04, 'S'),
    OV_MATCH(0x0B, 'E'),
    OV_MATCH(0x11, 'D'),
    OV_MATCH(0x18, 'N'),
    OV_MATCH(0x1C, 'C'),
    OV_MATCH(0x25, '2'),
    OV_MATCH(0x27, 'f'),
    OV_MATCH(0x2C, 'J'),
    OV_MATCH(0x30, 'S'),
    OV_MATCH(0x34, 'C'),
} OOVPA_END;


OOVPA_XREF(JvsBACKUP_Read_String, 4831, 13,

           XREF_JvsBACKUP_Read_String,
           XRefZero)
{

    // Status error <JvsBACKUP_Read>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'B'),
    OV_MATCH(0x18, 'R'),
    OV_MATCH(0x1B, 'd'),
    OV_MATCH(0x1C, '>'),
} OOVPA_END;

OOVPA_XREF(JvsBACKUP_Write_String, 4831, 13,

           XREF_JvsBACKUP_Write_String,
           XRefZero)
{

    // Status error <JvsBACKUP_Write>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'B'),
    OV_MATCH(0x18, 'W'),
    OV_MATCH(0x1C, 'e'),
    OV_MATCH(0x1D, '>'),
} OOVPA_END;

OOVPA_XREF(JvsEEPROM_Read_String, 4831, 13,

           XREF_JvsEEPROM_Read_String,
           XRefZero)
{

    // Status error <JvsEEPROM_Read>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'E'),
    OV_MATCH(0x18, 'R'),
    OV_MATCH(0x1B, 'd'),
    OV_MATCH(0x1C, '>'),
} OOVPA_END;

OOVPA_XREF(JvsEEPROM_Write_String, 4831, 13,

           XREF_JvsEEPROM_Write_String,
           XRefZero)
{

    // Status error <JvsEEPROM_Write>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'E'),
    OV_MATCH(0x18, 'W'),
    OV_MATCH(0x1C, 'e'),
    OV_MATCH(0x1D, '>'),
} OOVPA_END;

OOVPA_XREF(JvsFirmwareDownload_String, 4831, 14,

           XREF_JvsFirmwareDownload_String,
           XRefZero)
{

    // Status error1 <JvsFirmwareDownload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0C, '1'),
    OV_MATCH(0x0E, '<', 'J'),
    OV_MATCH(0x12, 'F'),
    OV_MATCH(0x1A, 'D'),
    OV_MATCH(0x21, 'd'),
    OV_MATCH(0x22, '>'),
} OOVPA_END;

OOVPA_XREF(JvsNodeReceivePacket_String, 4831, 13,

           XREF_JvsNodeReceivePacket_String,
           XRefZero)
{

    // Status waiting <JvsNodeReceivePacket>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'N'),
    OV_MATCH(0x17, 'R'),
    OV_MATCH(0x1E, 'P'),
    OV_MATCH(0x24, '>'),
} OOVPA_END;

OOVPA_XREF(JvsRTC_Read_String, 4831, 12,

           XREF_JvsRTC_Read_String,
           XRefZero)
{

    // Status wait <JvsRTC_Read>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0C, '<', 'J'),
    OV_MATCH(0x10, 'R'),
    OV_MATCH(0x14, 'R'),
    OV_MATCH(0x18, '>'),
} OOVPA_END;

OOVPA_XREF(JvsRTC_Write_String, 4831, 12,

           XREF_JvsRTC_Write_String,
           XRefZero)
{

    // Status wait <JvsRTC_Write>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0C, '<', 'J'),
    OV_MATCH(0x10, 'R'),
    OV_MATCH(0x14, 'W'),
    OV_MATCH(0x19, '>'),
} OOVPA_END;

OOVPA_XREF(JvsNodeSendPacket_String, 4831, 13,

           XREF_JvsNodeSendPacket_String,
           XRefZero)
{

    // Status waiting <JvsNodeSendPacket>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'N'),
    OV_MATCH(0x17, 'S'),
    OV_MATCH(0x1B, 'P'),
    OV_MATCH(0x21, '>'),
} OOVPA_END;

OOVPA_XREF(JvsFirmwareUpload_String, 4831, 14,

           XREF_JvsFirmwareUpload_String,
           XRefZero)
{

    // Status error1 <JvsFirmwareUpload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0C, '1'),
    OV_MATCH(0x0E, '<', 'J'),
    OV_MATCH(0x12, 'F'),
    OV_MATCH(0x1A, 'U'),
    OV_MATCH(0x1F, 'd'),
    OV_MATCH(0x20, '>'),
} OOVPA_END;

OOVPA_XREF(JvsScFirmwareDownload_String, 4831, 15,

           XREF_JvsScFirmwareDownload_String,
           XRefZero)
{

    // Status error1 <JvsScFirmwareDownload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0C, '1'),
    OV_MATCH(0x0E, '<', 'J'),
    OV_MATCH(0x12, 'S'),
    OV_MATCH(0x14, 'F'),
    OV_MATCH(0x1C, 'D'),
    OV_MATCH(0x23, 'd'),
    OV_MATCH(0x24, '>'),
} OOVPA_END;

OOVPA_XREF(JvsScFirmwareUpload_String, 4831, 14,

           XREF_JvsScFirmwareUpload_String,
           XRefZero)
{

    // Status waiting <JvsScFirmwareUpload>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x15, 'F'),
    OV_MATCH(0x1D, 'U'),
    OV_MATCH(0x22, 'd'),
    OV_MATCH(0x23, '>'),
} OOVPA_END;

OOVPA_XREF(JvsScReceiveMidi_String, 4831, 13,

           XREF_JvsScReceiveMidi_String,
           XRefZero)
{

    // Status waiting <JvsScReceiveMidi>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x15, 'R'),
    OV_MATCH(0x1C, 'M'),
    OV_MATCH(0x20, '>'),
} OOVPA_END;

OOVPA_XREF(JvsScReceiveRs323c_String, 4831, 13,

           XREF_JvsScReceiveRs323c_String,
           XRefZero)
{

    // Status error <JvsScReceiveRs323c>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'S'),
    OV_MATCH(0x13, 'R'),
    OV_MATCH(0x1A, 'R'),
    OV_MATCH(0x20, '>'),
} OOVPA_END;

OOVPA_XREF(JvsScSendMidi_String, 4831, 13,

           XREF_JvsScSendMidi_String,
           XRefZero)
{

    // Status waiting <JvsScSendMidi>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'w'),
    OV_MATCH(0x0F, '<', 'J'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x15, 'S'),
    OV_MATCH(0x19, 'M'),
    OV_MATCH(0x1D, '>'),
} OOVPA_END;


OOVPA_XREF(JvsScSendRs323c_String, 4831, 13,

           XREF_JvsScSendRs323c_String,
           XRefZero)
{

    // Status error <JvsScSendRs323c>
    OV_MATCH(0x00, 'S', 't', 'a', 't', 'u', 's'),
    OV_MATCH(0x07, 'e'),
    OV_MATCH(0x0D, '<', 'J'),
    OV_MATCH(0x11, 'S'),
    OV_MATCH(0x13, 'S'),
    OV_MATCH(0x17, 'R'),
    OV_MATCH(0x1D, '>'),
} OOVPA_END;

// ******************************************************************
// * JVS_SendCommand
// ******************************************************************
OOVPA_XREF(JVS_SendCommand, 4831, 1 + 12,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x250, XREF_JVS_SendCommand_String),

    OV_MATCH(0x00, 0x81, 0xEC),

    OV_MATCH(0x0A, 0xB4, 0x00),

    OV_MATCH(0x0E, 0x85, 0xED),

    OV_MATCH(0x10, 0x56, 0x57),

    OV_MATCH(0x31, 0x8B, 0xB4),

    OV_MATCH(0x90, 0x0F),

    OV_MATCH(0x96, 0xA8),
} OOVPA_END;

// ******************************************************************
// * JVS_SendCommand2
// * Variation of JVS_SendCommand
// ******************************************************************
OOVPA_XREF(JVS_SendCommand2, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x2C0, XREF_JVS_SendCommand_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x58, 0x53),

    OV_MATCH(0x86, 0x88, 0x44, 0x24, 0x70),
} OOVPA_END;

// ******************************************************************
// * JVS_SendCommand3
// * Variation of JVS_SendCommand
// ******************************************************************
OOVPA_XREF(JVS_SendCommand3, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x28B, XREF_JVS_SendCommand_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x58, 0x53),

    OV_MATCH(0x86, 0x88, 0x44, 0x24, 0x70),
} OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Read, 4831, 1 + 9,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x6E, XREF_JvsBACKUP_Read_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x11, 0x8D, 0x54, 0x24),

    OV_MATCH(0x17, 0x18),

    OV_MATCH(0x43, 0xBE, 0x00),

    OV_MATCH(0x4C, 0x05, 0x00),
} OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read2
// * Seems to be specfic to Crazy Taxi: Same function as above
// * Very different code structure, needs different signature
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Read2, 4831, 1 + 9,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x6F, XREF_JvsBACKUP_Read_String),

    OV_MATCH(0x00, 0x53),

    OV_MATCH(0x10, 0x6A),

    OV_MATCH(0x12, 0x0F, 0x83),

    OV_MATCH(0x18, 0x8B),

    OV_MATCH(0x43, 0x55, 0x52),

    OV_MATCH(0x4C, 0x8D, 0x87),
} OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read3
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Read3, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x5E, XREF_JvsBACKUP_Read_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x43, 0xBE, 0x00),

    OV_MATCH(0x4C, 0x05, 0x00),
} OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Write
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Write, 4831, 1 + 15,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x6E, XREF_JvsBACKUP_Write_String),

    OV_MATCH(0x00, 0x8B, 0x44, 0x24, 0x04),

    OV_MATCH(0x0A, 0x55, 0x56),

    OV_MATCH(0x0E, 0x00, 0x6A),

    OV_MATCH(0x11, 0x8D, 0x54),

    OV_MATCH(0x17, 0x1F),

    OV_MATCH(0x31, 0x51, 0x6A),

    OV_MATCH(0x90, 0x0C, 0x2E),
} OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Write2
// ******************************************************************
OOVPA_XREF(JvsBACKUP_Write2, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x5E, XREF_JvsBACKUP_Write_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x43, 0xBE, 0x00),

    OV_MATCH(0x4C, 0x05, 0x00),
} OOVPA_END;


// ******************************************************************
// * JvsEEPROM_Read
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Read, 4831, 1 + 9,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x188, XREF_JvsEEPROM_Read_String),

    OV_MATCH(0x00, 0x51),

    OV_MATCH(0x13, 0x40),

    OV_MATCH(0x21, 0x74, 0x24, 0x18),

    OV_MATCH(0x43, 0x6A, 0x17),

    OV_MATCH(0x4C, 0x6A, 0x40),
} OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Read2
// * Almost identical to JvsEEPROM_Read, but some bytes are shifted
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Read2, 4831, 1 + 9,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1B0, XREF_JvsEEPROM_Read_String),

    OV_MATCH(0x00, 0x51),

    OV_MATCH(0x12, 0x40),

    OV_MATCH(0x21, 0x74, 0x24, 0x18),

    OV_MATCH(0x43, 0x6A, 0x17),

    OV_MATCH(0x4C, 0x6A, 0x40),
} OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Read3
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Read3, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x199, XREF_JvsEEPROM_Read_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x14, 0x40),

    OV_MATCH(0x46, 0x6A),

    OV_MATCH(0x48, 0x6A),

    OV_MATCH(0x4A, 0x8D),
} OOVPA_END;


// ******************************************************************
// * JvsEEPROM_Write
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Write, 4831, 1 + 10,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x18E, XREF_JvsEEPROM_Write_String),

    OV_MATCH(0x13, 0x08),

    OV_MATCH(0x3E, 0x8D, 0x44, 0x24),

    OV_MATCH(0x42, 0x50, 0x6A),

    OV_MATCH(0x6B, 0xE1, 0xFF),

    OV_MATCH(0x70, 0x81, 0xFA),
} OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Write2
// * Almost identical to JvsEEPROM_Write2, but some bytes are shifted
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Write2, 4831, 1 + 10,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1B6, XREF_JvsEEPROM_Write_String),
    OV_MATCH(0x12, 0x08),

    OV_MATCH(0x3E, 0x8D, 0x44, 0x24),

    OV_MATCH(0x42, 0x50, 0x6A),

    OV_MATCH(0x6B, 0xE1, 0xFF),

    OV_MATCH(0x70, 0x81, 0xFA),
} OOVPA_END;

// ******************************************************************
// * JvsEEPROM_Write3
// ******************************************************************
OOVPA_XREF(JvsEEPROM_Write3, 4831, 1 + 3,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x199, XREF_JvsEEPROM_Write_String),

    OV_MATCH(0x00, 0x83, 0xEC),

    OV_MATCH(0x34, 0x8B),
} OOVPA_END;

// ******************************************************************
// * JvsFirmwareDownload
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1D4, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
} OOVPA_END;

// ******************************************************************
// * JvsFirmwareDownload2
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload2, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x203, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
} OOVPA_END;

// ******************************************************************
// * JvsFirmwareDownload3
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload3, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1E3, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
} OOVPA_END;


// ******************************************************************
// * JvsFirmwareDownload4
// ******************************************************************
OOVPA_XREF(JvsFirmwareDownload4, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1CF, XREF_JvsFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsFirmwareUpload
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1B7, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x12, 0x83, 0xF9, 0x20),

    OV_MATCH(0x40, 0x8D, 0x44, 0x24, 0x4C),
} OOVPA_END;

// ******************************************************************
// * JvsFirmwareUpload2
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload2, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1DE, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x12, 0x83, 0xF9, 0x20),

    OV_MATCH(0x40, 0x8D, 0x44, 0x24, 0x4C),
} OOVPA_END;


// ******************************************************************
// * JvsFirmwareUpload3
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload3, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1DA, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
} OOVPA_END;


// ******************************************************************
// * JvsFirmwareUpload4
// ******************************************************************
OOVPA_XREF(JvsFirmwareUpload4, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1BF, XREF_JvsFirmwareUpload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsNodeReceivePacket
// ******************************************************************
OOVPA_XREF(JvsNodeReceivePacket, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x6D, XREF_JvsNodeReceivePacket_String),

    OV_MATCH(0x28, 0x6A, 0x19),

    OV_MATCH(0x2B, 0x6A, 0x03),

    OV_MATCH(0x54, 0xF6),

    OV_MATCH(0x55, 0xC3, 0x01),

    OV_MATCH(0xC9, 0xC2),
} OOVPA_END;

// ******************************************************************
// * JvsNodeReceivePacket2
// ******************************************************************
OOVPA_XREF(JvsNodeReceivePacket2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x55, XREF_JvsNodeReceivePacket_String),

    OV_MATCH(0x00, 0x53, 0x55, 0x56, 0x57),
} OOVPA_END;

// ******************************************************************
// * JvsNodeSendPacket
// ******************************************************************
OOVPA_XREF(JvsNodeSendPacket, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x6D, XREF_JvsNodeSendPacket_String),

    OV_MATCH(0x23, 0x6A, 0x20),

    OV_MATCH(0x26, 0x6A, 0x0B),

    OV_MATCH(0x54, 0xF6, 0xC3, 0x01),

    OV_MATCH(0xC9, 0xC2),
} OOVPA_END;

// ******************************************************************
// * JvsNodeSendPacket2
// ******************************************************************
OOVPA_XREF(JvsNodeSendPacket2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x55, XREF_JvsNodeSendPacket_String),

    OV_MATCH(0x00, 0x53, 0x55, 0x56, 0x57),
} OOVPA_END;

// ******************************************************************
// * JvsRTC_Read
// ******************************************************************
OOVPA_XREF(JvsRTC_Read, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x81, XREF_JvsRTC_Read_String),

    OV_MATCH(0x05, 0x00, 0x53),

    OV_MATCH(0x10, 0x1C, 0x8B, 0x6C, 0x24),

    OV_MATCH(0x2B, 0x55, 0xE8),
} OOVPA_END;

// ******************************************************************
// * JvsRTC_Read2
// ******************************************************************
OOVPA_XREF(JvsRTC_Read2, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x96, XREF_JvsRTC_Read_String),

    OV_MATCH(0x05, 0x00, 0x53),

    OV_MATCH(0x10, 0x1C, 0x8B, 0x6C, 0x24),

    OV_MATCH(0x2B, 0x55, 0xE8),
} OOVPA_END;

// ******************************************************************
// * JvsRTC_Read3
// ******************************************************************
OOVPA_XREF(JvsRTC_Read3, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x68, XREF_JvsRTC_Read_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x10, 0x8B),

    OV_MATCH(0x14, 0x56, 0x57),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1D4, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
} OOVPA_END;

// ******************************************************************
// * JvsRTC_Write
// ******************************************************************
OOVPA_XREF(JvsRTC_Write, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x96, XREF_JvsRTC_Write_String),

    OV_MATCH(0x05, 0x00, 0x53),

    OV_MATCH(0x10, 0x1C, 0x8B, 0x6C, 0x24),

    OV_MATCH(0x2B, 0x55, 0xE8),
} OOVPA_END;

// ******************************************************************
// * JvsRTC_Write2
// ******************************************************************
OOVPA_XREF(JvsRTC_Write2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x68, XREF_JvsRTC_Write_String),

    OV_MATCH(0x00, 0x8B),

    OV_MATCH(0x10, 0x8B),

    OV_MATCH(0x14, 0x56, 0x57),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload2
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload2, 4831, 1 + 8,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x203, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x4C, 0x24, 0x30, 0x53),

    OV_MATCH(0x0F, 0x83),

    OV_MATCH(0x58, 0x6A, 0x20),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload3
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload3, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1E3, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareDownload4
// ******************************************************************
OOVPA_XREF(JvsScFirmwareDownload4, 4831, 1 + 5,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x1CF, XREF_JvsScFirmwareDownload_String),

    OV_MATCH(0x03, 0x8B, 0x44, 0x24, 0x30, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload
// ******************************************************************
OOVPA_XREF(JvsScFirmwareUpload, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0xA9, XREF_JvsScFirmwareUpload_String),

    OV_MATCH(0x00, 0x51, 0x8B),
    OV_MATCH(0x05, 0x53, 0x8B),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload2
// ******************************************************************
OOVPA_XREF(JvsScFirmwareUpload2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0xBE, XREF_JvsScFirmwareUpload_String),

    OV_MATCH(0x00, 0x51, 0x8B),

    OV_MATCH(0x05, 0x53, 0x8B),
} OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload3
// ******************************************************************
OOVPA_XREF(JvsScFirmwareUpload3, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x9E, XREF_JvsScFirmwareUpload_String),

    OV_MATCH(0x00, 0x83),

    OV_MATCH(0x03, 0x8B),

    OV_MATCH(0x07, 0x53, 0x55),
} OOVPA_END;

// ******************************************************************
// * JvsScReceiveMidi
// ******************************************************************
OOVPA_XREF(JvsScReceiveMidi, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x7D, XREF_JvsScReceiveMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsScReceiveMidi2
// ******************************************************************
OOVPA_XREF(JvsScReceiveMidi2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x65, XREF_JvsScReceiveMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_XREF(JvsScReceiveRs323c, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x63, XREF_JvsScReceiveRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x56),
} OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c2
// ******************************************************************
OOVPA_XREF(JvsScReceiveRs323c2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x4F, XREF_JvsScReceiveRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x56),
} OOVPA_END;

// ******************************************************************
// * JvsScSendMidi
// ******************************************************************
OOVPA_XREF(JvsScSendMidi, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x7D, XREF_JvsScSendMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsScSendMidi2
// ******************************************************************
OOVPA_XREF(JvsScSendMidi2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x5D, XREF_JvsScSendMidi_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x53),
} OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_XREF(JvsScSendRs323c, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x5E, XREF_JvsScSendRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0xC7),
} OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c2
// ******************************************************************
OOVPA_XREF(JvsScSendRs323c2, 4831, 1 + 4,

           XRefNoSaveIndex,
           XRefOne)
{

    XREF_ENTRY(0x4D, XREF_JvsScSendRs323c_String),

    OV_MATCH(0x00, 0x83, 0xEC, 0x08, 0x56),
} OOVPA_END;

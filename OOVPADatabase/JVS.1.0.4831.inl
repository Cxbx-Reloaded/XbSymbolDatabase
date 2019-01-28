// ******************************************************************
// *
// *   OOVPADatabase->JVS.1.0.4831.inl
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

// ******************************************************************
// * JVS_SendCommand
// ******************************************************************
OOVPA_NO_XREF(JVS_SendCommand, 4831, 12)
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
// * Variation of JVS_SendCommand, seems to take different parameters
// ******************************************************************
OOVPA_NO_XREF(JVS_SendCommand2, 4831, 8)
	{ 0x00, 0x83 },
	{ 0x01, 0xEC },	{ 0x02, 0x58 },	{ 0x03, 0x53 },	{ 0x86, 0x88 },	{ 0x87, 0x44 },	{ 0x88, 0x24 },	{ 0x89, 0x70 },
OOVPA_END;

// ******************************************************************
// * JvsBACKUP_Read
// ******************************************************************
OOVPA_NO_XREF(JvsBACKUP_Read, 4831, 9)
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
OOVPA_NO_XREF(JvsBACKUP_Read2, 4831, 9)
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
// * JvsBACKUP_Write
// ******************************************************************
OOVPA_NO_XREF(JvsBACKUP_Write, 4831, 15)
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
// * JvsEEPROM_Read
// ******************************************************************
OOVPA_NO_XREF(JvsEEPROM_Read, 4831, 9)
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
OOVPA_NO_XREF(JvsEEPROM_Read2, 4831, 9)
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
// * JvsEEPROM_Write
// ******************************************************************
OOVPA_NO_XREF(JvsEEPROM_Write, 4831, 10)
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
OOVPA_NO_XREF(JvsEEPROM_Write2, 4831, 10)
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
// * JvsFirmwareDownload
// ******************************************************************
OOVPA_NO_XREF(JvsFirmwareDownload, 4831, 8)
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
// * JvsFirmwareUpload
// ******************************************************************
OOVPA_NO_XREF(JvsFirmwareUpload, 4831, 8)
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
// * JvsNodeReceivePacket
// ******************************************************************
OOVPA_NO_XREF(JvsNodeReceivePacket, 4831, 8)
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
// * JvsNodeSendPacket
// ******************************************************************
OOVPA_NO_XREF(JvsNodeSendPacket, 4831, 8)
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
// * JvsRTC_Read
// ******************************************************************
OOVPA_NO_XREF(JvsRTC_Read, 4831, 8)
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
// * JvsScFirmwareDownload
// ******************************************************************
OOVPA_NO_XREF(JvsScFirmwareDownload, 4831, 8)
	{ 0x03, 0x8B },
	{ 0x04, 0x4C },
	{ 0x05, 0x24 },
	{ 0x06, 0x30 },
	{ 0x07, 0x53 },
	{ 0x0F, 0x83 },
	{ 0x10, 0xF9 },
	{ 0x11, 0x20 },
OOVPA_END;

// ******************************************************************
// * JvsScFirmwareUpload
// ******************************************************************
OOVPA_NO_XREF(JvsScFirmwareUpload, 4831, 8)
	{ 0x00, 0x51 },
	{ 0x10, 0x83 },
	{ 0x11, 0xF9 },
	{ 0x12, 0x20 },
	{ 0x3C, 0x8D },
	{ 0x3D, 0x44 },
	{ 0x3E, 0x24 },
	{ 0x3F, 0x2C },
OOVPA_END;

// ******************************************************************
// * JvsScReceiveMidi
// ******************************************************************
OOVPA_NO_XREF(JvsScReceiveMidi, 4831, 8)
	{ 0x00, 0x83 },
	{ 0x01, 0xEC },
	{ 0x10, 0x44 },
	{ 0x11, 0x24 },
	{ 0x30, 0x8D },
	{ 0x31, 0x4C },
	{ 0x90, 0x4C },
	{ 0x91, 0x24 },
OOVPA_END;

// ******************************************************************
// * JvsScReceiveRs323c
// ******************************************************************
OOVPA_NO_XREF(JvsScReceiveRs323c, 4831, 8)
	{ 0x00, 0x83 },
	{ 0x01, 0xEC },
	{ 0x13, 0xC7 },
	{ 0x14, 0x44 },
	{ 0x30, 0x8D },
	{ 0x31, 0x4C },
	{ 0x40, 0x57 },
	{ 0x41, 0x6A },
OOVPA_END;

// ******************************************************************
// * JvsScSendMidi
// ******************************************************************
OOVPA_NO_XREF(JvsScSendMidi, 4831, 8)
	{ 0x00, 0x83 },
	{ 0x01, 0xEC },
	{ 0x10, 0x24 },
	{ 0x11, 0x0C },
	{ 0x30, 0x0C },
	{ 0x31, 0x50 },
	{ 0x90, 0x8D },
	{ 0x91, 0x4C },
OOVPA_END;

// ******************************************************************
// * JvsScSendRs323c
// ******************************************************************
OOVPA_NO_XREF(JvsScSendRs323c, 4831, 8)
	{ 0x00, 0x83 },
	{ 0x01, 0xEC },
	{ 0x13, 0xE8 },
	{ 0x1E, 0x8D },
	{ 0x30, 0x24 },
	{ 0x31, 0x18 },
	{ 0x3E, 0x6A },
	{ 0x40, 0xE8 },
OOVPA_END;

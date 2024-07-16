// ******************************************************************
// *
// *   OOVPADatabase->JVS_OOVPA.inl
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

// Titles which did compiled with full library
//   [LibV] Title Name                       |  Verify   |  Comments
//-------------------------------------------------------------------
// * [4831] House of The Dead 3              |   100%    | Contain full library.
// * [4831] Crazy Taxi 3                     |   100%    | Contain full library.
// * [5028] SegaBoot v2.00.0                 |   100%    | Contain full library.
// * [5028] SegaBoot v2.13.0                 |   100%    | Contain full library.
// * [5028] Virtua Cop 3                     |   100%    | Contain full library.
// * [5455] Ollie King                       |   100%    | Contain full library.
// * [5558] Outrun 2                         |   100%    | Contain full library.
// * [5659] Outrun 2 SP                      |   100%    | Contain full library.
// * [5788] Ghost Squad                      |   100%    | Contain full library.
// * [5849] Sega Golf 2006                   |   100%    | Contain full library.

// NOTES:
//  * JVSSendCommand1/2/3 sometime changes even when the library version
//    is the same except the functions are quite different in layout, etc
//    and some offsets are different within them too.

#ifndef JVS_OOVPA_INL
#define JVS_OOVPA_INL

#include "OOVPA.h"

#include "JVS/4831.inl"

// ******************************************************************
// * JVSLIB_OOVPA
// ******************************************************************
OOVPATable JVSLIB_OOVPA[] = {

    // Variables
    REGISTER_OOVPAS_M(SYM_VAR(JVS_g_pPINSA),
                      SYM_SIG(4831)),
    REGISTER_OOVPAS_M(SYM_VAR(JVS_g_pPINSB),
                      SYM_SIG(4831)),
    // Chihiro/JVS (XRef strings)
    REGISTER_OOVPAS(SYM_VAR(JVS_SendCommand_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsBACKUP_Read_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsBACKUP_Write_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsEEPROM_Read_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsEEPROM_Write_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsFirmwareDownload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsFirmwareUpload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsNodeReceivePacket_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsNodeSendPacket_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsRTC_Read_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsRTC_Write_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScFirmwareDownload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScFirmwareUpload_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScReceiveMidi_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScReceiveRs323c_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScSendMidi_String),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_VAR(JvsScSendRs323c_String),
                    SYM_SIG(4831)),

    // Chihiro/JVS (Functions)
    REGISTER_OOVPAS(SYM_FUN(JVS_SendCommand, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, Command), PARAM(stk, unknown3), PARAM(stk, Length), PARAM(stk, unknown5), PARAM(stk, unknown6), PARAM(stk, unknown7), PARAM(stk, unknown8))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JVS_SendCommand, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, Command), PARAM(stk, unknown3), PARAM(stk, Length), PARAM(stk, unknown5), PARAM(stk, unknown6), PARAM(stk, unknown7), PARAM(stk, unknown8))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JVS_SendCommand, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, Command), PARAM(stk, unknown3), PARAM(stk, Length), PARAM(stk, unknown5), PARAM(stk, unknown6), PARAM(stk, unknown7), PARAM(stk, unknown8))),
                    SYM_SIG(4831, 4832)),
    REGISTER_OOVPAS(SYM_FUN(JvsBACKUP_Read, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsBACKUP_Read, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsBACKUP_Read, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsBACKUP_Write, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsBACKUP_Write, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsEEPROM_Read, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Read, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Read, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsEEPROM_Write, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Write, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsEEPROM_Write, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsFirmwareDownload, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareDownload, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareDownload, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareDownload, SUFFIX(4), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsFirmwareUpload, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareUpload, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareUpload, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsFirmwareUpload, SUFFIX(4), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsNodeReceivePacket, STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsNodeReceivePacket, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsNodeSendPacket, STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsNodeSendPacket, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsRTC_Read, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, time), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsRTC_Read, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, time), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsRTC_Read, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, time), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsRTC_Write, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, time), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsRTC_Write, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, time), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScFirmwareDownload, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareDownload, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareDownload, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareDownload, SUFFIX(4), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScFirmwareUpload, STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareUpload, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScFirmwareUpload, SUFFIX(3), STACK(/*default*/), PARAMS(PARAM(stk, Offset), PARAM(stk, Length), PARAM(stk, Buffer), PARAM(stk, unknown4))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScReceiveMidi, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScReceiveMidi, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScReceiveRs323c, STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScReceiveRs323c, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScSendMidi, STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScSendMidi, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, unknown1), PARAM(stk, unknown2), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN(JvsScSendRs323c, STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
    REGISTER_OOVPAS(SYM_FUN_ALT(JvsScSendRs323c, SUFFIX(2), STACK(/*default*/), PARAMS(PARAM(stk, Buffer), PARAM(stk, Length), PARAM(stk, unknown3))),
                    SYM_SIG(4831)),
};

// ******************************************************************
// * JVSLIB_OOVPA_COUNT
// ******************************************************************
#define JVSLIB_OOVPA_COUNT XBSDB_ARRAY_SIZE(JVSLIB_OOVPA)

#endif

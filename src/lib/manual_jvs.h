// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
// ******************************************************************
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
// *  All rights reserved
// *
// ******************************************************************
#pragma once

static inline void manual_register_jvs(iXbSymbolContext* pContext)
{
    internal_RegisterValidXRefAddr(pContext, Lib_JVS, XbSymbolLib_JVS, XREF_JVS_g_pPINSA, 4831, "JVS_g_pPINSA", symbol_variable, call_none, 0, NULL);
    internal_RegisterValidXRefAddr(pContext, Lib_JVS, XbSymbolLib_JVS, XREF_JVS_g_pPINSB, 4831, "JVS_g_pPINSB", symbol_variable, call_none, 0, NULL);
}

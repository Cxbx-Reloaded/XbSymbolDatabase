// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#, and Java: https://pvs-studio.com

// SPDX-License-Identifier: MIT
#pragma once

static inline void manual_register_jvs(iXbSymbolContext* pContext)
{
    internal_RegisterValidXRefAddr_M(pContext, Lib_JVS, XbSymbolLib_JVS, XREF_JVS_g_pPINSA, 4831, "JVS_g_pPINSA");
    internal_RegisterValidXRefAddr_M(pContext, Lib_JVS, XbSymbolLib_JVS, XREF_JVS_g_pPINSB, 4831, "JVS_g_pPINSB");
}

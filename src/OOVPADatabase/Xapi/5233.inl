// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * MU_Init
// ******************************************************************
// Generic OOVPA as of 5233 and newer.
OOVPA_SIG_HEADER_NO_XREF(MU_Init,
                         5233)
OOVPA_SIG_MATCH(

    // push ebp
    // mov ebp, esp
    // sub esp, 0x0C
    OV_MATCH(0x00, 0x55, 0x8B, 0xEC, 0x83, 0xEC, 0x0C),

    // push eax
    // push 0x00
    // push 0x3A
    // lea eax, [ebp-0x0C]
    OV_MATCH(0x8E, 0x50, 0x6A, 0x00, 0x6A, 0x3A, 0x8D, 0x45, 0xF4), // Was 5233 offset 0x8A

    //
);

// SPDX-License-Identifier: ODbL-1.0

// ******************************************************************
// * XInitDevices
// ******************************************************************
// * NOTE: We are actually intercepting USBD_Init, because
// *       XInitDevices Simply redirects to that function
// ******************************************************************
OOVPA_SIG_HEADER_NO_XREF(XInitDevices,
                         5120)
OOVPA_SIG_MATCH(

    { 0x0E, 0x75 },
    { 0x20, 0xBE },
    { 0x2E, 0xC0 },
    { 0x3E, 0xEC },
    { 0x50, 0x0F },
    { 0x5F, 0xE8 },
    { 0x70, 0x5F },
    //
);

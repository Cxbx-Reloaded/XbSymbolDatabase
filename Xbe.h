// ******************************************************************
// *
// *   Xbe.h
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
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *  (c) 2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#pragma once

#include <stdint.h>

#pragma pack(1)

// Xbe section header
typedef struct _xbe_s_flags {
    uint32_t bWritable : 1;                     // writable flag
    uint32_t bPreload : 1;                      // preload flag
    uint32_t bExecutable : 1;                   // executable flag
    uint32_t bInsertedFile : 1;                 // inserted file flag
    uint32_t bHeadPageRO : 1;                   // head page read only flag
    uint32_t bTailPageRO : 1;                   // tail page read only flag
    uint32_t Unused_a1 : 1;                     // unused (or unknown)
    uint32_t Unused_a2 : 1;                     // unused (or unknown)
    uint32_t Unused_b1 : 8;                     // unused (or unknown)
    uint32_t Unused_b2 : 8;                     // unused (or unknown)
    uint32_t Unused_b3 : 8;                     // unused (or unknown)
} xbe_s_flags;

typedef struct _xbe_section_header {

    union {
        xbe_s_flags dwFlags;
        uint32_t dwFlags_value;
    };

    uint32_t dwVirtualAddr;                     // virtual address
    uint32_t dwVirtualSize;                     // virtual size
    uint32_t dwRawAddr;                         // file offset to raw data
    uint32_t dwSizeofRaw;                       // size of raw data
    const char*  SectionNameAddr;               // section name addr
    uint32_t dwSectionRefCount;                 // section reference count
    uint32_t dwHeadSharedRefCountAddr;          // head shared page reference count address
    uint32_t dwTailSharedRefCountAddr;          // tail shared page reference count address
    uint8_t bzSectionDigest[20];                // section digest
} xbe_section_header;

// Xbe library versions
typedef struct _xbe_lv_flags {
    uint16_t QFEVersion : 13;                   // QFE Version
    uint16_t Approved : 2;                      // Approved? (0:no, 1:possibly, 2:yes)
    uint16_t bDebugBuild : 1;                   // Is this a debug build?
} xbe_lv_flags;
typedef struct _xbe_library_version {
    char   szName[8];                           // library name
    uint16_t wMajorVersion;                     // major version
    uint16_t wMinorVersion;                     // minor version
    uint16_t wBuildVersion;                     // build version

    union {
        xbe_lv_flags wFlags;
        uint16_t wFlags_value;
    };
} xbe_library_version;

// Xbe header
typedef struct _xbe_h_InitFlags {
    uint32_t bMountUtilityDrive : 1;            // mount utility drive flag
    uint32_t bFormatUtilityDrive : 1;           // format utility drive flag
    uint32_t bLimit64MB : 1;                    // limit development kit run time memory to 64mb flag
    uint32_t bDontSetupHarddisk : 1;            // don't setup hard disk flag
    uint32_t Unused : 4;                        // unused (or unknown)
    uint32_t Unused_b1 : 8;                     // unused (or unknown)
    uint32_t Unused_b2 : 8;                     // unused (or unknown)
    uint32_t Unused_b3 : 8;                     // unused (or unknown)
} xbe_h_InitFlags;

typedef struct _xbe_header {
    uint32_t dwMagic;                           // 0x0000 - magic number [should be "XBEH"]
    uint8_t pbDigitalSignature[256];            // 0x0004 - digital signature
    uint32_t dwBaseAddr;                        // 0x0104 - base address
    uint32_t dwSizeofHeaders;                   // 0x0108 - size of headers
    uint32_t dwSizeofImage;                     // 0x010C - size of image
    uint32_t dwSizeofImageHeader;               // 0x0110 - size of image header
    uint32_t dwTimeDate;                        // 0x0114 - timedate stamp
    uint32_t dwCertificateAddr;                 // 0x0118 - certificate address
    uint32_t dwSections;                        // 0x011C - number of sections
    xbe_section_header* pSectionHeadersAddr;    // 0x0120 - section headers address

    union {                                     // 0x0124 - initialization flags
        xbe_h_InitFlags dwInitFlags;
        uint32_t dwInitFlags_value;
    };

    uint32_t dwEntryAddr;                       // 0x0128 - entry point address
    uint32_t dwTLSAddr;                         // 0x012C - thread local storage directory address
    uint32_t dwPeStackCommit;                   // 0x0130 - size of stack commit
    uint32_t dwPeHeapReserve;                   // 0x0134 - size of heap reserve
    uint32_t dwPeHeapCommit;                    // 0x0138 - size of heap commit
    uint32_t dwPeBaseAddr;                      // 0x013C - original base address
    uint32_t dwPeSizeofImage;                   // 0x0140 - size of original image
    uint32_t dwPeChecksum;                      // 0x0144 - original checksum
    uint32_t dwPeTimeDate;                      // 0x0148 - original timedate stamp
    uint32_t dwDebugPathnameAddr;               // 0x014C - debug pathname address
    uint32_t dwDebugFilenameAddr;               // 0x0150 - debug filename address
    uint32_t dwDebugUnicodeFilenameAddr;        // 0x0154 - debug unicode filename address
    uint32_t dwKernelImageThunkAddr;            // 0x0158 - kernel image thunk address
    uint32_t dwNonKernelImportDirAddr;          // 0x015C - non kernel import directory address
    uint32_t dwLibraryVersions;                 // 0x0160 - number of library versions
    xbe_library_version* pLibraryVersionsAddr;  // 0x0164 - library versions address
    uint32_t dwKernelLibraryVersionAddr;        // 0x0168 - kernel library version address
    uint32_t dwXAPILibraryVersionAddr;          // 0x016C - xapi library version address
    uint32_t dwLogoBitmapAddr;                  // 0x0170 - logo bitmap address
    uint32_t dwSizeofLogoBitmap;                // 0x0174 - logo bitmap size
} xbe_header;
#pragma pack()

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

#pragma pack(1)

// Xbe section header
typedef struct _xbe_s_flags {
    unsigned int bWritable : 1;                 // writable flag
    unsigned int bPreload : 1;                  // preload flag
    unsigned int bExecutable : 1;               // executable flag
    unsigned int bInsertedFile : 1;             // inserted file flag
    unsigned int bHeadPageRO : 1;               // head page read only flag
    unsigned int bTailPageRO : 1;               // tail page read only flag
    unsigned int Unused_a1 : 1;                 // unused (or unknown)
    unsigned int Unused_a2 : 1;                 // unused (or unknown)
    unsigned int Unused_b1 : 8;                 // unused (or unknown)
    unsigned int Unused_b2 : 8;                 // unused (or unknown)
    unsigned int Unused_b3 : 8;                 // unused (or unknown)
} xbe_s_flags;

typedef struct _xbe_section_header {

    union {
        xbe_s_flags dwFlags;
        unsigned int dwFlags_value;
    };

    unsigned int dwVirtualAddr;                 // virtual address
    unsigned int dwVirtualSize;                 // virtual size
    unsigned int dwRawAddr;                     // file offset to raw data
    unsigned int dwSizeofRaw;                   // size of raw data
    const char*  SectionNameAddr;               // section name addr
    unsigned int dwSectionRefCount;             // section reference count
    unsigned int dwHeadSharedRefCountAddr;      // head shared page reference count address
    unsigned int dwTailSharedRefCountAddr;      // tail shared page reference count address
    unsigned char bzSectionDigest[20];          // section digest
} xbe_section_header;

// Xbe library versions
typedef struct _xbe_lv_flags {
    unsigned short QFEVersion : 13;             // QFE Version
    unsigned short Approved : 2;                // Approved? (0:no, 1:possibly, 2:yes)
    unsigned short bDebugBuild : 1;             // Is this a debug build?
} xbe_lv_flags;
typedef struct _xbe_library_version {
    char   szName[8];                           // library name
    unsigned short wMajorVersion;               // major version
    unsigned short wMinorVersion;               // minor version
    unsigned short wBuildVersion;               // build version

    union {
        xbe_lv_flags wFlags;
        unsigned short wFlags_value;
    };
} xbe_library_version;

// Xbe header
typedef struct _xbe_h_InitFlags {
    unsigned int bMountUtilityDrive : 1;        // mount utility drive flag
    unsigned int bFormatUtilityDrive : 1;       // format utility drive flag
    unsigned int bLimit64MB : 1;                // limit development kit run time memory to 64mb flag
    unsigned int bDontSetupHarddisk : 1;        // don't setup hard disk flag
    unsigned int Unused : 4;                    // unused (or unknown)
    unsigned int Unused_b1 : 8;                 // unused (or unknown)
    unsigned int Unused_b2 : 8;                 // unused (or unknown)
    unsigned int Unused_b3 : 8;                 // unused (or unknown)
} xbe_h_InitFlags;

typedef struct _xbe_header {
    unsigned int dwMagic;                       // 0x0000 - magic number [should be "XBEH"]
    unsigned char pbDigitalSignature[256];      // 0x0004 - digital signature
    unsigned int dwBaseAddr;                    // 0x0104 - base address
    unsigned int dwSizeofHeaders;               // 0x0108 - size of headers
    unsigned int dwSizeofImage;                 // 0x010C - size of image
    unsigned int dwSizeofImageHeader;           // 0x0110 - size of image header
    unsigned int dwTimeDate;                    // 0x0114 - timedate stamp
    unsigned int dwCertificateAddr;             // 0x0118 - certificate address
    unsigned int dwSections;                    // 0x011C - number of sections
    xbe_section_header* pSectionHeadersAddr;    // 0x0120 - section headers address

    union {                                     // 0x0124 - initialization flags
        xbe_h_InitFlags dwInitFlags;
        unsigned int dwInitFlags_value;
    };

    unsigned int dwEntryAddr;                   // 0x0128 - entry point address
    unsigned int dwTLSAddr;                     // 0x012C - thread local storage directory address
    unsigned int dwPeStackCommit;               // 0x0130 - size of stack commit
    unsigned int dwPeHeapReserve;               // 0x0134 - size of heap reserve
    unsigned int dwPeHeapCommit;                // 0x0138 - size of heap commit
    unsigned int dwPeBaseAddr;                  // 0x013C - original base address
    unsigned int dwPeSizeofImage;               // 0x0140 - size of original image
    unsigned int dwPeChecksum;                  // 0x0144 - original checksum
    unsigned int dwPeTimeDate;                  // 0x0148 - original timedate stamp
    unsigned int dwDebugPathnameAddr;           // 0x014C - debug pathname address
    unsigned int dwDebugFilenameAddr;           // 0x0150 - debug filename address
    unsigned int dwDebugUnicodeFilenameAddr;    // 0x0154 - debug unicode filename address
    unsigned int dwKernelImageThunkAddr;        // 0x0158 - kernel image thunk address
    unsigned int dwNonKernelImportDirAddr;      // 0x015C - non kernel import directory address
    unsigned int dwLibraryVersions;             // 0x0160 - number of library versions
    xbe_library_version* pLibraryVersionsAddr;  // 0x0164 - library versions address
    unsigned int dwKernelLibraryVersionAddr;    // 0x0168 - kernel library version address
    unsigned int dwXAPILibraryVersionAddr;      // 0x016C - xapi library version address
    unsigned int dwLogoBitmapAddr;              // 0x0170 - logo bitmap address
    unsigned int dwSizeofLogoBitmap;            // 0x0174 - logo bitmap size
} xbe_header;
#pragma pack()

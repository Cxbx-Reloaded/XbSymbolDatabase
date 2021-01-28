// ******************************************************************
// *
// *   OOVPA.h
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
// *  (c) 2002-2003 Aaron Robinson <caustik@caustik.com>
// *  (c) 2017 PatrickvL
// *  (c) 2017-2018 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#ifndef OOVPA_H
#define OOVPA_H

// http://stackoverflow.com/questions/5134523/msvc-doesnt-expand-va-args-correctly
// MSVC_EXPAND works around a Visual C++ problem, expanding __VA_ARGS__ incorrectly:
#define MSVC_EXPAND(x) x

#define STRINGIZEX(x) #x
#define STRINGIZE(x)  STRINGIZEX(x)

#pragma pack(1)

// ******************************************************************
// * Optimized (Offset, Value)-Pair Array
// ******************************************************************
typedef struct _OOVPA {
    // This OOVPA field, Count, indicates the number of
    // {Offset, Value}-pairs present in the Lovp array,
    // available after casting this OOVPA to LOOVPA.
    // (This Count INCLUDES optional leading {Offset, XREF_*-enum}-
    // pairs - see comment at XRefCount.)
    unsigned char Count;

    // This OOVPA field, XRefCount, contains the number of
    // {Offset, XREF_*-enum}-pairs that come before all other
    // {Offset, Value}-pairs.
    // (The {Offset, XREF_*-enum}-pairs are INCLUDED in OOVPA.Count)
    // (Also, see comments at XRefZero and XRefOne.)
    unsigned char XRefCount;

    // This OOVPA field, XRefSaveIndex, contains either an
    // XREF_* enum value, or the XRefNoSaveIndex marker when there's
    // no XREF_* enum defined for this OOVPA.
    unsigned short XRefSaveIndex;

    unsigned char DetectSelect;

    unsigned char Padding[3];

    // Define LOVP here to reduce type definition complexity.
    // (Otherwise, if defined in the template classes, that would mean
    // that for each template instance, the type is redefined. Let's
    // avoid that.)
} OOVPA;

// {Offset, Value}-pair(s)
typedef struct _LOVP {
    // Both the Offset and Value are 16-bit to allow for XRefs with a
    // large offset. Value can be safely cast to 8-bit for OOVPA, but must
    // remain 16-bit for XRef entries.
    unsigned short offset;
    union {
        // Generic structure TODO: Remove me after replace array to macro for OOVPA database
        unsigned short value;

        struct {
            unsigned char unused;
            unsigned char value;
        } byte;

        struct {
            unsigned short index;
        } xref;
    };
} LOVP;

// Set variable's padding to 0.
#define VARPADSET 0

/*
// XRefZero constant, when set in the OOVPA.XRefCount field,
// indicates there are no {offset, XREF_*-enum} present in the OOVPA.

// XRefOne constant, when set in the OOVPA.XRefCount field,
// indicates the OOVPA contains one (1) {offset, XREF_* enum} pair.

// Sometimes, there can be more than one {Offset, XREF_*-enum}
// pair at the start of the OOVPA's.
*/
#define XRefZero  0
#define XRefOne   1
#define XRefTwo   2
#define XRefThree 3
#define XRefFour  4

// This XRefNoSaveIndex constant, when set in the OOVPA.XRefSaveIndex
// field, functions as a marker indicating there's no XREF_* enum
// defined for the OOVPA.
#define XRefNoSaveIndex 0xFFFF

// TODO: Rename to OV_XREF.
// Macro used for storing an XRef {Offset, XREF}-Pair.
// clang-format off
#define XREF_ENTRY( Offset, XRef) \
    { Offset, .xref.index = XRef }
// clang-format on

// Macro for storing a normal (non-XRef) {Offset, Value}-Pair
// Offsets can go up to 16 bits, values are always one byte (8 bits)
// clang-format off
#define OV_BYTE(Offset, Value) \
    { Offset, .value = Value }
// clang-format on
// TODO: Remove above line, then uncomment the line below for easy swap after OOVPA database has been fixed.
//  { Offset, { .unused = 0, .value = Value } }

// Macro for determine how the OOVPA scan will process for detection.
#define DetectDefault 0
#define DetectFirst   1
#define DetectSecond  2
#define DetectThird   3
#define DetectFourth  4

// ******************************************************************
// * Large Optimized (Offset,Value)-Pair Array
// ******************************************************************
#pragma warning(push)
#pragma warning(disable : 4200)
typedef struct _LOOVPA {
    OOVPA Header;

    // Large (Offset,Value)-Pair(s)
    LOVP Lovp[];
} LOOVPA;
#pragma warning(pop)

#define OOVPA_XREF_EXTEND(Name, Version, Count, XRefSaveIndex, XRefCount, DetectSelect) \
    LOOVPA Name##_##Version = { Count, XRefCount, XRefSaveIndex, DetectSelect, VARPADSET, VARPADSET, VARPADSET, {

#define OOVPA_XREF_DETECT(Name, Version, Count, XRefSaveIndex, XRefCount, DetectSelect) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefSaveIndex, XRefCount, DetectSelect)

#define OOVPA_NO_XREF_DETECT(Name, Version, Count, DetectSelect) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefNoSaveIndex, XRefZero, DetectSelect)

#define OOVPA_XREF(Name, Version, Count, XRefSaveIndex, XRefCount) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefSaveIndex, XRefCount, DetectDefault)

#define OOVPA_NO_XREF(Name, Version, Count) \
    OOVPA_XREF_EXTEND(Name, Version, Count, XRefNoSaveIndex, XRefZero, DetectDefault)

// clang-format off
#define OOVPA_END } }
// clang-format on

// ******************************************************************
// * OOVPATable
// ******************************************************************
typedef struct _OOVPATable {
    OOVPA* Oovpa;
    char* szFuncName;
    unsigned short Version; // : 13; // 2^13 = 8192, enough to store lowest and higest possible Library Version number in
} OOVPATable;

// http://en.cppreference.com/w/cpp/iterator/size
//#include <iterator>
//#define XBSDB_ARRAY_SIZE(x) std::size(x)
#define XBSDB_ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

// clang-format off
#define OOVPA_TABLE_ENTRY_FULL(Oovpa, DebugName, Version) \
    { &Oovpa##_##Version.Header, DebugName, Version }
// clang-format on

// Regiser each version into one symbol table database.
#define REGISTER_OOVPA(Symbol, Version) \
    OOVPA_TABLE_ENTRY_FULL(Symbol, #Symbol, Version)

// Based on https://codecraft.co/2014/11/25/variadic-macros-tricks/
// and https://groups.google.com/d/msg/comp.std.c/d-6Mj5Lko_s/jqonQLK20HcJ
// clang-format off
#define REGISTER_OOVPA_0(...)
 #define REGISTER_OOVPA_1(Symbol, Version) REGISTER_OOVPA(Symbol, Version)
 #define REGISTER_OOVPA_2(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_1(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_3(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_2(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_4(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_3(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_5(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_4(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_6(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_5(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_7(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_6(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_8(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_7(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_9(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_8(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_10(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_9(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_11(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_10(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_12(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_11(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_13(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_12(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_14(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_13(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_15(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_14(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_16(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_15(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_17(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_16(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_18(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_17(Symbol, __VA_ARGS__))
 #define REGISTER_OOVPA_19(Symbol, Version, ...) REGISTER_OOVPA(Symbol, Version), MSVC_EXPAND(REGISTER_OOVPA_18(Symbol, __VA_ARGS__))
// clang-format on

// clang-format off
#define OV_BYTES_0(...)
 #define OV_BYTES_1(Offset, Value) OV_BYTE(Offset, Value)
 #define OV_BYTES_2(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_1(Offset+1, __VA_ARGS__))
 #define OV_BYTES_3(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_2(Offset+1, __VA_ARGS__))
 #define OV_BYTES_4(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_3(Offset+1, __VA_ARGS__))
 #define OV_BYTES_5(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_4(Offset+1, __VA_ARGS__))
 #define OV_BYTES_6(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_5(Offset+1, __VA_ARGS__))
 #define OV_BYTES_7(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_6(Offset+1, __VA_ARGS__))
 #define OV_BYTES_8(Offset, Value, ...) OV_BYTE(Offset, Value), MSVC_EXPAND(OV_BYTES_7(Offset+1, __VA_ARGS__))
// clang-format on

// Accept any number of args >= N, but expand to just the Nth one. In this case,
// we have settled on 20 as N. We could pick a different number by adjusting
// the count of throwaway args before N. Note that this macro is preceded by
// an underscore--it's an implementation detail, not something we expect people
// to call directly.
#define _GET_NTH_ARG(                                 \
    _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, \
    _9, _8, _7, _6, _5, _4, _3, _2, _1, _0,           \
    N, ...) N

#define REGISTER_OOVPAS(Symbol, ...)                                                                                        \
    MSVC_EXPAND(_GET_NTH_ARG("ignored", __VA_ARGS__,                                                                        \
                             REGISTER_OOVPA_19, REGISTER_OOVPA_18, REGISTER_OOVPA_17, REGISTER_OOVPA_16, REGISTER_OOVPA_15, \
                             REGISTER_OOVPA_14, REGISTER_OOVPA_13, REGISTER_OOVPA_12, REGISTER_OOVPA_11, REGISTER_OOVPA_10, \
                             REGISTER_OOVPA_9, REGISTER_OOVPA_8, REGISTER_OOVPA_7, REGISTER_OOVPA_6, REGISTER_OOVPA_5,      \
                             REGISTER_OOVPA_4, REGISTER_OOVPA_3, REGISTER_OOVPA_2, REGISTER_OOVPA_1, REGISTER_OOVPA_0)(Symbol, __VA_ARGS__))

// See _GET_NTH_ARG comment for details.
// Even though x86 instructions can be anywhere from 1 to 15 bytes long,
// we don't need to fill in whole instruction.
#define _GET_NTH_ARG_OVP(               \
    _8, _7, _6, _5, _4, _3, _2, _1, _0, \
    N, ...) N

#define OV_MATCH(Offset, ...)                                                                \
    MSVC_EXPAND(_GET_NTH_ARG_OVP("ignored", __VA_ARGS__,                                     \
                                 OV_BYTES_8, OV_BYTES_7, OV_BYTES_6, OV_BYTES_5, OV_BYTES_4, \
                                 OV_BYTES_3, OV_BYTES_2, OV_BYTES_1, OV_BYTES_0)(Offset, __VA_ARGS__))

#pragma pack()

#endif

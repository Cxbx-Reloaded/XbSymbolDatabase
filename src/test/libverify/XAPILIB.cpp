// SPDX-License-Identifier: ODbL-1.0

#include <map>
#include <string>

#include "unittest.hpp"

static const library_list database_full = {

    // derived xrefs
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(XapiLastErrorCode, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),

    // OOVPA sigs
    // Without xrefs dependency
    REGISTER_SYMBOL_INLINE_XAPI(_cinit, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(_rtinit, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiFormatObjectAttributes, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiMapLetterToDirectory, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XLaunchNewImageA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XUnmountAlternateTitleA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),

    // With xrefs dependency (unorder, need to scan next before order list)
    REGISTER_SYMBOL_INLINE_XAPI(mainXapiStartup, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(GetLastError, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(SetLastError, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiBootToDash, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiSelectCachePartition, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiSetLastNTError, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),

    // With xrefs dependency (order)
    REGISTER_SYMBOL_INLINE_XAPI(CreateMutexA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(MoveFileA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiInitProcess, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XCalculateSignatureBegin, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    // REGISTER_SYMBOL_INLINE(XCalculateSignatureBeginEx, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // no signature and currently unknown.
    REGISTER_SYMBOL_INLINE_XAPI(GetOverlappedResult, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(GetTimeZoneInformation, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(GetTypeInformation_4, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(GetTypeInformation_8, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(OutputDebugStringA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(OutputDebugStringW, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(mainCRTStartup, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(QueueUserAPC, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(QueryPerformanceCounter, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(SignalObjectAndWait, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XAutoPowerDownResetTimer, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XFormatUtilityDrive, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XGetLaunchInfo, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XGetSectionSize, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMountAlternateTitleA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMountUtilityDrive, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XSetProcessQuantumLength, VER_RANGE(4134, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(timeKillEvent, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(timeSetEvent, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

static const library_list fiber_full = {

    // derived xrefs
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(XapiCurrentFiber, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_VAR_OFFSET(XapiThreadFiberData, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),

    // OOVPA sigs

    // With xrefs dependency (order)
    REGISTER_SYMBOL_INLINE_XAPI(ConvertThreadToFiber, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(CreateFiber, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(DeleteFiber, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(SwitchToFiber, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiFiberStartup, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

static const library_list thread_full = {

    // derived xrefs
    REGISTER_SYMBOL_INLINE_XAPI(_tls_array, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(_tls_index, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiThreadNotifyRoutineList, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_XapiCurrentTopLevelFilter, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),

    // OOVPA sigs
    // Without xrefs dependency
    REGISTER_SYMBOL_INLINE(XapiCallThreadNotifyRoutines, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),

    // With xrefs dependency (unorder, need to scan next before order list)
    REGISTER_SYMBOL_INLINE_XAPI(UnhandledExceptionFilter, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XapiThreadStartup, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),

    // With xrefs dependency (order)
    REGISTER_SYMBOL_INLINE_XAPI(CreateThread, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(ExitThread, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(SwitchToThread, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(GetExitCodeThread, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(GetThreadPriority, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(RaiseException, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(SetThreadPriority, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE_XAPI(SetThreadPriorityBoost, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XRegisterThreadNotifyRoutine, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

static const library_list mu_optional = {

    // derived xrefs
    REGISTER_SYMBOL_INLINE(g_DeviceType_MU, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_XapiAltLett_MU, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_XapiMountedMUs, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),

    // With xrefs dependency (order)
    REGISTER_SYMBOL_INLINE(XMUWriteNameToDriveLetter, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)), // So far is only found in dashboard
};

static const library_list mu_full = {

    // OOVPA sigs

    // With xrefs dependency (order)
    REGISTER_SYMBOL_INLINE(MU_Init, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMountMUA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMountMURootA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMUNameFromDriveLetter, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMUPortFromDriveLetterA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XMUSlotFromDriveLetterA, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XReadMUMetaData, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XUnmountMU, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

static const library_list xinput_optional = {

    // variables
    REGISTER_SYMBOL_INLINE(g_DeviceType_Mouse, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_DeviceType_SBC, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),

    // derived xrefs
    REGISTER_SYMBOL_INLINE(g_DeviceType_Gamepad, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_DeviceType_IRDongle, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_DeviceType_Keyboard, VER_RANGE(0, VER_MAX, VER_NONE, VER_NONE)),
};

static const library_list xinput_full = {

    // derived xrefs
    REGISTER_SYMBOL_INLINE(g_DeviceTypeInfoTableBegin, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(g_DeviceTypeInfoTableEnd, VER_RANGE(4242, VER_MAX, VER_NONE, VER_NONE)),

    // OOVPA sigs

    // With xrefs dependency (order)
    REGISTER_SYMBOL_INLINE(XGetDeviceChanges, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XGetDeviceEnumerationStatus, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XGetDevices, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XID_fCloseDevice, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInitDevices, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputClose, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputGetCapabilities, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputGetDeviceDescription, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputGetState, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputOpen, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputPoll, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputSetLightgunCalibration, VER_RANGE(4831, VER_MAX, VER_NONE, VER_NONE)),
    REGISTER_SYMBOL_INLINE(XInputSetState, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

static const library_list usbd_full = {
    // OOVPA sigs
    // Without xrefs dependency
    REGISTER_SYMBOL_INLINE(IUsbInit_GetMaxDeviceTypeCount, VER_RANGE(3911, VER_MAX, VER_NONE, VER_NONE)),
};

enum LOCAL_XREFS {
#undef XREF_SYMBOL
#define XREF_SYMBOL(e) e,
#include <xref/xapilib.def>
#undef XREF_SYMBOL
    LOCAL_COUNT
};

// Verify if symbol name is at start of offset.
#define XREF_SYMBOL_GET(e) e
#define XREF_OFFSET XREF_SYMBOL_GET(XAPI__tls_array)
static_assert(XREF_OFFSET == 0);
// Then get symbol's actual offset.
#undef XREF_SYMBOL_GET
#define XREF_SYMBOL_GET(e) XREF_##e

static const subcategory_db xapilib_db = {
    .name = "general",
    .optional = nullptr,
    .min = nullptr,
    .full = &database_full,
};

static const subcategory_db fiber_db = {
    .name = "fiber",
    .optional = nullptr,
    .min = nullptr,
    .full = &fiber_full,
};

static const subcategory_db thread_db = {
    .name = "thread",
    .optional = nullptr,
    .min = nullptr,
    .full = &thread_full,
};

static const subcategory_db mu_db = {
    .name = "Memory Unit",
    .optional = &mu_optional,
    .min = nullptr,
    .full = &mu_full,
};

static const subcategory_db xinput_db = {
    .name = "XInput",
    .optional = &xinput_optional,
    .min = nullptr,
    .full = &xinput_full,
};

static const subcategory_db usbd_db = {
    .name = "USBD",
    .optional = nullptr,
    .min = nullptr,
    .full = &usbd_full,
};

// TODO: Create (O)HCD subcategory database when relative signatures are added
// NOTE: May need split into HCD and OHCD groups.

// TODO: Create OHCI subcategory database when relative signatures are added

void getLibraryXAPILIB(library_db& lib_db)
{
    lib_db.subcategories = { &xapilib_db, &fiber_db, &thread_db, &mu_db, &xinput_db, &usbd_db };
    lib_db.xref_offset = XREF_OFFSET;
    lib_db.xref_total = LOCAL_COUNT;
    lib_db.xref_exclude = 0;
}

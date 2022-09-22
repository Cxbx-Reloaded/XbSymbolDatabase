// ******************************************************************
// *
// *   OOVPADatabase->Xapi_OOVPA.inl
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
// *  (c) 2017 jarupxx
// *
// *  All rights reserved
// *
// ******************************************************************

// Titles which did compiled with full library
//   [LibV] Title Name                       |  Verify   |  Comments
//-------------------------------------------------------------------
// * [3911] Cel Damage                       |   100%    | have 38/45 library.
// * [3950] Shikigami no Shiro               |   100%    | have 35/45 library.
// * [4034] Dark Summit                      |   100%    | have 21/45 library.
// * [4039] New Legends                      |   100%    | have 30/45 library.
// * [4134] Double-S.T.E.A.L                 |   100%    | have 39/47 library.
// * [4242] NFL Blitz 2002                   |   100%    | have 46/48 library.
// * [4361] ESPN NBA 2Night 2002             |   100%    | have 33/48 library.
// * [4432] RedCard 2003                     |   100%    | have 46/48 library.
// * [4531] NHL HITZ 2003                    |   100%    | have 41/48 library.
// * [4627] MLB SlugFest 2003                |   100%    | have 46/48 library.
// * [4721] Terminator - Dawn of Fate        |   100%    | have 41/48 library.
// * [4831] Whacked                          |   100%    | have 42/50 library.
// * [4928] Drihoo                           |   100%    | have 42/50 library.
// * [5028] Shikigami no Shiro Evolution     |   100%    | have 39/50 library.
// * [5120] N.U.D.E.@                        |   100%    | have 40/50 library.
// * [5233] Evil Dead                        |   100%    | have 39/50 library.
// * [5344] Starsky & Hutch                  |   100%    | have 43/50 library.
// * [5455] NCAA Football 2004               |   100%    | have 44/50 library.
// * [5558] XIII                             |   100%    | have 42/50 library.
// * [5659] LMA Manager 2004                 |   100%    | have 42/50 library.
// * [5788] All-Star Baseball 2005           |   100%    | have 42/50 library.
// * [5849] Nickelodeon Tak 2                |   100%    | have 40/50 library.

// TODO: Known Xapi OOVPA issue list
// * Verification needed: Function Name ( Revision )
//   * ConvertThreadToFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * CreateFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * DeleteFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * ExitThread (4034)
//   * GetExitCodeThread (4034)
//   * GetOverlappedResult (4034)
//   * GetThreadPriority (4034)
//   * GetTimeZoneInformation (4034)
//   * GetTypeInformation (4134)
//   * MoveFileA (4034)
//   * QueueUserAPC (4034)
//   * SetThreadPriority (4034)
//   * SetThreadPriorityBoost (4034)
//   * SignalObjectAndWait (4034)
//   * SwitchToFiber (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * SwitchToThread (4034)
//   * XCalculateSignatureBegin (4034)
//   * XGetDeviceChanges (4034)
//   * XInputGetCapabilities (4034)
//   * XInputGetDeviceDescription (4928, 5028, 5120, 5233, 5455)
//   * XInputPoll (4034)
//   * XMountAlternateTitleA (4034)
//   * XMountMURootA (3950, 4034, 4039, 4134, 5028, 5120, 5233)
//   * XapiFiberStartup (3950, 4034, 4039, 4134, 4531, 4721, 5028, 5455)
//   * timeKillEvent (3950, 4034, 5028, 5233)
//   * timeSetEvent (4034, 5233)
//   * XReadMUMetaData (3911, 3950, 4034, 4039, 4134)
// * Following OOVPA are invalid
//   * CloseHandle (3911) // Has exact asm codes _ResetEvent@4
//   * ReadFileEx (3911) // Has exact asm codes _WriteFileEx@20
//   * WriteFileEx (3911) // Has exact asm codes _ReadFileEx@20
//   * lstrcmpiW (3911) // Necessary XREF _xCompareStringW@20
// * Following OOVPA are missing (Obsolete?)
//   * GetThreadPriorityBoost
//   * RtlAllocateHeap
//   * RtlCreateHeap
//   * RtlDestroyHeap
//   * RtlFreeHeap
//   * RtlReAllocateHeap
//   * RtlSizeHeap
//   * XCalculateSignatureBeginEx
//   * XCalculateSignatureEnd
//   * XCalculateSignatureUpdate
// NOTE: Known Xapi OOVPA not included in initial revision.
//   * XFormatUtilityDrive (4242)
//   * XSetProcessQuantumLength (4134)
//   * XInputGetDeviceDescription (4831)
//   * XGetDeviceEnumerationStatus (4831)
// List of known Symbols may can be add to database (3911)
//   * CancelWaitableTimer
//   * CharLowerA
//   * CharLowerW
//   * CharUpperA
//   * CharUpperW
//   * CloseHandle
//   * CompareFileTime
//   * CopyFileA
//   * CopyFileExA
//   * CopyRect
//   * CreateDirectoryA
//   * CreateEventA
//   * CreateFileA
//   * CreateIoCompletionPort
//   * CreateSemaphoreA
//   * CreateWaitableTimerA
//   * DebugBreak
//   * DebugPrint
//   * DeleteFileA
//   * DeviceIoControl
//   * DmGetCurrentValue
//   * DmTell
//   * DuplicateHandle
//   * EqualRect
//   * FileTimeToLocalFileTime
//   * FileTimeToSystemTime
//   * FindFirstFileA
//   * FindNextFileA
//   * FlushFileBuffers
//   * GetCurrentThreadId
//   * GetDiskFreeSpaceExA
//   * GetFileAttributesA
//   * GetFileAttributesExA
//   * GetFileInformationByHandle
//   * GetFileSize
//   * GetFileSizeEx
//   * GetFileTime
//   * GetLocalTime
//   * GetNextNickname
//   * GetProcessHeap
//   * GetQueuedCompletionStatus
//   * GetSystemTime
//   * GetSystemTimeAsFileTime
//   * GetThreadPriorityBoost
//   * GetThreadTimes
//   * GetTickCount
//   * GetVolumeInformationA
//   * GlobalAlloc
//   * GlobalMemoryStatus
//   * GlobalReAlloc
//   * HCD_CancelRequest
//   * HCD_DisableRootHubPort
//   * HCD_DriverEntry
//   * HCD_EnumHardware
//   * HCD_NewHostController
//   * HCD_ResetRootHubPort
//   * HCD_SubmitRequest
//   * HeapCreate
//   * HeapDestroy
//   * HeapFree
//   * HexDigitToChar
//   * InflateRect
//   * IntersectRect
//   * IsBadCodePtr
//   * IsBadReadPtr
//   * IsBadStringPtrA
//   * IsBadStringPtrW
//   * IsBadWritePtr
//   * IsRectEmpty
//   * KeGetCurrentIrql
//   * KeGetCurrentIrql
//   * KeGetCurrentPrcb
//   * KeGetCurrentPrcb
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * KeGetCurrentThread
//   * LocalAlloc
//   * LocalFileTimeToFileTime
//   * LocalFree
//   * LocalHandle
//   * LocalLock
//   * LocalReAlloc
//   * LocalSize
//   * LocalUnlock
//   * lstrcatA
//   * lstrcatW
//   * lstrcmpA
//   * lstrcmpiA
//   * lstrcmpiW
//   * lstrcmpW
//   * lstrcpyA
//   * lstrcpynA
//   * lstrcpynW
//   * lstrcpyW
//   * lstrlenA
//   * lstrlenW
//   * MoveFileExA
//   * MoveFileWithProgressA
//   * MulDiv
//   * MultiByteToWideChar
//   * MU_AddDevice
//   * MU_CloseDeviceObject
//   * MU_CreateDeviceObject
//   * MU_RemoveDevice
//   * OffsetRect
//   * OpenEventA
//   * OpenMutexA
//   * OpenSemaphoreA
//   * OpenWaitableTimerA
//   * PortNumberToRootHubPort
//   * PostQueuedCompletionStatus
//   * PtInRect
//   * PulseEvent
//   * QueryPerformanceFrequency
//   * ReadFile
//   * ReadFileEx
//   * ReadFileScatter
//   * ReleaseMutex
//   * ReleaseSemaphore
//   * RemoveDirectoryA
//   * ResetEvent
//   * ResumeThread
//   * RootHubPortToPortNumber
//   * RtlAllocateHeap
//   * RtlAllocateHeapSlowly
//   * RtlCreateHeap
//   * RtlDestroyHeap
//   * RtlFreeHeap
//   * RtlFreeHeapSlowly
//   * RtlpCheckBusyBlockTail
//   * RtlpCoalesceFreeBlocks
//   * RtlpCreateUnCommittedRange
//   * RtlpCutoverTimeToSystemTime
//   * RtlpDeCommitFreeBlock
//   * RtlpDestroyHeapSegment
//   * RtlpDestroyUnCommittedRange
//   * RtlpExtendHeap
//   * RtlpFindAndCommitPages
//   * RtlpGetExtraStuffPointer
//   * RtlpGetSizeOfBigBlock
//   * RtlpGrowBlockInPlace
//   * RtlpInitializeHeapSegment
//   * RtlpInsertFreeBlock
//   * RtlpInsertUnCommittedPages
//   * RtlRandom
//   * RtlReAllocateHeap
//   * RtlSizeHeap
//   * RtlZeroHeap
//   * SetEndOfFile
//   * SetEvent
//   * SetFileAttributesA
//   * SetFilePointer
//   * SetFilePointerEx
//   * SetFileTime
//   * SetRect
//   * SetRectEmpty
//   * SetUnhandledExceptionFilter
//   * SetWaitableTimer
//   * Sleep
//   * SleepEx
//   * SubtractRect
//   * SuspendThread
//   * SystemTimeToFileTime
//   * timeGetSystemTime
//   * TlsAlloc
//   * TlsFree
//   * TlsGetValue
//   * TlsSetValue
//   * UnionRect
//   * USBD_CalculateUsbBandwidth
//   * USBD_CompleteRequest
//   * USBD_DeviceConnected
//   * USBD_DeviceDisconnected
//   * USBD_Init
//   * USBD_NewHostController
//   * USBHUB_AddDevice
//   * USBHUB_Init
//   * USBHUB_RemoveDevice
//   * VirtualAlloc
//   * VirtualAllocEx
//   * VirtualFree
//   * VirtualFreeEx
//   * VirtualProtect
//   * VirtualProtectEx
//   * VirtualQuery
//   * VirtualQueryEx
//   * WaitForMultipleObjects
//   * WaitForMultipleObjectsEx
//   * WaitForSingleObject
//   * WaitForSingleObjectEx
//   * WideCharToMultiByte
//   * WriteFile
//   * WriteFileEx
//   * WriteFileGather
//   * wsprintfA
//   * wsprintfW
//   * wvsprintfA
//   * wvsprintfW
//   * XapiAutoPowerDownTimeout
//   * XapiConvertSignatureToNonRoamable
//   * XapiCopySectionToFile
//   * XapiDirectoryInformationToFindData
//   * XapiDispatchAPC
//   * XapiFillInSaveGameData
//   * XapiFindValueInMetaFile
//   * XapiFormatFATVolume
//   * XapiFormatTimeOut
//   * XapiGetDirectoryDisplayBlocks
//   * XapiGetNextSoundtrack
//   * XapiInitAutoPowerDown
//   * XapiIsXapiThread
//   * XapiMmTimerThread
//   * XapiNukeDirectory
//   * XapiNukeDirectoryFromHandle
//   * XapiOpenStDbAndReadHeader
//   * XapipGetTimeZoneBias
//   * XapipQueryTimeZoneInformation
//   * XapipUseDaylightSavingTime
//   * XapiReadFromStDb
//   * XapiSaveGameHashEncode
//   * XapiSetupPerTitleDriveLetters
//   * XapiTouchDirectoryTimestamp
//   * XapiValidateAndSkipUnicodeSignature
//   * XapiValidateDiskPartition
//   * XapiVerifyGameName
//   * XboxTimeZoneDateToSystemTime
//   * XboxTimeZoneNameToWstr
//   * XCalculateSignatureBeginEx
//     * XapipCalculateContentSignatureBegin,
//     * XapipCalculateSaveGameSignatureBegin,
//   * XCalculateSignatureEnd
//   * XCalculateSignatureUpdate
//   * xCompareStringA
//   * xCompareStringW
//   * XCreateSaveGame
//   * XDeleteSaveGame
//   * XdReportDeviceInsertionRemoval
//   * XFindClose
//   * XFindFirstNicknameW
//   * XFindFirstSaveGame
//   * XFindFirstSoundtrack
//   * XFindNextNicknameW
//   * XFindNextSaveGame
//   * XFindNextSoundtrack
//   * XFreeSectionA
//   * XFreeSectionByHandle
//   * XGetAudioFlags
//   * XGetAVPack
//   * XGetDiskClusterSizeA
//   * XGetDiskSectorSizeA
//   * XGetDisplayBlocks
//   * XGetFileCacheSize
//   * XGetGameRegion
//   * XGetLanguage
//   * XGetParentalControlSetting
//   * XGetSectionHandleA
//   * XGetSoundtrackSongInfo
//   * XGetVideoFlags
//   * XGetVideoStandard
//   * XID_AddDevice
//   * XID_Init
//   * XID_RemoveDevice
//   * XLoadSectionA
//   * XLoadSectionByHandle
//   * XMUNameFromDriveLetter
//   * XMUPortFromDriveLetterA
//   * XMUSlotFromDriveLetterA
//   * XOpenSoundtrackSong
//   * XPhysicalAlloc
//   * XPhysicalFree
//   * XPhysicalProtect
//   * XPhysicalSize
//   * XQueryMemoryProtect
//   * XQueryValue
//   * XSetFileCacheSize
//   * XSetNicknameW
//   * XShaHmacComputeFinal
//   * XShaHmacInitialize
//   * XShaHmacUpdate
//   * XWriteTitleInfoAndRebootA
//   * XWriteTitleInfoNoReboot
//   * initterm
//   * initterm_e
//   * InterlockedCompareExchange
//   * InterlockedDecrement
//   * InterlockedExchange
//   * InterlockedExchangeAdd
//   * InterlockedIncrement

#ifndef XAPI_OOVPA_INL
#define XAPI_OOVPA_INL

#include "OOVPA.h"

#include "Xapi/3911.inl"
#include "Xapi/3950.inl"
#include "Xapi/4039.inl"
#include "Xapi/4134.inl"
#include "Xapi/4242.inl"
#include "Xapi/4361.inl"
#include "Xapi/4721.inl"
#include "Xapi/4831.inl"
#include "Xapi/5028.inl"
#include "Xapi/5120.inl"
#include "Xapi/5233.inl"
#include "Xapi/5344.inl"
#include "Xapi/5455.inl"

#define REGISTER_OOVPAS_XAPI(Symbol, ...) REGISTER_OOVPAS_PREFIX(XAPI, Symbol, __VA_ARGS__)

// ******************************************************************
// * XAPILIB_OOVPA
// ******************************************************************
OOVPATable XAPILIB_OOVPA[] = {

    // Without xrefs dependency
    REGISTER_OOVPAS_XAPI(_cinit, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(_rtinit, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_C(IUsbInit_GetMaxDeviceTypeCount, 3911),
    REGISTER_OOVPAS(XapiFormatObjectAttributes, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XapiCallThreadNotifyRoutines, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_M(XapiMapLetterToDirectory, 3911),
    REGISTER_OOVPAS(XLaunchNewImageA, 3911, 4721, 5344),
    REGISTER_OOVPAS(XUnmountAlternateTitleA, 3911),

    // With xrefs dependency (unorder, need to scan next before order list)
    REGISTER_OOVPAS_XAPI(mainXapiStartup, 3911, 4831), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS_XAPI(GetLastError, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(SetLastError, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(UnhandledExceptionFilter, 3911, 4831), // Final generic OOVPA: 4831 Removed: 0
    REGISTER_OOVPAS(XapiBootToDash, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XapiSelectCachePartition, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XapiSetLastNTError, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XapiThreadStartup, 3911), // Final generic OOVPA: 3911; Removed: 0

    // With xrefs dependency (order)
    REGISTER_OOVPAS_XAPI(CreateMutexA, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(CreateThread, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(ExitThread, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(MoveFileA, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(SwitchToThread, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XapiInitProcess, 3911, 3950, 4242, 4831, 5028), // obsolete, Too High Level (from 4721's comment)
    REGISTER_OOVPAS_XAPI(ConvertThreadToFiber, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XCalculateSignatureBegin, 3911, 4034), // Final generic OOVPA: ????; Removed: 0 // TODO: need verification for 4034 against 3950 and lower.
    REGISTER_OOVPAS_XAPI(CreateFiber, 3911),
    REGISTER_OOVPAS_XAPI(DeleteFiber, 3911),
    REGISTER_OOVPAS_XAPI(GetExitCodeThread, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(GetOverlappedResult, 3911),
    REGISTER_OOVPAS_XAPI(GetThreadPriority, 3911),
    REGISTER_OOVPAS_XAPI(GetTimeZoneInformation, 3911),
    REGISTER_OOVPAS_XAPI(GetTypeInformation, 4134), // TODO: Actually introduced in some unknown XDK between 4134 and 4361
    REGISTER_OOVPAS_M(MU_Init, 3911, 4242, 5233),
    REGISTER_OOVPAS_XAPI(OutputDebugStringA, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(OutputDebugStringW, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS_XAPI(mainCRTStartup, 3911, 4361), // Final generic OOVPA: 4361; Removed: 0
    REGISTER_OOVPAS_XAPI(QueueUserAPC, 3911),
    REGISTER_OOVPAS_XAPI(QueryPerformanceCounter, 3911),
    REGISTER_OOVPAS_XAPI(RaiseException, 3911),
    REGISTER_OOVPAS_XAPI(SetThreadPriority, 3911),
    REGISTER_OOVPAS_XAPI(SetThreadPriorityBoost, 3911),
    REGISTER_OOVPAS_XAPI(SignalObjectAndWait, 3911),
    REGISTER_OOVPAS_XAPI(SwitchToFiber, 3911),
    REGISTER_OOVPAS(XAutoPowerDownResetTimer, 3911), // Just calls KeSetTimer (from 3911's comment)
    REGISTER_OOVPAS(XFormatUtilityDrive, 4242),
    REGISTER_OOVPAS(XGetDeviceChanges, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XGetDeviceEnumerationStatus, 4831),
    REGISTER_OOVPAS(XGetDevices, 3911),
    REGISTER_OOVPAS(XGetLaunchInfo, 3911),
    REGISTER_OOVPAS(XID_fCloseDevice, 3911, 4831),
    REGISTER_OOVPAS(XInitDevices, 3911, 5120),
    REGISTER_OOVPAS(XInputClose, 3911),
    REGISTER_OOVPAS(XInputGetCapabilities, 3911, 4831), // Final generic OOVPA: 4831; Removed: 0
    REGISTER_OOVPAS(XInputGetDeviceDescription, 4831),
    REGISTER_OOVPAS(XInputGetState, 3911, 4242, 5455),
    REGISTER_OOVPAS(XInputOpen, 3911, 4242),
    REGISTER_OOVPAS(XInputPoll, 3911),
    REGISTER_OOVPAS(XInputSetLightgunCalibration, 4831),
    REGISTER_OOVPAS(XInputSetState, 3911, 4242, 4831),
    REGISTER_OOVPAS(XMountAlternateTitleA, 3911, 5028, 5455),
    REGISTER_OOVPAS(XMountMUA, 3911, 4242),
    REGISTER_OOVPAS(XMountMURootA, 3911, 4242),
    REGISTER_OOVPAS(XMountUtilityDrive, 3911), // Final generic OOVPA: 3911; Removed: 0
    REGISTER_OOVPAS(XReadMUMetaData, 4242),
    REGISTER_OOVPAS(XRegisterThreadNotifyRoutine, 3911),
    REGISTER_OOVPAS(XSetProcessQuantumLength, 4134),
    REGISTER_OOVPAS(XUnmountMU, 3911, 4242),
    REGISTER_OOVPAS(XapiFiberStartup, 3911),
    REGISTER_OOVPAS_XAPI(timeKillEvent, 3911),
    REGISTER_OOVPAS_XAPI(timeSetEvent, 3911),

};

// ******************************************************************
// * XAPILIB_OOVPA_COUNT
// ******************************************************************
#define XAPILIB_OOVPA_COUNT XBSDB_ARRAY_SIZE(XAPILIB_OOVPA)

#endif

// ******************************************************************
// *
// *   XbSymbolDatabase.h
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
// *  (c) 2016-2017 PatrickvL
// *  (c) 2017-2018 Luke Usher
// *  (c) 2018-2019 RadWolfie
// *
// *  All rights reserved
// *
// ******************************************************************
#pragma once

#include <stdlib.h> // for size_t
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ******************************************************************
// * Library strings
// ******************************************************************
#define Lib_UNKNOWN     "UNKNOWN"
// Group of sections since most libraries are compiled inside the
// section(s) below.
#define Sec_text        ".text"
#define Sec_FLASHROM    "FLASHROM"
// DSOUND has a vtable store in .rdata section.
#define Sec_rdata       ".rdata"
// Individual library (yet do include group sections above)
#define Lib_D3D8        "D3D8"
#define Sec_D3D         "D3D"
#define Lib_D3D8LTCG    "D3D8LTCG"
#define Lib_D3DX8       "D3DX8"
#define Sec_D3DX        "D3DX"
#define Lib_DSOUND      "DSOUND"
#define Sec_DSOUND      Lib_DSOUND
#define Lib_JVS         "JVS"
#define Lib_XACTENG     "XACTENG"
#define Sec_XACTENG     Lib_XACTENG
#define Lib_XAPILIB     "XAPILIB"
#define Sec_XPP         "XPP"
#define Lib_XGRAPHC     "XGRAPHC"
#define Sec_XGRPH       "XGRPH"
#define Lib_XNET        "XNET"
#define Lib_XNETN       "XNETN"
#define Lib_XNETS       "XNETS"
#define Lib_XONLINE     "XONLINE"
#define Sec_XONLINE     Lib_XONLINE
#define Lib_XONLINES    "XONLINES"
#define Sec_XNET        "XNET"

#define XbSymbolLib_D3D8        (1 << 0)
#define XbSymbolLib_D3D8LTCG    (1 << 1)
#define XbSymbolLib_D3DX8       (1 << 2)
#define XbSymbolLib_DSOUND      (1 << 3)
#define XbSymbolLib_JVS         (1 << 4)
#define XbSymbolLib_XACTENG     (1 << 5)
#define XbSymbolLib_XAPILIB     (1 << 6)
#define XbSymbolLib_XGRAPHC     (1 << 7)
#define XbSymbolLib_XNET        (1 << 8)
#define XbSymbolLib_XNETN       (1 << 9)
#define XbSymbolLib_XNETS       (1 << 10)
#define XbSymbolLib_XONLINE     (1 << 11)
#define XbSymbolLib_XONLINES    (1 << 12)

#define XbSymbolLib_ALL ( XbSymbolLib_D3D8| XbSymbolLib_D3D8LTCG| XbSymbolLib_D3DX8| XbSymbolLib_DSOUND \
                        | XbSymbolLib_JVS| XbSymbolLib_XACTENG| XbSymbolLib_XAPILIB| XbSymbolLib_XGRAPHC \
                        | XbSymbolLib_XNET| XbSymbolLib_XNETN| XbSymbolLib_XNETS| XbSymbolLib_XONLINE \
                        | XbSymbolLib_XONLINES)

// ******************************************************************
// * XRefDatabaseOffset
// ******************************************************************
typedef enum _XRefDatabaseOffset
{
    // BEGIN - DO NOT REARRANGE (kernel thunk)
    XREF_KT_FUNC_AvGetSavedDataAddress=1,                // 0x0001 (001)
    XREF_KT_FUNC_AvSendTVEncoderOption,                  // 0x0002 (002)
    XREF_KT_FUNC_AvSetDisplayMode,                       // 0x0003 (003)
    XREF_KT_FUNC_AvSetSavedDataAddress,                  // 0x0004 (004)
    XREF_KT_FUNC_DbgBreakPoint,                          // 0x0005 (005)
    XREF_KT_FUNC_DbgBreakPointWithStatus,                // 0x0006 (006)
    XREF_KT_FUNC_DbgLoadImageSymbols,                    // 0x0007 (007) DEVKIT
    XREF_KT_FUNC_DbgPrint,                               // 0x0008 (008)
    XREF_KT_FUNC_HalReadSMCTrayState,                    // 0x0009 (009)
    XREF_KT_FUNC_DbgPrompt,                              // 0x000A (010)
    XREF_KT_FUNC_DbgUnLoadImageSymbols,                  // 0x000B (011) DEVKIT
    XREF_KT_FUNC_ExAcquireReadWriteLockExclusive,        // 0x000C (012)
    XREF_KT_FUNC_ExAcquireReadWriteLockShared,           // 0x000D (013)
    XREF_KT_FUNC_ExAllocatePool,                         // 0x000E (014)
    XREF_KT_FUNC_ExAllocatePoolWithTag,                  // 0x000F (015)
    XREF_KT_VAR__ExEventObjectType,                      // 0x0010 (016)
    XREF_KT_FUNC_ExFreePool,                             // 0x0011 (017)
    XREF_KT_FUNC_ExInitializeReadWriteLock,              // 0x0012 (018)
    XREF_KT_FUNC_ExInterlockedAddLargeInteger,           // 0x0013 (019)
    XREF_KT_FUNC_ExInterlockedAddLargeStatistic,         // 0x0014 (020)
    XREF_KT_FUNC_ExInterlockedCompareExchange64,         // 0x0015 (021)
    XREF_KT_VAR__ExMutantObjectType,                     // 0x0016 (022)
    XREF_KT_FUNC_ExQueryPoolBlockSize,                   // 0x0017 (023)
    XREF_KT_FUNC_ExQueryNonVolatileSetting,              // 0x0018 (024)
    XREF_KT_FUNC_ExReadWriteRefurbInfo,                  // 0x0019 (025)
    XREF_KT_FUNC_ExRaiseException,                       // 0x001A (026)
    XREF_KT_FUNC_ExRaiseStatus,                          // 0x001B (027)
    XREF_KT_FUNC_ExReleaseReadWriteLock,                 // 0x001C (028)
    XREF_KT_FUNC_ExSaveNonVolatileSetting,               // 0x001D (029)
    XREF_KT_VAR__ExSemaphoreObjectType,                  // 0x001E (030)
    XREF_KT_VAR__ExTimerObjectType,                      // 0x001F (031)
    XREF_KT_FUNC_ExfInterlockedInsertHeadList,           // 0x0020 (032)
    XREF_KT_FUNC_ExfInterlockedInsertTailList,           // 0x0021 (033)
    XREF_KT_FUNC_ExfInterlockedRemoveHeadList,           // 0x0022 (034)
    XREF_KT_FUNC_FscGetCacheSize,                        // 0x0023 (035)
    XREF_KT_FUNC_FscInvalidateIdleBlocks,                // 0x0024 (036)
    XREF_KT_FUNC_FscSetCacheSize,                        // 0x0025 (037)
    XREF_KT_FUNC_HalClearSoftwareInterrupt,              // 0x0026 (038)
    XREF_KT_FUNC_HalDisableSystemInterrupt,              // 0x0027 (039)
    XREF_KT_VAR__HalDiskCachePartitionCount,             // 0x0028 (040)
    XREF_KT_VAR__HalDiskModelNumber,                     // 0x0029 (041)
    XREF_KT_VAR__HalDiskSerialNumber,                    // 0x002A (042)
    XREF_KT_FUNC_HalEnableSystemInterrupt,               // 0x002B (043)
    XREF_KT_FUNC_HalGetInterruptVector,                  // 0x002C (044)
    XREF_KT_FUNC_HalReadSMBusValue,                      // 0x002D (045)
    XREF_KT_FUNC_HalReadWritePCISpace,                   // 0x002E (046)
    XREF_KT_FUNC_HalRegisterShutdownNotification,        // 0x002F (047)
    XREF_KT_FUNC_HalRequestSoftwareInterrupt,            // 0x0030 (048)
    XREF_KT_FUNC_HalReturnToFirmware,                    // 0x0031 (049)
    XREF_KT_FUNC_HalWriteSMBusValue,                     // 0x0032 (050)
    XREF_KT_FUNC_InterlockedCompareExchange,             // 0x0033 (051)
    XREF_KT_FUNC_InterlockedDecrement,                   // 0x0034 (052)
    XREF_KT_FUNC_InterlockedIncrement,                   // 0x0035 (053)
    XREF_KT_FUNC_InterlockedExchange,                    // 0x0036 (054)
    XREF_KT_FUNC_InterlockedExchangeAdd,                 // 0x0037 (055)
    XREF_KT_FUNC_InterlockedFlushSList,                  // 0x0038 (056)
    XREF_KT_FUNC_InterlockedPopEntrySList,               // 0x0039 (057)
    XREF_KT_FUNC_InterlockedPushEntrySList,              // 0x003A (058)
    XREF_KT_FUNC_IoAllocateIrp,                          // 0x003B (059)
    XREF_KT_FUNC_IoBuildAsynchronousFsdRequest,          // 0x003C (060)
    XREF_KT_FUNC_IoBuildDeviceIoControlRequest,          // 0x003D (061)
    XREF_KT_FUNC_IoBuildSynchronousFsdRequest,           // 0x003E (062)
    XREF_KT_FUNC_IoCheckShareAccess,                     // 0x003F (063)
    XREF_KT_VAR__IoCompletionObjectType,                 // 0x0040 (064)
    XREF_KT_FUNC_IoCreateDevice,                         // 0x0041 (065)
    XREF_KT_FUNC_IoCreateFile,                           // 0x0042 (066)
    XREF_KT_FUNC_IoCreateSymbolicLink,                   // 0x0043 (067)
    XREF_KT_FUNC_IoDeleteDevice,                         // 0x0044 (068)
    XREF_KT_FUNC_IoDeleteSymbolicLink,                   // 0x0045 (069)
    XREF_KT_VAR__IoDeviceObjectType,                     // 0x0046 (070)
    XREF_KT_VAR__IoFileObjectType,                       // 0x0047 (071)
    XREF_KT_FUNC_IoFreeIrp,                              // 0x0048 (072)
    XREF_KT_FUNC_IoInitializeIrp,                        // 0x0049 (073)
    XREF_KT_FUNC_IoInvalidDeviceRequest,                 // 0x004A (074)
    XREF_KT_FUNC_IoQueryFileInformation,                 // 0x004B (075)
    XREF_KT_FUNC_IoQueryVolumeInformation,               // 0x004C (076)
    XREF_KT_FUNC_IoQueueThreadIrp,                       // 0x004D (077)
    XREF_KT_FUNC_IoRemoveShareAccess,                    // 0x004E (078)
    XREF_KT_FUNC_IoSetIoCompletion,                      // 0x004F (079)
    XREF_KT_FUNC_IoSetShareAccess,                       // 0x0050 (080)
    XREF_KT_FUNC_IoStartNextPacket,                      // 0x0051 (081)
    XREF_KT_FUNC_IoStartNextPacketByKey,                 // 0x0052 (082)
    XREF_KT_FUNC_IoStartPacket,                          // 0x0053 (083)
    XREF_KT_FUNC_IoSynchronousDeviceIoControlRequest,    // 0x0054 (084)
    XREF_KT_FUNC_IoSynchronousFsdRequest,                // 0x0055 (085)
    XREF_KT_FUNC_IofCallDriver,                          // 0x0056 (086)
    XREF_KT_FUNC_IofCompleteRequest,                     // 0x0057 (087)
    XREF_KT_VAR__KdDebuggerEnabled,                      // 0x0058 (088)
    XREF_KT_VAR__KdDebuggerNotPresent,                   // 0x0059 (089)
    XREF_KT_FUNC_IoDismountVolume,                       // 0x005A (090)
    XREF_KT_FUNC_IoDismountVolumeByName,                 // 0x005B (091)
    XREF_KT_FUNC_KeAlertResumeThread,                    // 0x005C (092)
    XREF_KT_FUNC_KeAlertThread,                          // 0x005D (093)
    XREF_KT_FUNC_KeBoostPriorityThread,                  // 0x005E (094)
    XREF_KT_FUNC_KeBugCheck,                             // 0x005F (095)
    XREF_KT_FUNC_KeBugCheckEx,                           // 0x0060 (096)
    XREF_KT_FUNC_KeCancelTimer,                          // 0x0061 (097)
    XREF_KT_FUNC_KeConnectInterrupt,                     // 0x0062 (098)
    XREF_KT_FUNC_KeDelayExecutionThread,                 // 0x0063 (099)
    XREF_KT_FUNC_KeDisconnectInterrupt,                  // 0x0064 (100)
    XREF_KT_FUNC_KeEnterCriticalRegion,                  // 0x0065 (101)
    XREF_KT_VAR__MmGlobalData,                           // 0x0066 (102)
    XREF_KT_FUNC_KeGetCurrentIrql,                       // 0x0067 (103)
    XREF_KT_FUNC_KeGetCurrentThread,                     // 0x0068 (104)
    XREF_KT_FUNC_KeInitializeApc,                        // 0x0069 (105)
    XREF_KT_FUNC_KeInitializeDeviceQueue,                // 0x006A (106)
    XREF_KT_FUNC_KeInitializeDpc,                        // 0x006B (107)
    XREF_KT_FUNC_KeInitializeEvent,                      // 0x006C (108)
    XREF_KT_FUNC_KeInitializeInterrupt,                  // 0x006D (109)
    XREF_KT_FUNC_KeInitializeMutant,                     // 0x006E (110)
    XREF_KT_FUNC_KeInitializeQueue,                      // 0x006F (111)
    XREF_KT_FUNC_KeInitializeSemaphore,                  // 0x0070 (112)
    XREF_KT_FUNC_KeInitializeTimerEx,                    // 0x0071 (113)
    XREF_KT_FUNC_KeInsertByKeyDeviceQueue,               // 0x0072 (114)
    XREF_KT_FUNC_KeInsertDeviceQueue,                    // 0x0073 (115)
    XREF_KT_FUNC_KeInsertHeadQueue,                      // 0x0074 (116)
    XREF_KT_FUNC_KeInsertQueue,                          // 0x0075 (117)
    XREF_KT_FUNC_KeInsertQueueApc,                       // 0x0076 (118)
    XREF_KT_FUNC_KeInsertQueueDpc,                       // 0x0077 (119)
    XREF_KT_VAR__KeInterruptTime,                        // 0x0078 (120)
    XREF_KT_FUNC_KeIsExecutingDpc,                       // 0x0079 (121)
    XREF_KT_FUNC_KeLeaveCriticalRegion,                  // 0x007A (122)
    XREF_KT_FUNC_KePulseEvent,                           // 0x007B (123)
    XREF_KT_FUNC_KeQueryBasePriorityThread,              // 0x007C (124)
    XREF_KT_FUNC_KeQueryInterruptTime,                   // 0x007D (125)
    XREF_KT_FUNC_KeQueryPerformanceCounter,              // 0x007E (126)
    XREF_KT_FUNC_KeQueryPerformanceFrequency,            // 0x007F (127)
    XREF_KT_FUNC_KeQuerySystemTime,                      // 0x0080 (128)
    XREF_KT_FUNC_KeRaiseIrqlToDpcLevel,                  // 0x0081 (129)
    XREF_KT_FUNC_KeRaiseIrqlToSynchLevel,                // 0x0082 (130)
    XREF_KT_FUNC_KeReleaseMutant,                        // 0x0083 (131)
    XREF_KT_FUNC_KeReleaseSemaphore,                     // 0x0084 (132)
    XREF_KT_FUNC_KeRemoveByKeyDeviceQueue,               // 0x0085 (133)
    XREF_KT_FUNC_KeRemoveDeviceQueue,                    // 0x0086 (134)
    XREF_KT_FUNC_KeRemoveEntryDeviceQueue,               // 0x0087 (135)
    XREF_KT_FUNC_KeRemoveQueue,                          // 0x0088 (136)
    XREF_KT_FUNC_KeRemoveQueueDpc,                       // 0x0089 (137)
    XREF_KT_FUNC_KeResetEvent,                           // 0x008A (138)
    XREF_KT_FUNC_KeRestoreFloatingPointState,            // 0x008B (139)
    XREF_KT_FUNC_KeResumeThread,                         // 0x008C (140)
    XREF_KT_FUNC_KeRundownQueue,                         // 0x008D (141)
    XREF_KT_FUNC_KeSaveFloatingPointState,               // 0x008E (142)
    XREF_KT_FUNC_KeSetBasePriorityThread,                // 0x008F (143)
    XREF_KT_FUNC_KeSetDisableBoostThread,                // 0x0090 (144)
    XREF_KT_FUNC_KeSetEvent,                             // 0x0091 (145)
    XREF_KT_FUNC_KeSetEventBoostPriority,                // 0x0092 (146)
    XREF_KT_FUNC_KeSetPriorityProcess,                   // 0x0093 (147)
    XREF_KT_FUNC_KeSetPriorityThread,                    // 0x0094 (148)
    XREF_KT_FUNC_KeSetTimer,                             // 0x0095 (149)
    XREF_KT_FUNC_KeSetTimerEx,                           // 0x0096 (150)
    XREF_KT_FUNC_KeStallExecutionProcessor,              // 0x0097 (151)
    XREF_KT_FUNC_KeSuspendThread,                        // 0x0098 (152)
    XREF_KT_FUNC_KeSynchronizeExecution,                 // 0x0099 (153)
    XREF_KT_VAR__KeSystemTime,                           // 0x009A (154)
    XREF_KT_FUNC_KeTestAlertThread,                      // 0x009B (155)
    XREF_KT_VAR__KeTickCount,                            // 0x009C (156)
    XREF_KT_VAR__KeTimeIncrement,                        // 0x009D (157)
    XREF_KT_FUNC_KeWaitForMultipleObjects,               // 0x009E (158)
    XREF_KT_FUNC_KeWaitForSingleObject,                  // 0x009F (159)
    XREF_KT_FUNC_KfRaiseIrql,                            // 0x00A0 (160)
    XREF_KT_FUNC_KfLowerIrql,                            // 0x00A1 (161)
    XREF_KT_VAR__KiBugCheckData,                         // 0x00A2 (162)
    XREF_KT_FUNC_KiUnlockDispatcherDatabase,             // 0x00A3 (163)
    XREF_KT_VAR__LaunchDataPage,                         // 0x00A4 (164)
    XREF_KT_FUNC_MmAllocateContiguousMemory,             // 0x00A5 (165)
    XREF_KT_FUNC_MmAllocateContiguousMemoryEx,           // 0x00A6 (166)
    XREF_KT_FUNC_MmAllocateSystemMemory,                 // 0x00A7 (167)
    XREF_KT_FUNC_MmClaimGpuInstanceMemory,               // 0x00A8 (168)
    XREF_KT_FUNC_MmCreateKernelStack,                    // 0x00A9 (169)
    XREF_KT_FUNC_MmDeleteKernelStack,                    // 0x00AA (170)
    XREF_KT_FUNC_MmFreeContiguousMemory,                 // 0x00AB (171)
    XREF_KT_FUNC_MmFreeSystemMemory,                     // 0x00AC (172)
    XREF_KT_FUNC_MmGetPhysicalAddress,                   // 0x00AD (173)
    XREF_KT_FUNC_MmIsAddressValid,                       // 0x00AE (174)
    XREF_KT_FUNC_MmLockUnlockBufferPages,                // 0x00AF (175)
    XREF_KT_FUNC_MmLockUnlockPhysicalPage,               // 0x00B0 (176)
    XREF_KT_FUNC_MmMapIoSpace,                           // 0x00B1 (177)
    XREF_KT_FUNC_MmPersistContiguousMemory,              // 0x00B2 (178)
    XREF_KT_FUNC_MmQueryAddressProtect,                  // 0x00B3 (179)
    XREF_KT_FUNC_MmQueryAllocationSize,                  // 0x00B4 (180)
    XREF_KT_FUNC_MmQueryStatistics,                      // 0x00B5 (181)
    XREF_KT_FUNC_MmSetAddressProtect,                    // 0x00B6 (182)
    XREF_KT_FUNC_MmUnmapIoSpace,                         // 0x00B7 (183)
    XREF_KT_FUNC_NtAllocateVirtualMemory,                // 0x00B8 (184)
    XREF_KT_FUNC_NtCancelTimer,                          // 0x00B9 (185)
    XREF_KT_FUNC_NtClearEvent,                           // 0x00BA (186)
    XREF_KT_FUNC_NtClose,                                // 0x00BB (187)
    XREF_KT_FUNC_NtCreateDirectoryObject,                // 0x00BC (188)
    XREF_KT_FUNC_NtCreateEvent,                          // 0x00BD (189)
    XREF_KT_FUNC_NtCreateFile,                           // 0x00BE (190)
    XREF_KT_FUNC_NtCreateIoCompletion,                   // 0x00BF (191)
    XREF_KT_FUNC_NtCreateMutant,                         // 0x00C0 (192)
    XREF_KT_FUNC_NtCreateSemaphore,                      // 0x00C1 (193)
    XREF_KT_FUNC_NtCreateTimer,                          // 0x00C2 (194)
    XREF_KT_FUNC_NtDeleteFile,                           // 0x00C3 (195)
    XREF_KT_FUNC_NtDeviceIoControlFile,                  // 0x00C4 (196)
    XREF_KT_FUNC_NtDuplicateObject,                      // 0x00C5 (197)
    XREF_KT_FUNC_NtFlushBuffersFile,                     // 0x00C6 (198)
    XREF_KT_FUNC_NtFreeVirtualMemory,                    // 0x00C7 (199)
    XREF_KT_FUNC_NtFsControlFile,                        // 0x00C8 (200)
    XREF_KT_FUNC_NtOpenDirectoryObject,                  // 0x00C9 (201)
    XREF_KT_FUNC_NtOpenFile,                             // 0x00CA (202)
    XREF_KT_FUNC_NtOpenSymbolicLinkObject,               // 0x00CB (203)
    XREF_KT_FUNC_NtProtectVirtualMemory,                 // 0x00CC (204)
    XREF_KT_FUNC_NtPulseEvent,                           // 0x00CD (205)
    XREF_KT_FUNC_NtQueueApcThread,                       // 0x00CE (206)
    XREF_KT_FUNC_NtQueryDirectoryFile,                   // 0x00CF (207)
    XREF_KT_FUNC_NtQueryDirectoryObject,                 // 0x00D0 (208)
    XREF_KT_FUNC_NtQueryEvent,                           // 0x00D1 (209)
    XREF_KT_FUNC_NtQueryFullAttributesFile,              // 0x00D2 (210)
    XREF_KT_FUNC_NtQueryInformationFile,                 // 0x00D3 (211)
    XREF_KT_FUNC_NtQueryIoCompletion,                    // 0x00D4 (212)
    XREF_KT_FUNC_NtQueryMutant,                          // 0x00D5 (213)
    XREF_KT_FUNC_NtQuerySemaphore,                       // 0x00D6 (214)
    XREF_KT_FUNC_NtQuerySymbolicLinkObject,              // 0x00D7 (215)
    XREF_KT_FUNC_NtQueryTimer,                           // 0x00D8 (216)
    XREF_KT_FUNC_NtQueryVirtualMemory,                   // 0x00D9 (217)
    XREF_KT_FUNC_NtQueryVolumeInformationFile,           // 0x00DA (218)
    XREF_KT_FUNC_NtReadFile,                             // 0x00DB (219)
    XREF_KT_FUNC_NtReadFileScatter,                      // 0x00DC (220)
    XREF_KT_FUNC_NtReleaseMutant,                        // 0x00DD (221)
    XREF_KT_FUNC_NtReleaseSemaphore,                     // 0x00DE (222)
    XREF_KT_FUNC_NtRemoveIoCompletion,                   // 0x00DF (223)
    XREF_KT_FUNC_NtResumeThread,                         // 0x00E0 (224)
    XREF_KT_FUNC_NtSetEvent,                             // 0x00E1 (225)
    XREF_KT_FUNC_NtSetInformationFile,                   // 0x00E2 (226)
    XREF_KT_FUNC_NtSetIoCompletion,                      // 0x00E3 (227)
    XREF_KT_FUNC_NtSetSystemTime,                        // 0x00E4 (228)
    XREF_KT_FUNC_NtSetTimerEx,                           // 0x00E5 (229)
    XREF_KT_FUNC_NtSignalAndWaitForSingleObjectEx,       // 0x00E6 (230)
    XREF_KT_FUNC_NtSuspendThread,                        // 0x00E7 (231)
    XREF_KT_FUNC_NtUserIoApcDispatcher,                  // 0x00E8 (232)
    XREF_KT_FUNC_NtWaitForSingleObject,                  // 0x00E9 (233)
    XREF_KT_FUNC_NtWaitForSingleObjectEx,                // 0x00EA (234)
    XREF_KT_FUNC_NtWaitForMultipleObjectsEx,             // 0x00EB (235)
    XREF_KT_FUNC_NtWriteFile,                            // 0x00EC (236)
    XREF_KT_FUNC_NtWriteFileGather,                      // 0x00ED (237)
    XREF_KT_FUNC_NtYieldExecution,                       // 0x00EE (238)
    XREF_KT_FUNC_ObCreateObject,                         // 0x00EF (239)
    XREF_KT_VAR__ObDirectoryObjectType,                  // 0x00F0 (240)
    XREF_KT_FUNC_ObInsertObject,                         // 0x00F1 (241)
    XREF_KT_FUNC_ObMakeTemporaryObject,                  // 0x00F2 (242)
    XREF_KT_FUNC_ObOpenObjectByName,                     // 0x00F3 (243)
    XREF_KT_FUNC_ObOpenObjectByPointer,                  // 0x00F4 (244)
    XREF_KT_VAR__ObpObjectHandleTable,                   // 0x00F5 (245)
    XREF_KT_FUNC_ObReferenceObjectByHandle,              // 0x00F6 (246)
    XREF_KT_FUNC_ObReferenceObjectByName,                // 0x00F7 (247)
    XREF_KT_FUNC_ObReferenceObjectByPointer,             // 0x00F8 (248)
    XREF_KT_VAR__ObSymbolicLinkObjectType,               // 0x00F9 (249)
    XREF_KT_FUNC_ObfDereferenceObject,                   // 0x00FA (250)
    XREF_KT_FUNC_ObfReferenceObject,                     // 0x00FB (251)
    XREF_KT_FUNC_PhyGetLinkState,                        // 0x00FC (252)
    XREF_KT_FUNC_PhyInitialize,                          // 0x00FD (253)
    XREF_KT_FUNC_PsCreateSystemThread,                   // 0x00FE (254)
    XREF_KT_FUNC_PsCreateSystemThreadEx,                 // 0x00FF (255)
    XREF_KT_FUNC_PsQueryStatistics,                      // 0x0100 (256)
    XREF_KT_FUNC_PsSetCreateThreadNotifyRoutine,         // 0x0101 (257)
    XREF_KT_FUNC_PsTerminateSystemThread,                // 0x0102 (258)
    XREF_KT_VAR__PsThreadObjectType,                     // 0x0103 (259)
    XREF_KT_FUNC_RtlAnsiStringToUnicodeString,           // 0x0104 (260)
    XREF_KT_FUNC_RtlAppendStringToString,                // 0x0105 (261)
    XREF_KT_FUNC_RtlAppendUnicodeStringToString,         // 0x0106 (262)
    XREF_KT_FUNC_RtlAppendUnicodeToString,               // 0x0107 (263)
    XREF_KT_FUNC_RtlAssert,                              // 0x0108 (264)
    XREF_KT_FUNC_RtlCaptureContext,                      // 0x0109 (265)
    XREF_KT_FUNC_RtlCaptureStackBackTrace,               // 0x010A (266)
    XREF_KT_FUNC_RtlCharToInteger,                       // 0x010B (267)
    XREF_KT_FUNC_RtlCompareMemory,                       // 0x010C (268)
    XREF_KT_FUNC_RtlCompareMemoryUlong,                  // 0x010D (269)
    XREF_KT_FUNC_RtlCompareString,                       // 0x010E (270)
    XREF_KT_FUNC_RtlCompareUnicodeString,                // 0x010F (271)
    XREF_KT_FUNC_RtlCopyString,                          // 0x0110 (272)
    XREF_KT_FUNC_RtlCopyUnicodeString,                   // 0x0111 (273)
    XREF_KT_FUNC_RtlCreateUnicodeString,                 // 0x0112 (274)
    XREF_KT_FUNC_RtlDowncaseUnicodeChar,                 // 0x0113 (275)
    XREF_KT_FUNC_RtlDowncaseUnicodeString,               // 0x0114 (276)
    XREF_KT_FUNC_RtlEnterCriticalSection,                // 0x0115 (277)
    XREF_KT_FUNC_RtlEnterCriticalSectionAndRegion,       // 0x0116 (278)
    XREF_KT_FUNC_RtlEqualString,                         // 0x0117 (279)
    XREF_KT_FUNC_RtlEqualUnicodeString,                  // 0x0118 (280)
    XREF_KT_FUNC_RtlExtendedIntegerMultiply,             // 0x0119 (281)
    XREF_KT_FUNC_RtlExtendedLargeIntegerDivide,          // 0x011A (282)
    XREF_KT_FUNC_RtlExtendedMagicDivide,                 // 0x011B (283)
    XREF_KT_FUNC_RtlFillMemory,                          // 0x011C (284)
    XREF_KT_FUNC_RtlFillMemoryUlong,                     // 0x011D (285)
    XREF_KT_FUNC_RtlFreeAnsiString,                      // 0x011E (286)
    XREF_KT_FUNC_RtlFreeUnicodeString,                   // 0x011F (287)
    XREF_KT_FUNC_RtlGetCallersAddress,                   // 0x0120 (288)
    XREF_KT_FUNC_RtlInitAnsiString,                      // 0x0121 (289)
    XREF_KT_FUNC_RtlInitUnicodeString,                   // 0x0122 (290)
    XREF_KT_FUNC_RtlInitializeCriticalSection,           // 0x0123 (291)
    XREF_KT_FUNC_RtlIntegerToChar,                       // 0x0124 (292)
    XREF_KT_FUNC_RtlIntegerToUnicodeString,              // 0x0125 (293)
    XREF_KT_FUNC_RtlLeaveCriticalSection,                // 0x0126 (294)
    XREF_KT_FUNC_RtlLeaveCriticalSectionAndRegion,       // 0x0127 (295)
    XREF_KT_FUNC_RtlLowerChar,                           // 0x0128 (296)
    XREF_KT_FUNC_RtlMapGenericMask,                      // 0x0129 (297)
    XREF_KT_FUNC_RtlMoveMemory,                          // 0x012A (298)
    XREF_KT_FUNC_RtlMultiByteToUnicodeN,                 // 0x012B (299)
    XREF_KT_FUNC_RtlMultiByteToUnicodeSize,              // 0x012C (300)
    XREF_KT_FUNC_RtlNtStatusToDosError,                  // 0x012D (301)
    XREF_KT_FUNC_RtlRaiseException,                      // 0x012E (302)
    XREF_KT_FUNC_RtlRaiseStatus,                         // 0x012F (303)
    XREF_KT_FUNC_RtlTimeFieldsToTime,                    // 0x0130 (304)
    XREF_KT_FUNC_RtlTimeToTimeFields,                    // 0x0131 (305)
    XREF_KT_FUNC_RtlTryEnterCriticalSection,             // 0x0132 (306)
    XREF_KT_FUNC_RtlUlongByteSwap,                       // 0x0133 (307)
    XREF_KT_FUNC_RtlUnicodeStringToAnsiString,           // 0x0134 (308)
    XREF_KT_FUNC_RtlUnicodeStringToInteger,              // 0x0135 (309)
    XREF_KT_FUNC_RtlUnicodeToMultiByteN,                 // 0x0136 (310)
    XREF_KT_FUNC_RtlUnicodeToMultiByteSize,              // 0x0137 (311)
    XREF_KT_FUNC_RtlUnwind,                              // 0x0138 (312)
    XREF_KT_FUNC_RtlUpcaseUnicodeChar,                   // 0x0139 (313)
    XREF_KT_FUNC_RtlUpcaseUnicodeString,                 // 0x013A (314)
    XREF_KT_FUNC_RtlUpcaseUnicodeToMultiByteN,           // 0x013B (315)
    XREF_KT_FUNC_RtlUpperChar,                           // 0x013C (316)
    XREF_KT_FUNC_RtlUpperString,                         // 0x013D (317)
    XREF_KT_FUNC_RtlUshortByteSwap,                      // 0x013E (318)
    XREF_KT_FUNC_RtlWalkFrameChain,                      // 0x013F (319)
    XREF_KT_FUNC_RtlZeroMemory,                          // 0x0140 (320)
    XREF_KT_VAR__XboxEEPROMKey,                          // 0x0141 (321)
    XREF_KT_VAR__XboxHardwareInfo,                       // 0x0142 (322)
    XREF_KT_VAR__XboxHDKey,                              // 0x0143 (323)
    XREF_KT_VAR__XboxKrnlVersion,                        // 0x0144 (324)
    XREF_KT_VAR__XboxSignatureKey,                       // 0x0145 (325)
    XREF_KT_VAR__XeImageFileName,                        // 0x0146 (326)
    XREF_KT_FUNC_XeLoadSection,                          // 0x0147 (327)
    XREF_KT_FUNC_XeUnloadSection,                        // 0x0148 (328)
    XREF_KT_FUNC_PortBufferRead_uint8,                   // 0x0149 (329)
    XREF_KT_FUNC_PortBufferRead_uint16,                  // 0x014A (330)
    XREF_KT_FUNC_PortBufferRead_uint32,                  // 0x014B (331)
    XREF_KT_FUNC_PortBufferWrite_uint8,                  // 0x014C (332)
    XREF_KT_FUNC_PortBufferWrite_uint16,                 // 0x014D (333)
    XREF_KT_FUNC_PortBufferWrite_uint32,                 // 0x014E (334)
    XREF_KT_FUNC_XcSHAInit,                              // 0x014F (335)
    XREF_KT_FUNC_XcSHAUpdate,                            // 0x0150 (336)
    XREF_KT_FUNC_XcSHAFinal,                             // 0x0151 (337)
    XREF_KT_FUNC_XcRC4Key,                               // 0x0152 (338)
    XREF_KT_FUNC_XcRC4Crypt,                             // 0x0153 (339)
    XREF_KT_FUNC_XcHMAC,                                 // 0x0154 (340)
    XREF_KT_FUNC_XcPKEncPublic,                          // 0x0155 (341)
    XREF_KT_FUNC_XcPKDecPrivate,                         // 0x0156 (342)
    XREF_KT_FUNC_XcPKGetKeyLen,                          // 0x0157 (343)
    XREF_KT_FUNC_XcVerifyPKCS1Signature,                 // 0x0158 (344)
    XREF_KT_FUNC_XcModExp,                               // 0x0159 (345)
    XREF_KT_FUNC_XcDESKeyParity,                         // 0x015A (346)
    XREF_KT_FUNC_XcKeyTable,                             // 0x015B (347)
    XREF_KT_FUNC_XcBlockCrypt,                           // 0x015C (348)
    XREF_KT_FUNC_XcBlockCryptCBC,                        // 0x015D (349)
    XREF_KT_FUNC_XcCryptService,                         // 0x015E (350)
    XREF_KT_FUNC_XcUpdateCrypto,                         // 0x015F (351)
    XREF_KT_FUNC_RtlRip,                                 // 0x0160 (352)
    XREF_KT_VAR__XboxLANKey,                             // 0x0161 (353)
    XREF_KT_VAR__XboxAlternateSignatureKeys,             // 0x0162 (354)
    XREF_KT_VAR__XePublicKeyData,                        // 0x0163 (355)
    XREF_KT_VAR__HalBootSMCVideoMode,                    // 0x0164 (356)
    XREF_KT_VAR__IdexChannelObject,                      // 0x0165 (357)
    XREF_KT_FUNC_HalIsResetOrShutdownPending,            // 0x0166 (358)
    XREF_KT_FUNC_IoMarkIrpMustComplete,                  // 0x0167 (359)
    XREF_KT_FUNC_HalInitiateShutdown,                    // 0x0168 (360)
    XREF_KT_FUNC_RtlSnprintf,                            // 0x0169 (361)
    XREF_KT_FUNC_RtlSprintf,                             // 0x016A (362)
    XREF_KT_FUNC_RtlVsnprintf,                           // 0x016B (363)
    XREF_KT_FUNC_RtlVsprintf,                            // 0x016C (364)
    XREF_KT_FUNC_HalEnableSecureTrayEject,               // 0x016D (365)
    XREF_KT_FUNC_HalWriteSMCScratchRegister,             // 0x016E (366)
    XREF_KT_FUNC_UnknownAPI367,                          // 0x016F (367)
    XREF_KT_FUNC_UnknownAPI368,                          // 0x0170 (368)
    XREF_KT_FUNC_UnknownAPI369,                          // 0x0171 (369)
    XREF_KT_FUNC_XProfpControl,                          // 0x0172 (370) PROFILING
    XREF_KT_FUNC_XProfpGetData,                          // 0x0173 (371) PROFILING
    XREF_KT_FUNC_IrtClientInitFast,                      // 0x0174 (372) PROFILING
    XREF_KT_FUNC_IrtSweep,                               // 0x0175 (373) PROFILING
    XREF_KT_FUNC_MmDbgAllocateMemory,                    // 0x0176 (374) DEVKIT ONLY!
    XREF_KT_FUNC_MmDbgFreeMemory,                        // 0x0177 (375) DEVKIT ONLY!
    XREF_KT_FUNC_MmDbgQueryAvailablePages,               // 0x0178 (376) DEVKIT ONLY!
    XREF_KT_FUNC_MmDbgReleaseAddress,                    // 0x0179 (377) DEVKIT ONLY!
    XREF_KT_FUNC_MmDbgWriteCheck,                        // 0x017A (378) DEVKIT ONLY!
    XREF_KT_COUNT,
    // END - DO NOT REARRANGE (kernel thunk)
    // D3D variable addresses
    XREF_D3DDEVICE=XREF_KT_COUNT, // initially set to XREF_ADDR_DERIVE // TODO : Rename to XREF_D3D__PDEVICE or something? // NOTE: There is such thing as D3D__DEVICE except it is at different address.
    XREF_D3DRS_CULLMODE, // initially set to XREF_ADDR_DERIVE
    //XREF_D3DRS_MULTISAMPLEMODE, // Avoid; It replaced to X_D3DRS_MULTISAMPLETYPE around XDK 4361
    XREF_D3DRS_MULTISAMPLERENDERTARGETMODE, // initially set to XREF_ADDR_DERIVE
    XREF_D3DRS_ROPZCMPALWAYSREAD, // initially set to XREF_ADDR_DERIVE
    XREF_D3DRS_ROPZREAD, // initially set to XREF_ADDR_DERIVE
    XREF_D3DRS_DONOTCULLUNCOMPRESSED, // initially set to XREF_ADDR_DERIVE
    XREF_D3DRS_STENCILCULLENABLE, // initially set to XREF_ADDR_DERIVE
    XREF_D3DTSS_TEXCOORDINDEX, // initially set to XREF_ADDR_DERIVE
    XREF_G_STREAM, // initially set to XREF_ADDR_DERIVE
    // Offsets :
    XREF_OFFSET_D3DDEVICE_M_PIXELSHADER, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_TEXTURES, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_PALETTES, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_RENDERTARGET, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_DEPTHSTENCIL, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_VERTICALBLANKEVENT, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_VBLANKCALLBACK, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_VERTEXSHADER, // initially set to XREF_ADDR_DERIVE
    // DSOUND variable addresses
    XREF_DSS_VOICE_VTABLE,
    XREF_DSS_STREAM_VTABLE,
    // Functions
    XREF_D3DDevice_SetRenderState_CullMode,
    XREF_D3DRS_STENCILENABLE,
    XREF_D3DRS_TWOSIDEDLIGHTING,
    XREF_D3DRS_BACKFILLMODE,
    XREF_D3DRS_FILLMODE,
    XREF_D3DRS_ZBIAS,
    XREF_D3DRS_LOGICOP,
    XREF_D3DRS_MULTISAMPLEANTIALIAS,
    XREF_D3DRS_SAMPLEALPHA,
    XREF_D3DRS_LINEWIDTH,
    XREF_D3DRS_MULTISAMPLEMASK,
    XREF_D3DRS_DXT1NOISEENABLE,
    XREF_D3DRS_YUVENABLE,
    XREF_D3DRS_OCCLUSIONCULLENABLE,
    XREF_D3DRS_MULTISAMPLEMODE,
    XREF_D3DDevice_SetLight,
    XREF_D3DDevice_LazySetStateVB,
    XREF_D3D_BlockOnResource,
    XREF_D3D_BlockOnTime,
    XREF_D3D_CreateStandAloneSurface,
    XREF_D3D_DestroyResource,
    XREF_D3D_SetFence,
    XREF_D3D_SetTileNoWait,
    XREF_D3D_KickOffAndWaitForIdle,
    XREF_D3D_MakeRequestedSpace,
    XREF_D3D_CDevice_KickOff,
    XREF_D3D_CDevice_MakeSpace,
    XREF_D3DPalette_Lock2,
    XREF_D3DTexture_GetSurfaceLevel2,
    XREF_D3DDevice_BlockUntilVerticalBlank,
    XREF_D3DDevice_CreatePalette2,
    XREF_D3DDevice_CreateIndexBuffer2,
    XREF_D3DDevice_CreateTexture2,
    XREF_D3DDevice_CreateVertexBuffer2,
    XREF_D3DDevice_GetBackBuffer2,
    XREF_D3DDevice_GetDepthStencilSurface2,
    XREF_D3DDevice_GetRenderTarget2,
    XREF_D3DDevice_SetRenderTarget,
    XREF_D3DDevice_MakeSpace,
    XREF_D3DDevice_SetRenderState_Simple,
    XREF_D3DDevice_SetRenderStateNotInline,
    XREF_D3DDevice_SetVertexShaderConstant1,
    XREF_D3DDevice_SetVertexShaderConstant4,
    XREF_D3DResource_AddRef,
    XREF_D3DVertexBuffer_Lock2,
    XREF_XMETAL_StartPush,
    XREF_XnInit,
    XREF_XID_fCloseDevice,
    XREF_D3D_ClearStateBlockFlags,
    XREF_D3D_RecordStateBlock,
    XREF_Lock2DSurface,
    XREF_Lock3DSurface,
    // DSOUND
    XREF_CDirectSound3DCalculator_Calculate3D,
    XREF_CDirectSound3DCalculator_GetMixBinVolumes,
    XREF_CDirectSound3DCalculator_GetPanData,
    XREF_CDirectSound3DCalculator_GetVoiceData,
    XREF_CDirectSoundBuffer_GetCurrentPosition,
    XREF_CDirectSoundBuffer_GetStatus,
    XREF_CDirectSoundBuffer_GetVoiceProperties,
    XREF_CDirectSoundBuffer_Lock,
    XREF_CDirectSoundBuffer_Pause,
    XREF_CDirectSoundBuffer_PauseEx,
    XREF_CDirectSoundBuffer_Play,
    XREF_CDirectSoundBuffer_PlayEx,
    XREF_CDirectSoundBuffer_Set3DVoiceData,
    XREF_CDirectSoundBuffer_SetAllParameters,
    XREF_CDirectSoundBuffer_SetBufferData,
    XREF_CDirectSoundBuffer_SetConeAngles,
    XREF_CDirectSoundBuffer_SetConeOrientation,
    XREF_CDirectSoundBuffer_SetConeOutsideVolume,
    XREF_CDirectSoundBuffer_SetCurrentPosition,
    XREF_CDirectSoundBuffer_SetDistanceFactor,
    XREF_CDirectSoundBuffer_SetDopplerFactor,
    XREF_CDirectSoundBuffer_SetEG,
    XREF_CDirectSoundBuffer_SetFilter,
    XREF_CDirectSoundBuffer_SetFormat,
    XREF_CDirectSoundBuffer_SetFrequency,
    XREF_CDirectSoundBuffer_SetHeadroom,
    XREF_CDirectSoundBuffer_SetI3DL2Source,
    XREF_CDirectSoundBuffer_SetLFO,
    XREF_CDirectSoundBuffer_SetLoopRegion,
    XREF_CDirectSoundBuffer_SetMaxDistance,
    XREF_CDirectSoundBuffer_SetMinDistance,
    XREF_CDirectSoundBuffer_SetMixBins,
    XREF_CDirectSoundBuffer_SetMixBinVolumes,
    XREF_CDirectSoundBuffer_SetMode,
    XREF_CDirectSoundBuffer_SetNotificationPositions,
    XREF_CDirectSoundBuffer_SetOutputBuffer,
    XREF_CDirectSoundBuffer_SetPitch,
    XREF_CDirectSoundBuffer_SetPlayRegion,
    XREF_CDirectSoundBuffer_SetPosition,
    XREF_CDirectSoundBuffer_SetRolloffCurve,
    XREF_CDirectSoundBuffer_SetRolloffFactor,
    XREF_CDirectSoundBuffer_SetVelocity,
    XREF_CDirectSoundBuffer_SetVolume,
    XREF_CDirectSoundBuffer_Stop,
    XREF_CDirectSoundBuffer_StopEx,
    XREF_CDirectSoundBuffer_Use3DVoiceData,
    XREF_CDirectSoundStream_AddRef,
    XREF_CDirectSoundStream_Constructor,
    XREF_CDirectSoundStream_FlushEx,
    XREF_CDirectSoundStream_GetVoiceProperties,
    XREF_CDirectSoundStream_Pause,
    XREF_CDirectSoundStream_PauseEx,
    XREF_CDirectSoundStream_Release,
    XREF_CDirectSoundStream_Set3DVoiceData,
    XREF_CDirectSoundStream_SetAllParameters,
    XREF_CDirectSoundStream_SetConeAngles,
    XREF_CDirectSoundStream_SetConeOrientation,
    XREF_CDirectSoundStream_SetConeOutsideVolume,
    XREF_CDirectSoundStream_SetDistanceFactor,
    XREF_CDirectSoundStream_SetDopplerFactor,
    XREF_CDirectSoundStream_SetEG,
    XREF_CDirectSoundStream_SetFilter,
    XREF_CDirectSoundStream_SetFormat,
    XREF_CDirectSoundStream_SetFrequency,
    XREF_CDirectSoundStream_SetHeadroom,
    XREF_CDirectSoundStream_SetI3DL2Source,
    XREF_CDirectSoundStream_SetLFO,
    XREF_CDirectSoundStream_SetMaxDistance,
    XREF_CDirectSoundStream_SetMinDistance,
    XREF_CDirectSoundStream_SetMixBins,
    XREF_CDirectSoundStream_SetMixBinVolumes_12,
    XREF_CDirectSoundStream_SetMixBinVolumes_8,
    XREF_CDirectSoundStream_SetMode,
    XREF_CDirectSoundStream_SetOutputBuffer,
    XREF_CDirectSoundStream_SetPitch,
    XREF_CDirectSoundStream_SetPosition,
    XREF_CDirectSoundStream_SetRolloffCurve,
    XREF_CDirectSoundStream_SetRolloffFactor,
    XREF_CDirectSoundStream_SetVelocity,
    XREF_CDirectSoundStream_SetVolume,
    XREF_CDirectSoundStream_Use3DVoiceData,
    XREF_CDirectSoundVoiceSettings_SetMixBins,
    XREF_CDirectSoundVoiceSettings_SetMixBinVolumes,
    XREF_CDirectSoundVoice_CommitDeferredSettings,
    XREF_CDirectSoundVoice_GetVoiceProperties,
    XREF_CDirectSoundVoice_Set3DVoiceData,
    XREF_CDirectSoundVoice_SetAllParameters,
    XREF_CDirectSoundVoice_SetConeAngles,
    XREF_CDirectSoundVoice_SetConeOrientation,
    XREF_CDirectSoundVoice_SetConeOutsideVolume,
    XREF_CDirectSoundVoice_SetDistanceFactor,
    XREF_CDirectSoundVoice_SetDopplerFactor,
    XREF_CDirectSoundVoice_SetEG,
    XREF_CDirectSoundVoice_SetFilter,
    XREF_CDirectSoundVoice_SetFormat,
    XREF_CDirectSoundVoice_SetFrequency,
    XREF_CDirectSoundVoice_SetHeadroom,
    XREF_CDirectSoundVoice_SetI3DL2Source,
    XREF_CDirectSoundVoice_SetLFO,
    XREF_CDirectSoundVoice_SetMaxDistance,
    XREF_CDirectSoundVoice_SetMinDistance,
    XREF_CDirectSoundVoice_SetMixBins,
    XREF_CDirectSoundVoice_SetMixBinVolumes,
    XREF_CDirectSoundVoice_SetMode,
    XREF_CDirectSoundVoice_SetOutputBuffer,
    XREF_CDirectSoundVoice_SetPitch,
    XREF_CDirectSoundVoice_SetPosition,
    XREF_CDirectSoundVoice_SetRolloffCurve,
    XREF_CDirectSoundVoice_SetRolloffFactor,
    XREF_CDirectSoundVoice_SetVelocity,
    XREF_CDirectSoundVoice_SetVolume,
    XREF_CDirectSoundVoice_Use3DVoiceData,
    XREF_CDirectSound_CommitDeferredSettings,
    XREF_CDirectSound_CommitEffectData,
    XREF_CDirectSound_CreateSoundBuffer,
    XREF_CDirectSound_CreateSoundStream,
    XREF_CDirectSound_DownloadEffectsImage,
    XREF_CDirectSound_DoWork,
    XREF_CDirectSound_EnableHeadphones,
    XREF_CDirectSound_GetCaps,
    XREF_CDirectSound_GetEffectData,
    XREF_CDirectSound_GetOutputLevels,
    XREF_CDirectSound_GetSpeakerConfig,
    XREF_CDirectSound_GetTime,
    XREF_CDirectSound_MapBufferData,
    XREF_CDirectSound_SetAllParameters,
    XREF_CDirectSound_SetDistanceFactor,
    XREF_CDirectSound_SetDopplerFactor,
    XREF_CDirectSound_SetEffectData,
    XREF_CDirectSound_SetI3DL2Listener,
    XREF_CDirectSound_SetMixBinHeadroom,
    XREF_CDirectSound_SetOrientation,
    XREF_CDirectSound_SetPosition,
    XREF_CDirectSound_SetRolloffFactor,
    XREF_CDirectSound_SetVelocity,
    XREF_CDirectSound_SynchPlayback,
    XREF_CDirectSound_UnmapBufferData,
    XREF_CFullHRTFSource_GetCenterVolume,
    XREF_CLightHRTFSource_GetCenterVolume,
    XREF_CFullHrtfSource_GetHrtfFilterPair,
    XREF_CHrtfSource_SetAlgorithm_FullHrtf,
    XREF_CHrtfSource_SetAlgorithm_LightHrtf,
    XREF_CHRTFSource_SetFullHRTF4Channel,
    XREF_CHRTFSource_SetFullHRTF5Channel,
    XREF_CHRTFSource_SetLightHRTF4Channel,
    XREF_CHRTFSource_SetLightHRTF5Channel,
    XREF_CLightHrtfSource_GetHrtfFilterPair,
    XREF_CMcpxAPU_Commit3dSettings,
    XREF_CMcpxAPU_ServiceDeferredCommandsLow,
    XREF_CMcpxAPU_Set3dDistanceFactor,
    XREF_CMcpxAPU_Set3dDopplerFactor,
    XREF_CMcpxAPU_Set3dParameters,
    XREF_CMcpxAPU_Set3dPosition,
    XREF_CMcpxAPU_Set3dRolloffFactor,
    XREF_CMcpxAPU_Set3dVelocity,
    XREF_CMcpxAPU_SetI3DL2Listener,
    XREF_CMcpxAPU_SetMixBinHeadroom,
    XREF_CMcpxAPU_SynchPlayback,
    XREF_CDirectSoundBufferSettings_SetBufferData,
    XREF_CMcpxBuffer_GetCurrentPosition,
    XREF_CMcpxBuffer_GetStatus,
    XREF_CMcpxBuffer_Pause,
    XREF_CMcpxBuffer_Pause_Ex,
    XREF_CMcpxBuffer_Play,
    XREF_CMcpxBuffer_Play_Ex,
    XREF_CMcpxBuffer_SetBufferData,
    XREF_CMcpxBuffer_SetCurrentPosition,
    XREF_CMcpxBuffer_Stop,
    XREF_CMcpxBuffer_Stop_Ex,
    XREF_CMcpxStream_Discontinuity,
    XREF_CMcpxStream_Flush,
    XREF_CMcpxStream_GetStatus,
    XREF_CMcpxStream_Pause,
    XREF_CMcpxStream_Pause_Ex,
    XREF_CMcpxStream_Stop,
    XREF_CMcpxStream_Stop_Ex,
    XREF_CMcpxVoiceClient_Commit3dSettings,
    XREF_CMcpxVoiceClient_GetVoiceProperties,
    XREF_CMcpxVoiceClient_Set3dConeOrientation,
    XREF_CMcpxVoiceClient_Set3dConeOutsideVolume,
    XREF_CMcpxVoiceClient_Set3dMaxDistance,
    XREF_CMcpxVoiceClient_Set3dMinDistance,
    XREF_CMcpxVoiceClient_Set3dMode,
    XREF_CMcpxVoiceClient_Set3dParameters,
    XREF_CMcpxVoiceClient_Set3dPosition,
    XREF_CMcpxVoiceClient_Set3dVelocity,
    XREF_CMcpxVoiceClient_SetEG,
    XREF_CMcpxVoiceClient_SetFilter,
    XREF_CMcpxVoiceClient_SetI3DL2Source,
    XREF_CMcpxVoiceClient_SetLFO,
    XREF_CMcpxVoiceClient_SetMixBins,
    XREF_CMcpxVoiceClient_SetPitch,
    XREF_CMcpxVoiceClient_SetVolume,
    XREF_CSensaura3d_GetFullHRTFFilterPair,
    XREF_CSensaura3d_GetLiteHRTFFilterPair,
    XREF_D3D_CommonSetRenderTarget,
    XREF_DirectSoundEnterCriticalSection,
    XREF_DSound_CRefCount_AddRef,
    XREF_DSound_CRefCount_Release,
    XREF_IDirectSound_CreateSoundBuffer,
    XREF_IDirectSound_CreateSoundStream,
    XREF_WaveFormat_CreateXboxAdpcmFormat,
    XREF_XAudioCalculatePitch,
    // XACT
    // +s
    XREF_XACT_CEngine_RegisterWaveBank,
    XREF_XACT_CEngine_RegisterStreamedWaveBank,
    XREF_XACT_CEngine_CreateSoundBank,
    XREF_XACT_CEngine_DownloadEffectsImage,
    XREF_XACT_CEngine_CreateSoundSource,
    XREF_XACT_CSoundBank_GetSoundCueIndexFromFriendlyName,
    XREF_XACT_CSoundBank_Play,
    XREF_XACT_CEngine_RegisterNotification,
    XREF_XACT_CEngine_GetNotification,
    XREF_XACT_CEngine_UnRegisterWaveBank,
    // XONLINE
    // +s
    XREF_XoUpdateLaunchNewImageInternal,
    XREF_CXo_XOnlineLogon,
    XREF_CXo_XOnlineMatchSearch,

    // XAPI
    XREF_XAPI_GetTypeInformation,

    // JVS
    XREF_JVS_SendCommand_String,
    XREF_JvsBACKUP_Read_String,
    XREF_JvsBACKUP_Write_String,
    XREF_JvsEEPROM_Read_String,
    XREF_JvsEEPROM_Write_String,
    XREF_JvsFirmwareDownload_String,
    XREF_JvsFirmwareUpload_String,
    XREF_JvsNodeReceivePacket_String,
    XREF_JvsNodeSendPacket_String,
    XREF_JvsRTC_Read_String,
    XREF_JvsRTC_Write_String,
    XREF_JvsScFirmwareDownload_String,
    XREF_JvsScFirmwareUpload_String,
    XREF_JvsScReceiveMidi_String,
    XREF_JvsScReceiveRs323c_String,
    XREF_JvsScSendMidi_String,
    XREF_JvsScSendRs323c_String,

    XREF_COUNT // XREF_COUNT must always be last.
    // Also, if XREF_COUNT > sizeof(uint16), enlarge struct OOVPA.XRefSaveIndex (and Value somehow)
} XRefDatabaseOffset;

#define XREF_ADDR_UNDETERMINED -1
#define XREF_ADDR_NOT_FOUND ((void*)0)
#define XREF_ADDR_DERIVE 1

typedef enum _xb_output_message {
    XB_OUTPUT_MESSAGE_DEBUG=0,
    XB_OUTPUT_MESSAGE_INFO,
    XB_OUTPUT_MESSAGE_WARN,
    XB_OUTPUT_MESSAGE_ERROR,
    // Only for internal usage.
    XB_OUTPUT_MESSAGE_MAX
} xb_output_message;

typedef enum _xb_xbe_type {
    XB_XBE_TYPE_RETAIL=0,
    XB_XBE_TYPE_DEBUG,
    XB_XBE_TYPE_CHIHIRO,
    // Only for internal usage.
    XB_XBE_TYPE_MAX
} xb_xbe_type;

static const uint32_t XB_XOR_KT[] = {
    0x5B6D40B6, // Kernel Thunk (Retail)
    0xEFB1F152, // Kernel Thunk (Debug)
    0x2290059D  // Kernel Thunk (Chihiro)
};

static const char* xbe_type_str[XB_XBE_TYPE_MAX] = {
    "RETAIL",
    "DEBUG",
    "CHIHIRO"
};

#ifndef xbaddr
typedef uint32_t xbaddr;
#endif

typedef struct _XbSDBLibrary {
    uint16_t    build_version;
    uint16_t    qfe_version;
    uint32_t    flag;
    char        name[8];
} XbSDBLibrary;

typedef struct _XbSDBLibraryHeader {
    unsigned int    count;
    XbSDBLibrary*   filters;
} XbSDBLibraryHeader;

typedef struct _XbSDBSection {
    // These three variables must be fixed info.
    char            name[8];
    uint32_t        xb_virt_addr;
    uint32_t        buffer_size;
    void*           buffer_lower;
} XbSDBSection;

typedef struct _XbSDBSectionHeader {
    unsigned int    count;
    XbSDBSection*   filters;
} XbSDBSectionHeader;

typedef void* XbSymbolContextHandle;

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

/// <summary>
/// Return value is only useful to prevent re-cache the file every time. It does not taken existing functions into account.
/// </summary>
/// <returns>Return a version of current library database.</returns>
unsigned int XbSymbolDatabase_LibraryVersion();

/// <summary>
/// Register one or more library to be scan instead of whole database for optimize performance.
/// <param name="library_filter">See defined prefix of XbSymbolLib_ above to choose one or more library you wish to scan.</param>
/// </summary>
/// <returns>Return true if success, or else will return false for invalid parameter.</returns>
bool XbSymbolContext_RegisterLibrary(XbSymbolContextHandle pHandle, uint32_t library_filter);

/// <summary>
/// To register any detected symbol name with address and build version back to third-party program.
/// NOTE: Be aware of library name will be varity since some libraries are detecting in other sections as well.
/// </summary>
/// <param name="library_str">Name of the library in string.</param>
typedef void(*xb_output_message_t)(xb_output_message message_flag, const char* message_str);

/// <summary>
/// For output a message to a program when have information to be output.
/// </summary>
/// <param name="message_func">Set output message to a function.</param>
void XbSymbolDatabase_SetOutputMessage(xb_output_message_t message_func);

/// <summary>
/// To register any detected symbol name with address and build version back to third-party program.
/// NOTE: Be aware of library name will be varity since some libraries are detecting in other sections as well.
/// </summary>
/// <param name="library_str">Name of the library in string.</param>
/// <param name="library_flag">Name of the library in flag.</param>
/// <param name="symbol_str">Name of the library in symbol string.</param>
/// <param name="address">Return xbox's virtual address.</param>
/// <param name="build_verison">Found with specific build verison.</param>
typedef void (*xb_symbol_register_t)(const char* library_str, uint32_t library_flag, const char* symbol_str, xbaddr address, uint32_t build_verison);

/// <summary>
/// DEPRECATED: To scan symbols in memory of raw xbe or host's virtual xbox environment.
/// </summary>
/// <param name="xb_header_addr">Starting point of xbox header address.</param>
/// <param name="register_func">Callback register function to be call for any detected symbols.</param>
/// <param name="is_raw">True: Full scan of raw xbe; False: Scan only loaded sections.</param>
/// <returns>Only return false if something is not valid.</returns>
bool XbSymbolScan(const void* xb_header_addr, xb_symbol_register_t register_func, bool is_raw);

/// <summary>
/// To convert library name string into flag format.
/// </summary>
/// <param name="library_name">Input library name string.</param>
/// <returns>Return 0 if does not in the database. Otherwise will return flag value.</returns>
uint32_t XbSymbolDatabase_LibraryToFlag(const char* library_name);

/// <summary>
/// (Debug feature) By calling it will perform a self test for duplicate OOVPAs. (May will change at any time.)
/// </summary>
/// <returns>Return total count of errors.</returns>
unsigned int XbSymbolDatabase_TestOOVPAs();

/// <summary>
/// (Debug feature) Set to true will perform full range of OOVPAs registered in current database.
/// Or stop at xbe's build version detected.
/// </summary>
/// <param name="bypass_limit">Input boolean to either bypass or enable the build version limit.</param>
void XbSymbolContext_SetBypassBuildVersionLimit(XbSymbolContextHandle pHandle, bool bypass_limit);

/// <summary>
/// To set verbose level can be output message.
/// By default, release build is set to info+ level and debug build is set to debug+ level.
/// </summary>
/// <param name="verbose_level">See xb_output_message enum for list of options.</param>
/// <returns>True: Successful set. False: Invalid input value.</returns>
bool XbSymbolDatabase_SetOutputVerbosity(xb_output_message verbose_level);

/// <summary>
/// (Debug feature) Set to true will continue the same signature scan after first detected.
/// </summary>
/// <param name="enable">Input boolean to either continue with the signature scan after first symbol found or not.</param>
void XbSymbolContext_SetContinuousSigScan(XbSymbolContextHandle pHandle, bool enable);

/// <summary>
/// (Debug feature) Set to true will register first detected address only.
/// This function can be used if XbSymbolContext_SetContinuousSigScan is set to true.
/// </summary>
/// <param name="enable">Input boolean to use first symbol address only or not.</param>
void XbSymbolContext_SetFirstDetectAddressOnly(XbSymbolContextHandle pHandle, bool enable);

/// <summary>
/// Step 1: Generate library array for LibraryHeader input.
/// First call with <paramref name="library_out"/> as null pointer will return total count. Then second call will insert information to <paramref name="library_out"/>.filters field.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <param name="library_out">Input null pointer will provide the count to allocate memory for library_out.filters field. Otherwise, information will be input to library_out.filters field.</param>
/// <returns>Return total library found can be use in scan process.</returns>
unsigned int XbSymbolDatabase_GenerateLibraryFilter(const void* xb_header_addr, XbSDBLibraryHeader* library_out);

/// <summary>
/// Step 2: Generate section array for SectionHeader input.
/// First call with <paramref name="section_out"/> as null pointer will return total count. Then second call will insert information to <paramref name="section_out"/>.filters field.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <param name="section_out">Input null pointer will provide the count to allocate memory, then allocate memory to section_out.filters field.</param>
/// <param name="is_raw">True: Convert array to use raw xbe's relative address; False: Convert array to use xbox virtual memory relative address.</param>
/// <returns>Return total sections found can be use in scan process.</returns>
unsigned int XbSymbolDatabase_GenerateSectionFilter(const void* xb_header_addr, XbSDBSectionHeader* section_out, bool is_raw);

/// <summary>
/// Step 3: Get Xbox kernel thunk address.
/// </summary>
/// <param name="xb_header_addr">Input pointer to xbox pe header.</param>
/// <returns>Return kernel thunk address. NOTE: This function may not return valid address.</returns>
xbaddr XbSymbolDatabase_GetKernelThunkAddress(const void* xb_header_addr);

/// <summary>
/// Step 4: Create XbSymbolContextHandle context for the scan process.
/// </summary>
/// <param name="ppHandle">Output XbSymbolContextHandle handler.</param>
/// <param name="register_func">Register callback function for any detected symbols during scan process.</param>
/// <param name="library_input">See XbSymbolDatabase_GenerateLibraryFilter for details.</param>
/// <param name="section_input">See XbSymbolDatabase_GenerateSectionFilter for details.</param>
/// <param name="kernel_thunk">Input decoded virtual kernel thunk.</param>
/// <returns>Return true if context handle's creation is a success.</returns>
bool XbSymbolDatabase_CreateXbSymbolContext(XbSymbolContextHandle* ppHandle, xb_symbol_register_t register_func, XbSDBLibraryHeader library_input, XbSDBSectionHeader section_input, xbaddr kernel_thunk);

/// <summary>
/// Step 5: Perform a manual scan to set references, XRefDatabaseOffset, manually by requirement.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_ScanManual(XbSymbolContextHandle pHandle);

/// <summary>
/// Step 6a: (multi-thread safe, C11 standard) Process individual library input by third-party.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
/// <param name="pLibrary">Input pointer of a library to start a scan process.</param>
/// <param name="xref_first_pass">True: Optimized first search scan process; False: 2nd call and later will continue to return non-zero; see return for detail.</param>
/// <returns>Return total xref count found. Unless it return zero, then there's nothing left to find.</returns>
unsigned int XbSymbolContext_ScanLibrary(XbSymbolContextHandle pHandle, const XbSDBLibrary* pLibrary, bool xref_first_pass);

/// <summary>
/// Step 6b: (single-thread usage) Process all of filter libraries internally.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_ScanAllLibraryFilter(XbSymbolContextHandle pHandle);

/// <summary>
/// Step 7: Register any references, XRefDatabaseOffset, may not had been output during the scan process.
/// NOTE: Currently a stub at the moment.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_RegisterXRefs(XbSymbolContextHandle pHandle);

/// <summary>
/// Final Step: Release context.
/// </summary>
/// <param name="pHandle">Input XbSymbolContextHandle handler.</param>
void XbSymbolContext_Release(XbSymbolContextHandle pHandle);

#ifdef __cplusplus
}
#endif

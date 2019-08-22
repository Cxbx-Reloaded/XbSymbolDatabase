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
#ifndef HLEDATABASE_H
#define HLEDATABASE_H

#include <stdlib.h> // for size_t
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "OOVPA.h"

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
// * XRefDataBaseOffset
// ******************************************************************
typedef enum _XRefDataBaseOffset
{
    // D3D variable addresses
    XREF_D3DDEVICE=0, // initially set to XREF_ADDR_DERIVE // TODO : Rename to XREF_D3D__PDEVICE or something? // NOTE: There is such thing as D3D__DEVICE except it is at different address.
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
    XREF_OFFSET_D3DDEVICE_M_EVENTHANDLE, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_SWAPCALLBACK, // initially set to XREF_ADDR_DERIVE
    XREF_OFFSET_D3DDEVICE_M_VBLANKCALLBACK, // initially set to XREF_ADDR_DERIVE
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
} XRefDataBaseOffset;

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

static const char* xbe_type_str[XB_XBE_TYPE_MAX] = {
    "RETAIL",
    "DEBUG",
    "CHIHIRO"
};

#ifndef xbaddr
typedef uint32_t xbaddr;
#endif

// ******************************************************************
// * API functions to use with other projects.
// ******************************************************************

/// <summary>
/// Return value is only useful to prevent re-cache the file every time. It does not taken existing functions into account.
/// </summary>
/// <returns>Return a version of current library database.</returns>
unsigned int XbSymbolLibraryVersion();

/// <summary>
/// Register one or more library to be scan instead of whole database for optimize performance.
/// <param name="library_flag">See defined prefix of XbSymbolLib_ above to choose one or more library you wish to scan.</param>
/// </summary>
/// <returns>Return true if success, or else will return false for invalid parameter.</returns>
bool XbSymbolRegisterLibrary(uint32_t library_flag);

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
void XbSymbolSetOutputMessage(xb_output_message_t message_func);

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
/// To scan symbols in memory of raw xbe or host's virtual xbox environment.
/// </summary>
/// <param name="xb_header_addr">Starting point of xbox header address.</param>
/// <param name="register_func">Callback register function to be call for any detected symbols.</param>
/// <param name="is_raw">True: Full scan of raw xbe; False: Scan only loaded sections.</param>
/// <returns>Only return false if something is not valid.</returns>
bool XbSymbolScan(const void* xb_header_addr, xb_symbol_register_t register_func, bool is_raw);

/* NOTE: Do not use this function, It is currently not functional and optimized at the moment.
/// <summary>
/// To scan symbols for each Xbe's section given with boundaries requirement.
/// NOTE: Scanning per section is a requirement to prevent any false detection since some binary functions are too small and a lot of identical codes.
/// </summary>
/// <param name="xbeData">Starting point of xbe memory address.</param>
/// <param name="section_name">Section name string to scan.</param>
/// <param name="lower_bound">Starting point of relative address base on xbeData.</param>
/// <param name="upper_bound">Ending point of relative address base on xbeData.</param>
/// <param name="register_func">Callback register function to be call for any detected symbols.</param>
/// <returns>Only return true if a section name is in the database.</returns>
bool XbSymbolScanSection(uint32_t xbe_base_address, uint32_t xbe_size, const char* section_name, uint32_t section_virtual_address, uint32_t section_size, uint16_t build_verison, xb_symbol_register_t register_func);
*/

/// <summary>
/// To convert library name string into flag format.
/// </summary>
/// <param name="library_name">Input library name string.</param>
/// <returns>Return 0 if does not in the database. Otherwise will return flag value.</returns>
uint32_t XbSymbolLibraryToFlag(const char* library_name);

/// <summary>
/// (Debug feature) By calling it will perform a self test for duplicate OOVPAs. (May will change at any time.)
/// </summary>
/// <returns>Return total count of errors.</returns>
unsigned int XbSymbolDataBaseTestOOVPAs();

/// <summary>
/// (Debug feature) Set to true will perform full range of OOVPAs registered in current database.
/// Or stop at xbe's build version detected.
/// </summary>
/// <param name="bypass_limit">Input boolean to either bypass or enable the build version limit.</param>
void XbSymbolBypassBuildVersionLimit(bool bypass_limit);

/// <summary>
/// To set verbose level can be output message.
/// By default, release build is set to info+ level and debug build is set to debug+ level.
/// </summary>
/// <param name="verbose_level">See xb_output_message enum for list of options.</param>
bool XbSymbolSetOutputVerbosity(xb_output_message verbose_level);

/// <summary>
/// (Debug feature) Set to true will continue the same signature scan after first detected.
/// </summary>
/// <param name="enable">Input boolean to either continue with the signature scan after first symbol found or not.</param>
void XbSymbolContinuousSigScan(bool enable);

/// <summary>
/// (Debug feature) Set to true will register first detected address only.
/// This function can be used if XbSymbolContinuousSigScan is set to true.
/// </summary>
/// <param name="enable">Input boolean to use first symbol address only or not.</param>
void XbSymbolFirstDetectAddressOnly(bool enable);

#ifdef __cplusplus
}
#endif

#endif /*HLEDATABASE_H*/

/*
CRTKDABLoader: This class loads all RTKDAB.dll functions

Copyright (c) 2015 Albrecht Lohofener <albrechtloh@gmx.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include <string>

#include "CRTKDABCallBacks.h"

// Define the RTKDAB.dll function prototype
typedef int(__cdecl* RTDAB_OpenDevice_t)(void);
typedef int(__cdecl* RTDAB_CloseDevice_t)(void); // Not tested. Prototyp can be wrong!

typedef int(__cdecl* RTDAB_Start_t)(void);
typedef int(__cdecl* RTDAB_Stop_t)(void); // Not tested. Prototyp can be wrong!
typedef int(__cdecl* RTDAB_DebugCMD_t)(void); // Not tested. Prototyp can be wrong!

typedef int(__cdecl* RTDAB_SetFreqAndBW_t)(int Frequeny_kHz);
typedef int(__cdecl* RTDAB_AddServiceCom_t)(int ParaMode, int ID, int StartCU, int U_E, int Index, int EEPIdx, int CUNum, int PacketAddr, int FEC);
typedef int(__cdecl* RTDAB_ChangeSCOrg_t)(void); // Not tested. Prototyp can be wrong!
typedef int(__cdecl* RTDAB_DelServiceCom_t)(int ParaMode, int ID, int PacketAddr);

typedef int(__cdecl* RTDAB_GetFreqAndBW_t)(int* FreqAndBWPtr); // Not tested. Prototyp can be wrong!
typedef int(__cdecl* RTDAB_GetSignalQuality_t)(int* SignalQualityPtr);
typedef int(__cdecl* RTDAB_GetSignalLock_t)(int* SignalLockPtr);
typedef int(__cdecl* RTDAB_GetSignalPresent_t)(int* SignalPresentPtr);
typedef int(__cdecl* RTDAB_GetSignalStrength_t)(int* SignalStrengthPtr);
typedef int(__cdecl* RTDAB_GetTunerRange_t)(int* TunerRangePtr); // Not tested. Prototyp can be wrong!

typedef int(__cdecl* RTDAB_SetMSCCallBack_t)(void* CallBackFcnPtr);
typedef int(__cdecl* RTDAB_SetFICCallBack_t)(void* CallBackFcnPtr); // Not tested. Prototyp can be wrong!
typedef int(__cdecl* RTDAB_SetStreamDataCallBack_t)(void* CallBackFcnPtr); // Not tested. Prototyp can be wrong!
typedef int(__cdecl* RTDAB_SetPacketCallBack_t)(void* CallBackFcnPtr); // Not tested. Prototyp can be wrong!
typedef int(__cdecl* RTDAB_SetMWFICCallBack_t)(void* CallBackFcnPtr); // Not tested. Prototyp can be wrong!

// Define the RTL283XACCESS.dll function prototype
typedef int(__cdecl* RTL283XACCESS_SetIPAddressAndPort_t)(const char* IPAddress, uint32_t Port);

// This is a singleton 
class CRTKDABLoader
{
public:
	static CRTKDABLoader* create(CRTKDABCallBacks &RTKDABCallBacks);
	~CRTKDABLoader();

	bool Load(void);
	bool Load(std::string rtl_tcp_IPAddress, uint32_t rtl_tcp_Port);

	int OpenDevice(void);
	int CloseDevice(void);

	int Start(void);
	int Stop(void);
	int DebugCMD(void);

	int SetFreqAndBW(int Frequeny_kHz);
	int AddServiceCom(int ParaMode, int ID, int StartCU, int U_E, int Index, int EEPIdx, int CUNum, int PacketAddr, int FEC);
	int ChangeSCOrg(void);
	int DelServiceCom(int ParaMode, int ID, int PacketAddr);

	int GetFreqAndBW(void);
	int GetSignalQuality(void);
	int GetSignalLock(void);
	int GetSignalPresent(void);
	int GetSignalStrength(void);
	int GetTunerRange(void);

	// ***** RTKDAB call back functions *****
	static int MSCCallBack(char* Data, int Size, int a);
	static int StreamDataCallBack(void* ptr);
	static int PacketCallBack(void* ptr);
	static int MWFICCallBack(void* Data, int DataRate, int Size);
	static int FICCallBack(void* Data, int DataRate, int Size);

protected:
	CRTKDABLoader(CRTKDABCallBacks &RTKDABCallBacks);

private:
	static CRTKDABLoader* Instance;

	CRTKDABCallBacks* m_RTKDABCallBacksPtr;

	void* RTKDAB_dllHandle;
	void* RTL283XACCESS_dllHandle;

	bool isRTKDABdllLoaded;

	// Pointers to the RTKDAB.dll funtions
	RTDAB_OpenDevice_t RTKDAB_OpenDevice;
	RTDAB_CloseDevice_t RTKDAB_CloseDevice;

	RTDAB_Start_t RTDAB_Start;
	RTDAB_Stop_t RTDAB_Stop;
	RTDAB_DebugCMD_t RTDAB_DebugCMD;

	RTDAB_SetFreqAndBW_t RTDAB_SetFreqAndBW;
	RTDAB_AddServiceCom_t RTDAB_AddServiceCom;
	RTDAB_ChangeSCOrg_t RTDAB_ChangeSCOrg;
	RTDAB_DelServiceCom_t RTDAB_DelServiceCom;

	RTDAB_GetFreqAndBW_t RTDAB_GetFreqAndBW;
	RTDAB_GetSignalQuality_t RTDAB_GetSignalQuality;
	RTDAB_GetSignalLock_t RTDAB_GetSignalLock;
	RTDAB_GetSignalPresent_t RTDAB_GetSignalPresent;
	RTDAB_GetSignalStrength_t RTDAB_GetSignalStrength;
	RTDAB_GetTunerRange_t RTDAB_GetTunerRange;

	RTDAB_SetMSCCallBack_t RTDAB_SetMSCCallBack;
	RTDAB_SetFICCallBack_t RTDAB_SetFICCallBack;
	RTDAB_SetStreamDataCallBack_t RTDAB_SetStreamDataCallBack;
	RTDAB_SetPacketCallBack_t RTDAB_SetPacketCallBack;
	RTDAB_SetMWFICCallBack_t RTDAB_SetMWFICCallBack;

	//Pointers to the RTL283XACCESS.dll funtions
	RTL283XACCESS_SetIPAddressAndPort_t RTL283XACCESS_SetIPAddressAndPort;
};


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

#include "CRTKDABLoader.h"

#include <iostream>
#include <windows.h> // 

CRTKDABLoader* CRTKDABLoader::Instance = 0;

CRTKDABLoader* CRTKDABLoader::create(CRTKDABCallBacks &RTKDABCallBacks)
{
	if(Instance == 0)
		Instance = new CRTKDABLoader(RTKDABCallBacks);
	else
		fprintf(stderr, "Only one CRTKDABLoader instance is allowed\n");

	return Instance;
}

CRTKDABLoader::CRTKDABLoader(CRTKDABCallBacks &RTKDABCallBacks)
{
	m_RTKDABCallBacksPtr = &RTKDABCallBacks;

	RTKDAB_dllHandle = NULL;
	RTL283XACCESS_dllHandle = NULL;
	isRTKDABdllLoaded = false;
	isOpened = false;

	// RTKDAB.dll functions pointer 
	RTKDAB_OpenDevice = NULL;
	RTKDAB_CloseDevice = NULL;

	RTDAB_Start = NULL;
	RTDAB_Stop = NULL;
	RTDAB_DebugCMD = NULL;

	RTDAB_SetFreqAndBW = NULL;
	RTDAB_AddServiceCom = NULL;
	RTDAB_ChangeSCOrg = NULL;
	RTDAB_DelServiceCom = NULL;

	RTDAB_GetFreqAndBW = NULL;
	RTDAB_GetSignalQuality = NULL;
	RTDAB_GetSignalLock = NULL;
	RTDAB_GetSignalPresent = NULL;
	RTDAB_GetSignalStrength = NULL;
	RTDAB_GetTunerRange = NULL;

	RTDAB_SetMSCCallBack = NULL;
	RTDAB_SetFICCallBack = NULL;
	RTDAB_SetStreamDataCallBack = NULL;
	RTDAB_SetPacketCallBack = NULL;
	RTDAB_SetMWFICCallBack = NULL;

	// RTL283XACCESS.dll functions pointer 
	RTL283XACCESS_SetIPAddressAndPort = NULL;
	RTL283XACCESS_GetConnectionState = NULL;
}

CRTKDABLoader::~CRTKDABLoader()
{
	//Free the library:
	FreeLibrary((HINSTANCE) RTKDAB_dllHandle);
	FreeLibrary((HINSTANCE) RTL283XACCESS_dllHandle);
}

bool CRTKDABLoader::Load(void)
{
	// Default rtl_tcp IP adress and port
	return Load("127.0.0.1", 1234);
}

bool CRTKDABLoader::Load(std::string rtl_tcp_IPAddress, uint32_t rtl_tcp_Port)
{
	int retVal;
	
	// First try to load "RTL283XACCESS.dll". If it doesn't exist "RTKDAB.dll" will crash
	RTL283XACCESS_dllHandle = (HINSTANCE)LoadLibrary("RTL283XACCESS.dll");
	if (NULL == RTL283XACCESS_dllHandle)
	{
		fprintf(stderr, "Error while loading RTL283XACCESS.dll\n");
	}
	else
	{
		fprintf(stderr, "RTL283XACCESS.dll library loaded sucessfully\n");

		// Set the rtl_tcp IP address and port
		// RTKDAB.dll will load this DLL as well but the DLL will only be loaded once. So it is possible to set the IP address and port.
		RTL283XACCESS_SetIPAddressAndPort = (RTL283XACCESS_SetIPAddressAndPort_t) GetProcAddress((HINSTANCE)RTL283XACCESS_dllHandle, "SetIPAddressAndPort");
		RTL283XACCESS_GetConnectionState = (RTL283XACCESS_GetConnectionState_t)GetProcAddress((HINSTANCE)RTL283XACCESS_dllHandle, "GetConnectionState");

		if (RTL283XACCESS_SetIPAddressAndPort)
			RTL283XACCESS_SetIPAddressAndPort(rtl_tcp_IPAddress.c_str(), rtl_tcp_Port);

		// Load RTKDAB.dll
		RTKDAB_dllHandle = (HINSTANCE)LoadLibrary("RTKDAB.dll");

		// If the handle is valid, try to get the function address. 
		if (NULL != RTKDAB_dllHandle)
		{
			isRTKDABdllLoaded = true;

			fprintf(stderr, "RTKDAB.dll library loaded sucessfully\n");

			// ****** Get the pointer pointers to the functions ******
			RTKDAB_OpenDevice = (RTDAB_OpenDevice_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_OpenDevice");
			RTKDAB_CloseDevice = (RTDAB_CloseDevice_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_CloseDevice");

			RTDAB_Start = (RTDAB_Start_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_Start");
			RTDAB_Stop = (RTDAB_Stop_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_Stop");
			RTDAB_DebugCMD = (RTDAB_Start_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_Start");

			RTDAB_SetFreqAndBW = (RTDAB_SetFreqAndBW_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_SetFreqAndBW");
			RTDAB_AddServiceCom = (RTDAB_AddServiceCom_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_AddServiceCom");
			RTDAB_ChangeSCOrg = (RTDAB_ChangeSCOrg_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_ChangeSCOrg");
			RTDAB_DelServiceCom = (RTDAB_DelServiceCom_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_DelServiceCom");

			RTDAB_GetFreqAndBW = (RTDAB_GetFreqAndBW_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_GetFreqAndBW");
			RTDAB_GetSignalQuality = (RTDAB_GetSignalQuality_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_GetSignalQuality");
			RTDAB_GetSignalLock = (RTDAB_GetSignalLock_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_GetSignalLock");
			RTDAB_GetSignalPresent = (RTDAB_GetSignalPresent_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_GetSignalPresent");
			RTDAB_GetSignalStrength = (RTDAB_GetSignalStrength_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_GetSignalStrength");
			RTDAB_GetTunerRange = (RTDAB_GetTunerRange_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_GetTunerRange");

			RTDAB_SetMSCCallBack = (RTDAB_SetMSCCallBack_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_SetMSCCallBack");
			RTDAB_SetFICCallBack = (RTDAB_SetFICCallBack_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_SetFICCallBack");
			RTDAB_SetStreamDataCallBack = (RTDAB_SetStreamDataCallBack_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_SetStreamDataCallBack");
			RTDAB_SetPacketCallBack = (RTDAB_SetPacketCallBack_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_SetPacketCallBack");
			RTDAB_SetMWFICCallBack = (RTDAB_SetMWFICCallBack_t)GetProcAddress((HINSTANCE)RTKDAB_dllHandle, "RTDAB_SetMWFICCallBack");

			// ****** Set the call back functions ******
			// ToDo: Add retVal analysis
			if (NULL != RTDAB_SetMSCCallBack)
			{
				retVal = RTDAB_SetMSCCallBack(&CRTKDABLoader::MSCCallBack);
			}

			if (NULL != RTDAB_SetFICCallBack)
			{
				retVal = RTDAB_SetFICCallBack(&CRTKDABLoader::FICCallBack);
			}

			if (NULL != RTDAB_SetStreamDataCallBack)
			{
				retVal = RTDAB_SetStreamDataCallBack(&CRTKDABLoader::StreamDataCallBack);
			}

			if (NULL != RTDAB_SetPacketCallBack)
			{
				retVal = RTDAB_SetPacketCallBack(&CRTKDABLoader::PacketCallBack);
			}

			if (NULL != RTDAB_SetMWFICCallBack)
			{
				retVal = RTDAB_SetMWFICCallBack(&CRTKDABLoader::MWFICCallBack);
			}
		}
		else
		{
			fprintf(stderr, "Error while loading RTKDAB.dll\n");
		}
	}

	return isRTKDABdllLoaded;
}

int CRTKDABLoader::OpenDevice(void)
{
	int retVal = -1;

	fprintf(stderr, "Called OpenDevice()\n");

	if(NULL != RTKDAB_OpenDevice && isRTKDABdllLoaded)
	{
		retVal = RTKDAB_OpenDevice();

		if (retVal == 1)
			isOpened = true;
	}
 
	return retVal;
}

int CRTKDABLoader::CloseDevice(void)
{
	int retVal = -1;

	fprintf(stderr, "Called CloseDevice()\n");
	if (NULL != RTKDAB_CloseDevice && isRTKDABdllLoaded)
	{
		retVal = RTKDAB_CloseDevice();

		if (RTL283XACCESS_GetConnectionState)
		{
			while (RTL283XACCESS_GetConnectionState() == 1)
			{
				fprintf(stderr, "Waiting for closed connection\n");
				Sleep(100); // Wait 100 ms
			}
		}
	}

	// No matter what. Mark the device as closed
	isOpened = false;

	return retVal;
}

int CRTKDABLoader::Start(void)
{
	int retVal = -1;

	fprintf(stderr, "Called Start()\n");
	if (NULL != RTDAB_Start && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_Start();
	}

	return retVal;
}

int CRTKDABLoader::Stop(void)
{
	int retVal = -1;

	fprintf(stderr, "Called Stop()\n");
	if (NULL != RTDAB_Stop && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_Stop();
	}

	return retVal;
}

int CRTKDABLoader::DebugCMD(void)
{
	int retVal = -1;

	if (NULL != RTDAB_DebugCMD && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_DebugCMD();
	}

	return retVal;
}

int CRTKDABLoader::SetFreqAndBW(int Frequeny_kHz)
{
	int retVal = -1;

	fprintf(stderr, "Called SetFreqAndBW()\n");
	if (NULL != RTDAB_SetFreqAndBW && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_SetFreqAndBW(Frequeny_kHz);
	}

	return retVal;
}

int CRTKDABLoader::AddServiceCom(int ParaMode, int ID, int StartCU, int U_E, int Index, int EEPIdx, int CUNum, int PacketAddr, int FEC)
{
	int retVal = -1;

	if (NULL != RTDAB_AddServiceCom && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_AddServiceCom(ParaMode, ID, StartCU, U_E, Index, EEPIdx, CUNum, PacketAddr, FEC);
	}

	return retVal;
}

int CRTKDABLoader::ChangeSCOrg(void)
{
	int retVal = -1;

	if (NULL != RTDAB_ChangeSCOrg && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_ChangeSCOrg();
	}

	return retVal;
}

int CRTKDABLoader::DelServiceCom(int ParaMode, int ID, int PacketAddr)
{
	int retVal = -1;

	if (NULL != RTDAB_DelServiceCom && isRTKDABdllLoaded && isOpened)
	{
		retVal = RTDAB_DelServiceCom(ParaMode, ID, PacketAddr);
	}

	return retVal;
}

int CRTKDABLoader::GetFreqAndBW(void)
{
	int retVal = -1;
	int FreqAndBW = -1;

	if (NULL != RTDAB_GetFreqAndBW && isRTKDABdllLoaded && isOpened)
	{
		// ToDo: Add retVal analysis
		retVal = RTDAB_GetFreqAndBW(&FreqAndBW);
	}

	return FreqAndBW;
}

int CRTKDABLoader::GetSignalQuality(void)
{
	int retVal = -1;
	int SignalQuality = 1;

	if (NULL != RTDAB_GetSignalQuality && isRTKDABdllLoaded && isOpened)
	{
		// ToDo: Add retVal analysis
		retVal = RTDAB_GetSignalQuality(&SignalQuality);
	}

	return SignalQuality;
}

int CRTKDABLoader::GetSignalLock(void)
{
	int retVal = -1;
	int SignalLock = -1;

	if (NULL != RTDAB_GetSignalLock && isRTKDABdllLoaded && isOpened)
	{
		// ToDo: Add retVal analysis
		retVal = RTDAB_GetSignalLock(&SignalLock);
	}

	return SignalLock;
}

int CRTKDABLoader::GetSignalPresent(void)
{
	int retVal = -1;
	int SignalPresent = -1;

	if (NULL != RTDAB_GetSignalPresent && isRTKDABdllLoaded && isOpened)
	{
		// ToDo: Add retVal analysis
		retVal = RTDAB_GetSignalPresent(&SignalPresent);
	}

	return SignalPresent;
}

int CRTKDABLoader::GetSignalStrength(void)
{
	int retVal = -1;
	int SignalStrength = -1;

	if (NULL != RTDAB_GetSignalStrength && isRTKDABdllLoaded && isOpened)
	{
		// ToDo: Add retVal analysis
		retVal = RTDAB_GetSignalStrength(&SignalStrength);
	}

	return SignalStrength;
}

int CRTKDABLoader::GetTunerRange(void)
{
	int retVal = -1;
	int TunerRange = -1;

	if (NULL != RTDAB_GetTunerRange && isRTKDABdllLoaded && isOpened)
	{
		// ToDo: Add retVal analysis
		retVal = RTDAB_GetTunerRange(&TunerRange);
	}

	return TunerRange;
}

// ***** RTKDAB call back functions *****
int CRTKDABLoader::MSCCallBack(char* Data, int Size, int a)
{
	if(Instance->m_RTKDABCallBacksPtr)
		Instance->m_RTKDABCallBacksPtr->MSCCallBack(Data, Size, a);

	return 0;
}

int CRTKDABLoader::StreamDataCallBack(void* ptr)
{
	if (Instance->m_RTKDABCallBacksPtr)
		Instance->m_RTKDABCallBacksPtr->StreamDataCallBack(ptr);

	return 0;
}

int CRTKDABLoader::PacketCallBack(void* ptr)
{
	if (Instance->m_RTKDABCallBacksPtr)
		Instance->m_RTKDABCallBacksPtr->PacketCallBack(ptr);

	return 0;
}

/*
* Parameters:
* Data??
* DataRate??
* Size??
*/
int CRTKDABLoader::MWFICCallBack(void* Data, int DataRate, int Size)
{
	if (Instance->m_RTKDABCallBacksPtr)
		Instance->m_RTKDABCallBacksPtr->MWFICCallBack(Data, DataRate, Size);

	return 0;
}

/*
* Parameters:
* Data??
* DataRate??
* Size??
*/
int CRTKDABLoader::FICCallBack(void* Data, int DataRate, int Size)
{
	if (Instance->m_RTKDABCallBacksPtr)
		Instance->m_RTKDABCallBacksPtr->FICCallBack(Data, DataRate, Size);

	return 0;
}
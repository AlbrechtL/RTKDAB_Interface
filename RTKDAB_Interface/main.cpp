/*
Main: Main for RTKDAB_Interface

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

#include <iostream>
#include <stdio.h>
#include <conio.h>

//  #define ANYRPC_THREADING <-- Has to be added to the Visual Studio project

#include "CProcessFunctions.h"
#include "CProcessCallBacks.h"
#include "CRTKDABLoader.h"

#define MESSAGEPACK_SERVER_PORT 8778
#define MESSAGEPACK_CLIENT_IPADDRESS "10.10.1.123"
#define MESSAGEPACK_CLIENT_PORT 9000
#define RTL_TCP_IPADDRESS "10.10.1.123"
#define RTL_TCP_PORT 1234

using namespace std;

int main(void)
{
	int SignalQuality = 0;
	int SignalLock = 0;
	int SignalPresent = 0;
	int SignalStrength = 0;

	// ProcessCallBacks tries to connect to a messagepack server to transmit the call back data
	CProcessCallBacks ProcessCallBacks(MESSAGEPACK_CLIENT_IPADDRESS, MESSAGEPACK_CLIENT_PORT);

	CRTKDABLoader RTKDABLoader = *CRTKDABLoader::create(ProcessCallBacks); // CRTKDABLoader is a singleton class

	// Open a messagepack server to accept calls
	CProcessFunctions ProcessFunctions(MESSAGEPACK_SERVER_PORT, &RTKDABLoader);

	// Load the RTKDAB.dll und connect to "rtl_tcp" with the given IP address and port
	RTKDABLoader.Load(RTL_TCP_IPADDRESS, RTL_TCP_PORT);
	//RTKDABLoader.Load();
	RTKDABLoader.OpenDevice();
	RTKDABLoader.SetFreqAndBW(222064); // Channel 11D
	RTKDABLoader.Start();
	
	char ch = 0;
	while(ch != 'q')
	{
		ch = _getch();

		if (ch == 's')
		{
			SignalQuality = RTKDABLoader.GetSignalQuality();
			SignalLock = RTKDABLoader.GetSignalLock();
			SignalPresent = RTKDABLoader.GetSignalPresent();
			SignalStrength = RTKDABLoader.GetSignalStrength();

			cout << "Signal quality: " << SignalQuality << "\n";
			cout << "Signal lock: " << SignalLock << "\n";
			cout << "Signal present: " << SignalPresent << "\n";
			cout << "Signal strength: " << SignalStrength << "\n";
		}

		if (ch == 'c')
		{
			// int ParaMode, int ID, int StartCU, int U_E, int Index, int EEPIdx, int CUNum, int PacketAddr, int FEC
			// 1 Live at 222064 kHz
			RTKDABLoader.AddServiceCom(0, 1, 0, 1, 0, 2, 72, 0, 2);
		}

		if (ch == 'x')
		{
			// int ParaMode, int ID, int StartCU, int U_E, int Index, int EEPIdx, int CUNum, int PacketAddr, int FEC
			// WDR2 at 222064 kHz
			RTKDABLoader.AddServiceCom(0, 7, 360, 1, 0, 2, 72, 0, 2);
		}
	}

	system("pause");

	return 0;
}
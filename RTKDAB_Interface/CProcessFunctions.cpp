/*
CProcessFunctions: This is a message pack interface to call RTKDAB.dll functions

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

#include "CProcessFunctions.h"

using namespace anyrpc;

CProcessFunctions::CProcessFunctions(int Port, CRTKDABLoader* RTKDABLoader)
{
	// New message pack TCP server with threading
	MessagePack_Server = new anyrpc::MessagePackTcpServerTP;

	// Bind to port
	MessagePack_Server->BindAndListen(Port);

	// Add the method calls
	MethodManager = MessagePack_Server->GetMethodManager();

	// Add callback methods
	MethodManager->AddMethod(new CAddServiceCom("AddServiceCom", "No help available", true, RTKDABLoader));
	MethodManager->AddMethod(new CDelServiceCom("DelServiceCom", "No help available", true, RTKDABLoader));
	MethodManager->AddMethod(new CSetFreq("SetFreq", "No help available", true, RTKDABLoader));

	MessagePack_Server->StartThread();
}


CProcessFunctions::~CProcessFunctions()
{
	MessagePack_Server->StopThread();
}

CFunctionCallback::CFunctionCallback(std::string const& name, std::string const& help, bool deleteOnRemove, CRTKDABLoader* RTKDABLoader_) :Method(name, help, deleteOnRemove)
{
	RTKDABLoader = RTKDABLoader_;
}

void CAddServiceCom::Execute(anyrpc::Value& params, anyrpc::Value& result)
{
	int ParaMode = 0;
	int ID = 0;
	int StartCU = 0;
	int U_E = 0;
	int Index = 0;
	int EEPIdx = 0;
	int CUNum = 0;
	int PacketAddr = 0;
	int FEC = 0;

	// Some checks about the received data
	if (params.IsArray() &&
		params.Size() == 9 &&
		params[0].IsNumber() &&
		params[1].IsNumber() &&
		params[2].IsNumber() &&
		params[3].IsNumber() &&
		params[4].IsNumber() &&
		params[5].IsNumber() &&
		params[6].IsNumber() &&
		params[7].IsNumber() &&
		params[8].IsNumber())
	{
		ParaMode = params[0].GetInt();
		ID = params[1].GetInt();
		StartCU = params[2].GetInt();
		U_E = params[3].GetInt();
		Index = params[4].GetInt();
		EEPIdx = params[5].GetInt();
		CUNum = params[6].GetInt();
		PacketAddr = params[7].GetInt();
		FEC = params[8].GetInt();

		RTKDABLoader->AddServiceCom(ParaMode, ID, StartCU, U_E, Index, EEPIdx, CUNum, PacketAddr, FEC);
	}
}

void CDelServiceCom::Execute(anyrpc::Value& params, anyrpc::Value& result)
{
	int ParaMode = 0;
	int ID = 0;
	int PacketAddr = 0;

	// Some checks about the received data
	if (params.IsArray() &&
		params.Size() == 3 &&
		params[0].IsNumber() &&
		params[1].IsNumber() &&
		params[2].IsNumber())
	{
		ParaMode = params[0].GetInt();
		ID = params[1].GetInt();
		PacketAddr = params[2].GetInt();

		RTKDABLoader->DelServiceCom(ParaMode, ID, PacketAddr);
	}
}


void CSetFreq::Execute(anyrpc::Value& params, anyrpc::Value& result)
{
	int Frequency = 0;

	// Some checks about the received data
	if (params.IsNumber())
	{
		Frequency = params.GetInt();

		RTKDABLoader->SetFreqAndBW(Frequency);
	}
}
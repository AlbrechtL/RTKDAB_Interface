/*
CProcessCallBacks: This is a message pack interface to provide RTKDAB.dll call back functions 

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

#include "CProcessCallBacks.h"

#include <iostream>
#include <stdio.h>

CProcessCallBacks::CProcessCallBacks(std::string ServerIPAdress, int ServerPort)
{
	pMessagePackRPC_Client = new anyrpc::MessagePackTcpClient;

	pMessagePackRPC_Client->SetServer(ServerIPAdress.c_str(), ServerPort);
	pMessagePackRPC_Client->SetTimeout(50);
}


CProcessCallBacks::~CProcessCallBacks()
{
}

int CProcessCallBacks::MSCCallBack(char* Data, int Size, int a)
{
	anyrpc::Value params;
	anyrpc::Value result;
	bool success;

	params.SetArray();
	params[0].SetBinary((unsigned char*) Data, Size, true);
	params[1] = Size;
	params[2] = a;

	success = pMessagePackRPC_Client->Call("MSCData", params, result);

	return 0;
}

int CProcessCallBacks::StreamDataCallBack(void* ptr)
{
	return 0;
}

int CProcessCallBacks::PacketCallBack(void* ptr)
{
	return 0;
}

int CProcessCallBacks::MWFICCallBack(void* Data, int DataRate, int Size)
{
	return 0;
}

int CProcessCallBacks::FICCallBack(void* Data, int Size, int Mode)
{
	anyrpc::Value params;
	anyrpc::Value result;
	bool success;

	params.SetArray();
	params[0].SetBinary((unsigned char*)Data, Size, true);
	params[1] = Size;
	params[2] = Mode;

	success = pMessagePackRPC_Client->Call("FICData", params, result);

	return 0;
}
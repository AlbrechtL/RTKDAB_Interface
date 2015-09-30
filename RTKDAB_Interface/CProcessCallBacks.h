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

#pragma once

#include <string.h>

#include "CRTKDABCallBacks.h"
#include "anyrpc/include/anyrpc.h"

class CProcessCallBacks :
	public CRTKDABCallBacks
{
public:
	CProcessCallBacks(std::string ServerIPAdress, int ServerPort);
	~CProcessCallBacks();

	int MSCCallBack(char* Data, int Size, int a);
	int StreamDataCallBack(void* ptr);
	int PacketCallBack(void* ptr);
	int MWFICCallBack(void* Data, int DataRate, int Size);
	int FICCallBack(void* Data, int Size, int Mode);

private:
	anyrpc::Client* pMessagePackRPC_Client;
};


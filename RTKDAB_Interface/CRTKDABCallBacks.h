/*
CRTKDABCallBacks: This is an interface for the RTKDAB.dll call back functions. This is just a virtual class. You have to derive from it.

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
class CRTKDABCallBacks
{
public:
	CRTKDABCallBacks();
	virtual ~CRTKDABCallBacks();

	virtual int MSCCallBack(char* Data, int Size, int a) = 0;
	virtual int StreamDataCallBack(void* ptr) = 0;
	virtual int PacketCallBack(void* ptr) = 0;
	virtual int MWFICCallBack(void* Data, int DataRate, int Size) = 0;
	virtual int FICCallBack(void* Data, int Size, int Mode) = 0;
};


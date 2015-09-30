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

#pragma once

#include "CRTKDABLoader.h"

#include "anyrpc/include/anyrpc.h"
#include "anyrpc/include/method.h"

class CProcessFunctions
{
public:
	CProcessFunctions(int Port, CRTKDABLoader* RTKDABLoader);
	~CProcessFunctions();

private:
	anyrpc::Server *MessagePack_Server;
	anyrpc::MethodManager *MethodManager;
};

class CFunctionCallback : public anyrpc::Method
{
public:
	CFunctionCallback(std::string const& name, std::string const& help, bool deleteOnRemove, CRTKDABLoader* RTKDABLoader_);

	virtual void Execute(anyrpc::Value& params, anyrpc::Value& result) = 0;

protected:
	CRTKDABLoader* RTKDABLoader;
};

class CAddServiceCom : public CFunctionCallback
{
public:
	CAddServiceCom(std::string const& name, std::string const& help, bool deleteOnRemove, CRTKDABLoader* RTKDABLoader_) :CFunctionCallback(name, help, deleteOnRemove, RTKDABLoader_){};

	void Execute(anyrpc::Value& params, anyrpc::Value& result);
};

class CDelServiceCom : public CFunctionCallback
{
public:
	CDelServiceCom(std::string const& name, std::string const& help, bool deleteOnRemove, CRTKDABLoader* RTKDABLoader_) :CFunctionCallback(name, help, deleteOnRemove, RTKDABLoader_) {};

	void Execute(anyrpc::Value& params, anyrpc::Value& result);
};

class CSetFreq : public CFunctionCallback
{
public:
	CSetFreq(std::string const& name, std::string const& help, bool deleteOnRemove, CRTKDABLoader* RTKDABLoader_) :CFunctionCallback(name, help, deleteOnRemove, RTKDABLoader_) {};

	void Execute(anyrpc::Value& params, anyrpc::Value& result);
};
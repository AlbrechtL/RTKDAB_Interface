/*
* rtltcpaccess, a drop-in replacement for RTL283XACCESS.dll
* Original source code: https://github.com/steve-m/rtltcpaccess
*
* Copyright (c) 2013 Steve Markgraf <steve@steve-m.de>
* Copyright (c) 2015 Albrecht Lohofener <albrechtloh@gmx.de>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#define RTL283XACCESSDLL_API __declspec(dllexport) 

/* Function requried by RTKDAB.dll */
RTL283XACCESSDLL_API DWORD RTK_BDAFilterInit(HANDLE hnd);
RTL283XACCESSDLL_API DWORD RTK_BDAFilterRelease(HANDLE hnd);
RTL283XACCESSDLL_API DWORD RTK_Demod_Byte_Read(INT page, INT reg, INT len, PBYTE val);
RTL283XACCESSDLL_API DWORD RTK_Demod_Byte_Write(INT page, INT reg, INT len, PBYTE val);
RTL283XACCESSDLL_API DWORD RTK_DeviceUpdate(void);
RTL283XACCESSDLL_API DWORD RTK_GetData(LPBYTE data, DWORD bufsize, LPDWORD getlen, LPDWORD discardlen);
RTL283XACCESSDLL_API DWORD RTK_ReleaseDABEventHandle(HANDLE *handle);
RTL283XACCESSDLL_API DWORD RTK_Get_TunerType(LPDWORD tuner_type);
RTL283XACCESSDLL_API DWORD RTK_SetDABEventHandle(HANDLE *handle);
RTL283XACCESSDLL_API DWORD RTK_SYS_Byte_Read(WORD addr, INT len, PBYTE val);
RTL283XACCESSDLL_API DWORD RTK_SYS_Byte_Write(WORD addr, INT len, PBYTE val);
RTL283XACCESSDLL_API DWORD RTK_SetDABEventHandle(HANDLE *handle);
RTL283XACCESSDLL_API DWORD RTK_Set_Bandwidth(DWORD bw);
RTL283XACCESSDLL_API DWORD RTK_Set_Frequency(DWORD freq);

/* Options for this dll */
RTL283XACCESSDLL_API int SetIPAddressAndPort(char* IPAddress, uint32_t Port);
RTL283XACCESSDLL_API int GetConnectionState(void);
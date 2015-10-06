RTKDAB_Interface
===================
This is an interface for the Realtek "RTKDAB.dll". It provides the DLL functiona via a [MessagePack](http://msgpack.org/) TCP API.

Description
-----------
"RTKDAB.dll" is a SDR library which demodulates a DAB signal from raw ADC samples. It works much better with weak signals compared to [SDR-J](http://www.sdr-j.tk/index.html) or [dab2eti](https://github.com/linuxstb/dabtools).
To goal is to use this library together with open source DAB software and [RTL2832U](http://sdr.osmocom.org/trac/wiki/rtl-sdr) dongles. Since it is a binary MS Windows DLL a interface is necessary which also runs in [wine](https://www.winehq.org/).

**Why is "RTKDAB.dll" better?**

Maybe because it is based on the ["Fraunhofer DAB/DRM MultimediaPlayer"](http://www.iis.fraunhofer.de/en/ff/amm/prod/digirundfunk/digirundf/dabdrmmplayer.html) where a lot of Fraunhofer IIS engineers and researches work on this library.

**Where do you know the "RTKDAB.dll" API from?**

I know it from reverse engineering. I didn't had access to the Realtek SDK or to non-public Fraunhofer IIS documentation.

Usage
-----
"RTKDAB_Interface" uses the program "rtl_tcp" to read data from the RTL2832U dongles. You have to install "rtl_tcp" first and to start it. For Ubuntu you can do:

    # sudo apt-get install rtl-sdr
    # rtl_tcp

**How-to obtain "RTKDAB.dll"**

Because of license problems it is not possible to provide "RTKDAB.dll". But it is included in the program "NOXON DAB MediaPlayer".
- Download "NOXON DAB MediaPlayer" http://ftp.noxonradio.de/NOXON/NOXON_DAB_Stick/Updates/NOXON_DAB_Stick_DAB_MediaPlayer_Setup_4.1.0.exe
- Install it (also working in wine)
- Navigate to the folder e.g."C:\Program Files\NOXON Media\NOXON DAB MediaPlayer"
- Copy "RTKDAB.dll" and place it where "RTKDAB_Interface.exe" is located

Now you can run "RTKDAB_Interface.exe"

**How-to run "RTKDAB_Interface.exe" in wine**
- Basically the same like MS Windows
- Make sure that you have the Microsoft Visual C++ Redistributable Package 2012 installed. For the installation see [here](https://appdb.winehq.org/objectManager.php?sClass=application&iId=5766)
- Tested with wine 1.7.50 and Ubuntu 14.04

MessagePack TCP API
-------------------
RTKDAB_Interface has two MessagePack TCP interfaces. A MessagePack client to transmit the FIC and MSC data ("RTKDAB.dll" callback) and a MessagePack server to provide the "RTKDAB.dll" API. 

**MessagePack client methods**

"RTKDAB_Interface" will connect to a MessagePack TCP server and call the following methods.

Method | Parameters | Return | Description
------ | ---------- | ------ | -----------
MSCData | bin DataArray, int MSC data size, int SCID | None | Transmits the MSC data to a given sub-channel
FICData | bin DataArray, int FIC data size, int Mode | None | Transmits the FIC data to a given channel
StreamData | N/A | N/A | Not implemented
PacketData | N/A | N/A | Not implemented
MWFICData | N/A | N/A | Not implemented

**MessagePack server methods**

"RTKDAB_Interface" provides the following methods. A MessagePack TCP client can call it.

Method | Parameters | Return | Description
------ | ---------- | ------ | -----------
AddServiceCom | int ParaMode, int ID, int StartCU, int U_E, int Index, int EEPIdx, int CUNum, int PacketAddr, int FEC  | None | Adda a service componente
DelServiceCom | int ParaMode, int ID, int PacketAddr | None | Deletes a service componente
SetFreq | int Frequency in kHz | None | Sets the tuner to a mid frequeny
OpenDevice | N/A | N/A | Not implemented
CloseDevice | N/A | N/A | Not implemented
Start | N/A | N/A | Not implemented
Stop | N/A | N/A | Not implemented
ChangeSCOrg | N/A | N/A | Not implemented
GetFreqAndBW | N/A | N/A | Not implemented
GetSignalQuality | N/A | N/A | Not implemented
GetSignalLock | N/A | N/A | Not implemented
GetSignalPresent | N/A | N/A | Not implemented
GetSignalStrength | N/A | N/A | Not implemented

Building
-----------
- Microsoft Visual Studio Community 2015 with platform toolset Visual Studio 2012

Dependencys
-----------  
- AnyRPC: https://github.com/sgieseking/anyrpc

**Forked into this repository**
- rtltcpaccess: https://github.com/steve-m/rtltcpaccess

References
--------------
- DAB Specification: https://www.worlddab.org/technology-rollout/standards/technical-specifications-list
  - EN 300 401 "Radio Broadcasting Systems; Digital Audio Broadcasting (DAB) to mobile, portable and fixed receivers"
  - TS 102 563 "Digital Audio Broadcasting (DAB); Transport of Advanced Audio Coding (AAC) audio"

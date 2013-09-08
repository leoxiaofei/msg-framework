// MSG Framework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MsgFramework.h"
#include "MsgService.h"
#include "udpmonitor.h"

int MsgFrameMain( int argc, _TCHAR* argv[] )
{
	MsgService service;

	service.GetUdp()->SendTo(10, "abcdefghijklmn", 15, "127.0.0.1");
	service.Wait();
	return 0;
}
// msgassist.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "msgassist.h"
#include "msgtrace.h"
#include <winuser.h>
#include "global.h"
#include <stdio.h>


// This is the constructor of a class that has been exported.
// see msgassist.h for the class definition
MsgAssist::MsgAssist()
{

}

MsgAssist::~MsgAssist()
{

}

LRESULT WINAPI MessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(MSGASSIST::hHook, nCode, wParam, lParam);
}

bool MsgAssist::SetHook()
{
	MSGASSIST::hHook = SetWindowsHookEx(/*WH_GETMESSAGE*/
		WH_KEYBOARD, MessageProc, MSGASSIST::hInstDll, 0);
	return true;
}

bool MsgAssist::UnHook()
{
	UnhookWindowsHookEx(MSGASSIST::hHook);
	return true;

}

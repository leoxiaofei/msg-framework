#include "stdafx.h"
#include "global.h"


namespace MSGASSIST
{
	HINSTANCE hInstDll = NULL;

#pragma data_seg("Shared")

	HHOOK		hHook;

#pragma data_seg()
}

#pragma comment(linker,"/SECTION:Shared,RWS")

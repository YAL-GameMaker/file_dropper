// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

void file_dropper_preinit();
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		file_dropper_preinit();
	}
	return TRUE;
}


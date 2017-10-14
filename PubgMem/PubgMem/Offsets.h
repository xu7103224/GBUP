#pragma once
#include <iostream>
#include <windows.h>
#define TARGETPROC  L"tslgame.exe"
#define PROCESSNAME L"TslGame.exe"
namespace PUBG
{
	struct COffsets
	{
		DWORD_PTR tlsGameBase = 0;

		DWORD_PTR pUWorld = 0;
		DWORD_PTR pGameInstance = 0;
		DWORD_PTR pLocalPlayerArray = 0;
		DWORD_PTR pLocalPlayer = 0;
		DWORD_PTR pViewportClient = 0;
	};
	extern COffsets offsets;
	void initOffsets(COffsets &Of = offsets);
	
}
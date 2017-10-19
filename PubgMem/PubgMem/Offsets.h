#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <list>
#define TARGETPROC  L"tslgame.exe"
#define PROCESSNAME L"TslGame.exe"
struct FCameraCacheEntry;
// pUWorld  48 8B 1D ? ? ? ? 74 40
#define PUWORLD_OFFSETS 0x37E4918

// NamePrt  48 8B 3D ? ? ? ? 48 85 FF 75 38
#define NAME_OFFSETS 0x36E7710
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

	struct CGlobalObjs
	{
		CGlobalObjs();
		~CGlobalObjs();
		void update();

		FCameraCacheEntry *cameracache;
		int screenWidth;
		int screenHeight;
		RECT screenrc;
	};

	extern COffsets offsets;

	extern int ActorIds[4];
	extern int uaz[3];
	extern int dacia[4];
	extern int motorbike[5];
	extern int buggy[3];
	extern int boat;
	extern int itemtype[2];
	extern std::vector<std::string> playerNames;
	extern std::vector<std::string> uazNames;
	extern std::vector<std::string> buggyNames;
	extern std::vector<std::string> daciaNames;
	extern std::vector<std::string> bikeNames;
	extern std::vector<std::string> boatName;
	extern std::vector<std::string> ItemName_;
	extern std::list<int> upper_part;
	extern std::list<int> right_arm;
	extern std::list<int> left_arm;
	extern std::list<int> spine;
	extern std::list<int> lower_right;
	extern std::list<int> lower_left;
	extern std::list<std::list<int>> skeleton;
	extern CGlobalObjs g_global;
	void initOffsets(COffsets &Of = offsets);
	
}
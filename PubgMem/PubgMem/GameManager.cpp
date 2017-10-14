#include "GameManager.h"
#include <iostream>
#include <tchar.h>
#include "PUBG_Engine_classes.h"
#define GAMEWINDOW "UnrealWindow"
namespace PUBG
{
	HANDLE TragetHandle{ 0 };
	pubgCon* pubgCon::m_instance = NULL;

	pubgCon::pubgCon() 
		: status(STATUS_SUCCESS)
		, BaseAddress(0)
	{
		my_atomic.store(FALSE);

#ifdef _DEBUG
		GameWindow = FindWindowA(GAMEWINDOW,NULL);
		if (GameWindow == 0) std::cout << "窗口没找到！\n";
#endif
		ZeroMemory(&uWorld, sizeof(UWorld));
	}

	pubgCon::~pubgCon()
	{
		delete pubgCon::instance();
	}

	pubgCon * pubgCon::instance()
	{
		if (NULL == m_instance)
		{
			m_instance = new(std::nothrow) pubgCon;
			if (!m_instance)
				return NULL;

		}
		return m_instance;
	}

	// 48 8B 1D ? ? ? ? 74 40
	VOID  pubgCon::RefreshOffsets()
	{
#ifdef _DEBUG
		std::cout << "查找相应模块\n";
#endif
		BaseAddress = proc.module().GetModule(TARGETPROC)->baseAddress;
		offsets.tlsGameBase = proc.module().GetModule(TARGETPROC)->baseAddress;
		proc.memory().Read<DWORD_PTR>(offsets.tlsGameBase + 0x37D7818, offsets.pUWorld);
		proc.memory().Read<DWORD_PTR>(offsets.pUWorld + 0x140, offsets.pGameInstance);
		proc.memory().Read<DWORD_PTR>(offsets.pGameInstance + 0x38, offsets.pLocalPlayerArray);
		std::cout << "tlsGameBase = " << std::hex << offsets.tlsGameBase << "\n pUWorld = " << std::hex << offsets.pUWorld \
			      << "\n pGameInstance = " << std::hex << offsets.pGameInstance << "\n pLocalPlayerArray = " << offsets.pLocalPlayerArray \
			      << std::endl;
		
	}

	UWorld * pubgCon::pUWorld()
	{
		DWORD_PTR pworldAdd{ 0 };
		proc.memory().Read<DWORD_PTR>(BaseAddress + 0x37D7818, pworldAdd);
		proc.memory().Read<UWorld>(pworldAdd, uWorld);
		return &uWorld;
	}

	ULocalPlayer * pubgCon::pLocalPlayer()
	{
		UGameInstance temp;
		proc.memory().Read<UGameInstance>(reinterpret_cast<DWORD_PTR>(pUWorld()->OwningGameInstance), temp);
		if (temp.LocalPlayers.Data) {
			DWORD_PTR pLocalPlayer{ 0 };
			proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(temp.LocalPlayers.Data), pLocalPlayer);
			proc.memory().Read<ULocalPlayer>(pLocalPlayer, LocalPlayer);
			return &LocalPlayer;
		}
		return nullptr;
	}

	DWORD pubgCon::GetPlayerCount()
	{
		std::lock_guard<std::mutex> l(mymutex);
		UGameViewportClient ViewportClient;
		UWorld world;
		ULevel ulevel;
		proc.memory().Read<UGameViewportClient>(reinterpret_cast<DWORD_PTR>(pLocalPlayer()->ViewportClient), ViewportClient);
		proc.memory().Read<UWorld>(reinterpret_cast<DWORD_PTR>(ViewportClient.World), world);
		proc.memory().Read<ULevel>(reinterpret_cast<DWORD_PTR>(world.PersistentLevel), ulevel);
		
		int PlayerCounts(0);   //玩家数
		int EntitiesCount(0);  //实体数
		int VehiclesCount(0);  //车辆数
		for (int i(0); i < ulevel.AActors.Count; i++) {
			DWORD_PTR Addres;
			AActor Actor;
			proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(ulevel.AActors.Data) + i * 8, Addres);
			proc.memory().Read<AActor>(Addres, Actor);
			if (Actor.BasePointer == 0)
				continue;
			EntitiesCount++;

			//
			//获取obj名字
			//
			std::string &name = GetActorNameById(Actor.Id2);
			std::cout << "obj name = " << name << std::endl;
			if (Actor.IsPlayer(name))
				PlayerCounts++;
		}
		std::cout << "Players counts =" << PlayerCounts << std::endl;
		return ulevel.AActors.Count;
	}


	std::string pubgCon::GetActorNameById(int ID)
	{
		DWORD_PTR fName;
		char name[64] = { NULL };

		proc.memory().Read<DWORD_PTR>(BaseAddress + 0x36DA610, fName);
		proc.memory().Read<DWORD_PTR>(fName + int(ID / 0x4000) * 8, fName);
		proc.memory().Read<DWORD_PTR>(fName + 8 * int(ID % 0x4000), fName);
		if (ReadProcessMemory(proc.core().handle(), (LPVOID)(fName + 16), name, sizeof(name) - 2, NULL) != 0)
			return std::string(name);
		return std::string("NULL");
	}


	const char * pubgCon::GetActorName(PVOID pActor)
	{
		//48 8B 3D ? ? ? ? 48 85 FF 75 38
		DWORD_PTR GNameAdd = BaseAddress + 0x36DA610;
		DWORD ID{ 0 };
		proc.memory().Read<DWORD>(GNameAdd, ID);
		UINT64 fNamePtr = (GNameAdd + (ID / 0x4000) * 8);

		return nullptr;
	}


	VOID pubgCon::InitObj()
	{
		std::lock_guard<std::mutex> l(mymutex);
		status = proc.Attach(TragetHandle);
		if (NT_SUCCESS(status))
		{
			try
			{
				RefreshOffsets();
				my_atomic.store(TRUE);
			}
			catch (...){
				my_atomic.store(FALSE);
			}
		}
	}


	VOID pubgCon::MainLoop()
	{
		while (!my_atomic.load())
		{
			InitObj();
			Sleep(500);
		}
		std::cout << "success!" << std::endl;
		do
		{
			GetPlayerCount();
			Sleep(2000);
		} while (true);
	}
}
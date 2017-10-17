#pragma once
#include "Process.h"
#include "PUBG_Engine_classes.h"
#include "Offsets.h"
#include <exception>
#include <future>
#include <atomic>
#include <mutex>
#include <unordered_set>
#include <vector>
#include <list>
namespace PUBG
{
	enum ActorType {
		Player,
		Vehicle,
		Item
	};
	enum VehicleType {
		UAZ,       //吉普
		DACIA,     //轿车
		MOTORBIKE, //摩托
		BUGGY,     //越野赛车
		BOAT,      //船
		NONVehic   //非载具
	};

	struct ActorList {
		std::vector<DWORD_PTR> Players;
		std::vector<std::vector<DWORD_PTR>> Vehicles;
		std::vector<DWORD_PTR> Items;
	};

	extern HANDLE TragetHandle;
	class pubgCon
	{
	public:
		~pubgCon();
		static pubgCon *instance();

		VOID    MainLoop();
		VOID    InitObj();
		VOID    RefreshOffsets();

	public:
		UWorld          *pUWorld();
		//ULevel          *pPlayList(); =  GetPersistentLevel()
		ULocalPlayer    *pLocalPlayer(); 
		ActorList       *pAllActorsList();
		DWORD           GetPlayerCount();
		DWORD           GetEntitiesCount();
		Vector3D		GetActorPos(DWORD_PTR pactor);
		std::string		GetActorNameById(int ID);


	private:
		Process           proc;
		HWND              GameWindow;  //.窗口句柄
		NTSTATUS          status;
		std::atomic<bool> my_atomic;
		std::mutex        mymutex;

    /// 游戏相关
	private:
		DWORD_PTR     BaseAddress;
		UWorld        uWorld;
		ULocalPlayer  LocalPlayer;
		ActorList     AllActors;

		VOID         CacheNames();
		BOOL         IsPlayerActor(AActor* ptr);
		ULevel       GetPersistentLevel();
		VehicleType  IsVehicleActor(AActor* ptr);
		AActor       GetActorbyIndex(DWORD i, ULevel& ulevel);
		DWORD_PTR    GetActorPtrbyIndex(DWORD i, ULevel& ulevel);

		std::unordered_set<AActor*> GetPlayerList();
		
	private:
		pubgCon();
		static pubgCon* m_instance;
	};
}
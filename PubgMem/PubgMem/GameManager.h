#pragma once
#include "Process.h"
#include "PUBG_Engine_classes.h"
#include "Offsets.h"
#include <exception>
#include <future>
#include <atomic>
#include <mutex>
#include <unordered_set>
#include <list>
namespace PUBG
{
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

		BOOL       IsPlayerActor(AActor* ptr);
		ULevel     GetPersistentLevel();
		AActor     GetActorbyIndex(DWORD i, ULevel& ulevel);
		DWORD_PTR  GetActorPtrbyIndex(DWORD i, ULevel& ulevel);

		std::unordered_set<AActor*> GetPlayerList();
		std::unordered_set<AActor*> GetEntitiesList();  // 未完成
	private:
		pubgCon();
		static pubgCon* m_instance;
	};
}
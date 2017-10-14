#pragma once
#include "Process.h"
#include "PUBG_Engine_classes.h"
#include "Offsets.h"
#include <exception>
#include <future>
#include <atomic>
#include <mutex>
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
		ULocalPlayer    *pLocalPlayer();
		DWORD           GetPlayerCount();
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
	private:
		pubgCon();
		static pubgCon* m_instance;
	};
}
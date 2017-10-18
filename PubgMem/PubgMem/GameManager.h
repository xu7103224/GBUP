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
#include <windows.h>


typedef BOOL ( __stdcall *_EnumActorCallback)(AActor &actor, DWORD_PTR actoraddr, void *parameter);

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
		UWorld				*pUWorld();
		//ULevel			  *pPlayList(); =  GetPersistentLevel()
		ULocalPlayer    	*pLocalPlayer(); 
		ActorList       	*pAllActorsList();
		DWORD				GetPlayerCount();
		DWORD				GetEntitiesCount();
		Vector3D			GetActorPos(DWORD_PTR pactor);
		std::string			GetActorNameById(int ID);
		BOOL				EnumActor(_EnumActorCallback cb, void *parameter);	//当cb返回true时终止遍历，否则遍历所有actor之后返回false
		void				EnumPlayComponent();//测试用
		FTransform			GetBoneIndex(DWORD_PTR mesh, int index);
		Vector3D			GetBoneWithRotation(DWORD_PTR mesh, int id);
		FCameraCacheEntry	GetCameraCache();
		Vector3D			WorldToScreen(Vector3D & WorldLocation, FCameraCacheEntry & CameraCacheL);
		std::vector<D3DXLine> &GetLine(DWORD_PTR mesh, std::vector<D3DXLine>& vl);//获取一组骨架线
		void				printPlayLine();
		void				UpdatePlayersSkeleton();				//更新所有玩家的骨骼
		void				CopyPlayersSkeleton(std::vector<D3DXLine> &v);
		//测试用
		



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
		BOOL       IsPlayerActor(AActor* ptr);
		ULevel     GetPersistentLevel();
		VehicleType  IsVehicleActor(AActor* ptr);
		AActor     GetActorbyIndex(DWORD i, ULevel& ulevel);
		DWORD_PTR  GetActorPtrbyIndex(DWORD i, ULevel& ulevel);


		std::unordered_set<AActor*> GetPlayerList();

		//所有玩家骨骼线
		std::vector<D3DXLine>		PlayersSkeleton;
		std::mutex					PlayersSkeletonLock;
		
	private:
		pubgCon();
		static pubgCon* m_instance;

	};
}
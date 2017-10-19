#pragma once
#include "Process.h"
#include "PUBG_Engine_classes.h"
#include "Offsets.h"
#include "Overlay.h"
#include <exception>
#include <future>
#include <atomic>
#include <mutex>
#include <unordered_map>
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
		void				EnumAllObj();	
		FTransform			GetBoneIndex(DWORD_PTR mesh, int index);
		Vector3D			GetBoneWithRotation(DWORD_PTR mesh, int id);
		FCameraCacheEntry	GetCameraCache();	//获取摄像头
		Vector3D			WorldToScreen(Vector3D & WorldLocation, FCameraCacheEntry & CameraCacheL);
		//void				UpdatePlayersSkeleton();										    //更新所有玩家的骨骼
		std::vector<D3DXLine> &GetSkeletons(DWORD_PTR mesh, std::vector<D3DXLine>& vl);			//获取一组骨架线

		void				OnPlayer(ACharacter &player);                      //所有关于玩家的操作在这里
		void				OnVehicle(DWORD_PTR vehicleaddr, VehicleType type);//所有关于载具的操作在这里
		void                OnItem(DWORD_PTR actorPtr);                        //所有物品生成点的操作在这里
		



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

		BOOL			EnumActor(_EnumActorCallback cb, void *parameter);	//当cb返回true时终止遍历，否则遍历所有actor之后返回false
		VOID			CacheNames();
		BOOL			IsPlayerActor(AActor* ptr);
		BOOL			IsPlayerActor(AActor &actor);
		BOOL            IsDroppedItemGroup(AActor* ptr);
		BOOL            IsDroppedItemGroup(AActor &actor);
		ULevel			GetPersistentLevel();
		VehicleType		IsVehicleActor(AActor* ptr);
		VehicleType		IsVehicleActor(AActor &actor);
		AActor			GetActorbyIndex(DWORD i, ULevel& ulevel);
		DWORD_PTR		GetActorPtrbyIndex(DWORD i, ULevel& ulevel);

		std::unordered_set<AActor*> GetPlayerList();

		//所有玩家骨骼线
		std::vector<D3DXLine>		PlayersSkeleton;

		//可探测物品点
		std::vector<DroppedItemKey> ItemListD;

		//可探测玩家数量
		int PlayerCounts;
		
	private:
		pubgCon();
		static pubgCon* m_instance;

	};
}
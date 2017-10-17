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


typedef BOOL ( __stdcall *_EnumActorCallback)(AActor &actor, void *parameter);

namespace PUBG
{
	enum ActorType {
		Player,
		Vehicle,
		Item
	};
	enum VehicleType {
		UAZ,       //����
		DACIA,     //�γ�
		MOTORBIKE, //Ħ��
		BUGGY,     //ԽҰ����
		BOAT,      //��
		NONVehic   //���ؾ�
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
		BOOL				EnumActor(_EnumActorCallback cb, void *parameter);					//��cb����trueʱ��ֹ�����������������actor֮�󷵻�false
		void				EnumPlayComponent();
		FTransform			GetBoneIndex(DWORD_PTR mesh, int index);
		Vector3D			GetBoneWithRotation(DWORD_PTR mesh, int id);
		FCameraCacheEntry	GetCameraCache();
		void				DrawSkeleton(DWORD_PTR mesh);//��ʱ����



	private:
		Process           proc;
		HWND              GameWindow;  //.���ھ��
		NTSTATUS          status;
		std::atomic<bool> my_atomic;
		std::mutex        mymutex;

    /// ��Ϸ���
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
	private:
		pubgCon();
		static pubgCon* m_instance;

	};
}
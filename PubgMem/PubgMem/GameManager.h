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
		void				EnumAllObj();	
		FTransform			GetBoneIndex(DWORD_PTR mesh, int index);
		Vector3D			GetBoneWithRotation(DWORD_PTR mesh, int id);
		FCameraCacheEntry	GetCameraCache();	//��ȡ����ͷ
		Vector3D			WorldToScreen(Vector3D & WorldLocation, FCameraCacheEntry & CameraCacheL);
		//void				UpdatePlayersSkeleton();										    //����������ҵĹ���
		std::vector<D3DXLine> &GetSkeletons(DWORD_PTR mesh, std::vector<D3DXLine>& vl);			//��ȡһ��Ǽ���

		void				OnPlayer(ACharacter &player);                      //���й�����ҵĲ���������
		void				OnVehicle(DWORD_PTR vehicleaddr, VehicleType type);//���й����ؾߵĲ���������
		void                OnItem(DWORD_PTR actorPtr);                        //������Ʒ���ɵ�Ĳ���������
		



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

		BOOL			EnumActor(_EnumActorCallback cb, void *parameter);	//��cb����trueʱ��ֹ�����������������actor֮�󷵻�false
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

		//������ҹ�����
		std::vector<D3DXLine>		PlayersSkeleton;

		//��̽����Ʒ��
		std::vector<DroppedItemKey> ItemListD;

		//��̽���������
		int PlayerCounts;
		
	private:
		pubgCon();
		static pubgCon* m_instance;

	};
}
#include "GameManager.h"
#include <iostream>
#include <tchar.h>
#include "PUBG_Engine_classes.h"
#include "PUBG_Engine_structs.h"
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
		{
			AllActors.Vehicles.push_back(std::vector<DWORD_PTR>()); // UAZ
			AllActors.Vehicles.push_back(std::vector<DWORD_PTR>()); // DACIA
			AllActors.Vehicles.push_back(std::vector<DWORD_PTR>()); // MOTORBIKE
			AllActors.Vehicles.push_back(std::vector<DWORD_PTR>()); // BUGGY
			AllActors.Vehicles.push_back(std::vector<DWORD_PTR>()); // BOAT
		}
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
		proc.memory().Read<DWORD_PTR>(offsets.tlsGameBase + PUWORLD_OFFSETS, offsets.pUWorld);
		proc.memory().Read<DWORD_PTR>(offsets.pUWorld + 0x140, offsets.pGameInstance);
		proc.memory().Read<DWORD_PTR>(offsets.pGameInstance + 0x38, offsets.pLocalPlayerArray);
		std::cout << "tlsGameBase = " << std::hex << offsets.tlsGameBase << "\n pUWorld = " << std::hex << offsets.pUWorld \
			      << "\n pGameInstance = " << std::hex << offsets.pGameInstance << "\n pLocalPlayerArray = " << offsets.pLocalPlayerArray \
			      << std::endl;
		
		
	}

	UWorld * pubgCon::pUWorld()
	{
		DWORD_PTR pworldAdd{ 0 };
		proc.memory().Read<DWORD_PTR>(BaseAddress + PUWORLD_OFFSETS, pworldAdd);
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
		ULevel ulevel = GetPersistentLevel();
		int PlayerCounts(0);   //玩家数
		for (int i(0); i < ulevel.AActors.Count; i++) {
			DWORD_PTR Addres;
			AActor Actor;
			proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(ulevel.AActors.Data) + i * 8, Addres);
			proc.memory().Read<AActor>(Addres, Actor);

			//
			//获取obj名字
			//
			std::string name = GetActorNameById(Actor.Name.ComparisonIndex);
			// auto pos = GetActorPos(Addres);
			// std::cout << "obj name = " << name \
			//	<< ", x = " << std::to_string(pos.x)\
			//	<< ", y = " << std::to_string(pos.y)\
			//	<< ", z = " << std::to_string(pos.z)\
			//	<< std::endl;

			if (Actor.IsPlayer(name)) {
				++PlayerCounts;
			}
				
		}
		std::cout << "Players counts =" << PlayerCounts << std::endl;
		return ulevel.AActors.Count;
	}

	DWORD pubgCon::GetEntitiesCount()
	{
		ULevel ulevel = GetPersistentLevel();
		return ulevel.AActors.Count;
	}
	VOID pubgCon::CacheNames()
	{
		std::string name = "";
		for (int i(0), c1(0), c2(0), c3(0), c4(0), c5(0), c6(0); i < 200000; i++)
		{
			if (c1 == 4 && c2 == 3 && c3 == 4 && c4 == 5 && c5 == 3 && boat != 0 && c6 == 2)
			{
				std::cout << "IDs retrieved" << std::endl;
				return;
			}
			name = GetActorNameById(i);
			if (name == playerNames.at(0).c_str() || name == playerNames.at(1).c_str() || name == playerNames.at(2).c_str() || name == playerNames.at(3).c_str())
			{
				std::cout << name << " " << i << std::endl;
				ActorIds[c1++] = i;
			}
			if (name == uazNames.at(0).c_str() || name == uazNames.at(1).c_str() || name == uazNames.at(2).c_str())
			{
				uaz[c2++] = i;
				std::cout << name << " " << i << std::endl;
			}
			if (name == daciaNames.at(0).c_str() || name == daciaNames.at(1).c_str() || name == daciaNames.at(2).c_str() || name == daciaNames.at(3).c_str())
			{
				dacia[c3++] = i;
				std::cout << name << " " << i << std::endl;
			}
			if (name == bikeNames.at(0).c_str() || name == bikeNames.at(1).c_str() || name == bikeNames.at(2).c_str() || name == bikeNames.at(3).c_str() || name == bikeNames.at(4).c_str())
			{
				std::cout << name << " " << i << std::endl;
				motorbike[c4++] = i;
			}
			if (name == buggyNames.at(0).c_str() || name == buggyNames.at(1).c_str() || name == buggyNames.at(2).c_str())
			{
				std::cout << name << " " << i << std::endl;
				buggy[c5++] = i;
			}
			if (name == boatName.at(0).c_str())
			{
				std::cout << name << " " << i << std::endl;
				boat = i;
			}
			if (name == ItemName_[0] || name == ItemName_[1])
			{
				std::cout << name << " " << i << std::endl;
				itemtype[c6++] = i;
			}
		}
		return VOID();
	}

	Vector3D pubgCon::GetActorPos(DWORD_PTR pactor)
	{
		Vector3D pos;
		DWORD_PTR RootComponent;
		proc.memory().Read<DWORD_PTR>(pactor + FIELD_OFFSET(AActor, RootComponent)/*0x180*/, RootComponent);
		proc.memory().Read<Vector3D>((DWORD_PTR)RootComponent + FIELD_OFFSET(USceneComponent,UnknownData04)/*0x174*/, pos);
		return pos;
	}

	ULevel pubgCon::GetPersistentLevel()
	{
		UGameViewportClient ViewportClient;
		UWorld world;
		ULevel ulevel;
		proc.memory().Read<UGameViewportClient>(reinterpret_cast<DWORD_PTR>(pLocalPlayer()->ViewportClient), ViewportClient);
		proc.memory().Read<UWorld>(reinterpret_cast<DWORD_PTR>(ViewportClient.World), world);
		proc.memory().Read<ULevel>(reinterpret_cast<DWORD_PTR>(world.PersistentLevel), ulevel);
		return ulevel;
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

	BOOL pubgCon::EnumActor(_EnumActorCallback cb, void *parameter)
	{
		ULevel ulevel = GetPersistentLevel();
		for (int i(0); i < ulevel.AActors.Count; i++) {
			DWORD_PTR Addres;
			AActor Actor;
			proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(ulevel.AActors.Data) + i * 8, Addres);
			proc.memory().Read<AActor>(Addres, Actor);
			if (cb(Actor, Addres, parameter)) {
				return TRUE;
			}
		}

		return FALSE;
	}

	void pubgCon::EnumPlayComponent()
	{
		void *param( reinterpret_cast<void *>(this));
		EnumActor([](AActor& actor, DWORD_PTR addr, void *parameter)->BOOL {
			pubgCon* _this = reinterpret_cast<pubgCon *>(parameter);
			USceneComponent comp;

			std::string name = _this->GetActorNameById(actor.Name.ComparisonIndex);
			if (actor.IsPlayer(name)) {
				_this->proc.memory().Read<USceneComponent>(reinterpret_cast<DWORD_PTR>(actor.RootComponent), comp);
				int tier = 0;
				std::function<void(USceneComponent& comp, int tier)> fn;

				fn = [&](USceneComponent& comp, int tier) {

					std::cout << "tier = " << tier << ", name = " << _this->GetActorNameById(comp.Name.ComparisonIndex) << std::endl;
					if (comp.AttachParent) {
						for (int i(0); i < comp.AttachChildren.Count; ++i) {
							USceneComponent sub;
							DWORD_PTR Addres;
							_this->proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(comp.AttachChildren.Data) + i * 8, Addres);
							_this->proc.memory().Read<USceneComponent>(Addres, sub);
							fn(sub, tier + 1);
						}
					}
				};
				fn(comp, tier);

			}
			return FALSE;
		}, param);
	}

	BOOL pubgCon::IsPlayerActor(AActor * ptr)
	{
		AActor temp;
		proc.memory().Read<AActor>(reinterpret_cast<DWORD_PTR>(ptr), temp);
		for (int i(0); i < 4; i++) {
			if (ActorIds[i] == temp.Name.ComparisonIndex)
				return TRUE;
		}
		return FALSE;
	}
	VehicleType pubgCon::IsVehicleActor(AActor * ptr)
	{
		AActor temp;
		proc.memory().Read<AActor>(reinterpret_cast<DWORD_PTR>(ptr), temp);
		for (int i(0); i < 3; i++) {//UAZ
			if (uaz[i] == temp.Name.ComparisonIndex)
				return UAZ;
		}
		for (int i(0); i < 4; i++) { //DACIA
			if (dacia[i] == temp.Name.ComparisonIndex)
				return DACIA;
		}
		for (int i(0); i < 5; i++) { //MOTORBIKE
			if (motorbike[i] == temp.Name.ComparisonIndex)
				return MOTORBIKE;
		}
		for (int i(0); i < 3; i++) { //BUGGY
			if (motorbike[i] == temp.Name.ComparisonIndex)
				return BUGGY;
		}
		if (boat == temp.Name.ComparisonIndex)
			return BOAT;
		else
			return NONVehic;
	}
	
	AActor pubgCon::GetActorbyIndex(DWORD i, ULevel& ulevel)
	{
		AActor Actor;
		DWORD_PTR Addres;
		proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(ulevel.AActors.Data) + i * 8, Addres);
		proc.memory().Read<AActor>(Addres, Actor);
		return Actor;
	}

	DWORD_PTR pubgCon::GetActorPtrbyIndex(DWORD i, ULevel& ulevel)
	{
		DWORD_PTR Addres{ 0 };
		proc.memory().Read<DWORD_PTR>(reinterpret_cast<DWORD_PTR>(ulevel.AActors.Data) + i * 8, Addres);
		return Addres;
	}

	std::unordered_set<AActor*> pubgCon::GetPlayerList()
	{
		std::unordered_set<AActor*> res;
		ULevel ulevel = GetPersistentLevel();
		for (int i(0); i < ulevel.AActors.Count; i++) {
			DWORD_PTR ActorPtr(GetActorPtrbyIndex(i, ulevel));
			if (IsPlayerActor(reinterpret_cast<AActor*>(ActorPtr)))
				res.insert(reinterpret_cast<AActor*>(ActorPtr));
		}
		return res;
	}

	ActorList * pubgCon::pAllActorsList()
	{
		std::lock_guard<std::mutex> l(mymutex);
		AllActors.Players.clear();
		AllActors.Items.clear();
		if (AllActors.Vehicles.size() == 5)
			for (int i(0); i < 5; i++)
				AllActors.Vehicles.at(i).clear();
		else {
			std::cout << "Vehicles counts is invaild!" << std::endl;
			return nullptr;
		}
		VehicleType vehicletype_{ NONVehic };
		std::unordered_set<AActor*> res;
		ULevel ulevel = GetPersistentLevel();
		for (int i(0); i < ulevel.AActors.Count; i++) {
			DWORD_PTR ActorPtr(GetActorPtrbyIndex(i, ulevel));
			if (IsPlayerActor(reinterpret_cast<AActor*>(ActorPtr))) {
				AllActors.Players.push_back(ActorPtr);
				continue;
			}

			if ((vehicletype_ = IsVehicleActor(reinterpret_cast<AActor*>(ActorPtr))) != NONVehic) {
				AllActors.Vehicles.at(vehicletype_).push_back(ActorPtr);
				continue;
			}
			else
				AllActors.Items.push_back(ActorPtr);
		}
		return &AllActors;
	}

	// xuq add begin
	FCameraCacheEntry pubgCon::GetCameraCache()
	{
		FCameraCacheEntry cce;
		DWORD_PTR lp = reinterpret_cast<DWORD_PTR>(pLocalPlayer());
		DWORD_PTR temp;
		proc.memory().Read<DWORD_PTR>(lp + FIELD_OFFSET(ULocalPlayer,PlayerController)/*0x30*/, temp);
		proc.memory().Read<DWORD_PTR>(temp + FIELD_OFFSET(APlayerController, PlayerCameraManager)/*0x438*/, temp);
		proc.memory().Read<FCameraCacheEntry>(temp + FIELD_OFFSET(APlayerCameraManager, CameraCache)/*0x410*/, cce);
		return cce;
	}

	FTransform pubgCon::GetBoneIndex(DWORD_PTR mesh, int index)
	{
		DWORD_PTR bonearray;
		proc.memory().Read<DWORD_PTR>(mesh + 0x790, bonearray);
		FTransform tf;
		proc.memory().Read<FTransform>(bonearray + (index * 0x30), tf);
		return tf;
	}

	Vector3D pubgCon::GetBoneWithRotation(DWORD_PTR mesh, int id)
	{
		FTransform bone = GetBoneIndex(mesh, id);
		FTransform ComponentToWorld;
		proc.memory().Read<FTransform>(mesh + 0x190, ComponentToWorld);
		D3DMATRIX Matrix;
		Matrix = D3DMATRIX::MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
		return Vector3D(Matrix._41, Matrix._42, Matrix._43);
	}


	Vector3D pubgCon::WorldToScreen(Vector3D &WorldLocation, FCameraCacheEntry &CameraCacheL)
	{
		int s_width = 0;//s_width	//屏幕宽
		int s_height = 0;//s_height	//屏幕高
		Vector3D Screenlocation = Vector3D(0, 0, 0);

		auto POV = CameraCacheL.POV;
		Vector3D Rotation = POV.Rotation.Vector(); // FRotator 这个转换不知道会不会有问题

		D3DMATRIX tempMatrix = D3DMATRIX::Matrix(Rotation); // Matrix

		Vector3D vAxisX, vAxisY, vAxisZ;

		vAxisX = Vector3D(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3D(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3D(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3D vDelta = WorldLocation - POV.Location;
		Vector3D vTransformed = Vector3D(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = POV.FOV;
		float ScreenCenterX = s_width / 2.0f;
		float ScreenCenterY = s_height / 2.0f;

		Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return Screenlocation;
	}

	std::vector<D3DXLine> &pubgCon::GetLine(DWORD_PTR mesh, std::vector<D3DXLine>& vl)
	{
		Vector3D neckpos = GetBoneWithRotation(mesh, Bones::neck_01);
		Vector3D pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
		Vector3D previous(0, 0, 0);
		Vector3D current, p1, c1;
		
		for (auto a : skeleton)
		{
			previous = Vector3D(0, 0, 0);
			for (int bone : a)
			{
				current = bone == Bones::neck_01 ? neckpos : (bone == Bones::pelvis ? pelvispos : GetBoneWithRotation(mesh, bone));
		
				if (previous.x == 0.f)
				{
					previous = current;
					continue;
				}
				p1 = WorldToScreen(previous, *g_global.cameracache);
				c1 = WorldToScreen(current, *g_global.cameracache);
				D3DXLine dLine;
				dLine.t1.x = p1.x;
				dLine.t1.y = p1.y;
				dLine.t2.x = c1.x;
				dLine.t2.y = c1.y;
				vl.push_back(dLine);
				previous = current;
			}
		}
		return vl;
	}

	void pubgCon::printPlayLine()
	{
		void *param(reinterpret_cast<void *>(this));
		EnumActor([](AActor& actor, DWORD_PTR addr, void *parameter)->BOOL {
			pubgCon *_this = reinterpret_cast<pubgCon *>(parameter);
			DWORD_PTR mesh;
			_this->proc.memory().Read<DWORD_PTR>(addr + 0x400, mesh);
			std::vector<D3DXLine> vl;
			_this->GetLine(mesh, vl);
			int count = 0;
			for (auto line : vl) {
				std::cout << count << "> t1.x=" << line.t1.x << ", t1.y=" << line.t1.y\
					<< ", t2.x = " << line.t2.x << ", t2.y = " << line.t2.y << std::endl;
			}
			return FALSE;
		}, param);
	}
	// xuq add end


	VOID pubgCon::InitObj()
	{
		std::lock_guard<std::mutex> l(mymutex);
		status = proc.Attach(TragetHandle);
		if (NT_SUCCESS(status))
		{
			try
			{
				//printPlayLine();
				g_global.update();
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
			//MessageBox(NULL, "AAAA", NULL, NULL);
			//EnumPlayComponent();
			GetPlayerCount();
			Sleep(2000);
		} while (true);
	}
}
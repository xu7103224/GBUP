#include "GameManager.h"
#include <iostream>
#include <tchar.h>
#include "FMath.h"
#include "PUBG_Engine_classes.h"
#include "PUBG_Engine_structs.h"
#define GAMEWINDOW "UnrealWindow"
namespace PUBG
{
	HANDLE TragetHandle{ 0 };
	pubgCon* pubgCon::m_instance = NULL;

	pubgCon::pubgCon() 
		: status(STATUS_SUCCESS)
		, BaseAddress(0),
		PlayerCounts(0),
		PlayersSkeletonSize(0)
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
		PlayersSkeleton.resize(SKELETON_MAX);
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
		proc.memory().Read<DWORD_PTR>(offsets.pLocalPlayerArray + 0x0, offsets.pLocalPlayer);
		proc.memory().Read<DWORD_PTR>(offsets.pLocalPlayer + 0x58, offsets.pViewportClient);
		std::cout << "tlsGameBase = " << std::hex << offsets.tlsGameBase << "\n pUWorld = " << std::hex << offsets.pUWorld \
			      << "\n pGameInstance = " << std::hex << offsets.pGameInstance << "\n pLocalPlayerArray = " << offsets.pLocalPlayerArray \
			      << "\n pLocalPlayer = " << offsets.pLocalPlayer << "\n pViewportClient = " << offsets.pViewportClient \
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
			 //auto pos = GetActorPos(Addres);
			 //std::cout << "obj name = " << name \
				//<< ", x = " << std::to_string(pos.x)\
				//<< ", y = " << std::to_string(pos.y)\
				//<< ", z = " << std::to_string(pos.z)\
				//<< std::endl;

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
		std::unordered_set<std::string> hashmap_i1(Item_1.begin(), Item_1.end());
		std::unordered_set<std::string> hashmap_i2(Item_2.begin(), Item_2.end());
		std::unordered_set<std::string> hashmap_i3(Item_3.begin(), Item_3.end());
		std::unordered_set<std::string> hashmap_i4(Item_4.begin(), Item_4.end());
		std::unordered_set<std::string> hashmap_i5(Item_5.begin(), Item_5.end());

		std::unordered_set<std::string> hashmap_player(playerNames.begin(), playerNames.end());
		std::unordered_set<std::string> hashmap_uaz(uazNames.begin(), uazNames.end());
		std::unordered_set<std::string> hashmap_dacia(daciaNames.begin(), daciaNames.end());
		std::unordered_set<std::string> hashmap_bike(bikeNames.begin(), bikeNames.end());
		std::unordered_set<std::string> hashmap_buggy(buggyNames.begin(), buggyNames.end());
		std::unordered_set<std::string> hashmap_Item(ItemName_.begin(), ItemName_.end());

		int item1(0), item2(0), item3(0), item4(0), item5(0);
		for (int i(0), c1(0), c2(0), c3(0), c4(0), c5(0), c6(0); i < 100000; i++)
		{
			name = GetActorNameById(i);

			if (c1 < 4 && hashmap_player.find(name) != hashmap_player.end()) {
				motorbike[c1++] = i;
				continue;
			}
			if (c2 < 3 && hashmap_uaz.find(name) != hashmap_uaz.end()) {
				motorbike[c2++] = i;
				continue;
			}
			if (c3 < 4 && hashmap_dacia.find(name) != hashmap_dacia.end()) {
				motorbike[c3++] = i;
				continue;
			}

			if (c4 < 5 && hashmap_bike.find(name) != hashmap_bike.end()) {
				motorbike[c4++] = i;
				continue;
			}
			if (c5 < 3 && hashmap_buggy.find(name) != hashmap_buggy.end()) {
				buggy[c5++] = i;
				continue;
			}
			if (name == boatName.at(0).c_str())
			{
				boat = i;
				continue;
			}
			if (c6 < 2 && hashmap_Item.find(name) != hashmap_Item.end()) {
				itemtype[c6++] = i;
				continue;
			}

			if (item1 < 58 && hashmap_i1.find(name) != hashmap_i1.end()) {
				std::cout << name << " " << i << std::endl;
				item_1_ID.insert(i);
				item1++;
				continue;

			}
			if (item2 < 22 && hashmap_i2.find(name) != hashmap_i2.end()) {
				std::cout << name << " " << i << std::endl;
				item_2_ID.insert(i);
				item2++;
				continue;
			}
			if (item3 < 36 && hashmap_i3.find(name) != hashmap_i3.end()) {
				std::cout << name << " " << i << std::endl;
				item_3_ID.insert(i);
				item3++;
				continue;
			}
			if (item4 < 6 && hashmap_i4.find(name) != hashmap_i4.end()) {
				std::cout << name << " " << i << std::endl;
				item_4_ID.insert(i);
				item4++;
				continue;
			}
			if (item5 < 6 && hashmap_i5.find(name) != hashmap_i5.end()) {
				std::cout << name << " " << i << std::endl;
				item_5_ID.insert(i);
				item5++;
				continue;
			}

			if (c1 == 4 && c2 == 3 && c3 == 4 && c4 == 5 && c5 == 3 && boat != 0 && c6 == 2
				&& item1 == 57 && item2 == 21 && item3 == 35 && item4 == 5 && item5 == 5)
				return;
			///遍历Item 类别，比较费时间

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

		proc.memory().Read<DWORD_PTR>(BaseAddress + NAME_OFFSETS, fName);
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

	void pubgCon::EnumAllObj()
	{
		void *param( reinterpret_cast<void *>(this));
		EnumActor([](AActor& actor, DWORD_PTR addr, void *parameter)->BOOL {
			pubgCon* _this = reinterpret_cast<pubgCon *>(parameter);
			USceneComponent comp;

			std::string name = _this->GetActorNameById(actor.Name.ComparisonIndex);
			//处理玩家数据
			if (_this->IsPlayerActor(actor)) {
				ACharacter player;
				_this->proc.memory().Read<ACharacter>(addr, player);
				_this->OnPlayer(player);
			}

			//处理载具数据
			VehicleType vtype;
			if ((vtype = _this->IsVehicleActor(actor)) != NONVehic) {
				_this->OnVehicle(addr, vtype);
			}

			//处理物品生成点
			if (_this->IsDroppedItemGroup(actor)) {
				//_this->OnItem(addr);
			}
			return FALSE;
		}, param);
	}

	BOOL pubgCon::IsPlayerActor(AActor * ptr)
	{
		AActor temp;
		proc.memory().Read<AActor>(reinterpret_cast<DWORD_PTR>(ptr), temp);
		return IsPlayerActor(temp);
	}

	BOOL pubgCon::IsPlayerActor(AActor &actor)
	{
		for (int i(0); i < 4; i++) {
			if (ActorIds[i] == actor.Name.ComparisonIndex)
				return TRUE;
		}
		return FALSE;
	}

	BOOL pubgCon::IsDroppedItemGroup(AActor * ptr)
	{
		AActor acotr;
		proc.memory().Read<AActor>(reinterpret_cast<DWORD_PTR>(ptr), acotr);
		return IsDroppedItemGroup(acotr);
	}

	BOOL pubgCon::IsDroppedItemGroup(AActor & actor)
	{
		if (actor.Name.ComparisonIndex == itemtype[0]
			|| actor.Name.ComparisonIndex == itemtype[1])
			return TRUE;
		return FALSE;
	}

	VehicleType pubgCon::IsVehicleActor(AActor * ptr)
	{
		AActor temp;
		proc.memory().Read<AActor>(reinterpret_cast<DWORD_PTR>(ptr), temp);
		return IsVehicleActor(temp);
	}

	VehicleType pubgCon::IsVehicleActor(AActor & actor)
	{
		for (int i(0); i < 3; i++) {//UAZ
			if (uaz[i] == actor.Name.ComparisonIndex)
				return UAZ;
		}
		for (int i(0); i < 4; i++) { //DACIA
			if (dacia[i] == actor.Name.ComparisonIndex)
				return DACIA;
		}
		for (int i(0); i < 5; i++) { //MOTORBIKE
			if (motorbike[i] == actor.Name.ComparisonIndex)
				return MOTORBIKE;
		}
		for (int i(0); i < 3; i++) { //BUGGY
			if (motorbike[i] == actor.Name.ComparisonIndex)
				return BUGGY;
		}
		if (boat == actor.Name.ComparisonIndex)
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

	FCameraCacheEntry &pubgCon::GetCameraCache(FCameraCacheEntry& cce)
	{
		DWORD_PTR lp = offsets.pLocalPlayer;
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
		Matrix = FMath::MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
		return Vector3D(Matrix._41, Matrix._42, Matrix._43);
	}

	Vector3D pubgCon::WorldToScreen(Vector3D &WorldLocation, FCameraCacheEntry &CameraCacheL)
	{
		Vector3D Screenlocation = Vector3D(0, 0, 0);

		auto POV = CameraCacheL.POV;
		Rotator Rotation = POV.Rotation;
		D3DMATRIX tempMatrix = FMath::Matrix(Rotation); 

		Vector3D vAxisX, vAxisY, vAxisZ;
		Rotation.GetAxes(vAxisX, vAxisY, vAxisZ);

		Vector3D vDelta = WorldLocation - POV.Location;
		Vector3D vTransformed = Vector3D(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = POV.FOV;
		float ScreenCenterX = g_global.screenWidth / 2.0f;
		float ScreenCenterY = g_global.screenHeight / 2.0f;

		Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return Screenlocation;
	}

	std::vector<D3DXLine> &pubgCon::GetSkeletons(DWORD_PTR mesh, std::vector<D3DXLine>& vl)
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
				vl[PlayersSkeletonSize] = dLine;
				++PlayersSkeletonSize;
				previous = current;
			}
		}
		return vl;
	}

	void pubgCon::OnPlayer(ACharacter & player)
	{
		//获取骨架
		GetSkeletons(reinterpret_cast<DWORD_PTR>(player.Mesh), PlayersSkeleton);

		//玩家计数
		++PlayerCounts;
	}

	void pubgCon::OnItem(DWORD_PTR actorPtr)
	{
		DWORD_PTR DroppedItemGroupArray(0);
		
		int count(0);
		proc.memory().Read<DWORD_PTR>(actorPtr + 0x2D8, DroppedItemGroupArray);
		proc.memory().Read<int>(actorPtr + 0x2E0, count);
		for (int i(0); i < count; i++) {
			wchar_t entityname[64] = { NULL };
			Vector3D  relative;
			DWORD_PTR pADroppedItemGroup(0);
			DWORD_PTR pUItem(0);
			DWORD_PTR pUItemFString(0);
			DWORD_PTR pItemName(0);
			DWORD     ItemId(0);
			uint8_t     Category(0);

			proc.memory().Read<DWORD_PTR>(DroppedItemGroupArray + i * 0x10, pADroppedItemGroup);
			proc.memory().Read<Vector3D>(pADroppedItemGroup + 0x1E0, relative);
			proc.memory().Read<DWORD_PTR>(pADroppedItemGroup + 0x448, pUItem);
			proc.memory().Read<uint8_t>(pUItem + 0x170, Category);
			proc.memory().Read<DWORD_PTR>(pUItem + 0x40, pUItemFString);
			proc.memory().Read<DWORD>(pUItem + 0x18, ItemId);

			proc.memory().Read<DWORD_PTR>(pUItemFString + 0x28, pItemName);
			ItemListD.push_back({ ItemId , Category , relative.x, relative.y, relative.z });
		
		}
		
		
	}

	void pubgCon::OnVehicle(DWORD_PTR vehicleaddr, VehicleType type)
	{

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
				CacheNames();
				my_atomic.store(TRUE);
			}
			catch (...){
				my_atomic.store(FALSE);
			}
		}
	}


	VOID pubgCon::MainLoop()
	{
		static int loopcount = 0;
		Overlay::instance()->SetupWindow();

		while (!my_atomic.load())
		{
			InitObj();
			Sleep(500);
		}
		std::cout << "init success!" << std::endl;

		do
		{
			//
			//update
			//

			if ((loopcount % 2000) == 0) {
				g_global.updateCameraCache();
			}
			g_global.update();
			EnumAllObj();
			
			//
			//update window data
			//
			Overlay *wnd = Overlay::instance();
			wnd->updateSkeletons(PlayersSkeleton, PlayersSkeletonSize);
#ifdef _DEBUG
			static int loopcount = 0;
			++loopcount;
			if((loopcount%2000)==0){ 
				std::cout << "Players counts =" << PlayerCounts << std::endl;
			}
#endif // _DEBUG

			//
			//clear
			//
			
			ItemListD.clear();
			PlayerCounts = 0;
			PlayersSkeletonSize = 0;//骨骼线清零
			Sleep(0);
			++loopcount;
		} while (true);
	}
}
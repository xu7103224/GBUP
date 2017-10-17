#include "Offsets.h"
#include "GameManager.h"
namespace PUBG
{
	COffsets offsets;
	int ActorIds[4];
	int uaz[3];
	int dacia[4];
	int motorbike[5];
	int buggy[3];
	int boat = 0;
	int itemtype[2];
	std::vector<std::string> playerNames = { "PlayerFemale_A", "PlayerFemale_A_C", "PlayerMale_A", "PlayerMale_A_C" };
	std::vector<std::string> uazNames = { "Uaz_A_01_C", "Uaz_B_01_C", "Uaz_C_01_C" };
	std::vector<std::string> buggyNames = { "Buggy_A_01_C", "Buggy_A_02_C", "Buggy_A_03_C" };
	std::vector<std::string> daciaNames = { "Dacia_A_01_C", "Dacia_A_02_C", "Dacia_A_03_C", "Dacia_A_04_C" };
	std::vector<std::string> bikeNames = { "ABP_Motorbike_03_C", "ABP_Motorbike_04_C", "BP_Motorbike_03_C", "BP_Motorbike_04_C" ,"ABP_Motorbike_03_Sidecart_C" };
	std::vector<std::string> boatName = { "Boat_PG117_C" };
	std::vector<std::string> ItemName_ = { "DroppedItemInteractionComponent", "DroppedItemGroup" };

	//组件列表
	std::list<int> upper_part = { Bones::neck_01, Bones::Head, Bones::forehead };
	std::list<int> right_arm = { Bones::neck_01, Bones::upperarm_r, Bones::lowerarm_r, Bones::hand_r };
	std::list<int> left_arm = { Bones::neck_01, Bones::upperarm_l, Bones::lowerarm_l, Bones::hand_l };
	std::list<int> spine = { Bones::neck_01, Bones::spine_01, Bones::spine_02, Bones::pelvis };
	std::list<int> lower_right = { Bones::pelvis, Bones::thigh_r, Bones::calf_r, Bones::foot_r };
	std::list<int> lower_left = { Bones::pelvis, Bones::thigh_l, Bones::calf_l, Bones::foot_l };
	std::list<std::list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

	void initOffsets(COffsets &Of)
	{

	}


	CGlobalObjs g_global;

	CGlobalObjs::CGlobalObjs()
	{
		cameracache = new FCameraCacheEntry();

	}

	CGlobalObjs::~CGlobalObjs()
	{
		SAFE_DELETE(cameracache);
	}

	void CGlobalObjs::update()
	{
		pubgCon *pc = pubgCon::instance();
		*cameracache = pc->GetCameraCache();
	}

}
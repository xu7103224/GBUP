#include "Offsets.h"

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

	void initOffsets(COffsets &Of)
	{

	}
}
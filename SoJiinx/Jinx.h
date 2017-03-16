#include "PluginSDK.h"

class Jinx
{
public:
	static int GetFishboneRange();
	static bool HasFishbone();

	static float GetRealPowPowRange(IUnit* target);
	static void FishboneToMinigun(IUnit* target);

	static std::vector<std::string> SpecialSpells;
};


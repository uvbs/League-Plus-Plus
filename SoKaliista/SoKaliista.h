#include "PluginSDK.h"
#include <map>

class SoKaliista
{
public:
	static double GetRendDamage(IUnit* target);
	static Vec3 GetFirstWallPoint(Vec3 from, Vec3 to, int step = 25);
	static Vec3 WallJumpTarget;
	static int WallJumpTime;
	static bool WallJumpPossible;
	static IUnit* Soulbound;
	static std::map<float, float> SoulboundDamage;
};


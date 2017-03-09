#include "PluginSDK.h"

class sExtensions
{
public:
	static bool IsFarming();
	static float GetDistance(IUnit* sender, IUnit* target);
	static float GetRealDistance(IUnit* sender, IUnit* target);
	static int CountAlliesInTargetRange(IUnit* target, float range);
	static int CountEnemiesInTargetRange(IUnit* target, float range);
	static int CountMinionsInTargetRange(IUnit* target, float range);
};
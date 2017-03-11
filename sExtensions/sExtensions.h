#include "PluginSDK.h"

class sExtensions
{
public:
	static std::string format(const char* format, ...);
	static bool TextureExists(std::string file);
	static ITexture* GetTexture(std::string file);
	static bool IsComboing();
	static bool IsHarassing();
	static bool IsClearing();
	static bool IsLasthitting();
	static bool IsFarming();
	static float GetDistance(IUnit* sender, IUnit* target);
	static float GetDistance(Vec3 senderPosition, Vec3 targetPosition);
	static float GetRealDistance(IUnit* sender, IUnit* target);
	static int CountAlliesInTargetRange(IUnit* target, float range);
	static int CountEnemiesInTargetRange(IUnit* target, float range);
	static int CountMinionsInTargetRange(IUnit* target, float range);
};
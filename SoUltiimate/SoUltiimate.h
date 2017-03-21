#include <vector>
#include <map>
#include "PluginSDK.h"

struct TeleportStatus
{
	int Status;
	float Duration;
	float StartTime;
	float EndTime;
	float UltimateTime;
};

class SoUltiimate
{
public:
	static void Initialize();
	static void HandleUltimate(IUnit* hero, float recallDuration);

	static std::vector<char*> Champions;
	static std::map<int, float> VisibleTimers;
	static std::map<int, std::map<eTeleportType, TeleportStatus>> TeleportTimers;
};
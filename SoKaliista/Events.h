#include "PluginSDK.h"

class Events
{
public:
	static void Initialize();
private:
	static void OnGameUpdate();
	static void OnRender();
	static void OnSpellCast(CastedSpell const& spell);
	static void OnOrbwalkNonKillableMinion(IUnit* minion);
	static void OnLevelUp(IUnit* source, int newLevel);
};


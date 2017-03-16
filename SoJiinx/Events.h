#include "PluginSDK.h"

class Events
{
public:
	static void Initialize();
private:
	static void OnGameUpdate();
	static void OnRender();
	static void OnLevelUp(IUnit* source, int newLevel);
	static void OnOrbwalkBeforeAttack(IUnit* target);
	static void OnGapCloser(GapCloserSpell const& spell);
	static void OnSpellCast(CastedSpell const& spell);
};


#include "sExtensions.h"
#include "sLogics.h"
#include "sMenu.h"
#include "sSpells.h"

class Jinx
{
public:
	static void GetSpecialSpells();
	static int FishboneRange();
	static bool HasFishbone();

	static float GetRealPowPowRange(IUnit* target);
	static void FishboneToMinigun(IUnit* target);

	static IPluginSDK* SDK;
	static sExtensions* Extensions;
	static IUnit* Player;
	static sMenu* Menu;
	static sSpells* Spells;
	static sLogics* Logics;

	static std::vector<std::string> SpecialSpells;
};

inline void Jinx::GetSpecialSpells()
{
	SpecialSpells.insert(SpecialSpells.end(), {
		"luxlightbinding",
		"katarinar",
		"drain",
		"consume",
		"absolutezero",
		"staticfield",
		"reapthewhirlwind",
		"jinxw",
		"jinxr",
		"shenstandunited",
		"threshe",
		"threshrpenta",
		"threshq",
		"meditate",
		"caitlynpiltoverpeacemaker",
		"volibearqattack",
		"cassiopeiapetrifyinggaze",
		"ezrealtrueshotbarrage",
		"galioidolofdurand",
		"luxmalicecannon",
		"missfortunebullettime",
		"infiniteduress",
		"alzaharnethergrasp",
		"lucianq",
		"velkozr",
		"rocketgrabmissile"
	});
}

inline int Jinx::FishboneRange()
{
	int ranges[6] = { 0, 75, 100, 125, 150, 175 };

	return ranges[Player->GetSpellBook()->GetLevel(kSlotQ)];
}

inline bool Jinx::HasFishbone()
{
	return Player->HasBuff("JinxQ");
}

inline float Jinx::GetRealPowPowRange(IUnit* target)
{
	return 650.f + Player->BoundingRadius() + target->BoundingRadius();
}

inline void Jinx::FishboneToMinigun(IUnit* target)
{
	auto realDistance = Extensions->GetRealDistance(Player, target);

	if (Extensions->GetRealDistance(Player, target) < GetRealPowPowRange(target) && Extensions->CountEnemiesInTargetRange(target, 250) < Menu->QComboAoE->GetInteger() && Extensions->IsComboing() || !target->IsHero() && Extensions->IsFarming())
	{
		if (Player->ManaPercent() < Menu->ManaQCombo->GetInteger() && Extensions->IsComboing() ||
			SDK->GetDamage()->GetAutoAttackDamage(Player, target, false) * Menu->QKillableAutoAttacks->GetInteger() < target->GetHealth())
		{
			Spells->Q->CastOnPlayer();
		}
	}
}
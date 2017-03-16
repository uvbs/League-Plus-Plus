#include "Jinx.h"
#include "Extension.h"
#include "Plugin.h"
#include "Hero.h"

std::vector<std::string> Jinx::SpecialSpells = {
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
};

int Jinx::GetFishboneRange()
{
	int ranges[6] = { 0, 75, 100, 125, 150, 175 };

	return ranges[GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ)];
}

bool Jinx::HasFishbone()
{
	return GEntityList->Player()->HasBuff("JinxQ");
}

float Jinx::GetRealPowPowRange(IUnit* target)
{
	return 650.f + GEntityList->Player()->BoundingRadius() + target->BoundingRadius();
}

void Jinx::FishboneToMinigun(IUnit* target)
{
	if (GExtension->GetRealDistance(GEntityList->Player(), target) < GetRealPowPowRange(target) && GExtension->CountEnemiesInTargetRange(target, 250) < GPlugin->GetMenuOption("Q", "Combo.Enemies")->GetInteger() && GExtension->IsComboing() || !target->IsHero() && GExtension->IsFarming())
	{
		if (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuOption("Mana", "Q.Combo")->GetInteger() && GExtension->IsComboing() ||
			GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuOption("Q", "Mana.Ignore")->GetInteger() < target->GetHealth())
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}
}

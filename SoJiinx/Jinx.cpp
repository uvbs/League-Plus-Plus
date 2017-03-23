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
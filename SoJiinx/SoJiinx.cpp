#include "SoJiinx.h"
#include "Extension.h"

std::vector<std::string> SoJiinx::SpecialSpells = {
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

int SoJiinx::GetFishboneRange()
{
	int ranges[6] = { 0, 75, 100, 125, 150, 175 };

	return ranges[GEntityList->Player()->GetSpellBook()->GetLevel(kSlotQ)];
}

bool SoJiinx::HasFishbone()
{
	return GEntityList->Player()->HasBuff("JinxQ");
}
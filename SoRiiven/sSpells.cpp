#include "PluginSDK.h"
#include "Riven.h"

void sSpells::Create()
{
	Q = Riven::SDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
	W = Riven::SDK->CreateSpell(kSlotW, 250.f);
	E = Riven::SDK->CreateSpell(kSlotE, 270.f);
	R1 = Riven::SDK->CreateSpell(kSlotR);
	R2 = Riven::SDK->CreateSpell2(kSlotR, kConeCast, true, true, kCollidesWithYasuoWall);
}

void sSpells::Initialize() const
{
	Q->SetSkillshot(0.25f, 100.f, 2200.f, 260.f);
	R2->SetSkillshot(0.25f, 110.f, 1600.f, 900.f);
}

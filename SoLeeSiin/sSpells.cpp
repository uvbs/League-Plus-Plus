#include "PluginSDK.h"
#include "LeeSin.h"

void sSpells::Create()
{
	Q = LeeSin::SDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	W = LeeSin::SDK->CreateSpell(kSlotW, 700.f);
	E = LeeSin::SDK->CreateSpell(kSlotE, 425.f);
	R = LeeSin::SDK->CreateSpell(kSlotR, 375.f);
	R2 = LeeSin::SDK->CreateSpell2(kSlotR, kLineCast, true, false, kCollidesWithNothing);
}

void sSpells::Initialize() const
{
	Q->SetSkillshot(0.25f, 60.f, 1800.f, 1100.f);
	R2->SetSkillshot(0.25f, 100.f, 1500.f, 800.f);
}

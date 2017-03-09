#include "PluginSDK.h"
#include "Jinx.h"

void sSpells::Create()
{
	Q = Jinx::SDK->CreateSpell(kSlotQ);
	W = Jinx::SDK->CreateSpell2(kSlotW, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	E = Jinx::SDK->CreateSpell2(kSlotE, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	R = Jinx::SDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall));
}

void sSpells::Initialize() const
{
	W->SetSkillshot(0.6f, 75.f, 3300.f, 1450.f);
	E->SetSkillshot(1.2f, 1.f, 1750.f, 900.f);
	R->SetSkillshot(0.7f, 140.f, 1500.f, 3000.f);
}

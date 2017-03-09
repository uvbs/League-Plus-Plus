#include "PluginSDK.h"
#include "Kalista.h"

void sSpells::Create()
{
	Q = Kalista::SDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	W = Kalista::SDK->CreateSpell(kSlotW, 5200);
	E = Kalista::SDK->CreateSpell(kSlotE, 950);
	R = Kalista::SDK->CreateSpell(kSlotR, 1200);
}

void sSpells::Initialize() const
{
	Q->SetSkillshot(0.25f, 40.f, 1200.f, 1150.f);
}

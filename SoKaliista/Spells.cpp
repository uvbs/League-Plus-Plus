#include "Hero.h"
#include "Spells.h"

void Spells::Initialize()
{
	auto Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	Q->SetSkillshot(0.25f, 40.f, 1200.f, 1150.f);
	auto W = GPluginSDK->CreateSpell(kSlotW, 5200);
	auto E = GPluginSDK->CreateSpell(kSlotE, 1000);
	auto R = GPluginSDK->CreateSpell(kSlotR, 1500);

	GHero->AddSpell("Q", Q);
	GHero->AddSpell("W", W);
	GHero->AddSpell("E", E);
	GHero->AddSpell("R", R);
}

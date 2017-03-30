#include "Hero.h"
#include "Spells.h"

void Spells::Initialize()
{
	auto Q = GPluginSDK->CreateSpell(kSlotQ);
	auto W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	W->SetSkillshot(0.6f, 75.f, 3300.f, 1450.f);
	auto E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	E->SetSkillshot(1.9f, 1.f, 1750.f, 900.f);
	auto R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall));
	R->SetSkillshot(0.7f, 140.f, 1500.f, 3000.f);

	GHero->AddSpell("Q", Q);
	GHero->AddSpell("W", W);
	GHero->AddSpell("E", E);
	GHero->AddSpell("R", R);
}
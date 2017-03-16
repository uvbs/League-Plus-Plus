#include "Hero.h"
#include "Spells.h"

void Spells::Initialize()
{
	auto Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, kCollidesWithYasuoWall);
	Q->SetSkillshot(0.25f, 40.f, 1000.f, 1450.f);
	auto W = GPluginSDK->CreateSpell(kSlotW);
	auto R = GPluginSDK->CreateSpell(kSlotR, 5500);

	GHero->AddSpell("Q", Q);
	GHero->AddSpell("W", W);
	GHero->AddSpell("R", R);
}

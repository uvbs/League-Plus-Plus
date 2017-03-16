#include "Hero.h"
#include "Spells.h"

void Spells::Initialize()
{
	auto Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, false, true, kCollidesWithNothing);
	Q->SetSkillshot(0.6f, 250.f, 2000.f, 650.f);
	auto W = GPluginSDK->CreateSpell(kSlotW);
	auto E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, true, kCollidesWithNothing);
	E->SetSkillshot(0.25f, 35.f, 1250.f, 1075.f);
	auto R = GPluginSDK->CreateSpell(kSlotR, 550.f);

	GHero->AddSpell("Q", Q);
	GHero->AddSpell("W", W);
	GHero->AddSpell("E", E);
	GHero->AddSpell("R", R);
}

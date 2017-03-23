#include "Hero.h"
#include "Spells.h"

void Spells::Initialize()
{
	auto Q = GPluginSDK->CreateSpell(kSlotQ);
	auto W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, kCollidesWithNothing);
	W->SetOverrideRange(900);
	auto E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithYasuoWall);
	E->SetOverrideRange(550 + 7 * (GEntityList->Player()->GetLevel() - 1));
	auto R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, true, kCollidesWithYasuoWall);
	R->SetOverrideRange(550 + 7 * (GEntityList->Player()->GetLevel() - 1));

	GHero->AddSpell("Q", Q);
	GHero->AddSpell("W", W);
	GHero->AddSpell("E", E);
	GHero->AddSpell("R", R);
}
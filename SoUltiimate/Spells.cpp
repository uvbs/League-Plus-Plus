#include "Hero.h"
#include "Spells.h"

void Spells::Initialize()
{
	if (std::string(GEntityList->Player()->ChampionName()) == "Ashe")
	{
		auto R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall));
		R->SetSkillshot(0.25f, 130.f, 1600.f, FLT_MAX);

		GHero->AddSpell("R", R);
	}

	if (std::string(GEntityList->Player()->ChampionName()) == "Draven")
	{
		auto R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall));
		R->SetSkillshot(0.4f, 160.f, 2000.f, FLT_MAX);

		GHero->AddSpell("R", R);
	}

	if (std::string(GEntityList->Player()->ChampionName()) == "Ezreal")
	{
		auto R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, kCollidesWithYasuoWall);
		R->SetSkillshot(1.f, 160.f, 2000.f, FLT_MAX);

		GHero->AddSpell("R", R);
	}

	if (std::string(GEntityList->Player()->ChampionName()) == "Jinx")
	{
		auto R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithYasuoWall));
		R->SetSkillshot(0.6f, 140.f, 1700.f, FLT_MAX);

		GHero->AddSpell("R", R);
	}

	if (std::string(GEntityList->Player()->ChampionName()) == "Karthus")
	{
		auto R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
		R->SetSkillshot(3.125f, 0.f, 0.f, FLT_MAX);

		GHero->AddSpell("R", R);
	}
}

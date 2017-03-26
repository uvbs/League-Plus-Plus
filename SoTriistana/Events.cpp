#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"

void Events::Initialize()
{
	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterRenderEvent(OnRender);
	GPlugin->RegisterLevelUpEvent(OnLevelUp);
}

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	auto E = GHero->GetSpell2("E");
	E->SetOverrideRange(550 + 7 * (GEntityList->Player()->GetLevel() - 1));
	GHero->AddSpell("E", E);

	auto R = GHero->GetSpell2("R");
	R->SetOverrideRange(550 + 7 * (GEntityList->Player()->GetLevel() - 1));
	GHero->AddSpell("R", R);

	if (GExtension->IsComboing())
	{
		Modes::Combo();
	}

	Modes::Always();
	Modes::KillSteal();
}

void Events::OnRender()
{
	if (GPlugin->GetMenuBoolean("Drawings", "W") && (GHero->GetSpell2("W")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell2("W")->Range());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "E") && (GHero->GetSpell2("E")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell2("E")->Range());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "R") && (GHero->GetSpell2("R")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell2("R")->Range());
	}
}

void Events::OnLevelUp(IUnit* source, int newLevel)
{
	switch (newLevel)
	{
	case 6:
	case 11:
	case 16:
		source->LevelUpSpell(kSlotR);
		break;
	default:
		break;
	}
}

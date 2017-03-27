#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"
#include "TwistedFate.h"
#include <string>

void Events::Initialize()
{
	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterRenderEvent(OnRender);
	GPlugin->RegisterSpellCastEvent(OnSpellCast);
	GPlugin->RegisterLevelUpEvent(OnLevelUp);
}

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	Modes::Always();

	if (GExtension->IsComboing())
	{
		Modes::Combo();
	}
}

void Events::OnRender()
{
	if (GPlugin->GetMenuBoolean("Drawings", "Q") && (GHero->GetSpell2("Q")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell2("Q")->Range());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "R") && (GHero->GetSpell("R")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell("R")->GetSpellRange());
	}
}

void Events::OnSpellCast(CastedSpell const& spell)
{
	if (spell.Caster_ != GEntityList->Player())
		return;

	if (std::string(spell.Name_) == "Gate" && GPlugin->GetMenuBoolean("W", "R.Yellow"))
	{
		if (GHero->GetSpell("W")->IsReady() && strstr(GEntityList->Player()->GetSpellBook()->GetName(kSlotW), "PickACard") != nullptr)
		{
			GHero->GetSpell("W")->CastOnPlayer();
			TwistedFate::SelectedCard = TwistedFate::kCardYellow;
		}
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

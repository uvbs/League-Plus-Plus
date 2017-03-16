#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"
#include "TwistedFate.h"

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

	if (GExtension->IsComboing())
	{
		Modes::Combo();
	}

	Modes::Always();
}

void Events::OnRender()
{
	if (GPlugin->GetMenuOption("Drawings", "Q")->Enabled() && GHero->GetSpell2("Q")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell2("Q")->Range());
	}

	if (GPlugin->GetMenuOption("Drawings", "R")->Enabled() && GHero->GetSpell("R")->IsReady() || !GPlugin->GetMenuOption("Drawings", "Ready")->Enabled())
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell("R")->GetSpellRange());
	}
}

void Events::OnSpellCast(CastedSpell const& spell)
{
	if (spell.Caster_ != GEntityList->Player())
		return;

	TwistedFate::CardSelector->OnSpellCast(spell);

	if (std::string(spell.Name_) == "Gate" && GPlugin->GetMenuOption("W", "R.Yellow")->Enabled())
	{
		TwistedFate::CardSelector->StartSelecting(TwistedFate::CardSelector->kCardYellow);
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

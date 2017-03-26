#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"
#include <algorithm>
#include "Jinx.h"

void Events::Initialize()
{
	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterRenderEvent(OnRender);
	GPlugin->RegisterOrbwalkBeforeAttackEvent(OnOrbwalkBeforeAttack);
	GPlugin->RegisterGapCloserEvent(OnGapCloser);
	GPlugin->RegisterSpellCastEvent(OnSpellCast);
	GPlugin->RegisterLevelUpEvent(OnLevelUp);
}

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	auto R = GHero->GetSpell2("R");
	R->SetOverrideRange(GPlugin->GetMenuInteger("R", "Range"));
	GHero->AddSpell("R", R);

	if (GExtension->IsComboing())
	{
		Modes::Combo();
	}

	if (GExtension->IsClearing())
	{
		Modes::Clear();
	}

	if (GExtension->IsLasthitting())
	{
		Modes::Lasthit();
	}

	if (GExtension->IsHarassing())
	{
		Modes::Harass();
	}

	Modes::Always();
	Modes::KillSteal();
	Modes::Semi();
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

void Events::OnOrbwalkBeforeAttack(IUnit* target)
{
	if (!Jinx::HasFishbone())
		return;

	if (GHero->GetSpell("Q")->IsReady() && target->IsHero())
	{
		if (GExtension->GetRealDistance(GEntityList->Player(), target) < 525 && GExtension->CountEnemiesInTargetRange(target, 250) < GPlugin->GetMenuInteger("Q", "Combo.Enemies") && GExtension->IsComboing() || !target->IsHero() && GExtension->IsFarming())
		{
			if (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Mana", "Q.Combo") && GExtension->IsComboing() || GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuInteger("Q", "Mana.Ignore") < target->GetHealth())
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
	}

	if (GHero->GetSpell("Q")->IsReady() && !GExtension->IsComboing() && target->IsCreep())
	{
		if (GExtension->IsClearing() && GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Mana", "Q.Clear") && GExtension->CountMinionsInTargetRange(target, 250) + 1 >= GPlugin->GetMenuInteger("Q", "Clear.Minions"))
		{

		}
		else if (GExtension->GetRealDistance(GEntityList->Player(), target) < 525)
		{
			GOrbwalking->DisableNextAttack();
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}
}

void Events::OnGapCloser(GapCloserSpell const& spell)
{
	if (!GHero->GetSpell2("E")->IsReady())
		return;

	if (!GPlugin->GetMenuBoolean("E", "OnGapCloser"))
		return;

	if (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Mana", "E.Auto"))
		return;

	if (!GEntityList->Player()->IsValidTarget(spell.Sender, GHero->GetSpell2("E")->Range()))
		return;

	GHero->GetSpell2("E")->CastOnPosition(spell.EndPosition);
}

void Events::OnSpellCast(CastedSpell const& spell)
{
	if (!spell.Caster_->IsHero())
		return;

	if (!spell.Caster_->IsEnemy(GEntityList->Player()))
		return;

	if (!GHero->GetSpell2("E")->IsReady())
		return;

	if (!GPlugin->GetMenuBoolean("E", "OnSpecialSpell"))
		return;

	if (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Mana", "E.Auto"))
		return;

	if (!GEntityList->Player()->IsValidTarget(spell.Caster_, GHero->GetSpell2("E")->Range()))
		return;

	auto spellName = std::string(spell.Name_);
	transform(spellName.begin(), spellName.end(), spellName.begin(), ::tolower);

	if (find(Jinx::SpecialSpells.begin(), Jinx::SpecialSpells.end(), spellName.c_str()) != Jinx::SpecialSpells.end())
	{
		GHero->GetSpell2("E")->CastOnPosition(spell.Caster_->GetPosition());
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

#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"
#include <algorithm>
#include "SoJiinx.h"

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
	R->SetOverrideRange(GPlugin->GetMenuInteger("Misc", "R.Range.Maximum"));
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
	if (GPlugin->GetMenuBoolean("Drawings", "Q") && (GHero->GetSpell2("Q")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "Q.Color"), SoJiinx::HasFishbone() ? 525 : SoJiinx::GetFishboneRange() + 525);
	}

	if (GPlugin->GetMenuBoolean("Drawings", "W") && (GHero->GetSpell2("W")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "W.Color"), GHero->GetSpell2("W")->Range());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "E") && (GHero->GetSpell2("E")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "E.Color"), GHero->GetSpell2("E")->Range());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "R.Minimum") && (GHero->GetSpell2("R")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "R.Minimum.Color"), GPlugin->GetMenuInteger("Misc", "R.Range.Minimum"));
	}

	if (GPlugin->GetMenuBoolean("Drawings", "R.Maximum") && (GHero->GetSpell2("R")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "R.Maximum.Color"), GHero->GetSpell2("R")->Range());
	}

	if (GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 1 || GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 3)
	{
		(GPlugin->GetMenuBoolean("Harass", "Q") ? SoJiinx::HarassOn : SoJiinx::HarassOff)->Draw(GPlugin->GetMenuInteger("Drawings", "Harass.Q.Texture.X"), GPlugin->GetMenuInteger("Drawings", "Harass.Q.Texture.Y"));
	}

	if (GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 2 || GPlugin->GetMenuInteger("Drawings", "Harass.Q") == 3)
	{
		Vec3 worldToScreen;
		GGame->Projection(GEntityList->Player()->GetPosition(), &worldToScreen);
		GRender->DrawTextW(Vec2(worldToScreen.x, worldToScreen.y), GPlugin->GetMenuBoolean("Harass", "Q") ? Vec4(0, 255, 0, 255) : Vec4(255, 0, 0, 255), "Q Harass: %s", GPlugin->GetMenuBoolean("Harass", "Q") ? "ON" : "OFF");
	}
}

void Events::OnOrbwalkBeforeAttack(IUnit* target)
{
	if (!SoJiinx::HasFishbone())
		return;

	if (GExtension->IsComboing() && target->IsHero() && GHero->GetSpell("Q")->IsReady())
	{
		if (GExtension->GetRealDistance(GEntityList->Player(), target) < 525 && GExtension->CountEnemiesInTargetRange(target, 250) + 1 < GPlugin->GetMenuInteger("Combo", "Q.Enemies") ||
			GExtension->GetRealDistance(GEntityList->Player(), target) < 525 && GExtension->CountEnemiesInTargetRange(target, 250) + 1 >= GPlugin->GetMenuInteger("Combo", "Q.Enemies") && GPlugin->GetMenuBoolean("Combo", "Q.Enemies.Range") ||
			GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Combo", "Q.Mana") && GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuInteger("Combo", "Q.Mana.Ignore") < target->GetHealth())
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}

	if (GExtension->IsClearing() && target->IsCreep() && GHero->GetSpell("Q")->IsReady())
	{
		if (!GPlugin->GetMenuBoolean("Clear", "Q") || GExtension->CountMinionsInTargetRange(target, 200) + 1 < GPlugin->GetMenuInteger("Clear", "Q.Enemies") || GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Clear", "Q.Mana"))
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}

	if (GExtension->IsFarming() && target->IsCreep() && GHero->GetSpell("Q")->IsReady())
	{
		if (!target->IsDead() && target->IsHero() && GPlugin->GetMenuBoolean("Harass", "Q") &&
			GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Harass", "Q.Mana") &&
			GPlugin->GetMenuBoolean("Harass", "Q.Minions") &&  GExtension->CountEnemiesInTargetRange(target, 200) >= 1 &&
			GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) > target->GetHealth())
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}
}

void Events::OnGapCloser(GapCloserSpell const& spell)
{
	if (!GHero->GetSpell2("E")->IsReady())
		return;

	if (!GPlugin->GetMenuBoolean("E.Auto", "OnGapCloser"))
		return;

	if (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("E.Auto", "Mana"))
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

	auto spellName = std::string(spell.Name_);
	transform(spellName.begin(), spellName.end(), spellName.begin(), ::tolower);

	if (GHero->GetSpell2("E")->IsReady() && GPlugin->GetMenuBoolean("E.Auto", "OnSpecialSpell") && GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("E.Auto", "Mana") && GEntityList->Player()->IsValidTarget(spell.Caster_, GHero->GetSpell2("E")->Range()))
	{
		if (find(SoJiinx::SpecialSpells.begin(), SoJiinx::SpecialSpells.end(), spellName.c_str()) != SoJiinx::SpecialSpells.end())
		{
			GHero->GetSpell2("E")->CastOnPosition(spell.Caster_->GetPosition());
		}
	}

	if (GHero->GetSpell2("W")->IsReady() && GPlugin->GetMenuBoolean("W.Auto", "OnSpecialSpell") && GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("W.Auto", "Mana") && GEntityList->Player()->IsValidTarget(spell.Caster_, GHero->GetSpell2("W")->Range()))
	{
		if (find(SoJiinx::SpecialSpells.begin(), SoJiinx::SpecialSpells.end(), spellName.c_str()) != SoJiinx::SpecialSpells.end())
		{
			GHero->GetSpell2("W")->CastOnPosition(spell.Caster_->GetPosition());
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

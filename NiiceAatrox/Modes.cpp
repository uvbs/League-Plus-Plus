#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"

void Modes::Combo()
{
	if (GPlugin->GetMenuOption("Q", "Combo")->Enabled() && GHero->GetSpell2("Q")->IsReady())
	{
		GHero->GetSpell2("Q")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range()), kHitChanceHigh);
	}

	if (GPlugin->GetMenuOption("W", "Combo")->Enabled() && GHero->GetSpell("W")->IsReady())
	{
		if (GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() <= GPlugin->GetMenuOption("W", "Combo.Heal")->GetInteger())
		{
			GHero->GetSpell("W")->CastOnPlayer();
		}
		else if (!GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() >  GPlugin->GetMenuOption("W", "Combo.Heal")->GetInteger())
		{
			GHero->GetSpell("W")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuOption("E", "Combo")->Enabled() && GHero->GetSpell2("E")->IsReady())
	{
		GHero->GetSpell2("E")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("E")->Range()), kHitChanceHigh);
	}

	if (GPlugin->GetMenuOption("R", "Combo")->Enabled() && GHero->GetSpell("R")->IsReady())
	{
		auto enemies = 0;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("R")->GetSpellRange()))
				continue;

			if (enemy->HealthPercent() <= GPlugin->GetMenuOption("R", "Combo.Health")->GetInteger())
			{
				GHero->GetSpell("R")->CastOnPlayer();
				break;
			}

			enemies++;
		}

		if (enemies >= GPlugin->GetMenuOption("R", "Combo.Enemies")->GetInteger())
		{
			GHero->GetSpell("R")->CastOnPlayer();
		}
	}
}

void Modes::Clear()
{
	if (GPlugin->GetMenuOption("Q", "Clear")->Enabled() && GHero->GetSpell2("Q")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell2("Q")->Range()))
				continue;

			GHero->GetSpell2("Q")->CastOnUnit(minion);
			break;
		}
	}

	if (GPlugin->GetMenuOption("W", "Clear")->Enabled() && GHero->GetSpell("W")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
				continue;

			if (GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() <= GPlugin->GetMenuOption("W", "Clear.Heal")->GetInteger())
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			else if (!GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() >  GPlugin->GetMenuOption("W", "Clear.Heal")->GetInteger())
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			break;
		}
	}

	if (GPlugin->GetMenuOption("E", "Clear")->Enabled() && GHero->GetSpell2("E")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell2("E")->Range()))
				continue;

			GHero->GetSpell2("E")->CastOnUnit(minion);
			break;
		}
	}
}

void Modes::Jungle()
{
	if (GPlugin->GetMenuOption("Q", "Jungle")->Enabled() && GHero->GetSpell2("Q")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell2("Q")->Range()))
				continue;

			GHero->GetSpell2("Q")->CastOnUnit(minion);
			break;
		}
	}

	if (GPlugin->GetMenuOption("W", "Jungle")->Enabled() && GHero->GetSpell("W")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
				continue;

			if (GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() <= GPlugin->GetMenuOption("W", "Jungle.Heal")->GetInteger())
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			else if (!GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() >  GPlugin->GetMenuOption("W", "Jungle.Heal")->GetInteger())
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			break;
		}
	}

	if (GPlugin->GetMenuOption("E", "Jungle")->Enabled() && GHero->GetSpell2("E")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell2("E")->Range()))
				continue;

			GHero->GetSpell2("E")->CastOnUnit(minion);
			break;
		}
	}
}

void Modes::Harass()
{
	if (GPlugin->GetMenuOption("E", "Harass")->Enabled() && GHero->GetSpell2("E")->IsReady())
	{
		GHero->GetSpell2("E")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("E")->Range()), kHitChanceMedium);
	}
}

void Modes::Flee()
{
	if (GetAsyncKeyState(GPlugin->GetMenuOption("Keys", "Flee")->GetInteger()))
	{
		GGame->IssueOrder(GEntityList->Player(), kMoveTo, GGame->CursorPosition());

		if (GPlugin->GetMenuOption("Q", "Flee")->Enabled() && GHero->GetSpell2("Q")->IsReady())
		{
			GHero->GetSpell2("Q")->CastOnPosition(GGame->CursorPosition());
		}

		if (GPlugin->GetMenuOption("E", "Flee")->Enabled() && GHero->GetSpell2("E")->IsReady())
		{
			GHero->GetSpell2("E")->CastOnTarget(GTargetSelector->FindTarget(ClosestPriority, PhysicalDamage, GHero->GetSpell2("E")->Range()), kHitChanceMedium);
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuOption("Q", "KillSteal")->Enabled() && GHero->GetSpell2("Q")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("Q")->Range()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotQ) < enemy->GetHealth())
				continue;

			if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
				continue;

			GHero->GetSpell2("Q")->CastOnTarget(enemy, kHitChanceHigh);
			break;
		}
	}

	if (GPlugin->GetMenuOption("E", "KillSteal")->Enabled() && GHero->GetSpell2("E")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("E")->Range()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotE) < enemy->GetHealth())
				continue;

			if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
				continue;

			GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceHigh);
			break;
		}
	}
}

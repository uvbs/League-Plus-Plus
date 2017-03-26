#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"

void Modes::Combo()
{
	if (GPlugin->GetMenuBoolean("Q", "Combo") && GHero->GetSpell2("Q")->IsReady())
	{
		GHero->GetSpell2("Q")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range()), kHitChanceHigh);
	}

	if (GPlugin->GetMenuBoolean("W", "Combo") && GHero->GetSpell("W")->IsReady())
	{
		if (GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() <= GPlugin->GetMenuInteger("W", "Combo.Heal"))
		{
			GHero->GetSpell("W")->CastOnPlayer();
		}
		else if (!GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() >  GPlugin->GetMenuInteger("W", "Combo.Heal"))
		{
			GHero->GetSpell("W")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("E", "Combo") && GHero->GetSpell2("E")->IsReady())
	{
		GHero->GetSpell2("E")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("E")->Range()), kHitChanceHigh);
	}

	if (GPlugin->GetMenuBoolean("R", "Combo") && GHero->GetSpell("R")->IsReady())
	{
		auto enemies = 0;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("R")->GetSpellRange()))
				continue;

			if (enemy->HealthPercent() <= GPlugin->GetMenuInteger("R", "Combo.Health"))
			{
				GHero->GetSpell("R")->CastOnPlayer();
				break;
			}

			enemies++;
		}

		if (enemies >= GPlugin->GetMenuInteger("R", "Combo.Enemies"))
		{
			GHero->GetSpell("R")->CastOnPlayer();
		}
	}
}

void Modes::Clear()
{
	if (GPlugin->GetMenuBoolean("Q", "Clear") && GHero->GetSpell2("Q")->IsReady())
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

	if (GPlugin->GetMenuBoolean("W", "Clear") && GHero->GetSpell("W")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
				continue;

			if (GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() <= GPlugin->GetMenuInteger("W", "Clear.Heal"))
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			else if (!GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() >  GPlugin->GetMenuInteger("W", "Clear.Heal"))
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			break;
		}
	}

	if (GPlugin->GetMenuBoolean("E", "Clear") && GHero->GetSpell2("E")->IsReady())
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
	if (GPlugin->GetMenuBoolean("Q", "Jungle") && GHero->GetSpell2("Q")->IsReady())
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

	if (GPlugin->GetMenuBoolean("W", "Jungle") && GHero->GetSpell("W")->IsReady())
	{
		for (auto minion : GEntityList->GetAllMinions(false, false, true))
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
				continue;

			if (GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() <= GPlugin->GetMenuInteger("W", "Jungle.Heal"))
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			else if (!GEntityList->Player()->HasBuff("AatroxWPower") && GEntityList->Player()->HealthPercent() >  GPlugin->GetMenuInteger("W", "Jungle.Heal"))
			{
				GHero->GetSpell("W")->CastOnPlayer();
			}
			break;
		}
	}

	if (GPlugin->GetMenuBoolean("E", "Jungle") && GHero->GetSpell2("E")->IsReady())
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
	if (GPlugin->GetMenuBoolean("E", "Harass") && GHero->GetSpell2("E")->IsReady())
	{
		GHero->GetSpell2("E")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("E")->Range()), kHitChanceMedium);
	}
}

void Modes::Flee()
{
	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Keys", "Flee")))
	{
		GGame->IssueOrder(GEntityList->Player(), kMoveTo, GGame->CursorPosition());

		if (GPlugin->GetMenuBoolean("Q", "Flee") && GHero->GetSpell2("Q")->IsReady())
		{
			GHero->GetSpell2("Q")->CastOnPosition(GGame->CursorPosition());
		}

		if (GPlugin->GetMenuBoolean("E", "Flee") && GHero->GetSpell2("E")->IsReady())
		{
			GHero->GetSpell2("E")->CastOnTarget(GTargetSelector->FindTarget(ClosestPriority, PhysicalDamage, GHero->GetSpell2("E")->Range()), kHitChanceMedium);
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuBoolean("Q", "KillSteal") && GHero->GetSpell2("Q")->IsReady())
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

	if (GPlugin->GetMenuBoolean("E", "KillSteal") && GHero->GetSpell2("E")->IsReady())
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

#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "SoTriistana.h"
#include "Extension.h"

void Modes::Combo()
{
	if (GPlugin->GetMenuOption("E", "Focus")->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GEntityList->Player()->AttackRange()))
				continue;

			if (!enemy->HasBuff("tristanaecharge"))
				continue;

			GTargetSelector->SetOverrideFocusedTarget(enemy);
			break;
		}
	}

	if (GPlugin->GetMenuOption("Q", "Combo")->Enabled() && GHero->GetSpell("Q")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GEntityList->Player()->AttackRange());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GEntityList->Player()->AttackRange()))
		{
			if (GPlugin->GetMenuOption("Q", "E.Check")->Enabled())
			{
				for (auto enemy : GEntityList->GetAllHeros(false, true))
				{
					if (enemy->IsDead())
						continue;

					if (!GEntityList->Player()->IsValidTarget(enemy, GEntityList->Player()->AttackRange()))
						continue;

					if (!enemy->HasBuff("tristanaecharge"))
						continue;

					GHero->GetSpell("Q")->CastOnPlayer();
					break;
				}
			} 
			else
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
	}

	if (GPlugin->GetMenuOption("E", "Combo")->Enabled() && GHero->GetSpell2("E")->IsReady())
	{
		auto ePriority = 0;
		IUnit* target = nullptr;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("E")->Range()))
				continue;

			if (!GPlugin->GetMenuOption("E.Whitelist", const_cast<char*>(enemy->ChampionName()))->Enabled())
				continue;

			if (GPlugin->GetMenuOption("E.Priority", const_cast<char*>(enemy->ChampionName()))->GetInteger() < ePriority)
				continue;

			ePriority = GPlugin->GetMenuOption("E.Priority", const_cast<char*>(enemy->ChampionName()))->GetInteger();
			target = enemy;
		}

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("E")->Range()))
			GHero->GetSpell2("E")->CastOnTarget(target);
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuOption("R", "Finisher")->Enabled() && GHero->GetSpell2("R")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("R")->Range()))
				continue;

			if (GPlugin->GetMenuOption("R", "E.Overkill")->Enabled() && SoTriistana::GetChargedDamage(enemy) > enemy->GetHealth())
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR) + GDamage->GetAutoAttackDamage(GEntityList->Player(), enemy, false) > enemy->GetHealth())
			{
				GHero->GetSpell2("R")->CastOnTarget(enemy);
				GGame->IssueOrder(GEntityList->Player(), kAttackUnit, enemy);
			}

			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR) > enemy->GetHealth())
			{
				GHero->GetSpell2("R")->CastOnTarget(enemy);
			}
		}
	}
}

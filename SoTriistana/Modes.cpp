#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "SoTriistana.h"

void Modes::Combo()
{
	if (GPlugin->GetMenuBoolean("E", "Focus"))
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

	if (GPlugin->GetMenuBoolean("Q", "Combo") && GHero->GetSpell("Q")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GEntityList->Player()->AttackRange());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GEntityList->Player()->AttackRange()))
		{
			if (GPlugin->GetMenuBoolean("Q", "E.Check"))
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

	if (GPlugin->GetMenuBoolean("E", "Combo") && GHero->GetSpell2("E")->IsReady())
	{
		auto ePriority = 0;
		IUnit* target = nullptr;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("E")->Range()))
				continue;

			if (!GPlugin->GetMenuBoolean("E.Whitelist", const_cast<char*>(enemy->ChampionName())))
				continue;

			if (GPlugin->GetMenuInteger("E.Priority", const_cast<char*>(enemy->ChampionName())) < ePriority)
				continue;

			ePriority = GPlugin->GetMenuInteger("E.Priority", const_cast<char*>(enemy->ChampionName()));
			target = enemy;
		}

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("E")->Range()))
			GHero->GetSpell2("E")->CastOnTarget(target);
	}
}

void Modes::Always()
{
	if (GetAsyncKeyState(GPlugin->GetMenuInteger("R", "Key")) && GHero->GetSpell2("R")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(static_cast<eTargetPriority>(GPlugin->GetMenuInteger("R", "Semi.Mode")), PhysicalDamage, GHero->GetSpell2("R")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("R")->Range()))
		{
			GHero->GetSpell2("R")->CastOnUnit(target);
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuBoolean("R", "Finisher") && GHero->GetSpell2("R")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			auto chargedDamage = SoTriistana::GetChargedDamage(enemy);

			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("R")->Range()))
				continue;

			if (GPlugin->GetMenuBoolean("R", "E.Overkill") && chargedDamage > enemy->GetHealth())
				continue;

			if (chargedDamage + GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR) + GDamage->GetAutoAttackDamage(GEntityList->Player(), enemy, false) > enemy->GetHealth())
			{
				GHero->GetSpell2("R")->CastOnTarget(enemy);
				GGame->IssueOrder(GEntityList->Player(), kAttackUnit, enemy);
			}
		}
	}
}

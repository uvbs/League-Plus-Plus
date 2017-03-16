#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "Extension.h"

void Modes::Combo()
{
	auto enemyInRange = false;
	auto enemyInLongRange = false;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (GEntityList->Player()->IsValidTarget(enemy, GEntityList->Player()->AttackRange()))
		{
			enemyInRange = true;
			break;
		}

		if (GEntityList->Player()->IsValidTarget(enemy, GEntityList->Player()->AttackRange() + 1000))
		{
			enemyInLongRange = true;
		}
	}

	if (!enemyInRange && enemyInLongRange)
	{
		for (auto minion : GEntityList->GetAllMinions(false, true, true))
		{
			if (GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
			{
				GOrbwalking->Orbwalk(minion, GGame->CursorPosition());
				break;
			}
		}
	}

	if (GPlugin->GetMenuOption("Q", "Combo")->Enabled() && GHero->GetSpell2("Q")->IsReady())
	{
		GHero->GetSpell2("Q")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range()), kHitChanceHigh);
	}
}

void Modes::Clear()
{
	if (GPlugin->GetMenuOption("Q", "Lasthit.Unkillable")->Enabled())
	{
		for (auto creep : GEntityList->GetAllMinions(false, true, false))
		{
			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell2("Q")->Range()))
				continue;

			if (GHealthPrediction->GetPredictedHealth(creep, kLaneClearPrediction, GGame->Time(), GHero->GetSpell2("Q")->GetDelay()) > GDamage->GetSpellDamage(GEntityList->Player(), creep, kSlotQ))
				continue;

			if (creep->HasBuff("kalistaexpungemarker"))
				continue;

			GHero->GetSpell2("Q")->CastOnTarget(creep, kHitChanceHigh);
		}
	}

	if (GPlugin->GetMenuOption("E", "Clear")->Enabled())
	{
		auto killableCreeps = 0;

		for (auto creep : GEntityList->GetAllMinions(false, true, false))
		{
			if (creep->IsDead())
				continue;

			if (!creep->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), creep, kSlotE) <= creep->GetHealth() + creep->HPRegenRate() * 2)
				continue;

			killableCreeps++;
		}

		if (killableCreeps >= GPlugin->GetMenuOption("E", "Clear.Minions")->GetInteger())
		{
			GHero->GetSpell("E")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuOption("E", "Harass")->Enabled())
	{
		IUnit* killableCreep = nullptr;

		for (auto creep : GEntityList->GetAllMinions(false, true, false))
		{
			if (creep->IsDead())
				continue;

			if (!creep->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), creep, kSlotE) < creep->GetHealth() + creep->HPRegenRate())
				continue;

			killableCreep = creep;
			break;
		}

		if (killableCreep != nullptr)
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (!enemy->HasBuff("kalistaexpungemarker"))
					continue;

				if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("E")->GetSpellRange()))
					continue;

				if (!GEntityList->Player()->IsValidTarget(killableCreep, GHero->GetSpell("E")->GetSpellRange()))
					continue;

				if (GDamage->GetSpellDamage(GEntityList->Player(), killableCreep, kSlotE) < killableCreep->GetHealth() + killableCreep->HPRegenRate())
					continue;

				GHero->GetSpell("E")->CastOnPlayer();
				killableCreep = nullptr;
				break;
			}
		}
	}
}

void Modes::Jungle()
{
	if (GPlugin->GetMenuOption("E", "Jungle")->Enabled())
	{
		for (auto creep : GEntityList->GetAllMinions(false, false, true))
		{
			if (creep->IsDead())
				continue;

			if (!creep->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), creep, kSlotE) <= creep->GetHealth() + creep->HPRegenRate() * 2)
				continue;

			GHero->GetSpell("E")->CastOnPlayer();
		}
	}
}

void Modes::Harass()
{
	if (GPlugin->GetMenuOption("Q", "Harass")->Enabled() && GHero->GetSpell2("Q")->IsReady())
	{
		GHero->GetSpell2("Q")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range()), kHitChanceMedium);
	}
}

void Modes::Always()
{
	auto dragonPosition = Vec3(9796.f, -71.f, 4432.f);
	auto baronPosition = Vec3(5064.f, -71.f, 10568.f);

	if (GetAsyncKeyState(GPlugin->GetMenuOption("W", "Dragon")->GetInteger()))
	{
		if (GExtension->GetDistance(GEntityList->Player()->GetPosition(), dragonPosition) <= GHero->GetSpell("W")->GetSpellRange())
		{
			GHero->GetSpell("W")->CastOnPosition(dragonPosition);
		}
	}

	if (GetAsyncKeyState(GPlugin->GetMenuOption("W", "Baron")->GetInteger()))
	{
		if (GExtension->GetDistance(GEntityList->Player()->GetPosition(), baronPosition) <= GHero->GetSpell("W")->GetSpellRange())
		{
			GHero->GetSpell("W")->CastOnPosition(baronPosition);
		}
	}

	if (GPlugin->GetMenuOption("R", "Save")->Enabled())
	{
		IUnit* soulboundChampion = nullptr;

		for (auto ally : GEntityList->GetAllHeros(true, false))
		{
			if (ally->HasBuff("kalistacoopstrikeally"))
			{
				soulboundChampion = ally;
			}
		}

		if (soulboundChampion != nullptr && soulboundChampion->HealthPercent() <= GPlugin->GetMenuOption("R", "Save.Health")->GetInteger() && GExtension->CountEnemiesInTargetRange(soulboundChampion, 500) > 0)
		{
			GHero->GetSpell("R")->CastOnPlayer();
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuOption("Q", "KillSteal")->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("Q")->Range()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotQ) <= enemy->GetHealth())
				continue;

			if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
				continue;

			GHero->GetSpell2("Q")->CastOnTarget(enemy, kHitChanceHigh);
		}
	}

	if (GPlugin->GetMenuOption("E", "Combo")->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (!enemy->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotE) <= enemy->GetHealth() + enemy->HPRegenRate() / 2)
				continue;

			if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
				continue;

			GHero->GetSpell("E")->CastOnPlayer();
		}
	}
}

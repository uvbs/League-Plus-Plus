#include "Kalista.h"

void sLogics::Q()
{
	if (Kalista::Extensions->IsComboing())
	{
		if (Kalista::Menu->QCombo->Enabled())
		{
			auto target = Kalista::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Kalista::Spells->Q->Range());

			if (Kalista::Player->IsValidTarget(target, Kalista::Spells->Q->Range()))
			{
				Kalista::Spells->Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}

	if (Kalista::Extensions->IsHarassing())
	{
		if (Kalista::Menu->QHarass->Enabled())
		{
			auto target = Kalista::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Kalista::Spells->Q->Range());

			if (Kalista::Player->IsValidTarget(target, Kalista::Spells->Q->Range()))
			{
				Kalista::Spells->Q->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}

	if (Kalista::Extensions->IsClearing())
	{
		if (Kalista::Menu->QLastHitUnkillable->Enabled())
		{
			for (auto creep : Kalista::SDK->GetEntityList()->GetAllMinions(false, true, false))
			{
				if (!Kalista::Player->IsValidTarget(creep, Kalista::Spells->Q->Range()))
					continue;

				if (Kalista::SDK->GetHealthPrediction()->GetPredictedHealth(creep, kLaneClearPrediction, Kalista::SDK->GetGame()->Time(), Kalista::Spells->Q->GetDelay()) > Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, creep, kSlotQ))
					continue;

				if (creep->HasBuff("kalistaexpungemarker"))
					continue;

				Kalista::Spells->Q->CastOnTarget(creep, kHitChanceHigh);
			}
		}
	}
}

void sLogics::W()
{
	auto dragonPosition = Vec3(9796.f, -71.f, 4432.f);
	auto baronPosition = Vec3(5064.f, -71.f, 10568.f);

	if (GetAsyncKeyState(Kalista::Menu->WDragonKey->GetInteger()))
	{
		if (Kalista::Extensions->GetDistance(Kalista::Player->GetPosition(), dragonPosition) <= Kalista::Spells->W->GetSpellRange())
		{
			Kalista::Spells->W->CastOnPosition(dragonPosition);
		}
	}

	if (GetAsyncKeyState(Kalista::Menu->WBaronKey->GetInteger()))
	{
		if (Kalista::Extensions->GetDistance(Kalista::Player->GetPosition(), baronPosition) <= Kalista::Spells->W->GetSpellRange())
		{
			Kalista::Spells->W->CastOnPosition(baronPosition);
		}
	}
}

void sLogics::E()
{
	if (Kalista::Menu->EStealJungle->Enabled() && !Kalista::Player->IsRecalling())
	{
		for (auto creep : Kalista::SDK->GetEntityList()->GetAllMinions(false, false, true))
		{
			if (creep->IsDead())
				continue;

			if (!creep->HasBuff("kalistaexpungemarker"))
				continue;
			
			if (Kalista::Extensions->GetDistance(Kalista::Player, creep) >= Kalista::Spells->E->GetSpellRange())
				continue;

			if (Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, creep, kSlotE) <= creep->GetHealth() + creep->HPRegenRate())
				continue;

			Kalista::Spells->E->CastOnPlayer();
		}
	}

	if (Kalista::Menu->ECombo->Enabled())
	{
		if (Kalista::Extensions->IsComboing())
		{
			if (Kalista::Menu->EOutOfRange->Enabled())
			{
				auto target = Kalista::SDK->CreateTargetSelector()->GetFocusedTarget();

				if (target != nullptr && target->IsValidTarget())
				{
					Vec3 FuturePosition;

					Kalista::SDK->GetPrediction()->GetFutureUnitPosition(target, 1, false, FuturePosition);

					if (Kalista::Extensions->GetDistance(Kalista::Player->GetPosition(), FuturePosition) >= Kalista::Spells->E->GetSpellRange())
					{
						if (Kalista::Extensions->GetDistance(Kalista::Player, target) < Kalista::Spells->E->GetSpellRange())
						{
							auto damage = Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, target, kSlotE);

							if (damage / target->GetHealth() >= Kalista::Menu->EOutOfRangeMinimum->GetInteger())
							{
								Kalista::Spells->E->CastOnPlayer();
							}
						}
					}
				}
			}

			if (Kalista::Menu->EBeforeDeath->Enabled())
			{
				if (Kalista::SDK->GetHealthPrediction()->GetPredictedHealth(Kalista::Player, kLaneClearPrediction, Kalista::SDK->GetGame()->Time(), 2) <= 0)
				{
					Kalista::Spells->E->CastOnPlayer();
				}
			}
		}

		for (auto enemy : Kalista::SDK->GetEntityList()->GetAllHeros(false, true))
		{
			if (!enemy->HasBuff("kalistaexpungemarker"))
				continue;

			if (Kalista::Extensions->GetDistance(Kalista::Player, enemy) >= Kalista::Spells->E->GetSpellRange())
				continue;

			if (Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, enemy, kSlotE) <= enemy->GetHealth() + enemy->HPRegenRate() / 2)
				continue;

			if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
				continue;
			
			Kalista::Spells->E->CastOnPlayer();
		}
	}

	if (Kalista::Extensions->IsFarming())
	{
		if (Kalista::Menu->ELaneClear->Enabled())
		{
			auto killableCreeps = 0;

			for (auto creep : Kalista::SDK->GetEntityList()->GetAllMinions(false, true, false))
			{
				if (creep->IsDead())
					continue;

				if (!creep->HasBuff("kalistaexpungemarker"))
					continue;

				if (Kalista::Extensions->GetDistance(Kalista::Player, creep) >= Kalista::Spells->E->GetSpellRange())
					continue;

				if (Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, creep, kSlotE) <= creep->GetHealth() + creep->HPRegenRate())
					continue;
					
				killableCreeps++;
			}

			if (killableCreeps >= Kalista::Menu->ELaneClearMinimum->GetInteger())
			{
				Kalista::Spells->E->CastOnPlayer();
			}
		}

		if (Kalista::Menu->EHarass->Enabled())
		{
			IUnit* killableCreep = nullptr;

			for (auto creep : Kalista::SDK->GetEntityList()->GetAllMinions(false, true, false))
			{
				if (creep->IsDead())
					continue;

				if (!creep->HasBuff("kalistaexpungemarker"))
					continue;

				if (Kalista::Extensions->GetDistance(Kalista::Player, creep) >= Kalista::Spells->E->GetSpellRange())
					continue;

				if (Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, creep, kSlotE) < creep->GetHealth() + creep->HPRegenRate())
					continue;

				killableCreep = creep;
				break;
			}

			if (killableCreep != nullptr)
			{
				for (auto enemy : Kalista::SDK->GetEntityList()->GetAllHeros(false, true))
				{
					if (!enemy->HasBuff("kalistaexpungemarker"))
						continue;

					if (Kalista::Extensions->GetDistance(Kalista::Player, enemy) >= Kalista::Spells->E->GetSpellRange())
						continue;

					if (Kalista::Extensions->GetDistance(Kalista::Player, killableCreep) >= Kalista::Spells->E->GetSpellRange())
						continue;

					if (Kalista::SDK->GetDamage()->GetSpellDamage(Kalista::Player, killableCreep, kSlotE) < killableCreep->GetHealth() + killableCreep->HPRegenRate())
						continue;

					Kalista::Spells->E->CastOnPlayer();
					killableCreep = nullptr;
					break;
				}
			}
		}
	}
}

void sLogics::R()
{
	if (!Kalista::Menu->RSaveAlly->Enabled())
		return;

	IUnit* soulboundChampion = nullptr;

	for (auto ally : Kalista::SDK->GetEntityList()->GetAllHeros(true, false))
	{
		if (ally->HasBuff("kalistacoopstrikeally"))
		{
			soulboundChampion = ally;
		}
	}

	if (soulboundChampion != nullptr && soulboundChampion->HealthPercent() <= Kalista::Menu->RSaveAllyHealth->GetInteger() && Kalista::Extensions->CountEnemiesInTargetRange(soulboundChampion, 500) > 0)
	{
		Kalista::Spells->R->CastOnPlayer();
	}
}
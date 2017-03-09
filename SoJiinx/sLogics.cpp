#include "Jinx.h"

void sLogics::Q()
{
	if (Jinx::HasFishbone())
	{
		auto target = Jinx::SDK->GetOrbwalking()->GetLastTarget();

		if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeLaneClear && Jinx::Player->ManaPercent() > Jinx::Menu->ManaQClear->GetInteger() && target && target->IsCreep())
		{

		}
		else if (target && target->IsHero())
		{
			Jinx::FishboneToMinigun(target);
		}
		else
		{
			if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() != kModeCombo && Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() != kModeNone)
			{
				Jinx::Spells->Q->CastOnPlayer();
			}
		}
	}
	else
	{
		auto target = Jinx::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, 525 + 40);

		if (target && target->IsValidTarget())
		{
			if (Jinx::Extensions->GetDistance(Jinx::Player, target) < Jinx::FishboneRange() + 525)
			{
				if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo && Jinx::Menu->QCombo->Enabled() && Jinx::Extensions->CountEnemiesInTargetRange(target, 250) + 1 >= Jinx::Menu->QComboAoE->GetInteger() && (Jinx::Player->ManaPercent() > Jinx::Menu->ManaQCombo->GetInteger() || GDamage->GetAutoAttackDamage(Jinx::Player, target, false) * Jinx::Menu->QKillableAutoAttacks->GetInteger() > target->GetHealth()))
				{
					Jinx::Spells->Q->CastOnPlayer();
				}

				if (Jinx::Extensions->IsFarming() && !Jinx::Player->IsWindingUp() && Jinx::Menu->QHarass->Enabled() && (Jinx::Player->ManaPercent() > Jinx::Menu->ManaQHarass->GetInteger() || GDamage->GetAutoAttackDamage(Jinx::Player, target, false) * Jinx::Menu->QKillableAutoAttacks->GetInteger() > target->GetHealth()))
				{
					Jinx::Spells->Q->CastOnPlayer();
				}
			}
		}
		else
		{
			if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo && Jinx::Player->ManaPercent() > Jinx::Menu->ManaQCombo->GetInteger())
			{
				Jinx::Spells->Q->CastOnPlayer();
			}
			else if (Jinx::Extensions->IsFarming() && !Jinx::Player->IsWindingUp() && Jinx::Menu->QFarmOutOfRange->Enabled() && Jinx::SDK->GetOrbwalking()->CanAttack())
			{
				for (auto minion : Jinx::SDK->GetEntityList()->GetAllMinions(false, true, false))
				{
					if (Jinx::Extensions->GetDistance(Jinx::Player, minion) < 525 + Jinx::FishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(Jinx::Player, minion, false) * 1.2 && Jinx::GetRealPowPowRange(minion) < Jinx::Extensions->GetRealDistance(Jinx::Player, minion) && 525 + Jinx::FishboneRange() < Jinx::Extensions->GetRealDistance(Jinx::Player, minion))
					{
						Jinx::SDK->GetOrbwalking()->SetOverrideTarget(minion);
						Jinx::Spells->Q->CastOnPlayer();

						return;
					}
				}
			}

			if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeLaneClear && Jinx::Player->ManaPercent() > Jinx::Menu->ManaQClear->GetInteger())
			{
				auto orbTarget = Jinx::SDK->GetOrbwalking()->GetLastTarget();

				if (orbTarget && orbTarget->IsCreep() && Jinx::Extensions->CountMinionsInTargetRange(orbTarget, 250) + 1 >= Jinx::Menu->QMinions->GetInteger())
				{
					Jinx::Spells->Q->CastOnPlayer();
				}
			}
		}
	}
}

void sLogics::W()
{
	if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo)
	{
		if (Jinx::Menu->WCombo->Enabled())
		{
			if (Jinx::Player->ManaPercent() > Jinx::Menu->ManaWCombo->GetInteger())
			{
				auto target = Jinx::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Jinx::Spells->W->Range());

				if (Jinx::Player->IsValidTarget(target, Jinx::Spells->W->Range()))
				{
					Jinx::Spells->W->CastOnTarget(target, Jinx::Menu->WHitchance->GetInteger() + 2);
				}
			}
		}
	}

	if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeMixed)
	{
		if (Jinx::Menu->WHarass->Enabled())
		{
			if (Jinx::Player->ManaPercent() > Jinx::Menu->ManaWHarass->GetInteger())
			{
				auto target = Jinx::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Jinx::Spells->W->Range());

				if (Jinx::Player->IsValidTarget(target, Jinx::Spells->W->Range()))
				{
					Jinx::Spells->W->CastOnTarget(target, Jinx::Menu->WHitchance->GetInteger() + 2);
				}
			}
		}
	}

	if (GetAsyncKeyState(Jinx::Menu->WSemiManual->GetInteger()))
	{
		auto target = Jinx::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Jinx::Spells->W->Range());

		if (Jinx::Player->IsValidTarget(target, Jinx::Spells->W->Range()))
		{
			Jinx::Spells->W->CastOnTarget(target, Jinx::Menu->WHitchance->GetInteger() + 2);
		}
	}

	if (Jinx::Menu->WKillSteal->Enabled())
	{
		for (auto enemy : Jinx::SDK->GetEntityList()->GetAllHeros(false, true))
		{
			if (enemy != nullptr && !enemy->IsDead())
			{
				auto damage = GDamage->GetSpellDamage(Jinx::Player, enemy, kSlotW);

				if (Jinx::Player->IsValidTarget(enemy, Jinx::Spells->W->Range()) && !enemy->IsInvulnerable())
				{
					if (enemy->GetHealth() <= damage)
					{
						Jinx::Spells->W->CastOnTarget(enemy, Jinx::Menu->WHitchance->GetInteger() + 2);
					}
				}
			}
		}
	}

	if (Jinx::Menu->WEpics->Enabled())
	{
		for (auto creep : Jinx::SDK->GetEntityList()->GetAllMinions(false, false, true))
		{
			if (Jinx::Extensions->GetDistance(Jinx::Player, creep) < Jinx::Spells->W->Range())
			{
				if (Jinx::Player->IsValidTarget(creep, Jinx::Spells->W->Range()))
				{
					if (std::string(creep->GetBaseSkinName()).compare(0, 10, "sru_dragon") == 0 || std::string(creep->GetBaseSkinName()).compare(0, 10, "SRU_Baron") == 0)
					{
						auto predictedHealth = Jinx::SDK->GetHealthPrediction()->GetPredictedHealth(creep, kLaneClearPrediction, GGame->Time(), 0.5f);

						if (predictedHealth < Jinx::SDK->GetDamage()->GetSpellDamage(Jinx::Player, creep, kSlotW))
						{
							Jinx::Spells->W->CastOnUnit(creep);
						}
					}
				}
			}
		}
	}
}

void sLogics::E()
{
	if (Jinx::SDK->GetOrbwalking()->GetOrbwalkingMode() == kModeCombo)
	{
		if (Jinx::Menu->ECombo->Enabled())
		{
			if (Jinx::Player->ManaPercent() > Jinx::Menu->ManaECombo->GetInteger())
			{
				if (Jinx::Player->IsMoving())
				{
					auto target = Jinx::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Jinx::Spells->E->Range());

					if (Jinx::Player->IsValidTarget(target, Jinx::Spells->E->Range()))
					{
						Jinx::Spells->E->CastOnTarget(target, kHitChanceMedium);
					}
				}
			}
		}
	}

	if (Jinx::Menu->ETeleport->Enabled())
	{
		if (Jinx::Player->ManaPercent() > Jinx::Menu->ManaE->GetInteger())
		{
			for (auto unit : Jinx::SDK->GetEntityList()->GetAllUnits())
			{
				if (Jinx::Extensions->GetDistance(Jinx::Player, unit) <= Jinx::Spells->E->Range()) {
					if (unit->GetObjectName() == "teleport_target" || unit->GetObjectName() == "Pantheon_GrandSkyfall_Jump")
					{
						Jinx::Spells->E->CastOnPosition(unit->GetPosition());
					}
				}
			}
		}
	}

	if (Jinx::Player->ManaPercent() > Jinx::Menu->ManaE->GetInteger())
	{
		for (auto enemy : Jinx::SDK->GetEntityList()->GetAllHeros(false, true))
		{
			Jinx::Spells->E->CastOnTargetAoE(enemy, Jinx::Menu->EAoE->GetInteger(), kHitChanceHigh);

			if (Jinx::Menu->ECC->Enabled())
			{
				Jinx::Spells->E->CastOnTarget(enemy, kHitChanceImmobile);
			}

			if (Jinx::Menu->EDash->Enabled())
			{
				Jinx::Spells->E->CastOnTarget(enemy, kHitChanceDashing);
			}

			if (Jinx::Menu->ESlow->Enabled())
			{
				if (enemy->MovementSpeed() < 250)
				{
					Jinx::Spells->E->CastOnTarget(enemy, kHitChanceHigh);
				}
			}
		}
	}
}

void sLogics::R()
{
	Jinx::Spells->R->SetOverrideRange(Jinx::Menu->RMaxRange->GetInteger());

	if (GetAsyncKeyState(Jinx::Menu->RSemiManual->GetInteger()))
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Jinx::Spells->R->Range());

		if (Jinx::Player->IsValidTarget(target, Jinx::Spells->R->Range()))
		{
			if (Jinx::Extensions->CountAlliesInTargetRange(target, Jinx::Menu->RKillStealAllies->GetInteger()) == 0)
			{
				if (Jinx::Menu->RSemiManualMode->GetInteger() == 0)
				{
					Jinx::Spells->R->CastOnTarget(target, kHitChanceHigh);
				}
				else
				{
					Jinx::Spells->R->CastOnTargetAoE(target, 2, kHitChanceHigh);
				}
			}
		}
	}

	if (Jinx::Menu->RKillSteal->Enabled())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr && !enemy->IsDead() && !enemy->IsInvulnerable())
			{
				auto predictedHealth = enemy->GetHealth() + enemy->HPRegenRate() * 2;
				auto damage = GDamage->GetSpellDamage(Jinx::Player, enemy, kSlotR);

				if (Jinx::Extensions->GetDistance(Jinx::Player, enemy) < 1500)
				{
					damage *= Jinx::Extensions->GetDistance(Jinx::Player, enemy) / 1500;
				}

				if (damage > predictedHealth)
				{
					if (Jinx::Extensions->CountAlliesInTargetRange(enemy, Jinx::Menu->RKillStealAllies->GetInteger()) == 0)
					{
						Jinx::Spells->R->CastOnTarget(enemy, kHitChanceHigh);
					}
				}
			}
		}
	}
}
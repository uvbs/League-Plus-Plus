#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "Extension.h"
#include "Jinx.h"

void Modes::Combo()
{
	if (Jinx::HasFishbone())
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target && target->IsHero())
		{
			Jinx::FishboneToMinigun(target);
		}
	}
	else
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 525 + 40);

		if (target && target->IsValidTarget())
		{
			if (GExtension->GetDistance(GEntityList->Player(), target) < Jinx::GetFishboneRange() + 525 && GExtension->GetDistance(GEntityList->Player(), target) > GEntityList->Player()->AttackRange())
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		} 
		else
		{
			if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuOption("Mana", "Q.Combo")->GetInteger())
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
	}

	if (GPlugin->GetMenuOption("W", "Combo")->Enabled() && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuOption("Mana", "W.Combo")->GetInteger() && GHero->GetSpell2("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("W")->Range());
		
		if (GExtension->GetDistance(GEntityList->Player(), target) >= GPlugin->GetMenuOption("W", "Combo.Range")->GetInteger())
		{
			GHero->GetSpell2("W")->CastOnTarget(target, GPlugin->GetMenuOption("W", "Hitchance")->GetInteger() + 2);
		}
	}

	if (GPlugin->GetMenuOption("E", "Combo")->Enabled() && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuOption("Mana", "E.Combo")->GetInteger() && GHero->GetSpell2("E")->IsReady() && GEntityList->Player()->IsMoving())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("E")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("E")->Range()))
		{
			auto& out = Vec3();
			GPrediction->GetFutureUnitPosition(target, GHero->GetSpell2("E")->GetDelay() + 0.15f, false, out);
			GHero->GetSpell2("E")->CastOnPosition(out);
		}
	}
}

void Modes::Clear()
{
	if (Jinx::HasFishbone())
	{
		auto target = GOrbwalking->GetLastTarget();

		if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuOption("Mana", "Q.Clear")->GetInteger() && target && target->IsCreep())
		{

		}
		else if (target && target->IsHero())
		{
			Jinx::FishboneToMinigun(target);
		}
		else
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GPlugin->GetMenuOption("Q", "Lasthit.OutOfRange")->Enabled() && GOrbwalking->CanAttack())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (GExtension->GetDistance(GEntityList->Player(), minion) < 525 + Jinx::GetFishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, false) * 1.2 && Jinx::GetRealPowPowRange(minion) < GExtension->GetRealDistance(GEntityList->Player(), minion) && 525 + Jinx::GetFishboneRange() < GExtension->GetRealDistance(GEntityList->Player(), minion))
				{
					GOrbwalking->SetOverrideTarget(minion);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}

		if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuOption("Mana", "Q.Clear")->GetInteger())
		{
			auto orbTarget = GOrbwalking->GetLastTarget();

			if (orbTarget && orbTarget->IsCreep() && GExtension->CountMinionsInTargetRange(orbTarget, 250) + 1 >= GPlugin->GetMenuOption("Q", "Clear.Minions")->GetInteger())
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
	}
}

void Modes::Lasthit()
{
	if (Jinx::HasFishbone())
	{
		GHero->GetSpell("Q")->CastOnPlayer();
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GPlugin->GetMenuOption("Q", "Lasthit.OutOfRange")->Enabled() && GOrbwalking->CanAttack())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (GExtension->GetDistance(GEntityList->Player(), minion) < 525 + Jinx::GetFishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, false) * 1.2 && Jinx::GetRealPowPowRange(minion) < GExtension->GetRealDistance(GEntityList->Player(), minion) && 525 + Jinx::GetFishboneRange() < GExtension->GetRealDistance(GEntityList->Player(), minion))
				{
					GOrbwalking->SetOverrideTarget(minion);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}
	}
}

void Modes::Harass()
{
	if (Jinx::HasFishbone())
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target && target->IsHero())
		{
			Jinx::FishboneToMinigun(target);
		}
		else
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GPlugin->GetMenuOption("Q", "Lasthit.OutOfRange")->Enabled() && GOrbwalking->CanAttack())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (GExtension->GetDistance(GEntityList->Player(), minion) < 525 + Jinx::GetFishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, false) * 1.2 && Jinx::GetRealPowPowRange(minion) < GExtension->GetRealDistance(GEntityList->Player(), minion) && 525 + Jinx::GetFishboneRange() < GExtension->GetRealDistance(GEntityList->Player(), minion))
				{
					GOrbwalking->SetOverrideTarget(minion);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}
	}

	if (GPlugin->GetMenuOption("W", "Harass")->Enabled() && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuOption("Mana", "W.Harass")->GetInteger() && GHero->GetSpell2("W")->IsReady())
	{
		GHero->GetSpell2("W")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("W")->Range()), GPlugin->GetMenuOption("W", "Hitchance")->GetInteger() + 2);
	}
}

void Modes::Always()
{
	if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuOption("Mana", "E.Auto")->GetInteger() && GHero->GetSpell2("E")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (GHero->GetSpell2("E")->CastOnTargetAoE(enemy, GPlugin->GetMenuOption("E", "Enemies")->GetInteger(), kHitChanceHigh))
				break;

			if (GPlugin->GetMenuOption("E", "OnCC")->Enabled())
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceImmobile))
					break;
			}

			if (GPlugin->GetMenuOption("E", "OnDash")->Enabled())
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceDashing))
					break;
			}

			if (GPlugin->GetMenuOption("E", "OnSlow")->Enabled() && enemy->MovementSpeed() < 250)
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceHigh))
					break;
			}
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuOption("W", "KillSteal")->Enabled() && GHero->GetSpell2("W")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr && !enemy->IsDead() && GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()) && !enemy->IsInvulnerable() && enemy->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW))
			{
				GHero->GetSpell2("W")->CastOnTarget(enemy, GPlugin->GetMenuOption("W", "Hitchance")->GetInteger() + 2);
			}
		}
	}

	if (GPlugin->GetMenuOption("W", "Epics")->Enabled() && GHero->GetSpell2("W")->IsReady())
	{
		for (auto creep : GEntityList->GetAllMinions(false, false, true))
		{
			if (GExtension->GetDistance(GEntityList->Player(), creep) < GHero->GetSpell2("W")->Range())
			{
				if (GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell2("W")->Range()))
				{
					if (std::string(creep->GetBaseSkinName()).compare(0, 10, "sru_dragon") == 0 || std::string(creep->GetBaseSkinName()).compare(0, 10, "SRU_Baron") == 0)
					{
						auto predictedHealth = GHealthPrediction->GetPredictedHealth(creep, kLaneClearPrediction, GGame->Time(), 0.5f);

						if (predictedHealth < GDamage->GetSpellDamage(GEntityList->Player(), creep, kSlotW))
						{
							GHero->GetSpell2("W")->CastOnUnit(creep);
						}
					}
				}
			}
		}
	}

	if (GPlugin->GetMenuOption("R", "KillSteal")->Enabled() && GHero->GetSpell2("R")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr && !enemy->IsDead() && GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("R")->Range()) && !enemy->IsInvulnerable())
			{
				auto predictedHealth = enemy->GetHealth() + enemy->HPRegenRate() * 2;
				auto damage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR);

				if (GExtension->GetDistance(GEntityList->Player(), enemy) < 1500)
				{
					damage *= GExtension->GetDistance(GEntityList->Player(), enemy) / 1500;
				}

				damage += (enemy->GetMaxHealth() - predictedHealth) * 0.25;

				if (damage > predictedHealth)
				{
					if (GExtension->CountAlliesInTargetRange(enemy, GPlugin->GetMenuOption("R", "KillSteal.Allies")->GetInteger()) == 0)
					{
						GHero->GetSpell2("R")->CastOnTarget(enemy, kHitChanceHigh);
					}
				}
			}
		}
	}
}

void Modes::Semi()
{
	if (GetAsyncKeyState(GPlugin->GetMenuOption("W", "Key")->GetInteger()) && GHero->GetSpell2("W")->IsReady())
	{
		GHero->GetSpell2("W")->CastOnTarget(GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("W")->Range()), GPlugin->GetMenuOption("W", "Hitchance")->GetInteger() + 2);
	}

	if (GetAsyncKeyState(GPlugin->GetMenuOption("R", "Key")->GetInteger()) && GHero->GetSpell2("R")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("R")->Range());

		if (GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("R")->Range()))
		{
			if (GPlugin->GetMenuOption("R", "Key.Mode")->GetInteger() == 0)
			{
				GHero->GetSpell2("R")->CastOnTarget(target, kHitChanceHigh);
			}
			else
			{
				GHero->GetSpell2("R")->CastOnTargetAoE(target, 2, kHitChanceHigh);
			}
		}
	}
}
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

		if (target != nullptr && target->IsValidTarget())
		{
			if (GExtension->GetRealDistance(GEntityList->Player(), target) < 525 && !GPlugin->GetMenuBoolean("Q", "Combo.Stacks") && GExtension->CountEnemiesInTargetRange(target, 250) < GPlugin->GetMenuInteger("Q", "Combo.Enemies"))
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}

			if (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Mana", "Q.Combo") && GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuInteger("Q", "Mana.Ignore") < target->GetHealth())
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}

			if (GPlugin->GetMenuBoolean("Q", "Combo.Stacks") && GEntityList->Player()->GetBuffCount("jinxqramp") < 3 && GExtension->GetRealDistance(GEntityList->Player(), target) < 525 || GExtension->GetRealDistance(GEntityList->Player(), target) < 525)
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
	}
	else
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target != nullptr && target->IsValidTarget() &&
			(GExtension->GetRealDistance(GEntityList->Player(), target) <= 525 + Jinx::GetFishboneRange() && 
				GExtension->GetRealDistance(GEntityList->Player(), target) > 525 || 
				GExtension->GetRealDistance(GEntityList->Player(), target) <= 525 + Jinx::GetFishboneRange() &&
				GExtension->GetRealDistance(GEntityList->Player(), target) > 525 &&
				GPlugin->GetMenuBoolean("Q", "Combo.Stacks") &&
				GEntityList->Player()->GetBuffCount("jinxqramp") == 3 || 
				GExtension->GetRealDistance(GEntityList->Player(), target) <= 525 + Jinx::GetFishboneRange() && 
				GExtension->CountEnemiesInTargetRange(target, 250) >= GPlugin->GetMenuInteger("Q", "Combo.Enemies") && 
				(GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Mana", "Q.Combo") || 
					GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuInteger("Q", "Mana.Ignore") > target->GetHealth())))
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("W", "Combo") && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Mana", "W.Combo") && GHero->GetSpell2("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(static_cast<eTargetPriority>(GPlugin->GetMenuInteger("W", "Target")), PhysicalDamage, GHero->GetSpell2("W")->Range());
		
		if (target != nullptr && GExtension->GetDistance(GEntityList->Player(), target) >= GPlugin->GetMenuInteger("W", "Combo.Range"))
		{
			GHero->GetSpell2("W")->CastOnTarget(target, GPlugin->GetMenuInteger("W", "Hitchance") + 2);
		}
	}

	if (GPlugin->GetMenuBoolean("E", "Combo") && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Mana", "E.Combo") && GHero->GetSpell2("E")->IsReady() && GEntityList->Player()->IsMoving())
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

		if (target != nullptr && target->IsCreep() && GExtension->CountMinionsInTargetRange(target, 250) + 1 >= GPlugin->GetMenuInteger("Q", "Clear.Minions") && GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Mana", "Q.Clear"))
		{

		}
		else if (target != nullptr && target->IsHero())
		{
			if (GExtension->GetRealDistance(GEntityList->Player(), target) < 525 && GExtension->CountEnemiesInTargetRange(target, 250) < GPlugin->GetMenuInteger("Q", "Combo.Enemies") || (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Mana", "Q.Combo") || GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuInteger("Q", "Mana.Ignore") < target->GetHealth()))
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
		else
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GPlugin->GetMenuBoolean("Q", "Lasthit.OutOfRange") && GOrbwalking->CanAttack())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (GExtension->GetDistance(GEntityList->Player(), minion) < 525 + Jinx::GetFishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, false) * 1.2 && 525 < GExtension->GetRealDistance(GEntityList->Player(), minion) && 525 + Jinx::GetFishboneRange() < GExtension->GetRealDistance(GEntityList->Player(), minion))
				{
					GOrbwalking->SetOverrideTarget(minion);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}

		if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Mana", "Q.Clear"))
		{
			auto orbTarget = GOrbwalking->GetLastTarget();

			if (orbTarget != nullptr && orbTarget->IsCreep() && GExtension->CountMinionsInTargetRange(orbTarget, 250) + 1 >= GPlugin->GetMenuInteger("Q", "Clear.Minions"))
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
		if (!GEntityList->Player()->IsWindingUp() && GPlugin->GetMenuBoolean("Q", "Lasthit.OutOfRange") && GOrbwalking->CanAttack())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (GExtension->GetDistance(GEntityList->Player(), minion) < 525 + Jinx::GetFishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, false) * 1.2 && 525 < GExtension->GetRealDistance(GEntityList->Player(), minion) && 525 + Jinx::GetFishboneRange() < GExtension->GetRealDistance(GEntityList->Player(), minion))
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

		if (target != nullptr && target->IsHero())
		{
			if (GExtension->GetRealDistance(GEntityList->Player(), target) < 525 && GExtension->CountEnemiesInTargetRange(target, 250) < GPlugin->GetMenuInteger("Q", "Combo.Enemies") || (GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Mana", "Q.Combo") || GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) * GPlugin->GetMenuInteger("Q", "Mana.Ignore") < target->GetHealth()))
			{
				GHero->GetSpell("Q")->CastOnPlayer();
			}
		}
		else
		{
			GHero->GetSpell("Q")->CastOnPlayer();
		}
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GPlugin->GetMenuBoolean("Q", "Lasthit.OutOfRange") && GOrbwalking->CanAttack())
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, false))
			{
				if (GExtension->GetDistance(GEntityList->Player(), minion) < 525 + Jinx::GetFishboneRange() && minion->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), minion, false) * 1.2 && 525 < GExtension->GetRealDistance(GEntityList->Player(), minion) && 525 + Jinx::GetFishboneRange() < GExtension->GetRealDistance(GEntityList->Player(), minion))
				{
					GOrbwalking->SetOverrideTarget(minion);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}
	}

	if (GPlugin->GetMenuBoolean("W", "Harass") && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Mana", "W.Harass") && GHero->GetSpell2("W")->IsReady())
	{
		GHero->GetSpell2("W")->CastOnTarget(GTargetSelector->FindTarget(static_cast<eTargetPriority>(GPlugin->GetMenuInteger("W", "Target")), PhysicalDamage, GHero->GetSpell2("W")->Range()), GPlugin->GetMenuInteger("W", "Hitchance") + 2);
	}
}

void Modes::Always()
{
	if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Mana", "E.Auto") && GHero->GetSpell2("E")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("E")->Range()))
				continue;

			if (GHero->GetSpell2("E")->CastOnTargetAoE(enemy, GPlugin->GetMenuInteger("E", "Enemies"), kHitChanceHigh))
				break;

			if (GPlugin->GetMenuBoolean("E", "OnCC"))
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceImmobile))
					break;
			}

			if (GPlugin->GetMenuBoolean("E", "OnDash"))
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceDashing))
					break;
			}

			if (GPlugin->GetMenuBoolean("E", "OnSlow") && enemy->MovementSpeed() < 250)
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceHigh))
					break;
			}
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuBoolean("W", "KillSteal") && GHero->GetSpell2("W")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr && !enemy->IsDead() && GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()) && !enemy->IsInvulnerable() && enemy->GetHealth() <= GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW))
			{
				if (GExtension->GetDistance(GEntityList->Player(), enemy) >= GPlugin->GetMenuInteger("W", "Combo.Range"))
				{
					GHero->GetSpell2("W")->CastOnTarget(enemy, GPlugin->GetMenuInteger("W", "Hitchance") + 2);
				}
			}
		}
	}

	if (GPlugin->GetMenuBoolean("W", "Epics") && GHero->GetSpell2("W")->IsReady())
	{
		for (auto creep : GEntityList->GetAllMinions(false, false, true))
		{
			if (creep->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell2("W")->Range()))
				continue;

			if (GExtension->GetMinionType(creep) & kMinionJungleEpic)
			{
				auto predictedHealth = GHealthPrediction->GetPredictedHealth(creep, kLaneClearPrediction, GGame->Time(), 0.5f);

				if (predictedHealth < GDamage->GetSpellDamage(GEntityList->Player(), creep, kSlotW))
				{
					GHero->GetSpell2("W")->CastOnTarget(creep);
				}
			}
		}
	}

	if (GPlugin->GetMenuBoolean("R", "KillSteal") && GHero->GetSpell2("R")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("R")->Range()))
				continue;

			if (GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()) && GPlugin->GetMenuBoolean("R", "KillSteal.W") && GHero->GetSpell2("W")->IsReady() && GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW) > enemy->GetHealth())
				continue;

			auto predictedHealth = enemy->GetHealth() + enemy->HPRegenRate() * 6;
			auto damage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR);

			if (GExtension->GetDistance(GEntityList->Player(), enemy) < 1500)
			{
				damage *= GExtension->GetDistance(GEntityList->Player(), enemy) / 1500;
			}

			damage += (enemy->GetMaxHealth() - predictedHealth) * 0.25;

			if (damage > predictedHealth)
			{
				if (GExtension->CountAlliesInTargetRange(enemy, GPlugin->GetMenuInteger("R", "KillSteal.Allies")) == 0)
				{
					GHero->GetSpell2("R")->CastOnTarget(enemy, kHitChanceHigh);
				}
			}
		}
	}
}

void Modes::Semi()
{
	if (GetAsyncKeyState(GPlugin->GetMenuInteger("W", "Key")) && GHero->GetSpell2("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(static_cast<eTargetPriority>(GPlugin->GetMenuInteger("W", "Target")), PhysicalDamage, GHero->GetSpell2("W")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("W")->Range()))
			GHero->GetSpell2("W")->CastOnTarget(target, GPlugin->GetMenuInteger("W", "Hitchance") + 2);
	}

	if (GetAsyncKeyState(GPlugin->GetMenuInteger("R", "Key")) && GHero->GetSpell2("R")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("R")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("R")->Range()))
		{
			if (GPlugin->GetMenuInteger("R", "Key.Mode") == 0)
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
#include "Modes.h"
#include "Plugin.h"
#include "Hero.h"
#include "Extension.h"
#include "SoJiinx.h"

void Modes::Combo()
{
	if (SoJiinx::HasFishbone())
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target == nullptr || target->IsDead() || !GPlugin->GetMenuBoolean("Combo", "Q") ||
			GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Combo", "Q.Mana") &&
			GPlugin->GetMenuInteger("Combo", "Q.Mana.Ignore") * GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) < target->GetHealth() ||
			(GExtension->GetDistance(GEntityList->Player(), target) < 525 &&
				GExtension->CountEnemiesInTargetRange(target, 200) + 1 < GPlugin->GetMenuInteger("Combo", "Q.Enemies") ||
				GExtension->GetDistance(GEntityList->Player(), target) < 525 && GPlugin->GetMenuBoolean("Combo", "Q.Enemies.Range"))) 
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}
	else
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target != nullptr && !target->IsDead() && GPlugin->GetMenuBoolean("Combo", "Q") && 
			(GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Combo", "Q.Mana") || 
				GPlugin->GetMenuInteger("Combo", "Q.Mana.Ignore") * GDamage->GetAutoAttackDamage(GEntityList->Player(), target, false) > target->GetHealth()) &&
			(GExtension->GetDistance(GEntityList->Player(), target) > 525 && GExtension->GetDistance(GEntityList->Player(), target) < 525 + SoJiinx::GetFishboneRange() || 
				GExtension->CountEnemiesInTargetRange(target, 200) + 1 >= GPlugin->GetMenuInteger("Combo", "Q.Enemies") && 
				(GExtension->GetDistance(GEntityList->Player(), target) > 525 || !GPlugin->GetMenuBoolean("Combo", "Q.Enemies.Range"))))
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("Combo", "W") && GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Combo", "W.Mana") && GHero->GetSpell2("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(static_cast<eTargetPriority>(GPlugin->GetMenuInteger("Combo", "W.Mode")), PhysicalDamage, GHero->GetSpell2("W")->Range());

		if (target != nullptr && GExtension->GetDistance(GEntityList->Player(), target) >= GPlugin->GetMenuInteger("Combo", "W.Range"))
		{
			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("W")->RunPrediction(target, false, GHero->GetSpell2("W")->GetCollisionFlags(), &predictionOutput);

			if (predictionOutput.HitChance >= GPlugin->GetMenuInteger("Misc", "W.Hitchance") + 3)
			{
				GHero->GetSpell2("W")->CastOnPosition(predictionOutput.CastPosition);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Combo", "E") && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Combo", "E.Mana") && 
		GHero->GetSpell2("E")->IsReady() && GEntityList->Player()->IsMoving())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("E")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("E")->Range()))
		{
			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("E")->RunPrediction(target, true, GHero->GetSpell2("E")->GetCollisionFlags(), &predictionOutput);

			if (predictionOutput.HitChance >= kHitChanceVeryHigh)
			{
				GHero->GetSpell2("E")->CastOnPosition(predictionOutput.CastPosition);
			}
		}
	}
}

void Modes::Clear()
{
	if (SoJiinx::HasFishbone())
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target == nullptr || target->IsDead() || !target->IsCreep() || !GPlugin->GetMenuBoolean("Clear", "Q") ||
			GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Clear", "Q.Mana") ||
			GExtension->CountMinionsInTargetRange(target, 200) + 1 < GPlugin->GetMenuInteger("Clear", "Q.Enemies") ||
			GExtension->GetDistance(GEntityList->Player(), target) > 525 + SoJiinx::GetFishboneRange())
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GOrbwalking->CanAttack() && GPlugin->GetMenuBoolean("Clear", "Q.Lasthit"))
		{
			for (auto creep : GEntityList->GetAllMinions(false, true, true))
			{
				if (GExtension->GetRealDistance(GEntityList->Player(), creep) > 525 && GExtension->GetDistance(GEntityList->Player(), creep) < 525 + SoJiinx::GetFishboneRange() && 
					!creep->IsDead() && creep->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), creep, false) * 1.2)
				{
					GOrbwalking->SetOverrideTarget(creep);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}

		auto target = GOrbwalking->GetLastTarget();

		if (target != nullptr && !target->IsDead() && target->IsCreep() && GPlugin->GetMenuBoolean("Clear", "Q") &&
			GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Clear", "Q.Mana") &&
			GExtension->CountMinionsInTargetRange(target, 200) + 1 >= GPlugin->GetMenuInteger("Clear", "Q.Enemies") &&
			GExtension->GetDistance(GEntityList->Player(), target) < 525 + SoJiinx::GetFishboneRange())
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
		else if (target != nullptr && !target->IsDead() && target->IsHero() && GPlugin->GetMenuBoolean("Harass", "Q") &&
			GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Harass", "Q.Mana") &&
			GExtension->GetDistance(GEntityList->Player(), target) < 525 + SoJiinx::GetFishboneRange())
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}
}

void Modes::Lasthit()
{
	if (SoJiinx::HasFishbone())
	{
		GHero->GetSpell("Q")->CastOnPlayer();
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GOrbwalking->CanAttack() && GPlugin->GetMenuBoolean("Clear", "Q.Lasthit"))
		{
			for (auto creep : GEntityList->GetAllMinions(false, true, true))
			{
				if (GExtension->GetRealDistance(GEntityList->Player(), creep) > 525 && GExtension->GetDistance(GEntityList->Player(), creep) < 525 + SoJiinx::GetFishboneRange() &&
					!creep->IsDead() && creep->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), creep, false) * 1.2)
				{
					GOrbwalking->SetOverrideTarget(creep);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}
	}
}

void Modes::Harass()
{
	if (SoJiinx::HasFishbone())
	{
		auto target = GOrbwalking->GetLastTarget();

		if (target == nullptr || !target->IsCreep() || !GPlugin->GetMenuBoolean("Clear", "Q") ||
			GEntityList->Player()->ManaPercent() < GPlugin->GetMenuInteger("Clear", "Q.Mana") ||
			GExtension->CountMinionsInTargetRange(target, 200) + 1 < GPlugin->GetMenuInteger("Clear", "Q.Enemies") ||
			GExtension->GetDistance(GEntityList->Player(), target) > 525 + SoJiinx::GetFishboneRange())
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}
	else
	{
		if (!GEntityList->Player()->IsWindingUp() && GOrbwalking->CanAttack() && GPlugin->GetMenuBoolean("Clear", "Q.Lasthit"))
		{
			for (auto creep : GEntityList->GetAllMinions(false, true, true))
			{
				if (GExtension->GetRealDistance(GEntityList->Player(), creep) > 525 && GExtension->GetDistance(GEntityList->Player(), creep) < 525 + SoJiinx::GetFishboneRange() &&
					!creep->IsDead() && creep->GetHealth() < GDamage->GetAutoAttackDamage(GEntityList->Player(), creep, false) * 1.2)
				{
					GOrbwalking->SetOverrideTarget(creep);
					GHero->GetSpell("Q")->CastOnPlayer();

					return;
				}
			}
		}

		auto target = GOrbwalking->GetLastTarget();

		if (target != nullptr && target->IsHero() && GPlugin->GetMenuBoolean("Harass", "Q") &&
			GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Harass", "Q.Mana") &&
			GExtension->GetDistance(GEntityList->Player(), target) < 525 + SoJiinx::GetFishboneRange())
		{
			GHero->GetSpell2("Q")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("Harass", "W") && GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("Harass", "W.Mana") && GHero->GetSpell2("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("W")->Range());

		if (target != nullptr)
		{
			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("W")->RunPrediction(target, false, GHero->GetSpell2("W")->GetCollisionFlags(), &predictionOutput);

			if (predictionOutput.HitChance >= GPlugin->GetMenuInteger("Misc", "W.Hitchance") + 3)
			{
				GHero->GetSpell2("W")->CastOnPosition(predictionOutput.CastPosition);
			}
		}
	}
}

void Modes::Always()
{
	if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("W.Auto", "Mana") && GHero->GetSpell2("W")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()))
				continue;

			if (GPlugin->GetMenuBoolean("W.Auto", "OnCC"))
			{
				if (GHero->GetSpell2("W")->CastOnTarget(enemy, kHitChanceImmobile))
					break;
			}

			if (GPlugin->GetMenuBoolean("W.Auto", "OnDash"))
			{
				if (GHero->GetSpell2("W")->CastOnTarget(enemy, kHitChanceDashing))
					break;
			}

			if (GPlugin->GetMenuBoolean("W.Auto", "OnSlow") && enemy->MovementSpeed() < 250)
			{
				if (GHero->GetSpell2("W")->CastOnTarget(enemy, kHitChanceHigh))
					break;
			}
		}
	}

	if (GEntityList->Player()->ManaPercent() > GPlugin->GetMenuInteger("E.Auto", "Mana") && GHero->GetSpell2("E")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("E")->Range()))
				continue;

			if (GPlugin->GetMenuBoolean("E.Auto", "OnArea") && GHero->GetSpell2("E")->CastOnTargetAoE(enemy, GPlugin->GetMenuInteger("E.Auto", "OnArea.Enemies"), kHitChanceHigh))
				break;

			if (GPlugin->GetMenuBoolean("E.Auto", "OnCC"))
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceImmobile))
					break;
			}

			if (GPlugin->GetMenuBoolean("E.Auto", "OnDash"))
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceDashing))
					break;
			}

			if (GPlugin->GetMenuBoolean("E.Auto", "OnSlow") && enemy->MovementSpeed() < 250)
			{
				if (GHero->GetSpell2("E")->CastOnTarget(enemy, kHitChanceHigh))
					break;
			}
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuBoolean("KillSteal", "W") && GHero->GetSpell2("W")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()))
				continue;

			if (enemy->IsInvulnerable())
				continue;
			
			if (GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW) < enemy->GetHealth())
				continue;

			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("W")->RunPrediction(enemy, false, GHero->GetSpell2("W")->GetCollisionFlags(), &predictionOutput);

			if (predictionOutput.HitChance >= GPlugin->GetMenuInteger("Misc", "W.Hitchance") + 3)
			{
				GHero->GetSpell2("W")->CastOnPosition(predictionOutput.CastPosition);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("KillSteal", "R") && GHero->GetSpell2("R")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()))
				continue;

			if (enemy->IsInvulnerable())
				continue;

			if (GExtension->CountAlliesInTargetRange(enemy, GPlugin->GetMenuInteger("KillSteal", "R.Allies")) > 0)
				continue;

			if (GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell2("W")->Range()) && GPlugin->GetMenuBoolean("KillSteal", "R.Overkill") && GHero->GetSpell2("W")->IsReady() && GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotW) > enemy->GetHealth())
				continue;

			auto predictedHealth = enemy->GetHealth() + enemy->HPRegenRate() * 6;
			auto damage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotR);

			if (GExtension->GetDistance(GEntityList->Player(), enemy) < 1500)
			{
				damage *= GExtension->GetDistance(GEntityList->Player(), enemy) / 1500;
			}

			damage += (enemy->GetMaxHealth() - predictedHealth) * 0.25;

			if (damage < predictedHealth)
				continue;

			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("R")->RunPrediction(enemy, false, GHero->GetSpell2("R")->GetCollisionFlags(), &predictionOutput);

			if (predictionOutput.HitChance >= kHitChanceHigh)
			{
				GHero->GetSpell2("R")->CastOnPosition(predictionOutput.CastPosition);
			}
		}
	}
}

void Modes::Semi()
{
	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Misc", "W.Key")) && GHero->GetSpell2("W")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("W")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("W")->Range()))
		{
			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("W")->RunPrediction(target, false, GHero->GetSpell2("W")->GetCollisionFlags(), &predictionOutput);

			if (predictionOutput.HitChance >= GPlugin->GetMenuInteger("Misc", "W.Hitchance") + 3)
			{
				GHero->GetSpell2("W")->CastOnPosition(predictionOutput.CastPosition);
			}
		}
	}

	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Misc", "R.Key")) && GHero->GetSpell2("R")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("R")->Range());

		if (target != nullptr && GEntityList->Player()->IsValidTarget(target, GHero->GetSpell2("R")->Range()))
		{
			AdvPredictionOutput predictionOutput;
			GHero->GetSpell2("R")->RunPrediction(target, true, GHero->GetSpell2("R")->GetCollisionFlags(), &predictionOutput);

			if (GPlugin->GetMenuInteger("Misc", "R.Key.Mode") == 0)
			{
				if (predictionOutput.HitChance >= kHitChanceHigh)
				{
					GHero->GetSpell2("R")->CastOnPosition(predictionOutput.CastPosition);
				}
			}
			else
			{
				if (predictionOutput.HitChance >= kHitChanceHigh && predictionOutput.AoETargetsHit.size() >= 2);
				{
					GHero->GetSpell2("R")->CastOnPosition(predictionOutput.CastPosition);
				}
			}
		}
	}
}
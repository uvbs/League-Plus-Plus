#include "Hero.h"
#include "SoKaliista.h"
#include "Plugin.h"
#include "Modes.h"
#include "Extension.h"
#include <numeric>
#include "Item.h"

void Modes::Combo()
{
	if (GPlugin->GetMenuBoolean("Cutlass", "Use.Combo") && GItem->GetItem(GItem->BilgewaterCutlass)->IsOwned() && GItem->GetItem(GItem->BilgewaterCutlass)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Cutlass", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->BilgewaterCutlass)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("Cutlass", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->BilgewaterCutlass)->CastOnTarget(enemy);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("BotRK", "Use.Combo") && GItem->GetItem(GItem->BladeoftheRuinedKing)->IsOwned() && GItem->GetItem(GItem->BladeoftheRuinedKing)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("BotRK", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->BladeoftheRuinedKing)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("BotRK", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->BladeoftheRuinedKing)->CastOnTarget(enemy);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Ghostblade", "Use.Combo") && GItem->GetItem(GItem->YoumuusGhostblade)->IsOwned() && GItem->GetItem(GItem->YoumuusGhostblade)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Ghostblade", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->YoumuusGhostblade)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("Ghostblade", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->YoumuusGhostblade)->CastOnPlayer();
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Combo", "Minions"))
	{
		auto enemyInRange = false;
		auto enemyInLongRange = false;
		IUnit* target = nullptr;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (GEntityList->Player()->IsValidTarget(enemy, GEntityList->Player()->AttackRange() + 50))
			{
				enemyInRange = true;
				break;
			}

			if (GEntityList->Player()->IsValidTarget(enemy, GPlugin->GetMenuInteger("Combo", "Minions.Range")))
			{
				target = enemy;
				enemyInLongRange = true;
			}
		}

		if (!enemyInRange && enemyInLongRange)
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, true))
			{
				if (GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
				{
					GOrbwalking->Orbwalk(minion, target->GetPosition());
					break;
				}
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Combo", "Q") && GHero->GetSpell2("Q")->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range());

		if (GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Combo", "Q.Mana") || GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ) > target->GetHealth() && GPlugin->GetMenuBoolean("Combo", "Q.Mana.Ignore"))
		{
			GHero->GetSpell2("Q")->CastOnTarget(target, kHitChanceHigh);
		}
	}

	if (GPlugin->GetMenuBoolean("Combo", "E"))
	{
		IUnit* killableMinion = nullptr;

		for (auto minion : GEntityList->GetAllMinions(false, true, true))
		{
			if (minion->IsDead())
				continue;

			if (!minion->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (SoKaliista::GetRendDamage(minion) < minion->GetHealth())
				continue;

			killableMinion = minion;
			break;
		}

		if (killableMinion != nullptr)
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (!enemy->HasBuff("kalistaexpungemarker") || enemy->GetBuffCount("kalistaexpungemarker") < GPlugin->GetMenuInteger("Combo", "E.Stacks"))
					continue;

				if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("E")->GetSpellRange()))
					continue;

				if (!GEntityList->Player()->IsValidTarget(killableMinion, GHero->GetSpell("E")->GetSpellRange()))
					continue;

				if (SoKaliista::GetRendDamage(killableMinion) < killableMinion->GetHealth())
					continue;

				if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
					continue;

				GHero->GetSpell("E")->CastOnPlayer();
				break;
			}
		}
	}
}

void Modes::Harass()
{
	if (GPlugin->GetMenuBoolean("Cutlass", "Use.Harass") && GItem->GetItem(GItem->BilgewaterCutlass)->IsOwned() && GItem->GetItem(GItem->BilgewaterCutlass)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Cutlass", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->BilgewaterCutlass)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("Cutlass", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->BilgewaterCutlass)->CastOnTarget(enemy);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("BotRK", "Use.Harass") && GItem->GetItem(GItem->BladeoftheRuinedKing)->IsOwned() && GItem->GetItem(GItem->BladeoftheRuinedKing)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("BotRK", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->BladeoftheRuinedKing)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("BotRK", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->BladeoftheRuinedKing)->CastOnTarget(enemy);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Ghostblade", "Use.Harass") && GItem->GetItem(GItem->YoumuusGhostblade)->IsOwned() && GItem->GetItem(GItem->YoumuusGhostblade)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Ghostblade", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->YoumuusGhostblade)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("Ghostblade", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->YoumuusGhostblade)->CastOnPlayer();
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Harass", "Q") && GHero->GetSpell2("Q")->IsReady() && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Harass", "Q.Mana"))
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, GHero->GetSpell2("Q")->Range());

		if (target != nullptr)
		{
			GHero->GetSpell2("Q")->CastOnTarget(target, kHitChanceHigh);
		}
	}
}

void Modes::Clear()
{
	if (GPlugin->GetMenuBoolean("Clear", "Q") && GHero->GetSpell2("Q")->IsReady() && GEntityList->Player()->ManaPercent() >= GPlugin->GetMenuInteger("Clear", "Q.Mana"))
	{
		Vec3 position;
		std::vector<IUnit*> minions;
		GPrediction->FindBestCastPositionEx(GEntityList->Player()->GetPosition(), GHero->GetSpell2("Q")->GetDelay(), GHero->GetSpell2("Q")->Range(), GHero->GetSpell2("Q")->Radius(), true, true, false, position, minions);
		auto minionsHit = 0;
		
		for (auto minion : minions)
		{
			if (minion->IsDead())
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell2("Q")->Range()))
				continue;

			if (GDamage->GetSpellDamage(GEntityList->Player(), minion, kSlotQ) < minion->GetHealth())
				continue;

			minionsHit++;
		}

		if (minionsHit >= GPlugin->GetMenuInteger("Clear", "Q.Minions"))
		{
			GHero->GetSpell2("Q")->CastOnPosition(position);
		}
	}

	if (GPlugin->GetMenuBoolean("Clear", "E") && GHero->GetSpell("E")->IsReady())
	{
		auto killableMinions = 0;

		for (auto minion : GEntityList->GetAllMinions(false, true, false))
		{
			if (minion->IsDead())
				continue;

			if (!minion->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (SoKaliista::GetRendDamage(minion) < minion->GetHealth())
				continue;

			killableMinions++;
		}

		if (killableMinions >= GPlugin->GetMenuInteger("Clear", "E.Minions"))
		{
			GHero->GetSpell("E")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("Harass", "E") && GHero->GetSpell("E")->IsReady())
	{
		IUnit* killableCreep = nullptr;

		for (auto creep : GEntityList->GetAllMinions(false, true, true))
		{
			if (creep->IsDead())
				continue;

			if (!creep->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (SoKaliista::GetRendDamage(creep) < creep->GetHealth())
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

				if (SoKaliista::GetRendDamage(enemy) < killableCreep->GetHealth() + killableCreep->HPRegenRate())
					continue;

				GHero->GetSpell("E")->CastOnPlayer();
				break;
			}
		}
	}
}
void Modes::Flee()
{
	if (GPlugin->GetMenuBoolean("Cutlass", "Use.Flee") && GItem->GetItem(GItem->BilgewaterCutlass)->IsOwned() && GItem->GetItem(GItem->BilgewaterCutlass)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Cutlass", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->BilgewaterCutlass)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("Cutlass", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->BilgewaterCutlass)->CastOnTarget(enemy);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("BotRK", "Use.Flee") && GItem->GetItem(GItem->BladeoftheRuinedKing)->IsOwned() && GItem->GetItem(GItem->BladeoftheRuinedKing)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("BotRK", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->BladeoftheRuinedKing)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("BotRK", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->BladeoftheRuinedKing)->CastOnTarget(enemy);
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Ghostblade", "Use.Flee") && GItem->GetItem(GItem->YoumuusGhostblade)->IsOwned() && GItem->GetItem(GItem->YoumuusGhostblade)->IsReady())
	{
		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Ghostblade", "Health"))
		{
			for (auto enemy : GEntityList->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (!GItem->GetItem(GItem->YoumuusGhostblade)->IsTargetInRange(enemy))
					continue;

				if (enemy->HealthPercent() >= GPlugin->GetMenuInteger("Ghostblade", "Enemy.Health"))
					continue;

				GItem->GetItem(GItem->YoumuusGhostblade)->CastOnPlayer();
			}
		}
	}

	if (SoKaliista::WallJumpTarget != Vec3(0, 0, 0))
	{
		GGame->IssueOrder(GEntityList->Player(), kMoveTo, SoKaliista::WallJumpTarget);

		if (GGame->TickCount() - SoKaliista::WallJumpTime > 500)
		{
			SoKaliista::WallJumpTarget = Vec3(0, 0, 0);
			SoKaliista::WallJumpTime = 0;
		}
		else
			return;
	}

	if (GPlugin->GetMenuBoolean("Flee", "Autoattack") && !GPlugin->GetMenuBoolean("Flee", "Walljump"))
	{
		for (auto minion : GEntityList->GetAllMinions(false, true, true))
		{
			if (GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
			{
				GOrbwalking->Orbwalk(minion, GGame->CursorPosition());
				return;
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Flee", "Walljump"))
	{
		auto wallCheck = SoKaliista::GetFirstWallPoint(GEntityList->Player()->GetPosition(), GGame->CursorPosition());

		if (wallCheck != Vec3(0, 0, 0))
			wallCheck = SoKaliista::GetFirstWallPoint(GEntityList->Player()->GetPosition(), GGame->CursorPosition(), 5);

		auto movePosition = wallCheck != Vec3(0, 0, 0) ? wallCheck : GGame->CursorPosition();
		IUnit* target = nullptr;

		if (GPlugin->GetMenuBoolean("Flee", "Autoattack"))
		{
			for (auto minion : GEntityList->GetAllMinions(false, true, true))
			{
				if (GEntityList->Player()->IsValidTarget(minion, GEntityList->Player()->AttackRange()))
				{
					target = minion;
					break;
				}
			}
		}

		SoKaliista::WallJumpPossible = false;

		if (GHero->GetSpell2("Q")->IsReady() && wallCheck != Vec3(0, 0, 0))
		{
			auto wallPosition = movePosition;
			auto direction = (GGame->CursorPosition() - wallPosition).VectorNormalize();
			auto maxAngle = 80.f;
			auto step = maxAngle / 20;
			auto currentAngle = 0.f;
			auto currentStep = 0.f;
			auto jumpTriggered = false;

			while (true)
			{
				if (currentStep > maxAngle && currentAngle < 0)
					break;

				if ((currentAngle == 0 || currentAngle < 0) && currentStep != 0)
				{
					currentAngle = (currentStep) * (float)acos(-1) / 180;
					currentStep += step;
				}
				else if (currentAngle > 0)
					currentAngle = -currentAngle;

				Vec3 checkPoint;

				if (currentStep == 0)
				{
					currentStep = step;
					checkPoint = wallPosition + 300 * direction;
				}
				else
				{
					auto c = cos(currentAngle);
					auto s = sin(currentAngle);
					checkPoint = wallPosition + 300 * Vec3(direction.x * c - direction.z * s, GNavMesh->GetHeightForPoint(Vec2(direction.x * c - direction.z * s, direction.z * c + direction.x * s)), direction.z * c + direction.x * s);
				}

				if (!GNavMesh->IsPointWall(checkPoint))
				{
					wallCheck = SoKaliista::GetFirstWallPoint(GEntityList->Player()->GetPosition(), GGame->CursorPosition());

					if (wallCheck != Vec3(0, 0, 0))
					{
						auto wallPositionOpposite = SoKaliista::GetFirstWallPoint(GEntityList->Player()->GetPosition(), GGame->CursorPosition(), 5);
						auto distance = 0.f;
						std::vector<Vec3> pathOut;

						GEntityList->Player()->CreatePath(wallPositionOpposite, pathOut);

						for (auto i = 0; i < pathOut.size() - 1; i++)
						{
							distance += GExtension->GetDistance(pathOut[i], pathOut[i + 1]);
						}

						if (distance - GExtension->GetDistance(GEntityList->Player()->GetPosition(), wallPositionOpposite) > 200)
						{
							if (GExtension->GetDistance(GEntityList->Player()->GetPosition(), wallPositionOpposite) < pow(300 - GEntityList->Player()->BoundingRadius() / 2, 2))
							{
								SoKaliista::WallJumpTime = GGame->TickCount();
								SoKaliista::WallJumpTarget = wallPositionOpposite;
								GHero->GetSpell2("Q")->CastOnPosition(wallPositionOpposite);

								jumpTriggered = true;
								break;
							}

							SoKaliista::WallJumpPossible = true;
						}
					}
				}
			}

			if (!jumpTriggered)
				GOrbwalking->Orbwalk(target, movePosition);
		}
		else
			GOrbwalking->Orbwalk(target, movePosition);
	}
}

void Modes::Always()
{
	auto dragonPosition = Vec3(9796.f, -71.f, 4432.f);
	auto baronPosition = Vec3(5064.f, -71.f, 10568.f);

	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Sentinel", "Dragon")) && GHero->GetSpell("W")->IsReady())
	{
		if (GExtension->GetDistance(GEntityList->Player()->GetPosition(), dragonPosition) <= GHero->GetSpell("W")->GetSpellRange())
		{
			GHero->GetSpell("W")->CastOnPosition(dragonPosition);
		}
	}

	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Sentinel", "Baron")) && GHero->GetSpell("W")->IsReady())
	{
		if (GExtension->GetDistance(GEntityList->Player()->GetPosition(), baronPosition) <= GHero->GetSpell("W")->GetSpellRange())
		{
			GHero->GetSpell("W")->CastOnPosition(baronPosition);
		}
	}

	if (GPlugin->GetMenuBoolean("Misc", "E.Death") && GHero->GetSpell("E")->IsReady())
	{
		auto heroes = 0;

		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (!enemy->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (enemy->GetBuffCount("kalistaexpungemarker") < GPlugin->GetMenuInteger("Misc", "E.Death.Stacks"))
				continue;

			heroes++;
		}

		if (GEntityList->Player()->HealthPercent() < GPlugin->GetMenuInteger("Misc", "E.Death.Health") && heroes >= GPlugin->GetMenuInteger("Misc", "E.Death.Heroes"))
		{
			GHero->GetSpell("E")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("Misc", "R.Save") && SoKaliista::Soulbound != nullptr && GHero->GetSpell("R")->IsReady())
	{
		if (SoKaliista::Soulbound->HealthPercent() < 5 && GExtension->CountEnemiesInTargetRange(SoKaliista::Soulbound, 500) > 0 || 
			std::accumulate(SoKaliista::SoulboundDamage.begin(), SoKaliista::SoulboundDamage.end(), 0, [](const size_t previous, decltype(*SoKaliista::SoulboundDamage.begin()) p) { return previous + p.second; }) > SoKaliista::Soulbound->GetHealth())
		{
			GHero->GetSpell("R")->CastOnPlayer();
		}
	}
}

void Modes::KillSteal()
{
	if (GPlugin->GetMenuBoolean("Jungle", "E") && GHero->GetSpell("E")->IsReady())
	{
		for (auto creep : GEntityList->GetAllMinions(false, false, true))
		{
			if (creep->IsDead())
				continue;

			if (!creep->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(creep, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (SoKaliista::GetRendDamage(creep) < creep->GetHealth())
				continue;

			if (!GPlugin->GetMenuBoolean("Jungle", "E.Small") && GExtension->GetMinionType(creep) & kMinionJungleSmall)
				continue;

			if (!GPlugin->GetMenuBoolean("Jungle", "E.Big") && GExtension->GetMinionType(creep) & kMinionJungleBig)
				continue;

			if (!GPlugin->GetMenuBoolean("Jungle", "E.Epics") && GExtension->GetMinionType(creep) & kMinionJungleEpic)
				continue;

			GHero->GetSpell("E")->CastOnPlayer();
		}
	}

	if (GPlugin->GetMenuBoolean("Misc", "E.Killsteal") && GHero->GetSpell("E")->IsReady())
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (!enemy->HasBuff("kalistaexpungemarker"))
				continue;

			if (!GEntityList->Player()->IsValidTarget(enemy, GHero->GetSpell("E")->GetSpellRange()))
				continue;

			if (SoKaliista::GetRendDamage(enemy) < enemy->GetHealth())
				continue;

			if (enemy->HasBuffOfType(BUFF_Invulnerability) || enemy->HasBuffOfType(BUFF_SpellShield) || enemy->HasBuff("Undying Rage") || enemy->HasBuff("kindrednodeathbuff") || enemy->HasBuff("JudicatorIntervention"))
				continue;

			GHero->GetSpell("E")->CastOnPlayer();
		}
	}
}
#include "Events.h"
#include "Plugin.h"
#include "Hero.h"
#include "Modes.h"
#include "Extension.h"
#include "SoKaliista.h"

void Events::Initialize()
{
	GPlugin->RegisterGameUpdateEvent(OnGameUpdate);
	GPlugin->RegisterRenderEvent(OnRender);
	GPlugin->RegisterSpellCastEvent(OnSpellCast);
	GPlugin->RegisterOrbwalkNonKillableMinionEvent(OnOrbwalkNonKillableMinion);
	GPlugin->RegisterLevelUpEvent(OnLevelUp);
}

void Events::OnGameUpdate()
{
	if (!GUtility->IsLeagueWindowFocused())
		return;

	if (GGame->IsChatOpen())
		return;

	if (SoKaliista::Soulbound == nullptr)
	{
		for (auto ally : GEntityList->GetAllHeros(true, false))
		{
			if (ally->HasBuff("kalistacoopstrikeally"))
			{
				SoKaliista::Soulbound = ally;
			}
		}
	} 
	else
	{
		for (auto incomingDamage : SoKaliista::SoulboundDamage)
		{
			if (incomingDamage.first < GGame->Time())
			{
				SoKaliista::SoulboundDamage.erase(incomingDamage.first);
			}
		}
	}

	if (GExtension->IsComboing())
	{
		Modes::Combo();
	}

	if (GExtension->IsHarassing())
	{
		Modes::Harass();
	}

	if (GExtension->IsClearing())
	{
		Modes::Clear();
	}

	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Flee", "Key")))
	{
		Modes::Flee();
	}

	Modes::Always();
	Modes::KillSteal();
}

void Events::OnRender()
{
	if (GetAsyncKeyState(GPlugin->GetMenuInteger("Flee", "Key")))
	{
		GRender->DrawCircle(SoKaliista::WallJumpTarget, 50, SoKaliista::WallJumpPossible ? Vec4(0, 128, 0, 255) : GHero->GetSpell2("Q")->IsReady() ? Vec4(255, 0, 0, 255) : Vec4(0, 128, 128, 255), 10);
	}

	if (GPlugin->GetMenuBoolean("Drawings", "Q") && (GHero->GetSpell2("Q")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "Q.Color"), GHero->GetSpell2("Q")->Range());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "W") && (GHero->GetSpell("W")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "W.Color"), GHero->GetSpell("W")->GetSpellRange());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "E") && (GHero->GetSpell("E")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "E.Color"), GHero->GetSpell("E")->GetSpellRange());
	}

	if (GPlugin->GetMenuBoolean("Drawings", "E.Leaving") && (GHero->GetSpell("E")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), GPlugin->GetMenuColor("Drawings", "E.Leaving.Color"), GHero->GetSpell("E")->GetSpellRange() - 200);
	}

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		auto stackCount = enemy->GetBuffCount("kalistaexpungemarker");
		
		if (enemy->IsDead() || !enemy->IsVisible() || stackCount == 0)
			continue;

		Vec3 worldToScreen;
		GGame->Projection(enemy->GetPosition(), &worldToScreen);

		if (GPlugin->GetMenuBoolean("Drawings", "E.Stacks"))
		{
			GRender->DrawTextW(Vec2(worldToScreen.x - 80, worldToScreen.y), Vec4(255, 255, 255, 255), "Stacks: %d", stackCount);
		}

		if (GPlugin->GetMenuBoolean("Drawings", "E.Damage"))
		{
			auto currentPercentage = ceil(SoKaliista::GetRendDamage(enemy) / enemy->GetHealth() * 100);

			GRender->DrawTextW(Vec2(worldToScreen.x, worldToScreen.y), currentPercentage >= 100 ? Vec4(139, 0, 0, 255) : Vec4(255, 255, 255, 255), currentPercentage >= 100 ? "Killable w/ E" : "%.1f%%", currentPercentage);
		}

		if (GPlugin->GetMenuBoolean("Drawings", "E.Damage.Healthbar"))
		{
			auto eDamage = GDamage->GetSpellDamage(GEntityList->Player(), enemy, kSlotE);

			if (eDamage > 0)
			{
				auto eDamagePercentage = (enemy->GetHealth() - eDamage) / enemy->GetMaxHealth();
				auto missingHealthPercentage = 100 - enemy->GetHealth() / enemy->GetMaxHealth() * 100;

				Vec2 barPosition;

				if (enemy->GetHPBarPosition(barPosition))
				{
					auto startPoint = Vec2(barPosition.x + 10 + eDamagePercentage * 104, barPosition.y + 9);
					auto size = Vec2(104 - eDamagePercentage * 104 - 104 * missingHealthPercentage / 100, 7.8f);

					GRender->DrawFilledBox(startPoint, size, GPlugin->GetMenuColor("Drawings", "E.Damage.Healthbar.Color"));
				}
			}
		}
	}

	if (GPlugin->GetMenuBoolean("Drawings", "R") && (GHero->GetSpell("R")->IsReady() || !GPlugin->GetMenuBoolean("Drawings", "Ready")))
	{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), GHero->GetSpell("R")->GetSpellRange());
	}
}

void Events::OnSpellCast(CastedSpell const& spell)
{
	if (!spell.Caster_->IsEnemy(GEntityList->Player()))
		return;

	if (SoKaliista::Soulbound == nullptr)
		return;

	if (spell.Target_->GetNetworkId() != SoKaliista::Soulbound->GetNetworkId())
		return;

	if (!GPlugin->GetMenuBoolean("Misc", "R.Save"))
		return;

	if (!spell.Caster_->IsHero() || spell.AutoAttack_)
	{
		SoKaliista::SoulboundDamage[GExtension->GetRealDistance(spell.Caster_, SoKaliista::Soulbound) / spell.Speed_ + GGame->Time()] = GDamage->GetAutoAttackDamage(spell.Caster_, SoKaliista::Soulbound, false);
	}
	else if (spell.Caster_->IsHero())
	{
		if (std::string(spell.Name_) == "SummonerDot")
		{
			SoKaliista::SoulboundDamage[GGame->Time() + 2] = GDamage->GetSummonerSpellDamage(spell.Caster_, SoKaliista::Soulbound, kSummonerSpellIgnite);
		} 
		else if (GExtension->GetDistance(spell.EndPosition_, SoKaliista::Soulbound->GetPosition()) < pow(GSpellData->GetRadius(spell.Data_), 2))
		{
			SoKaliista::SoulboundDamage[GGame->Time() + 2] = GDamage->GetSpellDamage(spell.Caster_, SoKaliista::Soulbound, GSpellData->GetSlot(spell.Data_));
		}
	}
}

void Events::OnOrbwalkNonKillableMinion(IUnit* minion)
{
	if (GPlugin->GetMenuBoolean("Misc", "E.Unkillable") && GHero->GetSpell("E")->IsReady() && GEntityList->Player()->IsValidTarget(minion, GHero->GetSpell("E")->GetSpellRange()) && minion->HasBuff("kalistaexpungemarker") && SoKaliista::GetRendDamage(minion) > minion->GetHealth())
	{
		GHero->GetSpell("E")->CastOnPlayer();
	}
}

void Events::OnLevelUp(IUnit* source, int newLevel)
{
	switch (newLevel)
	{
	case 6:
	case 11:
	case 16:
		source->LevelUpSpell(kSlotR);
		break;
	default:
		break;
	}
}
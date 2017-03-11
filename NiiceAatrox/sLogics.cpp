#include "Aatrox.h"

void sLogics::Q()
{
	if (GetAsyncKeyState(Aatrox::Menu->MiscFleeKey->GetInteger()))
	{
		if (Aatrox::Menu->QFlee->Enabled())
		{
			Aatrox::Spells->Q->CastOnPosition(Aatrox::SDK->GetGame()->CursorPosition());
		}
	}

	if (Aatrox::Menu->QKillSteal->Enabled())
	{
		for (auto enemy : Aatrox::SDK->GetEntityList()->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (Aatrox::Extensions->GetDistance(Aatrox::Player, enemy) > Aatrox::Spells->Q->Range())
				continue;

			if (Aatrox::SDK->GetDamage()->GetSpellDamage(Aatrox::Player, enemy, kSlotQ) < enemy->GetHealth())
				continue;

			Aatrox::Spells->Q->CastOnTarget(enemy, kHitChanceHigh);
		}
	}

	if (Aatrox::Extensions->IsComboing())
	{
		if (Aatrox::Menu->QCombo->Enabled())
		{
			auto target = Aatrox::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Aatrox::Spells->Q->Range());

			Aatrox::Spells->Q->CastOnTarget(target, kHitChanceHigh);
		}
	}

	if (Aatrox::Extensions->IsClearing())
	{
		if (Aatrox::Menu->QClear->Enabled())
		{
			for (auto creep : Aatrox::SDK->GetEntityList()->GetAllMinions(false, true, true))
			{
				if (creep->IsDead())
					continue;

				if (Aatrox::Extensions->GetDistance(Aatrox::Player, creep) > Aatrox::Spells->Q->Range())
					continue;

				Aatrox::Spells->Q->CastOnUnit(creep);
			}
		}
	}
}

void sLogics::W()
{
	if (Aatrox::Extensions->IsComboing())
	{
		if (Aatrox::Menu->WCombo->Enabled())
		{
			if (Aatrox::Player->HasBuff("AatroxWPower") && Aatrox::Player->HealthPercent() <= Aatrox::Menu->WComboHeal->GetInteger())
			{
				Aatrox::Spells->W->CastOnPlayer();
			} 
			else if (!Aatrox::Player->HasBuff("AatroxWPower") && Aatrox::Player->HealthPercent() > Aatrox::Menu->WClearHeal->GetInteger())
			{
				Aatrox::Spells->W->CastOnPlayer();
			}
		}
	}

	if (Aatrox::Extensions->IsClearing())
	{
		if (Aatrox::Menu->WClear->Enabled())
		{
			if (Aatrox::Player->HasBuff("AatroxWPower") && Aatrox::Player->HealthPercent() <= Aatrox::Menu->WClearHeal->GetInteger())
			{
				Aatrox::Spells->W->CastOnPlayer();
			}
			else if (!Aatrox::Player->HasBuff("AatroxWPower") && Aatrox::Player->HealthPercent() > Aatrox::Menu->WClearHeal->GetInteger())
			{
				Aatrox::Spells->W->CastOnPlayer();
			}
		}
	}
}

void sLogics::E()
{
	if (GetAsyncKeyState(Aatrox::Menu->MiscFleeKey->GetInteger()))
	{
		if (Aatrox::Menu->EFlee->Enabled())
		{
			auto target = Aatrox::SDK->CreateTargetSelector()->FindTarget(ClosestPriority, PhysicalDamage, Aatrox::Spells->E->Range());

			Aatrox::Spells->E->CastOnTarget(target, kHitChanceMedium);
		}
	}

	if (Aatrox::Extensions->IsHarassing())
	{
		if (Aatrox::Menu->EHarass->Enabled())
		{
			auto target = Aatrox::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Aatrox::Spells->E->Range());

			Aatrox::Spells->E->CastOnTarget(target, kHitChanceHigh);
		}
	}

	if (Aatrox::Menu->EKillSteal->Enabled())
	{
		for (auto enemy : Aatrox::SDK->GetEntityList()->GetAllHeros(false, true))
		{
			if (enemy->IsDead())
				continue;

			if (Aatrox::Extensions->GetDistance(Aatrox::Player, enemy) > Aatrox::Spells->E->Range())
				continue;

			if (Aatrox::SDK->GetDamage()->GetSpellDamage(Aatrox::Player, enemy, kSlotE) < enemy->GetHealth())
				continue;

			Aatrox::Spells->E->CastOnTarget(enemy, kHitChanceHigh);
		}
	}

	if (Aatrox::Extensions->IsComboing())
	{
		if (Aatrox::Menu->ECombo->Enabled())
		{
			auto target = Aatrox::SDK->CreateTargetSelector()->FindTarget(QuickestKill, PhysicalDamage, Aatrox::Spells->E->Range());

			Aatrox::Spells->E->CastOnTarget(target, kHitChanceHigh);
		}
	}

	if (Aatrox::Extensions->IsClearing())
	{
		if (Aatrox::Menu->EClear->Enabled())
		{
			for (auto creep : Aatrox::SDK->GetEntityList()->GetAllMinions(false, true, true))
			{
				if (creep->IsDead())
					continue;

				if (Aatrox::Extensions->GetDistance(Aatrox::Player, creep) > Aatrox::Spells->E->Range())
					continue;

				Aatrox::Spells->E->CastOnUnit(creep);
			}
		}
	}
}

void sLogics::R()
{
	if (Aatrox::Extensions->IsComboing())
	{
		if (Aatrox::Menu->RCombo->Enabled())
		{
			auto enemies = 0;

			for (auto enemy : Aatrox::SDK->GetEntityList()->GetAllHeros(false, true))
			{
				if (enemy->IsDead())
					continue;

				if (Aatrox::Extensions->GetDistance(Aatrox::Player, enemy) > Aatrox::Spells->R->GetSpellRange())
					continue;

				if (enemy->HealthPercent() <= Aatrox::Menu->RComboEnemyHealth->GetInteger())
				{
					Aatrox::Spells->R->CastOnPlayer();
					break;
				}

				enemies++;
			}

			if (enemies >= Aatrox::Menu->RComboEnemyCount->GetInteger())
			{
				Aatrox::Spells->R->CastOnPlayer();
			}
		}
	}
}
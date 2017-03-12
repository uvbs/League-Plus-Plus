#include "Riven.h"

void sLogics::Q()
{
	if (Riven::Menu->QKeep->Enabled())
	{
		if (Riven::Player->HasBuff("RivenTriCleave"))
		{
			if (Riven::SDK->GetBuffDataReader()->GetEndTime(Riven::Player->GetBuffDataByName("RivenTriCleave")) - Riven::SDK->GetGame()->Time() <= 0.25f)
			{
				if (!Riven::Player->IsRecalling() && !Riven::Player->GetSpellBook()->IsChanneling())
				{
					auto qPosition = Riven::Player->ServerPosition() + Riven::Player->Direction() * (Riven::Spells->Q->Range() + 100);

					if (Riven::Extensions->CountEnemiesInPositionRange(qPosition, 200) <= 1 && !Riven::SDK->GetUtility()->IsPositionUnderTurret(qPosition))
					{
						Riven::Spells->Q->CastOnPosition(Riven::SDK->GetGame()->CursorPosition());
					}
				}
			}
		}
	}
}

void sLogics::W()
{

}

void sLogics::E()
{

}

void sLogics::R()
{

}
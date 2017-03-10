#include "LeeSin.h"

void sLogics::Q()
{

}

void sLogics::W()
{

}

void sLogics::E()
{

}

void sLogics::R()
{
	if (GetAsyncKeyState(LeeSin::Menu->RFlash->GetInteger()))
	{
		auto target = LeeSin::SDK->CreateTargetSelector()->GetFocusedTarget();

		if (target != nullptr && target->IsValidTarget())
		{
			auto flashSlot = LeeSin::Player->GetSpellSlot("summonerflash");

			if (flashSlot != kSlotUnknown)
			{
				LeeSin::Spells->R->CastOnUnit(target);
				LeeSin::SDK->CreateSpell(flashSlot)->CastOnPosition(LeeSin::Player->GetPosition());
			}
		}
	}
}
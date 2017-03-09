#include "Kalista.h"

void sLogics::Q()
{

}

void sLogics::W()
{
	auto dragonPosition = Vec3(9796.f, 4432.f, -71.f);
	auto baronPosition = Vec3(5064.f, 10568.f, -71.f);

	if (!Kalista::Spells->W->IsReady())
		return;

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

}

void sLogics::R()
{
	
}
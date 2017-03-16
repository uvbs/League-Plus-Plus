#include "TwistedFate.h"

int TwistedFate::LastPingTick = 0;
int TwistedFate::CardPickTick = 0;

void TwistedFate::SelectCard(int card)
{
	if (CardPickTick == 0)
		CardPickTick = GGame->TickCount();

	CardSelector->StartSelecting(card);
}

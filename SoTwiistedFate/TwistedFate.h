#pragma once
#include "CardSelector.h"

class TwistedFate
{
public:
	static CardSelector* CardSelector;

	static int LastPingTick;
	static int CardPickTick;

	static void SelectCard(int card);
};


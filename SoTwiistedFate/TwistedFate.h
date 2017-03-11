#include "sExtensions.h"
#include "sLogics.h"
#include "sMenu.h"
#include "sSpells.h"
#include "sCardSelector.h"

class TwistedFate
{
public:
	static IPluginSDK* SDK;
	static sExtensions* Extensions;
	static IUnit* Player;
	static sMenu* Menu;
	static sSpells* Spells;
	static sLogics* Logics;
	static sCardSelector* CardSelector;

	static int LastPingTick;
	static int CardPickTick;

	static void SelectCard(int card);
};

inline void TwistedFate::SelectCard(int card)
{
	if (CardPickTick == 0)
		CardPickTick = SDK->GetGame()->TickCount();

	CardSelector->StartSelecting(card);
}
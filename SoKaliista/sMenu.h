#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenu* Draw;
	IMenuOption* DrawQ;
	IMenuOption* DrawW;
	IMenuOption* DrawE;
	IMenuOption* DrawEDamage;
	IMenuOption* DrawR;
	IMenuOption* DrawReady;

	IMenu* Q;
	IMenuOption* QCombo;
	IMenuOption* QComboMinion;
	IMenuOption* QHarass;
	IMenuOption* QClear;
	IMenuOption* QClearMinimum;
	IMenuOption* QFarmOutOfRange;

	IMenu* W;
	IMenuOption* WDragonKey;
	IMenuOption* WBaronKey;

	IMenu* E;
	IMenuOption* ECombo;
	IMenuOption* EBeforeDeath;
	IMenuOption* EOutOfRange;
	IMenuOption* EOutOfRangeMinimum;
	IMenuOption* EHarass;
	IMenuOption* ELastHit;
	IMenuOption* ELastHitUnkillable;
	IMenuOption* ELaneClear;
	IMenuOption* ELaneClearMinimum;

	IMenu* R;
	IMenuOption* RSaveAlly;
	IMenuOption* RSaveAllyHealth;
};
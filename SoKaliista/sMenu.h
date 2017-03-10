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
	IMenuOption* QHarass;
	IMenuOption* QLastHitUnkillable;

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
	IMenuOption* EStealJungle;

	IMenu* R;
	IMenuOption* RSaveAlly;
	IMenuOption* RSaveAllyHealth;
};
#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenu* Draw;
	IMenuOption* DrawW;
	IMenuOption* DrawE;
	IMenuOption* DrawR;
	IMenuOption* DrawReady;

	IMenu* Q;
	IMenuOption* QCombo;
	IMenuOption* QComboAoE;
	IMenuOption* QHarass;
	IMenuOption* QFarmOutOfRange;
	IMenuOption* QMinions;
	IMenuOption* QKillableAutoAttacks;

	IMenu* W;
	IMenuOption* WCombo;
	IMenuOption* WHarass;
	IMenuOption* WEpics;
	IMenuOption* WKillSteal;
	IMenuOption* WSemiManual;
	IMenuOption* WHitchance;

	IMenu* E;
	IMenuOption* ECombo;
	IMenuOption* ETeleport;
	IMenuOption* ECC;
	IMenuOption* ESlow;
	IMenuOption* EDash;
	IMenuOption* EGapCloser;
	IMenuOption* ESpecialSpell;
	IMenuOption* EAoE;

	IMenu* R;
	IMenuOption* RKillSteal;
	IMenuOption* RKillStealW;
	IMenuOption* RKillStealAllies;
	IMenuOption* RSemiManual;
	IMenuOption* RSemiManualMode;
	IMenuOption* RMaxRange;

	IMenu* Mana;
	IMenuOption* ManaQCombo;
	IMenuOption* ManaQHarass;
	IMenuOption* ManaQClear;
	IMenuOption* ManaWCombo;
	IMenuOption* ManaWHarass;
	IMenuOption* ManaECombo;
	IMenuOption* ManaE;
};
#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenu* Draw;
	IMenuOption* DrawQ;
	IMenuOption* DrawE;
	IMenuOption* DrawR;
	IMenuOption* DrawReady;

	IMenu* Q;
	IMenuOption* QCombo;
	IMenuOption* QClear;
	IMenuOption* QKillSteal;
	IMenuOption* QFlee;

	IMenu* W;
	IMenuOption* WCombo;
	IMenuOption* WComboHeal;
	IMenuOption* WClear;
	IMenuOption* WClearHeal;

	IMenu* E;
	IMenuOption* ECombo;
	IMenuOption* EHarass;
	IMenuOption* EClear;
	IMenuOption* EKillSteal;
	IMenuOption* EFlee;

	IMenu* R;
	IMenuOption* RCombo;
	IMenuOption* RComboEnemyHealth;
	IMenuOption* RComboEnemyCount;

	IMenu* Misc;
	IMenuOption* MiscFleeKey;
};
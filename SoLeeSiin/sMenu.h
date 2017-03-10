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
	IMenuOption* DrawR;
	IMenuOption* DrawInsec;
	IMenuOption* DrawInsecLines;
	IMenuOption* DrawReady;

	IMenu* Q;
	IMenuOption* QCombo;
	IMenuOption* Q2Combo;

	IMenu* W;
	IMenuOption* WCombo;
	IMenuOption* WJumpKey;
	IMenuOption* WJumpMouse;
	IMenuOption* WJumpMinions;
	IMenuOption* WJumpHeroes;

	IMenu* E;
	IMenuOption* ECombo;

	IMenu* R;
	IMenuOption* RCombo;
	IMenuOption* RFlash;
};
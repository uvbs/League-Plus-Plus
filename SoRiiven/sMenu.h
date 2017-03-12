#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenu* Draw;
	IMenuOption* DrawR;
	IMenuOption* DrawEngageRange;
	IMenuOption* DrawBurstRange;
	IMenuOption* DrawComboDamage;

	IMenu* Keys;
	IMenuOption* KeysFlee;
	IMenuOption* KeysBurst;

	IMenu* Q;
	IMenuOption* QKeep;
	IMenuOption* QGapclose;
	IMenuOption* QSafe;
	IMenuOption* QJungle;
	IMenuOption* QClear;

	IMenu* W;
	IMenuOption* WFlashBurst;
	IMenuOption* WCombo;
	IMenuOption* WInterrupt;
	IMenuOption* WGapCloser;
	IMenuOption* WJungle;
	IMenuOption* WClear;
	IMenuOption* WUnkillable;

	IMenu* E;
	IMenuOption* ECombo;
	IMenuOption* ESafe;
	IMenuOption* EJungle;
	IMenuOption* EClear;

	IMenu* R1;
	IMenuOption* R1Combo;
	IMenuOption* R1Mode;
	IMenuOption* R1Overkill;
	
	IMenu* R2;
	IMenuOption* R2Combo;
	IMenuOption* R2Hitchance;
	IMenuOption* R2Mode;
	IMenuOption* R2Keep;
};
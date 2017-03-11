#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenu* Draw;
	IMenuOption* DrawQ;
	IMenuOption* DrawR;
	IMenuOption* DrawReady;

	IMenu* Q;
	IMenuOption* QImmobile;
	IMenuOption* QDashing;
	IMenuOption* QSemiManual;

	IMenu* W;
	IMenuOption* WSelectYellow;
	IMenuOption* WSelectBlue;
	IMenuOption* WSelectRed;
	IMenuOption* WAutoYellowR;

	IMenu* R;
	IMenuOption* RPing;
};
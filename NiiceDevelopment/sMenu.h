#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenuOption* DrawGui;
	IMenuOption* GuiX;
	IMenuOption* GuiY;
	IMenuOption* DrawMouseLines;
	IMenuOption* DrawMouseInformations;
};
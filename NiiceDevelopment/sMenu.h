#include "PluginSDK.h"

class sMenu
{
public:
	explicit sMenu(IMenu* menu);

	IMenu* Main;

	IMenuOption* DrawHeroes;
	IMenuOption* DrawCreeps;
	IMenuOption* DrawJungleCreeps;
	IMenuOption* DrawTurrets;
	IMenuOption* DrawInformations;
	IMenuOption* DrawProperties;
	IMenuOption* DrawBuffs;
	IMenuOption* DrawExtendedBuffs;
	IMenuOption* DrawMouseLines;
	IMenuOption* DrawMouseInformations;
	IMenuOption* AnalyzeRange;
};
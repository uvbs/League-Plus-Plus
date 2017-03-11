#include "sExtensions.h"
#include "sLogics.h"
#include "sMenu.h"
#include "sSpells.h"

class Aatrox
{
public:
	static IPluginSDK* SDK;
	static sExtensions* Extensions;
	static IUnit* Player;
	static sMenu* Menu;
	static sSpells* Spells;
	static sLogics* Logics;
};
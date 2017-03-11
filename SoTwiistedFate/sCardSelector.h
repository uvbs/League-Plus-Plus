#include "PluginSDK.h"

class sCardSelector
{
public:
	static void StartSelecting(int card);
	static void OnGameUpdate();
	static void OnSpellCast(CastedSpell const& spell);

	enum Card {
		kCardYellow,
		kCardBlue,
		kCardRed,
		kCardNone
	};

	enum SelectStatus {
		kReady,
		kSelecting,
		kSelected,
		kCooldown
	};

	static int Select;
	static int Status;
};

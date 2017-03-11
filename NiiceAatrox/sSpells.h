#include "PluginSDK.h"

class sSpells
{
public:
	ISpell2* Q;
	ISpell*  W;
	ISpell2* E;
	ISpell*  R;

	void Create();
	void Initialize() const;
};
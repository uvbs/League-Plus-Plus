#include "PluginSDK.h"

class sSpells
{
public:
	ISpell2* Q;
	ISpell*  W;
	ISpell*  E;
	ISpell*  R;
	ISpell2* R2;

	void Create();
	void Initialize() const;
};
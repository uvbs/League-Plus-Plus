#include "PluginSDK.h"

class sSpells
{
public:
	ISpell*  Q;
	ISpell2* W;
	ISpell2* E;
	ISpell2* R;

	void Create();
	void Initialize() const;
};
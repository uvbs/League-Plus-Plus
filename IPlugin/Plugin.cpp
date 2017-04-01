#include "Plugin.h"
#include "Extension.h"

IPlugin* GPlugin;

char* IPlugin::Author;
char* IPlugin::Name;
int IPlugin::Version;
std::map<std::string, IMenu*> IPlugin::Menus;
std::map<std::string, std::map<std::string, IMenuOption*>> IPlugin::MenuOptions;

std::vector<std::function<void(IUnit*)>> IPlugin::OrbwalkBeforeAttackEvents;
std::vector<std::function<void(IUnit*, IUnit*)>> IPlugin::OrbwalkOnAttackEvents;
std::vector<std::function<void(IUnit*, IUnit*)>> IPlugin::OrbwalkAfterAttackEvents;
std::vector<std::function<void(IUnit*, IUnit*)>> IPlugin::OrbwalkTargetChangeEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::OrbwalkNonKillableMinionEvents;
std::vector<std::function<void()>> IPlugin::GameUpdateEvents;
std::vector<std::function<void()>> IPlugin::RenderEvents;
std::vector<std::function<void(CastedSpell const&)>> IPlugin::SpellCastEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::UnitDeathEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::CreateObjectEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::DestroyObjectEvents;
std::vector<std::function<void(CastedSpell const&)>> IPlugin::DoCastEvents;
std::vector<std::function<void(InterruptibleSpell const&)>> IPlugin::InterruptibleEvents;
std::vector<std::function<void(GapCloserSpell const&)>> IPlugin::GapCloserEvents;
std::vector<std::function<bool(IUnit*, eGameObjectOrder, Vec3*, IUnit*)>> IPlugin::IssueOrderEvents;
std::vector<std::function<void(IUnit*, void*)>> IPlugin::BuffAddEvents;
std::vector<std::function<void(IUnit*, void*)>> IPlugin::BuffRemoveEvents;
std::vector<std::function<void()>> IPlugin::GameEndEvents;
std::vector<std::function<void(IUnit*, int)>> IPlugin::LevelUpEvents;
std::vector<std::function<bool(eSpellSlot, IUnit*, Vec3*, Vec3*)>> IPlugin::PreCastEvents;
std::vector<std::function<IUnit*()>> IPlugin::OrbwalkFindTargetEvents;
std::vector<std::function<void(UnitDash*)>> IPlugin::DashEvents;
std::vector<std::function<void(IDirect3DDevice9*)>> IPlugin::D3DPresentEvents;
std::vector<std::function<void(IDirect3DDevice9*)>> IPlugin::D3DPreResetEvents;
std::vector<std::function<void(IDirect3DDevice9*)>> IPlugin::D3DPostResetEvents;
std::vector<std::function<void()>> IPlugin::RenderBehindHudEvents;
std::vector<std::function<bool(HWND, UINT, WPARAM, LPARAM)>> IPlugin::WndProcEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::EnterVisibleEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::ExitVisibleEvents;
std::vector<std::function<void(eSpellSlot, Vec3*, bool*, bool*)>> IPlugin::UpdateChargedSpellEvents;
std::vector<std::function<void(IUnit*, std::string const)>> IPlugin::PlayAnimationEvents;
std::vector<std::function<void(IUnit*)>> IPlugin::PauseAnimationEvents;
std::vector<std::function<void(JungleNotifyData*)>> IPlugin::JungleNotificationEvents;
std::vector<std::function<void(IUnit*, std::vector<Vec3> const&)>> IPlugin::NewPathEvents;
std::vector<std::function<void(OnTeleportArgs* args)>> IPlugin::TeleportEvents;

bool IPlugin::OrbwalkBeforeAttackEventHandlerAdded = false;
bool IPlugin::OrbwalkOnAttackEventHandlerAdded = false;
bool IPlugin::OrbwalkAfterAttackEventHandlerAdded = false;
bool IPlugin::OrbwalkTargetChangeEventHandlerAdded = false;
bool IPlugin::OrbwalkNonKillableMinionEventHandlerAdded = false;
bool IPlugin::GameUpdateEventHandlerAdded = false;
bool IPlugin::RenderEventHandlerAdded = false;
bool IPlugin::SpellCastEventHandlerAdded = false;
bool IPlugin::UnitDeathEventHandlerAdded = false;
bool IPlugin::CreateObjectEventHandlerAdded = false;
bool IPlugin::DestroyObjectEventHandlerAdded = false;
bool IPlugin::DoCastEventHandlerAdded = false;
bool IPlugin::InterruptibleEventHandlerAdded = false;
bool IPlugin::GapCloserEventHandlerAdded = false;
bool IPlugin::IssueOrderEventHandlerAdded = false;
bool IPlugin::BuffAddEventHandlerAdded = false;
bool IPlugin::BuffRemoveEventHandlerAdded = false;
bool IPlugin::GameEndEventHandlerAdded = false;
bool IPlugin::LevelUpEventHandlerAdded = false;
bool IPlugin::PreCastEventHandlerAdded = false;
bool IPlugin::OrbwalkFindTargetEventHandlerAdded = false;
bool IPlugin::DashEventHandlerAdded = false;
bool IPlugin::D3DPresentEventHandlerAdded = false;
bool IPlugin::D3DPreResetEventHandlerAdded = false;
bool IPlugin::D3DPostResetEventHandlerAdded = false;
bool IPlugin::RenderBehindHudEventHandlerAdded = false;
bool IPlugin::WndProcEventHandlerAdded = false;
bool IPlugin::EnterVisibleEventHandlerAdded = false;
bool IPlugin::ExitVisibleEventHandlerAdded = false;
bool IPlugin::UpdateChargedSpellEventHandlerAdded = false;
bool IPlugin::PlayAnimationEventHandlerAdded = false;
bool IPlugin::PauseAnimationEventHandlerAdded = false;
bool IPlugin::JungleNotificationEventHandlerAdded = false;
bool IPlugin::NewPathEventHandlerAdded = false;
bool IPlugin::TeleportEventHandlerAdded = false;

IPlugin::IPlugin(char* author, char* name, int version)
{
	Author = author;
	Name = name;
	Version = version;

	Menus["Main"] = GPluginSDK->AddMenu(name);
}

IPlugin::~IPlugin()
{
	for (auto menu : Menus)
	{
		menu.second->Remove();
	}

	GEventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkOnAttack, OnOrbwalkOnAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
	GEventManager->RemoveEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnUnitDeath, OnUnitDeath);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptible);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapCloser);
	GEventManager->RemoveEventHandler(kEventOnIssueOrder, OnIssueOrder);
	GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->RemoveEventHandler(kEventOnBuffRemove, OnBuffRemove);
	GEventManager->RemoveEventHandler(kEventOnGameEnd, OnGameEnd);
	GEventManager->RemoveEventHandler(kEventOnLevelUp, OnLevelUp);
	GEventManager->RemoveEventHandler(kEventOnPreCast, OnPreCast);
	GEventManager->RemoveEventHandler(kEventOrbwalkFindTarget, OnOrbwalkFindTarget);
	GEventManager->RemoveEventHandler(kEventOnDash, OnDash);
	GEventManager->RemoveEventHandler(kEventOnD3DPresent, OnD3DPresent);
	GEventManager->RemoveEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
	GEventManager->RemoveEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
	GEventManager->RemoveEventHandler(kEventOnRenderBehindHud, OnRenderBehindHud);
	GEventManager->RemoveEventHandler(kEventOnWndProc, OnWndProc);
	GEventManager->RemoveEventHandler(kEventOnEnterVisible, OnEnterVisible);
	GEventManager->RemoveEventHandler(kEventOnExitVisible, OnExitVisible);
	GEventManager->RemoveEventHandler(kEventOnUpdateChargedSpell, OnUpdateChargedSpell);
	GEventManager->RemoveEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->RemoveEventHandler(kEventOnPauseAnimation, OnPauseAnimation);
	GEventManager->RemoveEventHandler(kEventOnJungleNotification, OnJungleNotification);
	GEventManager->RemoveEventHandler(kEventOnNewPath, OnNewPath);
	GEventManager->RemoveEventHandler(kEventOnTeleport, OnTeleport);
}

char* IPlugin::GetAuthor()
{
	return Author;
}

char* IPlugin::GetName()
{
	return Name;
}

int IPlugin::GetVersion()
{
	return Version;
}

void IPlugin::AddMenu(std::string name, std::string title)
{
	Menus[name] = Menus["Main"]->AddMenu(title.c_str());
}

void IPlugin::AddMenu(std::string name, std::string title, std::string parentName)
{
	Menus[name] = Menus[parentName]->AddMenu(title.c_str());
}

void IPlugin::AddCheckBox(std::string menu, std::string name, std::string title, bool value)
{
	MenuOptions[menu][name] = Menus[menu]->CheckBox(title.c_str(), value);
}

void IPlugin::AddCheckBox(std::string name, std::string title, bool value)
{
	MenuOptions["Main"][name] = Menus["Main"]->CheckBox(title.c_str(), value);
}

// Credits: Tsuhgi (Had this briliant idea)
void IPlugin::AddToggle(std::string menu, std::string name, std::string title, bool value, int defaultKey)
{
	AddCheckBox(menu, name, title, value);
	AddKey(menu, name + ".ToggleKey", "^-> " + title + " - Toggle", defaultKey);

	RegisterGameUpdateEvent([=]() 
		{
			static auto previousState = false;
			auto currentState = GetAsyncKeyState(GetMenuInteger(menu, name + ".ToggleKey"));

			if (previousState && !currentState)
			{
				UpdateInteger(menu, name, !GetMenuBoolean(menu, name));
			}

			previousState = currentState;
		});
}

void IPlugin::AddToggle(std::string name, std::string title, bool value, int defaultKey)
{
	AddCheckBox(name, title, value);
	AddKey(name + ".ToggleKey", "^-> " + title + " - Toggle", defaultKey);

	RegisterGameUpdateEvent([=]() 
		{
			static auto previousState = false;
			auto currentState = GetAsyncKeyState(GetMenuInteger(name + ".ToggleKey"));

			if (previousState && !currentState)
			{
				UpdateInteger(name, !GetMenuBoolean(name));
			}

			previousState = currentState;
		});
}

void IPlugin::AddColor(std::string menu, std::string name, std::string title, DWORD value)
{
	MenuOptions[menu][name] = Menus[menu]->AddColor(title.c_str(), value);
}

void IPlugin::AddColor(std::string menu, std::string name, std::string title, float R, float G, float B, float A)
{
	MenuOptions[menu][name] = Menus[menu]->AddColor(title.c_str(), R, G, B, A);
}

void IPlugin::AddColor(std::string name, std::string title, DWORD value)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddColor(title.c_str(), value);
}

void IPlugin::AddColor(std::string name, std::string title, float R, float G, float B, float A)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddColor(title.c_str(), R, G, B, A);
}

void IPlugin::AddFloat(std::string menu, std::string name, std::string title, float minValue, float maxValue, float value)
{
	MenuOptions[menu][name] = Menus[menu]->AddFloat(title.c_str(), minValue, maxValue, value);
}

void IPlugin::AddFloat(std::string name, std::string title, float minValue, float maxValue, float value)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddFloat(title.c_str(), minValue, maxValue, value);
}

void IPlugin::AddInteger(std::string menu, std::string name, std::string title, int minValue, int maxValue, int value)
{
	MenuOptions[menu][name] = Menus[menu]->AddInteger(title.c_str(), minValue, maxValue, value);
}

void IPlugin::AddInteger(std::string name, std::string title, int minValue, int maxValue, int value)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddInteger(title.c_str(), minValue, maxValue, value);
}

void IPlugin::AddKey(std::string menu, std::string name, std::string title, int defaultKey)
{
	MenuOptions[menu][name] = Menus[menu]->AddKey(title.c_str(), defaultKey);
}

void IPlugin::AddKey(std::string name, std::string title, int defaultKey)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddKey(title.c_str(), defaultKey);
}

void IPlugin::AddSelection(std::string menu, std::string name, std::string title, int defaultIdx, std::vector<std::string> const& names)
{
	MenuOptions[menu][name] = Menus[menu]->AddSelection(title.c_str(), defaultIdx, names);
}

void IPlugin::AddSelection(std::string name, std::string title, int defaultIdx, std::vector<std::string> const& names)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddSelection(title.c_str(), defaultIdx, names);
}

void IPlugin::UpdateInteger(std::string menu, std::string name, int value)
{
	MenuOptions[menu][name]->UpdateInteger(value);
}

void IPlugin::UpdateInteger(std::string name, int value)
{
	MenuOptions["Main"][name]->UpdateInteger(value);
}

IMenu* IPlugin::GetMenu(std::string name)
{
	return Menus[name];
}

IMenu* IPlugin::GetMenu()
{
	return Menus["Main"];
}

bool IPlugin::MenuExists(std::string name)
{
	return Menus.count(name) == 1;
}

bool IPlugin::MenuOptionExists(std::string menu, std::string name)
{
	if (Menus.count(menu) == 0)
		return false;

	return MenuOptions[menu].count(name) == 1;
}

IMenuOption* IPlugin::GetMenuOption(std::string menu, std::string name)
{
	return MenuOptions[menu][name];
}

IMenuOption* IPlugin::GetMenuOption(std::string name)
{
	return MenuOptions["Main"][name];
}

bool IPlugin::GetMenuBoolean(std::string menu, std::string name)
{
	return MenuOptions[menu][name]->Enabled();
}

bool IPlugin::GetMenuBoolean(std::string name)
{
	return MenuOptions["Main"][name]->Enabled();
}

Vec4 IPlugin::GetMenuColor(std::string menu, std::string name)
{
	Vec4 color;
	MenuOptions[menu][name]->GetColor(&color);

	return color;
}

Vec4 IPlugin::GetMenuColor(std::string name)
{
	Vec4 color;
	MenuOptions["Main"][name]->GetColor(&color);

	return color;
}

float IPlugin::GetMenuFloat(std::string menu, std::string name)
{
	return MenuOptions[menu][name]->GetFloat();
}

float IPlugin::GetMenuFloat(std::string name)
{
	return MenuOptions["Main"][name]->GetFloat();
}

int IPlugin::GetMenuInteger(std::string menu, std::string name)
{
	return MenuOptions[menu][name]->GetInteger();
}

int IPlugin::GetMenuInteger(std::string name)
{
	return MenuOptions["Main"][name]->GetInteger();
}

void IPlugin::RegisterOrbwalkBeforeAttackEvent(std::function<void(IUnit*)> function)
{
	if (!OrbwalkBeforeAttackEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
		OrbwalkBeforeAttackEventHandlerAdded = true;
	}

	OrbwalkBeforeAttackEvents.push_back(function);
}

void IPlugin::RegisterOrbwalkOnAttackEvent(std::function<void(IUnit*, IUnit*)> function)
{
	if (!OrbwalkOnAttackEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOrbwalkOnAttack, OnOrbwalkOnAttack);
		OrbwalkOnAttackEventHandlerAdded = true;
	}

	OrbwalkOnAttackEvents.push_back(function);
}

void IPlugin::RegisterOrbwalkAfterAttackEvent(std::function<void(IUnit*, IUnit*)> function)
{
	if (!OrbwalkAfterAttackEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
		OrbwalkAfterAttackEventHandlerAdded = true;
	}

	OrbwalkAfterAttackEvents.push_back(function);
}

void IPlugin::RegisterOrbwalkTargetChangeEvent(std::function<void(IUnit*, IUnit*)> function)
{
	if (!OrbwalkTargetChangeEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
		OrbwalkTargetChangeEventHandlerAdded = true;
	}

	OrbwalkTargetChangeEvents.push_back(function);
}

void IPlugin::RegisterOrbwalkNonKillableMinionEvent(std::function<void(IUnit*)> function)
{
	if (!OrbwalkNonKillableMinionEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
		OrbwalkNonKillableMinionEventHandlerAdded = true;
	}

	OrbwalkNonKillableMinionEvents.push_back(function);
}

void IPlugin::RegisterGameUpdateEvent(std::function<void()> function)
{
	if (!GameUpdateEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
		GameUpdateEventHandlerAdded = true;
	}

	GameUpdateEvents.push_back(function);
}

void IPlugin::RegisterRenderEvent(std::function<void()> function)
{
	if (!RenderEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnRender, OnRender);
		RenderEventHandlerAdded = true;
	}

	RenderEvents.push_back(function);
}

void IPlugin::RegisterSpellCastEvent(std::function<void(CastedSpell const&)> function)
{
	if (!SpellCastEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnSpellCast, OnSpellCast);
		SpellCastEventHandlerAdded = true;
	}

	SpellCastEvents.push_back(function);
}

void IPlugin::RegisterUnitDeathEvent(std::function<void(IUnit*)> function)
{
	if (!UnitDeathEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnUnitDeath, OnUnitDeath);
		UnitDeathEventHandlerAdded = true;
	}

	UnitDeathEvents.push_back(function);
}

void IPlugin::RegisterCreateObjectEvent(std::function<void(IUnit*)> function)
{
	if (!CreateObjectEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
		CreateObjectEventHandlerAdded = true;
	}

	CreateObjectEvents.push_back(function);
}

void IPlugin::RegisterDestroyObjectEvent(std::function<void(IUnit*)> function)
{
	if (!DestroyObjectEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
		DestroyObjectEventHandlerAdded = true;
	}

	DestroyObjectEvents.push_back(function);
}

void IPlugin::RegisterDoCastEvent(std::function<void(CastedSpell const&)> function)
{
	if (!DoCastEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
		DoCastEventHandlerAdded = true;
	}

	DoCastEvents.push_back(function);
}

void IPlugin::RegisterInterruptibleEvent(std::function<void(InterruptibleSpell const&)> function)
{
	if (!InterruptibleEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
		InterruptibleEventHandlerAdded = true;
	}

	InterruptibleEvents.push_back(function);
}

void IPlugin::RegisterGapCloserEvent(std::function<void(GapCloserSpell const&)> function)
{
	if (!GapCloserEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
		GapCloserEventHandlerAdded = true;
	}

	GapCloserEvents.push_back(function);
}

void IPlugin::RegisterIssueOrderEvent(std::function<bool(IUnit*, eGameObjectOrder, Vec3*, IUnit*)> function)
{
	if (!IssueOrderEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnIssueOrder, OnIssueOrder);
		IssueOrderEventHandlerAdded = true;
	}

	IssueOrderEvents.push_back(function);
}

void IPlugin::RegisterBuffAddEvent(std::function<void(IUnit*, void*)> function)
{
	if (!BuffAddEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
		BuffAddEventHandlerAdded = true;
	}

	BuffAddEvents.push_back(function);
}

void IPlugin::RegisterBuffRemoveEvent(std::function<void(IUnit*, void*)> function)
{
	if (!BuffRemoveEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnBuffRemove, OnBuffRemove);
		BuffRemoveEventHandlerAdded = true;
	}

	BuffRemoveEvents.push_back(function);
}

void IPlugin::RegisterGameEndEvent(std::function<void()> function)
{
	if (!GameEndEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnGameEnd, OnGameEnd);
		GameEndEventHandlerAdded = true;
	}

	GameEndEvents.push_back(function);
}

void IPlugin::RegisterLevelUpEvent(std::function<void(IUnit*, int)> function)
{
	if (!LevelUpEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnLevelUp, OnLevelUp);
		LevelUpEventHandlerAdded = true;
	}

	LevelUpEvents.push_back(function);
}

void IPlugin::RegisterPreCastEvent(std::function<bool(eSpellSlot, IUnit*, Vec3*, Vec3*)> function)
{
	if (!PreCastEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnPreCast, OnPreCast);
		PreCastEventHandlerAdded = true;
	}

	PreCastEvents.push_back(function);
}

void IPlugin::RegisterOrbwalkFindTargetEvent(std::function<IUnit*()> function)
{
	if (!OrbwalkFindTargetEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOrbwalkFindTarget, OnOrbwalkFindTarget);
		OrbwalkFindTargetEventHandlerAdded = true;
	}

	OrbwalkFindTargetEvents.push_back(function);
}

void IPlugin::RegisterDashEvent(std::function<void(UnitDash*)> function)
{
	if (!DashEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnDash, OnDash);
		DashEventHandlerAdded = true;
	}

	DashEvents.push_back(function);
}

void IPlugin::RegisterD3DPresentEvent(std::function<void(IDirect3DDevice9*)> function)
{
	if (!D3DPresentEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnD3DPresent, OnD3DPresent);
		D3DPresentEventHandlerAdded = true;
	}

	D3DPresentEvents.push_back(function);
}

void IPlugin::RegisterD3DPreResetEvent(std::function<void(IDirect3DDevice9*)> function)
{
	if (!D3DPreResetEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
		D3DPreResetEventHandlerAdded = true;
	}

	D3DPreResetEvents.push_back(function);
}

void IPlugin::RegisterD3DPostResetEvent(std::function<void(IDirect3DDevice9*)> function)
{
	if (!D3DPostResetEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
		D3DPostResetEventHandlerAdded = true;
	}

	D3DPostResetEvents.push_back(function);
}

void IPlugin::RegisterRenderBehindHudEvent(std::function<void()> function)
{
	if (!RenderBehindHudEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnRenderBehindHud, OnRenderBehindHud);
		RenderBehindHudEventHandlerAdded = true;
	}

	RenderBehindHudEvents.push_back(function);
}

void IPlugin::RegisterWndProcEvent(std::function<bool(HWND, UINT, WPARAM, LPARAM)> function)
{
	if (!WndProcEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnWndProc, OnWndProc);
		WndProcEventHandlerAdded = true;
	}

	WndProcEvents.push_back(function);
}

void IPlugin::RegisterEnterVisibleEvent(std::function<void(IUnit*)> function)
{
	if (!EnterVisibleEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnEnterVisible, OnEnterVisible);
		EnterVisibleEventHandlerAdded = true;
	}

	EnterVisibleEvents.push_back(function);
}

void IPlugin::RegisterExitVisibleEvent(std::function<void(IUnit*)> function)
{
	if (!ExitVisibleEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnExitVisible, OnExitVisible);
		ExitVisibleEventHandlerAdded = true;
	}

	ExitVisibleEvents.push_back(function);
}

void IPlugin::RegisterUpdateChargedSpellEvent(std::function<void(eSpellSlot, Vec3*, bool*, bool*)> function)
{
	if (!UpdateChargedSpellEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnUpdateChargedSpell, OnUpdateChargedSpell);
		UpdateChargedSpellEventHandlerAdded = true;
	}

	UpdateChargedSpellEvents.push_back(function);
}

void IPlugin::RegisterPlayAnimationEvent(std::function<void(IUnit*, std::string const)> function)
{
	if (!PlayAnimationEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
		PlayAnimationEventHandlerAdded = true;
	}

	PlayAnimationEvents.push_back(function);
}

void IPlugin::RegisterPauseAnimationEvent(std::function<void(IUnit*)> function)
{
	if (!PauseAnimationEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnPauseAnimation, OnPauseAnimation);
		PauseAnimationEventHandlerAdded = true;
	}

	PauseAnimationEvents.push_back(function);
}

void IPlugin::RegisterJungleNotificationEvent(std::function<void(JungleNotifyData*)> function)
{
	if (!JungleNotificationEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnJungleNotification, OnJungleNotification);
		JungleNotificationEventHandlerAdded = true;
	}

	JungleNotificationEvents.push_back(function);
}

void IPlugin::RegisterNewPathEvent(std::function<void(IUnit*, std::vector<Vec3> const&)> function)
{
	if (!NewPathEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnNewPath, OnNewPath);
		NewPathEventHandlerAdded = true;
	}

	NewPathEvents.push_back(function);
}

void IPlugin::RegisterTeleportEvent(std::function<void(OnTeleportArgs* argHandlerAdded)> function)
{
	if (!TeleportEventHandlerAdded)
	{
		GEventManager->AddEventHandler(kEventOnTeleport, OnTeleport);
		TeleportEventHandlerAdded = true;
	}

	TeleportEvents.push_back(function);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkBeforeAttack(IUnit* target)
{
	for (auto event : OrbwalkBeforeAttackEvents)
		event(target);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkOnAttack(IUnit* source, IUnit* target)
{
	for (auto event : OrbwalkOnAttackEvents)
		event(source, target);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkAfterAttack(IUnit* source, IUnit* target)
{
	for (auto event : OrbwalkAfterAttackEvents)
		event(source, target);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkTargetChange(IUnit* oldTarget, IUnit* newTarget)
{
	for (auto event : OrbwalkTargetChangeEvents)
		event(oldTarget, newTarget);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkNonKillableMinion(IUnit* minion)
{
	for (auto event : OrbwalkNonKillableMinionEvents)
		event(minion);
}

PLUGIN_EVENTD(void) IPlugin::OnGameUpdate()
{
	for (auto event : GameUpdateEvents)
		event();
}

PLUGIN_EVENTD(void) IPlugin::OnRender()
{
	for (auto event : RenderEvents)
		event();
}

PLUGIN_EVENTD(void) IPlugin::OnSpellCast(CastedSpell const& spell)
{
	for (auto event : SpellCastEvents)
		event(spell);
}

PLUGIN_EVENTD(void) IPlugin::OnUnitDeath(IUnit* source)
{
	for (auto event : UnitDeathEvents)
		event(source);
}

PLUGIN_EVENTD(void) IPlugin::OnCreateObject(IUnit* source)
{
	for (auto event : CreateObjectEvents)
		event(source);
}

PLUGIN_EVENTD(void) IPlugin::OnDestroyObject(IUnit* source)
{
	for (auto event : DestroyObjectEvents)
		event(source);
}

PLUGIN_EVENTD(void) IPlugin::OnDoCast(CastedSpell const& spell)
{
	for (auto event : DoCastEvents)
		event(spell);
}

PLUGIN_EVENTD(void) IPlugin::OnInterruptible(InterruptibleSpell const& spell)
{
	for (auto event : InterruptibleEvents)
		event(spell);
}

PLUGIN_EVENTD(void) IPlugin::OnGapCloser(GapCloserSpell const& spell)
{
	for (auto event : GapCloserEvents)
		event(spell);
}

PLUGIN_EVENTD(bool) IPlugin::OnIssueOrder(IUnit* source, eGameObjectOrder orderIdx, Vec3* position, IUnit* target)
{
	for (auto event : IssueOrderEvents)
		event(source, orderIdx, position, target);

	return true;
}

PLUGIN_EVENTD(void) IPlugin::OnBuffAdd(IUnit* source, void* buffData)
{
	for (auto event : BuffAddEvents)
		event(source, buffData);
}

PLUGIN_EVENTD(void) IPlugin::OnBuffRemove(IUnit* source, void* buffData)
{
	for (auto event : BuffRemoveEvents)
		event(source, buffData);
}

PLUGIN_EVENTD(void) IPlugin::OnGameEnd()
{
	for (auto event : GameEndEvents)
		event();
}

PLUGIN_EVENTD(void) IPlugin::OnLevelUp(IUnit* source, int newLevel)
{
	for (auto event : LevelUpEvents)
		event(source, newLevel);
}

PLUGIN_EVENTD(bool) IPlugin::OnPreCast(eSpellSlot slot, IUnit* target, Vec3* startPosition, Vec3* endPosition)
{
	for (auto event : PreCastEvents)
		event(slot, target, startPosition, endPosition);

	return true;
}

PLUGIN_EVENTD(IUnit*) IPlugin::OnOrbwalkFindTarget()
{
	for (auto event : OrbwalkFindTargetEvents)
		event();

	return nullptr;
}

PLUGIN_EVENTD(void) IPlugin::OnDash(UnitDash* dash)
{
	for (auto event : DashEvents)
		event(dash);
}

PLUGIN_EVENTD(void) IPlugin::OnD3DPresent(IDirect3DDevice9* device)
{
	for (auto event : D3DPresentEvents)
		event(device);
}

PLUGIN_EVENTD(void) IPlugin::OnD3DPreReset(IDirect3DDevice9* device)
{
	for (auto event : D3DPreResetEvents)
		event(device);
}

PLUGIN_EVENTD(void) IPlugin::OnD3DPostReset(IDirect3DDevice9* device)
{
	for (auto event : D3DPostResetEvents)
		event(device);
}

PLUGIN_EVENTD(void) IPlugin::OnRenderBehindHud()
{
	for (auto event : RenderBehindHudEvents)
		event();
}

PLUGIN_EVENTD(bool) IPlugin::OnWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	for (auto event : WndProcEvents)
		event(hwnd, message, wParam, lParam);

	return false;
}

PLUGIN_EVENTD(void) IPlugin::OnEnterVisible(IUnit* source)
{
	for (auto event : EnterVisibleEvents)
		event(source);
}

PLUGIN_EVENTD(void) IPlugin::OnExitVisible(IUnit* source)
{
	for (auto event : ExitVisibleEvents)
		event(source);
}

PLUGIN_EVENTD(void) IPlugin::OnUpdateChargedSpell(eSpellSlot slot, Vec3* position, bool* releaseCast, bool* triggerEvent)
{
	for (auto event : UpdateChargedSpellEvents)
		event(slot, position, releaseCast, triggerEvent);
}

PLUGIN_EVENTD(void) IPlugin::OnPlayAnimation(IUnit* source, std::string const animation)
{
	for (auto event : PlayAnimationEvents)
		event(source, animation);
}

PLUGIN_EVENTD(void) IPlugin::OnPauseAnimation(IUnit* source)
{
	for (auto event : PauseAnimationEvents)
		event(source);
}

PLUGIN_EVENTD(void) IPlugin::OnJungleNotification(JungleNotifyData* data)
{
	for (auto event : JungleNotificationEvents)
		event(data);
}

PLUGIN_EVENTD(void) IPlugin::OnNewPath(IUnit* source, std::vector<Vec3> const& path)
{
	for (auto event : NewPathEvents)
		event(source, path);
}

PLUGIN_EVENTD(void) IPlugin::OnTeleport(OnTeleportArgs* args)
{
	for (auto event : TeleportEvents)
		event(args);
}

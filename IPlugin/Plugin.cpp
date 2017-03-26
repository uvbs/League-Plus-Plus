#include "Plugin.h"
#include "Extension.h"

IPlugin* GPlugin;

float IPlugin::LogoDuration;
ITexture* IPlugin::Logo;
char* IPlugin::Author;
char* IPlugin::Name;
int IPlugin::Version;
std::map<char*, IMenu*> IPlugin::Menus; 
std::map<char*, std::map<char*, IMenuOption*>> IPlugin::MenuOptions;

std::function<void(IUnit*)> IPlugin::OrbwalkBeforeAttackEvent;
std::function<void(IUnit*, IUnit*)> IPlugin::OrbwalkOnAttackEvent;
std::function<void(IUnit*, IUnit*)> IPlugin::OrbwalkAfterAttackEvent;
std::function<void(IUnit*, IUnit*)> IPlugin::OrbwalkTargetChangeEvent;
std::function<void(IUnit*)> IPlugin::OrbwalkNonKillableMinionEvent;
std::function<void()> IPlugin::GameUpdateEvent;
std::function<void()> IPlugin::RenderEvent;
std::function<void(CastedSpell const&)> IPlugin::SpellCastEvent;
std::function<void(IUnit*)> IPlugin::UnitDeathEvent;
std::function<void(IUnit*)> IPlugin::CreateObjectEvent;
std::function<void(IUnit*)> IPlugin::DestroyObjectEvent;
std::function<void(CastedSpell const&)> IPlugin::DoCastEvent;
std::function<void(InterruptibleSpell const&)> IPlugin::InterruptibleEvent;
std::function<void(GapCloserSpell const&)> IPlugin::GapCloserEvent;
std::function<bool(IUnit*, eGameObjectOrder, Vec3*, IUnit*)> IPlugin::IssueOrderEvent;
std::function<void(IUnit*, void*)> IPlugin::BuffAddEvent;
std::function<void(IUnit*, void*)> IPlugin::BuffRemoveEvent;
std::function<void()> IPlugin::GameEndEvent;
std::function<void(IUnit*, int)> IPlugin::LevelUpEvent;
std::function<bool(eSpellSlot, IUnit*, Vec3*, Vec3*)> IPlugin::PreCastEvent;
std::function<IUnit*()> IPlugin::OrbwalkFindTargetEvent;
std::function<void(UnitDash*)> IPlugin::DashEvent;
std::function<void(IDirect3DDevice9*)> IPlugin::D3DPresentEvent;
std::function<void(IDirect3DDevice9*)> IPlugin::D3DPreResetEvent;
std::function<void(IDirect3DDevice9*)> IPlugin::D3DPostResetEvent;
std::function<void()> IPlugin::RenderBehindHudEvent;
std::function<bool(HWND, UINT, WPARAM, LPARAM)> IPlugin::WndProcEvent;
std::function<void(IUnit*)> IPlugin::EnterVisibleEvent;
std::function<void(IUnit*)> IPlugin::ExitVisibleEvent;
std::function<void(eSpellSlot, Vec3*, bool*, bool*)> IPlugin::UpdateChargedSpellEvent;
std::function<void(IUnit*, std::string const)> IPlugin::PlayAnimationEvent;
std::function<void(IUnit*)> IPlugin::PauseAnimationEvent;
std::function<void(JungleNotifyData*)> IPlugin::JungleNotificationEvent;
std::function<void(IUnit*, std::vector<Vec3> const&)> IPlugin::NewPathEvent;
std::function<void(OnTeleportArgs* args)> IPlugin::TeleportEvent;

IPlugin::IPlugin(char* author, char* name, int version)
{
	LogoDuration = GGame->Time() + 3;
	Logo = GExtension->GetTexture("soniice_sonic.png");
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

void IPlugin::AddMenu(char* name, char* title)
{
	Menus[name] = Menus["Main"]->AddMenu(title);
}

void IPlugin::AddMenu(char* name, char* title, char* parentName)
{
	Menus[name] = Menus[parentName]->AddMenu(title);
}

void IPlugin::AddCheckBox(char* menu, char* name, char* title, bool value)
{
	MenuOptions[menu][name] = Menus[menu]->CheckBox(title, value);
}

void IPlugin::AddCheckBox(char* name, char* title, bool value)
{
	MenuOptions["Main"][name] = Menus["Main"]->CheckBox(title, value);
}

void IPlugin::AddColor(char* menu, char* name, char* title, DWORD value)
{
	MenuOptions[menu][name] = Menus[menu]->AddColor(title, value);
}

void IPlugin::AddColor(char* menu, char* name, char* title, float R, float G, float B, float A)
{
	MenuOptions[menu][name] = Menus[menu]->AddColor(title, R, G, B, A);
}

void IPlugin::AddColor(char* name, char* title, DWORD value)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddColor(title, value);
}

void IPlugin::AddColor(char* name, char* title, float R, float G, float B, float A)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddColor(title, R, G, B, A);
}

void IPlugin::AddFloat(char* menu, char* name, char* title, float minValue, float maxValue, float value)
{
	MenuOptions[menu][name] = Menus[menu]->AddFloat(title, minValue, maxValue, value);
}

void IPlugin::AddFloat(char* name, char* title, float minValue, float maxValue, float value)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddFloat(title, minValue, maxValue, value);
}

void IPlugin::AddInteger(char* menu, char* name, char* title, int minValue, int maxValue, int value)
{
	MenuOptions[menu][name] = Menus[menu]->AddInteger(title, minValue, maxValue, value);
}

void IPlugin::AddInteger(char* name, char* title, int minValue, int maxValue, int value)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddInteger(title, minValue, maxValue, value);
}

void IPlugin::AddKey(char* menu, char* name, char* title, int defaultKey)
{
	MenuOptions[menu][name] = Menus[menu]->AddKey(title, defaultKey);
}

void IPlugin::AddKey(char* name, char* title, int defaultKey)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddKey(title, defaultKey);
}

void IPlugin::AddSelection(char* menu, char* name, char* title, int defaultIdx, std::vector<std::string> const& names)
{
	MenuOptions[menu][name] = Menus[menu]->AddSelection(title, defaultIdx, names);
}

void IPlugin::AddSelection(char* name, char* title, int defaultIdx, std::vector<std::string> const& names)
{
	MenuOptions["Main"][name] = Menus["Main"]->AddSelection(title, defaultIdx, names);
}

void IPlugin::UpdateInteger(char* menu, char* name, int value)
{
	MenuOptions[menu][name]->UpdateInteger(value);
}

void IPlugin::UpdateInteger(char* name, int value)
{
	MenuOptions["Main"][name]->UpdateInteger(value);
}

IMenu* IPlugin::GetMenu(char* name)
{
	return Menus[name];
}

IMenu* IPlugin::GetMenu()
{
	return Menus["Main"];
}

IMenuOption* IPlugin::GetMenuOption(char* menu, char* name)
{
	return MenuOptions[menu][name];
}

IMenuOption* IPlugin::GetMenuOption(char* name)
{
	return MenuOptions["Main"][name];
}

bool IPlugin::GetMenuBoolean(char* menu, char* name)
{
	return MenuOptions[menu][name]->Enabled();
}

bool IPlugin::GetMenuBoolean(char* name)
{
	return MenuOptions["Main"][name]->Enabled();
}

Vec4 IPlugin::GetMenuColor(char* menu, char* name)
{
	Vec4 color;
	MenuOptions[menu][name]->GetColor(&color);

	return color;
}

Vec4 IPlugin::GetMenuColor(char* name)
{
	Vec4 color;
	MenuOptions["Main"][name]->GetColor(&color);

	return color;
}

float IPlugin::GetMenuFloat(char* menu, char* name)
{
	return MenuOptions[menu][name]->GetFloat();
}

float IPlugin::GetMenuFloat(char* name)
{
	return MenuOptions["Main"][name]->GetFloat();
}

int IPlugin::GetMenuInteger(char* menu, char* name)
{
	return MenuOptions[menu][name]->GetInteger();
}

int IPlugin::GetMenuInteger(char* name)
{
	return MenuOptions["Main"][name]->GetInteger();
}

void IPlugin::RegisterOrbwalkBeforeAttackEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnOrbwalkBeforeAttack);
	OrbwalkBeforeAttackEvent = function;
}
void IPlugin::RegisterOrbwalkOnAttackEvent(std::function<void(IUnit*, IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOrbwalkOnAttack, OnOrbwalkOnAttack);
	OrbwalkOnAttackEvent = function;
}
void IPlugin::RegisterOrbwalkAfterAttackEvent(std::function<void(IUnit*, IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
	OrbwalkAfterAttackEvent = function;
}
void IPlugin::RegisterOrbwalkTargetChangeEvent(std::function<void(IUnit*, IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOrbwalkTargetChange, OnOrbwalkTargetChange);
	OrbwalkTargetChangeEvent = function;
}
void IPlugin::RegisterOrbwalkNonKillableMinionEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOrbwalkNonKillableMinion, OnOrbwalkNonKillableMinion);
	OrbwalkNonKillableMinionEvent = function;
}
void IPlugin::RegisterGameUpdateEvent(std::function<void()> function)
{
	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GameUpdateEvent = function;
}
void IPlugin::RegisterRenderEvent(std::function<void()> function)
{
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	RenderEvent = function;
}
void IPlugin::RegisterSpellCastEvent(std::function<void(CastedSpell const&)> function)
{
	GEventManager->AddEventHandler(kEventOnSpellCast, OnSpellCast);
	SpellCastEvent = function;
}
void IPlugin::RegisterUnitDeathEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnUnitDeath, OnUnitDeath);
	UnitDeathEvent = function;
}
void IPlugin::RegisterCreateObjectEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	CreateObjectEvent = function;
}
void IPlugin::RegisterDestroyObjectEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	DestroyObjectEvent = function;
}
void IPlugin::RegisterDoCastEvent(std::function<void(CastedSpell const&)> function)
{
	GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
	DoCastEvent = function;
}
void IPlugin::RegisterInterruptibleEvent(std::function<void(InterruptibleSpell const&)> function)
{
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptible);
	InterruptibleEvent = function;
}
void IPlugin::RegisterGapCloserEvent(std::function<void(GapCloserSpell const&)> function)
{
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapCloser);
	GapCloserEvent = function;
}
void IPlugin::RegisterIssueOrderEvent(std::function<bool(IUnit*, eGameObjectOrder, Vec3*, IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnIssueOrder, OnIssueOrder);
	IssueOrderEvent = function;
}
void IPlugin::RegisterBuffAddEvent(std::function<void(IUnit*, void*)> function)
{
	GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
	BuffAddEvent = function;
}
void IPlugin::RegisterBuffRemoveEvent(std::function<void(IUnit*, void*)> function)
{
	GEventManager->AddEventHandler(kEventOnBuffRemove, OnBuffRemove);
	BuffRemoveEvent = function;
}
void IPlugin::RegisterGameEndEvent(std::function<void()> function)
{
	GEventManager->AddEventHandler(kEventOnGameEnd, OnGameEnd);
	GameEndEvent = function;
}
void IPlugin::RegisterLevelUpEvent(std::function<void(IUnit*, int)> function)
{
	GEventManager->AddEventHandler(kEventOnLevelUp, OnLevelUp);
	LevelUpEvent = function;
}
void IPlugin::RegisterPreCastEvent(std::function<bool(eSpellSlot, IUnit*, Vec3*, Vec3*)> function)
{
	GEventManager->AddEventHandler(kEventOnPreCast, OnPreCast);
	PreCastEvent = function;
}
void IPlugin::RegisterOrbwalkFindTargetEvent(std::function<IUnit*()> function)
{
	GEventManager->AddEventHandler(kEventOrbwalkFindTarget, OnOrbwalkFindTarget);
	OrbwalkFindTargetEvent = function;
}
void IPlugin::RegisterDashEvent(std::function<void(UnitDash*)> function)
{
	GEventManager->AddEventHandler(kEventOnDash, OnDash);
	DashEvent = function;
}
void IPlugin::RegisterD3DPresentEvent(std::function<void(IDirect3DDevice9*)> function)
{
	GEventManager->AddEventHandler(kEventOnD3DPresent, OnD3DPresent);
	D3DPresentEvent = function;
}
void IPlugin::RegisterD3DPreResetEvent(std::function<void(IDirect3DDevice9*)> function)
{
	GEventManager->AddEventHandler(kEventOnD3DPreReset, OnD3DPreReset);
	D3DPreResetEvent = function;
}
void IPlugin::RegisterD3DPostResetEvent(std::function<void(IDirect3DDevice9*)> function)
{
	GEventManager->AddEventHandler(kEventOnD3DPostReset, OnD3DPostReset);
	D3DPostResetEvent = function;
}
void IPlugin::RegisterRenderBehindHudEvent(std::function<void()> function)
{
	GEventManager->AddEventHandler(kEventOnRenderBehindHud, OnRenderBehindHud);
	RenderBehindHudEvent = function;
}
void IPlugin::RegisterWndProcEvent(std::function<bool(HWND, UINT, WPARAM, LPARAM)> function)
{
	GEventManager->AddEventHandler(kEventOnWndProc, OnWndProc);
	WndProcEvent = function;
}
void IPlugin::RegisterEnterVisibleEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnEnterVisible, OnEnterVisible);
	EnterVisibleEvent = function;
}
void IPlugin::RegisterExitVisibleEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnExitVisible, OnExitVisible);
	ExitVisibleEvent = function;
}
void IPlugin::RegisterUpdateChargedSpellEvent(std::function<void(eSpellSlot, Vec3*, bool*, bool*)> function)
{
	GEventManager->AddEventHandler(kEventOnUpdateChargedSpell, OnUpdateChargedSpell);
	UpdateChargedSpellEvent = function;
}
void IPlugin::RegisterPlayAnimationEvent(std::function<void(IUnit*, std::string const)> function)
{
	GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	PlayAnimationEvent = function;
}
void IPlugin::RegisterPauseAnimationEvent(std::function<void(IUnit*)> function)
{
	GEventManager->AddEventHandler(kEventOnPauseAnimation, OnPauseAnimation);
	PauseAnimationEvent = function;
}
void IPlugin::RegisterJungleNotificationEvent(std::function<void(JungleNotifyData*)> function)
{
	GEventManager->AddEventHandler(kEventOnJungleNotification, OnJungleNotification);
	JungleNotificationEvent = function;
}
void IPlugin::RegisterNewPathEvent(std::function<void(IUnit*, std::vector<Vec3> const&)> function)
{
	GEventManager->AddEventHandler(kEventOnNewPath, OnNewPath); 
	NewPathEvent = function;
}

void IPlugin::RegisterTeleportEvent(std::function<void(OnTeleportArgs* args)> function)
{
	GEventManager->AddEventHandler(kEventOnTeleport, OnTeleport);
	TeleportEvent = function;
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkBeforeAttack(IUnit* target)
{
	if (OrbwalkBeforeAttackEvent != nullptr)
		OrbwalkBeforeAttackEvent(target);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkOnAttack(IUnit* source, IUnit* target)
{
	if (OrbwalkOnAttackEvent != nullptr)
		OrbwalkOnAttackEvent(source, target);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkAfterAttack(IUnit* source, IUnit* target)
{
	if (OrbwalkAfterAttackEvent != nullptr)
		OrbwalkAfterAttackEvent(source, target);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkTargetChange(IUnit* oldTarget, IUnit* newTarget)
{
	if (OrbwalkTargetChangeEvent != nullptr)
		OrbwalkTargetChangeEvent(oldTarget, newTarget);
}

PLUGIN_EVENTD(void) IPlugin::OnOrbwalkNonKillableMinion(IUnit* minion)
{
	if (OrbwalkNonKillableMinionEvent != nullptr)
		OrbwalkNonKillableMinionEvent(minion);
}

PLUGIN_EVENTD(void) IPlugin::OnGameUpdate()
{
	if (GameUpdateEvent != nullptr)
		GameUpdateEvent();
}

PLUGIN_EVENTD(void) IPlugin::OnRender()
{
	if (LogoDuration >= GGame->Time())
	{
		Logo->Draw(GRender->ScreenSize().x - Logo->GetSize().x, GRender->ScreenSize().y - Logo->GetSize().y);
	}

	if (RenderEvent != nullptr)
		RenderEvent();
}

PLUGIN_EVENTD(void) IPlugin::OnSpellCast(CastedSpell const& spell)
{
	if (SpellCastEvent != nullptr)
		SpellCastEvent(spell);
}

PLUGIN_EVENTD(void) IPlugin::OnUnitDeath(IUnit* source)
{
	if (UnitDeathEvent != nullptr)
		UnitDeathEvent(source);
}

PLUGIN_EVENTD(void) IPlugin::OnCreateObject(IUnit* source)
{
	if (CreateObjectEvent != nullptr)
		CreateObjectEvent(source);
}

PLUGIN_EVENTD(void) IPlugin::OnDestroyObject(IUnit* source)
{
	if (DestroyObjectEvent != nullptr)
		DestroyObjectEvent(source);
}

PLUGIN_EVENTD(void) IPlugin::OnDoCast(CastedSpell const& spell)
{
	if (DoCastEvent != nullptr)
		DoCastEvent(spell);
}

PLUGIN_EVENTD(void) IPlugin::OnInterruptible(InterruptibleSpell const& spell)
{
	if (InterruptibleEvent != nullptr)
		InterruptibleEvent(spell);
}

PLUGIN_EVENTD(void) IPlugin::OnGapCloser(GapCloserSpell const& spell)
{
	if (GapCloserEvent != nullptr)
		GapCloserEvent(spell);
}

PLUGIN_EVENTD(bool) IPlugin::OnIssueOrder(IUnit* source, eGameObjectOrder orderIdx, Vec3* position, IUnit* target)
{
	if (IssueOrderEvent != nullptr)
		IssueOrderEvent(source, orderIdx, position, target);

	return true;
}

PLUGIN_EVENTD(void) IPlugin::OnBuffAdd(IUnit* source, void* buffData)
{
	if (BuffAddEvent != nullptr)
		BuffAddEvent(source, buffData);
}

PLUGIN_EVENTD(void) IPlugin::OnBuffRemove(IUnit* source, void* buffData)
{
	if (BuffRemoveEvent != nullptr)
		BuffRemoveEvent(source, buffData);
}

PLUGIN_EVENTD(void) IPlugin::OnGameEnd()
{
	if (GameEndEvent != nullptr)
		GameEndEvent();
}

PLUGIN_EVENTD(void) IPlugin::OnLevelUp(IUnit* source, int newLevel)
{
	if (LevelUpEvent != nullptr)
		LevelUpEvent(source, newLevel);
}

PLUGIN_EVENTD(bool) IPlugin::OnPreCast(eSpellSlot slot, IUnit* target, Vec3* startPosition, Vec3* endPosition)
{
	if (PreCastEvent != nullptr)
		PreCastEvent(slot, target, startPosition, endPosition);

	return true;
}

PLUGIN_EVENTD(IUnit*) IPlugin::OnOrbwalkFindTarget()
{
	if (OrbwalkFindTargetEvent != nullptr)
		OrbwalkFindTargetEvent();

	return nullptr;
}

PLUGIN_EVENTD(void) IPlugin::OnDash(UnitDash* dash)
{
	if (DashEvent != nullptr)
		DashEvent(dash);
}

PLUGIN_EVENTD(void) IPlugin::OnD3DPresent(IDirect3DDevice9* device)
{
	if (D3DPresentEvent != nullptr)
		D3DPresentEvent(device);
}

PLUGIN_EVENTD(void) IPlugin::OnD3DPreReset(IDirect3DDevice9* device)
{
	if (D3DPreResetEvent != nullptr)
		D3DPreResetEvent(device);
}

PLUGIN_EVENTD(void) IPlugin::OnD3DPostReset(IDirect3DDevice9* device)
{
	if (D3DPostResetEvent != nullptr)
		D3DPostResetEvent(device);
}

PLUGIN_EVENTD(void) IPlugin::OnRenderBehindHud()
{
	if (RenderBehindHudEvent != nullptr)
		RenderBehindHudEvent();
}

PLUGIN_EVENTD(bool) IPlugin::OnWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WndProcEvent != nullptr)
		WndProcEvent(hwnd, message, wParam, lParam);

	return false;
}

PLUGIN_EVENTD(void) IPlugin::OnEnterVisible(IUnit* source)
{
	if (EnterVisibleEvent != nullptr)
		EnterVisibleEvent(source);
}

PLUGIN_EVENTD(void) IPlugin::OnExitVisible(IUnit* source)
{
	if (ExitVisibleEvent != nullptr)
		ExitVisibleEvent(source);
}

PLUGIN_EVENTD(void) IPlugin::OnUpdateChargedSpell(eSpellSlot slot, Vec3* position, bool* releaseCast, bool* triggerEvent)
{
	if (UpdateChargedSpellEvent != nullptr)
		UpdateChargedSpellEvent(slot, position, releaseCast, triggerEvent);
}

PLUGIN_EVENTD(void) IPlugin::OnPlayAnimation(IUnit* source, std::string const animation)
{
	if (PlayAnimationEvent != nullptr)
		PlayAnimationEvent(source, animation);
}

PLUGIN_EVENTD(void) IPlugin::OnPauseAnimation(IUnit* source)
{
	if (PauseAnimationEvent != nullptr)
		PauseAnimationEvent(source);

}

PLUGIN_EVENTD(void) IPlugin::OnJungleNotification(JungleNotifyData* data)
{
	if (JungleNotificationEvent != nullptr)
		JungleNotificationEvent(data);
}

PLUGIN_EVENTD(void) IPlugin::OnNewPath(IUnit* source, std::vector<Vec3> const& path)
{
	if (NewPathEvent != nullptr)
		NewPathEvent(source, path);
}

PLUGIN_EVENTD(void) IPlugin::OnTeleport(OnTeleportArgs* args)
{
	if (TeleportEvent != nullptr)
		TeleportEvent(args);
}

#include "PluginSDK.h"
#include "D3D9.h"
#include <map>

class IPlugin
{
public:
	IPlugin(char* author, char* name, int version);
	~IPlugin();
	
	static char* GetAuthor();
	static char* GetName();
	static int GetVersion();
	static void AddMenu(char* name, char* title);
	static void AddMenu(char* name, char* title, char* parentName);
	static void AddCheckBox(char* menu, char* name, char* title, bool value);
	static void AddColor(char* menu, char* name, char* title, DWORD value);
	static void AddColor(char* menu, char* name, char* title, float R, float G, float B, float A);
	static void AddFloat(char* menu, char* name, char* title, float minValue, float maxValue, float value);
	static void AddInteger(char* menu, char* name, char* title, int minValue, int maxValue, int value);
	static void AddKey(char* menu, char* name, char* title, int defaultKey);
	static void AddSelection(char* menu, char* name, char* title, int defaultIdx, std::vector<std::string> const& names);
	static IMenu* GetMenu(char* name);
	static IMenuOption* GetMenuOption(char* menu, char* name);

	static void RegisterOrbwalkBeforeAttackEvent(std::function<void(IUnit*)> function);
	static void RegisterOrbwalkOnAttackEvent(std::function<void(IUnit*, IUnit*)> function);
	static void RegisterOrbwalkAfterAttackEvent(std::function<void(IUnit*, IUnit*)> function);
	static void RegisterOrbwalkTargetChangeEvent(std::function<void(IUnit*, IUnit*)> function);
	static void RegisterOrbwalkNonKillableMinionEvent(std::function<void(IUnit*)> function);
	static void RegisterGameUpdateEvent(std::function<void()> function);
	static void RegisterRenderEvent(std::function<void()> function);
	static void RegisterSpellCastEvent(std::function<void(CastedSpell const&)> function);
	static void RegisterUnitDeathEvent(std::function<void(IUnit*)> function);
	static void RegisterCreateObjectEvent(std::function<void(IUnit*)> function);
	static void RegisterDestroyObjectEvent(std::function<void(IUnit*)> function);
	static void RegisterDoCastEvent(std::function<void(CastedSpell const&)> function);
	static void RegisterInterruptibleEvent(std::function<void(InterruptibleSpell const&)> function);
	static void RegisterGapCloserEvent(std::function<void(GapCloserSpell const&)> function);
	static void RegisterIssueOrderEvent(std::function<bool(IUnit*, eGameObjectOrder, Vec3*, IUnit*)> function);
	static void RegisterBuffAddEvent(std::function<void(IUnit*, void*)> function);
	static void RegisterBuffRemoveEvent(std::function<void(IUnit*, void*)> function);
	static void RegisterGameEndEvent(std::function<void()> function);
	static void RegisterLevelUpEvent(std::function<void(IUnit*, int)> function);
	static void RegisterPreCastEvent(std::function<bool(eSpellSlot, IUnit*, Vec3*, Vec3*)> function);
	static void RegisterOrbwalkFindTargetEvent(std::function<IUnit*()> function);
	static void RegisterDashEvent(std::function<void(UnitDash*)> function);
	static void RegisterD3DPresentEvent(std::function<void(IDirect3DDevice9*)> function);
	static void RegisterD3DPreResetEvent(std::function<void(IDirect3DDevice9*)> function);
	static void RegisterD3DPostResetEvent(std::function<void(IDirect3DDevice9*)> function);
	static void RegisterRenderBehindHudEvent(std::function<void()> function);
	static void RegisterWndProcEvent(std::function<bool(HWND, UINT, WPARAM, LPARAM)> function);
	static void RegisterEnterVisibleEvent(std::function<void(IUnit*)> function);
	static void RegisterExitVisibleEvent(std::function<void(IUnit*)> function);
	static void RegisterUpdateChargedSpellEvent(std::function<void(eSpellSlot, Vec3*, bool*, bool*)> function);
	static void RegisterPlayAnimationEvent(std::function<void(IUnit*, std::string const)> function);
	static void RegisterPauseAnimationEvent(std::function<void(IUnit*)> function);
	static void RegisterJungleNotificationEvent(std::function<void(JungleNotifyData*)> function);
	static void RegisterNewPathEvent(std::function<void(IUnit*, std::vector<Vec3> const&)> function);
	static void RegisterTeleportEvent(std::function<void(OnTeleportArgs* args)> function);

private:
	static char* Author;
	static char* Name;
	static int Version;
	static std::map<char*, IMenu*> Menus;
	static std::map<char*, std::map<char*, IMenuOption*>> MenuOptions;

	static std::function<void(IUnit*)> OrbwalkBeforeAttackEvent;
	static std::function<void(IUnit*, IUnit*)> OrbwalkOnAttackEvent;
	static std::function<void(IUnit*, IUnit*)> OrbwalkAfterAttackEvent;
	static std::function<void(IUnit*, IUnit*)> OrbwalkTargetChangeEvent;
	static std::function<void(IUnit*)> OrbwalkNonKillableMinionEvent;
	static std::function<void()> GameUpdateEvent;
	static std::function<void()> RenderEvent;
	static std::function<void(CastedSpell const&)> SpellCastEvent;
	static std::function<void(IUnit*)> UnitDeathEvent;
	static std::function<void(IUnit*)> CreateObjectEvent;
	static std::function<void(IUnit*)> DestroyObjectEvent;
	static std::function<void(CastedSpell const&)> DoCastEvent;
	static std::function<void(InterruptibleSpell const&)> InterruptibleEvent;
	static std::function<void(GapCloserSpell const&)> GapCloserEvent;
	static std::function<bool(IUnit*, eGameObjectOrder, Vec3*, IUnit*)> IssueOrderEvent;
	static std::function<void(IUnit*, void*)> BuffAddEvent;
	static std::function<void(IUnit*, void*)> BuffRemoveEvent;
	static std::function<void()> GameEndEvent;
	static std::function<void(IUnit*, int)> LevelUpEvent;
	static std::function<bool(eSpellSlot, IUnit*, Vec3*, Vec3*)> PreCastEvent;
	static std::function<IUnit*()> OrbwalkFindTargetEvent;
	static std::function<void(UnitDash*)> DashEvent;
	static std::function<void(IDirect3DDevice9*)> D3DPresentEvent;
	static std::function<void(IDirect3DDevice9*)> D3DPreResetEvent;
	static std::function<void(IDirect3DDevice9*)> D3DPostResetEvent;
	static std::function<void()> RenderBehindHudEvent;
	static std::function<bool(HWND, UINT, WPARAM, LPARAM)> WndProcEvent;
	static std::function<void(IUnit*)> EnterVisibleEvent;
	static std::function<void(IUnit*)> ExitVisibleEvent;
	static std::function<void(eSpellSlot, Vec3*, bool*, bool*)> UpdateChargedSpellEvent;
	static std::function<void(IUnit*, std::string const)> PlayAnimationEvent;
	static std::function<void(IUnit*)> PauseAnimationEvent;
	static std::function<void(JungleNotifyData*)> JungleNotificationEvent;
	static std::function<void(IUnit*, std::vector<Vec3> const&)> NewPathEvent;
	static std::function<void(OnTeleportArgs* args)> TeleportEvent;

	PLUGIN_EVENT(void) OnOrbwalkBeforeAttack(IUnit* target);
	PLUGIN_EVENT(void) OnOrbwalkOnAttack(IUnit* source, IUnit* target);
	PLUGIN_EVENT(void) OnOrbwalkAfterAttack(IUnit* source, IUnit* target);
	PLUGIN_EVENT(void) OnOrbwalkTargetChange(IUnit* oldTarget, IUnit* newTarget);
	PLUGIN_EVENT(void) OnOrbwalkNonKillableMinion(IUnit* minion);
	PLUGIN_EVENT(void) OnGameUpdate();
	PLUGIN_EVENT(void) OnRender();
	PLUGIN_EVENT(void) OnSpellCast(CastedSpell const& spell);
	PLUGIN_EVENT(void) OnUnitDeath(IUnit* source);
	PLUGIN_EVENT(void) OnCreateObject(IUnit* source);
	PLUGIN_EVENT(void) OnDestroyObject(IUnit* source);
	PLUGIN_EVENT(void) OnDoCast(CastedSpell const& spell);
	PLUGIN_EVENT(void) OnInterruptible(InterruptibleSpell const& spell);
	PLUGIN_EVENT(void) OnGapCloser(GapCloserSpell const& spell);
	PLUGIN_EVENT(bool) OnIssueOrder(IUnit* source, eGameObjectOrder orderIdx, Vec3* position, IUnit* target);
	PLUGIN_EVENT(void) OnBuffAdd(IUnit* source, void* buffData);
	PLUGIN_EVENT(void) OnBuffRemove(IUnit* source, void* buffData);
	PLUGIN_EVENT(void) OnGameEnd();
	PLUGIN_EVENT(void) OnLevelUp(IUnit* source, int newLevel);
	PLUGIN_EVENT(bool) OnPreCast(eSpellSlot slot, IUnit* target, Vec3* startPosition, Vec3* endPosition);
	PLUGIN_EVENT(IUnit*) OnOrbwalkFindTarget();
	PLUGIN_EVENT(void) OnDash(UnitDash* dash);
	PLUGIN_EVENT(void) OnD3DPresent(IDirect3DDevice9* device);
	PLUGIN_EVENT(void) OnD3DPreReset(IDirect3DDevice9* device);
	PLUGIN_EVENT(void) OnD3DPostReset(IDirect3DDevice9* device);
	PLUGIN_EVENT(void) OnRenderBehindHud();
	PLUGIN_EVENT(bool) OnWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	PLUGIN_EVENT(void) OnEnterVisible(IUnit* source);
	PLUGIN_EVENT(void) OnExitVisible(IUnit* source);
	PLUGIN_EVENT(void) OnUpdateChargedSpell(eSpellSlot slot, Vec3* position, bool* releaseCast, bool* triggerEvent);
	PLUGIN_EVENT(void) OnPlayAnimation(IUnit* source, std::string const animation);
	PLUGIN_EVENT(void) OnPauseAnimation(IUnit* source);
	PLUGIN_EVENT(void) OnJungleNotification(JungleNotifyData* data);
	PLUGIN_EVENT(void) OnNewPath(IUnit* source, std::vector<Vec3> const& path);
	PLUGIN_EVENT(void) OnTeleport(OnTeleportArgs* args);
};

extern IPlugin* GPlugin;
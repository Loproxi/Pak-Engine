#ifndef __MODULEUICONTROLLER_H__
#define __MODULEUICONTROLLER_H__

#include "Module.h"
#include "Globals.h"
#include <vector>

class WindowBaseClass;
class GameObject;

enum class UIwindows
{
	
	CONFIGURATION,
	ABOUT,
	CONSOLE,
	INSPECTOR,
	HIERARCHY,
	SCENE,
	GAME,
	MAX

};

class ModuleUIcontroller : public Module
{

public:

	ModuleUIcontroller(Application* app, bool start_enabled);

	~ModuleUIcontroller();

	bool Init(pugi::xml_node& config);

	bool Start();

	UpdateStatus PreUpdate();

	UpdateStatus Update();

	UpdateStatus PostUpdate();

	bool Draw();

	void RenderImGui();

	void MainMenuBar(bool& ret);

	bool CleanUp() override;

	bool SaveSettings(pugi::xml_node& config);

	WindowBaseClass* GetUIControllerWindow(UIwindows type);

	void ReportLog(std::string msg);

	GameObject* GetGameObjSelected();

	void SetGameObjSelected(GameObject* _go);

public:

	bool show_demo_window = false;

private:

	GameObject* goToInspector;

	WindowBaseClass* windows[(uint)UIwindows::MAX];

	bool winenable[(uint)UIwindows::MAX];
	

};
#endif // !__MODULERENDERER3D_H__

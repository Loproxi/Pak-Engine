#ifndef __MODULEUICONTROLLER_H__
#define __MODULEUICONTROLLER_H__

#include "Module.h"
#include "Globals.h"
#include <vector>

class WindowBaseClass;

enum class UIwindows
{
	SCENE,
	CONFIGURATION,
	ABOUT,
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

public:

	bool show_demo_window = false;

private:

	pugi::xml_node* editorNode;

	WindowBaseClass* windows[(uint)UIwindows::MAX];

	bool winenable[(uint)UIwindows::MAX];
	

};
#endif // !__MODULERENDERER3D_H__

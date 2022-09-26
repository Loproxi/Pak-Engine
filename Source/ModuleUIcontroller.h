#ifndef __MODULEUICONTROLLER_H__
#define __MODULEUICONTROLLER_H__

#include "Module.h"
#include "Globals.h"
#include <vector>

class WindowBaseClass;

enum class UIwindows
{
	
	CONFIGURATION,
	ABOUT,
	MAX

};

class ModuleUIcontroller : public Module
{

public:

	ModuleUIcontroller(Application* app, bool start_enabled);

	~ModuleUIcontroller();

	bool Init() override;

	bool Start() override;

	UpdateStatus PreUpdate();

	UpdateStatus Update();

	UpdateStatus PostUpdate();

	bool Draw();

	void RenderImGui();

	void MainMenuBar(bool& ret);

	bool CleanUp() override;

public:

	bool show_demo_window = false;

private:

	WindowBaseClass* windows[(uint)UIwindows::MAX];

};
#endif // !__MODULERENDERER3D_H__

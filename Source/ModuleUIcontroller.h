#ifndef __MODULEUICONTROLLER_H__
#define __MODULEUICONTROLLER_H__

#include "Module.h"
#include "Globals.h"

class ModuleUIcontroller : public Module
{

public:

	ModuleUIcontroller(Application* app, bool start_enabled);

	~ModuleUIcontroller();

	bool Init() override;

	bool Start() override;

	bool Draw();

	bool CleanUp() override;

public:

	bool show_demo_window = false;

};
#endif // !__MODULERENDERER3D_H__

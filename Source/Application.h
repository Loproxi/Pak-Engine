#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "List.h"
#include "Timer.hpp"

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleCamera3D;
class ModuleRenderer3D;

class Application
{
public:
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera3D* camera = nullptr;
	ModuleRenderer3D* renderer3D = nullptr;

	float fps = 1.0f/60.0f;
	Timer	timer;

private:
	
	float	dt = 0;
	List<Module*> list_modules;

public:
	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

#endif // !__APPLICATION_H__
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "List.h"
#include "Timer.hpp"



class Module;
class ModuleWindow;
class ModuleInput;
class ModuleCamera3D;
class ModuleRenderer3D;
class ModuleUIcontroller;

class Application
{
public:
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera3D* camera = nullptr;
	ModuleRenderer3D* renderer3D = nullptr;
	ModuleUIcontroller* uiController = nullptr;

	float fps = 1.0f/60.0f;
	Timer	timer;

private:
	
	float	dt = 0;
	List<Module*> list_modules;

	static Application* App;

public:
	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

	float GetFrameRateLimit();
	void SetFrameRateLimit(float fps);

	static Application* GetInstance();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

#endif // !__APPLICATION_H__
#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModuleUIcontroller.h"
#include "src/pugixml.hpp"

Application* Application::App = nullptr;

Application::Application()
{
	window = new ModuleWindow(this, true);
	input = new ModuleInput(this, true);
	camera = new ModuleCamera3D(this, true);
	uiController = new ModuleUIcontroller(this, true);
	renderer3D = new ModuleRenderer3D(this, true);
	
	
	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	
	AddModule(input);
	AddModule(camera);

	// Scenes

	//UI controller
	AddModule(uiController);
	
	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	for (int i = 0, count = list_modules.count() ; i <count ; i++)
	{
		list_modules[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	for (int i = 0, count = list_modules.count(); i < count; i++)
	{
		list_modules[i]->Start();
	}

	//ms_timer.Start();
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	//ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
UpdateStatus Application::Update()
{
	UpdateStatus ret = UPDATE_CONTINUE;

	PrepareUpdate();

	for (int i = 0, count = list_modules.count(); i < count && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PreUpdate();
	}

	for (int i = 0, count = list_modules.count(); i < count && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->Update();
	}

	for (int i = 0, count = list_modules.count(); i < count && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PostUpdate();
	}

	dt = timer.getDeltaTime();

	if (dt < fps)
	{
		float sleepTime = (fps - dt) * 1000;
		Sleep(sleepTime);
	}

	timer.Reset();

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = list_modules.count() -1; i >= 0 && ret; i--)
	{
		ret = list_modules[i]->CleanUp();
	}

	for (int i = list_modules.count() - 1; i >= 0; i--)
	{
		RELEASE(list_modules[i]);
	}

	return ret;
}

float Application::GetFrameRateLimit()
{

	return (1.0f/fps);
}

void Application::SetFrameRateLimit(float max_fps)
{
	if (max_fps > 0)
	{
		fps = 1.0f / max_fps;
	}
	else
	{
		fps = 1.0f / 60.0f;
	}
}

float Application::GetDeltaTime_MS()
{

	float ret = App->timer.getDeltaTime() * 1000;

	return ret;
}

void Application::LoadConfigXml()
{

	

}

Application* Application::GetInstance()
{

	if (App == nullptr) {
		App = new Application();
	}
	return App;
}

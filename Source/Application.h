#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "List.h"
#include "Timer.hpp"
#include "rapidjson.h"
#include "src/pugixml.hpp"

#define CONFIG_FILENAME		"SaveFiles/configuration.xml"

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

	std::string title;
	std::string organization;

public:
	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

	float GetFrameRateLimit();
	void SetFrameRateLimit(float fps);

	float GetDeltaTime_MS();

	const char* GetTitle() { return title.c_str(); }

	const char* GetOrganization() { return organization.c_str(); }

	bool InitConfigXml();

	pugi::xml_node LoadConfig(pugi::xml_document& configFile)const;

	std::string GetPakEngineVersion();

	static Application* GetInstance();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

};

#endif // !__APPLICATION_H__
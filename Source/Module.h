#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"
#include "src/pugixml.hpp"

class PhysBody3D;
class Application;

class Module
{
private:
	bool enabled = false;
	std::string name = { "Nameless Module" };
public:
	Application* App = nullptr;
	
public:
	Module();

	Module(Application* parent, bool start_enabled = true);

	std::string GetNameOfModule() const { return name; }

	void SetNameOfModule(std::string name);

	virtual ~Module();

	virtual bool Init(pugi::xml_node& config);

	virtual bool Start();

	virtual UpdateStatus PreUpdate();

	virtual UpdateStatus Update();

	virtual UpdateStatus PostUpdate();

	virtual bool CleanUp();

	virtual bool SaveSettings(pugi::xml_node&);
};

#endif // !__MODULE_H__
#include "Module.h"

Module::Module()
{
}

Module::Module(Application* parent, bool start_enabled)
{
	App = parent;
	enabled = start_enabled;
}

void Module::SetNameOfModule(std::string name)
{
	this->name = name;
}

Module::~Module()
{}

bool Module::Init(pugi::xml_node& config)
{
	return true;
}

bool Module::Start()
{
	return true;
}

UpdateStatus Module::PreUpdate()
{
	return UPDATE_CONTINUE;
}

UpdateStatus Module::Update()
{
	return UPDATE_CONTINUE;
}

UpdateStatus Module::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool Module::CleanUp()
{
	return true;
}

bool Module::SaveSettings(pugi::xml_node& config)
{
	return true;
}
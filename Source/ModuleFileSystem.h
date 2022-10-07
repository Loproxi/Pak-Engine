#ifndef _MODULEFILESYSTEM_H__
#define _MODULEFILESYSTEM_H__


#include "Module.h"
class ModuleFileSystem :
    public Module
{
public:
    ModuleFileSystem(Application* app, bool start_enabled = true);

    ~ModuleFileSystem();

    bool Init();
    bool Start();
    bool CleanUp();

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

    bool SaveSettings(pugi::xml_node& config);

};

#endif // !_MODULEFILESYSTEM_H__
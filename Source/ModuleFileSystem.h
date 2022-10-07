#pragma once
#include "Module.h"
class ModuleFileSystem :
    public Module
{
public:
    ModuleFileSystem(Application* app, bool start_enabled = true);

   /* ~ModuleFileSystem();

    bool Init();
    UpdateStatus PreUpdate();
    bool CleanUp();

    bool SaveSettings(pugi::xml_node& config);*/
};


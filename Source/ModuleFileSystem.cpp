#include "ModuleFileSystem.h"


ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled)
{
}

ModuleFileSystem::~ModuleFileSystem()
{
}

bool ModuleFileSystem::Init()
{
    


    return true;
}

bool ModuleFileSystem::Start()
{


    return true;
}

UpdateStatus ModuleFileSystem::PreUpdate()
{



    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleFileSystem::Update()
{
    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleFileSystem::PostUpdate()
{
    return UpdateStatus::UPDATE_CONTINUE;
}

bool ModuleFileSystem::CleanUp()
{
    
    return true;
}

bool ModuleFileSystem::SaveSettings(pugi::xml_node& config)
{
    return true;
}

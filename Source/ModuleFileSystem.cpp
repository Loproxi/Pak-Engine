#include "ModuleFileSystem.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled):Module(app,start_enabled)
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

void ModuleFileSystem::DragAndDropOnEngine(std::string path)
{

    std::string fileExtension(path);

    fileExtension = fileExtension.substr(fileExtension.find_last_of(".") + 1);

    if (fileExtension == "fbx")
    {
        App->renderer3D->LoadModelImporter(path);
    }
    else if (fileExtension == "png")
    {
        App->renderer3D->LoadTextureImporter(path);
    }

}

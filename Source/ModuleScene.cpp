#include "ModuleScene.h"
#include "GameObject.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
 
}

ModuleScene::~ModuleScene()
{
}

bool ModuleScene::Init(pugi::xml_node& config)
{
    root = new GameObject("SceneRoot");
    root->parent = nullptr;

    return true;
}

bool ModuleScene::Start()
{
    return true;
}

UpdateStatus ModuleScene::PreUpdate()
{
    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleScene::Update()
{
    UpdateGameObjects();
    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleScene::PostUpdate()
{
    return UpdateStatus::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
    RELEASE(root);

    return true;
}

void ModuleScene::UpdateGameObjects()
{
    UpdatingGameObjectTree(root);
}

void ModuleScene::UpdatingGameObjectTree(GameObject* parent)
{
    if (parent->active)
    {
        parent->Update();

        for (int i = 0; i < parent->children.size(); i++)
        {
            UpdatingGameObjectTree(parent->children[i]);
        }
    }
}

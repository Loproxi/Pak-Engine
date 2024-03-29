#include "ModuleScene.h"
#include "GameObject.h"
#include "Comp_Camera.h"
#include "Comp_Transform.h"
#include "Camera3D.h"

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
    test = new GameObject("Camera1");
    test->SetParent(root);
    test2 = new GameObject("Camera2");
    test2->SetParent(root);
    smoke1 = new GameObject("SmokeParticle1");
    smoke1->SetParent(root);
    smoke2 = new GameObject("SmokeParticle2");
    smoke2->SetParent(root);

    return true;
}

bool ModuleScene::Start()
{

    test->AddComponent(COMP_TYPE::CAMERA);
    
    Comp_Camera* prueba = (Comp_Camera*)test2->AddComponent(COMP_TYPE::CAMERA);
    prueba->camera->Move(float3(0.0f, 5.0f, -10.0f));

    smoke1->GetComponent<Comp_Transform>()->position = float3(24.7f, 9.4f, 37.7f);
    smoke2->GetComponent<Comp_Transform>()->position = float3(43.7f, 9.4f, 37.7f);
    smoke1->AddComponent(COMP_TYPE::PARTICLE_SYSTEM);
    smoke2->AddComponent(COMP_TYPE::PARTICLE_SYSTEM);

    return true;
}

UpdateStatus ModuleScene::PreUpdate()
{
    PreUpdateGameObjectTree(root);

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

void ModuleScene::DestroyGameObject(GameObject* goToDestroy)
{

    for (int i = 0;i<gameobjects.size();i++)
    {

        if (gameobjects[i] == goToDestroy)
        {
            RELEASE(gameobjects[i]);
            gameobjects.erase(gameobjects.begin() + i);
        }

    }

}

void ModuleScene::PreUpdateGameObjectTree(GameObject* parent)
{
    if (parent->active)
    {
        parent->PreUpdate();

        for (int i = 0; i < parent->children.size(); i++)
        {
            PreUpdateGameObjectTree(parent->children[i]);
        }
    }
}

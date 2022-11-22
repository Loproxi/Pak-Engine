#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include <vector>

class GameObject;

class ModuleScene :
    public Module
{
public:

	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Init(pugi::xml_node& config)override;
	bool Start() override;

	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;

	bool CleanUp() override;

	void UpdateGameObjects();

	void PreUpdateGameObjectTree(GameObject* parent);
	void UpdatingGameObjectTree(GameObject* parent);

	void DestroyGameObject(GameObject* goToDestroy);

public:

	GameObject* test;
	GameObject* test2;

	GameObject* root;

	std::vector<GameObject*> gameobjects;

};

#endif // !__MODULE_SCENE_H__
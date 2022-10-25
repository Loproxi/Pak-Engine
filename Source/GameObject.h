#ifndef _GAMEOBJECT_H__
#define _GAMEOBJECT_H__

#include "Component.h"
#include <vector>

class Component;

class GameObject
{
public:

	GameObject(std::string name);

	virtual ~GameObject();

	void Update();

	void PostUpdate();

	Component* AddComponent(COMP_TYPE type);

	void GetComponent();


private:



public:

	std::vector<Component*> components;
	std::vector<GameObject*> children;

	GameObject* parent = nullptr;

	bool active;
	std::string name;

};

#endif // !_GAMEOBJECT_H__
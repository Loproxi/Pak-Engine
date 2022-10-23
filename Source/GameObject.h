#ifndef _GAMEOBJECT_H__
#define _GAMEOBJECT_H__

#include <vector>

class Component;

class GameObject
{
public:

	GameObject();

	virtual ~GameObject();

	void AddComponent();

	void GetComponent();


private:



public:

	std::vector<Component*> components;
	std::vector<GameObject*> children;

	GameObject* parent = nullptr;

	bool active;

};

#endif // !_GAMEOBJECT_H__
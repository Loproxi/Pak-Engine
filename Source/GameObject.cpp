#include "GameObject.h"
#include "Comp_MeshRenderer.h"
#include "Application.h"


GameObject::GameObject(std::string name):active(true)
{
	this->name = name;
}


GameObject::~GameObject()
{
	for (int i = 0; i < components.size(); i++)
	{
		RELEASE(components[i]);
	}
	components.clear();

	for (int i = 0; i < children.size(); i++)
	{
		RELEASE(children[i]);
	}
	children.clear();

}

void GameObject::Update()
{

	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}

}

void GameObject::PostUpdate()
{
}

Component* GameObject::AddComponent(COMP_TYPE type)
{

	Component* component = nullptr;

	switch (type)
	{
	case NONE:
		Application::GetInstance()->AddLog(Logs::WARNING, " Can't create a None Component ");
		break;
	case MESH_RENDERER: 
		component = new Comp_MeshRenderer(this);
		component->type = type;
		break;
	}

	if (component != nullptr)
	{
		components.push_back(component);
	}

	return component;
}

Component* GameObject::GetComponent(COMP_TYPE _type)
{
	Component* comp = nullptr;

	for (int i = 0; i < components.size(); i++)
	{
		if (this->components[i]->type = _type)
		{
			comp = components[i];
			return comp;
		}
	}
	return comp;
}

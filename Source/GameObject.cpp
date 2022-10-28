#include "GameObject.h"
#include "Comp_MeshRenderer.h"
#include "Comp_Transform.h"
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
		if (this->active)
		{
			if (this != nullptr)
			{
				components[i]->Update();
			}
		}
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
	case TRANSFORM:
		component = new Comp_Transform(this);
		component->type = type;
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

void GameObject::AddChild(GameObject* _go)
{
	if (_go == nullptr) return;
	if (this->parent == _go) return;


	this->children.push_back(_go);
	
	_go->parent = this;
	
}

void GameObject::SetParent(GameObject* _go)
{
	this->parent->RemoveChild(this);
	_go->AddChild(this);

}

void GameObject::RemoveChild(GameObject* _go)
{
	if (this->children.size() == 0) return;

	for (int i = 0; i < this->children.size(); i++)
	{
		if (this->children[i] == _go)
		{
			this->children.erase(this->children.end() - i);
		}
	}
}

#include "GameObject.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleUIcontroller.h"

#include "Comp_MeshRenderer.h"
#include "Comp_Transform.h"
#include "Comp_Camera.h"



GameObject::GameObject(std::string name):active(true),readytobedeleted(false)
{
	if (name == "")
	{
		name = "GameObject";
	}
	this->name = name;

	this->AddComponent(COMP_TYPE::TRANSFORM);

	

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

void GameObject::PreUpdate()
{
	if (this->readytobedeleted == true)
	{

		GameObject* parenttemp = this->parent;
		
		parenttemp->RemoveChild(this);
			
		delete this;

		app = Application::GetInstance();
		
		app->uiController->SetGameObjSelected(nullptr);

	}
}

void GameObject::Update()
{

	for (int i = 0; i < components.size(); i++)
	{
		if (this->active)
		{
			if (components[i]->active)
			{
				if (this != nullptr)
				{
					components[i]->Update();
				}
			}
		}
	}

}

void GameObject::PostUpdate()
{
}

Component* GameObject::AddComponent(COMP_TYPE type)
{

	for each (Component* var in this->components)
	{
		if (var->type == type)
		{
			Application::GetInstance()->AddLog(Logs::WARNING, this->name + " already has this type of component!");
			return nullptr;
		}
	}

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
	case CAMERA: 
		component = new Comp_Camera(this);
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
	if (_go->CheckifGameObjIsParent(this))
	{
		return;
	}

	if (this->parent != nullptr)
	{
		this->parent->RemoveChild(this);
	}
	_go->AddChild(this);

}

void GameObject::RemoveChild(GameObject* _go)
{
	if (this->children.size() == 0) return;

	for (int i = 0; i < this->children.size(); i++)
	{
		if (this->children[i] == _go)
		{
			this->children.erase(this->children.begin() + i);
		}
	}
}

bool GameObject::CheckifGameObjIsParent(GameObject* _goToDrop)
{
	//Parent of go in begindragdrop
	GameObject* temp = this->parent;

	//When temp is root stop searching
	while (temp != nullptr)
	{
		//if goToDrop is this gameobject parent not set Parent
		if (temp == _goToDrop)
		{
			return true;
		}
		else
		{
			//Update temp in order to see if someone else in the tree should not be set parent
			temp = temp->parent;
		}
	}
	//if goToDrop is not this gameobject parent then, Set Parent
	return false;
}
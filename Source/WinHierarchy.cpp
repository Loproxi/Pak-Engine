#include "WinHierarchy.h"
#include "ImGuiUtils.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"

WinHierarchy::WinHierarchy()
{
	name = "Hierarchy";
	app = Application::GetInstance();
}

WinHierarchy::~WinHierarchy()
{
}

void WinHierarchy::Start()
{
}

void WinHierarchy::Draw()
{
	//Window
	if (isEnabled)
	{
		if (ImGui::Begin(name.c_str(), &isEnabled))
		{
			ShowGameObjects(app->scene->root);

			
		}
		ImGui::End();
	}
}

void WinHierarchy::ShowGameObjects(GameObject* go)
{

	ImGuiTreeNodeFlags nodeFlags = ImGuiDockNodeFlags_None;
	nodeFlags += ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (go->children.size() == 0)
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	const bool nodeOpen = ImGui::TreeNodeEx(go->name.c_str(), nodeFlags);

	if (nodeOpen && go->children.size() != 0)
	{
		
		for (int i = 0; i < go->children.size(); i++)
		{
			ShowGameObjects(go->children[i]);
		}
		
		ImGui::TreePop();
		
	}

	
}

void WinHierarchy::DisplayGameObject(GameObject* go)
{
	

	
}

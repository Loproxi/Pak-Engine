#include "WinHierarchy.h"
#include "ImGuiUtils.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRenderer3D.h"
#include "ModuleUIcontroller.h"
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

			PrimitivesMenu();
		}
		ImGui::End();
	}
}

void WinHierarchy::PrimitivesMenu()
{
	if (!ImGui::IsItemHovered())
	{
		if (ImGui::BeginPopupContextWindow("Primitives", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonDefault_))
		{
			if (ImGui::BeginMenu("Primitives"))
			{
				if (ImGui::MenuItem("Cube"))
				{
					app->renderer3D->LoadModelImporter("Assets/Primitives/Cube.fbx");
				}
				if (ImGui::MenuItem("Sphere"))
				{
					app->renderer3D->LoadModelImporter("Assets/Primitives/Sphere.fbx");
				}
				if (ImGui::MenuItem("Monkey"))
				{
					app->renderer3D->LoadModelImporter("Assets/Primitives/Monkey.fbx");
				}
				if (ImGui::MenuItem("Plane"))
				{
					app->renderer3D->LoadModelImporter("Assets/Primitives/Plane.fbx");
				}
				if (ImGui::MenuItem("Pyramid"))
				{
					app->renderer3D->LoadModelImporter("Assets/Primitives/Pyramid.fbx");
				}
				if (ImGui::MenuItem("Cylinder"))
				{
					app->renderer3D->LoadModelImporter("Assets/Primitives/Cylinder.fbx");
				}

				ImGui::EndMenu();
			}


			ImGui::EndPopup();

		}
	}
}

void WinHierarchy::ShowGameObjects(GameObject* go)
{

	ImGuiTreeNodeFlags nodeFlags = ImGuiDockNodeFlags_None;
	nodeFlags += ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

	if (go->children.size() == 0)
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	}

	if (go == app->uiController->GetGameObjSelected())
	{
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	};

	bool nodeOpen = ImGui::TreeNodeEx(go->name.c_str(), nodeFlags);
	if (go->children.size() == 0)nodeOpen = false;

	if (ImGui::IsItemClicked(0)) 
	{
		app->uiController->SetGameObjSelected(go);
	}

	if (go->parent != nullptr)
	{
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("GameObject", go, sizeof(GameObject*));

			goToDrop = go;

			ImGui::Text("Where do you want to drop this in the hierarchy ? ");

			ImGui::EndDragDropSource();
		}
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GameObject"))
		{
			//Not working as intended
			GameObject* temp = (GameObject*)payload->Data;

			goToDrop->SetParent(go);

			goToDrop = nullptr;
		}

		ImGui::EndDragDropTarget();
	}
	
	if (nodeOpen && go->children.size() != 0)
	{
		
		for (int i = 0; i < go->children.size(); i++)
		{
			ShowGameObjects(go->children[i]);
		}
		//Peta al fer pop de sceneroot fix it
		
		if (go->children.size() != 0)
		{
			ImGui::TreePop();
		}
	}

	
}


#include "WinHierarchy.h"
#include "ImGuiUtils.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleRenderer3D.h"
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

			if (ImGui::BeginPopupContextWindow("Primitives", ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonDefault_))
			{
				if (ImGui::BeginMenu("Primitives"))
				{
					if (ImGui::MenuItem("Cube"))
					{
						app->renderer3D->LoadModelImporter("../Output/Assets/Primitives/Cube.fbx");
					}
					if (ImGui::MenuItem("Sphere"))
					{
						app->renderer3D->LoadModelImporter("../Output/Assets/Primitives/Sphere.fbx");
					}
					if (ImGui::MenuItem("Monkey"))
					{
						app->renderer3D->LoadModelImporter("../Output/Assets/Primitives/Monkey.fbx");
					}
					if (ImGui::MenuItem("Plane"))
					{
						app->renderer3D->LoadModelImporter("../Output/Assets/Primitives/Plane.fbx");
					}
					if (ImGui::MenuItem("Pyramid"))
					{
						app->renderer3D->LoadModelImporter("../Output/Assets/Primitives/Pyramid.fbx");
					}
					if (ImGui::MenuItem("Cylinder"))
					{
						app->renderer3D->LoadModelImporter("../Output/Assets/Primitives/Cylinder.fbx");
					}

					ImGui::EndMenu();
				}
					

				ImGui::EndPopup();
				
			}

		}
		ImGui::End();
	}
}

void WinHierarchy::ShowGameObjects(GameObject* go)
{

	ImGuiTreeNodeFlags nodeFlags = ImGuiDockNodeFlags_None;
	nodeFlags += ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

	if (go->children.size() == 0)
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;

	bool nodeOpen = ImGui::TreeNodeEx(go->name.c_str(), nodeFlags);
	if (go->children.size() == 0)nodeOpen = false;

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("GameObject", go, sizeof(GameObject*));

		goToDrop = go;

		ImGui::Text("Where do you want to drop this in the hierarchy ? ");

		ImGui::EndDragDropSource();
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

void WinHierarchy::DisplayGameObject(GameObject* go)
{
	

	
}

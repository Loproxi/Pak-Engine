#include "Comp_Camera.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "Camera3D.h"
#include "ImGuiUtils.h"
#include "ModuleWindow.h"


Comp_Camera::Comp_Camera(GameObject* go):Component(go)
{
	app = Application::GetInstance();
	camera = app->camera->AddCamera();
	camera->SetUpFrameBuffer(app->window->GetScreenWidth(), app->window->GetScreenHeight());
	camera->SetAsGameCamera();
}

Comp_Camera::~Comp_Camera()
{
}

void Comp_Camera::Update()
{
}

void Comp_Camera::OnUIController()
{
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{

		//if (ImGui::SliderInt("FOV"))
		//{
	
		//}

		ImGui::DragFloat("Near plane Distance ", &camera->CameraFrustrum.nearPlaneDistance, 0.1f, 0.01);

		ImGui::DragFloat("Far plane Distance ", &camera->CameraFrustrum.farPlaneDistance, 1.0f, 0.01);

		if (ImGui::Button("Set as Game Camera "))
		{
			this->camera->SetAsGameCamera();
		}

	}
}

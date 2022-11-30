#include "WinScene.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModuleUIcontroller.h"
#include "imgui.h"
#include "Comp_MeshRenderer.h"

WinScene::WinScene()
{
	
	name = "Scene";
	app = Application::GetInstance();
}

WinScene::~WinScene()
{
}

void WinScene::Start()
{
	app->AddLog(Logs::NORMAL, "WinScene Created");
	
}

void WinScene::Draw()
{
	if (ImGui::Begin(name.c_str(),&isEnabled))
	{
		ImVec2 size = ImGui::GetContentRegionAvail();
		if (size.x != app->camera->scenecam.framebuffer.GetWidthFrame() || size.y != app->camera->scenecam.framebuffer.GetHeightFrame())
		{
			
			//app->camera->scenecam.framebuffer.SettingUpFrameBuffer(size.x, size.y);
			app->camera->scenecam.SetAspectRatio(size.x, size.y);
		}
		
		ImGui::Image((ImTextureID)app->camera->scenecam.framebuffer.GetTextureBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

		if (app->uiController->GetGameObjSelected()!= nullptr)
		{

			if (ImGui::IsMouseClicked(0))
			{
				//ScreenPos 
				ImVec2 mouseposinscreen = ImGui::GetMousePos();
				ImVec2 winscenepos = ImGui::GetWindowPos();
				//Position in win scene
				ImVec2 mouseposinwinscene;
				mouseposinwinscene.x = (mouseposinscreen.x - winscenepos.x);
				mouseposinwinscene.y = mouseposinscreen.y - (winscenepos.y + ImGui::GetFrameHeight());
				
				//normalize mouse pos in win scene
				ImVec2 mousewinscenenorm;
				mousewinscenenorm.x = mouseposinwinscene.x / ImGui::GetWindowSize().x;
				mousewinscenenorm.y = mouseposinwinscene.y / (ImGui::GetWindowSize().y - ImGui::GetFrameHeight());
				
				//Transform each point into the center of win scene
				mousewinscenenorm.x = (mousewinscenenorm.x - 0.5f) / 0.5f;
				mousewinscenenorm.y = -(mousewinscenenorm.y - 0.5f) / 0.5f;
				LOG("Position : %f,%f", mousewinscenenorm.x, mousewinscenenorm.y);

				LineSegment picking = app->camera->scenecam.CameraFrustrum.UnProjectLineSegment(mousewinscenenorm.x, mousewinscenenorm.y);

				Comp_MeshRenderer* meshhit = app->renderer3D->RayIntersects(picking);
				
				if (meshhit != nullptr)
				{
					app->uiController->SetGameObjSelected(meshhit->comp_owner);
				}
				else
				{
					app->uiController->SetGameObjSelected(nullptr);
				}
				app->renderer3D->trihitsdistmap.clear();
				
			}
		}

	}
	ImGui::End();
}

#include "WinScene.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModuleUIcontroller.h"
#include "imgui.h"

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
	}
	ImGui::End();
}

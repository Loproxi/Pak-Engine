#include "WinGame.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ImGuiUtils.h"

WinGame::WinGame()
{
	name = "Game";
	app = Application::GetInstance();
	
}

WinGame::~WinGame()
{
}

void WinGame::Start()
{
	app->AddLog(Logs::NORMAL, "WinGame Created");
}

void WinGame::Draw()
{
	//framebuffer = &app->camera->gamecamactive->framebuffer;
	if (ImGui::Begin(name.c_str(), &isEnabled))
	{
		
		if (app->camera->gamecams.size() != 0 && app->camera->gamecamactive != nullptr)
		{
			ImVec2 size = ImGui::GetContentRegionAvail();
			if (size.x != app->camera->gamecamactive->framebuffer.GetWidthFrame() || size.y != app->camera->gamecamactive->framebuffer.GetHeightFrame())
			{

				//app->camera->gamecamactive->framebuffer.SettingUpFrameBuffer(size.x, size.y);
				app->camera->gamecamactive->SetAspectRatio(size.x, size.y);
			}
			ImGui::Image((ImTextureID)app->camera->gamecamactive->framebuffer.GetTextureBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
		}
		else
		{
			ImGui::SetWindowFontScale(2.0f);
			
			ImGui::TextCentered("There are no Game Cameras Available");
		}
	}
	ImGui::End();
}

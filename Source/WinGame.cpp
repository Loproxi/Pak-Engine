#include "WinGame.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ImGuiUtils.h"

WinGame::WinGame()
{
	name = "Game";
	app = Application::GetInstance();
	framebuffer = &app->camera->gamecams.at(0)->framebuffer;
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
	if (ImGui::Begin(name.c_str(), &isEnabled))
	{
		ImVec2 size = ImGui::GetContentRegionAvail();
		if (size.x != framebuffer->GetWidthFrame() || size.y != framebuffer->GetHeightFrame())
		{

			framebuffer->SettingUpFrameBuffer(size.x, size.y);
		}

		ImGui::Image((ImTextureID)framebuffer->GetTextureBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
}

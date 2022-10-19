#include "WinScene.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleUIcontroller.h"
#include "imgui.h"

WinScene::WinScene()
{
	
	name = "Scene";
	app = Application::GetInstance();
	framebuffer = app->renderer3D->GetFrameBufferRef();
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
		if (size.x != framebuffer->GetWidthFrame() || size.y != framebuffer->GetHeightFrame())
		{
			
			framebuffer->SettingUpFrameBuffer(size.x, size.y);
		}
		
		ImGui::Image((ImTextureID)framebuffer->GetTextureBuffer(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	}
	ImGui::End();
}

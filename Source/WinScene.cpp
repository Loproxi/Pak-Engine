#include "WinScene.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
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
	framebuffer = app->renderer3D->GetFrameBufferRef();
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
		
		ImGui::Image((ImTextureID)framebuffer->GetTextureBuffer(), {(float)framebuffer->GetWidthFrame(),(float)framebuffer->GetHeightFrame()});
	}
	ImGui::End();
}

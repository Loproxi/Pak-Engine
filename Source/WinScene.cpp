#include "WinScene.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "imgui.h"

WinScene::WinScene()
{
	isEnabled = true;
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
	if (ImGui::Begin("Scene",&isEnabled))
	{
		ImGui::Image((ImTextureID)framebuffer->GetTextureBuffer(), ImGui::GetContentRegionAvail());
	}
	ImGui::End();
}

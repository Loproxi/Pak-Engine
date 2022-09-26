#include "WinConfig.h"
#include "Globals.h"
#include "imgui.h"
#include "SDL.h"
#include "Application.h";
#include "ModuleWindow.h"

WinConfig::WinConfig()
{
	name = "Configuration";

	app = Application::GetInstance();

}

WinConfig::~WinConfig()
{
}

void WinConfig::Draw()
{

	if (ImGui::Begin(name.c_str(), &isEnabled))
	{

		if (ImGui::CollapsingHeader("Application"))
		{
			
		}
		if (ImGui::CollapsingHeader("Window"))
		{
			if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f))
			{
				SDL_SetWindowBrightness(app->window->window, brightness);
			}
			if (ImGui::SliderInt("Width", &width, 640, 3000))
			{
				app->window->SetScreenWidth(width);
			}
			if(ImGui::SliderInt("Height", &height, 360, 2000))
			{
				app->window->SetScreenHeight(height);
			}
			ImGui::Text("Refresh Rate: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f), "%u", app->window->GetRefreshRate());
			
		}
		
	}
	ImGui::End();

}

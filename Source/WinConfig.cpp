#include "WinConfig.h"
#include "Globals.h"
#include "imgui.h"
#include "SDL.h"
#include "Application.h";
#include "ModuleWindow.h"
#include "ImGuiUtils.h"

WinConfig::WinConfig()
{
	name = "Configuration";

	app = Application::GetInstance();

	hw.ram = SDL_GetSystemRAM();

	hw.cpu_count = SDL_GetCPUCount();

	hw.cacheline = SDL_GetCPUCacheLineSize();

	frames.reserve(120);

	limitframerate = app->GetFrameRateLimit();
	
}

WinConfig::~WinConfig()
{
}

void WinConfig::Draw()
{
	FrameInfoLogic();

	if (ImGui::Begin(name.c_str(), &isEnabled))
	{

		if (ImGui::CollapsingHeader("Application"))
		{
			ImGui::SliderInt("FPS CAP", &limitframerate, 1, 360);
			app->SetFrameRateLimit(limitframerate);
			ImGui::PlotHistogram("##Framerate", &frames.front(),frames.size(),0,title,0.0f,120,ImVec2(310,120));
			

		}
		if (ImGui::CollapsingHeader("Window"))
		{
			WindowHeader();
			
		}
		if (ImGui::CollapsingHeader("Hardware"))
		{
			HardwareHeader();
		}
	}
	ImGui::End();

}

void WinConfig::FrameInfoLogic()
{
	if (frames.size() == frames.capacity())
	{
		std::vector<float>::iterator iterator = frames.begin();
		frames.erase(iterator);
		frames.push_back(app->GetFrameRateLimit());
	}
	else
	{
		frames.push_back(app->GetFrameRateLimit());
	}
	sprintf_s(title, 20, "Framerate %.1f", frames.back());
}

void WinConfig::WindowHeader()
{
	width = app->window->GetScreenWidth();

	height = app->window->GetScreenHeight();

	if (ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f))
	{
		SDL_SetWindowBrightness(app->window->window, brightness);
	}
	if (ImGui::SliderInt("Width", &width, 640, 3000))
	{
		app->window->SetScreenWidth(width);
	}
	if (ImGui::SliderInt("Height", &height, 360, 2000))
	{
		app->window->SetScreenHeight(height);
	}
	ImGui::Text("Refresh Rate: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%u", app->window->GetRefreshRate());
	if (ImGui::Checkbox("Fullscreen", &fullscreen))
	{
		app->window->SetFullScreenOrFullScreenDesktop(fullscreen);
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Resizable", &resizable))
	{
		app->window->SetWindowResizable(resizable);
	}
	if (ImGui::Checkbox("Borderless", &borderless))
	{
		app->window->SetWindowBorderless(borderless);
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("FullDesktop", &fulldesktop))
	{

		app->window->SetFullScreenOrFullScreenDesktop(fulldesktop, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}

void WinConfig::HardwareHeader()
{
	ImGui::TextWrapped("CPUs: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string(hw.cpu_count).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Cores");
	ImGui::TextWrapped("Cache: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string(hw.cacheline).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Bytes");
	ImGui::TextWrapped("RAM: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string((hw.ram / 1024)).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Gb");
}



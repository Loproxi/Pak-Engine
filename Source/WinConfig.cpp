#include "WinConfig.h"
#include "Globals.h"
#include "imgui.h"
#include "SDL.h"
#include "Application.h";
#include "ModuleRenderer3D.h"
#include "ModuleUIcontroller.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ImGuiUtils.h"
#include "gpudetect/DeviceId.h"

WinConfig::WinConfig()
{
	name = "Configuration";

	app = Application::GetInstance();

	hw.ram = SDL_GetSystemRAM();

	hw.cpu_count = SDL_GetCPUCount();

	hw.cacheline = SDL_GetCPUCacheLineSize();

	getGraphicsDeviceInfo(0, 0, 0, &hw.vrambudgetmb, &hw.vramcurrentusagemb, &hw.vramavailablemb, &hw.vramreservedmb);

	frames.reserve(120);
	ms.reserve(120);

	limitframerate = app->GetFrameRateLimit();

	fullscreen = app->window->GetFullscreen();
	resizable = app->window->GetResizable();
	borderless = app->window->GetBorderless();
	fulldesktop = app->window->GetFullscreenDesktop();
	vsync = app->renderer3D->GetVsync();
	depthtest = app->renderer3D->GetDepthTest();
	cullface = app->renderer3D->GetCullFace();
	lighting = app->renderer3D->GetLightning();
	wireframe = app->renderer3D->GetWireframe();
}

WinConfig::~WinConfig()
{
	frames.clear();
	ms.clear();
	
}

void WinConfig::Start()
{
	app->uiController->ReportLog("WinConfig Created");
}

void WinConfig::Draw()
{
	

	if (ImGui::Begin(name.c_str(), &isEnabled))
	{

		if (ImGui::CollapsingHeader("Application"))
		{
			ApplicationHeader();

		}
		if (ImGui::CollapsingHeader("Window"))
		{
			WindowHeader();
			
		}
		if (ImGui::CollapsingHeader("Renderer"))
		{
			RendererHeader();
		}
		if (ImGui::CollapsingHeader("Input"))
		{
			app->input->GetMousePosition(&mousepositionX, &mousepositionY);
			//SDL_GetMouseState(&mousepositionX, &mousepositionY);
			
			ImGui::TextWrapped("Mouse Position: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string(mousepositionX).c_str());
			ImGui::SameLine();
			ImGui::TextWrapped(",");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string(mousepositionY).c_str());


		}
		if (ImGui::CollapsingHeader("Hardware"))
		{
			HardwareHeader();
		}
	}
	ImGui::End();

}



void WinConfig::ApplicationHeader()
{
	FrameInfoLogic();
	MsInfoLogic();
	ImGui::SliderInt("MAX FPS", &limitframerate, 1, 360);
	app->SetFrameRateLimit(limitframerate);
	ImGui::PlotHistogram("##Framerate", &frames.front(), frames.size(), 0, title, 0.0f, 120, ImVec2(310, 120));
	ImGui::PlotHistogram("##Deltatime", &ms.front(), ms.size(), 0, title2, 0.0f, 120, ImVec2(310, 120));
	
}

void WinConfig::MsInfoLogic()
{
	if (ms.size() == ms.capacity())
	{
		std::vector<float>::iterator iterator = ms.begin();
		ms.erase(iterator);
		ms.push_back(app->GetDeltaTime_MS());
	}
	else
	{
		ms.push_back(app->GetDeltaTime_MS());
	}
	sprintf_s(title2, 20, "Miliseconds %.1f", ms.back());
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
	if (ImGui::Checkbox("Fullscreen", fullscreen))
	{
		app->window->SetFullScreen();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Resizable", resizable))
	{
		app->window->SetWindowResizable();
	}
	if (ImGui::Checkbox("Borderless", borderless))
	{
		app->window->SetWindowBorderless();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("FullDesktop", fulldesktop))
	{
		app->window->SetFullScreenDesktop();
	}
}

void WinConfig::RendererHeader()
{
	if (ImGui::Checkbox("Vsync    ", &vsync))
	{
		app->renderer3D->SetVsync(vsync);
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("DepthTest", depthtest))
	{
		app->renderer3D->SetDepthTest();
	}
	if (ImGui::Checkbox("CullFace ", cullface))
	{
		app->renderer3D->SetCullFace();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Lighting ", lighting))
	{
		app->renderer3D->SetLightning();
	}
	if (ImGui::Checkbox("Wireframe", wireframe))
	{
		app->renderer3D->SetWireframe();
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
	ImGui::TextWrapped("VRAM Budget: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string((hw.vrambudgetmb / (1024.f * 1024.f))).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Mb");
	ImGui::TextWrapped("VRAM Current Usage: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string((hw.vramcurrentusagemb / (1024.f * 1024.f))).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Mb");
	ImGui::TextWrapped("VRAM Available: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string((hw.vramavailablemb / (1024.f * 1024.f))).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Mb");
	ImGui::TextWrapped("VRAM Reserved: ");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), std::to_string((hw.vramreservedmb / (1024.f * 1024.f))).c_str());
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0, 1.0f), " Mb");

}


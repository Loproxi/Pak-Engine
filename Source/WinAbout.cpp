#include "WinAbout.h"
#include "Globals.h"
#include "Application.h"
#include "ImGuiUtils.h"
#include "SDL.h"
#include "MathGeoLib.h"
#include "glew.h"
#include "ModuleUIcontroller.h"
#include "assimp/version.h"




WinAbout::WinAbout()
{
	name = "About";

	app = Application::GetInstance();
	
	SDL_version sdlVersion;
	SDL_GetVersion(&sdlVersion);
	verSDL = "SDL version " + std::to_string(sdlVersion.major) + "." + std::to_string(sdlVersion.minor) + "." + std::to_string(sdlVersion.patch);

	verGlew = "Glew version ";
	verGlew += (const char*)glewGetString(GLEW_VERSION);

	verImGui = "ImGui version " + (std::string)ImGui::GetVersion();

	verMathGeoLib = "MathGeoLib version 1.5";

	verOpenGL = "OpenGL version ";
	verOpenGL += (const char*)glGetString(GL_VERSION);

	verAssimp = "Assimp version ";
	verAssimp += std::to_string(aiGetVersionMajor()) + "." + std::to_string(aiGetVersionMinor()) + "." + std::to_string(aiGetVersionRevision());

	verDevil = "DevIL  v1.8.0 ";
		
}

WinAbout::~WinAbout()
{
}

void WinAbout::Start()
{
	app->AddLog(Logs::NORMAL, "WinAbout Created");
}

void WinAbout::Draw()
{
	
	if (ImGui::Begin(name.c_str(),&isEnabled))
	{

		ImGui::TextWrapped("Pak-Engine v%s", app->GetPakEngineVersion().c_str());
		ImGui::Spacing();
		ImGui::TextWrapped("My First 3D Game Engine");
		ImGui::Spacing();
		ImGui::TextURL("Developed by Pol Rius Banus (Loproxi)", "https://github.com/Loproxi/Pak-Engine",0,0);
		ImGui::NewLine();
		
		
		GetLibVersionsAndPrint();

		LicenseText();

	}
	ImGui::End();
}

void WinAbout::LicenseText()
{
	ImGui::TextWrapped("License:");
	ImGui::Spacing();
	ImGui::TextWrapped("MIT License");
	ImGui::NewLine();
	ImGui::TextWrapped("Copyright (c) 2022 Loproxi");
	ImGui::NewLine();
	ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the \Software\), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions : ");
	ImGui::NewLine();
	ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");
	ImGui::NewLine();
	ImGui::TextWrapped("THE SOFTWARE IS PROVIDED \AS IS\, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
}

void WinAbout::GetLibVersionsAndPrint()
{
	
	ImGui::TextWrapped("3rd Party Libraries used:");
	ImGui::Spacing();

	ImGui::BulletText(""); ImGui::TextURL(verSDL.c_str(), "https://libsdl.org/index.php", 1, 0);
	ImGui::NewLine();

	ImGui::BulletText(""); ImGui::TextURL(verGlew.c_str(), "http://glew.sourceforge.net/", 1, 0);
	ImGui::NewLine();

	ImGui::BulletText(""); ImGui::TextURL(verImGui.c_str(), "https://github.com/ocornut/imgui", 1, 0);
	ImGui::NewLine();

	ImGui::BulletText(""); ImGui::TextURL(verMathGeoLib.c_str(), "https://github.com/juj/MathGeoLib", 1, 0);
	ImGui::NewLine();

	ImGui::BulletText(""); ImGui::TextURL(verOpenGL.c_str(), "https://www.opengl.org/", 1, 0);
	ImGui::NewLine();

	ImGui::BulletText(""); ImGui::TextURL(verAssimp.c_str(), "https://assimp-docs.readthedocs.io/en/v5.1.0/", 1, 0);
	ImGui::NewLine();

	ImGui::BulletText(""); ImGui::TextURL(verDevil.c_str(), "http://openil.sourceforge.net/", 1, 0);
	ImGui::NewLine();
}




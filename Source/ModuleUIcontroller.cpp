#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "Application.h"

#include "ModuleUIcontroller.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"
#include "WinAbout.h"
#include "WinConfig.h"
#include "WinScene.h"
#include "WinConsole.h"
#include "WinHierarchy.h"


ModuleUIcontroller::ModuleUIcontroller(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleUIcontroller::~ModuleUIcontroller()
{
}

bool ModuleUIcontroller::Init(pugi::xml_node& config)
{
	bool ret = true;

	
	/*const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);*/

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	winenable[(uint)UIwindows::SCENE] = config.child("Editor").child("window_scene").attribute("value").as_bool();
	winenable[(uint)UIwindows::CONFIGURATION] = config.child("Editor").child("window_config").attribute("value").as_bool();
	winenable[(uint)UIwindows::ABOUT] = config.child("Editor").child("window_about").attribute("value").as_bool();
	winenable[(uint)UIwindows::CONSOLE] = config.child("Editor").child("window_console").attribute("value").as_bool();
	winenable[(uint)UIwindows::HIERARCHY] = config.child("Editor").child("window_hierarchy").attribute("value").as_bool();

	return ret;
}

bool ModuleUIcontroller::Start()
{
	bool ret = true;

	//Must be here because in init the render context hasn't been created yet.
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->GetSDL_GLContext());
	ImGui_ImplOpenGL3_Init();

	windows[(uint)UIwindows::SCENE] = new WinScene();
	windows[(uint)UIwindows::CONFIGURATION] = new WinConfig();
	windows[(uint)UIwindows::ABOUT] = new WinAbout();
	windows[(uint)UIwindows::CONSOLE] = new WinConsole();
	windows[(uint)UIwindows::HIERARCHY] = new WinHierarchy();

	for (uint i = 0; i < (uint)UIwindows::MAX; i++)
	{
		windows[i]->isEnabled = winenable[i];
		windows[i]->Start();
	}

	return ret;
}

UpdateStatus ModuleUIcontroller::PreUpdate()
{
	UpdateStatus ret = UpdateStatus::UPDATE_CONTINUE;

	

	return ret;
}

UpdateStatus ModuleUIcontroller::Update()
{
	UpdateStatus ret = UpdateStatus::UPDATE_CONTINUE;

	return ret;
}

UpdateStatus ModuleUIcontroller::PostUpdate()
{
	UpdateStatus ret = UpdateStatus::UPDATE_CONTINUE;
	/*if (!Draw())
	{
		ret = UpdateStatus::UPDATE_STOP;
	};*/
	

	return ret;
}

bool ModuleUIcontroller::Draw()
{
	bool ret = true;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	// Docking
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	//Draw Menu
	MainMenuBar(ret);

	for ( int i = 0; i < (uint)UIwindows::MAX;i++)
	{
		if (windows[i]->isEnabled)
		{
			windows[i]->Draw();
		}

	}

	//Render
	RenderImGui();

	return ret;
}

void ModuleUIcontroller::RenderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void ModuleUIcontroller::MainMenuBar(bool& ret)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close , Alt+F4"))
			{
				//Do something
				ret = false;
			}

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Editor"))
		{
			if (ImGui::MenuItem("Configuration"))
			{
				//Do something
				windows[(uint)UIwindows::CONFIGURATION]->isEnabled = true;
			}
			if (ImGui::MenuItem("Scene"))
			{
				//Do something
				windows[(uint)UIwindows::SCENE]->isEnabled = true;
			}
			if (ImGui::MenuItem("Console"))
			{
				//Do something
				windows[(uint)UIwindows::CONSOLE]->isEnabled = true;
			}
			if (ImGui::MenuItem("Hierarchy"))
			{
				//Do something
				windows[(uint)UIwindows::HIERARCHY]->isEnabled = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("ImGui Demo"))
			{
				//Do something
				show_demo_window = !show_demo_window;
			}
			if (ImGui::MenuItem("Documentation"))
			{
				//Do something
				ShellExecute(0, 0, "https://github.com/Loproxi/Pak-Engine/wiki", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("Download latest"))
			{
				//Do something
				ShellExecute(0, 0, "https://github.com/Loproxi/Pak-Engine/releases", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("Report a bug"))
			{
				//Do something
				ShellExecute(0, 0, "https://github.com/Loproxi/Pak-Engine/issues", 0, 0, SW_SHOW);
			}
			if (ImGui::MenuItem("About"))
			{
				//Do something
				windows[(uint)UIwindows::ABOUT]->isEnabled = true;
			}

			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
	}

	
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow();
	}
}


bool ModuleUIcontroller::SaveSettings(pugi::xml_node& config)
{
	config.child("Editor").child("window_scene").attribute("value") = windows[(uint)UIwindows::SCENE]->isEnabled;
	config.child("Editor").child("window_config").attribute("value") = windows[(uint)UIwindows::CONFIGURATION]->isEnabled;		
	config.child("Editor").child("window_about").attribute("value") = windows[(uint)UIwindows::ABOUT]->isEnabled;
	config.child("Editor").child("window_console").attribute("value") = windows[(uint)UIwindows::CONSOLE]->isEnabled;
	config.child("Editor").child("window_hierarchy").attribute("value") = windows[(uint)UIwindows::HIERARCHY]->isEnabled;

	return true;
}


bool ModuleUIcontroller::CleanUp()
{
	bool ret = true;

	for (int i = 0; i < (uint)UIwindows::MAX; i++)
	{
		
		delete windows[i];
		windows[i] = nullptr;

	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return ret;
}

WindowBaseClass* ModuleUIcontroller::GetEditorWindow(UIwindows type)
{
	uint vecPosition = (uint)type;
	
	if (vecPosition < (uint)UIwindows::MAX)
	{
		return windows[vecPosition];
	}
	return nullptr;
}

void ModuleUIcontroller::ReportLog(std::string msg)
{
	WinConsole* temp = (WinConsole*)App->uiController->GetEditorWindow(UIwindows::CONSOLE);

	//temp->AddLog(msg);
}
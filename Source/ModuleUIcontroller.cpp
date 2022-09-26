#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "Application.h"

#include "ModuleUIcontroller.h"
#include "ModuleRenderer3D.h"
#include "ModuleWindow.h"
#include "WinAbout.h"
#include "WinConfig.h"


ModuleUIcontroller::ModuleUIcontroller(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleUIcontroller::~ModuleUIcontroller()
{
}

bool ModuleUIcontroller::Init()
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

	

	

	return ret;
}

bool ModuleUIcontroller::Start()
{
	bool ret = true;

	//Must be here because in init the render context hasn't been created yet.
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->GetSDL_GLContext());
	ImGui_ImplOpenGL3_Init();

	windows[(uint)UIwindows::CONFIGURATION] = new WinConfig();
	windows[(uint)UIwindows::ABOUT] = new WinAbout();
	

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

	if (!Draw())
	{
		ret = UpdateStatus::UPDATE_STOP;
	};

	return ret;
}

UpdateStatus ModuleUIcontroller::PostUpdate()
{
	UpdateStatus ret = UpdateStatus::UPDATE_CONTINUE;

	

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

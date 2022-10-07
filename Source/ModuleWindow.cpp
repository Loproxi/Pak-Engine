#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = nullptr;
	screen_surface = nullptr;
	SetNameOfModule("Window");
	width = 1280;
	height = 720;
	fullscreen = resizable = borderless = fullscreen_desktop = false;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init(pugi::xml_node& config)
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		/*width = SCREEN_WIDTH * SCREEN_SIZE;
		height = SCREEN_HEIGHT * SCREEN_SIZE;*/
		width = config.child("Window").child("resolution").attribute("width").as_int();
		height = config.child("Window").child("resolution").attribute("height").as_int();
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		fullscreen = config.child("Window").child("fullscreen").attribute("value").as_bool();
		resizable = config.child("Window").child("resizable").attribute("value").as_bool();
		borderless = config.child("Window").child("borderless").attribute("value").as_bool();
		fullscreen_desktop = config.child("Window").child("fullscreen_window").attribute("value").as_bool();

		if(fullscreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if(resizable == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}
		if(borderless == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		if(fullscreen_desktop == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(App->GetTitle(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

bool ModuleWindow::SaveSettings(pugi::xml_node& config)
{
	config.child("Window").child("resolution").attribute("width") = width;
	config.child("Window").child("resolution").attribute("height") = height;

	config.child("Window").child("fullscreen").attribute("value").set_value(fullscreen);
	config.child("Window").child("resizable").attribute("value") = resizable;
	config.child("Window").child("borderless").attribute("value") = borderless;
	config.child("Window").child("fullscreen_window").attribute("value").set_value(fullscreen_desktop);

	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

const char* ModuleWindow::GetTitle()
{
	return title.c_str();
}

void ModuleWindow::SetOrganization(const char* org)
{
	organization = org;
}

const char* ModuleWindow::GetOrganization()
{
	return organization.c_str();
}


void ModuleWindow::SetScreenWidth(int width)
{
	
	SDL_SetWindowSize(window, width, GetScreenHeight());

	SDL_GetWindowSize(window, &this->width, NULL);
	
}

void ModuleWindow::SetScreenHeight(int height)
{
	SDL_SetWindowSize(window, GetScreenWidth(), height);

	SDL_GetWindowSize(window, NULL, &this->height);
}

uint ModuleWindow::GetRefreshRate()
{

	SDL_DisplayMode displaymode;

	if (SDL_GetDisplayMode(0, 0, &displaymode) != 0)
	{
		SDL_Log("SDL_GetDisplayMode failed: %s", SDL_GetError());
		return 1;
	}
	else
	{
		return (uint)displaymode.refresh_rate;
	}

}

void ModuleWindow::SetFullScreen()
{
	fullscreen ? SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) : SDL_SetWindowFullscreen(window, 0);
}

void ModuleWindow::SetFullScreenDesktop()
{
	if (fullscreen_desktop)
	{
		if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
		{
			SDL_Log("SDL_SetWindowFullscreen failed: %s", SDL_GetError());
			return;
		}
		
	}
	else
	{
		if (SDL_SetWindowFullscreen(window, 0) != 0)
		{
			SDL_Log("SDL_SetWindowFullscreen failed: %s", SDL_GetError());
			return;
		}
	}
}

void ModuleWindow::SetWindowBorderless()
{

	if (borderless)
	{
		SDL_SetWindowBordered(window, SDL_FALSE);
	}
	else
	{
		SDL_SetWindowBordered(window, SDL_TRUE);
	}

}

void ModuleWindow::SetWindowResizable()
{

	if (resizable)
	{
		
		SDL_SetWindowResizable(window, SDL_TRUE);
		
	}
	else
	{
		
		SDL_SetWindowResizable(window, SDL_FALSE);
	}
	
}



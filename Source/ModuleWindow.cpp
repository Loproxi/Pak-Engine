#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = nullptr;
	screen_surface = nullptr;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
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
		width = SCREEN_WIDTH * SCREEN_SIZE;
		height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

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

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
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

void ModuleWindow::SetFullScreenOrFullScreenDesktop(bool fullscreen, SDL_WindowFlags flag)
{
	if (fullscreen)
	{
		if (SDL_SetWindowFullscreen(window, flag) != 0)
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

void ModuleWindow::SetWindowBorderless(bool borderless)
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

void ModuleWindow::SetWindowResizable(bool resizable)
{

	if (resizable)
	{
		SDL_SetWindowResizable(window, SDL_TRUE);
		
	}
	else
	{
		SDL_SetWindowResizable(window, SDL_FALSE);
	}
	SDL_GetWindowSize(window, &this->width,&this->height);
}



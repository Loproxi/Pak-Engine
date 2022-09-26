#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "External/SDL/include/SDL.h"

typedef unsigned int uint;

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	int GetScreenWidth() { return width; }

	int GetScreenHeight() { return height; }

	void SetScreenWidth(int width);
	
	void SetScreenHeight(int height);

	uint GetRefreshRate();
	

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

private:
	int width;
	int height;
};

#endif // __ModuleWindow_H__
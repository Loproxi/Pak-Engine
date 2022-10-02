#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "External/SDL/include/SDL.h"
#include <string>

typedef unsigned int uint;

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init(pugi::xml_node& config);
	bool CleanUp();

	bool SaveSettings(pugi::xml_node& config);

	//Getters
	const char* GetTitle();
	const char* GetOrganization();
	bool* GetFullscreen() { return &fullscreen; }
	bool* GetResizable() { return &resizable; }
	bool* GetBorderless() { return &borderless; }
	bool* GetFullscreenDesktop() { return &fullscreen_desktop; }
	int GetScreenWidth() { return width; }
	int GetScreenHeight() { return height; }
	uint GetRefreshRate();

	//Setters
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
	void SetTitle(const char* title);
	void SetOrganization(const char* organization);
	void SetFullScreen();
	void SetFullScreenDesktop();
	//This Doesn't work on fullscreen mode
	void SetWindowBorderless();
	//This Doesn't work on fullscreen mode
	void SetWindowResizable();

public:
	//The window we'll be rendering to
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screen_surface = nullptr;

private:
	int width;
	int height;
	bool fullscreen, resizable, borderless, fullscreen_desktop;
	std::string title;
	std::string organization;
};

#endif // __ModuleWindow_H__
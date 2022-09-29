#ifndef __MODULERENDERER3D_H__
#define __MODULERENDERER3D_H__

#include "Module.h"
#include "Light.h"


#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init(pugi::xml_node& config);
	UpdateStatus PreUpdate();
	UpdateStatus PostUpdate();
	bool CleanUp();
	bool SaveSettings(pugi::xml_node& config);

	bool GetVsync() { return vsync; }

	void SetVsync(bool vsync);

	void OnResize(int width, int height);

	SDL_GLContext GetSDL_GLContext() { return context; }

public:

	Light lights[MAX_LIGHTS];
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

private:

	SDL_GLContext context;
	bool vsync;
	
};

#endif // !__MODULERENDERER3D_H__
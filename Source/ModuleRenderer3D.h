#ifndef __MODULERENDERER3D_H__
#define __MODULERENDERER3D_H__

#include "Module.h"
#include "Light.h"
#include "FrameBuffer.h"
#include "Primitive.h"
#include "ModelImporter.h"

#define MAX_LIGHTS 8

struct RenderStuff
{
	bool vsync;
	bool depthtest;
	bool cullface;
	bool lighting;
	bool wireframe;
};

class Primitive;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init(pugi::xml_node& config);
	bool Start();
	bool CleanUp();

	UpdateStatus PreUpdate();
	UpdateStatus PostUpdate();


	bool SaveSettings(pugi::xml_node& config);
	void OnResize(int width, int height);

	void LoadImporter(std::string path);

	//Getters
	SDL_GLContext GetSDL_GLContext() { return context; }
	bool GetVsync() { return renderstuff.vsync; }
	bool* GetDepthTest() { return &renderstuff.depthtest; }
	bool* GetCullFace() { return &renderstuff.cullface; }
	bool* GetLightning() { return &renderstuff.lighting; }
	bool* GetWireframe() { return &renderstuff.wireframe; }
	FrameBuffer* GetFrameBufferRef() { return &framebuffer; }

	//Setters
	void SetVsync(bool vsync);
	void SetDepthTest();
	void SetCullFace();
	void SetLightning();
	void SetWireframe();

public:

	Light lights[MAX_LIGHTS];
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	Cube* cube;
	Spheree sphere;
	Pyramid pyramid;
	Mesh* test;
	Mesh prueba1;
	Mesh prueba2;
	ModelImporter house;
private:

	std::vector<ModelImporter*>models;

	ModelImporter* currentModel;
	
	FrameBuffer framebuffer;

	SDL_GLContext context;
	
	RenderStuff renderstuff;
};

#endif // !__MODULERENDERER3D_H__
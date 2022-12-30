#ifndef __MODULERENDERER3D_H__
#define __MODULERENDERER3D_H__

#include "Module.h"
#include "Light.h"
#include "FrameBuffer.h"
#include "Primitive.h"
#include "ModelImporter.h"
#include "Shaders.h"
#include <map>

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
class Comp_MeshRenderer;
class Camera3D;
struct Texture;

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

	void LoadModelImporter(std::string path);
	void LoadTextureImporter(std::string path);

	void AddDebug(/*float3* points*/);

	Comp_MeshRenderer* RayIntersects(LineSegment& line);

	void DrawTransparentObjects(std::map<float, Comp_MeshRenderer*>& transMeshes);

	//Getters
	SDL_GLContext GetSDL_GLContext() { return context; }
	bool GetVsync() { return renderstuff.vsync; }
	bool* GetDepthTest() { return &renderstuff.depthtest; }
	bool* GetCullFace() { return &renderstuff.cullface; }
	bool* GetLightning() { return &renderstuff.lighting; }
	bool* GetWireframe() { return &renderstuff.wireframe; }

	//Setters
	void SetVsync(bool vsync);
	void SetDepthTest();
	void SetCullFace();
	void SetLightning();
	void SetWireframe();

public:

	Light lights[MAX_LIGHTS];
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix;
	Cube* cube;
	Mesh* test;
	Shaders* testshader;
	bool showBB;
	std::string modelname;

	std::vector<Comp_MeshRenderer*>meshes;
	std::vector<Comp_MeshRenderer*>transmeshes;
	std::vector<Texture*>textures;
	std::vector<float3>debugpoints;
	std::map<float, Comp_MeshRenderer*> trihitsdistmap;
	std::map<float, Comp_MeshRenderer*> transparentObjectsmap;

private:

	int texturenum = -1;

	ModelImporter* currentModel = nullptr;

	SDL_GLContext context;
	
	RenderStuff renderstuff;

	
};

#endif // !__MODULERENDERER3D_H__
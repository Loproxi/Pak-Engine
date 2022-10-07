#ifndef _MODELIMPORTER_H__
#define _MODELIMPORTER_H__
#include "Globals.h"

struct LoadedMeshGeometry
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class ModelImporter
{
	bool init();

	bool Update();

	bool CleanUp();

	void LoadMesh(char* path);

public:

	LoadedMeshGeometry meshdataloaded;
};

#endif // !_MODELIMPORTER_H__

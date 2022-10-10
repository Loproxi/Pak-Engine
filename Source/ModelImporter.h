#ifndef _MODELIMPORTER_H__
#define _MODELIMPORTER_H__
#include "Globals.h"
#include "MathGeoLib.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "glew.h"
#include "Mesh.h"
#include <vector>

#define ASSIMP_LOAD_FLAGS(aiProcess_Triangulate)

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
public:
	
	bool init();

	bool Update();

	bool CleanUp();

	void Import(std::string);

	void LoadModel(const aiScene* scene ,aiMesh* meshfromfbx);

public:

	LoadedMeshGeometry meshdataloaded;
};

#endif // !_MODELIMPORTER_H__

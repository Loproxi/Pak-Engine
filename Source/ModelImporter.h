#ifndef _MODELIMPORTER_H__
#define _MODELIMPORTER_H__

#include <vector>

#include "Globals.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Mesh.h"


#define ASSIMP_LOAD_FLAGS(aiProcess_Triangulate)

struct LoadedMeshGeometry
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	GLuint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float3* vertex = nullptr;
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
	
	std::vector<Mesh> meshes;
};

#endif // !_MODELIMPORTER_H__

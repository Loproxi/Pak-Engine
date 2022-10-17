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
	std::vector<Vertex> vertex;

};

class ModelImporter
{
public:

	ModelImporter();

	~ModelImporter();
	
	bool init();

	bool Update();

	bool CleanUp();

	void Draw();

	void Import(std::string);

	void goThroughNodes(aiNode* node, const aiScene* scene);
	Mesh goThroughMeshes(aiMesh* meshfromfbx, const aiScene* scene);

public:

	std::vector<Mesh>meshes;
	
};

#endif // !_MODELIMPORTER_H__

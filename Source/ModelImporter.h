#ifndef _MODELIMPORTER_H__
#define _MODELIMPORTER_H__

#include <vector>

#include "Globals.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Mesh.h"
#include "GameObject.h"
#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;


//struct LoadedMeshGeometry
//{
//	uint id_index = 0; // index in VRAM
//	uint num_index = 0;
//	GLuint* index = nullptr;
//	uint id_vertex = 0; // unique vertex in VRAM
//	uint num_vertex = 0;
//	std::vector<Vertex> vertex;
//
//};

struct NodeCustom
{
	std::string name = "CustomFileNode";
	std::vector<NodeCustom>children;
	std::string pathtomesh = "NOMESH";
	float3 position = { 0.0f,0.0f,0.0f };
	float3 rotation = { 0.0f,0.0f,0.0f };
	float3 scale = { 1.0f,1.0f,1.0f };

};

class Shaders;

class ModelImporter
{
public:

	ModelImporter();

	~ModelImporter();
	
	bool init();

	bool Update();

	bool CleanUp();

	void Import(std::string);

	void goThroughNodes(aiNode* node, const aiScene* scene,GameObject* parent = nullptr);

	Mesh* goThroughMeshes(aiMesh* meshfromfbx, const aiScene* scene);

	void SaveModelIntoCF(NodeCustom& custnode);

	void IterateNodeCustomChildren(json& json, NodeCustom& childnode);

public:

	std::string modelpath;
	std::vector<std::string>meshnames;

};

#endif // !_MODELIMPORTER_H__

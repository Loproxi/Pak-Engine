#include "ModelImporter.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

bool ModelImporter::init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
	return true;
}

bool ModelImporter::Update()
{
	return true;
}

bool ModelImporter::CleanUp()
{
	aiDetachAllLogStreams();
	return true;
}

void ModelImporter::LoadMesh(char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			meshdataloaded.num_vertex = scene->mMeshes[i]->mNumVertices;
			meshdataloaded.vertex = new float[meshdataloaded.num_vertex * 3];
			memcpy(meshdataloaded.vertex, scene->mMeshes[i]->mVertices, sizeof(float) * meshdataloaded.num_vertex * 3);
			LOG("New mesh with %d vertices", meshdataloaded.num_vertex);
		}
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", path);
	}
	
}

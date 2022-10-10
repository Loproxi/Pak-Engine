#include "ModelImporter.h"


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

void ModelImporter::Import(std::string path)
{
	const aiScene* scene = aiImportFile(path.c_str(), aiProcess_FlipUVs | aiProcess_Triangulate);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			LoadModel(scene, scene->mMeshes[i]);
		}
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", path);
	}
	
}

void ModelImporter::LoadModel(const aiScene* scene,aiMesh* meshfromfbx)
{

	//float3 temp;

	for (uint i = 0; i < meshfromfbx->mNumVertices; i++)
	{
		
		/*temp.x = meshfromfbx->mVertices[i].x;
		temp.y = meshfromfbx->mVertices[i].y;
		temp.z = meshfromfbx->mVertices[i].z;
		vertices.push_back(temp);
		LOG("New mesh with %d vertices", vertices.size());*/
		meshdataloaded.num_vertex = scene->mMeshes[i]->mNumVertices;
		meshdataloaded.vertex = new float[meshdataloaded.num_vertex * 3];
		memcpy(meshdataloaded.vertex, scene->mMeshes[i]->mVertices, sizeof(float) * meshdataloaded.num_vertex * 3);
		LOG("New mesh with %d vertices", meshdataloaded.num_vertex);
	}

	if (meshfromfbx->HasFaces())
	{
		meshdataloaded.num_index = meshfromfbx->mNumFaces * 3;
		meshdataloaded.index = new uint[meshdataloaded.num_index]; // assume each face is a triangle
		for (uint i = 0; i < meshfromfbx->mNumFaces; ++i)
		{
			if (meshfromfbx->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 indices!");
			}
			else
			{

				//indices.push_back(meshfromfbx->mFaces->mIndices[i]);
				memcpy(&meshdataloaded.index[i * 3], meshfromfbx->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}
	
}

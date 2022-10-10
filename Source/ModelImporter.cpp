#include "ModelImporter.h"
#include "MathGeoLib.h"


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
	LoadedMeshGeometry ourMesh;
	// copy vertices
	ourMesh.num_vertex = meshfromfbx->mNumVertices;
	ourMesh.vertex = new float3[ourMesh.num_vertex];
	memcpy(ourMesh.vertex, meshfromfbx->mVertices, sizeof(float3) * ourMesh.num_vertex);
	LOG("New mesh with %d vertices", ourMesh.num_vertex);
	
	if (meshfromfbx->HasFaces())
	{
		ourMesh.num_index = meshfromfbx->mNumFaces * 3;
		ourMesh.index = new GLuint[ourMesh.num_index]; // assume each face is a triangle
		for (uint i = 0; i < meshfromfbx->mNumFaces; ++i)
		{
			if (meshfromfbx->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&ourMesh.index[i * 3], meshfromfbx->mFaces[i].mIndices, 3 * sizeof(GLuint));
			}
		}
	}

	Mesh temp(&ourMesh);

	meshes.push_back(temp);

	delete ourMesh.vertex;
	delete ourMesh.index;

}

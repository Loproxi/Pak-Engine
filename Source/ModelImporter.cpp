#include "ModelImporter.h"
#include "MathGeoLib.h"


ModelImporter::ModelImporter()
{
}

ModelImporter::~ModelImporter()
{
}

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

	for (int i = 0; i < meshes.size(); i++)
	{
		delete meshes[i];
		meshes[i] = nullptr;
	}

	meshes.clear();

	
	return true;
}

void ModelImporter::Draw()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->RenderMeshes();
	}
}

void ModelImporter::Import(std::string path)
{
	const aiScene* scene = aiImportFile(path.c_str(), aiProcess_FlipUVs | aiProcess_Triangulate);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		
		goThroughNodes( scene->mRootNode,scene);
		
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", path);
	}

}

void ModelImporter::goThroughNodes(aiNode* node, const aiScene* scene)
{

	// go through all the nodes meshes in the tree
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(goThroughMeshes(mesh, scene));
	}
	//go through all the children nodes meshes in the tree
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		goThroughNodes(node->mChildren[i], scene);
	}

}

Mesh* ModelImporter::goThroughMeshes(aiMesh* meshfromfbx, const aiScene* scene)
{

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	

	for (unsigned int i = 0; i < meshfromfbx->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position.x = meshfromfbx->mVertices[i].x;
		vertex.position.y = meshfromfbx->mVertices[i].y;
		vertex.position.z = meshfromfbx->mVertices[i].z;

		if (meshfromfbx->HasNormals())
		{
			vertex.normals.x = meshfromfbx->mNormals[i].x;
			vertex.normals.y = meshfromfbx->mNormals[i].y;
			vertex.normals.z = meshfromfbx->mNormals[i].z;
		}

		vertices.push_back(vertex);
	}

	if (meshfromfbx->HasFaces())
	{
		//Without this line memcpy doesn't work because doesn't knows its size
		indices.resize(meshfromfbx->mNumFaces * 3);
		for (uint i = 0; i < meshfromfbx->mNumFaces; ++i)
		{

			if (meshfromfbx->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 indices!");
			}
			else
			{
				memcpy(&indices[i * 3], meshfromfbx->mFaces[i].mIndices, 3 * sizeof(GLuint));
			}
		}
	}
	
	//With new we avoid calling the destructor till the application is closing
	return new Mesh(&vertices[0], vertices.size(),&indices[0],indices.size());
}



//Mesh ModelImporter::LoadModel(const aiScene* scene,aiMesh* meshfromfbx)
//{
//	LoadedMeshGeometry ourMesh;
//	// copy vertices
//	ourMesh.num_vertex = meshfromfbx->mNumVertices;
//
//	for (uint i = 0; i < ourMesh.num_vertex; i++)
//	{
//		ourMesh.vertex.push_back(Vertex(float3(meshfromfbx->mVertices[i].x, meshfromfbx->mVertices[i].y, meshfromfbx->mVertices[i].z), float3(meshfromfbx->mNormals[i].x, meshfromfbx->mNormals[i].y, meshfromfbx->mNormals[i].z)));
//	}
//	LOG("New mesh with %d vertices", ourMesh.num_vertex);
//
//	if (meshfromfbx->HasFaces())
//	{
//		ourMesh.num_index = meshfromfbx->mNumFaces * 3;
//		ourMesh.index = new GLuint[ourMesh.num_index]; // assume each face is a triangle
//		for (uint i = 0; i < meshfromfbx->mNumFaces; ++i)
//		{
//			if (meshfromfbx->mFaces[i].mNumIndices != 3)
//			{
//				LOG("WARNING, geometry face with != 3 indices!");
//			}
//			else
//			{
//				memcpy(&ourMesh.index[i * 3], meshfromfbx->mFaces[i].mIndices, 3 * sizeof(GLuint));
//			}
//		}
//	}
//
//	Mesh temp(&ourMesh.vertex[0],ourMesh.num_vertex,ourMesh.index,ourMesh.num_index);
//	
//	return temp;
//}

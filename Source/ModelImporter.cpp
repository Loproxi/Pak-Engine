#include "ModelImporter.h"
#include "MathGeoLib.h"
#include "Shaders.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleFileSystem.h"
#include "Comp_MeshRenderer.h"
#include "Comp_Transform.h"

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

	json ex3 = {
  {"happy", true},
  {"pi", 3.141},
	};
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
		modelpath = path;
		// Use scene->mNumMeshes to iterate on scene->mMeshes array

		goThroughNodes(scene->mRootNode,scene);
		
		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", path);
	}

}

void ModelImporter::goThroughNodes(aiNode* node, const aiScene* scene,GameObject* parent)
{
	NodeCustom modelnode;
	modelnode.name = node->mName.C_Str();
	
	GameObject* go = new GameObject(node->mName.C_Str());
	if (parent == nullptr)
	{
		
		go->parent = Application::GetInstance()->scene->root;
		Application::GetInstance()->scene->root->AddChild(go);
	}
	else 
	{
		go->parent = parent;
		parent->AddChild(go);
	}

	if (node->mNumMeshes != 0)
	{
		modelnode.pathtomesh = "NOMESH";
	}
	else
	{
		modelnode.pathtomesh = "Library/Models/";
		modelnode.pathtomesh += node->mName.C_Str();
		modelnode.pathtomesh += ".PKmesh";
	}

	aiVector3D aiscale;
	aiVector3D aiposition;
	aiVector3D airotation;

	node->mTransformation.Decompose(aiscale, airotation, aiposition);

	float3 position(aiposition.x, aiposition.y, aiposition.z);
	float3 scale(aiscale.x, aiscale.y, aiscale.z);
	float3 rotation;
	modelnode.position = position;
	rotation.x = math::RadToDeg(airotation.x);
	rotation.y = math::RadToDeg(airotation.y);
	rotation.z = math::RadToDeg(airotation.z);
	modelnode.rotation = rotation;
	go->GetComponent<Comp_Transform>()->position = position;
	go->GetComponent<Comp_Transform>()->eulerRotation = rotation;
	go->GetComponent<Comp_Transform>()->localScale = { 1.0f,1.0f,1.0f };
	modelnode.scale = { 1.0f,1.0f,1.0f };
	
	// go through all the nodes meshes in the tree
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		go->AddComponent(COMP_TYPE::MESH_RENDERER);
		
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		//Comp_MeshRenderer* temp = (Comp_MeshRenderer*)go->GetComponent(COMP_TYPE::MESH_RENDERER);

		Mesh* meshinlib = nullptr;

		meshinlib = goThroughMeshes(mesh, scene);

		meshinlib->SaveMeshIntoCustomFile(node->mName.C_Str());
		
		go->GetComponent<Comp_MeshRenderer>()->SetMesh(meshinlib);
		
	}
	//go through all the children nodes meshes in the tree
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		goThroughNodes(node->mChildren[i], scene,go);
	}

	SaveModelIntoCF(modelnode);
}

Mesh* ModelImporter::goThroughMeshes(aiMesh* meshfromfbx, const aiScene* scene)
{
	//Temp vectors in order to save all the needed information to mesh class
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	
	//Getting all the vertices information from assimp to our structure
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
		if (meshfromfbx->HasTextureCoords(0))
		{
			vertex.texcoords.x = meshfromfbx->mTextureCoords[0][i].x;
			vertex.texcoords.y = meshfromfbx->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.texcoords.x = 0.0f;
			vertex.texcoords.y = 0.0f;
		}
		

		vertices.push_back(vertex);
	}

	//Getting all the indices information from assimp to our structure
	if (meshfromfbx->HasFaces())
	{
		//Without this line memcpy doesn't work because doesn't knows his size
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
	Application::GetInstance()->AddLog(Logs::NORMAL, "Mesh Loaded");
	//With new we avoid calling the destructor till the application is closing
	return new Mesh(&vertices[0], vertices.size(),&indices[0],indices.size(),modelpath);
}

void ModelImporter::SaveModelIntoCF(NodeCustom& custnode)
{
	/*{"answer", {
			{"everything", 42}
		}},

			{"children", {
			{"currency", "USD"},
		}}
		*/

	std::string modelfilepath = "Library/Models/" + custnode.name + ".PKmodel";

	std::vector<std::string> childnames;

	for (uint i = 0; i < custnode.children.size(); i++)
	{
		childnames.push_back(custnode.children[i].name);
	}

	json models = {

		{"modelroot",
			{
				{"name", custnode.name},
				{"pathtomesh", custnode.pathtomesh},
				{"position", {custnode.position.x, custnode.position.y, custnode.position.z}},
				{"rotation", {custnode.rotation.x, custnode.rotation.y, custnode.rotation.z}},
				{"scale", {custnode.scale.x, custnode.scale.y, custnode.scale.z}},
				{"childsnames", childnames},
			}
		}
	};

	for (int i = 0; i < custnode.children.size(); i++)
	{
		IterateNodeCustomChildren(models, custnode.children[i]);
	}

	std::string s = models.dump();
	char* buffer = new char[s.length() + 1];
	strcpy(buffer, s.c_str());
	

	Application::GetInstance()->fileSystem->SaveBufferToFile(modelfilepath, buffer, s.size(),false);
	RELEASE_ARRAY(buffer);

}

void ModelImporter::IterateNodeCustomChildren(json& refjson, NodeCustom& childnode)
{
	std::vector<std::string> childnames;

	for (uint i = 0; i < childnode.children.size(); i++)
	{
		childnames.push_back(childnode.children[i].name);
	}

	json childmodels = {

		{childnode.name,
			{
				{"name", childnode.name},
				{"pathtomesh", childnode.pathtomesh},
				{"position", {childnode.position.x, childnode.position.y, childnode.position.z}},
				{"rotation", {childnode.rotation.x, childnode.rotation.y, childnode.rotation.z}},
				{"scale", {childnode.scale.x, childnode.scale.y, childnode.scale.z}},
				{"childsnames", childnames},
			}
		}
	};

	refjson += childmodels;

	for (int i = 0; i < childnode.children.size(); i++)
	{
		IterateNodeCustomChildren(refjson, childnode.children[i]);
	}
}


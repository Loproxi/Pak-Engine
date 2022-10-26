#include "Comp_MeshRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"

Comp_MeshRenderer::Comp_MeshRenderer(GameObject* _go): Component(_go),mesh(nullptr)
{
	this->name = "Mesh_Renderer";
	this->type = COMP_TYPE::MESH_RENDERER;
	
	app = Application::GetInstance();
}

Comp_MeshRenderer::~Comp_MeshRenderer()
{
	RELEASE(mesh);
}

void Comp_MeshRenderer::Update()
{
	
	app->renderer3D->meshes.push_back(this);

}

void Comp_MeshRenderer::OnUIController()
{


	
}

void Comp_MeshRenderer::Draw(Shaders* shaders)
{
	this->mesh->RenderMeshes(shaders);
}

void Comp_MeshRenderer::SetMesh(Mesh* _mesh)
{
	this->mesh = _mesh;
}

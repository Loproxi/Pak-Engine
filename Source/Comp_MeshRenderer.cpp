#include "Comp_MeshRenderer.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ImGuiUtils.h"
#include "Comp_Transform.h"

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
	if (ImGui::CollapsingHeader("MeshRenderer: ", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (mesh != nullptr)
		{
			ImGui::Checkbox("Active ", &active);
			//ImGui::Image((ImTextureID)_mesh->textureID, ImVec2(128, 128));
			std::string tempvertices = std::to_string(mesh->GetNumVertices());
			std::string tempindices = std::to_string(mesh->GetNumIndices());
			ImGui::Text("Vertices: "); 
			ImGui::SameLine(); 
			ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), tempvertices.c_str());
			ImGui::Text("Indices: "); 
			ImGui::SameLine(); 
			ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), tempindices.c_str());
			ImGui::Spacing();
			ImGui::Text("Path: ");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), mesh->GetPath().c_str());
		}
	}
}

void Comp_MeshRenderer::Draw(Shaders* shaders)
{
	if (this->mesh != nullptr)
	{
		 
		this->mesh->RenderMeshes(shaders,comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix());
	}
}

void Comp_MeshRenderer::SetMesh(Mesh* _mesh)
{
	this->mesh = _mesh;
}

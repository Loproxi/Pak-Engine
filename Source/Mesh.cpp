#include "Mesh.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModelImporter.h"
#include "Shaders.h"



Mesh::Mesh():VAO(0),EBO(0),VBO(0),texture(0),shader(nullptr)
{
}

Mesh::Mesh(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices, const float3 position, const float3 rotation, const float3 scale)
{
	SetVertexData(numvertices, vertices, numindices, indices);
	InitBuffers();
	
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

//Mesh::Mesh(const LoadedMeshGeometry* test)
//{
//	
//	for (uint i = 0; i < test->num_vertex; i++)
//	{
//		this->vertices.push_back(test->vertex[i]);
//	}
//	for (uint i = 0; i < test->num_index; i++)
//	{
//		this->indices.push_back(test->index[i]);
//	}
//
//	InitBuffers();
//
//}

Mesh::~Mesh()
{

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

}

void Mesh::SetVertexData(const uint numvertices, const Vertex* vertices, const uint numindices, const GLuint* indices)
{
	for (uint i = 0; i < numvertices; i++)
	{
		this->vertices.push_back(vertices[i]);
	}
	for (uint i = 0; i < numindices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

void Mesh::InitBuffers()
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoords));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	texture = Application::GetInstance()->renderer3D->textures.at(0)->textID;

	glBindVertexArray(0);
}

void Mesh::Update()
{
}

void Mesh::GenModelMatrix()
{
	modelMatrix.SetIdentity();

}

void Mesh::PrintMatrix(float4x4* matrix)
{
	for (int i = 0; i < matrix->Cols; i++)
	{
		for (int j = 0; j < matrix->Rows; j++)
		{
			printf("| %f |", matrix->At(j, i));
		}
		printf("\n");
	}
}

void Mesh::RenderMeshes(Shaders* shader)
{
	
	shader->UseProgram();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shader->Set1Int("texture0", 0);

	modelMatrix.SetIdentity();

	shader->SetMat4fv("viewMatrix", Application::GetInstance()->camera->GetViewMatrix());
	shader->SetMat4fv("projectionMatrix", Application::GetInstance()->renderer3D->GetProjectionMatrix());
	shader->SetMat4fv("modelMatrix", &modelMatrix.v[0][0]);
	
	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, indices.size());
	glBindVertexArray(0);
}

void Mesh::SetTextureID(GLuint id)
{
	texture = id;
}
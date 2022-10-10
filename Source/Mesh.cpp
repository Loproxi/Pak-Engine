#include "Mesh.h"
#include "ModelImporter.h"


Mesh::Mesh(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices, const float3 position, const float3 rotation, const float3 scale)
{
	SetVertexData(numvertices, vertices, numindices, indices);
	InitBuffers();
	
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

//Mesh::Mesh(const LoadedMeshGeometry* modelloaded)
//{
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
		this->vertices.push_back(vertices[i].position);
	}
	for (uint i = 0; i < numindices; i++)
	{
		this->indices.push_back(indices[i]);
	}
}

void Mesh::InitBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float3),NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Mesh::Update()
{
}

void Mesh::GenModelMatrix()
{
	modelMatrix.SetIdentity();
	if (modelMatrix.IsIdentity())
	{
		//Crear una matriu nova i li pasem els valors de position rotation scale
		modelMatrix.Transpose();
		PrintMatrix(&modelMatrix);
		
	}
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

void Mesh::RenderMeshes()
{
	//GenModelMatrix();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}

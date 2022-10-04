#include "Mesh.h"

Mesh::Mesh(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices)
{
	SetVertexData(numvertices, vertices, numindices, indices);
	InitBuffers();
	
	this->position = { 0.0f,0.0f,0.0f };
	this->rotation = { 0.0f,0.0f,0.0f };
	this->scale = { 1.0f,1.0f,1.0f };
}

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
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Mesh::Update()
{
}

void Mesh::RenderMeshes()
{

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,0);
	glBindVertexArray(0);
}

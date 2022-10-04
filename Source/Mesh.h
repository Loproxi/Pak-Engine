#ifndef _MESHRENDER_H_
#define _MESHRENDER_H_

#include "Globals.h"
#include "Vertex.h"
#include "glew.h"

class Mesh
{
public:
	Mesh(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices);

	~Mesh();

	void SetVertexData(const uint numvertices, const Vertex* vertices, const uint numindices, const GLuint* indices);

	void InitBuffers();

	void Update();

	void RenderMeshes();

private:

	float3 position;
	float3 rotation;
	float3 scale;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // !_MESHRENDER_H_
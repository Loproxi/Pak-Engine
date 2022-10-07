#ifndef _MESHRENDER_H_
#define _MESHRENDER_H_

#include "Globals.h"
#include "glew.h"
#include "MathGeoLib.h"
#include "Math/float4x4.h"

class Mesh
{
public:
	Mesh(const float3* vertices, const uint numvertices, const GLuint* indices, const uint numindices, const float3 position = {0.0f,0.0f,0.0f}, const float3 rotation = { 0.0f,0.0f,0.0f }, const float3 scale = { 1.0f,1.0f,1.0f });

	~Mesh();

	void RenderMeshes();

private:

	void SetVertexData(const uint numvertices, const float3* vertices, const uint numindices, const GLuint* indices);

	void InitBuffers();

	void Update();

	void GenModelMatrix();
	
	void PrintMatrix(float4x4* matrix);
	
private:

	float3 position;
	float3 rotation;
	float3 scale;

	std::vector<float3> vertices;
	std::vector<GLuint> indices;

	float4x4 modelMatrix;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // !_MESHRENDER_H_
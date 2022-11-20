#ifndef _MESHRENDER_H_
#define _MESHRENDER_H_

#include "Globals.h"
#include "glew.h"
#include "MathGeoLib.h"
#include "Math/float4x4.h"
#include "TextureImporter.h"


struct Vertex
{
	Vertex() 
	{

	}
	Vertex(float3 pos, float3 normals,float2 texcoords)
	{
		this->position = pos;
		this->normals = normals;
		this->texcoords = texcoords;
		
	}
	~Vertex() 
	{

	}
	float3 position;
	float3 normals;
	float2 texcoords;
};

struct LoadedMeshGeometry;
class Shaders;
class GameObject;

class Mesh
{
public:

	Mesh();
	
	Mesh(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices,std::string path ="");

	Mesh(const LoadedMeshGeometry* test);

	~Mesh();

	void RenderMeshes(Shaders* shader,float4x4 modelmatrix);

	Vertex* GetVertices(){ return &vertices[0]; }
	GLuint* GetIndices() { return &indices[0]; }
	GLuint* GetTextureID() { return &texture; }
	void SetTextureID(GLuint id);
	int GetNumVertices() { return numvertices; }
	uint GetNumIndices() { return numindices; }
	std::string GetPath() { return path; }

private:

	void SetVertexData(const uint numvertices, const Vertex* vertices, const uint numindices, const GLuint* indices);

	void InitBuffers();

	void Update();

	void GenModelMatrix();
	
	void PrintMatrix(float4x4* matrix);

	AABB GenLocalAABB();

	AABB GenGlobalBB(GameObject* go);
	
private:

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	uint numvertices;
	uint numindices;

	

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint texture;
	
	TextureImporter textimporter;

	Shaders* shader;

	std::string path;

	AABB LocalAxisAlignBB;
	AABB GlobalAxisAlignBB;
	OBB GlobalOrientedBB;

protected:
	float4x4 modelMatrix;

	friend class Comp_MeshRenderer;
};

#endif // !_MESHRENDER_H_
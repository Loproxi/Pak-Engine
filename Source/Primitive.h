#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <vector>

#include "glmath.h"
#include "Color.h"
#include "glew.h"
#include "MathGeoLib.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder
};

class Primitive
{
public:
	Primitive();

	PrimitiveTypes	GetType() const;

	float3* GetVertices() { return &vertices[0]; }
	GLuint* Getindices() { return &indices[0]; }
	std::vector<GLuint>* GetindicesVector() { return &indices; }
	std::vector<float3>* GetVerticesVector() { return &vertices; }
	uint GetNumVertices() { return vertices.size(); }
	uint GetNumIndices() { return indices.size(); }

	void SetData(const float3* vertices, const uint numvertices, const GLuint* indices, const uint numindices);

protected:
	PrimitiveTypes type;

private:

	std::vector<float3> vertices;
	std::vector<GLuint> indices;
	uint numvertices;
	uint numindices;

};

// ============================================
class Cube : public Primitive
{
public :
	Cube();
	Cube(float sizeX, float sizeY, float sizeZ);
public:
	float3 size;
};

// ============================================
class Spheree : public Primitive
{
public:
	Spheree();
	Spheree(unsigned int rings, unsigned int sectors, float radius);

};

// ============================================
class Cylinder : public Primitive
{
public:
	Cylinder();
	Cylinder(float radius, float height);
};

// ============================================
class Pyramid : public Primitive
{
public:
	Pyramid();
public:
	float3 size;
};

// ============================================
class Plane : public Primitive
{
public:
	Plane();
	Plane(float x, float y, float z, float d);
	void InnerRender() const;
public:
	vec3 normal;
	float constant = 0;
};

#endif // !__PRIMITIVE_H__
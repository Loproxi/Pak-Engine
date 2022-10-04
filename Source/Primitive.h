#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <vector>

#include "glmath.h"
#include "Color.h"
#include "glew.h"
#include "Vertex.h"

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

	Vertex* GetVertices() { return &vertices[0]; }
	GLuint* Getindices() { return &indices[0]; }
	uint GetNumVertices() { return vertices.size(); }
	uint GetNumIndices() { return indices.size(); }

	void SetData(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices);

protected:
	PrimitiveTypes type;

private:

	std::vector<Vertex> vertices;
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
	vec3 size;
};

// ============================================
class Spheree : public Primitive
{
public:
	Spheree();
	Spheree(unsigned int rings, unsigned int sectors, float radius);
	
public:
	float radius = 0;

private:

};

// ============================================
class Cylinder : public Primitive
{
public:
	Cylinder();
	Cylinder(float radius, float height);
public:
	float radius = 0;
	float height = 0;
};

// ============================================
class Line : public Primitive
{
public:
	Line();
	Line(float x, float y, float z);
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
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
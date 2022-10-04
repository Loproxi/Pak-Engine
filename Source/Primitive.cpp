#include "Globals.h"
#include "Primitive.h"




// ------------------------------------------------------------
Primitive::Primitive() : type(PrimitiveTypes::Primitive_Point)
{}

// ------------------------------------------------------------
PrimitiveTypes Primitive::GetType() const
{
	return type;
}

void Primitive::SetData(const Vertex* vertices, const uint numvertices, const GLuint* indices, const uint numindices)
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


// CUBE ============================================
Cube::Cube() : Primitive(), size(1.0f, 1.0f, 1.0f)
{
	type = PrimitiveTypes::Primitive_Cube;

	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	Vertex vertices[8]
	{
		float3{-sx, sy, sz},
		float3{-sx, -sy, sz},
		float3{sx,  sy, sz},
		float3{sx,  -sy, sz},
		float3{-sx,  sy, -sz},
		float3{-sx, -sy, -sz},
		float3{sx,  sy, -sz},
		float3{sx, -sy, -sz },
	};

	
	
	GLuint indices[36] =
	{
		0, 3, 2, 0, 1, 3, //Front
		2, 7, 6, 2, 3, 7, //Right
		6, 5, 4, 6, 7, 5, //Back
		4, 1, 0, 4, 5, 1, //Left
		0, 6, 4, 0, 2, 6, //Up
		1, 5, 7, 1, 7, 3,
	};

	uint tempnumofvertices = sizeof(vertices) / sizeof(Vertex);
	uint tempnumofindices = sizeof(indices) / sizeof(GLuint);

	SetData(&vertices[0], tempnumofvertices, &indices[0], tempnumofindices);

}

Cube::Cube(float sizeX, float sizeY, float sizeZ) : Primitive(), size(sizeX, sizeY, sizeZ)
{
	type = PrimitiveTypes::Primitive_Cube;

	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;
	float sz = size.z * 0.5f;

	Vertex vertices[8]
	{
		float3{-sx, sy, sz},
		float3{-sx, -sy, sz},
		float3{sx,  sy, sz},
		float3{sx,  -sy, sz},
		float3{-sx,  sy, -sz},
		float3{-sx, -sy, -sz},
		float3{sx,  sy, -sz},
		float3{sx, -sy, -sz },
	};



	GLuint indices[36] =
	{
		0, 3, 2, 0, 1, 3, //Front
		2, 7, 6, 2, 3, 7, //Right
		6, 5, 4, 6, 7, 5, //Back
		4, 1, 0, 4, 5, 1, //Left
		0, 6, 4, 0, 2, 6, //Up
		1, 5, 7, 1, 7, 3,
	};

	uint tempnumofvertices = sizeof(vertices) / sizeof(Vertex);
	uint tempnumofindices = sizeof(indices) / sizeof(GLuint);

	SetData(&vertices[0], tempnumofvertices, &indices[0], tempnumofindices);
}

// SPHERE ============================================
Spheree::Spheree() : Primitive(), radius(1.0f)
{
	type = PrimitiveTypes::Primitive_Sphere;
}

Spheree::Spheree( unsigned int rings, unsigned int sectors ,float radius ) : Primitive(), radius(radius)
{
	type = PrimitiveTypes::Primitive_Sphere;

	//float const R = 1. / (float)(rings - 1);
	//float const S = 1. / (float)(sectors - 1);
	//int r, s;

	//vertices.resize(rings * sectors * 3);


	//std::vector<GLfloat>::iterator v = vertices.begin();

	//for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
	//	float const y = sin(-M_PI_2 + M_PI * r * R);
	//	float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
	//	float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

	//	*v++ = x * radius;
	//	*v++ = y * radius;
	//	*v++ = z * radius;

	//}

	//indices.resize(rings * sectors * 4);
	//std::vector<GLushort>::iterator i = indices.begin();
	//for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
	//	*i++ = r * sectors + s;
	//	*i++ = r * sectors + (s + 1);
	//	*i++ = (r + 1) * sectors + (s + 1);
	//	*i++ = (r + 1) * sectors + s;
	//}
}


// CYLINDER ============================================
//Cylinder::Cylinder() : Primitive(), radius(1.0f), height(1.0f)
//{
//	type = PrimitiveTypes::Primitive_Cylinder;
//}
//
//Cylinder::Cylinder(float radius, float height) : Primitive(), radius(radius), height(height)
//{
//	type = PrimitiveTypes::Primitive_Cylinder;
//}
//
//// LINE ==================================================
//Line::Line() : Primitive(), origin(0, 0, 0), destination(1, 1, 1)
//{
//	type = PrimitiveTypes::Primitive_Line;
//}
//
//Line::Line(float x, float y, float z) : Primitive(), origin(0, 0, 0), destination(x, y, z)
//{
//	type = PrimitiveTypes::Primitive_Line;
//}
//
//void Line::InnerRender() const
//{
//	glLineWidth(2.0f);
//
//	glBegin(GL_LINES);
//
//	glVertex3f(origin.x, origin.y, origin.z);
//	glVertex3f(destination.x, destination.y, destination.z);
//
//	glEnd();
//
//	glLineWidth(1.0f);
//}
//
//// PLANE ==================================================
//Plane::Plane() : Primitive(), normal(0, 1, 0), constant(1)
//{
//	type = PrimitiveTypes::Primitive_Plane;
//}
//
//Plane::Plane(float x, float y, float z, float d) : Primitive(), normal(x, y, z), constant(d)
//{
//	type = PrimitiveTypes::Primitive_Plane;
//}
//
//void Plane::InnerRender() const
//{
//	glLineWidth(1.0f);
//
//	glBegin(GL_LINES);
//
//	float d = 2000.0f;
//
//	for(float i = -d; i <= d; i += 1.0f)
//	{
//		glVertex3f(i, 0.0f, -d);
//		glVertex3f(i, 0.0f, d);
//		glVertex3f(-d, 0.0f, i);
//		glVertex3f(d, 0.0f, i);
//	}
//
//	glEnd();
//}
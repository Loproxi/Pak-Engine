#ifndef _SHADERS_H__
#define _SHADERS_H__

#include "glew.h"
#include "MathGeoLib/include/Math/MathAll.h"
#include <string>
#include <sstream>
#include <fstream>

class Application;

class Shaders
{
public:

	Shaders(const char* vertexlink,const char* fragmentlink);

	~Shaders();

	GLuint GetID(){ return this->shadID; }

	void SetMat4fv(const std::string& name, const float* value);

	void Set1Int(const std::string& name, GLint value);

	void Set4Float(const std::string& name, const float* value);

	void UseProgram();

private:

	std::string ProcessShaderLink(const char* filelink);

	void ProcessShader(const char* vertexfilelink, const char* fragmentfilelink);

	void ProcessProgram(GLuint vertexshader, GLuint fragmentshader);

private:

	GLuint shadID;
	Application* app;

};

#endif // !_SHADERS_H__
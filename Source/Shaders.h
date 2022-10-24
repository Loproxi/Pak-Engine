#ifndef _SHADERS_H__
#define _SHADERS_H__

#include "glew.h"
#include <string>
#include <sstream>
#include <fstream>

class Application;

class Shaders
{
public:

	Shaders(const char* vertexlink,const char* fragmentlink);

	~Shaders();

	GLuint GetID(){ return this->id; }

	void UseProgram();

private:

	std::string ProcessShaderLink(const char* filelink);

	void ProcessShader(const char* vertexfilelink, const char* fragmentfilelink);

	void ProcessProgram(GLuint vertexshader, GLuint fragmentshader);

private:

	GLuint id;
	Application* app;

};

#endif // !_SHADERS_H__
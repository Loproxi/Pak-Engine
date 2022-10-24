#include "Shaders.h"
#include "Application.h"

Shaders::Shaders(const char* vertexlink, const char* fragmentlink) :app(nullptr)
{
	app = Application::GetInstance();

	ProcessShader(vertexlink, fragmentlink);
}

Shaders::~Shaders()
{
}

std::string Shaders::ProcessShaderLink(const char* filelink)
{
	std::string tempcode;
	std::string shadercode;
	//Search a file with filelink's name and opens it
	std::ifstream filename;
	filename.open(filelink);

	if (filename.is_open())
	{
		//gets the data from filename and introduce it inside tempcode
		while (std::getline(filename, tempcode))
		{
			shadercode += tempcode + "\n";
		}

	}
	else
	{
		app->AddLog(Logs::ERROR_LOG, "ERROR SHADER, COULD NOT OPEN FILE");
	}

	filename.close();

	return shadercode;
}

void Shaders::ProcessShader(const char* vertexfilelink, const char* fragmentfilelink)
{
	GLint done;

	//Vertex Shader
	uint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	std::string tempcode = this->ProcessShaderLink(vertexfilelink);
	const char* vertexshadercode = tempcode.c_str();
	glShaderSource(vertexshader, 1, &vertexshadercode, NULL);
	glCompileShader(vertexshader);

	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &done);
	if (!done)
	{
		app->AddLog(Logs::ERROR_LOG, "VERTEX SHADER COULD NOT BE COMPILED");
	}


	//Fragment Shader
	uint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string tempcode2 = this->ProcessShaderLink(fragmentfilelink);
	const char* fragmentshadercode = tempcode2.c_str();
	glShaderSource(fragmentshader, 1, &fragmentshadercode, NULL);
	glCompileShader(fragmentshader);

	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &done);
	if (!done)
	{
		app->AddLog(Logs::ERROR_LOG, "FRAGMENT SHADER COULD NOT BE COMPILED");
	}

	ProcessProgram(vertexshader, fragmentshader);

}

void Shaders::ProcessProgram(GLuint vertexshader, GLuint fragmentshader)
{
	GLint done;

	this->id = glCreateProgram();
	glAttachShader(this->id, vertexshader);
	glAttachShader(this->id, fragmentshader);
	glLinkProgram(this->id);
	glValidateProgram(this->id);

	glGetShaderiv(this->id, GL_COMPILE_STATUS, &done);
	if (!done)
	{
		app->AddLog(Logs::ERROR_LOG, "PROGRAM SHADER COULD NOT BE CREATED");
	}

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

}

void Shaders::UseProgram()
{
	glUseProgram(this->id);
}

void Shaders::Set1Int(const std::string& name, GLint value)
{
	glUniform1i(glGetUniformLocation(this->id, name.c_str()),value);
}

void Shaders::SetMat4fv(const std::string& name, const float* value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, value);
}
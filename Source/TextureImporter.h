#ifndef _TEXTUREIMPORTER_H__
#define _TEXTUREIMPORTER_H__

#include "Glew/include/glew.h"
#include "Globals.h"

#include<vector>
#include<string>

struct Texture
{
	Texture(GLuint* id, uint* _width, uint* _height)
	{
		textID = *id;
		width = *_width;
		height = *_height;
	}

	GLuint textID;
	uint width;
	uint height;
};

class TextureImporter
{

public:

	TextureImporter();

	~TextureImporter();

	bool init();

	bool Update();

	bool CleanUp();

	static void Draw();

	static Texture* Import(std::string);

	static Texture* LoadCheckerImage();

};

#endif //_TEXTUREIMPORTER_H__


#ifndef _TEXTUREIMPORTER_H__
#define _TEXTUREIMPORTER_H__

#include<vector>
#include<string>

class TextureImporter
{

public:

	TextureImporter();

	~TextureImporter();

	bool init();

	bool Update();

	bool CleanUp();

	void Draw();

	void Import(std::string);

};

#endif //_TEXTUREIMPORTER_H__


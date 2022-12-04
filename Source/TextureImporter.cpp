#include "TextureImporter.h"

#include "Globals.h"
#include "Application.h"
#include "ModuleFileSystem.h"

#include "DevIL/include/ilut.h"
#include "DevIL\include\ilu.h"

TextureImporter::TextureImporter()
{
}

TextureImporter::~TextureImporter()
{
}

bool TextureImporter::CleanUp()
{
    return true;
}

Texture* TextureImporter::Import(std::string textfile)
{
    ILenum imageToTextID;
    ILboolean done;
    

    ilGenImages(1, &imageToTextID);
    ilBindImage(imageToTextID);

    done = ilLoadImage(textfile.c_str());

    SaveTextureIntoCF(textfile);

    if (!done)
    {
        Application::GetInstance()->AddLog(Logs::ERROR_LOG, "Error Loading Image in texture importer");
    }
    else
    {
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        GLuint _texture;

        GLuint width = ilGetInteger(IL_IMAGE_WIDTH);
        GLuint height = ilGetInteger(IL_IMAGE_HEIGHT);
        ILubyte* textdata = ilGetData();

        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
            0, GL_RGBA, GL_UNSIGNED_BYTE, textdata);
        glBindTexture(GL_TEXTURE_2D, 0);

        ilDeleteImages(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, 0);

        return new Texture(&_texture, &width, &height);

    }

    return nullptr;
}

Texture* TextureImporter::LoadCheckerImage()
{
     GLuint CHECKERS_HEIGHT = 240;
     GLuint CHECKERS_WIDTH = 240;

    GLubyte checkerImage[240][240][4];
    for (int i = 0; i < CHECKERS_HEIGHT; i++) {
        for (int j = 0; j < CHECKERS_WIDTH; j++) {
            int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
            checkerImage[i][j][0] = (GLubyte)c;
            checkerImage[i][j][1] = (GLubyte)255;
            checkerImage[i][j][2] = (GLubyte)c;
            checkerImage[i][j][3] = (GLubyte)255;
        }
    }

    GLuint textureID;


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
        0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);
    

    return new Texture(&textureID, &CHECKERS_WIDTH, &CHECKERS_HEIGHT);
}

void TextureImporter::SaveTextureIntoCF(std::string textfile)
{
    std::string tempname;
    Application::GetInstance()->fileSystem->GetFileName(textfile, tempname, false);
    
    std::string path = TEXTURES_FILE_DIR;
    path += "/";
    path += tempname;
    path += ".PKtext";
    ILuint sizeofdata;
    ILubyte* data;

    ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use
    sizeofdata = ilSaveL(IL_DDS, nullptr, 0); // Get the size of the data buffer
    if (sizeofdata > 0) {
        data = new ILubyte[sizeofdata]; // allocate data buffer
        if (ilSaveL(IL_DDS, data, sizeofdata) > 0)
        {
            // Save to buffer with the ilSaveIL function
            Application::GetInstance()->fileSystem->SaveBufferToFile(path,(char*)data,sizeofdata,false);
        }
            RELEASE_ARRAY(data);
    }
}

Texture* TextureImporter::LoadCFInEngine(char* textbuffer, uint imagesize)
{

    ILenum imageToTextID;
    ILboolean done;


    ilGenImages(1, &imageToTextID);
    ilBindImage(imageToTextID);

    done = ilLoadL(IL_TYPE_UNKNOWN, textbuffer, imagesize);
    

    if (!done)
    {
        Application::GetInstance()->AddLog(Logs::ERROR_LOG, "Error Loading Image in texture importer");
    }
    else
    {
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        GLuint _texture;

        GLuint width = ilGetInteger(IL_IMAGE_WIDTH);
        GLuint height = ilGetInteger(IL_IMAGE_HEIGHT);
        ILubyte* textdata = ilGetData();

        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
            0, GL_RGBA, GL_UNSIGNED_BYTE, textdata);
        glBindTexture(GL_TEXTURE_2D, 0);

        ilDeleteImages(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, 0);

        
        return new Texture(&_texture, &width, &height);
    }
    return nullptr;
}
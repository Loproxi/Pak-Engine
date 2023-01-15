#ifndef _MODULEFILESYSTEM_H__
#define _MODULEFILESYSTEM_H__

#define MESHES_FILE_DIR "Library/Meshes"
#define TEXTURES_FILE_DIR "Library/Textures"
#define MODELS_FILE_DIR "Library/Models"
#define PARTICLES_FILE_DIR "Library/Particles"

#include "Module.h"
#include "AssetsDirectory.h"

class ModuleFileSystem :
    public Module
{
public:
    //Module 
    ModuleFileSystem(Application* app, bool start_enabled = true);

    ~ModuleFileSystem();

    bool Init();
    bool Start();
    bool CleanUp();

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

    bool SaveSettings(pugi::xml_node& config);

    //Module File System Functions

    void DragAndDropOnEngine(std::string path);

    bool AddArchiveToPath(std::string path);

    bool CheckIfFileExists(std::string file);

    bool CreateDir(std::string dir);

    bool CheckIfDirectory(std::string file);

    std::string NormalizePath(std::string complete_path);

    std::string UnNormalizePath(std::string complete_path);

    uint LoadFileToBuffer(const char* file, char** buffer);
	
    uint SaveBufferToFile(std::string file, char* buffer, uint size, bool append);

    void GetFileName(std::string file, std::string& fileName, bool extension);
    
    void AddUpdateAssetFiles(AssetsDirectory& directory);

    void RecursiveAddUpdateAssetFiles(AssetsDirectory& directory);
};

#endif // !_MODULEFILESYSTEM_H__
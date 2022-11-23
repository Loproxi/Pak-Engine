#ifndef _MODULEFILESYSTEM_H__
#define _MODULEFILESYSTEM_H__


#include "Module.h"
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
};

#endif // !_MODULEFILESYSTEM_H__
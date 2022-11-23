#include "ModuleFileSystem.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "physfs.h"

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled):Module(app,start_enabled)
{
    PHYSFS_init(0);

    if (PHYSFS_setWriteDir(".") == 0)
    {
        App->AddLog(Logs::ERROR_LOG, "File System error while creating write dir");
    }

    AddArchiveToPath(".");
}

ModuleFileSystem::~ModuleFileSystem()
{
    //Crash
    PHYSFS_deinit();
}

bool ModuleFileSystem::Init()
{

    return true;
}

bool ModuleFileSystem::Start()
{


    return true;
}

UpdateStatus ModuleFileSystem::PreUpdate()
{



    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleFileSystem::Update()
{
    return UpdateStatus::UPDATE_CONTINUE;
}

UpdateStatus ModuleFileSystem::PostUpdate()
{
    return UpdateStatus::UPDATE_CONTINUE;
}

bool ModuleFileSystem::CleanUp()
{
    return true;
}

bool ModuleFileSystem::SaveSettings(pugi::xml_node& config)
{
    return true;
}

void ModuleFileSystem::DragAndDropOnEngine(std::string path)
{

    std::string fileExtension(path);

    fileExtension = fileExtension.substr(fileExtension.find_last_of(".") + 1);

    if (fileExtension == "fbx")
    {
        App->renderer3D->LoadModelImporter(path);
    }
    else if (fileExtension == "png" || fileExtension == "dds")
    {
        App->renderer3D->LoadTextureImporter(path);
    }

}

bool ModuleFileSystem::AddArchiveToPath(std::string path)
{
    if (PHYSFS_mount(path.c_str(), nullptr, 1) == 0)
    {
        App->AddLog(Logs::ERROR_LOG, "File System error while adding a path");
    }
    else return true;

    return false;
}

bool ModuleFileSystem::CheckIfFileExists(std::string file)
{
    return PHYSFS_exists(file.c_str()) != 0;
}

bool ModuleFileSystem::CreateDir(std::string dir)
{
    if (CheckIfDirectory(dir) == false)
    {
        PHYSFS_mkdir(dir.c_str());
        return true;
    }
    return false;
}

// Check if a file is a directory
bool ModuleFileSystem::CheckIfDirectory(std::string file) 
{
    return PHYSFS_isDirectory(file.c_str()) != 0;
}

std::string ModuleFileSystem::NormalizePath(std::string complete_path) 
{
    std::string newPath = complete_path;
    for (int i = 0; i < newPath.size(); ++i)
    {
        if (newPath[i] == '\\')
            newPath[i] = '/';
    }
    return newPath;
}
std::string ModuleFileSystem::UnNormalizePath(std::string complete_path)
{
    std::string newPath = complete_path;
    for (int i = 0; i < newPath.size(); ++i)
    {
        if (newPath[i] == '/')
            newPath[i] = '\\';
    }
    return newPath;
}

uint ModuleFileSystem::LoadFileToBuffer(const char* file, char** buffer)
{
    // Read a whole file and put it in a new buffer
    
    uint ret = 0;

    PHYSFS_file* fs_file = PHYSFS_openRead(file);

    if (fs_file != nullptr)
    {
        PHYSFS_sint64 size = PHYSFS_fileLength(fs_file);
        //LOG(LogType::L_ERROR, "[%s]", PHYSFS_getLastError())

        if (size > 0)
        {
            *buffer = new char[size + 1];
            uint readed = (uint)PHYSFS_read(fs_file, *buffer, 1, size);
            if (readed != size)
            {
                App->AddLog(Logs::ERROR_LOG, "File System error while reading from file");
                RELEASE_ARRAY(buffer);
            }
            else
            {
                ret = readed;
                //Adding end of file at the end of the buffer. Loading a shader file does not add this for some reason
                (*buffer)[size] = '\0';
            }
        }

        if (PHYSFS_close(fs_file) == 0)
            App->AddLog(Logs::ERROR_LOG,"File System error while closing file");
    }
    else
        App->AddLog(Logs::ERROR_LOG, "File System error while opening file");

    return ret;
    
}

uint ModuleFileSystem::SaveBufferToFile(std::string file, char* buffer, uint size, bool append)
{
    uint objCount = 0;

    bool exists = CheckIfFileExists(file);

    PHYSFS_file* filehandle = nullptr;
    if (append)
        filehandle = PHYSFS_openAppend(file.c_str());
    else
        filehandle = PHYSFS_openWrite(file.c_str());

    if (filehandle != nullptr)
    {
        objCount = PHYSFS_writeBytes(filehandle, (const void*)buffer, size);

        if (objCount == size)
        {
            if (exists)
            {
                if (append)
                {
                    App->AddLog(Logs::ERROR_LOG, "FILE SYSTEM: Append bytes to file ");
                }
                else
                    App->AddLog(Logs::ERROR_LOG, "FILE SYSTEM: File overwritten with bytes");
            }
            else
                App->AddLog(Logs::NORMAL, "FILE SYSTEM: New file created with bytes" );
        }
        else
            App->AddLog(Logs::ERROR_LOG, "FILE SYSTEM: Could not write to file ");

        if (PHYSFS_close(filehandle) == 0)
            App->AddLog(Logs::ERROR_LOG, "FILE SYSTEM: Could not close file ");
    }
    else
        App->AddLog(Logs::ERROR_LOG, "FILE SYSTEM: Could not open file to write ");

    return objCount;
}
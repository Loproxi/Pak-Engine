#include "AssetsDirectory.h"

AssetsDirectory::AssetsDirectory()
{
}

AssetsDirectory::AssetsDirectory(std::string name, std::string path)
{

	this->dirname = name;
	this->dirpath = path;

}

AssetsDirectory::~AssetsDirectory()
{
}

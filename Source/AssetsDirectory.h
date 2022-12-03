#ifndef __ASSETS_DIR_TREE_H__
#define __ASSETS_DIR_TREE_H__

#include <string>
#include <vector>

class AssetsDirectory;

struct AssetsFile
{
	AssetsFile() {

	};
	AssetsFile(std::string name,std::string assetpath) {
		this->filename = name;
		this->filepath = assetpath;
	};
	std::string filename;
	AssetsDirectory* parent;
	std::string filepath;
};

class AssetsDirectory
{
public:
	AssetsDirectory();

	AssetsDirectory(std::string name, std::string path);

	~AssetsDirectory();

public:

	std::string dirname;
	std::vector<AssetsFile> directoryfiles;
	std::vector<AssetsDirectory> directorydirs;
	AssetsDirectory* parent;
	std::string dirpath;

};

#endif // !__ASSETS_DIR_TREE_H__
#ifndef __WIN_ASSETS_H__
#define __WIN_ASSETS_H__

#include "WindowBaseClass.h"
#include "AssetsDirectory.h"

class Application;

class WinAssets :
    public WindowBaseClass
{
public:

    WinAssets();

    ~WinAssets();

    void Start();

    void Draw();

    void DrawRecursivelyAssetTree(AssetsDirectory& dir);

    void DrawAssetFile(AssetsDirectory& dir);

private:

    Application* app;

    AssetsDirectory* rootnodeassets;

    AssetsDirectory* selectednode;

};

#endif // !__WIN_ASSETS_H__
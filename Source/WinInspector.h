#ifndef __WIN_INSPECTOR_H__
#define __WIN_INSPECTOR_H__

#include "WindowBaseClass.h"

class GameObject;

class WinInspector :
    public WindowBaseClass
{
public:

    WinInspector();

    ~WinInspector();

    void Start();

    void Draw();

public:
    
    GameObject* goToInspect;

private:
    std::string items[2] = { "Mesh Renderer","Camera" };
};

#endif // !__WIN_INSPECTOR_H__
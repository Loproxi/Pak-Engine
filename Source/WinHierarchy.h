#ifndef __WIN_HIERARCHY_H__
#define __WIN_HIERARCHY_H__

#include "WindowBaseClass.h"

class Application;
class GameObject;

class WinHierarchy :
    public WindowBaseClass
{
public:

    WinHierarchy();

    ~WinHierarchy();

    void Start();

    void Draw();

    void PrimitivesMenu();

    void ShowGameObjects(GameObject* go);

private:

    Application* app;

    GameObject* goToDrop;

    int emptycounter = 0;
};

#endif // !__WIN_HIERARCHY_H__
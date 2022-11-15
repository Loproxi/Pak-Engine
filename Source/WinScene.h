#ifndef _WINSCENE_H_
#define _WINSCENE_H_
#include "WindowBaseClass.h"
#include "FrameBuffer.h"

class Application;

class WinScene :
    public WindowBaseClass
{
public:

    WinScene();

    ~WinScene();

    void Start();

    void Draw();

private:

    Application* app = nullptr;

};

#endif //_WINSCENE_H_
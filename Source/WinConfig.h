#ifndef _WINCONFIG_H_
#define _WINCONFIG_H_

#include "WindowBaseClass.h"

class Application;

class WinConfig :
    public WindowBaseClass
{
public:

    WinConfig();

    ~WinConfig();

    void Draw();

private:

    float brightness = 1.0f;

    int width;

    int height;

    Application* app = nullptr;

};

#endif // !_WINCONFIG_H_
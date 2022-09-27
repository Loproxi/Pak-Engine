#ifndef _WINCONFIG_H_
#define _WINCONFIG_H_

#include "WindowBaseClass.h"
#include "Globals.h"
#include <queue>

class Application;

struct Hardware_Info {
    float ram = 0.f;
    uint cpu_count = 0;
    uint cacheline = 0;
};

class WinConfig :
    public WindowBaseClass
{
public:

    WinConfig();

    ~WinConfig();

    void Draw();

    void HardwareHeader();

    void WindowHeader();

private:

    float brightness = 1.0f;

    int width;

    int height;

    bool fullscreen = false;

    bool fulldesktop = false;

    bool borderless = false;

    bool resizable = false;

    Application* app = nullptr;

    Hardware_Info hw;

    std::queue<float>frames;
};

#endif // !_WINCONFIG_H_
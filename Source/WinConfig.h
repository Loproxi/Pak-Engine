#ifndef _WINCONFIG_H_
#define _WINCONFIG_H_

#include "WindowBaseClass.h"
#include "Globals.h"
#include <vector>

class Application;

struct Hardware_Info {
    float ram = 0.0f;
    uint cpu_count = 0;
    uint cacheline = 0;
    uint64 vrambudgetmb = 0.0f;
    uint64 vramcurrentusagemb = 0.0f;
    uint64 vramavailablemb = 0.0f;
    uint64 vramreservedmb = 0.0f;
};

class WinConfig :
    public WindowBaseClass
{
public:

    WinConfig();

    ~WinConfig();

    void Start();

    void Draw();

    void RendererHeader();

    void ApplicationHeader();

    void MsInfoLogic();

    void FrameInfoLogic();

    void HardwareHeader();

    void WindowHeader();

private:

    float brightness = 1.0f;

    int width;

    int height;

    //CheckBox Options
    bool* fullscreen = nullptr;
    bool* fulldesktop = nullptr;
    bool* borderless = nullptr;
    bool* resizable = nullptr;
    bool vsync = false;
    bool* depthtest = nullptr;
    bool* cullface = nullptr;
    bool* lighting = nullptr;
    bool* wireframe = nullptr;

    Application* app = nullptr;

    Hardware_Info hw;

    std::vector<float>frames;
    std::vector<float>ms;

    char title[20];

    char title2[20];

    int limitframerate;

    int mousepositionX = 0;
    int mousepositionY = 0;

};

#endif // !_WINCONFIG_H_
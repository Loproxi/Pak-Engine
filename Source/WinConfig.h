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
    bool fullscreen = false;
    bool fulldesktop = false;
    bool borderless = false;
    bool resizable = false;
    bool vsync = false;
    bool depthtest = false;
    bool cullface = false;
    bool lighting = false;
    bool wireframe = false;

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
#ifndef _WINABOUT_H_
#define _WINABOUT_H_

#include "WindowBaseClass.h"

class Application;

class WinAbout :
    public WindowBaseClass
{

public:

    WinAbout();

    ~WinAbout();

    void Start();

    void Draw();

    void LicenseText();

    void GetLibVersionsAndPrint();

private:

    Application* app = nullptr;

    std::string verSDL;
    std::string verGlew;
    std::string verImGui;
    std::string verOpenGL;
    std::string verMathGeoLib;

};

#endif // !_WINABOUT_H_


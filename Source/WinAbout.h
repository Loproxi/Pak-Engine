#pragma once
#include "WindowBaseClass.h"
#include <string>;

class WinAbout :
    public WindowBaseClass
{

public:

    WinAbout();

    ~WinAbout();

    void Draw() override;

    void LicenseText();

    void GetLibVersionsAndPrint();

    std::string GetPakEngineVersion();

private:

    std::string verSDL;
    std::string verGlew;
    std::string verImGui;
    std::string verOpenGL;
    std::string verMathGeoLib;

};


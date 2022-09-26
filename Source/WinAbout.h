#ifndef _WINABOUT_H_
#define _WINABOUT_H_

#include "WindowBaseClass.h"


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

#endif // !_WINABOUT_H_


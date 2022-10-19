#ifndef _WINCONSOLE_H_
#define _WINCONSOLE_H_

#include "WindowBaseClass.h"
#include <vector>
#include "Application.h"


class WinConsole :
    public WindowBaseClass
{
public:

    WinConsole();

    ~WinConsole();

    void Start();

    void Draw();

private:

    std::string error,warning;

    Application* app;

    int count = 0;

    bool scrolltobottom;
    bool autoscroll;
};

#endif //_WINCONSOLE_H_

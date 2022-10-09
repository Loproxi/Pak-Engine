#ifndef _WINCONSOLE_H_
#define _WINCONSOLE_H_

#include "WindowBaseClass.h"
#include <vector>
#include "Globals.h"

struct logReport
{
    logReport(std::string msg);

    std::string message;

};

class WinConsole :
    public WindowBaseClass
{
public:

    WinConsole();

    ~WinConsole();

    void Start();

    void Draw();

    void AddLog(std::string msg);

private:

    std::vector<logReport> logReports;
    int count = 0;

    bool scrolltobottom;
    bool autoscroll;
};

#endif //_WINCONSOLE_H_

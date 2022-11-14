#ifndef __WIN_GAME_H__
#define __WIN_GAME_H__

#include "WindowBaseClass.h"
#include "FrameBuffer.h"


class Application;
class Camera3D;

class WinGame :
    public WindowBaseClass
{
public:

    WinGame();

    ~WinGame();

    void Start();

    void Draw();

private:

    Application* app = nullptr;
    FrameBuffer* framebuffer = nullptr;
};

#endif // !__WIN_GAME_H__

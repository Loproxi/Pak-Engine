#ifndef __COMP_CAMERA_H__
#define __COMP_CAMERA_H__


#include "Component.h"

class Application;

class Comp_Camera :
    public Component
{
public:

    Comp_Camera(GameObject* go);

    ~Comp_Camera();

    void Update() override;

    void OnUIController() override;

private:

    Application* app;
};

#endif // !__COMP_CAMERA_H__

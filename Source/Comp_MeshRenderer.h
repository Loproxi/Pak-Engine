#ifndef __COMPONENT_MESH_RENDERER_H_
#define __COMPONENT_MESH_RENDERER_H_

#include "Component.h"
#include "Mesh.h"

class Application;

class Comp_MeshRenderer :
    public Component
{
public:

    Comp_MeshRenderer(GameObject* _go);

    ~Comp_MeshRenderer();

    void Update() override;

    void OnUIController() override;

    void Draw(Shaders* shaders);

    void SetMesh(Mesh* _mesh);

    Mesh* GetMesh() { return mesh; }


public:

    Mesh* mesh;
    Application* app;

};

#endif // !__COMPONENT_MESH_RENDERER_H_
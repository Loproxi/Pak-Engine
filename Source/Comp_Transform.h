#ifndef __COMP_TRANSFORM_H__
#define __COMP_TRANSFORM_H__

#include "Component.h"
#include "MathGeoLib.h"


class Comp_Transform :
    public Component
{
public:
    Comp_Transform(GameObject* _go);

    ~Comp_Transform();

    void Update() override;

    void OnUIController() override;
public:
    float4x4 globalTransform;
    float4x4 localTransform;

    float3 position, localScale, eulerRotation;
    Quat rotation;
};

#endif // !__COMP_TRANSFORM_H__
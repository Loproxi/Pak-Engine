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

    float4x4 GetLocalMatrix();

    float4x4 GetGlobalMatrix();

    float4x4 GetidentityMatrix();

    float3 GetGlobalScale();

    void SetNewRotation(Quat rot);

    void SetNewTransform(float3 pos, float3x3 rot, float3 scale);

public:
    float4x4 globalTransform;
    float4x4 localTransform;
    float4x4 identity;

    float3 position, localScale, eulerRotation;
    Quat rotation;
};

#endif // !__COMP_TRANSFORM_H__
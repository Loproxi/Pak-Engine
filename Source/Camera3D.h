#ifndef _CAMERA_3D_H__
#define _CAMERA_3D_H__

#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Geometry/Frustum.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "FrameBuffer.h"

class ModuleCamera3D;

class Camera3D
{
public:

	Camera3D();

	~Camera3D();

	//Camera Options

	void Look(const float3& Position, const float3& Reference, bool RotateAroundReference = false);
	void LookAt(const float3& toLookAt);
	void Move(const float3& Movement);

	//Getters
	float* GetViewMatrix();
	float* GetProjMatrix();

public:

	float3 X;
	float3 Y;
	float3 Z;
	float3 position;
	float3 reference;

private:

	float4x4 ViewMatrix;
	float4x4 ViewMatrixInverse;
	float4x4 ProjMatrix;

	Frustum CameraFrustrum;

	FrameBuffer framebuffer;

	friend class ModuleCamera3D;
};

#endif // !_CAMERA_3D_H__
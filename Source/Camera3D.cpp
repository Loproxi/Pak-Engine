#include "Camera3D.h"
#include "MathGeoLib.h"


Camera3D::Camera3D()
{

	X = float3(1.0f, 0.0f, 0.0f);
	Y = float3(0.0f, 1.0f, 0.0f);
	Z = float3(0.0f, 0.0f, 1.0f);

	CameraFrustrum.type = FrustumType::PerspectiveFrustum;
	CameraFrustrum.verticalFov = DegToRad(60.0f);
	CameraFrustrum.horizontalFov = 2.0f * atanf(tanf(CameraFrustrum.verticalFov / 2.0f) * 1.77f);

	CameraFrustrum.farPlaneDistance = 500.0f;
	CameraFrustrum.nearPlaneDistance = 0.1f;
	CameraFrustrum.front = Z;
	CameraFrustrum.up = Y;

	position = float3(0.0f, 0.0f, -5.0f);
	reference = float3(0.0f, 0.0f, 0.0f);

	CameraFrustrum.pos = position;

}

Camera3D::~Camera3D()
{
}

void Camera3D::Look(const float3& Position, const float3& Reference, bool RotateAroundReference)
{
	position = Position;
	reference = Reference;

	CameraFrustrum.front = (position - reference).Normalized();
	
	CameraFrustrum.up = Cross(CameraFrustrum.front, X);

	if (!RotateAroundReference)
	{
		this->reference = this->position;
		this->position += Z * 0.05f;
	}

}

void Camera3D::LookAt(const float3& toLookAt)
{

	CameraFrustrum.front = (toLookAt - CameraFrustrum.pos).Normalized();

	//Cross product of Frustrum Z axis and Y axis
	X = Cross(float3(0.0f, 1.0f, 0.0f),CameraFrustrum.front).Normalized();
	//Cross product of Frustrum Z axis and X axis
	CameraFrustrum.up = Cross(CameraFrustrum.front, X);

}

void Camera3D::Move(const float3& Movement)
{
	//Updates frustrum position
	CameraFrustrum.pos += Movement;
}

float* Camera3D::GetViewMatrix()
{
	ViewMatrix = CameraFrustrum.ViewMatrix();
	//In order to pass it to opengl we have to transpose it
	ViewMatrix.Transpose();
	return &ViewMatrix.v[0][0];
}

float* Camera3D::GetProjMatrix()
{
	ProjMatrix = CameraFrustrum.ProjectionMatrix();
	//In order to pass it to opengl we have to transpose it
	ProjMatrix.Transpose();
	return &ProjMatrix.v[0][0];
}

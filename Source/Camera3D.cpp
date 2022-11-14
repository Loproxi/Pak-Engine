#include "Camera3D.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleInput.h"


Camera3D::Camera3D():FieldOfView(60.0f)
{

	X = float3(1.0f, 0.0f, 0.0f);
	Y = float3(0.0f, 1.0f, 0.0f);
	Z = float3(0.0f, 0.0f, 1.0f);

	CameraFrustrum.type = FrustumType::PerspectiveFrustum;
	CameraFrustrum.verticalFov = DegToRad(FieldOfView);
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
	//ViewMatrix;
	float4x4 tempview = CameraFrustrum.ViewMatrix();
	//In order to pass it to opengl we have to transpose it
	tempview.Transpose();
	return &tempview.v[0][0];
}

float* Camera3D::GetProjMatrix()
{
	//ProjMatrix = 
	float4x4 tempproj = CameraFrustrum.ProjectionMatrix();
	//In order to pass it to opengl we have to transpose it
	tempproj.Transpose();
	return &tempproj.v[0][0];
}

void Camera3D::SetUpFrameBuffer(int width, int height)
{
	framebuffer.SettingUpFrameBuffer(width, height);
}

void Camera3D::ScrollZoom()
{
	/*FieldOfView = FieldOfView - Application::GetInstance()->input->GetMouseZ();
	if (FieldOfView < 20.0f)FieldOfView = 20.0f;
	if (FieldOfView > 60.0f)FieldOfView = 60.0f;

	CameraFrustrum.verticalFov = DegToRad(FieldOfView);
	CameraFrustrum.horizontalFov = 2.0f * atanf(tanf(CameraFrustrum.verticalFov / 2.0f) * 1.77f);*/
}
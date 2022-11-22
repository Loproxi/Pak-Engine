#include "Camera3D.h"
#include "MathGeoLib.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"
#include "ModuleWindow.h"


Camera3D::Camera3D():FieldOfView(60.0f)
{

	X = float3(1.0f, 0.0f, 0.0f);
	Y = float3(0.0f, 1.0f, 0.0f);
	Z = float3(0.0f, 0.0f, 1.0f);

	aspectratio = 1.77f;

	CameraFrustrum.type = FrustumType::PerspectiveFrustum;
	CameraFrustrum.verticalFov = DegToRad(FieldOfView);
	CameraFrustrum.horizontalFov = 2.0f * atanf(tanf(CameraFrustrum.verticalFov / 2.0f) * aspectratio);

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

void Camera3D::SetAsGameCamera()
{
	app = Application::GetInstance();

	if (app->camera->gamecamactive != nullptr)
	{
		for (int i = 0; i < app->camera->gamecams.size(); i++)
		{
			if (app->camera->gamecams[i]->isgamecameractive == true)
			{
				app->camera->gamecams[i]->isgamecameractive = false;
				app->camera->gamecamactive = nullptr;
				break;
			}
		}
	}
	if(app->camera->gamecamactive == nullptr)
	{
		this->isgamecameractive = true;
		app->camera->gamecamactive = this;
		
	}
}

void Camera3D::SetAspectRatio(float width, float height)
{
	CameraFrustrum.horizontalFov = 2.0f * atanf(tanf(CameraFrustrum.verticalFov * 0.5f) * (width/height));
	aspectratio = (width / height);
}

void Camera3D::ScrollZoom()
{
	/*FieldOfView = FieldOfView - Application::GetInstance()->input->GetMouseZ();
	if (FieldOfView < 20.0f)FieldOfView = 20.0f;
	if (FieldOfView > 60.0f)FieldOfView = 60.0f;

	CameraFrustrum.verticalFov = DegToRad(FieldOfView);
	CameraFrustrum.horizontalFov = 2.0f * atanf(tanf(CameraFrustrum.verticalFov / 2.0f) * 1.77f);*/
}

bool Camera3D::FrustrumContainsBB(AABB& globalBB)
{
	bool isBBcontained = false;

	float3 OBBCornerpoints[8];
	Plane camerafrustrumplanes[6];
	int iTotalIn = 0;
	CameraFrustrum.GetPlanes(camerafrustrumplanes);
	globalBB.GetCornerPoints(OBBCornerpoints); // get the corners of the box into the vCorner array
	// test all 8 corners against the 6 sides
	// if all points are behind 1 specific plane, we are out
	// if we are in with all points, then we are fully in
	for (int p = 0; p < 6; ++p) {
		int iInCount = 8;
		int iPtIn = 1;
		for (int i = 0; i < 8; ++i) {
			// test this point against the planes
			if (camerafrustrumplanes[p].IsOnPositiveSide(OBBCornerpoints[i]) ) { //<-- “IsOnPositiveSide” from MathGeoLib
				iPtIn = 0;
				--iInCount;
			}
		}
		// were all the points outside of plane p?
		if (iInCount == 0)
		{
			isBBcontained = false;
			return isBBcontained;
		}
		// check if they were all on the right side of the plane
		iTotalIn += iPtIn;
	}

	isBBcontained = true;
	return isBBcontained;
}

#include <iostream>
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "MathGeoLib/include/Math/MathFunc.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	for (int i = 0; i < gamecams.size(); i++)
	{
		RELEASE(gamecams[i]);
	}
	gamecams.clear();
	return true;
}

bool ModuleCamera3D::SaveSettings(pugi::xml_node& config)
{
	return true;
}

Camera3D* ModuleCamera3D::AddCamera()
{
	Camera3D* camera = new Camera3D();
	gamecams.push_back(camera);
	return camera;
}

void ModuleCamera3D::DestroyCamera3D(Camera3D* camToDestroy)
{

	for (int i = 0; i < gamecams.size(); i++)
	{
		if (gamecams[i] == camToDestroy)
		{
			RELEASE(gamecams[i]);
			gamecams.erase(gamecams.begin() + i);
		}
	}
}

// -----------------------------------------------------------------
UpdateStatus ModuleCamera3D::Update()
{

	SceneCameraHandleInput();

	return UPDATE_CONTINUE;
}

void ModuleCamera3D::SceneCameraHandleInput()
{

	CamMovementInput();
	// Mouse motion ----------------
	CamRotationInput();

	/*if (App->input->GetMouseZ() != 0)
	{
		scenecam.ScrollZoom();
	}*/
}

void ModuleCamera3D::CamMovementInput()
{
	float3 newPos(0, 0, 0);
	float speed = 3.0f * App->fps;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 20.0f * App->fps;

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) newPos.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos += scenecam.CameraFrustrum.front * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos -= scenecam.CameraFrustrum.front * speed;


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= scenecam.CameraFrustrum.WorldRight() * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += scenecam.CameraFrustrum.WorldRight() * speed;

	scenecam.Move(newPos);
	scenecam.position += newPos;
	scenecam.reference += newPos;
}

void ModuleCamera3D::CamRotationInput()
{

	Quat DirectionTolook = Quat::identity;
	scenecam.CameraFrustrum.WorldMatrix().Decompose(float3(0.0f,0.0f,0.0f), DirectionTolook, float3(0.0f, 0.0f, 0.0f));

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		scenecam.position -= scenecam.reference;

		if (dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;

			Quat tempX = Quat::identity;
			//Apply delta X rotation on Y axis and apply it on the quaternion
			tempX.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DegToRad(DeltaX));
			//X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			//Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			//Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));

			DirectionTolook = tempX * DirectionTolook;
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Quat tempY = Quat::identity;
			//Apply delta Y rotation on X axis and apply it on the quaternion
			tempY.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DegToRad(DeltaY));

			DirectionTolook = DirectionTolook * tempY;
		}

		float4x4 aux = scenecam.CameraFrustrum.WorldMatrix();
		aux.SetRotatePart(DirectionTolook.Normalized());
		scenecam.CameraFrustrum.SetWorldMatrix(aux.Float3x4Part());
	}
}

//void ModuleCamera3D::SetTarget(Vehicle* tg, vec3 offset)
//{
//	target = tg;
//	this->offset = offset;
//}
//
//void ModuleCamera3D::RemoveTarget()
//{
//	target = nullptr;
//}

// -----------------------------------------------------------------

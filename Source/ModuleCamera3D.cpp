#include <iostream>
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "MathGeoLib/include/Math/MathFunc.h"


ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
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

	return true;
}

bool ModuleCamera3D::SaveSettings(pugi::xml_node& config)
{
	return true;
}

// -----------------------------------------------------------------
UpdateStatus ModuleCamera3D::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		std::cout << "Cam Pos: x(" << Position.x << ") y(" << Position.y << ") z(" << Position.z << ")" << std::endl;
	}
	//if (target != nullptr)
	//{
	//	Look(target->GetObserverPos(), target->GetPosition());
	//}
	else
	{
		// Implement a debug camera with keys and mouse
		// Now we can make this movememnt frame rate independant!

		Camera3DHandleInput();
	}

	LOG("Recalculate matrix -------------");
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

void ModuleCamera3D::Camera3DHandleInput()
{
	float3 newPos(0, 0, 0);
	float speed = 3.0f * App->fps;
	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 20.0f * App->fps;
	
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y += speed;
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) newPos.y -= speed;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos -= scenecam.CameraFrustrum.front * speed;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos += scenecam.CameraFrustrum.front * speed;


	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= scenecam.CameraFrustrum.WorldRight() * speed;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += scenecam.CameraFrustrum.WorldRight() * speed;

	scenecam.position += newPos;
	scenecam.reference += newPos;

	// Mouse motion ----------------

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

			tempX.SetFromAxisAngle(float3(0.0f, 1.0f, 0.0f), DegToRad(DeltaX));
			//X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			//Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
			//Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
		}

		if (dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Quat tempY = Quat::identity;

			tempY.SetFromAxisAngle(float3(1.0f, 0.0f, 0.0f), DegToRad(DeltaY));

			/*Y = rotate(Y, DeltaY, X);
			Z = rotate(Z, DeltaY, X);*/

			if (Y.y < 0.0f)
			{
				Z = vec3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = cross(Z, X);
			}
		}

		Position = Reference + Z * length(Position);
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
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = mat4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -dot(X, Position), -dot(Y, Position), -dot(Z, Position), 1.0f);
	ViewMatrixInverse = inverse(ViewMatrix);
}

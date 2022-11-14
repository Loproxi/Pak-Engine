#ifndef __MODULECAMERA3D_H__
#define __MODULECAMERA3D_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Camera3D.h"


class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	UpdateStatus Update();
	void Camera3DHandleInput();
	bool CleanUp();

	bool SaveSettings(pugi::xml_node& config);

	//void SetTarget(Vehicle* tg, vec3 offset);
	//void RemoveTarget();

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;

	vec3 offset;

	Camera3D scenecam;

};

#endif // !__MODULECAMERA3D_H__
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
	void SceneCameraHandleInput();
	void CamMovementInput();
	void CamRotationInput();
	bool CleanUp();

	bool SaveSettings(pugi::xml_node& config);

	//void SetTarget(Vehicle* tg, vec3 offset);
	//void RemoveTarget();
	Camera3D* AddCamera();

	void DestroyCamera3D(Camera3D* camToDestroy);

public:

	std::vector<Camera3D*> gamecams;

	Camera3D scenecam;

	Camera3D* cameratobedrawn = nullptr;

	Camera3D* gamecamactive = nullptr;

};

#endif // !__MODULECAMERA3D_H__
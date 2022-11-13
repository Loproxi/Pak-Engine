#include "Comp_Camera.h"
#include "Application.h"

Comp_Camera::Comp_Camera(GameObject* go):Component(go)
{
	app = Application::GetInstance();
}

Comp_Camera::~Comp_Camera()
{
}

void Comp_Camera::Update()
{
}

void Comp_Camera::OnUIController()
{
}

#include "Comp_Transform.h"


Comp_Transform::Comp_Transform(GameObject* _go):Component(_go)
{
	this->type = COMP_TYPE::TRANSFORM;
	localTransform.SetIdentity();
	globalTransform.SetIdentity();
}

Comp_Transform::~Comp_Transform()
{
}

void Comp_Transform::Update()
{
}

void Comp_Transform::OnUIController()
{
}

#include "Component.h"

Component::Component(GameObject* _go):comp_owner(_go),type(COMP_TYPE::NONE),active(true),name("Nameless Component")
{
	//Init variables
}

Component::~Component()
{
}

void Component::OnEnable()
{
}

void Component::Update()
{
}

void Component::OnDisable()
{
}

void Component::OnUIController()
{
}

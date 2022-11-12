#include "Comp_Transform.h"
#include "ImGuiUtils.h"


Comp_Transform::Comp_Transform(GameObject* _go):Component(_go)
{
	this->type = COMP_TYPE::TRANSFORM;
	localTransform.SetIdentity();
	globalTransform.SetIdentity();
	
	//Getting Pos,Rot and Scale from the local transform matrix
	localTransform.Decompose(position, rotation, localScale);
	//Transform quaternion to euler angles
	eulerRotation = rotation.ToEulerXYZ();
}

Comp_Transform::~Comp_Transform()
{
}

void Comp_Transform::Update()
{
}

void Comp_Transform::OnUIController()
{

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{

		ImGui::DragFloat3("Position", &position[0]);
		ImGui::DragFloat3("Rotation", &eulerRotation[0]);
		ImGui::DragFloat3("Scale", &localScale[0]);
	}

}

#include "Comp_Transform.h"
#include "ImGuiUtils.h"
#include "GameObject.h"


Comp_Transform::Comp_Transform(GameObject* _go):Component(_go)
{
	this->type = COMP_TYPE::TRANSFORM;
	localTransform.SetIdentity();
	globalTransform.SetIdentity();
	//Getting Pos,Rot and Scale from the local transform matrix
	localTransform.Decompose(position, rotation, localScale);
	//Transform quaternion to euler angles
	rotation.Normalize();
	eulerRotation = rotation.ToEulerXYZ();
	
}

Comp_Transform::~Comp_Transform()
{
}

void Comp_Transform::Update()
{

	
	//GetGlobalMatrix();
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

float4x4 Comp_Transform::GetLocalMatrix()
{
	float4x4 aux;
	rotation = Quat::FromEulerXYZ(math::DegToRad(eulerRotation.x), math::DegToRad(eulerRotation.y), math::DegToRad(eulerRotation.z));
	rotation.Normalize();

	aux = float4x4::FromTRS(position, rotation, localScale);

	
	return aux;
}

float4x4 Comp_Transform::GetGlobalMatrix()
{
	float4x4 aux;
	if (comp_owner->parent == nullptr)
	{
		aux = GetidentityMatrix() * GetLocalMatrix();
		
	}
	else
	{
		aux = comp_owner->parent->GetComponent<Comp_Transform>()->GetGlobalMatrix() * GetLocalMatrix();
		
	}

	return aux;
}

float4x4 Comp_Transform::GetidentityMatrix()
{
	float4x4 identity;
	identity.SetIdentity();
	return identity;
}

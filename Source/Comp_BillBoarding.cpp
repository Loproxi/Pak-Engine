#include "Comp_BillBoarding.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "Comp_Transform.h"
#include "ImGuiUtils.h"


Comp_BillBoarding::Comp_BillBoarding(GameObject* go) : Component(go),typeofBBoard(BILLBOARDTYPE::NO_ALIGN),staticYAxisBillboard(false)
{
	this->name = "BillBoard";
	this->type = COMP_TYPE::BILLBOARD;

	app = Application::GetInstance();
}

Comp_BillBoarding::~Comp_BillBoarding()
{
}

void Comp_BillBoarding::Update()
{
	switch (typeofBBoard)
	{

	case SCREENALIGN:

		//Screen Align CODE

		ScreenAlignBBoard();

		break;
	case WORLDALIGN:

		//World Align CODE

		break;
	case AXISALIGN:

		//Screen Align CODE

		break;

	default:
		break;
	}
}

void Comp_BillBoarding::OnUIController()
{

	if (ImGui::CollapsingHeader("BillBoard: ", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::BeginMenu("Select your BillBoard"))
		{

			if (ImGui::MenuItem("Screen Align BillBoard"))
			{
				typeofBBoard = BILLBOARDTYPE::SCREENALIGN;
			}
			else if (ImGui::MenuItem("World Align BillBoard"))
			{
				typeofBBoard = BILLBOARDTYPE::WORLDALIGN;
			}
			else if (ImGui::MenuItem("Axis Align BillBoard"))
			{
				typeofBBoard = BILLBOARDTYPE::AXISALIGN;
			}
			else if (ImGui::MenuItem("No Align BillBoard"))
			{
				typeofBBoard = BILLBOARDTYPE::NO_ALIGN;
			}
						
			
			ImGui::End();
		}
	}

	if (typeofBBoard == BILLBOARDTYPE::WORLDALIGN)
	{
		ImGui::Checkbox("Static BillBoard On Y Axis", &staticYAxisBillboard);
	}


}

void Comp_BillBoarding::ScreenAlignBBoard()
{
	//GET INFO ABOUT CAM AXIS
	float3 activecamfront = app->camera->gamecamactive->CameraFrustrum.front;
	float3 activecamup = app->camera->gamecamactive->CameraFrustrum.up;

	//Z-AXIS MUST BE INVERTED 
	zBBoardAxis = -activecamfront;
	//Y-AXIS KEEPS THE SAME VALUE
	yBBoardAxis = activecamup;

	//COMPUTE CROSS PRODUCT IN ORDER TO GET THE REMAINING AXIS
	xBBoardAxis = yBBoardAxis.Cross(zBBoardAxis).Normalized();

	//Gather the axis into a 3x3 matrix
	float3x3 rotBBoard;
	rotBBoard.Set(xBBoardAxis.x, xBBoardAxis.y, xBBoardAxis.z, yBBoardAxis.x, yBBoardAxis.y, yBBoardAxis.z, zBBoardAxis.x, zBBoardAxis.y, zBBoardAxis.z);

	float3 auxtranspos;

	comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix().Decompose(auxtranspos, Quat(),float3());

	float4x4 newTransform = float4x4::FromTRS(auxtranspos, rotBBoard, comp_owner->GetComponent<Comp_Transform>()->GetGlobalScale());


	//Convert it to global space
	float4x4 temp = comp_owner->parent->GetComponent<Comp_Transform>()->GetGlobalMatrix();
	temp.Inverse();

	newTransform = temp.Mul(newTransform);

	float3 newtranspos;
	float3 newtransscale;


	newTransform.Decompose(newtranspos, Quat(), newtransscale);
	//Pass it to comp owner transform 

	comp_owner->GetComponent<Comp_Transform>()->SetNewTransform(newtranspos, rotBBoard, newtransscale);


}

void Comp_BillBoarding::WorldAlignBBoard()
{
	//Vector from gameobject to cam
	zBBoardAxis = (app->camera->cameratobedrawn->CameraFrustrum.pos - comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix().TranslatePart()).Normalized();

	//Vector UP is the same as the cam
	if (staticYAxisBillboard == false)
	{
		yBBoardAxis = app->camera->cameratobedrawn->CameraFrustrum.up;
	}
	else
	{
		yBBoardAxis = {0.0f,1.0f,0.0f};
	}

	//COMPUTE CROSS PRODUCT IN ORDER TO GET THE REMAINING AXIS

	xBBoardAxis = zBBoardAxis.Cross(yBBoardAxis).Normalized();

	//COMPUTE Y AXIS AGAIN IN ORDER TO BE SURE THAT THE ANGLE BETWEEN Z AND Y IS 90 degrees

	yBBoardAxis = zBBoardAxis.Cross(xBBoardAxis).Normalized();

	//Gather the axis into a 3x3 matrix
	float3x3 rotBBoard;
	rotBBoard.Set(xBBoardAxis.x, xBBoardAxis.y, xBBoardAxis.z, yBBoardAxis.x, yBBoardAxis.y, yBBoardAxis.z, zBBoardAxis.x, zBBoardAxis.y, zBBoardAxis.z);

	Quat aux;
	aux = rotBBoard.Inverted().ToQuat();
	aux.Normalize();

	float3 newtranspos;
	float3 newtransscale;

	comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix().Decompose(newtranspos, Quat(), newtransscale);

	//Pass it to comp owner transform 

	//comp_owner->GetComponent<Comp_Transform>()->SetNewTransform(newtranspos, aux, newtransscale);

}

void Comp_BillBoarding::AxisAlignBBoard()
{

	//Vector from gameobject to cam
	zBBoardAxis = (app->camera->cameratobedrawn->CameraFrustrum.pos - comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix().TranslatePart()).Normalized();

	//Vector UP is the same as the cam
	yBBoardAxis = { 0.0f,1.0f,0.0f };

	//COMPUTE CROSS PRODUCT IN ORDER TO GET THE REMAINING AXIS

	xBBoardAxis = zBBoardAxis.Cross(yBBoardAxis).Normalized();

	//COMPUTE Y AXIS AGAIN IN ORDER TO BE SURE THAT THE ANGLE BETWEEN Z AND Y IS 90 degrees

	yBBoardAxis = zBBoardAxis.Cross(xBBoardAxis).Normalized();

	//Gather the axis into a 3x3 matrix
	float3x3 rotBBoard = float3x3::identity;
	rotBBoard.Set(xBBoardAxis.x, xBBoardAxis.y, xBBoardAxis.z, yBBoardAxis.x, yBBoardAxis.y, yBBoardAxis.z, zBBoardAxis.x, zBBoardAxis.y, zBBoardAxis.z);

	Quat aux;
	aux = rotBBoard.Inverted().ToQuat();
	aux.Normalize();

	float3 newtranspos;
	float3 newtransscale;

	comp_owner->GetComponent<Comp_Transform>()->GetGlobalMatrix().Decompose(newtranspos, Quat(), newtransscale);

	float4x4 newtransform = float4x4::FromTRS(newtranspos, rotBBoard, newtransscale);


	//Pass it to comp owner transform 


}

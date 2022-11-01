#include "WinInspector.h"
#include "ImGuiUtils.h"

WinInspector::WinInspector():goToInspect(nullptr)
{
	name = "Inspector";
	
}

WinInspector::~WinInspector()
{
}

void WinInspector::Start()
{
}

void WinInspector::Draw()
{
	if (isEnabled)
	{
		if (ImGui::Begin(name.c_str(), &isEnabled))
		{

			ImGui::Text("Not implemented yet");

			
		}
		ImGui::End();
	}
}

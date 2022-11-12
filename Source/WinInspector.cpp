#include "WinInspector.h"
#include "ImGuiUtils.h"
#include "GameObject.h"

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
			if (goToInspect != nullptr)
			{
				for each (Component* comp in goToInspect->components)
				{
					comp->OnUIController();
				}
			}
		}
		ImGui::End();
	}
}

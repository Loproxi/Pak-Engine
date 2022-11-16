#include "WinInspector.h"
#include "ImGuiUtils.h"
#include "GameObject.h"

WinInspector::WinInspector():goToInspect(nullptr)
{
	name = "Inspector##test";
	
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

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::BeginCombo("Add Component", "Select Component", ImGuiComboFlags_PopupAlignLeft))
				{
					for (int i = 0; i < 2; i++)
					{
						if (ImGui::Selectable(items[i].c_str()))
						{
							switch (i)
							{
							case 0:
								goToInspect->AddComponent(COMP_TYPE::MESH_RENDERER);
								break;
							case 1:
								goToInspect->AddComponent(COMP_TYPE::CAMERA);
								break;
							default:
								break;
							}
						}
					}
					ImGui::EndCombo();
				}
			}
		}
		ImGui::End();
	}
}

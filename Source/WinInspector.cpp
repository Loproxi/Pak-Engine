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

				ImGui::Checkbox("Set as Transparent", &goToInspect->transparent);

				for each (Component* comp in goToInspect->components)
				{
					comp->OnUIController();
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::BeginCombo("Add Component", "Select Component", ImGuiComboFlags_PopupAlignLeft))
				{
					for (int i = 0; i < 4; i++)
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
							case 2:
								goToInspect->AddComponent(COMP_TYPE::BILLBOARD);
								break;
							case 3:
								goToInspect->AddComponent(COMP_TYPE::PARTICLE_SYSTEM);
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

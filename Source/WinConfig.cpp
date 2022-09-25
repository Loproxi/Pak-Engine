#include "WinConfig.h"
#include "Globals.h"

WinConfig::WinConfig()
{
	name = "Configuration";

}

WinConfig::~WinConfig()
{
}

void WinConfig::Draw()
{

	if (ImGui::Begin(name.c_str(), &isEnabled))
	{

		if (ImGui::CollapsingHeader("Application"))
		{
			std::string appname;
			appname = TITLE;
			/*ImGui::InputText(appname.c_str())*/
		}
		
	}
	ImGui::End();

}

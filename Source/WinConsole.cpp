#include "WinConsole.h"
#include "imgui.h"

WinConsole::WinConsole():autoscroll(true),scrolltobottom(false)
{
	name = "Console";
	app = Application::GetInstance();
}

WinConsole::~WinConsole()
{
	app->logreports.clear();
}

void WinConsole::Start()
{
}

void WinConsole::Draw()
{
	if (ImGui::Begin(name.c_str(),&isEnabled))
	{
		if (ImGui::Button("Clear"))
		{
			app->logreports.clear();
		}
		ImGui::SameLine();
		if (ImGui::Button("Scroll To Bottom"))
		{
			scrolltobottom =true;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("AutoScroll", &autoscroll))
		{

		}
		if (ImGui::BeginChild("Output"))
		{
			for (uint i = 0; i < app->logreports.size(); i++)
			{
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), app->logreports.data()[i].message.c_str());
				
			}
			if (scrolltobottom)
			{
				ImGui::SetScrollHereY(1.0f);
				scrolltobottom = false;
			}
			if (autoscroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			{
				ImGui::SetScrollHereY(1.0f);
			}
			
		}
		ImGui::EndChild();

	}
	ImGui::End();
}

logReport::logReport(std::string msg)
{
	message = msg;
}

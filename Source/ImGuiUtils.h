#pragma once

#include "imgui.h"
#include "Globals.h"


 // from https://github.com/juliettef/IconFontCppHeaders


namespace ImGui
{
	class ColSwitchTemp
	{
		ImGuiCol_ toChange;
		ImVec4    prevCol;
		bool      bIsSet;
	public:
		ColSwitchTemp( ImGuiCol_ toChange_, ImVec4 to_ ) : toChange( toChange_ )
		{
			ImGuiStyle& style = ImGui::GetStyle();
			prevCol = style.Colors[toChange];
			style.Colors[toChange] = to_;
			bIsSet = true;
		}

		void Reset()
		{
			if( bIsSet )
			{
				ImGui::GetStyle().Colors[toChange] = prevCol;
				bIsSet = false;
			}
		}

		~ColSwitchTemp()
		{
			Reset();
		}

	};

	inline void TextCentered(std::string text) {
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(text.c_str());
	}

	inline void DummyWidget()
	{
		ImGui::Dummy( ImVec2(0.0f, ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y*2.0f ) );
	}

	inline void DummyText()
	{
		ImGui::Dummy( ImVec2(0.0f, ImGui::GetTextLineHeight() ) );
	}


	inline void AddUnderLine( ImColor col_ )
	{
		ImVec2 min = ImGui::GetItemRectMin();
		ImVec2 max = ImGui::GetItemRectMax();
		min.y = max.y;
		ImGui::GetWindowDrawList()->AddLine( min, max, col_, 1.0f );
	}

	// hyperlink urls
	inline void TextURL( const char* name_, const char* URL_, uint8_t SameLineBefore_, uint8_t SameLineAfter_ )
    {
	    if( 1 == SameLineBefore_ ){ ImGui::SameLine( 0.0f, ImGui::GetStyle().ItemInnerSpacing.x ); }
		ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered]);
        ImGui::Text( name_ );
		ImGui::PopStyleColor();
		if (ImGui::IsItemHovered())
		{
			if( ImGui::IsMouseClicked(0) )
			{
                ShellExecute(0, 0, URL_, 0, 0, SW_SHOW);
			}
			AddUnderLine( ImGui::GetStyle().Colors[ImGuiCol_ButtonHovered] );
            ImGui::SetTooltip("  Open in browser\n%s", URL_);
		}
		else
		{
			AddUnderLine( ImGui::GetStyle().Colors[ImGuiCol_Button] );
		}
		if( 1 == SameLineAfter_ ){ ImGui::SameLine( 0.0f, ImGui::GetStyle().ItemInnerSpacing.x ); }
    }

	// menu item urls
	inline void MenuItemURL( const char* name_, const char* URL_ )
    {
		std::string linkIconName = std::string("\t" + std::string(name_));
		if( ImGui::MenuItem( linkIconName.c_str()))
		{
			ShellExecute(0, 0, URL_, 0, 0, SW_SHOW);
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("  Open in browser\n%s", URL_);
		}
    }

};

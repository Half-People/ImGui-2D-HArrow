// By HalfPeople Studio
#pragma once
#include "Imgui.h"
#include <vector>
#include "imgui_internal.h"
#include <Windows.h>
#include "HArrow.h"


int SaveSelectWidget = -1;
std::vector<ImVec2> WidgetPos;


int Positioning =0;
//Execute only once
void InitGUI()
{
	for (size_t i = 0; i < 15; i++)
	{
		WidgetPos.push_back(ImVec2(5, 30 * i + 1));
	}
}

//draw loop
void DrawGUI()
{
	ImGui::Begin(u8"×÷˜IÓÃ");

	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 250);
	ImGui::SetNextItemWidth(150);
	ImGui::DragInt("Positioning", &Positioning,1,0,100000,"%d",ImGuiSliderFlags_AlwaysClamp);

	for (size_t i = 0; i < 15; i++)
	{

		ImGui::SetCursorPos(WidgetPos.at(i));
		ImGui::Button(std::string("Button_").append(std::to_string(i)).c_str());

		if (SaveSelectWidget == i)
		{
			HArray(WidgetPos.at(i), Positioning);
		}
		else
		{
			if (ImGui::IsItemActive())
			{
				SaveSelectWidget = i;
			}
		}
	}

	ImGui::End();

}

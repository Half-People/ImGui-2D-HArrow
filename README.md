# ImGui-2D-HArrow

# Demo
![image](https://user-images.githubusercontent.com/56476339/215027875-d9322ebc-77ab-4a74-8caf-3095452eabc9.png)
![ezgif com-gif-maker](https://user-images.githubusercontent.com/56476339/215029036-11dea605-799d-4b43-bce1-46081cd67f28.gif)

# HowToUse?
First you have to include HArrow.h and then add HArrow after the Widget you want to add Arrow

example:
```
#include "HArrow.h"


int SaveSelectWidget = -1;
std::vector<ImVec2> WidgetPos;


int Positioning =0;

void InitGUI()
{
	for (size_t i = 0; i < 15; i++)
	{
		WidgetPos.push_back(ImVec2(5, 30 * i + 1));
	}
}


void DrawGUI()
{
	ImGui::Begin(u8"作業用");

	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 250);
	ImGui::SetNextItemWidth(150);
	ImGui::DragInt("Positioning", &Positioning,1,0,100000,"%d",ImGuiSliderFlags_AlwaysClamp);

	for (size_t i = 0; i < 15; i++)
	{

		ImGui::SetCursorPos(WidgetPos.at(i));
		ImGui::Button(std::string("Button_").append(std::to_string(i)).c_str());

		if (SaveSelectWidget == i)
		{
			HArray(WidgetPos.at(i), Positioning); // <<-------------------------------------------------
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
```

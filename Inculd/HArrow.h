// By HalfPeople Studio

#pragma once
#include <imgui_internal.h>

static void HBorder(const char* ID, const ImVec4& col, const ImVec2& size_arg, float rounding = 1)
{
	ImGuiWindow* Windows = ImGui::GetCurrentWindow();
	if (Windows->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	ImGuiID id = Windows->GetID(ID);
	const float default_size = ImGui::GetFrameHeight();
	const ImVec2 size(size_arg.x == 0.0f ? default_size : size_arg.x, size_arg.y == 0.0f ? default_size : size_arg.y);
	const ImRect bb(Windows->DC.CursorPos, ImVec2(Windows->DC.CursorPos.x + size.x, Windows->DC.CursorPos.y + size.y));
	ImGui::ItemSize(bb, (size.y >= default_size) ? g.Style.FramePadding.y : 0.0f);
	if (!ImGui::ItemAdd(bb, id))
		return;

	Windows->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(col), rounding);
}

static void HArray(ImVec2& pos, int Positioning = 0)
{

	ImGuiContext& g = *GImGui;

	ImVec2 SaveStartPos;
	ImVec2 SaveSize;
	static ImVec2 Offset;
	static bool NeedUpdata;
	static int Mode = -1;
	static bool CanUpdata = true;

	if (g.IO.MouseDown[0])
	{
		if (NeedUpdata)
		{
			SaveStartPos = ImGui::GetWindowPos();
			SaveSize = ImGui::GetMousePos();
			Offset = ImVec2((pos.x + SaveStartPos.x) - SaveSize.x, (pos.y + SaveStartPos.y) - SaveSize.y);
			NeedUpdata = false;
		}
	}
	else
	{
		Mode = -1;
		NeedUpdata = true;
		CanUpdata = true;
	}

	SaveStartPos = pos;

	SaveSize = ImGui::GetItemRectSize();
	SaveStartPos.x += SaveSize.x / 2;
	SaveStartPos.y += (SaveSize.y / 2);

	ImGui::SetCursorPos(ImVec2(SaveStartPos.x + 9, SaveStartPos.y - 3));
	HBorder("###X", ImColor(255, 0, 0), ImVec2(41, 6));
	if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
	{
		Mode = 0;
	}


	ImGui::SetCursorPos(ImVec2(SaveStartPos.x - 3, SaveStartPos.y - 41));
	HBorder("###Y", ImColor(0, 255, 0), ImVec2(6, 41));
	if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
	{
		Mode = 1;
	}

	ImGui::SetCursorPos(ImVec2(SaveStartPos.x - 9, SaveStartPos.y - 9));
	HBorder("###Auto", ImColor(255, 255, 255), ImVec2(18, 18));
	if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
	{
		Mode = 2;
	}

	//if (ImGui::IsMouseDragging(0) && (!NeedUpdata) )
	if (!NeedUpdata && ImGui::IsMouseDragging(0))
	{
		ImVec2 MousePos = ImGui::GetMousePos();
		ImVec2 WinPos = ImGui::GetWindowPos();
		CanUpdata = false;


		if (Positioning)
		{
			ImDrawList* DL = ImGui::GetWindowDrawList();
			ImVec2 WindowSize = ImGui::GetWindowSize();
			for (size_t X = 0; X < WindowSize.x / Positioning; X++)
			{
				float XP = (X * Positioning) + WinPos.x + SaveSize.x / 2;
				DL->AddLine(ImVec2(XP, WinPos.y), ImVec2(XP, WindowSize.y + WinPos.y), ImColor(255, 255, 255, 40));
			}
			for (size_t Y = 0; Y < WindowSize.y / Positioning; Y++)
			{
				float YP = (Y * Positioning) + WinPos.y + SaveSize.y / 2;
				DL->AddLine(ImVec2(WinPos.x, YP), ImVec2(WindowSize.x + WinPos.x, YP), ImColor(255, 255, 255, 40));
			}

		}



		if (Mode == 0)//x
		{
			MousePos.x -= WinPos.x;
			if (Positioning)
			{
				pos.x = ((int)(MousePos.x + Offset.x) / Positioning) * Positioning;
			}
			else
			{
				pos.x = MousePos.x + Offset.x;
			}
		}
		else if (Mode == 1)//y
		{
			MousePos.y -= WinPos.y;
			if (Positioning)
			{
				pos.y = ((int)(MousePos.y + Offset.y) / Positioning) * Positioning;
			}
			else
			{
				pos.y = MousePos.y + Offset.y;
			}
		}
		else if (Mode == 2)//x and y
		{
			MousePos.x -= WinPos.x;
			MousePos.y -= WinPos.y;
			if (Positioning)
			{
				pos.x = ((int)(MousePos.x + Offset.x) / Positioning) * Positioning;
				pos.y = ((int)(MousePos.y + Offset.y) / Positioning) * Positioning;
			}
			else
			{
				pos.x = MousePos.x + Offset.x;
				pos.y = MousePos.y + Offset.y;
			}
		}

	}

}

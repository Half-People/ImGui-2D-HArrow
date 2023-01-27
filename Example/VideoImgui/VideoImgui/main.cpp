
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment(lib,"../API/GLFW/glfw3.lib")
#pragma comment(lib,"../API/GLEW/glew32s.lib")
#pragma comment(lib,"Opengl32.lib")
#include <iostream>
#include <string>


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GUI.h"

GLFWwindow* Windows;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Windows = glfwCreateWindow(900, 800,"HalfPeople-Imgui",NULL,NULL);

	glfwMakeContextCurrent(Windows);
	glfwSwapInterval(0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext(NULL);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("kaiu.ttf", 18, NULL, io.Fonts->GetGlyphRangesChineseFull());
	
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiCol_DockingEmptyBg;
	

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();




	ImGui_ImplGlfw_InitForOpenGL(Windows, true);
	ImGui_ImplOpenGL3_Init("#version 330");


	InitGUI(); // << ----

	while (!glfwWindowShouldClose(Windows))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport();

		DrawGUI(); // << ---

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(Windows);
		glfwPollEvents();
	}
}
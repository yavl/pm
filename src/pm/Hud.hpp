#pragma once

#include "pm.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace pm {
	class Hud {
	public:
		Hud(GLFWwindow* window);
		~Hud();
		void display();
	private:
		bool show_window;
		ImVec4 clear_color;
		ImFont* font;
	};
}
#pragma once

#include "pm.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_opengl3.h"

namespace pm {
	class Hud {
	private:
		bool show_window;
		ImVec4 clear_color;
		ImFont* font;
	public:
		Hud();
		Hud(GLFWwindow* window);
		~Hud();
		void display();
	};
}
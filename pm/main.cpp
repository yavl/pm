#include "pm/pm.hpp"
#include "pm/Texture.hpp"
#include "pm/Shader.hpp"
#include "pm/InputManager.hpp"
#include "HelloWorld.hpp"

using namespace pm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
Main* m;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = glfwCreateWindow(800, 600, "pm::engine", NULL, NULL);
	if (!window) {
		fmt::print("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	m = new Main(window, width, height);
	m->create();

	double lastFrame = 0.0;
	double currentFrame, dt;
	while (!glfwWindowShouldClose(window)) {
		currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		m->render((float) dt);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	delete m;
	m = nullptr;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	m->resize(width, height);
}
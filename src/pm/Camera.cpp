#include "Camera.hpp"
#include "WindowManager.hpp"

using namespace pm;

Camera::Camera(WindowManager* window, int width, int height) {
	this->window = window;
	camSpeed = 500.0f;
	zoomFactor = 0.15f;
	int winWidth = window->getWidth();
	int winHeight = window->getHeight();
	glfwSetScrollCallback(window->getGlfwWindow(), scroll_callback);
	oldState = GLFW_RELEASE;
}

void Camera::update(float dt) {
	// todo cleanup
	auto win = window->getGlfwWindow();
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
		pos.y -= camSpeed * dt * zoom;
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
		pos.x += camSpeed * dt * zoom;
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
		pos.y += camSpeed * dt * zoom;
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
		pos.x -= camSpeed * dt * zoom;

	int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_MIDDLE);
	double xpos, ypos;
	glfwGetCursorPos(win, &xpos, &ypos);
	float mouseX = static_cast<float>(xpos);
	float mouseY = static_cast<float>(ypos);
	if (state == GLFW_PRESS && oldState == GLFW_RELEASE) {
		dragNew = Coord(mouseX, mouseY);
		dragOld = dragNew;
	}
	if (state == GLFW_PRESS) {
		dragNew = Coord(mouseX, mouseY);
		if (dragNew != dragOld) {
			translate((dragOld.x - dragNew.x) * 2, (dragNew.y - dragOld.y) * 2);
			dragOld = dragNew;
		}		
	}
	oldState = state;

	// todo fix projection_matrix
	float winWidth = static_cast<float>(window->getWidth());
	float winHeight = static_cast<float>(window->getHeight());
	projection = glm::ortho(-winWidth, winWidth, -winHeight, winHeight, -1.0f, 1.0f);
	view = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0));
	view = glm::scale(view, glm::vec3(zoom, zoom, 1.f));
}

void Camera::setPosition(float x, float y) {
	pos.x = x;
	pos.y = y;
}

void Camera::translate(float x, float y) {
	pos.x -= x;
	pos.y -= y;
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0)
		zoom += 0.15f * zoom;
	else zoom -= 0.15f * zoom;
}

float Camera::zoom = 1.0f;
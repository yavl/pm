#pragma once

#include "pm.hpp"
#include "Vector2.hpp"
#include <memory>

namespace trew {
	class WindowManager;
	class Camera {
	public:
		Camera(std::shared_ptr<WindowManager> window);
		virtual ~Camera() = default;
		virtual void update(float dt);
		virtual void setPosXY(float x, float y);
		virtual void translate(float x, float y);
		virtual float getX() const;
		virtual float getY() const;
		virtual Vector2 screenToSpace(float x, float y);
        
        glm::mat4 projection;
		glm::mat4 view;
	private:
		virtual void updateProjection(int width, int height);

		std::shared_ptr<WindowManager> window;
		float camSpeed;
		float zoomFactor;
		Vector2 pos;
		Vector2 dragNew, dragOld;
		int oldState;
		float zoom;
	};
}

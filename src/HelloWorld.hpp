#pragma once

#include <memory>

namespace pm {
	class Texture;
	class Shader;
	class Camera;
	class Sprite;
	class InputManager;
	class Hud;
	class WindowManager;
	class AssetManager;
}

using namespace pm;

struct GLFWwindow;

class HelloWorld {
public:
	HelloWorld(WindowManager* window);
	virtual ~HelloWorld();
	void create();
	void render(float dt);
	void resize(int width, int height);
private:
	std::unique_ptr<Camera> cam;
	std::unique_ptr<InputManager> input;
	std::unique_ptr<Sprite> sprite;
	std::unique_ptr<Sprite> sprite2;
	WindowManager* window;
	AssetManager* assets;
};

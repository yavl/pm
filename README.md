# Trewlib
very tiny cross-platform 2D game library (WIP, not ready to use yet)
### Features
* OpenGL 3.3 renderer
* Compiles on Windows, macOS, Linux
* Does nothing except drawing sprites and loading shaders
### Dependencies
GLFW, stb_image, glm, glad, fmt
```c++
#include "pm/Texture.hpp"
#include "pm/Sprite.hpp"
#include "pm/Shader.hpp"
#include "pm/InputManager.hpp"

using namespace pm;

class Main {
private:
    Camera cam;
    InputManager input;
    Texture* tex;
    Texture* tex2;
    Sprite sprite;
    Sprite sprite2;
    GLFWwindow* window;
    Hud hud;
    Shader* sh;
public:
    Main(GLFWwindow* window, int width, int height) {
        this->window = window;
        cam = Camera(window, width, height);
        input = InputManager(window);
    }

    void create() {
        sh = new Shader("default.vert", "default.frag");

        tex = new Texture("tex.png", sh, &cam);
        tex2 = new Texture("tex2.png", sh, &cam);

        sprite = Sprite(tex);
        sprite2 = Sprite(tex2);

        hud = Hud(window);
    }

    void render(float dt) {
        cam.update(dt);
        input.update();
        sprite.draw();
        sprite2.draw();
        hud.display();
    }

    void resize(int width, int height) {
        cam.update_projection_matrix(width, height);
    }

    ~Main() {
        delete tex;
        delete tex2;
        delete sh;
    }
};
```

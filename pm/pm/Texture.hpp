#pragma once

#include "pm.hpp"
#include <SOIL/SOIL.h>
#include "Camera.hpp"
#include "Shader.hpp"

namespace pm {
	class Texture {
	private:
		unsigned char* image;
		int width, height;
		GLuint texture, VAO, VBO, EBO;
		Shader* shader;
		std::string name;
		Camera* cam;
		glm::mat4 matrix;
		float x, y;
	public:
		Texture(const char* path, Shader* shader, Camera* cam);
		~Texture();
		void draw(float x, float y);
		void set_shader(Shader* shader);
	};
}
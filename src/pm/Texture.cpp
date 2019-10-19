#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Logger.hpp"

using namespace pm;

const std::string logTag = "Texture";

Texture::Texture(std::string path) {
	this->name = path;
	this->matrix = glm::mat4(1.f);
	this->x = 0.f;
	this->y = 0.f;
	shader = nullptr;
	cam = nullptr;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	stbi_set_flip_vertically_on_load(true);
	this->image = stbi_load(path.c_str(), &width, &height, 0, STBI_rgb_alpha);
	if (this->image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		log(logTag, fmt::format("<{}> loaded with size: {}x{}", name, width, height));
	}
	else {
		logError(logTag, fmt::format("error loading <{}>", name));
	}
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// todo write and use SpriteBatch instead of below lines
	float widthf = (float)width;
	float heightf = (float)height;

	float vertices[] = {
		 // positions			 // colors           // texture coords
		 widthf,  heightf, 0.f,   1.f, 0.f, 0.f,   1.f, 1.f, // top right
		 widthf, -heightf, 0.f,   0.f, 1.f, 0.f,   1.f, 0.f, // bottom right
		-widthf, -heightf, 0.f,   0.f, 0.f, 1.f,   0.f, 0.f, // bottom left
		-widthf,  heightf, 0.f,   1.f, 1.f, 0.f,   0.f, 1.f  // top left 
	};
	
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

Texture::~Texture() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Texture::draw(float x, float y) {
	// todo draw with spritebatch instead of this
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader->use();
	matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(x, y, 0));
	shader->setUniform("u_projTrans", cam->projection * cam->view * matrix); // todo fix that
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Texture::setShader(Shader* shader) {
	this->shader = shader;
}

void Texture::setCamera(Camera* cam) {
	this->cam = cam;
}
#pragma once

#include <trew/trew.hpp>
#include <trew/Asset.hpp>
#include <trew/Drawable.hpp>
#include <string>

namespace trew {
	class Camera;
	class Shader;
	class Texture : public Asset, public Drawable {
	public:
		Texture(std::string path);
		~Texture();
		virtual void setShader(Shader* shader);
		virtual void setCamera(Camera* cam);

		void draw(float x, float y, float width, float height) override;
		int getImageWidth() const override;
		int getImageHeight() const override;
	private:
		unsigned char* image;
		int texWidth, texHeight;
		GLuint texture, VAO, VBO, EBO;
		Shader* shader;
		std::string name;
		Camera* cam;
		glm::mat4 matrix;
	};
}

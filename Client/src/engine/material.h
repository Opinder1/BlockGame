#pragma once

#include <string>

#include "shader.h"
#include "texture.h"

namespace engine {
	class Material {
	private:
		ShaderProgram program;

		Texture* texture;

	public:
		Material();
		Material(const std::string& name);
		~Material();

		void use();
	};
}
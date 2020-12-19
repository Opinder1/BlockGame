#pragma once

#include <ocode.h>

#include <string>
#include <GL/glew.h>
#include <rapidjson/document.h>

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
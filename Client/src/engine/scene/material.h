#pragma once

#include <ocode.h>

#include <rapidjson/document.h>

#include "../renderer/shader.h"
#include "../renderer/texture.h"

namespace engine {
	class Material : public Program {
	private:
		Texture* texture;

	public:
		Material();
		Material(const std::string& name);
		~Material();

		void use();
	};
}
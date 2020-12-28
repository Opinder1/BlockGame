#pragma once

#include <ocode.h>

#include <vector>
#include <string>

#include "mesh.h"
#include "material.h"
#include "texture.h"

namespace engine {
	class Model {
	private:
		std::vector<Mesh> meshes;

		std::vector<Texture> textures;

		Material* material;

	public:
		Model(const std::string& name, Material* material);
		~Model();

		void draw();
	};
}
#pragma once

#include <ocode.h>

#include <vector>
#include <string>

#include "object.h"
#include "mesh.h"
#include "material.h"

namespace engine {
	class Model : public Object {
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
#include "model.h"

namespace engine {
	Model::Model(const std::string& name, Material* material) : material(material) {

	}

	Model::~Model() {

	}

	void Model::draw() {
		material->use();

		for (auto& mesh : meshes) {
			mesh.draw();
		}
	}
} 
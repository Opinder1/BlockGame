#include "model.h"

namespace engine {
	Model::Model(const std::string& name, Material* material) : mesh(material), material(material) {
		instance_array.format<float, 4, 4, 1>(material->get_attribute("instance_translation"));
	}

	Model::~Model() {

	}

	void Model::draw() {
		material->use();

		mesh.draw((uint32)instance_translations.size());
	}

	uint32 Model::new_instance(const glm::mat4& translation) {
		size_t size = instance_translations.capacity();
		instance_translations.push_back(translation);

		if (instance_translations.capacity() != size) {
			instance_array.data((uint32)instance_translations.capacity(), instance_translations.data(), BufferType::DYNAMIC);
		}
		else {
			instance_array.sub_data((uint32)instance_translations.size() - 1, 1, instance_translations.data());
		}

		instance_pointers.push_back((uint32)instance_translations.size() - 1);
		return (uint32)instance_translations.size() - 1;
	}

	void Model::delete_instance(uint32 index) {
		size_t size = instance_translations.capacity();

		instance_translations.erase(instance_translations.begin() + index);

		instance_array.sub_data(index, (uint32)instance_translations.size() - index, instance_translations.data());
	}

	void Model::update_instance(uint32 index, const glm::mat4& translation) {
		instance_translations.at(index) = translation;

		instance_array.sub_data(index, 1, instance_translations.data());
	}

	uint32 Model::instance_count() {
		return (uint32)instance_translations.size();
	}
} 
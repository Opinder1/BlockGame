#pragma once

#include <ocode.h>

#include <vector>
#include <string>

#include "object.h"
#include "mesh.h"
#include "material.h"

namespace engine {
	class Instance;

	class Model : public Object {
	private:
		Mesh mesh;

		Material* material;

		ArrayBuffer instance_array;
		std::list<uint32> instance_pointers;
		std::vector<glm::mat4> instance_translations;

	public:
		Model(const std::string& name, Material* material);
		~Model();

		void draw();

		uint32 new_instance(const glm::mat4& translation);
		void delete_instance(uint32 index);
		void update_instance(uint32 index, const glm::mat4& translation);
		uint32 instance_count();
	};

	class Instance {
	private:
		uint32 index;
		Model* model;

	public:
		Instance(Model* model, const glm::mat4& translation) : model(model) {
			index = model->new_instance(translation);
		}

		~Instance() {
			model->delete_instance(index);
		}

		void update(const glm::mat4& translation) {
			model->update_instance(index, translation);
		}
	};
}
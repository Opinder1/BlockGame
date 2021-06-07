#include "instance_static.h"

namespace engine {
	InstanceStatic::InstanceStatic() {
		_new();

		instances.reserve(1);
		*instances.data() = Instance{};
		_new_filled();
	}

	InstanceStatic::~InstanceStatic() {
		_delete();
	}

	void InstanceStatic::_new_filled() {
		create<Instance>(instances.capacity(), nullptr, engine::BufferType::Static);
	}

	void InstanceStatic::_resize_filled() {
		create<Instance>(instances.capacity(), instances.data(), engine::BufferType::Static);
	}

	void InstanceStatic::_update_instance(ID id) {
		modify(id, 1, instances.data() + id);
	}

	ID InstanceStatic::new_instance(const Instance& instance) {
		ID id;

		if (deleted.size() > 0) {
			id = deleted.front();
			deleted.pop();

			instances.at(id) = instance;

			_update_instance(id);

			return id;
		}
		else {
			size_t size = instances.capacity();
			instances.push_back(instance);

			id = (ID)instances.size() - 1;

			if (instances.capacity() != size) {
				_resize_filled();
			}
			else {
				_update_instance(id);
			}

		}

		return id;
	}

	void InstanceStatic::modify_instance(ID id, const Instance& instance) {
		instances.at(id) = instance;

		_update_instance(id);
	}

	void InstanceStatic::delete_instance(ID id) {
		instances.at(id) = Instance{};

		_update_instance(id);

		deleted.push(id);
	}

	glm::uint32 InstanceStatic::instance_count() {
		return glm::uint32(instances.size() - deleted.size());
	}
}
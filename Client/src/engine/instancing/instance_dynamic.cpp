#include "instance_dynamic.h"

InstanceDynamic::InstanceDynamic() : count(0) {
	_new();

	instances.reserve(1);
	*instances.data() = Instance{};
	_new_filled();

	_reset_changes();
}

InstanceDynamic::~InstanceDynamic() {
	_delete();
}

void InstanceDynamic::_reset_changes() {
	changes.start = 0;
	changes.end = glm::uint64(0) - 1;
}

void InstanceDynamic::_new_filled() {
	create<Instance>(instances.capacity(), nullptr, engine::BufferType::Dynamic);
}

void InstanceDynamic::_resize_filled() {
	create<Instance>(instances.capacity(), instances.data(), engine::BufferType::Dynamic);
	
	_reset_changes();
}

void InstanceDynamic::_update_instance(glm::uint64 id) {
	if (id < changes.start) changes.start = id;

	if (id + 1 > changes.end) changes.end = id + 1;
}

glm::uint64 InstanceDynamic::new_instance(const Instance& instance) {
	glm::uint64 id;

	count++;

	if (deleted.size() > 0) {
		id = deleted.front();
		deleted.pop();

		instances.at(id) = instance;

		_update_instance(id);
	}
	else {
		size_t size = instances.capacity();
		instances.push_back(instance);

		id = instances.size() - 1;

		if (instances.capacity() != size) {
			_resize_filled();
		}
		else {
			_update_instance(id);
		}
	}

	return id;
}

void InstanceDynamic::modify_instance(glm::uint64 id, const Instance& instance) {
	instances.at(id) = instance;

	_update_instance(id);
}

void InstanceDynamic::delete_instance(glm::uint64 id) {
	count--;

	instances.at(id) = Instance{};

	_update_instance(id);

	deleted.push(id);
}

void InstanceDynamic::checkout_changes() {
	modify(changes.start, changes.end - changes.start, instances.data() + changes.start);

	_reset_changes();
}

glm::uint64 InstanceDynamic::instance_count() {
	return count;
}
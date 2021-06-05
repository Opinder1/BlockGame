#include "instance_stream.h"

InstanceStream::InstanceStream() : count(0) {
	_new();

	instances.reserve(1);
	*instances.data() = Instance{};
	_new_filled();
}

InstanceStream::~InstanceStream() {
	_delete();
}

void InstanceStream::_new_filled() {
	create<Instance>(instances.capacity(), nullptr, engine::BufferType::Stream);
}

void InstanceStream::_resize_filled() {
	create<Instance>(instances.capacity(), instances.data(), engine::BufferType::Stream);
}

void InstanceStream::_update_instance(glm::uint64 id) {

}

glm::uint64 InstanceStream::new_instance(const Instance& instance) {
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

void InstanceStream::modify_instance(glm::uint64 id, const Instance& instance) {
	instances.at(id) = instance;

	_update_instance(id);
}

void InstanceStream::delete_instance(glm::uint64 id) {
	count--;

	instances.at(id) = Instance{};

	_update_instance(id);

	deleted.push(id);
}

void InstanceStream::checkout_changes() {
	modify(0, instances.size(), instances.data());
}

glm::uint64 InstanceStream::instance_count() {
	return count;
}
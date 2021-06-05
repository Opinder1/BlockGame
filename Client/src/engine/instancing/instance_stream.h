#pragma once

#include <queue>
#include <vector>

#include "../renderer/buffer.h"

using Instance = glm::mat4;

class InstanceStream : private engine::ArrayBuffer {
private:
	std::queue<glm::uint64> deleted;
	std::vector<Instance> instances;

	glm::uint64 count;

	void _new_filled();
	void _resize_filled();
	void _update_instance(glm::uint64 id);

public:
	explicit InstanceStream(const InstanceStream&) = default;
	InstanceStream();
	~InstanceStream();

	glm::uint64 new_instance(const Instance& instance);

	void modify_instance(glm::uint64 id, const Instance& instance);

	void delete_instance(glm::uint64 id);

	void checkout_changes();

	glm::uint64 instance_count();
};
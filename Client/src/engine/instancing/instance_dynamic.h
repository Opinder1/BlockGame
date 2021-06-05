#pragma once

#include <queue>
#include <vector>

#include "../renderer/buffer.h"

using Instance = glm::mat4;

class InstanceDynamic : private engine::ArrayBuffer {
private:
	std::queue<glm::uint64> deleted;
	std::vector<Instance> instances;

	glm::uint64 count;

	struct {
		glm::uint64 start;
		glm::uint64 end;
	} changes;

	void _reset_changes();

	void _new_filled();
	void _resize_filled();
	void _update_instance(glm::uint64 id);

public:
	explicit InstanceDynamic(const InstanceDynamic&) = default;
	InstanceDynamic();
	~InstanceDynamic();

	glm::uint64 new_instance(const Instance& instance);

	void modify_instance(glm::uint64 id, const Instance& instance);

	void delete_instance(glm::uint64 id);

	void checkout_changes();

	glm::uint64 instance_count();
};
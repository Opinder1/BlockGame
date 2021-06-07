#pragma once

#include <queue>
#include <vector>

#include "../gl/buffer.h"

namespace engine {
	using ID = glm::uint32;
	using Instance = glm::mat4;

	class InstanceDynamic : private engine::ArrayBuffer {
	private:
		std::queue<ID> deleted;
		std::vector<Instance> instances;

		struct {
			glm::uint32 start;
			glm::uint32 end;
		} changes;

		void _reset_changes();

		void _new_filled();
		void _resize_filled();
		void _update_instance(ID id);

	public:
		explicit InstanceDynamic(const InstanceDynamic&) = default;
		InstanceDynamic();
		~InstanceDynamic();

		ID new_instance(const Instance& instance);

		void modify_instance(ID id, const Instance& instance);

		void delete_instance(ID id);

		void checkout_changes();

		glm::uint32 instance_count();
	};
}
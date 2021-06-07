#pragma once

#include <queue>
#include <vector>

#include "../gl/buffer.h"

namespace engine {
	using ID = glm::uint32;
	using Instance = glm::mat4;

	class InstanceStream : private engine::ArrayBuffer {
	private:
		std::queue<ID> deleted;
		std::vector<Instance> instances;

		void _new_filled();
		void _resize_filled();
		void _update_instance(ID id);

	public:
		explicit InstanceStream(const InstanceStream&) = default;
		InstanceStream();
		~InstanceStream();

		ID new_instance(const Instance& instance);

		void modify_instance(ID id, const Instance& instance);

		void delete_instance(ID id);

		void checkout_changes();
		void checkout_changes_range(glm::uint32 start, glm::uint32 end);

		glm::uint32 instance_count();
	};
}
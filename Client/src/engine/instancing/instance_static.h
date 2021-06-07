#pragma once

#include <queue>
#include <vector>

#include "../gl/buffer.h"

namespace engine {
	using ID = glm::uint32;
	using Instance = glm::mat4;

	// TODO Decide if these buffers are needed and if so which ones
	// TODO They should probably be templated as instances may not be mat4

	class InstanceStatic : private engine::ArrayBuffer {
	private:
		std::queue<ID> deleted;
		std::vector<Instance> instances;

		void _new_filled();
		void _resize_filled();
		void _update_instance(ID id);

	public:
		explicit InstanceStatic(const InstanceStatic&) = default;
		InstanceStatic();
		~InstanceStatic();

		ID new_instance(const Instance& instance);

		void modify_instance(ID id, const Instance& instance);

		void delete_instance(ID id);

		glm::uint32 instance_count();
	};
}
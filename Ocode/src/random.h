#pragma once

#include <GLM/glm.hpp>

#include <string>
#include <chrono>

namespace ocode {
	struct UUID {
		glm::uint16 data[8];

		std::string to_string();
	};

	class Random {
	private:
		glm::uint64 seed;

	public:
		Random(const Random&) = delete;
		Random();

		template<class Type>
		Type get() {
			seed = 6364136223846793005 * seed + 1;
			return (Type)seed;
		}

		UUID new_uuid();
	};
}
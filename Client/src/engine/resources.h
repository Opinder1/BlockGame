#pragma once

#include <ocode.h>

namespace engine {
	struct resource_exception : ocode::file_exception {};

	class ResourceManager {
		using Resources = std::unordered_map<std::string, const ocode::File>;

	private:
		Resources resources;

	public:
		using iterator = Resources::iterator;

		ResourceManager() {}
		~ResourceManager();

		void load_folder(const fs::path& resource_pack_name);
		void load_archive(const fs::path& resource_pack_name);

		void flush();

		iterator begin();
		iterator end();

		const ocode::File& operator[](const std::string& resource_name) const;

		ocode::File copy_resource(const std::string& resource_name);
	};
}
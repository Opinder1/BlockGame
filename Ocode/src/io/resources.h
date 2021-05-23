#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>

#include "file.h"

namespace ocode {
	struct resource_exception : file_exception {};

	class ResourceManager {
		using Resources = std::unordered_map<std::string, const File>;

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

		const File& operator[](const std::string& resource_name) const;

		File copy_resource(const std::string& resource_name);
	};
}
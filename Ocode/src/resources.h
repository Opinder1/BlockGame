#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>

namespace ocode {
	namespace fs = std::filesystem;

	struct resource_exception {
		std::string resource;
		std::string message;
	};

	struct resource_load_exception : resource_exception {};

	struct File {
		size_t size;
		void* data;
	};

	struct Resource {
		std::string path;
		File file;
	};

	class ResourceManager {
		using Resources = std::unordered_map<std::string, const Resource>;

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

		const Resource get_resource(const std::string& resource_name);

		const Resource& operator[](const std::string& resource_name);
	};
}
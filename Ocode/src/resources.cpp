#include "resources.h"

namespace ocode {
	File resource_from_file(fs::directory_entry path) {
		size_t file_size = path.file_size();

		char* buffer = new char[file_size];

		if (buffer == NULL) throw resource_load_exception{ path.path().u8string(), "Could not allocate memory for resource file" };

		std::ifstream file(path, std::ios::binary);

		file.read(buffer, file_size);

		if (!file) throw resource_load_exception{ path.path().u8string(), "Error while reading resource file" };

		return { file_size, buffer };
	}

	ResourceManager::~ResourceManager() {
		flush();
	}

	void ResourceManager::load_folder(const fs::path& resource_pack_name) {
		const fs::path resources_folder = resource_pack_name / "resources";

		if (!fs::directory_entry(resources_folder).is_directory())
			throw resource_load_exception{ resources_folder.u8string(), "The resource folder does not exist" };

		for (auto& path : fs::recursive_directory_iterator(resources_folder)) {
			if (!path.is_directory()) {
				const fs::path resource_path = path.path().lexically_relative(resources_folder);

				std::string name = resource_path.u8string();

				if (resources.find(name) == resources.end()) {
					resources.emplace(name, Resource{ resource_path.parent_path().u8string(), resource_from_file(path) });
				}
			}
		}
	}

	void ResourceManager::flush() {
		for (auto& resource : resources) {
			delete resource.second.file.data;
		}

		resources.clear();
	}

	ResourceManager::iterator ResourceManager::begin() {
		return resources.begin();
	}

	ResourceManager::iterator ResourceManager::end() {
		return resources.end();
	}

	const Resource ResourceManager::get_resource(const std::string& resource_name) {
		auto resource = resources.find(resource_name);

		if (resource == resources.end()) throw resource_exception{ resource_name, "Could not find resource" };

		return resource->second;
	}

	const Resource& ResourceManager::operator[](const std::string& resource_name) {
		return resources[resource_name];
	}
}
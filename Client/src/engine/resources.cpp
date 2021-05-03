#include "resources.h"

namespace engine {
	Resource resource_from_file(std::filesystem::directory_entry entry) {
		size_t file_size = entry.file_size();

		char* buffer = new char[file_size];

		if (buffer == NULL)
			throw resource_load_exception({ "Could not allocate memory for resource file '" + entry.path().string() + "'" });

		std::ifstream file(entry, std::ios::binary);

		file.read(buffer, file_size);

		if (!file)
			throw resource_load_exception({ "Error while reading resource file '" + entry.path().string() + "'" });

		return { file_size, buffer };
	}

	ResourceManager::~ResourceManager() {
		for (auto& resource : resources) {
			delete resource.second.data;
		}
	}

	void ResourceManager::load_folder(const std::string& folder_name) {
		std::filesystem::directory_entry root_path = std::filesystem::directory_entry(folder_name);

		if (!root_path.is_directory())
			throw resource_load_exception{ "The resource folder '" + folder_name + "' does not exist" };

		for (auto& path : std::filesystem::recursive_directory_iterator(folder_name)) {
			if (!path.is_directory()) {
				std::string path_name = path.path().string();

				std::string resource_name(path_name.begin() + folder_name.size(), path_name.end());

				if (resources.find(resource_name) == resources.end()) {
					resources.insert({ resource_name, resource_from_file(path) });
				}
			}
		}
	}

	Resource ResourceManager::get_resource(const std::string& resource_name) {
		auto resource = resources.find(resource_name);

		if (resource != resources.end())
			throw resource_exception{};

		return resource->second;
	}

	ResourceManager::iterator ResourceManager::begin() {
		return resources.begin();
	}

	ResourceManager::iterator ResourceManager::end() {
		return resources.end();
	}

	void ResourceManager::flush() {
		for (auto& resource : resources) {
			delete resource.second.data;
		}

		resources.clear();
	}
}
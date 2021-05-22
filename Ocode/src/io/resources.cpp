#include "resources.h"

namespace ocode {
	ResourceManager::~ResourceManager() {
		flush();
	}

	void ResourceManager::load_folder(const fs::path& resource_pack_name) {
		const fs::path resources_folder = resource_pack_name / "resources";

		if (!fs::directory_entry(resources_folder).is_directory()) throw file_exception{ "The resource folder does not exist" };

		for (auto& path : fs::recursive_directory_iterator(resources_folder)) {
			if (!path.is_directory()) {
				const fs::path resource_path = path.path().lexically_relative(resources_folder);

				std::string name = resource_path.u8string();

				if (resources.find(name) == resources.end())
					resources.emplace(name, Resource{ resource_path.parent_path().u8string(), load_file(path) });
			}
		}
	}

	void ResourceManager::flush() {
		for (auto& resource : resources)
			delete resource.second.file.data;

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

		if (resource == resources.end()) throw resource_exception{ "Could not find resource" };

		return resource->second;
	}

	const Resource& ResourceManager::operator[](const std::string& resource_name) {
		return resources[resource_name];
	}
}
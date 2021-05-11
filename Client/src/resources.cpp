#include "resources.h"

Resource resource_from_file(fs::directory_entry path) {
	size_t file_size = path.file_size();

	char* buffer = new char[file_size];

	if (buffer == NULL)
		throw resource_load_exception({ "Could not allocate memory for resource file '" + path.path().u8string() + "'" });

	std::ifstream file(path, std::ios::binary);

	file.read(buffer, file_size);

	if (!file)
		throw resource_load_exception({ "Error while reading resource file '" + path.path().u8string() + "'" });

	return { file_size, buffer };
}

ResourceManager::~ResourceManager() {
	for (auto& resource : resources) {
		delete resource.second.data;
	}
}

void ResourceManager::load_folder(const fs::path& resource_pack_name) {
	const fs::path resources_folder = resource_pack_name / "resources";

	if (!fs::directory_entry(resources_folder).is_directory())
		throw resource_load_exception{ "The resource folder '" + resources_folder.u8string() + "' does not exist" };

	for (auto& path : fs::recursive_directory_iterator(resources_folder)) {
		if (!path.is_directory()) {
			const fs::path resource_path = path.path().lexically_relative(resources_folder);

			ResourceID resource_name = resource_path.u8string();

			if (resources.find(resource_name) == resources.end()) {
				resources.insert({ resource_name, resource_from_file(path) });
			}
		}
	}
}

Resource ResourceManager::get_resource(const ResourceID& resource_name) {
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
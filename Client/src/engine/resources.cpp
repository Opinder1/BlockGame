#include "resources.h"

namespace engine {
	ResourceManager::~ResourceManager() {
		flush();
	}

	void ResourceManager::load_folder(const fs::path& resource_pack_name) {
		const fs::path& resources_folder = resource_pack_name / L"resources"s;

		if (!fs::is_directory(resources_folder)) throw ocode::file_exception{ "The resource folder does not exist: "s };

		for (const fs::directory_entry& entry : fs::recursive_directory_iterator(resources_folder)) {
			if (!entry.is_directory()) {
				const fs::path& path = entry.path();

				const std::string& name = path.lexically_relative(resources_folder).u8string();

				if (resources.find(name) == resources.end()) resources.emplace(name, ocode::load_file(path.u8string()));
			}
		}
	}

	void ResourceManager::load_archive(const fs::path& resource_pack_name) {
		if (!fs::exists(resource_pack_name)) throw ocode::file_exception{ "The zip file does not exist"s };

		lz::ZipArchive zip(resource_pack_name.u8string());

		zip.open();

		if (!zip.isOpen()) throw ocode::file_exception{ "Could not open zip file"s };

		if (!zip.getEntry("resources/"s).isDirectory()) throw ocode::file_exception{ "ZIP file missing resources folder"s };

		for (const lz::ZipEntry entry : zip.getEntries()) {
			if (entry.isFile()) {
				const std::string& name = fs::path(entry.getName()).lexically_relative(L"resources"s).string();

				if (resources.find(name) == resources.end()) resources.emplace(name, entry.readAsText());
			}
		}

		zip.close();
	}

	void ResourceManager::flush() {
		resources.clear();
	}

	ResourceManager::iterator ResourceManager::begin() {
		return resources.begin();
	}

	ResourceManager::iterator ResourceManager::end() {
		return resources.end();
	}

	const ocode::File& ResourceManager::operator[](const std::string& resource_name) const {
		auto resource = resources.find(resource_name);

		if (resource == resources.end()) throw resource_exception{ "Could not find resource "s + resource_name };

		return resource->second;
	}

	ocode::File ResourceManager::copy_resource(const std::string& resource_name) {
		return operator[](resource_name);
	}
}
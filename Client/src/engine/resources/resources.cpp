#include "resources.h"

namespace engine {
	ResourceManager::~ResourceManager() {
		flush();
	}

	void ResourceManager::load_folder(const fs::path& resource_pack_name) {
		const fs::path& resources_folder = resource_pack_name / L"resources"s;

		if (!fs::is_directory(resources_folder)) throw resource_exception{ "Resource pack does not have resources folder: "sv, resource_pack_name.u8string() };

		for (const fs::directory_entry& entry : fs::recursive_directory_iterator(resources_folder)) {
			if (!entry.is_directory()) {
				const fs::path& path = entry.path();

				const std::string& name = path.lexically_relative(resources_folder).u8string();

				if (resources.find(name) == resources.end()) {
					try {
						resources.emplace(name, ocode::load_file(path.u8string()));
					}
					catch (ocode::file_exception& e) {

					}
				}
			}
		}
	}

	void ResourceManager::load_archive(const fs::path& resource_pack_name) {
		if (!fs::exists(resource_pack_name)) throw resource_exception{ "The zip file does not exist"sv, resource_pack_name.u8string() };

		lz::ZipArchive zip(resource_pack_name.u8string());

		zip.open();

		if (!zip.isOpen()) throw resource_exception{ "Could not open zip file"sv, resource_pack_name.u8string() };

		if (!zip.getEntry("resources/"s).isDirectory()) throw resource_exception{ "ZIP file missing resources folder"sv, resource_pack_name.u8string() };

		for (const lz::ZipEntry entry : zip.getEntries()) {
			if (entry.isFile()) {
				const std::string& name = fs::path(entry.getName()).lexically_relative(L"resources"sv).string();

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
		const_iterator resource = resources.find(resource_name);

		if (resource == resources.end()) throw resource_exception{ "Could not find resource "sv, resource_name };

		return resource->second;
	}

	ocode::File ResourceManager::copy_resource(const std::string& resource_name) {
		return operator[](resource_name);
	}
}
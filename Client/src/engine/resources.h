#include <ocode.h>

#include <string>
#include <unordered_map>

#include <fstream>
#include <filesystem>

namespace engine {
	struct resource_load_exception {
		std::string message;
	};

	struct resource_exception {};

	struct Resource {
		size_t data_size;
		void* data;
	};

	class ResourceManager {
	private:
		std::unordered_map<std::string, Resource> resources;

	public:
		using iterator = std::unordered_map<std::string, Resource>::iterator;

		ResourceManager() {}
		~ResourceManager();

		void load_folder(const std::string& folder_name);
		void load_archive(const std::string& archive_name);

		Resource get_resource(const std::string& resource_name);

		void flush();

		iterator begin();
		iterator end();
	};
}
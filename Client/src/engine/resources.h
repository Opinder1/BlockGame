#include <ocode.h>

#include <string>
#include <unordered_map>

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

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
		using storage = std::unordered_map<std::string, Resource>;

	private:
		storage resources;

	public:
		using iterator = storage::iterator;

		ResourceManager() {}
		~ResourceManager();

		void load_folder(const std::string& resource_pack_name);
		void load_archive(const std::string& resource_pack_name);

		Resource get_resource(const std::string& resource_name);

		void flush();

		iterator begin();
		iterator end();
	};
}
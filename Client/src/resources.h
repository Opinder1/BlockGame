#include <blockgame.h>

struct resource_load_exception {
	std::string message;
};

struct resource_exception {};

using ResourceID = std::string;

struct Resource {
	size_t data_size;
	void* data;
};

class ResourceManager {
	using Resources = std::unordered_map<ResourceID, Resource>;

private:
	Resources resources;

public:
	using iterator = Resources::iterator;

	ResourceManager() {}
	~ResourceManager();

	void load_folder(const fs::path& resource_pack_name);
	void load_archive(const fs::path& resource_pack_name);

	// Probably not used at all
	Resource get_resource(const ResourceID& resource_name);

	void flush();

	iterator begin();
	iterator end();
};
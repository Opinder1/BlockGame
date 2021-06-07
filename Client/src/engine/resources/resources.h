#pragma once

#include <ocode.h>

#include "../gl/shader.h"
#include "../gl/texture.h"

namespace engine {
	struct resource_exception : ocode::file_exception {};

	struct program_exception {
		std::string_view message;
		std::string name;
		std::string log;
	};

	struct texture_exception {
		std::string_view message;
		std::string name;
	};

	class ResourceManager {
		using Resources = std::unordered_map<std::string, const ocode::File>;

	private:
		Resources resources;

	public:
		using iterator = Resources::iterator;
		using const_iterator = Resources::const_iterator;

		ResourceManager() {}
		~ResourceManager();

		void load_folder(const fs::path& resource_pack_name);
		void load_archive(const fs::path& resource_pack_name);

		void flush();

		iterator begin();
		iterator end();

		const ocode::File& operator[](const std::string& resource_name) const;

		ocode::File copy_resource(const std::string& resource_name);
	};

	ocode::File read_shader_file(const fs::path& path, const ResourceManager& resources, std::vector<std::string>& visited);
	Program load_program(const std::string& name, const ResourceManager& resources);
	Texture load_texture(const std::string& name, const ResourceManager& resources);
	//Model load_model(const std::string& name, const ResourceManager& resources); 
	//Sound load_sound(const std::string& name, const ResourceManager& resources);
}
#include "resources.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace engine {
	class STBI {
	public:
		STBI() {
			stbi_set_flip_vertically_on_load(true);
		}

		static glm::uint8* load_file(const ocode::File& file, const glm::uvec2& size, glm::uint32& n) {
			return stbi_load_from_memory((stbi_uc*)file.data(), int(file.size()), (int*)&size.x, (int*)&size.y, (int*)&n, 0);
		}

	} startup;

	TextureFormat get_format(glm::uint32 components) {
		switch (components) {
		case 1: return TextureFormat::R;
		case 2: return TextureFormat::RG;
		case 3: return TextureFormat::RGB;
		case 4: return TextureFormat::RGBA;
		default: return TextureFormat::DEPTH_AND_STENCIL;
		}
	}

	Texture load_texture(const std::string& name, const ResourceManager& resources) {
		try {
			const ocode::File& resource = resources[name];

			glm::uvec2 size;
			glm::uint32 file_components;
			glm::uint8* data = STBI::load_file(resource, size, file_components);

			if (data == nullptr) {
				delete data;
				throw texture_exception{ "Could parse image file"sv, name };
			}

			TextureFormat format = get_format(file_components);

			if (format == TextureFormat::DEPTH_AND_STENCIL) {
				delete data;
				throw texture_exception{ "Invalid pixel component count", name };
			}

			return new _Texture(data, size, format);
		}
		catch (ocode::file_exception& e) {
			throw texture_exception{ "Error reading texture file"sv, e.name };
		}
	}
}
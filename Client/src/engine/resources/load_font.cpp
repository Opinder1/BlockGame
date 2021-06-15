#include "resources.h"

#include "../opengl/opengl.h"

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace engine {
	class FreeType {
	public:
		FT_Library ft;

		FreeType() {
			if (FT_Init_FreeType(&ft)) throw "Error loading freetype";
		}

		~FreeType() {
			FT_Done_FreeType(ft);
		}

	} startup;

	Font load_font(const std::string& name, const ResourceManager& resources) {
		try {
			const ocode::File& resource = resources[name];

            // TODO Put this into the FreeType class thing
            FT_Face face;
            if (FT_New_Memory_Face(startup.ft, (const FT_Byte*)resource.data(), FT_Long(resource.size()), 0, &face)) throw "Failed to load font";

            // TODO Find some way of choosing font size or just load fonts at some massive size
            if (FT_Set_Pixel_Sizes(face, 0, 32)) throw "Failed to set font size";

            // Allow 1 pixel value per byte instead of alligned at every 4 bytes. This is because opengl likes to be able to support all formats up to rgba
            // TODO Generalize this function somewhere like in Texture class
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            std::vector<Character> characters;

            for (GLubyte character = 0; character < 128; character++)
            {
                // TODO Not sure if loading like this or loading glyphs is better
                // TODO also can i only load chars or can i do wchars?
                if (FT_Load_Char(face, character, FT_LOAD_RENDER)) throw "Failed to load Glyph";

                engine::Texture2D texture;

                texture._new();

                texture.set_filter(engine::TextureFilter::Linear, engine::TextureFilter::Linear);
                texture.set_wrap(engine::TextureWrap::Clamp, engine::TextureWrap::Clamp);

                engine::_Texture texture_data(face->glyph->bitmap.buffer, glm::uvec2{ face->glyph->bitmap.width, face->glyph->bitmap.rows }, engine::TextureFormat::R);
                texture.set_data(&texture_data);

                // TODO :( why like this? just make a texture atlas...
                characters.push_back(Character{
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    face->glyph->advance.x
                });
            }

            FT_Done_Face(face);
			return new _Font(characters);
		}
		catch (ocode::file_exception& e) {
			throw font_exception{ "Error reading font file"sv, e.name };
		}
	}
}

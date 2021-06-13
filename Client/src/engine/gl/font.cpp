#include "font.h"

namespace engine {
    _Font::_Font(std::vector<Character>& characters) : characters(std::move(characters)) {
        array._new();
        buffer._new();
        buffer.create<glm::vec4>(6, nullptr, engine::BufferType::Dynamic);
        array.set_attribute(0, buffer, engine::Type::float32, 4);
    }

    _Font::~_Font() {
        array._delete();
        buffer._delete();

        for (auto& character : characters) {
            character.texture._delete();
        }
    }

    void _Font::set_shader(Program shader) {
        this->shader = shader;
    }

    Program _Font::get_shader() {
        return shader;
    }

    void _Font::render(const std::string& text, glm::vec2 pos, float scale, const glm::vec3& color) {
        shader.use();
        shader.set<glm::vec3>("textColor", color);

        for (auto c : text)
        {
            // TODO character must be between 0 and 127 (could cause error)
            Character& ch = characters[c];

            float xpos = pos.x + ch.bearing.x * scale;
            float ypos = pos.y + (characters['H'].bearing.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
            // update VBO for each character
            glm::vec4 vertices[6] = {
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos,     ypos,       0.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f }
            };
            // render glyph texture over quad
            ch.texture.use(0);
            // update content of VBO memory
            buffer.modify(0, 6, vertices);
            // render quad
            array.draw(engine::DrawType::Triangles, 6);
            // now advance cursors for next glyph
            pos.x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
        }
    }
}
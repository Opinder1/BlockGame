#include "texture.h"

Texture::Texture(const char* file_name) : program("resources\\texture.shader") {
	if (program.link_status() == GL_FALSE) {
		printf("ProgramError:\n%s\n", program.get_log().c_str());
	}
}

Texture::~Texture() {

}

void Texture::use() {
	program.use();
}
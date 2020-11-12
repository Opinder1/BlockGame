#pragma once

#include "shader.h"

class Texture {
private:
	ShaderProgram program;
	
public:
	Texture(const char* file_name);
	~Texture();

	void use();
};
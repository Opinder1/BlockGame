#version 450 core

precision highp float;

uniform vec2 pos;
uniform vec2 scale;
uniform float rot;

in vec2 vertexpos;

out vec2 texcoord;

mat2 get_rotation(float rotation) {
	return mat2(cos(rotation), -sin(rotation), sin(rotation), cos(rotation));
}

void main() {
    gl_Position = vec4(((vertexpos - 0.5) * get_rotation(rot) * scale) + pos, 0.0, 1.0);
	texcoord = vertexpos;
}
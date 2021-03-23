#version 450 core

precision highp float;

uniform vec2 pos = vec2(0, 0);
uniform vec2 scale = vec2(1, 1);
uniform float rot = 0;

uniform uvec2 surface_size;
uniform uvec2 texture_size;

uniform bool center = false;

in vec2 vertexpos;

out vec2 texture_coord;

mat2 get_rotation(float rotation) {
	return mat2(cos(rotation), -sin(rotation), sin(rotation), cos(rotation));
}

void main() {
    if (center) {
		//Use center of screen as (0, 0). Use center of texture and rotate around center
		vec2 pixel_coord = ((vertexpos - 0.5) * texture_size * get_rotation(-rot) * scale) + pos;
		gl_Position = vec4((pixel_coord * 2) / surface_size, 0, 1);
	} else {
		//Use bottom left of screen as (0, 0). Use corner of texture and rotate around corner
		vec2 pixel_coord = (vertexpos * texture_size * get_rotation(-rot) * scale) + pos;
		gl_Position = vec4((pixel_coord * 2) / surface_size - 1, 0, 1);
	}

	texture_coord = vertexpos * texture_size;
}
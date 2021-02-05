#version 450 core

layout (std140, binding = 0) uniform Camera {
    mat4 camera;
};

uniform mat4 transform;

in vec3 vertex_position;
in vec3 normal_direction;
in vec3 texture_coordinate;

out vec3 color;

vec3 hash( vec3 p ){
	p = vec3( dot(p,vec3(127.1,311.7, 74.7)),
			  dot(p,vec3(269.5,183.3,246.1)),
			  dot(p,vec3(113.5,271.9,124.6)));

	return fract(sin(p)*43758.5453123);
}

void main() {
    gl_Position = camera * transform * vec4(vertex_position, 1.0f);
	
	vec3 c = vec3(transform[0][0], transform[1][1], transform[2][2]) / 5.0f;
	
	color = hash(c);
}
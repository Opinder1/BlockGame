#version 450 core

layout (std140) uniform Camera {
    mat4 camera;
};

in vec3 vertex_position;
in vec3 normal_direction;
in vec3 texture_coordinate;
in mat4 instance_translation;

out vec3 color;

float rand(float co) {
    return fract(sin(dot(vec2(co) ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    gl_Position = camera * instance_translation * vec4(vertex_position, 1.0f);
	color = vec3(rand(gl_InstanceID % 10000), rand(gl_InstanceID % 10000 + 1), rand(gl_InstanceID % 10000 + 2));
}
#version 450 core

precision highp float;

uniform sampler2D sampler;

in vec2 texture_coord;

out vec4 frag_color;

void main() {
    frag_color = texelFetch(sampler, ivec2(texture_coord), 0);
}
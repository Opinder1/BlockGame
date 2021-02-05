#version 450 core

precision highp float;

uniform sampler2D sampler;

in vec2 texcoord;

out vec4 frag_color;

void main() {
    frag_color = texture(sampler, texcoord);
}
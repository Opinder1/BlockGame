#version 450 core

precision highp float;

uniform sampler2DMS sampler;
uniform uvec2 size;
uniform uint samples;

in vec2 texcoord;

out vec4 frag_color;

void main() {   
    vec4 color = vec4(0);

    for (int i = 0; i < samples; i++) {
		ivec2 coord = ivec2(texcoord * size);
        color += texelFetch(sampler, coord, i);
	}

    color /= float(samples);

	frag_color = color;
}
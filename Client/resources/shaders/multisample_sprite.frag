#version 450 core

precision highp float;

uniform sampler2DMS texture_data;
uniform uint texture_samples;

in vec2 texture_coord;

out vec4 frag_color;

void main() {   
    vec4 color = vec4(0);

    for (int i = 0; i < texture_samples; i++) {
        color += texelFetch(texture_data, ivec2(texture_coord), i);
	}

    color /= float(texture_samples);

	frag_color = color;
}
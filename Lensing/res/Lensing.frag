#version 430 core

in vec2 uv;

uniform float width;
uniform float height;
uniform sampler2D tex;

layout(std430, binding = 2) buffer Normal_Map
{
	float frame[];
};

void main()
{
	ivec2 pos = ivec2((width - 1) * uv.x, (1 - uv.y) * (height - 1));
	int pixelOffset = pos.y * int(width) + pos.x;
	int dim = int(width * height);
	vec4 pix = vec4( frame[pixelOffset], frame[pixelOffset + dim], frame[pixelOffset + 2 * dim], 1);
	
	gl_FragColor = pix;
//	gl_FragColor = texture(tex, uv);
}
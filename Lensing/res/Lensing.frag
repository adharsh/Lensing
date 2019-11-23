#version 430 core

in vec2 uv;

uniform float width;
uniform float height;
uniform sampler2D texture1;

layout(std430, binding = 2) buffer Normal_Map
{
	float frame[];
};

void main()
{
	vec2 pos = vec2((width - 1) * uv.x, (1 - uv.y) * (height - 1));
//	pos += 0.5f;
	int pixelOffset = int((pos.y * width + pos.x) * 3);
	vec4 pix = vec4( frame[pixelOffset], frame[pixelOffset + 1], frame[pixelOffset + 2], 1);
	
	gl_FragColor = pix;
//	gl_FragColor = (texture(texture1, uv) + pix)/2;
//	gl_FragColor = vec4(uv, 0, 1);
//	gl_FragColor = vec4(normalize(pos), 0, 1);
}
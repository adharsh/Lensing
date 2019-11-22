#version 330 core

in vec2 uv;

uniform sampler2D texture1;

void main()
{
	//gl_FragColor = texture(texture1, uv);
	gl_FragColor = vec4(0, 1, 1, 1);
}
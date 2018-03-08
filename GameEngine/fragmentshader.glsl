#version 430

out vec4 Fcolor;
in vec2 uv;

uniform sampler2D Texture;

void main()
{
Fcolor = texture(Texture,uv);

};

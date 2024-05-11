#version 330 core

layout(location = 0) out vec4 colour;

in vec2 v_Uv;

void main()
{
	colour = texture(Sp_ActiveTexture, v_Uv);
}
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 uv;

out vec2 v_Uv;

void main()
{
	gl_Position = Sp_MVP * position;
	v_Uv = uv;
};
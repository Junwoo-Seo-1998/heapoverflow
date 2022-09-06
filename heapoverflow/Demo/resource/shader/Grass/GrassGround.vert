#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

out vec3 v_Position;

void main()
{
	v_Position=in_Position;
}
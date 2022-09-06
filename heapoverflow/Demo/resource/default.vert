#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;
out float color_factor;

void main()
{
	//v_Color=in_Color;
	vec3 light=vec3(0,0,1);

	color_factor=clamp(dot(light,in_Normal),0,1);
	v_Color=vec4(in_Normal,1);
	gl_Position=u_ViewProjection*u_Transform*vec4(in_Position,1.0);
}
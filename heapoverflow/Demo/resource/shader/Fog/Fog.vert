#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;
out vec4 v_Position;
out float color_factor;

void main()
{
	//v_Color=in_Color;
	vec3 light=vec3(0,0,1);

	color_factor=clamp(dot(light,in_Normal),0,1);
	v_Color=color_factor*vec4(0.7255, 0.7216, 0.4275, 1.0);
	gl_Position=u_ViewProjection*u_Transform*vec4(in_Position,1.0);
	v_Position=gl_Position;
}
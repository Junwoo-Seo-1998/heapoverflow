#version 330 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform mat4 u_LightProjection;

out vec3 vPosition;
out vec3 vNormal;
out vec4 vLightSpacePosition;

void main()
{
    vPosition=(u_Transform*vec4(in_Position,1.0)).xyz;
    vNormal=transpose(inverse(mat3(u_Transform)))*vec4(in_Normal,1).xyz;
	gl_Position=u_ViewProjection*u_Transform*vec4(in_Position,1.0);
    vLightSpacePosition=u_LightProjection*vec4(vPosition,1.0);
}
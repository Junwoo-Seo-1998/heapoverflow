#version 450 core

in vec4 point_color;
out vec4 color;

void main()
{
	//vec3 rgb_col=in_color.xyz;

	//color=vec4(rgb_col,1.f);
	color=point_color;
}
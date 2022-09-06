#version 330 core

in vec4 v_Position;
in vec4 v_Color;

in float color_factor;

uniform float fog_max_dist=200;
uniform float fog_min_dist=1;

uniform vec3 fog_color=vec3(0.796875, 0.796875, 0.796875);

out vec4 color;


void main()
{
	float dist=length(v_Position.xyz);
    float fogFactor=(fog_max_dist-dist)/(fog_max_dist-fog_min_dist);

	fogFactor=clamp(fogFactor,0.0, 1.0);
    vec3 shadeColor=v_Color.xyz;
    vec3 total_color=mix(fog_color,shadeColor,fogFactor);
	
	color=vec4(total_color,1.0);
}
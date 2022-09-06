#version 330 core

in vec3 vPosition;
in vec3 vNormal;
in vec4 vLightSpacePosition;

out vec4 FragColor;

uniform sampler2D ShadowMap;
uniform vec3 u_LightPosition;
uniform float u_BiasMax=0.05;
uniform float u_BiasMin=0.005;


float bias=0.05;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    float shadow=texture(ShadowMap,projCoords.xy).r;
    float currentDepth=projCoords.z;
    shadow=currentDepth-bias>shadow ? 1.0:0.0;

    if(projCoords.z >= 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    vec3 color=vec3(0.9255, 0.8235, 0.2314);
    vec3 ambient = 0.3 * color;
    vec3  N       = normalize(vNormal);
    vec3  L       = normalize(u_LightPosition - vPosition);
    float NDotL   = max(dot(N, L), 0.0);
    float  diffuse = NDotL;
    bias = max(u_BiasMax * (1.0 - dot(vNormal, L)), u_BiasMin);
    float shadow=ShadowCalculation(vLightSpacePosition);

    FragColor=vec4(vec3(ambient+(1-shadow)*diffuse*color),1.0);
    FragColor=pow(FragColor, vec4(1. / 2.2));
 
}

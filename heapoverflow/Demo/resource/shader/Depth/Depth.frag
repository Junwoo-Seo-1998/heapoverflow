#version 460

out vec4 FragColor;

in vec2 vTextureCoord;

uniform sampler2D ShadowMap;
uniform float     MinVisibleDepth = 0.0001f;

void main()
{
    float depth    = texture(ShadowMap, vTextureCoord).r;
    float rescaled = (depth - MinVisibleDepth) / (1.0 - MinVisibleDepth);
    rescaled       = clamp(rescaled, 0.0, 1.0);
    FragColor      = vec4(vec3(rescaled), 1.0);
}

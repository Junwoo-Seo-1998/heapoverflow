#version 460

layout(location = 0) in vec4 Position;
layout(location = 1) in vec2 TextureCoord;

out vec2 vTextureCoord;

void main()
{
    gl_Position   = Position;
    vTextureCoord = TextureCoord;
}

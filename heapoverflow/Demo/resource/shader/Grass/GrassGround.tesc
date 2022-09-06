#version 450 core

layout (vertices=3) out;

in vec3 v_Position[];
out vec3 tc_Position[];

uniform float Inner=1.0;
uniform float Outer=1.0;

void main()
{
    if(gl_InvocationID==0)
    {
        gl_TessLevelInner[0]=Inner;
        gl_TessLevelOuter[0]=Outer;
        gl_TessLevelOuter[1]=Outer;
        gl_TessLevelOuter[2]=Outer;
    }
    //gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;

    tc_Position[gl_InvocationID]=v_Position[gl_InvocationID];
}
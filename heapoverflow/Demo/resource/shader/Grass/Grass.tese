#version 450 core

layout (triangles, equal_spacing, ccw) in;

in vec3 tc_Position[];

out vec4 geom_Position;

void main()
{
    //vec3 gl_TessCoord --normalized coordinates 
    //for tri interpret them as barycentric coords
    float u=gl_TessCoord.x;
    float v=gl_TessCoord.y;
    float w=gl_TessCoord.z;
    vec3 p0=tc_Position[0]*u;
    vec3 p1=tc_Position[1]*v;
    vec3 p2=tc_Position[2]*w;

    vec3 point=p0+p1+p2;
    geom_Position=vec4(point,1);
}
#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices=5) out;

in vec4 geom_Position[];

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

uniform float u_width=2.0;
uniform float u_height=10.0;
uniform float u_rotation=0.0;

float slice=7;

out vec4 point_color;

void SubmitVertex(vec4 position,vec4 color)
{
    point_color=color;
    gl_Position=u_ViewProjection*position;
    EmitVertex();
}


mat4 rotationMatrix(vec3 axis, float angle) {
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

vec3 rotate(vec3 v, vec3 axis, float angle) {
	mat4 m = rotationMatrix(axis, angle);
	return (m * vec4(v, 1.0)).xyz;
}


void main()
{
    vec4 p=u_Transform*geom_Position[0];
    vec4 q=u_Transform*geom_Position[1];
    vec4 r=u_Transform*geom_Position[2];
    vec3 normal_vector=normalize(cross(q.xyz-p.xyz,r.xyz-p.xyz));
    vec4 center=(p+q+r)/3.0;

    vec4 p_dir_to_center=normalize(center-p);
    float width=u_width/u_ViewProjection[0][0]/u_Transform[0][0];
    vec4 b1=center+p_dir_to_center*width;
    vec4 b0=center-p_dir_to_center*width;
    float height=u_height;
    vec4 top_col=vec4(0.3412, 0.5882, 0.0588, 1.0);
    vec4 bottom_col=vec4(0.0196, 0.3608, 0.0078, 1.0);

    vec4 up_vector=vec4((normal_vector*height).xyz,0);
    vec3 rotate_axis=(b1-b0).xyz;
    vec3 rotated_top_vector=rotate(up_vector.xyz,rotate_axis,u_rotation/slice);

    SubmitVertex(b0,bottom_col);
    SubmitVertex(b1,bottom_col);

    vec4 top=center+vec4(rotated_top_vector,0);
    vec4 mid0=vec4(mix(b0,top, 0.5).xyz,1);
    SubmitVertex(mid0,bottom_col);
    vec4 mid1=vec4(mix(b1,top, 0.5).xyz,1);
    SubmitVertex(mid1,bottom_col);
    rotated_top_vector=rotate(rotated_top_vector,rotate_axis,u_rotation/slice);
    
    SubmitVertex(center+vec4(rotated_top_vector,0),top_col);


    EndPrimitive();
}



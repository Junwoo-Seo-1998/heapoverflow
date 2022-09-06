#version 330 core		
in vec4 v_Color;

in float color_factor;

out vec4 color;

void main()
{
	float factor=color_factor;

	//factor=1;


	const float step1=.1;
    const float step2=.4;
    const float step3=.6;
    const float step4=.9;

    if(factor < step1)
        factor = step1;
    else if (factor < step2)
        factor = step2;
    else if(factor<step3)
        factor=step3;
    else if(factor<step4)
        factor=step4;
    else
        factor = 1.;

	vec3 rgb_col=factor*vec3(0.7255, 0.7216, 0.4275);

	

	color=vec4(rgb_col,1.f);
}
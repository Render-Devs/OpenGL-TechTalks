#version 460

out vec4 FragColor;
in vec4 outColor;

subroutine vec4 gradientBaseColor();

layout(index = 3) subroutine(gradientBaseColor) vec4 redColor()
{
	return vec4(1.0, 0.0, 0.0, 1.0);
}

layout(index = 4) subroutine(gradientBaseColor) vec4 blueColor()
{
	return vec4(0.0, 0.3, 0.8, 1.0);
}

uniform vec2 u_resolution;
layout(location = 3) subroutine uniform gradientBaseColor newGradientColor;

void main()
{
	//vec2 st = gl_FragCoord.xy/u_resolution;
	//vec4 color1 = newGradientColor();
	//vec3 color2 = vec3(0.226, 0.0, 0.615);

	//float mixValue = distance(st, vec2(0,1));
	//vec3 resColor = mix(color1.rgb, color2, mixValue);

	FragColor = newGradientColor() * outColor;
}

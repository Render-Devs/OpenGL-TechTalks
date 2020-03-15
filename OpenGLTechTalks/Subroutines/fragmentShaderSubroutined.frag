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

layout(location = 3) subroutine uniform gradientBaseColor newGradientColor;

void main()
{
	FragColor = newGradientColor() * outColor;
}

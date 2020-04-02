#version 460
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec4 aColor;
out vec4 oColor;
void main()
{
  gl_Position = aPos;
  oColor = aColor;
}

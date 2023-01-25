#version 330 core

layout(location = 0) out vec4 FragColor;
in vec4 ourColor;
in vec3 ourPos;

void main()
{
  FragColor = vec4(ourPos * 0.5 + 0.5, 1.0);
  FragColor = ourColor;
}


#version 330 core

out vec4 FragColor;
in vec3 ourPos;

uniform vec3 u_Color;

void main()
{
  FragColor = vec4(u_Color, 1.0);
}


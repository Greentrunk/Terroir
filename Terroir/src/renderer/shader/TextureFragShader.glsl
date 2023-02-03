#version 330 core

out vec4 FragColor;
in vec2 v_TexCoord;

uniform vec3 u_Color;

void main()
{
  FragColor = vec4(v_TexCoord, 0.0, 1.0);
}



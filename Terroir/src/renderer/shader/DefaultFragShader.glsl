#type fragment
#version 330 core

 in vec3 v_Position;
in vec4 v_Color;
layout (location = 0) out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
color = vec4(v_Position * 0.5 + 0.5, 1.0);
color = v_Color;
}


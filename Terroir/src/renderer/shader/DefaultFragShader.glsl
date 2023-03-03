#type fragment
#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D image;
uniform vec4 u_Color;

void main()
{
color = u_Color;
}


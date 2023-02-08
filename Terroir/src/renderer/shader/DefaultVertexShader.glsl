#type vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;


out vec4 ourColor;
out vec3 ourPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
  ourPos = a_Pos;
  ourColor = a_Color;
  gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);
}


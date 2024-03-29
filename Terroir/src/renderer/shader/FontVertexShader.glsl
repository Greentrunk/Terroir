#type vertex
#version 330 core
layout (location = 0) in vec4 a_Vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Vertex.xy, 0.0, 1.0);
    TexCoords = a_Vertex.zw;
}  
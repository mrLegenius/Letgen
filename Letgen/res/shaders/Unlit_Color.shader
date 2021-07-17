#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_Color;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0f);
	v_Color = a_Color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

in vec4 v_Color;

void main()
{
	color = v_Color;
};
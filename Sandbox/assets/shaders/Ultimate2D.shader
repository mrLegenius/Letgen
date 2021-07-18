#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec4 v_Color;


uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform float u_TexTiling = 1.0;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0f);
	v_TexCoord = a_TexCoord * u_TexTiling;
	v_Color = a_Color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	color = texture(u_Texture, v_TexCoord) * u_Color;
	color = v_Color;
};
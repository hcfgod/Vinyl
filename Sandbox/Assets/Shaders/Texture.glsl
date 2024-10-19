// Basic texture shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoord;

out vec2 v_TextureCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	v_TextureCoord = a_TextureCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core

in vec2 v_TextureCoord;

out vec4 o_Color;
				
uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform float u_TilingFactor;

void main()
{			
	o_Color = texture(u_Texture, v_TextureCoord * u_TilingFactor) * u_Color;
}
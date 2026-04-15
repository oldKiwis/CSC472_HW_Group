#version 330

in vec3  a_Position;	// attribute variable: position vector
in vec2  a_TexCoord;	// attribute variable: texture coordinate

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform sampler2D u_Sampler;

out vec2 v_TexCoord;	// varying variable for passing texture coord to fragment shader

void main() 
{
	// PUT YOUR CODE HERE
	gl_Position = u_Projection * u_View * vec4(a_Position, 1.0);
	v_TexCoord  = a_TexCoord;
}
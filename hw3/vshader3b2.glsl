#version 330

in vec3  a_Position;	// attribute variable: position vector
in vec3  a_Color;	// attribute variable: color vector

uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 v_Color;	// varying variable for passing color to fragment shader

void main() 
{
	// PUT YOUR CODE HERE
	gl_Position = u_Projection * u_View * vec4(a_Position, 1.0);
	v_Color     = a_Color;
}

#version 330

in  vec3 v_Color;	// varying variable for passing color from vertex shader
out vec4 fragColor;

void main() 
{
	// PUT YOUR CODE HERE
	fragColor = vec4(v_Color, 1.0);
}
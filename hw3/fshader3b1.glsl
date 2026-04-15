#version 330

in  vec2 v_TexCoord;		// varying variable for passing texture coord from vertex shader
uniform sampler2D u_Sampler;	// uniform variable for the texture image
out vec4 fragColor;

void main() 
{
	// PUT YOUR CODE HERE
	fragColor = texture(u_Sampler, v_TexCoord);
}
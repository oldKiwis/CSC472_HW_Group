#version 330

// PUT YOUR CODE HERE
in vec3 vPosition;
in vec2 vTexCoord;

uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 fTexCoord;

void main() 
{
	// PUT YOUR CODE HERE
	gl_Position = u_Projection * u_View * vec4(vPosition, 1.0);
    fTexCoord = vTexCoord;
}

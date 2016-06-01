#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 color;	// The color variable has attribute position 1
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 texCoords;  
out vec3 ourColor; // Output a color to the fragment shader
out vec3 ourNormal;
out vec3 FragPos;
out vec2 TexCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

    gl_Position = projection* view * model * vec4(position, 1.0);
    ourColor = color; // Set ourColor to the input color we got from the vertex data
	ourNormal = mat3(transpose(inverse(model))) * normal;
	FragPos = vec3(model * vec4(position, 1.0f));
	TexCoords=texCoords;
} 

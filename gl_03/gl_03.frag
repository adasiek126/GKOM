#version 330 core

in vec3 ourColor;
in vec3 ourNormal;
in vec3 FragPos; 
out vec4 color;
uniform vec3 lightPos;  
void main()
{
	float ambientStrength = 1.0f;
	vec3 lightColor = vec3(1.0f,1.0f,1.0f);
	vec3 ambient = ambientStrength * vec3(0.3f, 0.3f, 0.3f);
	//vec3 result = ambient * ourColor;
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * ourColor;
	color = vec4(result, 1.0f);
}

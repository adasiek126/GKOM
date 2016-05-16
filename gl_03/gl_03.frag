#version 330 core

in vec3 ourColor;
in vec3 ourNormal;
in vec3 FragPos; 
out vec4 color;
uniform vec3 lightPos;  
uniform vec3 viewPos;
uniform float lightStrength;
//////////////////////////////////////////////////////////////////////
// wybrany materia�
//////////////////////////////////////////////////////////////////////
uniform int material = 0;

struct MaterialParameters
{
    vec4 ambient;       // wsp�czynnik odbicia �wiat�a otoczenia; oznaczenie Ma
    vec4 diffuse;       // wsp�czynnik odbicia �wiat�a rozproszonego; oznaczenie Md
    vec4 specular;      // wsp�czynnik odbicia �wiat�a zwierciadlanego; oznaczenie Ms
    float shininess;    // wyk�adnik wsp�czynnika funkcji rozb�ysku;
                        // zakres warto�ci <0;128>; oznaczenie Msh
};

//////////////////////////////////////////////////////////////////////
// prototypy funkcji
//////////////////////////////////////////////////////////////////////
MaterialParameters GetMaterial( const int material );

void main()
{
	/*// pobranie wybranego materia�u
    MaterialParameters mat = GetMaterial( material );	
	
	vec3 lightColor = lightStrength * vec3(1.0f,1.0f,1.0f);
	vec4 light = vec4(lightColor,1.0);
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);  

	//vec3 result = (ambient + diffuse + specular) * ourColor;

	color = diff * mat.diffuse * light  + mat.specular * light * spec;

	//color = vec4(result, 1.0f);*/

	float ambientStrength = 1.0f;
	vec3 lightColor = lightStrength*vec3(1.0f,1.0f,1.0f);
	vec3 ambient = ambientStrength * vec3(0.3f, 0.3f, 0.3f);
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(lightPos - FragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	float specularStrength = 0.9f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  

	vec3 result = (ambient + diffuse + specular) * ourColor;
	color = vec4(result, 1.0f);
}

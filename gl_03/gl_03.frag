#version 330 core

in vec3 ourColor;
in vec3 ourNormal;
in vec3 FragPos; 
in vec2 TexCoords;
out vec4 color; 
uniform vec3 viewPos;
uniform float lightStrength;
struct Material{
	vec3 ambient;
	vec3 diffuse;
	sampler2D textureDiffuse;
	vec3 specular;
	float shininess;
};
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light; 
uniform Material material;
uniform bool textureUse;
void main()
{
	/*// pobranie wybranego materia³u
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
  	
    // Diffuse 
    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
    
	vec3 ambient;
	vec3 diffuse;
	if(!textureUse)
	{
		diffuse= light.diffuse * (diff * material.diffuse);
		ambient= light.ambient * material.ambient;
	}  
	else
	{
		diffuse = light.diffuse * diff * vec3(texture(material.textureDiffuse, TexCoords));
		ambient = light.ambient * vec3(texture(material.textureDiffuse, TexCoords));
	}
		  
	vec3 specular = light.specular * (spec * material.specular);     
    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}

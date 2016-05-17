#include "BoxModel.h"


BoxModel::BoxModel(ShaderProgram* program, GLuint diffuseTexture, GLuint specularTexture) :Model(program)
{
	useTexture = GL_TRUE;
	useSpecularTexture = GL_TRUE;
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
	if (useTexture == GL_TRUE)
		verticesSize = 2 * 6 * 8;
	else
		verticesSize = 6 * 8;
	indicesSize = 12 * 3;
	a = length;
	b = length;
	c = length;
	material = getMaterialStruct(MTL_RED_PLASTIC);
	loadTexture();
	generateVertices();
	generateCuboid();
	generateNormals();
	if (useTexture == GL_TRUE)
	{
		generateTextureCoords();
		glGenBuffers(1, &texBO);
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &NBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	if (useTexture == GL_FALSE)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize*sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normalsSize*sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	if (useTexture == GL_TRUE)
	{
		glBindBuffer(GL_ARRAY_BUFFER, texBO);
		glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GLfloat), textureCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		//texture
		glEnableVertexAttribArray(3);
	}
	else
	{
		// vertex color data

		glEnableVertexAttribArray(1);
	}
	glEnableVertexAttribArray(0);

	

	//normals
	glEnableVertexAttribArray(2);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
}
BoxModel::BoxModel(ShaderProgram* program, GLfloat a, GLfloat b, GLfloat c, GLfloat red, GLfloat green, GLfloat blue) :Model(program)
{
	verticesSize = 6 * 8;
	indicesSize = 12 * 3;
	material = getMaterialStruct(MTL_POLISHED_COPPER);
	this->a = a;
	this->b = b;
	this->c = c;
	this->red = red;
	this->green = green;
	this->blue = blue;
	generateVertices();
	generateCuboid();
	generateNormals();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &NBO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize*sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, normalsSize*sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glEnableVertexAttribArray(0);

	// vertex color data

	glEnableVertexAttribArray(1);

	//normals
	glEnableVertexAttribArray(2);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
}
void BoxModel::generateVertices()
{
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
	if (useTexture == GL_TRUE)
	{
		GLfloat v_pom[] = {
			-0.25f*b, -0.25f*a, 0.25f*c, red, green, blue,
			0.25f*b, -0.25f*a, 0.25f*c, red, green, blue,
			0.25f*b, 0.25f*a, 0.25f*c, red, green, blue,
			-0.25f*b, 0.25f*a, 0.25*c, red, green, blue,
			-0.25f*b, -0.25f*a, -0.25f*c, red, green, blue,
			0.25f*b, -0.25f*a, -0.25f*c, red, green, blue,
			0.25f*b, 0.25f*a, -0.25f*c, red, green, blue,
			-0.25f*b, 0.25f*a, -0.25*c, red, green, blue,
			
			-0.25f*b, 0.25f*a, 0.25*c, red, green, blue,
			-0.25f*b, 0.25f*a, -0.25*c, red, green, blue,
			-0.25f*b, -0.25f*a, -0.25f*c, red, green, blue,
			-0.25f*b, -0.25f*a, 0.25f*c, red, green, blue,
			0.25f*b, 0.25f*a, -0.25f*c, red, green, blue,
			0.25f*b, 0.25f*a, 0.25f*c, red, green, blue,
			0.25f*b, -0.25f*a, -0.25f*c, red, green, blue,
			0.25f*b, -0.25f*a, 0.25f*c, red, green, blue,
		};
		GLuint i_pom[] = {
				1, 0, 3,
				1, 2, 3,
				15, 14, 12,
				15, 13, 12,
				//1, 5, 6,
				//1, 2, 6,
				5, 6, 7,
				5, 4, 7,
				10, 9, 8,
				10, 11, 8,
				//4, 7, 3,
				//4, 0, 3,
				6, 7, 3,
				6, 2, 3,
				5, 4, 0,
				5, 1, 0,

			};
			for (int i = 0; i < verticesSize; i++){
				vertices[i] = v_pom[i];
			}
			for (int i = 0; i < 12 * 3; i++){
				indices[i] = i_pom[i];
			}
	}
	else
	{
		GLfloat v_pom[] = {
			-0.25f*b, -0.25f*a, 0.25f*c, red, green, blue,
			0.25f*b, -0.25f*a, 0.25f*c, red, green, blue,
			0.25f*b, 0.25f*a, 0.25f*c, red, green, blue,
			-0.25f*b, 0.25f*a, 0.25*c, red, green, blue,
			-0.25f*b, -0.25f*a, -0.25f*c, red, green, blue,
			0.25f*b, -0.25f*a, -0.25f*c, red, green, blue,
			0.25f*b, 0.25f*a, -0.25f*c, red, green, blue,
			-0.25f*b, 0.25f*a, -0.25*c, red, green, blue,
		};
		GLuint i_pom[] = {
			1, 0, 3,
			1, 2, 3,
			1, 5, 6,
			1, 2, 6,
			5, 6, 7,
			5, 4, 7,
			4, 7, 3,
			4, 0, 3,
			6, 7, 3,
			6, 2, 3,
			5, 4, 0,
			5, 1, 0,

		};
		for (int i = 0; i < verticesSize; i++){
			vertices[i] = v_pom[i];
		}
		for (int i = 0; i < indicesSize; i++){
			indices[i] = i_pom[i];
		}
	}
	
}
void BoxModel::generateNormals(bool abs)
{
	Model::generateNormals();

}
void BoxModel::loadTexture()
{
	glGenTextures(1, &diffuseMap);
	int width, height;
	unsigned char* image;
	// Diffuse map
	image = SOIL_load_image("box.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (useSpecularTexture)
	{
		image = SOIL_load_image("box_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void BoxModel::generateTextureCoords()
{
	textureCoords = new GLfloat[32];
	GLfloat t_pom[32] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f,1.0f,
		1.0f,1.0f,
		1.0f,0.0f,
		0.0f,0.0f,
		0.0f,1.0f,
		1.0f,1.0f,
		0.0f,0.0f,
		1.0f,0.0f,
	};
	
	for (int i = 0; i < 32; i++)
	{
		textureCoords[i] = t_pom[i];
	}
}
BoxModel::~BoxModel()
{
	delete[] vertices;
	delete[] indices;
}

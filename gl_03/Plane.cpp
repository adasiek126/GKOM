#include "Plane.h"


Plane::Plane(ShaderProgram* program, bool useTexture, bool useSpecularTexture, GLuint diffuseTexture, GLuint specularTexture) :Model(program)
{
	this->verticesSize = 6 * 4;
	this->indicesSize = 3*2;
	this->useTexture = useTexture;
	this->useSpecularTexture = useSpecularTexture;
	this->diffuseTexture = diffuseTexture;
	this->specularTexture = specularTexture;
	material = getMaterialStruct(MTL_YELLOW_RUBBER);
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
	glBufferData(GL_ARRAY_BUFFER, verticesSize*sizeof(vertices), vertices, GL_STATIC_DRAW);
	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	if (useTexture == GL_FALSE)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
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

void Plane::generateVertices()
{
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
	GLfloat v_pom[] = {
		-width/2,0.0f,-depth/2,red,green,blue,
		-width/2,0.0f,depth/2,red,green,blue,
		width/2,0.0f,-depth/2,red,green,blue,
		width/2,0.0f,depth/2,red,green,blue,
	};
	GLuint i_pom[] = {
		0,1,3,
		0,2,3,
	};
	for (int i = 0; i < verticesSize; i++)
	{
		vertices[i] = v_pom[i];
	}
	for (int i = 0; i < indicesSize; i++)
	{
		indices[i] = i_pom[i];
	}
}
void Plane::generateTextureCoords()
{
	textureCoords = new GLfloat[2 * 4];
	GLfloat t_pom[] = {
		0.0f,0.0f,
		0.0f,1.0f,
		1.0f,0.0f,
		1.0f,1.0f,
	};
	for (int i = 0; i < 2 * 4; i++)
	{
		textureCoords[i] = t_pom[i];
	}
}
void Plane::repaint()
{
	glm::mat4 model;
	this->setTransformation(glm::translate(model, position));
	this->display();
}
void Plane::generateNormals(bool abs)
{
	normals = new GLfloat[indicesSize];
	memset(normals, 0, sizeof(GLfloat)*(indicesSize));
	normalsSize = indicesSize;
	for (int i = 0; i < indicesSize / 3; i++)
	{
		glm::vec3 v10;
		glm::vec3 v21;
		if (i % 2 == 1)
		{
			v10 = (glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 0] + 0], vertices[6 * indices[3 * i + 0] + 1], vertices[6 * indices[3 * i + 0] + 2]));
			v21 = (glm::vec3(vertices[6 * indices[3 * i + 2] + 0], vertices[6 * indices[3 * i + 2] + 1], vertices[6 * indices[3 * i + 2] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]));
		}
		else
		{
			v10 = (-glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]) + glm::vec3(vertices[6 * indices[3 * i + 0] + 0], vertices[6 * indices[3 * i + 0] + 1], vertices[6 * indices[3 * i + 0] + 2]));
			v21 = (glm::vec3(vertices[6 * indices[3 * i + 2] + 0], vertices[6 * indices[3 * i + 2] + 1], vertices[6 * indices[3 * i + 2] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]));
		}
		const glm::vec3 normal(glm::normalize(glm::cross(v10, v21)));
		if (abs)
		{
			normals[3 * indices[3 * i + 0] + 0] += std::abs(normal[0]);
			normals[3 * indices[3 * i + 0] + 1] += std::abs(normal[1]);
			normals[3 * indices[3 * i + 0] + 2] += std::abs(normal[2]);

			normals[3 * indices[3 * i + 1] + 0] += std::abs(normal[0]);
			normals[3 * indices[3 * i + 1] + 1] += std::abs(normal[1]);
			normals[3 * indices[3 * i + 1] + 2] += std::abs(normal[2]);

			normals[3 * indices[3 * i + 2] + 0] += std::abs(normal[0]);
			normals[3 * indices[3 * i + 2] + 1] += std::abs(normal[1]);
			normals[3 * indices[3 * i + 2] + 2] += std::abs(normal[2]);
		}
		else
		{
			normals[3 * indices[3 * i + 0] + 0] += (normal[0]);
			normals[3 * indices[3 * i + 0] + 1] += (normal[1]);
			normals[3 * indices[3 * i + 0] + 2] += (normal[2]);

			normals[3 * indices[3 * i + 1] + 0] += (normal[0]);
			normals[3 * indices[3 * i + 1] + 1] += (normal[1]);
			normals[3 * indices[3 * i + 1] + 2] += (normal[2]);

			normals[3 * indices[3 * i + 2] + 0] += (normal[0]);
			normals[3 * indices[3 * i + 2] + 1] += (normal[1]);
			normals[3 * indices[3 * i + 2] + 2] += (normal[2]);
		}

	}
	for (int i = 0; i < verticesSize / 6; i++)
	{
		glm::vec3 temp = glm::vec3(normals[3 * i + 0], normals[3 * i + 1], normals[3 * i + 2]);
		if (glm::length(temp) > 0.001f)
		{
			const glm::vec3 normal(glm::normalize(glm::vec3(normals[3 * i + 0], normals[3 * i + 1], normals[3 * i + 2])));
			normals[3 * i + 0] = normal[0];
			normals[3 * i + 1] = normal[1];
			normals[3 * i + 2] = normal[2];
		}
		else
		{
			normals[3 * i + 0] = 0.0f;
			normals[3 * i + 1] = 0.0f;
			normals[3 * i + 2] = 0.0f;
		}
	}
}
Plane::~Plane()
{
	delete[] vertices;
	delete[] indices;
}

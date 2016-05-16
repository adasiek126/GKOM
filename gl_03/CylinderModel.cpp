#include "CylinderModel.h"


CylinderModel::CylinderModel(ShaderProgram* program, GLfloat height,GLfloat radius) : Model(program)
{
	this->radius = radius;
	this->cylinderHeight = height;
	material = MTL_CHROME;
	verticesSize = 6 * (CylinderModel::walls * 2 + 2);
	indicesSize = 3 * 4 * CylinderModel::walls;
	generateVertices();
	generateCuboid();
	generateNormals();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &NBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*sizeof(vertices), vertices, GL_STATIC_DRAW);
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
CylinderModel::CylinderModel(ShaderProgram* program, GLfloat height, GLfloat radius, GLfloat red, GLfloat green, GLfloat blue) :Model(program)
{
	this->radius = radius;
	this->cylinderHeight = height;
	this->red = red;
	this->blue = blue;
	this->green = green;
	material = MTL_BLACK_RUBBER;
	verticesSize = 6 * (CylinderModel::walls * 2 + 2);
	indicesSize = 3 * 4 * CylinderModel::walls;
	generateVertices();
	generateCuboid();
	generateNormals();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &NBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*sizeof(vertices), vertices, GL_STATIC_DRAW);
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
void CylinderModel::generateVertices()
{
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
	GLfloat angle = 360.0f / walls;
	GLfloat radianAngleInc = glm::radians(angle);
	GLfloat radianAngle = 0.0f;
	vertices[0] = centerX;
	vertices[1] = centerY + 0.5f*cylinderHeight;
	vertices[2] = centerZ;
	vertices[3] = red;
	vertices[4] = green;
	vertices[5] = blue;
	vertices[6 * (walls * 2 + 2) - 6] = centerX;
	vertices[6 * (walls * 2 + 2) - 5] = centerY - 0.5f*cylinderHeight;
	vertices[6 * (walls * 2 + 2) - 4] = centerZ;
	vertices[6 * (walls * 2 + 2) - 3] = red;
	vertices[6 * (walls * 2 + 2) - 2] = green;
	vertices[6 * (walls * 2 + 2) - 1] = blue;
	bool odd = true;
	for (int i = 6; i < 6 * (walls * 2 + 1); i += 6)
	{
		vertices[i] = centerX + radius*glm::cos(radianAngle);
		vertices[i + 2] = centerZ + radius*glm::sin(radianAngle);
		if (odd){
			vertices[i + 1] = centerY + 0.5f*cylinderHeight;
			odd = false;
		}
		else
		{
			vertices[i + 1] = centerY - 0.5f*cylinderHeight;
			radianAngle += radianAngleInc;
			odd = true;
		}
		vertices[i + 3] = red;
		vertices[i + 4] = green;
		vertices[i + 5] = blue;

	}
	//Budowa scian bocznych
	GLuint vertexNumber = 1;
	odd = true;
	for (int i = 3 * walls; i < 3 * 4 * walls - 3 * walls; i += 3)
	{
		indices[i] = vertexNumber;
		if (vertexNumber + 3 >= lastVertexIndex)
		{
			indices[i + 2] = 2;
		}
		else{
			indices[i + 2] = vertexNumber + 3;
		}

		if (odd){
			indices[i + 1] = vertexNumber + 1;
			odd = false;
		}
		else
		{
			if (vertexNumber + 2 >= lastVertexIndex)
			{
				indices[i + 1] = 1;
			}
			else
			{
				indices[i + 1] = vertexNumber + 2;
			}
			vertexNumber += 2;
			odd = true;
		}
	}
	//---------------------------------------------
	//Budowa podstaw
	vertexNumber = 2;
	for (int i = 3 * 4 * walls - 3 * walls; i < 3 * 4 * walls; i += 3)
	{
		indices[i] = walls * 2 + 1;
		if (vertexNumber + 2 >= lastVertexIndex)
		{
			indices[i + 2] = 2;
		}
		else
		{
			indices[i + 2] = vertexNumber + 2;
		}
		indices[i + 1] = vertexNumber;
		vertexNumber += 2;
	}
	vertexNumber = 1;
	for (int i = 0; i < 3 * walls; i += 3)
	{
		indices[i] = 0;
		if (vertexNumber + 2 >= lastVertexIndex)
		{
			indices[i + 2] = 1;
		}
		else
		{
			indices[i + 2] = vertexNumber + 2;
		}
		indices[i + 1] = vertexNumber;
		vertexNumber += 2;
	}
}
CylinderModel::~CylinderModel()
{
	delete[] vertices;
	delete[] indices;
}

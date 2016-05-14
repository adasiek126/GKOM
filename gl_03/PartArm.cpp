#include "PartArm.h"


PartArm::PartArm(ShaderProgram* program):Model(program)
{
	verticesSize = 6 * 16;
	indicesSize = 3 * 28;
	generateVertices();
	generateCuboid();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize*sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize*sizeof(indices), indices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);
}

void PartArm::generateVertices()
{
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
	GLfloat v_pom[] = {
		0.25f*width, 0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width, 0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width, -0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
		0.25f*width, -0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
		0.25f*width, 0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width, 0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width, -0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
		0.25f*width, -0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - 0.5f*width - length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - 0.5f*width - length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + 0.5f*width + length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
		-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + 0.5f*width + length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
	};
	GLuint i_pom[] = {
		0, 1, 2,
		0, 3, 2,
		0, 4, 7,
		0, 3, 7,
		5, 4, 7,
		5, 6, 7,
		5, 1, 2,
		5, 6, 2,
		6, 7, 9,
		6, 10, 9,
		6, 2, 11,
		6, 10, 11,
		2, 3, 8,
		2, 11, 8,
		7, 3, 8,
		7, 9, 8,
		9, 8, 11,
		9, 10, 11,
		5, 14, 13,
		5, 4, 13,
		14, 5, 1,
		14, 15, 1,
		4, 0, 12,
		4, 13, 12,
		1, 15, 12,
		1, 0, 12,
		14, 13, 12,
		14, 15, 12
	};
	for (int i = 0; i < 6 * 16; i++)
	{
		vertices[i] = v_pom[i];
	}
	for (int i = 0; i < 3 * 28; i++)
	{
		indices[i] = i_pom[i];
	}
}

GLfloat PartArm::getPivotX()
{
	return this->getCuboid().getMaxX();
}
GLfloat PartArm::getPivotY()
{
	return this->getCuboid().getMaxY() - 0.25*width;
}
GLfloat PartArm::getPivotZ()
{
	return (this->getCuboid().getMaxZ() + this->getCuboid().getMinZ()) / 2;
}
PartArm::~PartArm()
{
	delete[] vertices;
	delete[] indices;
}

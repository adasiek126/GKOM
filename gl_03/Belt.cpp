#include "Belt.h"


Belt::Belt(ShaderProgram* program) :Model(program)
{
	this->verticesSize = 6 * 8;// 6 * (8 + 2 * (2 + walls * 2));
	this->indicesSize = 12;// 3 * (4 + 2 * (walls * 2));
	generateVertices();
	generateCuboid();
	on = true;
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

void Belt::generateVertices()
{
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
	//czesci plaskie
	GLfloat v_pom[] = {
		centerX - width / 2, centerY + height / 2, centerZ - depth / 2, red, green, blue,
		centerX - width / 2, centerY + height / 2, centerZ + depth / 2, red, green, blue,
		centerX + width / 2, centerY + height / 2, centerZ - depth / 2, red, green, blue,
		centerX + width / 2, centerY + height / 2, centerZ + depth / 2, red, green, blue,
		centerX - width / 2, centerY - height / 2, centerZ - depth / 2, red, green, blue,
		centerX - width / 2, centerY - height / 2, centerZ + depth / 2, red, green, blue,
		centerX + width / 2, centerY - height / 2, centerZ - depth / 2, red, green, blue,
		centerX + width / 2, centerY - height / 2, centerZ + depth / 2, red, green, blue,
	};
	for (int i = 0; i < 8*6; i++)
	{
		vertices[i] = v_pom[i];
	}
	GLuint indices_pom[] = {
		0, 2, 3,
		0, 1, 3,
		4, 6, 7,
		4, 5, 7,
	};
	for (int i = 0; i < 12; i++)
	{
		indices[i] = indices_pom[i];
	}

}

void Belt::repaint()
{
	glm::mat4 model;
	this->setTransformation(glm::translate(model, position));
	this->display();
}
Belt::~Belt()
{
	delete[] vertices;
	delete[] indices;
}

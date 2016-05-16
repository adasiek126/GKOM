#include "BoxModel.h"


BoxModel::BoxModel(ShaderProgram* program) :Model(program)
{
	verticesSize = 6 * 8;
	indicesSize = 12 * 3;
	a = length;
	b = length;
	c = length;
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
BoxModel::BoxModel(ShaderProgram* program, GLfloat a, GLfloat b, GLfloat c, GLfloat red, GLfloat green, GLfloat blue) :Model(program)
{
	verticesSize = 6 * 8;
	indicesSize = 12 * 3;
	this->a = a;
	this->b = b;
	this->c = c;
	this->red = red;
	this->green = green;
	this->blue = blue;
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
void BoxModel::generateVertices()
{
	vertices = new GLfloat[verticesSize];
	indices = new GLuint[indicesSize];
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
		0, 1, 2,
		0, 3, 2,
		1, 5, 6,
		1, 2, 6,
		5, 6, 7,
		5, 4, 7,
		4, 7, 3,
		4, 0, 3,
		3, 2, 6,
		3, 7, 6,
		0, 1, 5,
		0, 4, 5
	};
	for (int i = 0; i < 6 * 8; i++){
		vertices[i] = v_pom[i];
	}
	for (int i = 0; i < 12 * 3; i++){
		indices[i] = i_pom[i];
	}
}

BoxModel::~BoxModel()
{
	delete[] vertices;
	delete[] indices;
}

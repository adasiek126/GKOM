#include "Floor.h"


Floor::Floor(ShaderProgram* program) :Model(program)
{
	this->verticesSize = 6 * 4;
	this->indicesSize = 3*2;
	material = MTL_YELLOW_RUBBER;
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

void Floor::generateVertices()
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

void Floor::repaint()
{
	glm::mat4 model;
	this->setTransformation(glm::translate(model, position));
	this->display();
}
Floor::~Floor()
{
	delete[] vertices;
	delete[] indices;
}

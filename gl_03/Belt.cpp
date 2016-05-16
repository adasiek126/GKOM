#include "Belt.h"


Belt::Belt(ShaderProgram* program) :Model(program)
{
	this->verticesSize = 6 * (8 + 2 * (walls * 2-2));
	this->indicesSize =  3 * (4 + 2 * (walls * 2));
	cylinderLeft = new CylinderModel(program, depth + 0.5f, height / 2 - 0.01f*(height/2), 0.0f, 0.0f, 0.0f);
	cylinderRight = new CylinderModel(program, depth + 0.5f, height / 2 - 0.01f*(height / 2), 0.0f, 0.0f, 0.0f);
	frontSupport = new BoxModel(program, 2.0f*(centerY + 2.5f), 2.05f*width, 0.25f,0.3f,0.3f,0.2f);
	backSupport = new BoxModel(program, 2.0f*(centerY + 2.5f), 2.05f*width, 0.25f, 0.3f, 0.3f, 0.2f);
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

	GLfloat angleInc = 180.0f / walls;
	GLfloat radianAngleInc = glm::radians(angleInc);
	GLfloat angle = -90.0f;
	GLfloat radianAngle = glm::radians(angle);
	bool odd = false;
	for (int i = 8 * 6; i < 6*(8+(walls * 2 - 2)); i += 6)
	{
		vertices[i] = centerX + width / 2 + height / 2 * glm::cos(radianAngle);
		vertices[i + 1] = centerY + height / 2 * glm::sin(radianAngle);
		if (odd)
		{
			vertices[i + 2] = centerZ - depth / 2;
			odd = false;
			radianAngle += radianAngleInc;
		}
		else
		{
			vertices[i + 2] = centerZ + depth / 2;
			odd = true;
		}
		vertices[i + 3] = red;
		vertices[i + 4] = green;
		vertices[i + 5] = blue;
	}
	radianAngle = glm::radians(-angle);
	for (int i = 6 * (8 + (walls * 2 - 2)); i < verticesSize; i += 6)
	{
		vertices[i] = centerX - width / 2 + height / 2 * glm::cos(radianAngle);
		vertices[i + 1] = centerY + height / 2 * glm::sin(radianAngle);
		if (odd)
		{
			vertices[i + 2] = centerZ - depth / 2;
			odd = false;
			radianAngle += radianAngleInc;
		}
		else
		{
			vertices[i + 2] = centerZ + depth / 2;
			odd = true;
		}
		vertices[i + 3] = red;
		vertices[i + 4] = green;
		vertices[i + 5] = blue;
	}
	//Budowa scian bocznych
	GLuint vertexNumber = 6;
	GLuint lastVertexIndex = 8 + walls * 2 - 3;
	odd = true;
	for (int i = 12; i < 3 * (4 + (walls * 2)); i += 3)
	{
		indices[i] = vertexNumber;
		if (vertexNumber + 3 > lastVertexIndex)
		{
			indices[i + 2] = 2;
		}
		else
		{
			indices[i + 2] = vertexNumber + 3;
		}
		if (odd)
		{
			indices[i + 1] = vertexNumber + 1;
			odd = false;
		}
		else
		{
			if (vertexNumber + 2 > lastVertexIndex)
			{
				indices[i + 1] = 3;
			}
			else
			{
				indices[i + 1] = vertexNumber + 2;
			}
			vertexNumber += 2;
			odd = true;
		}
	}
	GLuint lastVertex = vertexNumber;
	int begin = 3 * (4 + (walls * 2));
	lastVertexIndex = (8 + 2*(walls * 2 - 2)) - 1;
	odd = true;
	for (int i = begin; i < indicesSize; i += 3)
	{
		if (i == begin)
		{
			indices[i] = lastVertex;
			indices[i + 1] = 0;
			indices[i + 2] = 1;
			continue;
		}
		if (i == begin + 3)
		{
			indices[i] = lastVertex;
			indices[i + 1] = lastVertex+1;
			indices[i + 2] = 1;
			continue;
		}
		if (i == indicesSize - 3)
		{
			indices[i] = lastVertexIndex;
			indices[i + 1] = lastVertexIndex - 1;
			indices[i + 2] = 5;
			continue;
		}
		if (i == indicesSize - 6)
		{
			indices[i] = lastVertexIndex;
			indices[i + 1] = 4;
			indices[i + 2] = 5;
			continue;
		}
		indices[i] = vertexNumber;
		indices[i + 2] = vertexNumber + 3;
		if (odd)
		{
			indices[i + 1] = vertexNumber + 1;
			odd = false;
		}
		else
		{
			indices[i + 1] = vertexNumber + 2;
			vertexNumber += 2;
			odd = true;
		}
	}
}

void Belt::repaint()
{
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(position[0] - width / 2 + centerX, position[2]+centerZ,position[1]-centerY));
	cylinderLeft->setTransformation(model);
	cylinderLeft->display();
	model = glm::mat4();
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(position[0] + width / 2 + centerX, position[2] + centerZ, position[1] - centerY));
	cylinderRight->setTransformation(model);
	cylinderRight->display();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(position[0]+centerX, position[1]+centerY-frontSupport->getHeight()/4 , position[2]+centerZ+1.1f*depth/2));
	frontSupport->setTransformation(model);
	frontSupport->display();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(position[0] + centerX, position[1] + centerY - frontSupport->getHeight() / 4, position[2] + centerZ - 1.1f*depth / 2));
	backSupport->setTransformation(model);
	backSupport->display();
	model = glm::mat4();
	this->setTransformation(glm::translate(model, position));
	this->display();
	
}
Belt::~Belt()
{
	delete[] vertices;
	delete[] indices;
	delete cylinderLeft;
	delete cylinderRight;
	delete frontSupport;
	delete backSupport;
}

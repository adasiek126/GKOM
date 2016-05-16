#include "PartArm.h"


PartArm::PartArm(ShaderProgram* program):Model(program)
{
	verticesSize = 6 * 16;
	indicesSize = 3 * 28;
	material = MTL_YELLOW_PLASTIC;
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
		2, 3, 0,
		4, 0, 3,
		3, 7, 4,
		5, 4, 7,
		7, 6, 5,
		1, 5, 6,
		6, 2, 1,
		3,2,11,
		11,8,3,
		7,3,8,
		8,9,7,
		6,7,9,
		9,10,6,
		10,6,2,
		2,11,10,
		9,8,11,
		11,10,9,
		15,1,0,
		0,12,15,
		4,0,12,
		12,13,4,
		5,4,13,
		13,14,5,
		14,5,1,
		1,15,14,
		14,15,12,
		12,13,14,
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
void PartArm::generateNormals(bool abs)
{
	normals = new GLfloat[verticesSize / 2];
	memset(normals, 0, sizeof(GLfloat)*(verticesSize / 2));
	for (int i = 0; i < indicesSize / 3; i++)
	{
		glm::vec3 v10;
		glm::vec3 v21;

		v10 = (glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 0] + 0], vertices[6 * indices[3 * i + 0] + 1], vertices[6 * indices[3 * i + 0] + 2]));
		v21 = (glm::vec3(vertices[6 * indices[3 * i + 2] + 0], vertices[6 * indices[3 * i + 2] + 1], vertices[6 * indices[3 * i + 2] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]));
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
	normalsSize = verticesSize / 2;
}
PartArm::~PartArm()
{
	delete[] vertices;
	delete[] indices;
}

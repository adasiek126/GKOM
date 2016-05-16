#include "Model.h"


Model::Model(ShaderProgram* program)
{
	normalsSize = 0;
	this->program = program;
}

glm::vec4& Model::getVerticeAfterTransformation(glm::vec4& vertice)
{
	return transformation * vertice;
}

void Model::setTransformation(glm::mat4& transformation)
{
	this->transformation = transformation;
	generateCuboid();
}

void Model::display()
{
	glBindVertexArray(VAO);
	GLint modelLoc = glGetUniformLocation(program->get_programID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation));
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
GLfloat* Model::getVertices()
{
	return vertices;
}
GLuint* Model::getIndices()
{
	return indices;
}
GLuint& Model::getEBO()
{
	return EBO;
}
GLuint& Model::getVBO()
{
	return VBO;
}
GLuint& Model::getVAO()
{
	return VAO;
}
Cuboid& Model::getCuboid()
{
	return cuboid;
}
void Model::generateCuboid()
{
	GLfloat maxX=vertices[0];
	GLfloat minX=vertices[0];
	GLfloat maxY=vertices[1];
	GLfloat minY=vertices[1];
	GLfloat maxZ=vertices[2];
	GLfloat minZ=vertices[2];
	for (int i = 0; i < verticesSize; i += 6)
	{
		if (vertices[i]>maxX)
		{
			maxX = vertices[i];
		}
		if (vertices[i] < minX)
		{
			minX = vertices[i];
		}
		if (vertices[i + 1] > maxY)
		{
			maxY = vertices[i + 1];
		}
		if (vertices[i + 1] < minY)
		{
			minY = vertices[i + 1];
		}
		if (vertices[i + 2] > maxZ)
		{
			maxZ = vertices[i + 2];
		}
		if (vertices[i + 2] < minZ)
		{
			minZ = vertices[i + 2];
		}
	}
	glm::vec4 beforeTransformation = glm::vec4(minX, minY, minZ, 1.0f);
	glm::vec4 afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setLBLVertex(glm::vec3(afterTransformation[0],afterTransformation[1],afterTransformation[2])/*glm::vec3(minX, minY, minZ)*/);
	beforeTransformation = glm::vec4(maxX, minY, minZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setLBRVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(maxX, minY, minZ)*/);
	beforeTransformation = glm::vec4(minX, minY, maxZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setLFLVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(minX, minY, maxZ)*/);
	beforeTransformation = glm::vec4(maxX, minY, maxZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setLFRVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(maxX, minY, maxZ)*/);
	beforeTransformation = glm::vec4(minX, maxY, minZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setUBLVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(minX, maxY, minZ)*/);
	beforeTransformation = glm::vec4(maxX, maxY, minZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setUBRVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(maxX, maxY, minZ)*/);
	beforeTransformation = glm::vec4(minX, maxY, maxZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setUFLVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(minX, maxY, maxZ)*/);
	beforeTransformation = glm::vec4(maxX, maxY, maxZ, 1.0f);
	afterTransformation = getVerticeAfterTransformation(beforeTransformation);
	cuboid.setUFRVertex(glm::vec3(afterTransformation[0], afterTransformation[1], afterTransformation[2])/*glm::vec3(maxX, maxY, maxZ)*/);
	cuboid.setMinX(minX);
	cuboid.setMaxX(maxX);
	cuboid.setMinY(minY);
	cuboid.setMaxY(maxY);
	cuboid.setMinZ(minZ);
	cuboid.setMaxZ(maxZ);
}
void Model::generateNormals(bool abs)
{
	normals = new GLfloat[verticesSize/2];
	memset(normals, 0, sizeof(GLfloat)*(verticesSize/2));
	for (int i = 0; i < indicesSize/3; i++)
	{
		glm::vec3 v10; 
		glm::vec3 v21;
		if (i % 2 == 1)
		{
			v10=(glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 0] + 0], vertices[6 * indices[3 * i + 0] + 1], vertices[6 * indices[3 * i + 0] + 2]));
			v21=(glm::vec3(vertices[6 * indices[3 * i + 2] + 0], vertices[6 * indices[3 * i + 2] + 1], vertices[6 * indices[3 * i + 2] + 2]) - glm::vec3(vertices[6 * indices[3 * i + 1] + 0], vertices[6 * indices[3 * i + 1] + 1], vertices[6 * indices[3 * i + 1] + 2]));
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
	normalsSize = verticesSize / 2;
}
Model::~Model()
{
	//delete[] normals;
}

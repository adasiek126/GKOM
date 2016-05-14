#include "Model.h"


Model::Model(ShaderProgram* program)
{
	
	this->program = program;
}

glm::vec4& Model::getVerticeAfterTransformation(glm::vec4& vertice)
{
	return transformation * vertice;
}

void Model::setTransformation(glm::mat4& transformation)
{
	this->transformation = transformation;
}

void Model::display()
{
	glBindVertexArray(VAO);
	GLint modelLoc = glGetUniformLocation(program->get_programID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformation));
	std::cout << indicesSize << std::endl;
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
	cuboid.setLBLVertex(glm::vec3(minX, minY, minZ));
	cuboid.setLBRVertex(glm::vec3(maxX, minY, minZ));
	cuboid.setLFLVertex(glm::vec3(minX, minY, maxZ));
	cuboid.setLFRVertex(glm::vec3(maxX, minY, maxZ));
	cuboid.setUBLVertex(glm::vec3(minX, maxY, minZ));
	cuboid.setUBRVertex(glm::vec3(maxX, maxY, minZ));
	cuboid.setUFLVertex(glm::vec3(minX, maxY, maxZ));
	cuboid.setUFRVertex(glm::vec3(maxX, maxY, maxZ));
	cuboid.setMinX(minX);
	cuboid.setMaxX(maxX);
	cuboid.setMinY(minY);
	cuboid.setMaxY(maxY);
	cuboid.setMinZ(minZ);
	cuboid.setMaxZ(maxZ);
}
Model::~Model()
{
}

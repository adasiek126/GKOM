#pragma once
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cuboid.h"
class Model
{
protected:
	GLuint verticesSize;
	GLuint indicesSize;
	GLfloat* vertices;
	GLuint* indices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	glm::mat4 transformation;
	virtual void generateVertices() = 0;
	ShaderProgram* program;
	Cuboid cuboid;
	void generateCuboid();
public:
	glm::vec4& getVerticeAfterTransformation(glm::vec4& vertice);
	void display();
	void setTransformation(glm::mat4& transformation);
	glm::mat4& getTransfloramtion(){ return transformation; };
	GLfloat* getVertices();
	GLuint* getIndices();
	GLuint& getEBO();
	GLuint& getVBO();
	GLuint& getVAO();
	Cuboid& getCuboid();
	Model(ShaderProgram* program);
	virtual ~Model();
};


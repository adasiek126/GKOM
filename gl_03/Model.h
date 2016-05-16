#pragma once
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cuboid.h"
#include "materials.h"
class Model
{
protected:
	GLuint verticesSize;
	GLuint indicesSize;
	GLuint normalsSize;
	GLfloat* vertices;
	GLfloat* normals;
	GLuint* indices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint NBO;
	glm::mat4 transformation;
	virtual void generateVertices() = 0;
	ShaderProgram* program;
	Cuboid cuboid;
	int material;
	void generateCuboid();
	virtual void generateNormals(bool abs = false);
public:
	glm::vec4& getVerticeAfterTransformation(glm::vec4& vertice);
	void display();
	void setTransformation(glm::mat4& transformation);
	glm::mat4& getTransfloramtion(){ return transformation; };
	GLfloat* getVertices();
	GLfloat* getNormals(){ return normals; }
	GLuint* getIndices();
	GLuint& getEBO();
	GLuint& getVBO();
	GLuint& getVAO();
	Cuboid& getCuboid();
	Model(ShaderProgram* program);
	virtual ~Model();
};


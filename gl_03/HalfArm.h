#pragma once
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class HalfArm
{
private:
	GLfloat vertices[16];
	GLuint indices[28];
	const GLfloat width;
	const GLfloat length;
	const GLfloat depth;
	const GLfloat height;
	const GLfloat alpha;
	glm::vec3 position;
	glm::mat4x4 modelTransform;
	static bool VAOinit;
	static bool VBOinit;
	static bool EBOinit;
public:
	HalfArm(GLfloat width, GLfloat height, GLfloat depth, GLfloat alpha, GLfloat length);
	void setPosition(glm::vec3& pos);
	static GLuint& getVAO();
	static GLuint& getVBO();
	static GLuint& getEBO();
	void bindGLArrays();
	void transform(glm::mat4x4 matrix);
	glm::mat4x4 getModelTransform();
	void draw(GLuint modelLoc);
	glm::vec3 getPosition();
	~HalfArm();
};


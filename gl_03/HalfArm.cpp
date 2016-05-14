#include "HalfArm.h"

HalfArm::HalfArm(GLfloat width, GLfloat height, GLfloat depth, GLfloat alpha, GLfloat length) :width(width), height(height), depth(depth), alpha(alpha), length(length)
{
	GLfloat vertices_pom[] = {
		// coordinates		// color
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
	for (int i = 0; i < 16; ++i)
	{
		vertices[i] = vertices_pom[i];
	}
	GLuint indices_pom[] = {
		0, 1, 2,
		0, 3, 2,
		0, 4, 7,
		0, 3, 7,
		5, 4, 7,
		5, 6, 7,
		5, 1, 2,
		5, 6, 2,
		6, 7, 9,
		6, 10, 9,
		6, 2, 11,
		6, 10, 11,
		2, 3, 8,
		2, 11, 8,
		7, 3, 8,
		7, 9, 8,
		9, 8, 11,
		9, 10, 11,
		5, 14, 13,
		5, 4, 13,
		14, 5, 1,
		14, 15, 1,
		4, 0, 12,
		4, 13, 12,
		1, 15, 12,
		1, 0, 12,
		14, 13, 12,
		14, 15, 12
	};
	for (int i = 0; i < 28; ++i)
	{
		indices[i] = indices_pom[i];
	}
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void HalfArm::setPosition(glm::vec3& pos)
{
	position = pos;
}
bool HalfArm::VAOinit = false;
GLuint& HalfArm::getVAO()
{
	static GLuint VAO;
	if (VAOinit == false){
		glGenVertexArrays(1, &VAO);
		VAOinit = true;
	}
	return VAO;
}
bool HalfArm::VBOinit = false;
GLuint& HalfArm::getVBO()
{
	static GLuint VBO;
	if (VBOinit == false){
		glGenBuffers(1, &VBO);
		VBOinit = true;
	}
	return VBO;
}
bool HalfArm::EBOinit = false;
GLuint& HalfArm::getEBO()
{
	static GLuint EBO;
	if (EBOinit == false){
		glGenBuffers(1, &EBO);
		EBOinit = true;
	}
	return EBO;
}

void HalfArm::bindGLArrays()
{
	glBindVertexArray(HalfArm::getVAO());

	glBindBuffer(GL_ARRAY_BUFFER, HalfArm::getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, HalfArm::getEBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex color data
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}
void HalfArm::transform(glm::mat4x4 matrix)
{
	modelTransform = matrix;
}
glm::mat4x4 HalfArm::getModelTransform()
{
	return modelTransform;
}
void HalfArm::draw(GLuint modelLoc)
{
	glBindVertexArray(HalfArm::getVAO());
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTransform));
	glDrawElements(GL_TRIANGLES, 3 * 28, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
glm::vec3 HalfArm::getPosition()
{
	return position;
}
HalfArm::~HalfArm()
{

}

#pragma once
#include <SOIL.h>
#include "Model.h"
class BoxModel :
	public Model
{
private:
	GLfloat length = 2.0f;
	GLfloat a;
	GLfloat b;
	GLfloat c;
	GLfloat red = 0.2f;
	GLfloat green = 0.7f;
	GLfloat blue = 0.3f;
	glm::vec3 position;
	GLuint texBO;
	GLfloat* textureCoords;
	void loadTexture();
protected:
	virtual void generateVertices();
	void generateNormals(bool abs = false);
	void generateTextureCoords();
public:
	GLfloat getHeight(){ return a; }
	GLfloat getWidth(){ return b; }
	GLfloat getDepth(){ return c; }
	glm::vec3& getPosition(){ return position; };
	void setPosition(glm::vec3& position){ this->position = position; };
	BoxModel(ShaderProgram* program, GLuint diffuseTexture, GLuint specularTexture);
	BoxModel(ShaderProgram* program, GLfloat a, GLfloat b, GLfloat c, GLfloat red, GLfloat green, GLfloat blue);
	~BoxModel();
};


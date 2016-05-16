#pragma once
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
protected:
	virtual void generateVertices();
public:
	GLfloat getHeight(){ return a; }
	GLfloat getWidth(){ return b; }
	GLfloat getDepth(){ return c; }
	glm::vec3& getPosition(){ return position; };
	void setPosition(glm::vec3& position){ this->position = position; };
	BoxModel(ShaderProgram* program);
	BoxModel(ShaderProgram* program, GLfloat a, GLfloat b, GLfloat c, GLfloat red, GLfloat green, GLfloat blue);
	~BoxModel();
};


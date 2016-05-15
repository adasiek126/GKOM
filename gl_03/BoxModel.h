#pragma once
#include "Model.h"
class BoxModel :
	public Model
{
private:
	GLfloat length = 2.0f;
	GLfloat red = 0.2f;
	GLfloat green = 0.7f;
	GLfloat blue = 0.3f;
	glm::vec3 position;
protected:
	virtual void generateVertices();
public:
	glm::vec3& getPosition(){ return position; };
	void setPosition(glm::vec3& position){ this->position = position; };
	BoxModel(ShaderProgram* program);
	~BoxModel();
};


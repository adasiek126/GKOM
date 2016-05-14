#pragma once
#include "Model.h"
class BoxModel :
	public Model
{
private:
	GLfloat length = 1.0f;
	GLfloat red = 0.2f;
	GLfloat green = 0.7f;
	GLfloat blue = 0.3f;
protected:
	virtual void generateVertices();
public:
	BoxModel(ShaderProgram* program);
	~BoxModel();
};


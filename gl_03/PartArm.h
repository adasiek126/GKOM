#pragma once
#include "Model.h"
class PartArm :
	public Model
{
private:
	const GLfloat length = 0.5f;
	const GLfloat alpha = 45.0f;
	const GLfloat width = 0.5f;
	const GLfloat depth = 1.0f;
	const GLfloat height = 0.5f;
protected:
	virtual void generateVertices();
	void generateNormals(bool abs = false);
public:
	PartArm(ShaderProgram* program);
	GLfloat getPivotX();
	GLfloat getPivotY();
	GLfloat getPivotZ();
	~PartArm();
};


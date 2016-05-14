#pragma once
#include "Model.h"
class CylinderModel :
	public Model
{
private:
	static const GLuint walls = 48;
	GLfloat centerX = 0.0f;
	GLfloat centerZ = 0.0f;
	GLfloat centerY = 0.0f;
	GLfloat cylinderHeight = 2.0f;
	GLfloat red = 0.7f;
	GLfloat green = 0.1f;
	GLfloat blue = 0.0f;
	GLfloat radius = 0.25f;
	GLuint lastVertexIndex = CylinderModel::walls * 2 + 1;
protected:
	virtual void generateVertices();
public:
	CylinderModel(ShaderProgram* program,GLfloat radius=0.25f);
	~CylinderModel();
};


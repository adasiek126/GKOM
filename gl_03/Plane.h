#pragma once
#include "Model.h"
class Plane :
	public Model
{
private:
	GLfloat width=20.0f;
	GLfloat depth=20.0f;
	GLfloat red=0.5f;
	GLfloat green=0.5f;
	GLfloat blue=0.0f;
	glm::vec3 position;
protected:
	void generateVertices();
	void generateTextureCoords();
	virtual void generateNormals(bool abs = false);
public:
	void setPosition(glm::vec3& pos){ position = pos; }
	glm::vec3& getPosition(){ return position; }
	void repaint();
	Plane(ShaderProgram* program, bool useTexture, bool useSpecularTexture, GLuint diffuseTexture, GLuint specularTexture);
	~Plane();
};


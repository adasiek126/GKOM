#pragma once
#include "PartArm.h"
class Arm
{
private:
	PartArm* leftArm;
	PartArm* rightArm;
	GLfloat angle;
	glm::vec3 position;
	void setRightArmPosition();
	void setPartsAngle();
public:
	Arm(ShaderProgram* program);
	void setAngle(GLfloat angle){ this->angle = angle; };
	GLfloat getAngle(){ return angle; };
	glm::vec3& getPosition(){ return position; }
	void setArmPosition();
	void setPosition(glm::vec3& position){ this->position = position; };
	void repaint();
	~Arm();
};


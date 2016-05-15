#pragma once
#include "Arm.h"
#include "CylinderModel.h"
class Holder
{
private:
	Arm* arm;
	CylinderModel* lowerCylinder;
	CylinderModel* upperCylinder;
	glm::vec3 position;
	GLfloat outthrusting;
	GLfloat angle;
	void generateLowerCylinderPosition();
	void generateUpperCylinderPosition();
public:
	Arm* getArm(){ return arm; };
	CylinderModel* getLowerCylinder(){ return lowerCylinder; };
	CylinderModel* getUpperCylinder(){ return upperCylinder; };
	void setOpenig(GLfloat angle){ this->angle = angle; };
	void repaint();
	void setLowerCylinderOuthrusting(GLfloat outthrusting);
	void setHolderPosition(glm::vec3 pos);
	Holder(ShaderProgram* program);
	~Holder();
};


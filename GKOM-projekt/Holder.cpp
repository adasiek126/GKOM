#include "Holder.h"


Holder::Holder(ShaderProgram* program)
{
	arm = new Arm(program);
	lowerCylinder = new CylinderModel(program,4.0f, 0.30f);
	upperCylinder = new CylinderModel(program,4.0f, 0.35f);
}
void Holder::repaint()
{
	glm::vec3 armPosition = glm::vec3(position[0], position[1] - outthrusting, position[2]);
	arm->setPosition(armPosition);
	arm->setAngle(this->angle);
	arm->repaint();
	generateLowerCylinderPosition();
	lowerCylinder->display();
	generateUpperCylinderPosition();
	upperCylinder->display();
}
void Holder::setLowerCylinderOuthrusting(GLfloat outthrusting)
{
	this->outthrusting = outthrusting;
}
void Holder::setHolderPosition(glm::vec3 pos)
{
	this->position = pos;
}
void Holder::generateLowerCylinderPosition()
{
	glm::vec3 armCenter= arm->getUpperCenter();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position[0] +arm->getPartsDistanceX()/2, position[1] + 0.65*lowerCylinder->getHeight() - outthrusting, position[2] + arm->getLeftArm()->getPivotZ()));
	lowerCylinder->setTransformation(model);
}
void Holder::generateUpperCylinderPosition()
{
	glm::vec3 armCenter = arm->getUpperCenter();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position[0] + arm->getPartsDistanceX() / 2, position[1] + 0.8*lowerCylinder->getHeight() + 0.2*upperCylinder->getHeight(), position[2] + arm->getLeftArm()->getPivotZ()));
	upperCylinder->setTransformation(model);
}
Holder::~Holder()
{
	delete arm;
	delete lowerCylinder;
	delete upperCylinder;
}

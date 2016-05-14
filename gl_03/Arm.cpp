#include "Arm.h"


Arm::Arm(ShaderProgram* program)
{
	leftArm = new PartArm(program);
	rightArm = new PartArm(program);
}
void Arm::setRightArmPosition()
{
	glm::mat4 model = rightArm->getTransfloramtion();
	model = glm::translate(model, glm::vec3(2.3f*leftArm->getCuboid().getMaxX(), 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rightArm->setTransformation(model);
}
void Arm::setArmPosition()
{
	glm::mat4 model=rightArm->getTransfloramtion();
	model = glm::translate(model, position);
	rightArm->setTransformation(model);
	model = leftArm->getTransfloramtion();
	model = glm::translate(model, position);
	leftArm->setTransformation(model);
}
void Arm::repaint()
{
	leftArm->setTransformation(glm::mat4());
	rightArm->setTransformation(glm::mat4());
	setArmPosition();
	setPartsAngle();
	setRightArmPosition();
	leftArm->display();
	rightArm->display();
}

void Arm::setPartsAngle()
{
	glm::mat4 model=leftArm->getTransfloramtion();
	model = glm::translate(model, glm::vec3(leftArm->getPivotX(), leftArm->getPivotY(),leftArm->getPivotZ()));
	model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-leftArm->getPivotX(), -leftArm->getPivotY(),leftArm->getPivotZ()));
	leftArm->setTransformation(model);
	model = rightArm->getTransfloramtion();
	model = glm::translate(model, glm::vec3(rightArm->getPivotX(), rightArm->getPivotY(), rightArm->getPivotZ()));
	model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::translate(model, glm::vec3(-rightArm->getPivotX(), -rightArm->getPivotY(),rightArm->getPivotZ()));
	rightArm->setTransformation(model);	
}
Arm::~Arm()
{
	delete leftArm;
	delete rightArm;
}

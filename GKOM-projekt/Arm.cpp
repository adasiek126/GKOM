#include "Arm.h"


Arm::Arm(ShaderProgram* program)
{
	leftArm = new PartArm(program);
	rightArm = new PartArm(program);
}
void Arm::setRightArmPosition()
{
	glm::mat4 model = rightArm->getTransfloramtion();
	model = glm::translate(model, glm::vec3(getPartsDistanceX(), 0.0f, 0.0f));
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
glm::vec3 Arm::getLowerCenter()
{
	glm::vec4 leftLowerPoint = glm::vec4(leftArm->getPivotX(), leftArm->getCuboid().getMinY(), leftArm->getPivotZ(), 1.0f);
	glm::vec4 afterTransformationLeft = leftArm->getVerticeAfterTransformation(leftLowerPoint);
	glm::vec4 rightLowerPoint = glm::vec4(rightArm->getPivotX(), rightArm->getCuboid().getMinY(), rightArm->getPivotZ(), 1.0f);
	glm::vec4 afterTransformationRight = rightArm->getVerticeAfterTransformation(rightLowerPoint);
	return glm::vec3((afterTransformationLeft[0] + afterTransformationRight[0]) / 2, (afterTransformationLeft[1] + afterTransformationRight[1]) / 2, (afterTransformationLeft[2] + afterTransformationRight[2]) / 2);
}
glm::vec3 Arm::getUpperCenter()
{
	glm::vec4 leftLowerPoint = glm::vec4(leftArm->getPivotX(), leftArm->getCuboid().getMaxY(), leftArm->getPivotZ(), 1.0f);
	glm::vec4 afterTransformationLeft = leftArm->getVerticeAfterTransformation(leftLowerPoint);
	glm::vec4 rightLowerPoint = glm::vec4(rightArm->getPivotX(), rightArm->getCuboid().getMaxY(), rightArm->getPivotZ(), 1.0f);
	glm::vec4 afterTransformationRight = rightArm->getVerticeAfterTransformation(rightLowerPoint);
	return glm::vec3((afterTransformationLeft[0] + afterTransformationRight[0]) / 2, (afterTransformationLeft[1] + afterTransformationRight[1]) / 2, (afterTransformationLeft[2] + afterTransformationRight[2]) / 2);
}
Arm::~Arm()
{
	delete leftArm;
	delete rightArm;
}

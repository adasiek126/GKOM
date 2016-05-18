#include "Scene.h"


Scene::Scene(ShaderProgram* program)
{
	holder = new Holder(program);
	box = new BoxModel(program, GL_TEXTURE0, GL_TEXTURE1);
	box->setDiffuseTextureFilename("box.png");
	box->setSpecularTextureFilename("box_specular.png");
	box->loadTexture();
	belt = new Belt(program);
	floor = new Plane(program,true,false,GL_TEXTURE2,NULL);
	floor->setDiffuseTextureFilename("beton.png");
	floor->loadTexture();
	floor->setPosition(glm::vec3(0.0f, -2.52f, 0.0f));
	backWall = new Plane(program, true, false, GL_TEXTURE3, NULL, glm::vec2(20.0f, 12.0f));
	backWall->setDiffuseTextureFilename("brick.png");
	backWall->loadTexture();
	frontWall = new Plane(program, true, false, GL_TEXTURE3, NULL, glm::vec2(20.0f, 12.0f));
	frontWall->setDiffuseTextureFilename("brick.png");
	frontWall->loadTexture();
	glm::mat4 model;
	box->setPosition(boxInitPosition);
	box->setTransformation(glm::translate(model, boxInitPosition));
	leftWall = new Plane(program, true, false, GL_TEXTURE3, NULL, glm::vec2(20.0f, 12.0f));
	leftWall->setDiffuseTextureFilename("brick.png");
	leftWall->loadTexture();
	rightWall = new Plane(program, true, false, GL_TEXTURE3, NULL, glm::vec2(20.0f, 12.0f));
	rightWall->setDiffuseTextureFilename("brick.png");
	rightWall->loadTexture();
	ceiling = new Plane(program, true, false, GL_TEXTURE2, NULL);
	ceiling->setDiffuseTextureFilename("beton.png");
	ceiling->loadTexture();
	ceiling->setPosition(glm::vec3(0.0f, 4.7f, 0.0f));
}
void Scene::repaint()
{
	generateBoxPosition();
	box->display();
	holder->repaint();
	belt->repaint();
	floor->repaint();
	ceiling->repaint();
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f,10.0f , -1.26f));
	backWall->setTransformation(model);
	backWall->display();
	model = glm::mat4();
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 10.0f, -1.26f));
	frontWall->setTransformation(model);
	frontWall->display();
	model = glm::mat4();
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, -10.0f, -1.26f));
	leftWall->setTransformation(model);
	leftWall->display();
	model = glm::mat4();
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 10.0f, -1.26f));
	rightWall->setTransformation(model);
	rightWall->display();
}
bool Scene::checkInteractionWithArm()
{
	glm::vec3 bUFL = box->getCuboid().getUFLVertex();
	glm::vec3 bUBL = box->getCuboid().getUBLVertex();
	glm::vec3 bUFR = box->getCuboid().getUFRVertex();
	glm::vec3 bUBR = box->getCuboid().getUBRVertex();
	glm::vec3 leftArmLFR = holder->getArm()->getLeftArm()->getCuboid().getLFRVertex();
	glm::vec3 leftArmLBR = holder->getArm()->getLeftArm()->getCuboid().getLBRVertex();
	glm::vec3 rightArmLFR = holder->getArm()->getRightArm()->getCuboid().getLFRVertex();
	glm::vec3 rightArmLBR = holder->getArm()->getRightArm()->getCuboid().getLBRVertex();
	if ((leftArmLFR[0] >= bUFL[0] || leftArmLFR[0] >= bUBL[0]) && (rightArmLFR[0] <= bUFR[0] || rightArmLFR[0] <= bUBR[0]))
	{
		if (leftArmLFR[1] < bUFL[1] && rightArmLFR[1] < bUBR[1])
		{
			if ((leftArmLFR[2] + leftArmLBR[2]) / 2 < bUFL[2] && (leftArmLFR[2] + leftArmLBR[2]) / 2 > bUBL[2])
			{
				return true;
			}
		}
	}
	return false;
}
void Scene::generateBoxPosition()
{
	glm::mat4 model;
	if (checkInteractionWithArm())
	{
		box->setPosition(holder->getArm()->getLowerCenter());
		box->setTransformation(glm::translate(model, holder->getArm()->getLowerCenter()));
	}	
	else
	{
		glm::vec3 boxPosition=box->getPosition();
		if (checkInteractionWithBelt())
		{
			if (belt->isOn())
				boxPosition[0] += belt->getSpeed();
		}
		else if (boxPosition[1] > -2.0f)
		{
			boxPosition[1] -= acceleration;
		}
		glm::mat4 model;
		box->setPosition(boxPosition);
		box->setTransformation(glm::translate(model, boxPosition));
	}
}
bool Scene::checkInteractionWithBelt()
{
	glm::vec3 bLFL = box->getCuboid().getLFLVertex();
	glm::vec3 bLBL = box->getCuboid().getLBLVertex();
	glm::vec3 bLFR = box->getCuboid().getLFRVertex();
	glm::vec3 bLBR = box->getCuboid().getLBRVertex();
	glm::vec3 beltUFL = belt->getCuboid().getUFLVertex();
	glm::vec3 beltUBR = belt->getCuboid().getUBRVertex();
	if (bLFL[0]+0.2f > beltUFL[0] && bLFL[0]-0.2f < beltUBR[0])
	{
		if (bLFL[1] - 0.1f < beltUFL[1])
		{
			if (bLFL[2]<beltUFL[2] && bLFL[2] > beltUBR[2])
			{
				return true;
			}
		}
	}
	return false;
}
Scene::~Scene()
{
	delete box;
	delete holder;
	delete belt;
	//delete floor;
}

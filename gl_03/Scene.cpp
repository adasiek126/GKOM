#include "Scene.h"


Scene::Scene(ShaderProgram* program)
{
	holder = new Holder(program);
	box = new BoxModel(program);
	glm::mat4 model;
	box->setPosition(boxInitPosition);
	box->setTransformation(glm::translate(model, boxInitPosition));
}
void Scene::repaint()
{
	generateBoxPosition();
	box->display();
	holder->repaint();
}
bool Scene::checkInteraction()
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
	if (checkInteraction())
	{
		box->setPosition(holder->getArm()->getLowerCenter());
		box->setTransformation(glm::translate(model, holder->getArm()->getLowerCenter()));
	}	
	else
	{
		glm::vec3 boxPosition=box->getPosition();
		if (boxPosition[1] > -2.0f)
		{
			boxPosition[1] -= 0.01f;
		}
		glm::mat4 model;
		box->setPosition(boxPosition);
		box->setTransformation(glm::translate(model, boxPosition));
	}
}
Scene::~Scene()
{
	delete box;
	delete holder;
}

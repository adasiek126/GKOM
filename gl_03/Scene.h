#pragma once
#include "Holder.h"
#include "BoxModel.h"
#include "Belt.h"
#include "Floor.h"
class Scene
{
private:
	BoxModel* box;
	Holder* holder;
	Belt* belt;
	Floor* floor;
	bool checkInteractionWithArm();
	bool checkInteractionWithBelt();
	void generateBoxPosition();
	glm::vec3 boxInitPosition;
	GLfloat acceleration = 0.1;
public:
	Holder* getHolder(){ return holder; };
	BoxModel* getBox(){ return box; };
	void repaint();
	Scene(ShaderProgram* program);
	~Scene();
};


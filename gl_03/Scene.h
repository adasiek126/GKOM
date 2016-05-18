#pragma once
#include "Holder.h"
#include "BoxModel.h"
#include "Belt.h"
#include "Plane.h"
class Scene
{
private:
	BoxModel* box;
	Holder* holder;
	Belt* belt;
	Plane* floor;
	Plane* backWall;
	Plane* leftWall;
	Plane* rightWall;
	Plane* frontWall;
	Plane* ceiling;
	bool checkInteractionWithArm();
	bool checkInteractionWithBelt();
	void generateBoxPosition();
	glm::vec3 boxInitPosition;
	GLfloat acceleration = 0.003f;
public:
	Holder* getHolder(){ return holder; };
	BoxModel* getBox(){ return box; };
	void repaint();
	Scene(ShaderProgram* program);
	~Scene();
};


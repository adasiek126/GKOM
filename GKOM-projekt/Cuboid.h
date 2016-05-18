#pragma once
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Cuboid
{
private:
	glm::vec3 lowerFrontRightVertex;
	glm::vec3 lowerFrontLeftVertex;
	glm::vec3 lowerBackRightVertex;
	glm::vec3 lowerBackLeftVertex;
	glm::vec3 upperFrontRightVertex;
	glm::vec3 upperFrontLeftVertex;
	glm::vec3 upperBackRightVertex;
	glm::vec3 upperBackLeftVertex;
	GLfloat minX;
	GLfloat maxX;
	GLfloat minY;
	GLfloat maxY;
	GLfloat minZ;
	GLfloat maxZ;
public:
	void setLFRVertex(glm::vec3& LFR){ lowerFrontRightVertex = LFR; };
	void setLFLVertex(glm::vec3& LFL){ lowerFrontLeftVertex = LFL; };
	void setLBRVertex(glm::vec3& LBR){ lowerBackRightVertex = LBR; };
	void setLBLVertex(glm::vec3& LBL){ lowerBackLeftVertex = LBL; };
	void setUFRVertex(glm::vec3& UFR){ upperFrontRightVertex = UFR; };
	void setUFLVertex(glm::vec3& UFL){ upperFrontLeftVertex = UFL; };
	void setUBRVertex(glm::vec3& UBR){ upperBackRightVertex = UBR; };
	void setUBLVertex(glm::vec3& UBL){ upperBackLeftVertex = UBL; };
	glm::vec3 getLFRVertex(){ return lowerFrontRightVertex; };
	glm::vec3 getLFLVertex(){ return lowerFrontLeftVertex; };
	glm::vec3 getLBRVertex(){ return lowerBackRightVertex; };
	glm::vec3 getLBLVertex(){ return lowerBackLeftVertex; };
	glm::vec3 getUFRVertex(){ return upperFrontRightVertex; };
	glm::vec3 getUFLVertex(){ return upperFrontLeftVertex; };
	glm::vec3 getUBRVertex(){ return upperBackRightVertex; };
	glm::vec3 getUBLVertex(){ return upperBackLeftVertex; };
	void setMinX(GLfloat x){ minX = x; };
	void setMaxX(GLfloat x){ maxX = x; };
	void setMinY(GLfloat y){ minY = y; };
	void setMaxY(GLfloat y){ maxY = y; };
	void setMinZ(GLfloat z){ minZ = z; };
	void setMaxZ(GLfloat z){ maxZ = z; };
	GLfloat getMinX(){ return minX; };
	GLfloat getMaxX(){ return maxX; };
	GLfloat getMinY(){ return minY; };
	GLfloat getMaxY(){ return maxY; };
	GLfloat getMinZ(){ return minZ; };
	GLfloat getMaxZ(){ return maxZ; };
	Cuboid();
	~Cuboid();
};


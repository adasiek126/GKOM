#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
struct Cylinder{
	static const GLuint walls = 48;
	GLfloat centerX = 0.0f;
	GLfloat centerZ = 0.0f;
	GLfloat centerY = 0.0f;
	GLfloat cylinderHeight = 2.0f;
	GLfloat red = 0.7f;
	GLfloat green = 0.1f;
	GLfloat blue = 0.0f;
	GLfloat radius = 0.25f;
	GLuint lastVertexIndex = Cylinder::walls * 2 + 1;
	GLfloat cylinderVertex[6 * (Cylinder::walls * 2 + 2)];
	GLuint cylinderIndices[3 * 4 * Cylinder::walls];
	void generateCylinderVertexes()
	{
		GLfloat angle = 360.0f / walls;
		GLfloat radianAngleInc = glm::radians(angle);
		GLfloat radianAngle = 0.0f;
		cylinderVertex[0] = centerX;
		cylinderVertex[1] = centerY + 0.5f*cylinderHeight;
		cylinderVertex[2] = centerZ;
		cylinderVertex[3] = red;
		cylinderVertex[4] = green;
		cylinderVertex[5] = blue;
		cylinderVertex[6 * (walls * 2 + 2) - 6] = centerX;
		cylinderVertex[6 * (walls * 2 + 2) - 5] = centerY - 0.5f*cylinderHeight;
		cylinderVertex[6 * (walls * 2 + 2) - 4] = centerZ;
		cylinderVertex[6 * (walls * 2 + 2) - 3] = red;
		cylinderVertex[6 * (walls * 2 + 2) - 2] = green;
		cylinderVertex[6 * (walls * 2 + 2) - 1] = blue;
		bool odd = true;
		for (int i = 6; i < 6 * (walls * 2 + 1); i += 6)
		{
			cylinderVertex[i] = centerX + radius*glm::cos(radianAngle);
			cylinderVertex[i + 2] = centerZ + radius*glm::sin(radianAngle);
			if (odd){
				cylinderVertex[i + 1] = centerY + 0.5f*cylinderHeight;
				odd = false;
			}
			else
			{
				cylinderVertex[i + 1] = centerY - 0.5f*cylinderHeight;
				radianAngle += radianAngleInc;
				odd = true;
			}
			cylinderVertex[i + 3] = red;
			cylinderVertex[i + 4] = green;
			cylinderVertex[i + 5] = blue;

		}
		//Budowa scian bocznych
		GLuint vertexNumber = 1;
		odd = true;
		for (int i = 3 * walls; i < 3 * 4 * walls - 3 * walls; i += 3)
		{
			cylinderIndices[i] = vertexNumber;
			if (vertexNumber + 3 >= lastVertexIndex)
			{
				cylinderIndices[i + 2] = 2;
			}
			else{
				cylinderIndices[i + 2] = vertexNumber + 3;
			}

			if (odd){
				cylinderIndices[i + 1] = vertexNumber + 1;
				odd = false;
			}
			else
			{
				if (vertexNumber + 2 >= lastVertexIndex)
				{
					cylinderIndices[i + 1] = 1;
				}
				else
				{
					cylinderIndices[i + 1] = vertexNumber + 2;
				}
				vertexNumber += 2;
				odd = true;
			}
		}
		//---------------------------------------------
		//Budowa podstaw
		vertexNumber = 2;
		for (int i = 3 * 4 * walls - 3 * walls; i < 3 * 4 * walls; i += 3)
		{
			cylinderIndices[i] = walls * 2 + 1;
			if (vertexNumber + 2 >= lastVertexIndex)
			{
				cylinderIndices[i + 2] = 2;
			}
			else
			{
				cylinderIndices[i + 2] = vertexNumber + 2;
			}
			cylinderIndices[i + 1] = vertexNumber;
			vertexNumber += 2;
		}
		vertexNumber = 1;
		for (int i = 0; i < 3 * walls; i += 3)
		{
			cylinderIndices[i] = 0;
			if (vertexNumber + 2 >= lastVertexIndex)
			{
				cylinderIndices[i + 2] = 1;
			}
			else
			{
				cylinderIndices[i + 2] = vertexNumber + 2;
			}
			cylinderIndices[i + 1] = vertexNumber;
			vertexNumber += 2;
		}

	}

};
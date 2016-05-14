#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

struct HalfArm
{
	const GLfloat length = 0.5f;
	const GLfloat alpha = 45.0f;
	const GLfloat width = 0.5f;
	const GLfloat depth = 1.0f;
	const GLfloat height = 0.5f;
	// Set up vertex data 
	GLfloat vertices[6*16];
	GLfloat wholeSize = 0.5f*height + 0.5f*width + length*glm::cos(glm::radians(alpha)) - (-0.5f*height - 0.5f*width - length*glm::cos(glm::radians(alpha)));
	GLfloat avgX = -0.25f*width + width + length*glm::sin(glm::radians(alpha));
	GLfloat avgY = 0.5f*height + 0.25f*width + length*glm::cos(glm::radians(alpha));
	GLfloat upperPivotX;
	GLfloat upperPivotY;
	GLfloat upperPivotZ;
	GLuint indices[3*28];
	void generateVertises()
	{
		GLfloat v_pom[]={// coordinates		// color
			0.25f*width, 0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width, 0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width, -0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
			0.25f*width, -0.5f*height, -0.25f*depth, 0.5f, 0.5f, 0.5f,
			0.25f*width, 0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width, 0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width, -0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
			0.25f*width, -0.5f*height, 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - 0.5f*width - length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), -0.5f*height - 0.5f*width - length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + 0.5f*width + length*glm::cos(glm::radians(alpha)), 0.25f*depth, 0.5f, 0.5f, 0.5f,
			-0.25f*width + width + length*glm::sin(glm::radians(alpha)), 0.5f*height + 0.5f*width + length*glm::cos(glm::radians(alpha)), -0.25f*depth, 0.5f, 0.5f, 0.5f,
		};
		GLfloat i_pom[] = {
			0, 1, 2,
			0, 3, 2,
			0, 4, 7,
			0, 3, 7,
			5, 4, 7,
			5, 6, 7,
			5, 1, 2,
			5, 6, 2,
			6, 7, 9,
			6, 10, 9,
			6, 2, 11,
			6, 10, 11,
			2, 3, 8,
			2, 11, 8,
			7, 3, 8,
			7, 9, 8,
			9, 8, 11,
			9, 10, 11,
			5, 14, 13,
			5, 4, 13,
			14, 5, 1,
			14, 15, 1,
			4, 0, 12,
			4, 13, 12,
			1, 15, 12,
			1, 0, 12,
			14, 13, 12,
			14, 15, 12
		};
		for (int i = 0; i < 6*16; i++)
		{
			vertices[i] = v_pom[i];
		}
		for (int i = 0; i < 3*28; i++)
		{
			indices[i] = i_pom[i];
		}
	}
};

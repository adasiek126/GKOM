#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

struct Box{
	GLfloat length=1.0f;
	GLfloat red = 0.2f;
	GLfloat green= 0.7f;
	GLfloat blue=0.3f;
	GLfloat vertices[6 * 8];
	GLuint indices[12 * 3];
	void generateVertices()
	{
		GLfloat v_pom[] ={
				-0.25f*length, -0.25f*length, 0.25f*length, red, green, blue,
				0.25f*length, -0.25f*length, 0.25f*length, red, green, blue,
				0.25f*length, 0.25f*length, 0.25f*length, red, green, blue,
				-0.25f*length, 0.25f*length, 0.25*length, red, green, blue,
				-0.25f*length, -0.25f*length, -0.25f*length, red, green, blue,
				0.25f*length, -0.25f*length, -0.25f*length, red, green, blue,
				0.25f*length, 0.25f*length, -0.25f*length, red, green, blue,
				-0.25f*length, 0.25f*length, -0.25*length, red, green, blue,
		};
		GLuint i_pom[] = {
			0, 1, 2,
			0, 3, 2,
			1, 5, 6,
			1, 2, 6,
			5, 6, 7,
			5, 4, 7,
			4, 7, 3,
			4, 0, 3,
			3, 2, 6,
			3, 7, 6,
			0, 1, 5,
			0, 4, 5
		};
		for (int i = 0; i < 6 * 8; i++){
			vertices[i] = v_pom[i];
		}
		for (int i = 0; i < 12*3; i++){
			indices[i] = i_pom[i];
		}
	}
};
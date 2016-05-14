#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "HalfArmModel.h"
#include "Cylinder.h"
#include "Box.h"
#include "Arm.h"
#include "CylinderModel.h"
#include "BoxModel.h"
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat camera_x = 0.0f;
GLfloat camera_y = 0.0f;
GLfloat camera_closer_x = 0.0f;
GLfloat camera_closer_y = 0.0f;
GLfloat camera_closer_z = 0.0f;
GLfloat arms_angle = 0.0f;
GLfloat lowerCylinderMove = 0.0f;
Cylinder cylinderFirst;
Cylinder cylinderSecond;
Box box;
HalfArm halfArm;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP)
		camera_x += 1.0f;
	if (key == GLFW_KEY_DOWN)
		camera_x -= 1.0f;
	if (key == GLFW_KEY_LEFT)
		camera_y += 1.0f;
	if (key == GLFW_KEY_RIGHT)
		camera_y -= 1.0f;
	if (key == GLFW_KEY_KP_ADD)
	{
		if (arms_angle < 60.0f)
			arms_angle += 1.0f;
	}
	if (key == GLFW_KEY_KP_SUBTRACT)
	{
		if (arms_angle > -0.001f)
			arms_angle -= 1.0f;
	}

	if (key == GLFW_KEY_KP_8)
	{
		if (lowerCylinderMove < cylinderFirst.cylinderHeight/2)
			lowerCylinderMove += 0.01f;
	}
	if (key == GLFW_KEY_KP_2)
	{
		if (lowerCylinderMove > -0.01f)
			lowerCylinderMove -= 0.01f;
	}
	if (key == GLFW_KEY_PAGE_UP)
	{
		camera_closer_x += 0.1f;
	}
	if (key == GLFW_KEY_PAGE_DOWN)
	{
		camera_closer_x -= 0.1f;
	}
	if (key == GLFW_KEY_HOME)
	{
		camera_closer_y += 0.1f;
	}
	if (key == GLFW_KEY_END)
	{
		camera_closer_y -= 0.1f;
	}
	if (key == GLFW_KEY_INSERT)
	{
		camera_closer_z += 0.1f;
	}
	if (key == GLFW_KEY_DELETE)
	{
		camera_closer_z -= 0.1f;
	}
}
void setArmsAngle(GLfloat angle, glm::mat4x4& model, bool reverse)
{
	model = glm::translate(model,glm::vec3(halfArm.avgX, halfArm.avgY, 0.0f));
	if (!reverse)
		model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
	else
		model = glm::rotate(model, glm::radians(-angle), glm::vec3(0.0f, 0.0f, -1.0f));
	model = glm::translate(model, glm::vec3(-halfArm.avgX, -halfArm.avgY, 0.0f));
}
bool isArmHoldsBox(Box& box, glm::vec3 boxPosition, GLfloat armsAngle, GLfloat armWholeSize, glm::vec3 armsPivotPosition)
{
	GLfloat box_minY = -0.25f*box.length+boxPosition[1];
	GLfloat box_maxY = 0.25f*box.length+boxPosition[1];
	GLfloat box_minX = -0.25*box.length+boxPosition[0];
	GLfloat box_maxX = 0.25*box.length+boxPosition[0];
	GLfloat box_minZ = -0.25*box.length + boxPosition[2];
	GLfloat box_maxZ = 0.25*box.length + boxPosition[2];
	GLfloat arm_x = armsPivotPosition[0] + armWholeSize*glm::sin(glm::radians(armsAngle));
	GLfloat arm_y = armsPivotPosition[1] + armWholeSize*glm::cos(glm::radians(armsAngle));
	GLfloat arm_z = armsPivotPosition[2];
	if (arm_x >= box_minX && arm_x <box_maxX && arm_y > box_minY && arm_y < box_maxY && arm_z > box_minZ && arm_z < box_maxZ)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 03", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		glEnable(GL_DEPTH_TEST);

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_03.vert", "gl_03.frag");
		cylinderFirst.generateCylinderVertexes();
		cylinderSecond.radius = 0.35f;
		cylinderSecond.generateCylinderVertexes();
		box.length = 2.0f;
		box.generateVertices();
		halfArm.generateVertises();
		GLuint VBO, VAO, EBO, cylinderVAO, cylinderEBO, cylinderVBO, cylinderSecondVAO, cylinderSecondEBO, cylinderSecondVBO, boxVBO, boxVAO, boxEBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(halfArm.vertices), halfArm.vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(halfArm.indices), halfArm.indices, GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

		glGenVertexArrays(1, &cylinderVAO);
		glGenBuffers(1, &cylinderVBO);
		glGenBuffers(1, &cylinderEBO);
		
		glBindVertexArray(cylinderVAO);

		glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cylinderFirst.cylinderVertex), cylinderFirst.cylinderVertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cylinderFirst.cylinderIndices), cylinderFirst.cylinderIndices, GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0);

		glGenVertexArrays(1, &cylinderSecondVAO);
		glGenBuffers(1, &cylinderSecondVBO);
		glGenBuffers(1, &cylinderSecondEBO);

		glBindVertexArray(cylinderSecondVAO);

		glBindBuffer(GL_ARRAY_BUFFER, cylinderSecondVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cylinderSecond.cylinderVertex), cylinderSecond.cylinderVertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderSecondEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cylinderSecond.cylinderIndices), cylinderSecond.cylinderIndices, GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0);
		glGenVertexArrays(1, &boxVAO);
		glGenBuffers(1, &boxVBO);
		glGenBuffers(1, &boxEBO);

		glBindVertexArray(boxVAO);

		glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(box.vertices), box.vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boxEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(box.indices), box.indices, GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0);
		glm::vec3 positions[] = {
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(2.3f*halfArm.avgX, 0.0f, 0.0f),
		};
		Arm arm(&theProgram);
		CylinderModel cylinderLower(&theProgram);
		CylinderModel cylinderUpper(&theProgram, 0.35f);
		BoxModel box(&theProgram);
		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// Draw our first triangle
			theProgram.Use();


			glm::mat4 view;
			glm::mat4 projection;
			view = glm::translate(view, glm::vec3(camera_closer_x, camera_closer_y, camera_closer_z-3.0f));
			view = glm::rotate(view, glm::radians(camera_x), glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::rotate(view, glm::radians(camera_y), glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

			GLint modelLoc = glGetUniformLocation(theProgram.get_programID(), "model");
			GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");

			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			/*glBindVertexArray(VAO);
			for (int i = 0; i < 2; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, glm::vec3(0.0f, -lowerCylinderMove, 0.0f));
				setArmsAngle(arms_angle, model, i % 2);
				model = glm::translate(model, positions[i]);
				
				GLfloat angle = 180.0f*i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
				
				
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

				glDrawElements(GL_TRIANGLES, 3*28, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);*/
			arm.setPosition(glm::vec3(0.0f, -lowerCylinderMove, 0.0f));
			arm.setAngle(arms_angle);
			arm.repaint();
			glm::mat4 model;
			cylinderLower.setTransformation(glm::translate(model, glm::vec3(2.3f / 2 * halfArm.avgX, 0.8*cylinderFirst.cylinderHeight / 2 + halfArm.avgY - lowerCylinderMove, 0.0)));
			cylinderLower.display();
			model = glm::mat4();
			cylinderUpper.setTransformation(glm::translate(model, glm::vec3(2.3f / 2 * halfArm.avgX, 0.8*cylinderSecond.cylinderHeight / 2 + 0.8*cylinderFirst.cylinderHeight / 2 + halfArm.avgY, 0.0)));
			cylinderUpper.display();
			model = glm::mat4();
			box.setTransformation(glm::translate(model, glm::vec3(2.3f / 2 * halfArm.avgX, -halfArm.avgY - cylinderFirst.cylinderHeight / 2, 0.0f)));
			box.display();
			/*glBindVertexArray(cylinderVAO);
			glm::mat4 model;
			model = glm::translate(model, glm::vec3(2.3f/2*halfArm.avgX, 0.8*cylinderFirst.cylinderHeight/2+halfArm.avgY-lowerCylinderMove, 0.0));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 3 * 4 * Cylinder::walls, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glBindVertexArray(cylinderSecondVAO);
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(2.3f / 2 * halfArm.avgX, 0.8*cylinderSecond.cylinderHeight / 2 + 0.8*cylinderFirst.cylinderHeight / 2 + halfArm.avgY, 0.0));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 3 * 4 * Cylinder::walls, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glBindVertexArray(boxVAO);
			model = glm::mat4();
			
			glm::vec3 pivotPos;
			pivotPos[0] = positions[0][0];
			pivotPos[1] = positions[0][1] - lowerCylinderMove;
			pivotPos[2] = positions[0][2];
			if (isArmHoldsBox(box, glm::vec3(2.3f / 2 * halfArm.avgX, -halfArm.avgY - cylinderFirst.cylinderHeight / 2, 0.0f), arms_angle, halfArm.wholeSize, pivotPos))
			{
				model = glm::translate(model, glm::vec3(2.3f / 2 * halfArm.avgX, -halfArm.avgY - lowerCylinderMove, 0.0f));
				std::cout << "ArmHoldsBox" << std::endl;
			}
			else
			{
				model = glm::translate(model, glm::vec3(2.3f / 2 * halfArm.avgX, -halfArm.avgY - cylinderFirst.cylinderHeight / 2, 0.0f));
			}
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, 3 * 4 * Cylinder::walls, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);*/
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

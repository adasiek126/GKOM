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
#include "Holder.h"
#include "Scene.h"
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat camera_x = 0.0f;
GLfloat camera_y = 0.0f;
GLfloat camera_closer_x = 0.0f;
GLfloat camera_closer_y = 0.0f;
GLfloat camera_closer_z = 0.0f;
GLfloat arms_angle = 0.0f;
GLfloat lowerCylinderMove = 0.0f;
GLfloat arm_x = 0.0f;
GLfloat arm_z = 0.0f;
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
	if (key == GLFW_KEY_KP_6)
	{
		arm_x += 0.1;
	}
	if (key == GLFW_KEY_KP_4)
	{
		arm_x -= 0.1;
	}
	if (key == GLFW_KEY_KP_7)
	{
		arm_z += 0.1;
	}
	if (key == GLFW_KEY_KP_1)
	{
		arm_z -= 0.1;
	}
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
		Scene scene(&theProgram);
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
			
			scene.getHolder()->setHolderPosition(glm::vec3(arm_x,0.0f, arm_z));
			scene.getHolder()->setLowerCylinderOuthrusting(lowerCylinderMove);
			scene.getHolder()->setOpenig(arms_angle);
			scene.repaint();
			//holder.repaint();
			//glm::mat4 model;
			//box.setTransformation(glm::translate(model,holder.getArm()->getLowerCenter()));
			//box.display();
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat camera_x = 0.0f;
GLfloat camera_y = 0.0f;
GLfloat camera_closer_x = -1.0f;
GLfloat camera_closer_y = 0.0f;
GLfloat camera_closer_z = -2.0f;
GLfloat arms_angle = 0.0f;
GLfloat lowerCylinderMove = 0.0f;
GLfloat arm_x = 0.0f;
GLfloat arm_z = 0.0f;
Scene* scene;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
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
		if (lowerCylinderMove < scene->getHolder()->getLowerCylinder()->getHeight()/2)
			lowerCylinderMove += 0.05f;
	}
	if (key == GLFW_KEY_KP_2)
	{
		if (lowerCylinderMove > -0.01f)
			lowerCylinderMove -= 0.05f;
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
		if (arm_x < 9.0f)
			arm_x += 0.1;
	}
	if (key == GLFW_KEY_KP_4)
	{
		if (arm_x > -9.0f)
			arm_x -= 0.1;
	}
	if (key == GLFW_KEY_KP_7)
	{
		if (arm_z <9.0f)
			arm_z += 0.1;
	}
	if (key == GLFW_KEY_KP_1)
	{
		if (arm_z > -9.0f)
			arm_z -= 0.1;
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
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL Projekt", nullptr, nullptr);
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
		scene=new Scene(&theProgram);
		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
			GLint lightPosLoc = glGetUniformLocation(theProgram.get_programID(), "lightPos");
			glUniform3f(lightPosLoc, 0.0f, -10.0f, 5.0f);
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			
			scene->getHolder()->setHolderPosition(glm::vec3(arm_x,1.0f, arm_z));
			scene->getHolder()->setLowerCylinderOuthrusting(lowerCylinderMove);
			scene->getHolder()->setOpenig(arms_angle);
			scene->repaint();
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		delete scene;
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

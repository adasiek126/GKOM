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
GLfloat camera_x = 20.0f;
GLfloat camera_y = 0.0f;
GLfloat camera_closer_x = -1.0f;
GLfloat camera_closer_y = 0.0f;
GLfloat camera_closer_z = -7.0f;
GLfloat arms_angle = 0.0f;
GLfloat lowerCylinderMove = 0.0f;
GLfloat arm_x = 0.0f;
GLfloat arm_z = 0.0f;
GLfloat lightStr = 1.0f;
GLfloat light_x = -1.0f;
GLfloat light_y = -10.0f;
GLfloat light_z = 5.0f;
GLfloat acceleration = 0.005f;
GLfloat beltSpeed = 0.001f;
GLboolean beltOn = true;
Scene* scene;
struct Light {
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
Light light;
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
	if (key == GLFW_KEY_BACKSLASH)
	{
		lightStr += 0.1f;
	}
	if (key == GLFW_KEY_RIGHT_BRACKET)
	{
		lightStr -= 0.1f;
	}
	if (key == GLFW_KEY_1)
	{
		light.position[0] += 0.1f;
	}
	if (key == GLFW_KEY_2)
	{
		light.position[0] -= 0.1f;
	}
	if (key == GLFW_KEY_3)
	{
		light.position[1] += 0.1f;
	}
	if (key == GLFW_KEY_4)
	{
		light.position[1] -= 0.1f;
	}
	if (key == GLFW_KEY_5)
	{
		light.position[2] += 0.1f;
	}
	if (key == GLFW_KEY_6)
	{
		light.position[2] -= 0.1f;
	}
	if (key == GLFW_KEY_A)
	{
		light.ambient[0] += 0.1f;
		light.ambient[1] += 0.1f;
		light.ambient[2] += 0.1f;
	}
	if (key == GLFW_KEY_Z)
	{
		light.ambient[0] -= 0.1f;
		light.ambient[1] -= 0.1f;
		light.ambient[2] -= 0.1f;
	}
	if (key == GLFW_KEY_D)
	{
		light.diffuse[0] += 0.1f;
		light.diffuse[1] += 0.1f;
		light.diffuse[2] += 0.1f;
	}
	if (key == GLFW_KEY_C)
	{
		light.diffuse[0] -= 0.1f;
		light.diffuse[1] -= 0.1f;
		light.diffuse[2] -= 0.1f;
	}
	if (key == GLFW_KEY_S)
	{
		light.specular[0] += 0.1f;
		light.specular[1] += 0.1f;
		light.specular[2] += 0.1f;
	}
	if (key == GLFW_KEY_X)
	{
		light.specular[0] -= 0.1f;
		light.specular[1] -= 0.1f;
		light.specular[2] -= 0.1f;
	}
	if (key == GLFW_KEY_LEFT_SHIFT)
	{
		acceleration += 0.001f;
	}
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		if (acceleration > 0.001f)
			acceleration -= 0.001f;
	}
	if (key == GLFW_KEY_RIGHT_SHIFT)
	{
		beltSpeed += 0.001f;
	}
	if (key == GLFW_KEY_RIGHT_CONTROL)
	{
		if (beltSpeed > 0.001f)
			beltSpeed -= 0.001f;
	}
	if (key == GLFW_KEY_ENTER)
	{
		beltOn = true;
	}
	if (key == GLFW_KEY_SEMICOLON)
	{
		beltOn = false;
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
		light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
		light.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
		light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		light.position = glm::vec3(light_x, light_y, light_z);
		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		ShaderProgram theProgram("projekt.vert", "projekt.frag");
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
			GLint viewPosLoc = glGetUniformLocation(theProgram.get_programID(), "viewPos");
			GLint lightStrLoc = glGetUniformLocation(theProgram.get_programID(), "lightStrength");
			GLint lightPosLoc = glGetUniformLocation(theProgram.get_programID(), "light.position");
			GLint lightAmbientLoc = glGetUniformLocation(theProgram.get_programID(), "light.ambient");
			GLint lightDiffuseLoc = glGetUniformLocation(theProgram.get_programID(), "light.diffuse");
			GLint lightSpecularLoc = glGetUniformLocation(theProgram.get_programID(), "light.specular");
			glUniform1f(lightStrLoc, lightStr);
			glUniform3f(lightAmbientLoc, light.ambient[0], light.ambient[1], light.ambient[2]);
			glUniform3f(lightDiffuseLoc, light.diffuse[0], light.diffuse[1], light.diffuse[2]); // Let's darken the light a bit to fit the scene
			glUniform3f(lightSpecularLoc, light.specular[0], light.specular[1], light.specular[2]);
			glUniform3f(viewPosLoc, camera_closer_x, camera_closer_y, camera_closer_z - 3.0f);
			glUniform3f(lightPosLoc, light.position[0], light.position[1], light.position[2]);
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			scene->setAcceleration(acceleration);
			scene->getBelt()->setSpeed(beltSpeed);
			scene->getBelt()->setOn(beltOn);
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

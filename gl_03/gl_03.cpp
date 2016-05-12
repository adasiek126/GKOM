#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;
GLfloat camera_x = 0.0f;
GLfloat camera_y = 0.0f;
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
		const GLfloat h = 1.5f;
		const GLfloat alpha = 45.0f;
		// Set up vertex data 
		GLfloat vertices[] = {
			// coordinates		// color
			0.25f, 0.5f, -0.25f,	0.5f, 0.5f, 0.5f,
			-0.25f, 0.5f, -0.25f,	0.5f, 0.5f, 0.5f,
			-0.25f, -0.5f, -0.25f,0.5f, 0.5f, 0.5f,
			0.25f, -0.5f, -0.25f, 0.5f,0.5f,0.5f,
			0.25f, 0.5f, 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f, 0.5f, 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f, -0.5f, 0.25f, 0.5f, 0.5f, 0.5f,
			0.25f, -0.5f, 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f+h*glm::sin(glm::radians(alpha)), -0.5f-h*glm::cos(glm::radians(alpha)), -0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), -0.5f- h*glm::cos(glm::radians(alpha)), 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), - h*glm::cos(glm::radians(alpha)), 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), -h*glm::cos(glm::radians(alpha)), -0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), 0.5f + h*glm::cos(glm::radians(alpha)), -0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), 0.5f + h*glm::cos(glm::radians(alpha)), 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), 1.0f+h*glm::cos(glm::radians(alpha)), 0.25f, 0.5f, 0.5f, 0.5f,
			-0.25f + h*glm::sin(glm::radians(alpha)), 1.0f+h*glm::cos(glm::radians(alpha)), -0.25f, 0.5f, 0.5f, 0.5f,
		};

		GLuint indices[] = {
			0, 1, 2,
			2, 3, 0,
			4,5,6,
			7,6,4,
			0,4,7,
			0,7,3,
			5,1,6,
			6,1,2,
			2,8,9,
			2,9,6,
			2,3,11,
			2,8,11,
			3,7,10,
			3,11,10,
			7,10,9,
			9,6,7,
			0, 15, 12,
			1, 0, 15,
			4, 14, 15,
			0, 4, 15,
			5, 13, 14,
			5, 4, 13,
			5,13,12,
			1,12,5,
			
			
			
		};
		
		GLuint VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

		glm::vec3 positions[] = {
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(0.28f,-0.68f,0.0f),
		};

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
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			view = glm::rotate(view, glm::radians(camera_x), glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::rotate(view, glm::radians(camera_y), glm::vec3(0.0f, 1.0f, 0.0f));
			projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

			GLint modelLoc = glGetUniformLocation(theProgram.get_programID(), "model");
			GLint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");

			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glBindVertexArray(VAO);
			for (int i = 0; i < 1; i++)
			{
				glm::mat4 model;
				model = glm::translate(model, positions[i]);
				GLfloat angle = 45.0f*i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
				
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

				glDrawElements(GL_TRIANGLES, 3*24, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);

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

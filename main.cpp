#include <iostream>
#include <string>
#include <glad\glad.h> // glad before glfw!
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//my includes
#include "headers/Shader.h"
#include "headers/Pendulum.h"
#include "headers/VAO.h"
#include "headers/VBO.h"

//my functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void initialize_glfw();
void initialize_glad();

float vertices[] = {
	//x, y, z, R, G, B
	//bottom line
	0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
	-0.5f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 
	//top line
	-0.5f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f 
};


int main()
{
	std::cout << "Hello Pendulum!\n";

	initialize_glfw();
	
	//create window using glfw
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL - Pendulum", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//make context with current window
	glfwMakeContextCurrent(window);
	
	//initialize glad
	initialize_glad();

	//viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// drawing lines

// CREATE LINES
	//create VBO and load data to buffer
	VBO vbo_class(vertices, sizeof(vertices));
	//create VAO object
	VAO vao_line;
	//bind VAO object
	vao_line.BindBuffer();
	//and set attributes of vertices
	// coordinates -> location  = 0
	vao_line.SetAttribPointer(vbo_class, 0, 3, 6, 0);
	// color -> location = 1
	vao_line.SetAttribPointer(vbo_class, 1, 3, 6, 3);
	//Unbind VAO, later we can use this VAO :)
	vao_line.UnbindBuffer();
	//shader for lines
	Shader s_line("shaders//shader_line.vs", "shaders//shader_line.fs");

// CREATE PENDULUM
	// create pendulum objects
	Pendulum p1(0.02f, .2f, 70.0f);
	Pendulum p2(0.03f, 1.0f, 50.0f);
	// and shaders for them
	Shader s_p1("shaders//shader_p1.vs", "shaders//shader_p1.fs");
	Shader s_p2("shaders//shader_p2.vs", "shaders//shader_p2.fs");

	//rendering loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw lines
		s_line.use(); //use shader Program
		
		vao_line.BindBuffer();
		glDrawArrays(GL_LINE_STRIP, 0, 2);
		glDrawArrays(GL_LINE_STRIP, 2, 2);

		// draw First pendulum
		s_p1.use();
		
		//when we draw pendulum, in vertex shader we dont translate point (0.0, 1.0)
		//because this is first point of line and this point is solid

		//translate in vertex shader
		unsigned int transformLoc = glGetUniformLocation(s_p1.get_ID(), "transform");
		glm::mat4 trans = glm::mat4(1.0f);
		glm::vec3 tr_vec(p1.get_x_translate(), p1.get_y_translate(), p1.get_z_translate());
		trans = glm::translate(trans, tr_vec);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		//color of pendulum to fragment shader
		unsigned int colorLoc = glGetUniformLocation(s_p1.get_ID(), "color");
		glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 0.0f);

		p1.calculate_new_pos(glfwGetTime());
		p1.draw_pendulum();

		//Second pendulum
		s_p2.use();		
		transformLoc = glGetUniformLocation(s_p2.get_ID(), "transform");
		trans = glm::mat4(1.0f);
		tr_vec = glm::vec3(p2.get_x_translate(), p2.get_y_translate(), p2.get_z_translate());
		trans = glm::translate(trans, tr_vec);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		colorLoc = glGetUniformLocation(s_p2.get_ID(), "color");
		color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 0.0f);

		p2.calculate_new_pos(glfwGetTime());
		p2.draw_pendulum();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void initialize_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void initialize_glad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		getchar();
		exit (-1);
	}
}
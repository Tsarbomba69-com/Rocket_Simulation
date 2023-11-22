#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "Shader.h"

const unsigned short OPENGL_MAJOR_VERSION = 4;
const unsigned short OPENGL_MINOR_VERSION = 6;

typedef struct Color {
	float r;
	float g;
	float b;
	float a;
} Color;

typedef struct Window {
	const unsigned int width;
	const unsigned int height;
	const char* title;
	Color background;
} Window;


int main() {
	int glfw = glfwInit();

	if (glfw == GLFW_FALSE) {
		fprintf(stderr, "[ERROR]: An error occurred. Error code: %d\n", glfw);
		return EXIT_FAILURE;
	}

	Window winConfig = { 800, 800, "Rocket Simulation", { .37f, .36f, .36f, 1 } };
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(winConfig.width, winConfig.height, winConfig.title, NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "[ERROR]: Could not create a window instance");
		glfwTerminate();
		return EXIT_FAILURE;
	}


	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, winConfig.width, winConfig.height);
	GLfloat vertices[] = {
		-.5f, 0, .2f,
		-.3f, 1, .2f,
		-.4f, 0, .3f,
		.5f, 0, -.2f,
		.3f, -1, -.2f,
		.4f, 0, -.3f,
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};
	Shader shaderProgram("default.vert", "default.frag");
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	// Generate the VAO, VBO, and EBO with only 1 object each
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(winConfig.background.r,
			winConfig.background.g,
			winConfig.background.b,
			winConfig.background.a);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram.ID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteShader(shaderProgram.ID);
	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
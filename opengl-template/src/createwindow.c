
#include "headers/openglutils.h"

#define VAONUM 1
#define VBONUM 2

GLuint shaderProgram;
GLuint vao[VAONUM];
GLuint vbo[VBONUM];

GLuint createShaderProgram () {
	const GLchar *vertexShaderSource = readShader("shaders/vertexShader.glsl");
	const GLchar *fragmentShaderSource = readShader("shaders/fragmentShader.glsl");

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	printShaderLog(vertexShader);
	printShaderLog(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	printProgramLog(shaderProgram);

	return shaderProgram;
}

/////////////////////////////////////////////
				 //Init
/////////////////////////////////////////////
void initialize () {
	shaderProgram = createShaderProgram();
	glGenVertexArrays(VAONUM, vao);
	glBindVertexArray(vao[0]);
	glPointSize(6.0f);
}

void terminate (GLFWwindow *window) {
	glfwDestroyWindow(window);
	glfwTerminate();
}

/////////////////////////////////////////////
				 //Update
/////////////////////////////////////////////
void update (GLFWwindow *window) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);

	glDrawArrays(GL_POINTS, 0, 1);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

/////////////////////////////////////////////
			  //Create Window
/////////////////////////////////////////////
int createWindow (int width, int height, char *title, bool resizable) {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: couldn't start GLFW");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	if (!resizable) {
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}
	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(window);

	if (((GLenum) glewInit()) != GLEW_OK) {
		fprintf(stderr, "ERROR: couldn't start GLEW");
		terminate(window);
		return -1;
	}

	initialize();
	do {
		update(window);
	} while (!glfwWindowShouldClose(window));

	terminate(window);
	return 0;
}


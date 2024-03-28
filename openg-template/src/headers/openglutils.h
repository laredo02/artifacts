
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int createWindow(int width, int height, char *title, bool resizable);
char *readShader(char *fileName);
void printShaderLog(GLuint shader);
void printProgramLog(GLint shaderProgram);


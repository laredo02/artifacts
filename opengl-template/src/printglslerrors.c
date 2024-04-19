
#include "headers/openglutils.h"

void printShaderLog(GLuint shader)
{
	int length;
	char *shaderLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 0) {
		shaderLog = (char*) malloc(length);
		glGetShaderInfoLog(shader, length, NULL, shaderLog);
		printf("%s", shaderLog);
		free(shaderLog);
	}
}

void printProgramLog(GLint shaderProgram)
{
	int length;
	char *shaderProgramLog;
	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
	if (length > 0) {
		shaderProgramLog = (char*) malloc(length);
		glGetShaderInfoLog(shaderProgram, length, NULL, shaderProgramLog);
		printf("%s", shaderProgramLog);
	}
	free(shaderProgramLog);
}


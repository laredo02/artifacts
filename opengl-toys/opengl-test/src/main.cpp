
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <chrono>
#include <cmath>

#include "../include/OpenGLManager.hpp"

void handleInputEvents (GLFWwindow *);

void computePointPosition (float x, float y) {

}

int main (const int argc, const char *argv[]) {
  glge::OpenGLManager opengl;
  
  if (opengl.startGLFW("GraphicsEngine", 640, 480))
    exit(EXIT_FAILURE);
  if (opengl.startGLAD())
    exit(EXIT_FAILURE);
  opengl.printSystemInfo();
  if (opengl.autoCompileShaders("shaders"))
    exit(EXIT_FAILURE);
  opengl.createShaderProgram();

  

  const float vertices[][4] = {{0.0f, 0.75f, 0.0f, 1.0f}, {0.75f, -0.75f, 0.0f, 1.0f}, {-0.75f, -0.75f, 0.0f, 1.0f},
			       {1.0f, 0.0f,  0.0f, 1.0f}, {0.0f,   1.0f,  0.0f, 1.0f}, { 0.0f,   0.0f,  1.0f, 1.0f}};

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *) (sizeof(float)*4*3));
  

  
  GLint positionOffset =  glGetUniformLocation(opengl.getShaderProgram(), "positionOffset");
  GLint colorOffset = glGetUniformLocation(opengl.getShaderProgram(), "colorOffset");
  GLint time = glGetUniformLocation(opengl.getShaderProgram(), "time");

  glUseProgram(opengl.getShaderProgram());
  
  while (!glfwWindowShouldClose(opengl.getWindow())) {
    
    float red = (float) cos(glfwGetTime()+0)*0.5+0.5,
      green = (float) cos(glfwGetTime()+M_PI/4)*0.5+0.5,
      blue = (float) cos(glfwGetTime()+M_PI/2)*0.5+0.5;
    const GLfloat color[] = {red, green, blue, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);

    float currentTime = (float) glfwGetTime();
    glUniform1f(time, currentTime);
    glUniform4f(colorOffset, green, blue, red, 1.0f);
    glUniform4f(positionOffset, (float) sin(currentTime)*0.3f, (float) cos(currentTime)*0.3f, 0.0f, 0.0f);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(opengl.getWindow());
    glfwPollEvents();

  }


  
  glDeleteVertexArrays(1, &vao); 
  glDeleteBuffers(2, &vbo);
  
  return 0;
}

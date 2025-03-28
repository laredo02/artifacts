
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void framebuffer_size_callback(GLFWwindow *, int, int);
void handleInputEvents(GLFWwindow *);

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS)
    std::cout << (char) key << std::endl;
}

class OpenGLManager {
private:
  GLFWwindow *window;
public:
  friend int main();
  int startGLFW (int width, int height, const char *name) {
    int ret = 0;
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == nullptr) {
      std::cout << "Failed to initialize GLFW" << std::endl;
      ret = 1;
      glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, KeyCallback);
    return ret;
  }
  int startGLAD () {
    int ret = 0;
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      ret = 2;
    }
    return ret;
  }
  ~OpenGLManager() {
    glfwTerminate();
  }
  
};

int main () {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  OpenGLManager opengl;
  opengl.startGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL");
  opengl.startGLAD();

  while (!glfwWindowShouldClose(opengl.window)) {
    handleInputEvents(opengl.window);
    glfwSwapBuffers(opengl.window);
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  return 0;
}

void handleInputEvents (GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS | glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback (GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

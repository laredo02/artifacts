

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

const char *vertexShaderSource =  "#version 460 core\n"
  "layout (location = 0) in vec4 position;\n"
  "layout (location = 1) in vec4 color;\n"
  "smooth out vec4 theColor;\n"
  "uniform vec4 offset;\n"
  "void main () {\n"
  "gl_Position = position + offset;\n"
  "theColor = color;\n"
  "}\n\0";
const char *fragmentShaderSource = "#version 460 core\n"
  "smooth in vec4 theColor;"
  "out vec4 outputColor;\n"
  "void main () {\n"
  "outputColor = theColor;\n"
  "}\n\0";

void framebuffer_size_callback(GLFWwindow *, int, int);
void handleInputEvents(GLFWwindow *);
void KeyCallback(GLFWwindow *, int, int, int, int);
char *readShader(const char *);

class OpenGLManager {
private:
  GLFWwindow *window;
  unsigned int vertexShader, fragmentShader, shaderProgram;
  std::vector<unsigned int> shaderVector;
public:
  friend int main();
  int startGLFW(int, int, const char *);
  int startGLAD();
  int compileShaders(const char *, const char *);
  ~OpenGLManager();
};

int OpenGLManager::startGLFW (int width, int height, const char *name) {
    int ret = 0;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

int OpenGLManager::startGLAD () {
    int ret = 0;
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      ret = 2;
    }
    return ret;
}

int OpenGLManager::compileShaders (const char *vertexShaderSource, const char *fragmentShaderSource) {
  int ret = 0, vertexStatus = 0, fragmentStatus = 0;
  char vertexShaderLog[1024], fragmentShaderLog[1024];
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);
  if (!vertexStatus) {
    glGetShaderInfoLog(vertexShader, sizeof(vertexShaderLog)/sizeof(const char), NULL, vertexShaderLog);
    std::cout << "ERROR: Vertex Shader compilation failed.\n" << vertexShaderLog << std::endl;
  } else {
    std::cout << "Vertex Shader compilation successful!" << std::endl;
  }
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);
  if (!fragmentStatus) {
    glGetShaderInfoLog(fragmentShader, sizeof(fragmentShaderLog)/sizeof(const char), NULL, fragmentShaderLog);
    std::cout << "ERROR: Fragment Shader compilation failed.\n" << fragmentShaderLog << std::endl;
  } else {
    std::cout << "Fragment Shader compilation successful!" << std::endl;
  }
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return 0;
}

OpenGLManager::~OpenGLManager() {
  glDeleteProgram(shaderProgram);
  std::cout << "Shader program deleted successfully" << std::endl;
  glfwTerminate();
  std::cout << "GLFW Terminated" << std::endl;
}

int main () {

  OpenGLManager opengl;
  opengl.startGLFW(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL");
  opengl.startGLAD();
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  opengl.compileShaders(vertexShaderSource, fragmentShaderSource);

  float vertices[] = {
		      -0.5f, -0.5f, 0.0f, 1.0f,
		      0.5f, 0.5f, 0.0f, 1.0f,
		      0.5f, -0.5f, 0.0f, 1.0f,

		      1.0f, 0.0f, 0.0f, 1.0f,
		      0.0f, 1.0f, 0.0f, 1.0f,
		      0.0f, 0.0f, 1.0f, 1.0f
  };

  unsigned int vertexArrayObject;
  glGenVertexArrays(1, &vertexArrayObject);
  glBindVertexArray(vertexArrayObject);
  
  unsigned int vertexBufferObject;
  glGenBuffers(1, &vertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *) 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *) (4*4*3));
  
  glBindVertexArray(0);

  unsigned int offsetUniformLocation = glGetUniformLocation(opengl.shaderProgram, "offset");
  float offsetz = 0.0f;

  double averageFps;
  auto last = std::chrono::steady_clock::now();
  while (!glfwWindowShouldClose(opengl.window)) {
    handleInputEvents(opengl.window);
 
    glClearColor(0.5f, 0.05f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vertexArrayObject);
    glUseProgram(opengl.shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwSwapBuffers(opengl.window);
    glfwPollEvents();
    
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = now-last;
    auto fps = 1/diff.count();
    std::cout << fps << " fps" << std::endl;
    averageFps = (averageFps+fps)/2;
    last = now;
  }
  std::cout << "Average FPS: " << averageFps << std::endl;


  
  glDeleteBuffers(1, &vertexBufferObject);
  return 0;
}

char *readShader (const char *filename) {
  return nullptr;
}

void handleInputEvents (GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS | glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback (GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS)
    std::cout << (char) key << std::endl;
}

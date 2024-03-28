
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <regex>

#include "../../include/OpenGLManager.hpp"

void glge::OpenGLManager::frameBufferSizeCallback (GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void glge::OpenGLManager::keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS)
    cout << (char) key << endl;
  if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_ENTER || key == GLFW_KEY_Q) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

int glge::OpenGLManager::startGLFW (const char *window_name, int width, int height) {
  int ret = 0;
  if (!glfwInit()) {
    std::cout << "\nERROR: Failed to initialize GLFW\n" << std::endl;
    ret = 1;
  } else {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, window_name, NULL, NULL);
    if (window == nullptr) {
      std::cout << "\nERROR: Failed to create GLFWwindow *\n" << std::endl;
      ret = 2;
      glfwTerminate();
    } else
      std::cout << "\nGLFW Initialized successfully!!" << std::endl;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetKeyCallback(window, keyCallback);
  }
  return ret;
}

int glge::OpenGLManager::startGLAD () {
  int ret = 0;
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "ERROR: Failed to initialize GLAD\n";
    ret = 3;
  } else
    std::cout << "GLAD Initialized successfully!!\n" << std::endl;
  return ret;
}

void glge::OpenGLManager::printSystemInfo () {
  cout << "===========================" << endl;
  cout << "        System Info        " << endl;
  cout << "===========================" << endl;
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n' << std::endl;
}

std::string glge::OpenGLManager::readShader (std::string shaderFileLocation) {
  std::string str;
  std::ifstream ifs(shaderFileLocation);
  std::stringstream ss;
  while (getline(ifs, str))
    ss << str << std::endl;
  ifs.close();
  return ss.str();
}

/**
 * DESCRIPTION: Compiles the shaders with .vertex and .fragment extension located at shadersDirectory, binds vertexShader and fragmentShader to valid shader IDs.
 * shadersDirectory: dir where shaders are supposedly located
 * RETURNS: non-cero value if an error occurs.
 */
GLuint glge::OpenGLManager::autoCompileShaders (string shadersDirectory) {
  GLuint ret = 0;
  shadersDirectory += "/";
  system(("ls " + shadersDirectory + " > .ls_shader_dir.tmp").c_str());
  ifstream in {".ls_shader_dir.tmp"};
  regex vertexPattern {R"(\w*\.vertex$)"}, fragmentPattern {R"(\w*\.fragment$)"};
  smatch matches;
  for (string line; getline(in, line); ) {
    if (regex_search(line, matches, vertexPattern))
      vertexShaderSource = readShader(shadersDirectory + line);
    if (regex_search(line, matches, fragmentPattern))
      fragmentShaderSource = readShader(shadersDirectory + line);
  }
  in.close();
  
  cout << "===========================" << endl;
  cout << "   Current Vertex Shader   " << endl;
  cout << "===========================" << endl;
  stringstream vss {vertexShaderSource};
  string line;
  for (int lineno = 0; getline(vss, line); lineno++)
    cout << lineno << "\t" << line << endl;

  vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);

  cout << "===========================" << endl;
  cout << "  Current Fragment Shader  " << endl;
  cout << "===========================" << endl;
  stringstream fss {fragmentShaderSource};
  for (int lineno = 0; getline(fss, line); lineno++)
    cout << lineno << "\t" << line << endl;

  fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

  ret = !(vertexShader && fragmentShader);
  if (ret)
    cout << "ERROR: Shader autocompilation failed" << endl;

  system("rm .ls_shader_dir.tmp");
  return ret;
}

/**
 * DESCRIPTION: Compile any shader
 * shaderSource: shader source code
 * TYPE: type of shader (GL_VERTEX_SHADER GL_TESS_CONTROL_SHADER GL_TESS_EVALUATION_SHADER GL_GEOMETRY_SHADER GL_FRAGMENT_SHADER GL_COMPUTE_SHADER)
 * RETURNS the shader reference ID or whatever it's called. If the shader doesn't compile it returns 0
 */
GLuint glge::OpenGLManager::compileShader (const string shaderSource, const unsigned int TYPE) {
  GLuint shader = glCreateShader(TYPE);
  int compiled = 0;
  char compileLog[1024];
  const char *cShaderSource = shaderSource.c_str();
  glShaderSource(shader, 1, &cShaderSource, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    glGetShaderInfoLog(shader, sizeof(compileLog)/sizeof(char), NULL, compileLog);
    glDeleteShader(shader);
    shader = 0;
    cout << "ERROR: shader compilation failed\n" << compileLog << endl;
  } else
    cout << "Shader compiled succesfully!" << endl;
  return shader;
}

void glge::OpenGLManager::createShaderProgram () {
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

GLFWwindow *glge::OpenGLManager::getWindow () const {
  return window;
}

GLuint glge::OpenGLManager::getVertexShader () const {
  return vertexShader;
}

GLuint glge::OpenGLManager::getFragmentShader () const {
  return fragmentShader;
}

GLuint glge::OpenGLManager::getShaderProgram () const {
  return shaderProgram;
}

// Terminate GLFW at exit
glge::OpenGLManager::~OpenGLManager () {
  glDeleteProgram(shaderProgram);
  glfwTerminate();
  std::cout << "\nGLFW Terminated\n" << std::endl;
}

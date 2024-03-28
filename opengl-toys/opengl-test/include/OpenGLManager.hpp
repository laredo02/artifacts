
#include <vector>
#include <string>

#include <GLFW/glfw3.h>

namespace glge {
  using namespace std;
  class OpenGLManager {
    std::string vertexShaderSource, fragmentShaderSource;
    GLuint vertexShader, fragmentShader, shaderProgram;
    GLFWwindow *window;
    static void frameBufferSizeCallback(GLFWwindow *, int, int);
    static void keyCallback(GLFWwindow *, int, int, int, int);
    std::string readShader(std::string);
  public:
    int startGLFW(const char *, int, int);
    int startGLAD( void );
    void printSystemInfo( void );
    GLuint autoCompileShaders(std::string); // weird function
    GLuint compileShader(const string, const unsigned int);
    void createShaderProgram( void );
    GLFWwindow *getWindow( void ) const;
    GLuint getVertexShader( void ) const;
    GLuint getFragmentShader( void ) const;
    GLuint getShaderProgram( void ) const;
    ~OpenGLManager();
  };
};


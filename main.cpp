#include <iostream>
#include <cmath>
#include<string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std; 

GLuint load_shader(const string&path,GLenum shader_type){
    fstream file(path);
    string sourceCode = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    const char *sourceCodeCStr = sourceCode.c_str();

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &sourceCodeCStr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(!status){
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *logStr = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, logStr);

        cerr << "ERROR IN " << path << endl;
        cerr << logStr << endl;
        
        delete[] logStr;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

int main()
{
    if(!glfwInit()){
        cerr << "Failed to initialize GLFW" << endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);

    if(!window){
        cerr << "Failed to create a window" << endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window); // It knows in glad that it will load the functions of openGL to the created window for the given openGL context major, and minor

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // It takes the function it needs in loading
    {
        std::cerr << "Failed to load procedures" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    GLuint program = glCreateProgram();
    GLuint vs = load_shader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
    GLuint fs = load_shader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);

    GLuint time_loc = glGetUniformLocation(program, "time");

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT); // To delete every frame

        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUniform1f(time_loc, time);

        glfwSwapBuffers(window); // To swap the back, and front buffers
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
}

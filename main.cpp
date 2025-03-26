#include <iostream>
#include <cmath>
#include<string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

struct Vec3{
    float x, y, z;
};

struct Color{
    uint8_t r, g, b, a;
};

struct Vertex{
    Vec3 position;
    Color color;
};

Vertex vertices[3] = {
    {{-0.5, -0.5, 0.0}, {255, 0, 0, 255}}, {{0.5, -0.5, 0.0}, {0, 255, 0, 255}}, {{-0.5, 0.5, 0.0}, {0, 0, 255, 255}}};

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
        cerr << "Failed to load procedures" << endl;
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

    GLuint vertex_buffer;
    GLuint vertex_array;

    GLuint position_loc = glGetAttribLocation(program, "position");
    GLuint color_loc = glGetAttribLocation(program, "color");
    GLuint time_loc = glGetUniformLocation(program, "time");

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glEnableVertexAttribArray(position_loc);
    glEnableVertexAttribArray(color_loc);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, false, sizeof(Vertex), (void *)0);
    glVertexAttribPointer(color_loc, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT); // To delete every frame

        glUseProgram(program);
        glBindVertexArray(vertex_array);

        glUniform1f(time_loc, time);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUniform1f(time_loc, time + 1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window); // To swap the back, and front buffers
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
}

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

struct Vec3
{
    float x, y, z;
};

struct Color
{
    uint8_t r, g, b, a;
};

struct Vertex
{
    Vec3 position;
    Color color;
};

uint16_t elements[6] = {0, 1, 2, 3, 1, 2};

Vertex vertices[4] = {
    {{-0.5, -0.5, 0.0}, {255, 0, 0, 255}},
    {{0.5, -0.5, 0.0}, {0, 255, 0, 255}},
    {{-0.5, 0.5, 0.0}, {0, 0, 255, 255}},
    {{0.5, 0.5, 0.0}, {255, 255, 0, 255}},
};

GLuint load_shader(const string &path, GLenum shader_type)
{
    fstream file(path);
    string sourceCode = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    const char *sourceCodeCStr = sourceCode.c_str();

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &sourceCodeCStr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status)
    {
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
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);

    if (!window)
    {
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
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 64 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    GLuint element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint16_t), elements, GL_STATIC_DRAW);

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // ************************ Start binding to the vertex array ************************

    GLuint position_loc = 0;                                                            // glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(position_loc);                                            // The vertex array knows that the vertex shader would read at the location defined
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, false, sizeof(Vertex), (void *)0); // The vertex array knows that for the location defined, it will read the value needed from the vertex buffer, with the defined size

    GLuint color_loc = 1; // glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(color_loc);
    glVertexAttribPointer(color_loc, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void *)offsetof(Vertex, color));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer); // We determine that that buffer would be the source of drawing when the vertex array would search for
    glBindVertexArray(0);

    // ************************ End binding to the vertex array ************************

    GLuint time_loc = glGetUniformLocation(program, "time");

    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT); // To delete every frame

        glUseProgram(program);
        glBindVertexArray(vertex_array);

        glUniform1f(time_loc, time);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void *)0);

        // glUniform1f(time_loc, time + 1);
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window); // To swap the back, and front buffers
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
}

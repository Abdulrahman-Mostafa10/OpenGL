#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

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

    
    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();
        glClearColor(0.5 * sinf(time) + 0.5, 0.5 * sinf(time + 1) + 0.5, 0.5 * sinf(time + 2) + 0.5, 1.0); // Draw the window with a sine function
        glClear(GL_COLOR_BUFFER_BIT); // To delete every frame
        glfwSwapBuffers(window);      // To swap the back, and front buffers
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

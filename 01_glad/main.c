#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

int main() {
    
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    return 0;
}

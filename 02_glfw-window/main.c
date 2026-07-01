#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

static void error_callback(int error_code, const char* description);

int main() {

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
	return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const char* title = "OpenGL Education";
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
    if (!window) {
	glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);


    if(!gladLoadGL(glfwGetProcAddress)) {
	glfwDestroyWindow(window);
	glfwTerminate();
	return -1;
    }
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window)) {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	glfwPollEvents();
    }

    // clean up memory
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

static void error_callback(int error_code, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

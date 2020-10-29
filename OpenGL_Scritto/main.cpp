#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {

    //Inzializiamo GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// utilizioamo il core profile

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#endif 

    //Finestra

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ProvaOpen Gl a mano", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    //glad: carichiamo tutti i ponter funzione 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD";
            return -1;
    }

}
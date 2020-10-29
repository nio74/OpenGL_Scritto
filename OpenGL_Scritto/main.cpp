#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //glad: carichiamo tutti i ponter funzione 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" <<std::endl;
            return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);//manda in funzione la finestra
        glfwPollEvents();//controlla gli eventi
        
    }

    float vertices[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,0.5f,0.0f,
        0.0f,0.5,0.0f
    }

    glfwTerminate();
    return 0;

}


//glfw: ogni colta che la dimensione delle dimensioni della finestra cambia(dall'utente o dal OS)
//      questa funzione callback viene eseguita
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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

    // build and compile our shader program
    // ------------------------------------
     // vertex shader

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//dichiariamo il tipo vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// dichiariamo la sorgente
    glCompileShader(vertexShader);//compiliamo il shader


    //controlliamo se la compilazione è andata a buon fine

    int success;
    char infolog[512];// creiamo un contenitore per i messaggi di log
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//richiediamo lo stato dello shader

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);

        std::cout << "ERROR: Cmpoilazione shader fallita" << infolog << std::endl;

    }

    

    float vertices[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,0.5f,0.0f,
        0.0f,0.5,0.0f
    };

    unsigned int VBO;//ID BUffer
    glGenBuffers(1, &VBO);//genera l'oggetto buffer
    glBindBuffer(GL_ARRAY_BUFFER,VBO);//Associa i dati e specifica il tipo in questo caso un ARRAY_BUFFER

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//è una funzione specificatamente mirata per copiare i dati definiti dall'utente nel buffer attualmente associato


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


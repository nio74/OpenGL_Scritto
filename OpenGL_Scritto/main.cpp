#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;
/**/

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
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

    //while (!glfwWindowShouldClose(window))
    //{
    //    glfwSwapBuffers(window);//manda in funzione la finestra
    //    glfwPollEvents();//controlla gli eventi
    //    
    //}

    // build and compile our shader program
    // ------------------------------------
     // vertex shader

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//dichiariamo il tipo vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// dichiariamo la sorgente
    glCompileShader(vertexShader);//compiliamo il shader


    //controlliamo se la compilazione è andata a buon fine

    int success;
    char infoLog[512];// creiamo un contenitore per i messaggi di log
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//richiediamo lo stato dello shader

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

        std::cout << "ERROR: Cmpoilazione shader fallita" << infoLog << std::endl;

    }
    //FragmentShader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//diciamo che tipo di shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Controlliamo se è andata a buon fine la compilazine
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
            << std::endl;
    }

    //Creiamo il shader Link vado a unire il vertexShader e il fragmentShader

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);// attacchiamo i shader
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);//Ora linkiamo il programma


    //controlliamo se il link è andato a buon fine
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog
            << std::endl;
    }


    //Eliminiamo gli shader dopo averli usati
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    unsigned int VBO, VAO;//ID BUffer
    glGenVertexArrays(1,&VAO);//Specifico il vertexArray
    glGenBuffers(1, &VBO);//genera l'oggetto buffer
    //associare prima il Vertex Array Object, quindi associare e impostare i buffer dei vertici, quindi configurare gli attributi dei vertici.
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);//Associa i dati e specifica il tipo in questo caso un ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//è una funzione specificatamente mirata per copiare i dati definiti dall'utente nel buffer attualmente associato
  
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAO);// visto che abbiamo un solo VAO non è necessario vincolarlo ogni volta, ma lo faremo per mantenere le cose un po 'più organizzate


    //Render loop

    while (!glfwWindowShouldClose(window))
    {
        //input tastiera

        processInput(window);

        //render color
        glClearColor(0.0f, 0.0f, 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //disegnamo il nostro triangolo

        glUseProgram(shaderProgram);

        //aggiorniamo lo shader uniform

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        



        glDrawArrays(GL_TRIANGLES, 0, 3);
                               // glBindVertexArray (0); // non è necessario svincolarlo ogni volta

        // controlla e chiama eventi e scambia i buffer

        glfwSwapBuffers(window);
        glfwPollEvents();

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
//controlliamo i processi di input premuti dalla tastiera
//-----------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE)== GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


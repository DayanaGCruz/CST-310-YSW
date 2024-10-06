
/* Dayana Gonzalez Cruz & Yulissa Valencia
CST-310: Computer Graphcics
Project 4: Your Surrounding World
Oct. 6, 2024
TR1100A Dr. Citro
*/

/* Utilizes model loading resource programs from the textbook's online copy
Link: https://learnopengl.com/Model-Loading/Assimp */

/* OPENGL Function Loading Lib.*/
#include <glad/glad.h> /* For loading OpenGL functions */
#include <GLFW/glfw3.h> /* General OpenGL window lib */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> /* For transformations like rotation, scaling, etc. */
#include <glm/gtc/type_ptr.hpp> /* To pass matrices as shader uniforms */
#include "../include/model.h"
#include "../include/shader.h"

#include <iostream> 
#include <filesystem>
#include <string>


/* Global Scope Variable Declarations */
GLuint windowWidth = 800;
GLuint windowHeight = 600;
GLuint program = 0;

glm::vec3 cameraPosition = (glm::vec3(0.0f, 0.0f, 3.0f));

/* Function Declarations */
void framebuffer_size_callback(GLFWwindow* window, int windowWidth, int windowHeight);
void processInput(GLFWwindow *window);


int main(void) 
{   
    std::cout << "Project 4: Your Surrounding World" << std::endl;
    /* Initialize GLFW */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    /* Window properties */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); /* Using OPENGL Context Ver. 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "Set window configurations!" << std::endl;
    /* Create a Window */
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Project 4: Your Surrounding World", NULL, NULL);
    if (window == NULL) {
        std::cout << "GLFW | Window creation failure" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Created window!" << std::endl;
    glfwMakeContextCurrent(window);
    std::cout << "Made context!" << std::endl;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); /* Adjust viewport when window resizes */

    std::cout << "Loading GLAD..." << std::endl;
     /* Load OpenGL function pointers using GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD | Initialization failed" << std::endl;
        return -1;
    }
    std::cout << "Loaded GLAD!" << std::endl;

    stbi_set_flip_vertically_on_load(true); /* Flip loaded texture's on y-axis */
    glEnable(GL_DEPTH_TEST); /* Enable depth testing */
   std::cout << "Loading shader..." << std::endl;
   Shader shader("shader.vs", "shader.fs");
   std::cout << "Loaded shader!" << std::endl;
   std::string path = std::filesystem::path("../resources/objects/room.obj").string();
   std::cout << "Loading model..." << std::endl;
   Model modelObj(path);
   std::cout << "Loaded model!" << std::endl;
    
    /* Render loop */
    while (!glfwWindowShouldClose(window)) 
    {      
        /* Input */
        processInput(window);

        /* Rendering */
        glClearColor(0.3f, 0.0f, 0.3f, 1.0f); /* Background color */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Activate shader */
        shader.use();

       glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
       glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
       shader.setMat4("projection", projection);
       shader.setMat4("view", view);
       
       /*Render loaded model*/
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setMat4("model", model);
        modelObj.Draw(shader);

        /* Swap buffers and poll IO events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /* Clean up resources */
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int windowWidth, int windowHeight) 
{
    glViewport(0, 0, windowWidth, windowHeight);
}

void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

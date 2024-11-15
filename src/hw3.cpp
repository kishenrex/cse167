#include "hw3.h"
#include "3rdparty/glad.h" // needs to be included before GLFW!
#include "3rdparty/glfw/include/GLFW/glfw3.h"
#include "hw3_scenes.h"
#include "3rdparty/glm/glm.hpp"
#include "3rdparty/glm/gtc/matrix_transform.hpp"
#include "3rdparty/glm/gtc/type_ptr.hpp"

using namespace hw3;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



void hw_3_1(const std::vector<std::string> &params) {
    // HW 3.1: Open a window using GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        // return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // return -1;
    }  

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    //render loop
    while(!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //rendering
        glClearColor(0.6f, 0.0f, 0.9f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);


        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 
    glfwTerminate();

    
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
        "gl_Position = transform * vec4(aPos, 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void hw_3_2(const std::vector<std::string> &params) {
    // HW 3.2: Render a single 2D triangle
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        
    }  

    //creating the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //setup to check if compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //creating the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //checking for frag shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //linking shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //shaders not needed anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

   

    //setting up vertices
    // float vertices[] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  // bottom left
    //     -0.5f,  0.5f, 0.0f   // top left 
    // };

    // unsigned int indices[] = {  // note that we start from 0!
    //     0, 1, 3,  // first Triangle
    //     1, 2, 3   // second Triangle
    // };

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);

    //creating the buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  


    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");


    


    //render loop
    while(!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //rendering
        glClearColor(0.6f, 0.0f, 0.9f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, 
            (float)glfwGetTime(), // Use glfwGetTime() for time-based rotation
            glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the z-axis

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glUseProgram(shaderProgram); //needed?
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    

    glfwTerminate();


}

const char *vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "uniform mat4 projection;\n"
    "uniform mat4 view;\n"
    "uniform mat4 model;\n" 
    "void main()\n"
    "{\n"
        "gl_Position = vec4(aPos, 1.0);\n"
        "ourColor = aColor;\n"
    "}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";

void hw_3_3(const std::vector<std::string> &params) {
    // HW 3.3: Render a scene
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
    std::cout << "local" << std::endl;


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        
    }  

    //creating the vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader);
    
    //setup to check if compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //creating the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader);

    //checking for frag shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //linking shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //shaders not needed anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    //setting up vertices

    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f,  0.5f, 0.0f
    // };  
    std::cout << "scene.meshes.size = " << scene.meshes.size() << std::endl;
    std::vector<int> VAOs;

    for (const TriangleMesh &mesh : scene.meshes) {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);  
        glBindVertexArray(VAO);
        VAOs.push_back(VAO);

        //creating the vertices buffer
        unsigned int VBO_vertex;
        glGenBuffers(1, &VBO_vertex); 
        glBindBuffer(GL_ARRAY_BUFFER, VBO_vertex);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices), mesh.vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
        glEnableVertexAttribArray(0);

        //creating the vertices color buffer
        unsigned int VBO_color;
        glGenBuffers(1, &VBO_color); 
        glBindBuffer(GL_ARRAY_BUFFER, VBO_color);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertex_colors), mesh.vertex_colors.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 
        glEnableVertexAttribArray(1); 
        

        // Create EBO
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.faces), mesh.faces.data(), GL_STATIC_DRAW);
        
    }


    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);    

    // unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection"); 
    // unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    // unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

    //render loop
    while(!glfwWindowShouldClose(window)) {
        //input
        processInput(window);

        //rendering
        glClearColor(0.6f, 0.0f, 0.9f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT); 

        // glm::mat4 projection = glm::mat4(1.0f);
        // projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); //use perspective --> can 1/tan from scene

        // glm::mat4 view = glm::mat4(1.0f);
        // view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f)); //inverse of cam to world matrix in scece

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 

        glUseProgram(shaderProgram);

        for (int i = 0; i < scene.meshes.size(); i++) {
            // glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection)); 
            // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, scene.meshes[i].model_matrix.ptr());
            glBindVertexArray(VAOs[i]);
            glDrawElements(GL_TRIANGLES, 3 * scene.meshes[i].faces.size(), GL_UNSIGNED_INT, 0); 
        } 

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 

    glfwTerminate();


}

void hw_3_4(const std::vector<std::string> &params) {
    // HW 3.4: Render a scene with lighting
    if (params.size() == 0) {
        return;
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;
}
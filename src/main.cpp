#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "serialPort.h"

#include "utils/arduinoController.h"
#include "utils/fileUtils.h"

const char* portName = "\\\\.\\COM3"; // If your device is on COM4
ArduinoController arduino(portName);

glm::mat4 model = glm::mat4(1.0f); // Identity matrix for model transformation
glm::mat4 view = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 10.0f), // Camera position
    glm::vec3(0.0f, 0.0f, 0.0f), // Look at the origin
    glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
);
glm::mat4 projection = glm::perspective(
    glm::radians(45.0f), // Field of view
    800.0f / 600.0f,     // Aspect ratio
    0.1f,                // Near plane
    100.0f               // Far plane
);

glm::mat4 mvp = projection * view * model;

// Callback to resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Error-checking function
void checkShaderCompile(GLuint shader, const std::string& type) {
    int success;
    char infoLog[512];
    if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << "\n";
        }
    }
    else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
        }
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Request OpenGL 3.3 Core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Modern OpenGL Triangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Define triangle vertices
    GLfloat vertices[] = {
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f // bottom right
    };

    // Generate VAO and VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO then VBO and upload data
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attribute layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const std::string vertexShaderSourceStr = get_file_contents("../../../src/shaders/vertexShader.vert");
    const std::string fragmentShaderSourceStr = get_file_contents("../../../src/shaders/potentiometerShader.frag");
    // Vertex Shader source
    const GLchar* vertexShaderSource = vertexShaderSourceStr.c_str();

    // Fragment Shader source
    const GLchar* fragmentShaderSource = fragmentShaderSourceStr.c_str();

	// Print shader sources for debugging
    //std::cout << "Vertex Shader:\n" << vertexShaderSourceStr << std::endl;
    //std::cout << "Fragment Shader:\n" << fragmentShaderSourceStr << std::endl;

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompile(vertexShader, "VERTEX");

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompile(fragmentShader, "FRAGMENT");

    // Link shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    GLfloat uStateLoc = glGetUniformLocation(shaderProgram, "u_State");
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "mvp");
    checkShaderCompile(shaderProgram, "PROGRAM");

    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Serial buffer
    GLchar buffer[2];

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        //GLuint state = arduino.readState();
        //std::cout << "Arduino state: " << state << std::endl;

        GLfloat potValue = arduino.readPot();
 
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Rendering commands
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        glUseProgram(shaderProgram);
        glUniform1f(uStateLoc, potValue);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(mvp));
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

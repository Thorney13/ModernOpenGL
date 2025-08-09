#include "utils/arduinoController.h"
#include "utils/fileUtils.h"
#include "utils/textureUtils.h"
#include "utils/inputUtils.h"
#include "utils/cameraUtils.h"
#include "utils/profilingUtils.h"
#include "meshes/cubeData.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//const char* portName = "\\\\.\\COM3"; // If your device is on COM4
//ArduinoController arduino(portName);

int windowWidth = 800;
int windowHeight = 600;

glm::mat4 model = glm::mat4(1.0f); // Identity matrix for model transformation
glm::mat4 view = getViewMatrix(); // Get initial view matrix from cameraUtils
glm::mat4 projection = glm::perspective(fov, (float)windowWidth / (float)windowHeight, nearPlane, farPlane);
glm::mat4 mvp = projection * view * model;

void  updateDeltaTime() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame; // Calculate time difference
	lastFrame = currentFrame; // Update last frame time
}

// Callback to resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

	windowWidth = width;
    windowHeight = height;

    // Recalculate projection matrix with new aspect ratio
    projection = glm::perspective(
        glm::radians(45.0f),
        (float)width / (float)height,
        0.1f,
        100.0f
    );

    // Recalculate MVP matrix
    mvp = projection * view * model;
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
    glfwSwapInterval(0); // Disable V-Sync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // If using docking branch:
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

	glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glDepthFunc(GL_LESS);

    // Generate VAO, VBO and EBO
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO then VBO and upload data
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // Vertex attribute layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Load shaders
    const std::string vertexShaderSourceStr = get_file_contents("../../../src/shaders/vertexShader.vert");
    const std::string fragmentShaderSourceStr = get_file_contents("../../../src/shaders/fragmentShader.frag");
    const GLchar* vertexShaderSource = vertexShaderSourceStr.c_str();
    const GLchar* fragmentShaderSource = fragmentShaderSourceStr.c_str();
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


    //GLfloat uStateLoc = glGetUniformLocation(shaderProgram, "u_State");
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "mvp");

    checkShaderCompile(shaderProgram, "PROGRAM");

    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Load texture using stb_image instead of gli
    GLuint textureID = 0;
    
    // Function to load texture with stb_image
	textureID = loadTexture("../../../src/textures/brick_BC.png");
  
    // Create fallback texture if loading failed
	if (textureID == 0) {
		textureID = createFallbackTexture();
	}

    // Serial buffer
    GLchar buffer[2];

	Profiler profiler; // Initialize profiler

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

		updateDeltaTime(); // Update delta time
		processInput(window); // Process input for camera movement
        profiler.frame();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        profiler.showOverlay();

        //GLuint state = arduino.readState();
        //std::cout << "Arduino state: " << state << std::endl;
        //GLfloat potValue = arduino.readPot();

        // Rendering commands
        ImGui::Render();
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = (float)glfwGetTime();
		float rotationSpeed = 0.5f; // Speed of rotation
		float rotationAngle = rotationSpeed * currentTime; // Increment rotation angle
		model = glm::rotate(glm::mat4(1.0f), rotationAngle, glm::vec3(1.0f, 1.0f, 1.0f)); // Rotate around Y-axis
        view = getViewMatrix(); // Update view matrix based on camera position and direction
		projection = glm::perspective(fov, (float)windowWidth / (float)windowHeight, nearPlane, farPlane); // Update projection matrix
		mvp = projection * view * model; // Update MVP matrix

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
        //glUniform1f(uStateLoc, potValue);

        if (textureID != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glUniform1i(glGetUniformLocation(shaderProgram, "u_Texture"), 0);
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

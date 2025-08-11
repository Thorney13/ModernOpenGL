#include "utils/arduino/arduinoController.h"
#include "scene/camera.h"
#include "utils/profilingUtils.h"
#include "rendering/meshes/cubeData.h"
#include "rendering/meshes/pyramidData.h"
#include "scene/gameObject.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//const char* portName = "\\\\.\\COM3"; // If your device is on COM4
//ArduinoController arduino(portName);

Camera camera;

int windowWidth = 800;
int windowHeight = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
bool rightMousePressed = false;
double lastX, lastY;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = camera.getViewMatrix();
glm::mat4 projection = camera.getProjectionMatrix((float)windowWidth / (float)windowHeight);
glm::mat4 mvp = projection * view * model;

void  updateDeltaTime() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}


void processInput(GLFWwindow* window) {
    float cameraSpeed = 2.5f * deltaTime;

    // Forward / Back
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboardInput(Camera::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboardInput(Camera::BACKWARD, deltaTime);

    // Left / Right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboardInput(Camera::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboardInput(Camera::LEFT, deltaTime);

    // Up / Down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.processKeyboardInput(Camera::UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.processKeyboardInput(Camera::DOWN, deltaTime);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMousePressed = true;
        firstMouse = true; // Reset first mouse flag when right button is pressed
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide cursor and capture mouse movement
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMousePressed = false;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Reset cursor mode
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!rightMousePressed) return; // Only process if right mouse button is pressed

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false; // Reset first mouse flag
        return;
    }

    float xoffset = float(xpos - lastX);
    float yoffset = float(lastY - ypos); // Invert y-axis for natural movement

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.processMouseScroll(float(yoffset));
}

// Callback to resize viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

	windowWidth = width;
    windowHeight = height;

    // Recalculate projection matrix with new aspect ratio
    projection = camera.getProjectionMatrix((float)windowWidth / (float)windowHeight);

    // Recalculate MVP matrix
    mvp = projection * view * model;
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
    glfwSetScrollCallback(window, scroll_callback);

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

	Mesh cube(cubeVertices, cubeIndices); // Create a cube mesh
	Mesh pyramid(pyramidVertices, pyramidIndices); // Create a pyramid mesh

    
    // Instead of all your shader compilation code:
    Shader* defaultShader = new Shader("../../../src/rendering/shaders/vertexShader.vert", "../../../src/rendering/shaders/fragmentShader.frag");

    Texture brickTexture("../../../src/rendering/textures/brick_BC.png");
	Texture woodTexture("../../../src/rendering/textures/wood_BC.png");

    Material brickMaterial(defaultShader);
    Material woodMaterial(defaultShader);

    brickMaterial.addTexture("u_Texture", brickTexture);
	woodMaterial.addTexture("u_Texture", woodTexture);


    if(!brickTexture.isLoaded()) {
        std::cerr << "Failed to load texture\n";
		brickTexture = Texture::createFallback();
	}

	GameObject cubeObject(&cube, &brickMaterial);
	cubeObject.setPosition(glm::vec3(-1.5f, 0.0f, 0.0f));
	cubeObject.getModelMatrix();

	GameObject pyramidObject(&pyramid, &woodMaterial);
	pyramidObject.setPosition(glm::vec3(1.5f, 0.0f, 0.0f));
	pyramidObject.getModelMatrix();

    Profiler profiler;

    //GLchar buffer[2];

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

        ImGui::Render();
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float currentTime = (float)glfwGetTime();
		float rotationSpeed = 20.0f;
		float rotationAngle = rotationSpeed * currentTime;

        cubeObject.setRotation(glm::vec3(rotationAngle, rotationAngle, rotationAngle));
        cubeObject.getModelMatrix();

        pyramidObject.setRotation(glm::vec3(-rotationAngle, -rotationAngle, -rotationAngle));
		pyramidObject.getModelMatrix();

        view = camera.getViewMatrix();
        projection = camera.getProjectionMatrix((float)windowWidth / (float)windowHeight);

        glm::mat4 viewProjection = projection * view;

        cubeObject.draw(viewProjection);
        pyramidObject.draw(viewProjection);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

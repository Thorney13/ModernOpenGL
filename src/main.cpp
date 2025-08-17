#include "utils/arduino/arduinoController.h"
#include "utils/profilingUtils.h"
#include "rendering/meshes/cubeData.h"
#include "rendering/meshes/pyramidData.h"
#include "rendering/renderer.h"
#include "core/window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//const char* portName = "\\\\.\\COM3"; // If your device is on COM4
//ArduinoController arduino(portName);

Camera camera;

int windowWidth = 800;
int windowHeight = 600;

Window window(windowWidth, windowHeight, "Modern OpenGL");

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
bool rightMousePressed = false;
double lastX, lastY;

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = camera.getViewMatrix();
glm::mat4 projection = camera.getProjectionMatrix((float)windowWidth / (float)windowHeight);
glm::mat4 mvp = projection * view * model;

void updateDeltaTime() {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
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

void input(GLFWwindow* window) {
    float cameraSpeed = 2.5f * deltaTime;
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

int main() {

    window.initialise();
    window.setMouseButtonCallback(mouse_button_callback);
    window.setCursorPosCallback(cursor_position_callback);
    window.setScrollCallback(scroll_callback);

    window.setResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
        projection = camera.getProjectionMatrix((float)w / (float)h);
        mvp = projection * view * model;
        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.getGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

	Mesh cube(cubeVertices, cubeIndices);
	Mesh pyramid(pyramidVertices, pyramidIndices);

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

	Scene mainScene;
	mainScene.setActiveCamera(&camera);
	mainScene.addGameObject(&cubeObject);
	mainScene.addGameObject(&pyramidObject);

	Renderer renderer;
	renderer.initialize();

    Profiler profiler;

    while (!window.shouldClose()) {
        if (glfwGetKey(window.getGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.setShouldClose(true);

        updateDeltaTime();
        input(window.getGLFWWindow());

        profiler.frame();

        mainScene.update();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        profiler.showOverlay();
        ImGui::Render();
        
        renderer.beginFrame();
        renderer.render(mainScene, window);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        renderer.endFrame();

        window.swapBuffers();
        window.pollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

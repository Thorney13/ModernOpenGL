#include "utils/arduino/arduinoController.h"
#include "utils/profilingUtils.h"
#include "rendering/meshes/cubeData.h"
#include "rendering/meshes/pyramidData.h"
#include "rendering/renderer.h"
#include "input/inputManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//const char* portName = "\\\\.\\COM3"; // If your device is on COM4
//ArduinoController arduino(portName);
int windowWidth = 800;
int windowHeight = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Window window(windowWidth, windowHeight, "Modern OpenGL");
Camera camera;
InputManager input;
Scene mainScene;

void updateDeltaTime() {
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

int main() {
    window.initialise();
    input.initialise(&window, &camera, &mainScene);

    window.setResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
        });

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

    std::string shaderPath = "../../../src/rendering/shaders/";
    std::string texturePath = "../../../src/rendering/textures/";

    Shader* defaultShader = new Shader(shaderPath + "vertexShader.vert", shaderPath + "fragmentShader.frag");

    Texture brickTexture(texturePath + "brick_BC.png");
	Texture woodTexture(texturePath + "wood_BC.png");

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

	mainScene.setActiveCamera(&camera);
	mainScene.addGameObject(&cubeObject);
	mainScene.addGameObject(&pyramidObject);

	Renderer renderer;
	renderer.initialize();
    renderer.setClearColor(glm::vec4(0.2f, 0.3f, 0.4f, 1.0f));

    Profiler profiler;

    while (!window.shouldClose()) {
        updateDeltaTime();
        input.processInput(deltaTime);

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

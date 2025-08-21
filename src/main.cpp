#include "utils/arduino/arduinoController.h"
#include "rendering/meshes/cubeData.h"
#include "rendering/meshes/pyramidData.h"
#include "rendering/renderer.h"
#include "core/inputManager.h"
#include "core/timeManager.h"
#include "gui/imGuiLayer.h"


//const char* portName = "\\\\.\\COM3"; // If your device is on COM4
//ArduinoController arduino(portName);
int windowWidth = 800;
int windowHeight = 600;

Window window(windowWidth, windowHeight, "Modern OpenGL");
Camera camera;
InputManager input;
Scene mainScene;
TimeManager timeManager;

int main() {
    window.initialise();
    input.initialise(&window, &camera, &mainScene);

    window.setResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
        });

    imGui gui;
    Profiler profiler;

    gui.initialise(window.getGLFWWindow());

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
    renderer.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    while (!window.shouldClose()) {
        timeManager.update();
        float deltaTime = timeManager.getDeltaTime();
        input.processInput(deltaTime);

        gui.updateProfiler();
        mainScene.update();

        gui.beginFrame();
        renderer.beginFrame();
        renderer.render(mainScene, window);
        gui.endFrame();

        renderer.endFrame();

        window.swapBuffers();
        window.pollEvents();
    }
    return 0;
}

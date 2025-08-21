#include "utils/arduino/arduinoController.h"
#include "rendering/meshes/cubeData.h"
#include "rendering/meshes/pyramidData.h"
#include "rendering/meshes/planeData.h"
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

Shader* shader3D = nullptr;
Shader* defaultShader = nullptr;

enum class RenderMode {
    MODE_3D,
    MODE_SHADERTOY
};

RenderMode currentMode = RenderMode::MODE_SHADERTOY;

void static setupResources()
{
    if (currentMode == RenderMode::MODE_3D)
    {
        std::string shaderPath = "../../../src/rendering/shaders/";
        std::string texturePath = "../../../src/rendering/textures/";

        shader3D = new Shader(shaderPath + "vertexShader.vert", shaderPath + "fragmentShader.frag");

        Mesh* cube = new Mesh(cubeVertices, cubeIndices);
        Mesh* pyramid = new Mesh(pyramidVertices, pyramidIndices);

        Texture* brickTexture = new Texture(texturePath + "brick_BC.png");
        Texture* woodTexture = new Texture(texturePath + "wood_BC.png");

        Material* brickMaterial = new Material(shader3D);
        Material* woodMaterial = new Material(shader3D);

        brickMaterial->addTexture("u_Texture", *brickTexture);
        woodMaterial->addTexture("u_Texture", *woodTexture);

        if (!brickTexture->isLoaded()) {
            std::cerr << "Failed to load texture\n";
            *brickTexture = Texture::createFallback();
        }

        GameObject* cubeObject = new GameObject(cube, brickMaterial);
        cubeObject->setPosition(glm::vec3(-1.5f, 0.0f, 0.0f));
        cubeObject->getModelMatrix();

        GameObject* pyramidObject = new GameObject(pyramid, woodMaterial);
        pyramidObject->setPosition(glm::vec3(1.5f, 0.0f, 0.0f));
        pyramidObject->getModelMatrix();

        mainScene.setActiveCamera(&camera);
        mainScene.addGameObject(cubeObject);
        mainScene.addGameObject(pyramidObject);
    }
    else
    {
        std::string shaderPath = "../../../src/rendering/shaders/shaderToy/";

        defaultShader = new Shader(shaderPath + "default.vert", shaderPath + "default.frag");

        Mesh* fullscreenQuad = new Mesh(quadVertices, quadIndices);
        Material* shaderToyMaterial = new Material(defaultShader);

        GameObject* shaderQuad = new GameObject(fullscreenQuad, shaderToyMaterial);
        shaderQuad->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        mainScene.setActiveCamera(&camera);
        mainScene.addGameObject(shaderQuad);
    }
}

void static updateScene() {
    if (currentMode == RenderMode::MODE_3D) {
    }
    else {
        float totalTime = static_cast<float>(glfwGetTime());
        if (defaultShader) {
            defaultShader->setFloat("iTime", totalTime);
            defaultShader->setVec2("iResolution", glm::vec2(windowWidth, windowHeight));
        }
    }
}

int main() {
    window.initialise();
    input.initialise(&window, &camera, &mainScene);

    window.setResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
        });

    imGui gui;
    Profiler profiler;

    gui.initialise(window.getGLFWWindow());

    setupResources();

	Renderer renderer;
	renderer.initialize();
    renderer.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    while (!window.shouldClose()) {
        timeManager.update();
        float deltaTime = timeManager.getDeltaTime();

        input.processInput(deltaTime);

        gui.updateProfiler();

        updateScene();

        mainScene.update();
        gui.beginFrame();
        renderer.beginFrame();
        renderer.render(mainScene, window);
        gui.endFrame();

        renderer.endFrame();

        window.swapBuffers();
        window.pollEvents();
    }

    delete shader3D;
    delete defaultShader;

    return 0;
}

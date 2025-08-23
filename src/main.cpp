#include "utils/arduino/arduinoController.h"
#include "rendering/meshes/cubeNormal.h"
#include "rendering/meshes/cubeSimple.h"
#include "rendering/meshes/pyramidData.h"
#include "rendering/meshes/planeData.h"
#include "rendering/renderer.h"
#include "core/inputManager.h"
#include "core/timeManager.h"
#include "gui/imGuiLayer.h"
#include "rendering/lightObject.h"

int windowWidth = 800;
int windowHeight = 600;

Window window(windowWidth, windowHeight, "Modern OpenGL");
Camera camera;
InputManager input;
Scene mainScene;
TimeManager timeManager;
GameObject* lightMain = nullptr;
GameObject* cubeObject = nullptr;

Shader* shader3D = nullptr;
Shader* defaultShader = nullptr;

enum class RenderMode {
    MODE_3D,
    MODE_SHADERTOY
};

//RenderMode currentMode = RenderMode::MODE_SHADERTOY;
RenderMode currentMode = RenderMode::MODE_3D;

void static setupResources()
{
    if (currentMode == RenderMode::MODE_3D)
    {
        std::string shaderPath = "../../../src/rendering/shaders/";

        shader3D = new Shader(shaderPath + "lighting/phong.vert", shaderPath + "lighting/phong.frag");
        defaultShader = new Shader(shaderPath + "shaderToy/default.vert", shaderPath + "shaderToy/default.frag");

        Mesh* cube = new Mesh(cubeNormalVertices, cubeNormalIndices);
        lightObject* light = new lightObject(cubeSimpleVertices, cubeSimpleIndices);

        Material* brickMaterial = new Material(shader3D);
        Material* lightMaterial = new Material(defaultShader);

        cubeObject = new GameObject(cube, brickMaterial);
        cubeObject->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        cubeObject->getModelMatrix();

        lightMain = new GameObject(light, lightMaterial);
        lightMain->setPosition(glm::vec3(1.0f, 1.0f, 1.0f));
        lightMain->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
        lightMain->getModelMatrix();

        mainScene.setActiveCamera(&camera);
        mainScene.addGameObject(lightMain);
        mainScene.addGameObject(cubeObject);

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
        mainScene.update();
        shader3D->setVec3("lightPos", lightMain->getPosition());
        shader3D->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader3D->setVec3("objectColor", glm::vec3(0.5f, 0.7f, 0.3f));
    }
    else {
        float totalTime = static_cast<float>(glfwGetTime());
        if (defaultShader) {
            defaultShader->setFloat("iTime", totalTime);
            defaultShader->setVec2("iResolution", glm::vec2(windowWidth, windowHeight));
            defaultShader->setVec3("camPos", camera.getPosition());
            defaultShader->setVec3("camTarget", camera.getFront());
        }
    }
}

int main() {
    window.initialise();

    setupResources();

    input.initialise(&window, &camera, &mainScene, lightMain);

    window.setResizeCallback([](int w, int h) {
        glViewport(0, 0, w, h);
        });

    imGui gui;
    Profiler profiler;

    gui.initialise(window.getGLFWWindow());

	Renderer renderer;
	renderer.initialize();
    renderer.setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    while (!window.shouldClose()) {
        timeManager.update();
        float deltaTime = timeManager.getDeltaTime();

        input.processInput(deltaTime);

        gui.updateProfiler();

        updateScene();

        gui.beginFrame();
        renderer.beginFrame();
        renderer.render(mainScene, window);
        gui.endFrame();

        renderer.endFrame();

        window.swapBuffers();
        window.pollEvents();
    }

    mainScene.cleanup();
    
    delete shader3D;
    delete defaultShader;
    lightMain = nullptr;
    cubeObject = nullptr;

    return 0;
}

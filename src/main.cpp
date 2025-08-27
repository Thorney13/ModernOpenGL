#include "rendering/renderer.h"
#include "core/inputManager.h"
#include "core/timeManager.h"
#include "gui/imGuiLayer.h"
#include "core/resourceManager.h"

int windowWidth = 800;
int windowHeight = 600;

Window window(windowWidth, windowHeight, "Modern OpenGL");
Camera camera;
InputManager input;
Scene mainScene;
TimeManager timeManager;
std::shared_ptr<GameObject> lightMain = nullptr;
std::shared_ptr<GameObject> cubeObject = nullptr;

enum class RenderMode {
    MODE_3D,
    MODE_SHADERTOY
};

//RenderMode currentMode = RenderMode::MODE_SHADERTOY;
RenderMode currentMode = RenderMode::MODE_3D;

void static setupResources()
{
    ResourceManager* rm = ResourceManager::getInstance();
    rm->initialize();

    if (currentMode == RenderMode::MODE_3D)
    {
        auto phongShader = rm->getShader("phong");
        auto defaultShader = rm->getShader("default");
        auto cube = rm->getMesh("cube");
        auto light = rm->getLight("lightCube");
        auto brickMaterial = rm->getMaterial("defaultLit");
        auto lightMaterial = rm->getMaterial("unlit");

        cubeObject = std::make_shared<GameObject>(cube, brickMaterial);
        cubeObject->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        cubeObject->setAutoRotate(true);

        lightMain = std::make_shared<GameObject>(light, lightMaterial);
        lightMain->setPosition(glm::vec3(1.0f, 1.0f, 1.0f));
        lightMain->setScale(glm::vec3(0.2f, 0.2f, 0.2f));

        mainScene.setActiveCamera(&camera);
        mainScene.addGameObject(lightMain);
        mainScene.addGameObject(cubeObject);

    }
    else
    {
        auto defaultShader = rm->getShader("default");
        auto quad = rm->getMesh("quad");
        auto shaderToyMaterial = rm->getMaterial("unlit");

        auto shaderQuad = std::make_shared<GameObject>(quad, shaderToyMaterial);
        shaderQuad->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        mainScene.setActiveCamera(&camera);
        mainScene.addGameObject(shaderQuad);
    }
}

void static updateScene() {
    if (currentMode == RenderMode::MODE_3D) {
        mainScene.update();

        auto phongShader = ResourceManager::getInstance()->getShader("phong");

        phongShader->setVec3("lightPos", lightMain->getPosition());
        phongShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        phongShader->setVec3("objectColor", glm::vec3(0.5f, 0.7f, 0.3f));
        phongShader->setVec3("viewPos", camera.getPosition());
    }
    else {
        float totalTime = static_cast<float>(glfwGetTime());

        auto defaultShader = ResourceManager::getInstance()->getShader("default");

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

    input.initialise(&window, &camera, &mainScene, lightMain.get());

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

    lightMain = nullptr;
    cubeObject = nullptr;

    return 0;
}

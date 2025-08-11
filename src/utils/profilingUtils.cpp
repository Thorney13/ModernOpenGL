#include "profilingUtils.h"
#include "utils/glIncludes.h"
#include "imgui.h"
#include <iostream>

Profiler::Profiler() : avgLastTime(glfwGetTime()), avgFrames(0), avgFps(0.0f), stableFps(0.0f), stableLastTime(glfwGetTime()), stableFrames(0) {
}

void Profiler::frame() {
    avgFrames++;
    stableFrames++;
    double currentTime = glfwGetTime();
    if (currentTime - stableLastTime >= 1.0) {
        stableFps = stableFrames / float(currentTime - stableLastTime);
        stableFrames = 0;
        stableLastTime = currentTime;
    }
    if (currentTime - avgLastTime >= 3.0) {
        avgFps = avgFrames / float(currentTime - avgLastTime);
        avgFrames = 0;
        avgLastTime = currentTime;
    }
}

void Profiler::showOverlay() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.3f);
    ImGui::Begin("Performance", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
    //ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("FPS (stable): %.1f", stableFps);
    //ImGui::Text("Avg FPS (3s): %.1f", avgFps);
    ImGui::End();
}
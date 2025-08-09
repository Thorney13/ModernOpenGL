#pragma once
#include <GLFW/glfw3.h>

class Profiler {
public:
    Profiler();
    void frame();
	void showOverlay();
private:
    double avgLastTime;
    int avgFrames;
    float avgFps;
    float stableFps;
    double stableLastTime;
    int stableFrames;
};

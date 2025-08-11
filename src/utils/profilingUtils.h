#pragma once

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

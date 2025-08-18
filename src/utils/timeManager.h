#pragma once

class TimeManager {
private:
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float totalTime = 0.0f;

public:
    TimeManager() = default;
    ~TimeManager() = default;

    void update();
    float getDeltaTime() const { return deltaTime; }
    float getTotalTime() const { return totalTime; }
};
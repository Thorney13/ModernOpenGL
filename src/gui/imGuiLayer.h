#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "core/window.h"
#include "utils/profilingUtils.h"

class imGui {
private:
	Window* window;
	Profiler profiler;


public:
	imGui();
	~imGui();

	void initialise(GLFWwindow* window);
	void updateProfiler() { profiler.frame(); }
	void beginFrame();
	void endFrame();

	Profiler* getProfiler() { return &profiler; }
};
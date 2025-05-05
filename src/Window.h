#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* mWindow = nullptr;

public:
	bool init(unsigned int width, unsigned int height, std::string title);
	void mainLoop();
	void cleanup();
};

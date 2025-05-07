#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* mWindow = nullptr;
	void handleWindowCloseEvents();
	void handleKeyEvents(int key, int scancode, int action, int mods);
	void handleCursorPosEvents(double xpos, double ypos);
	void handleMouseButtonEvents(int button, int action, int mods);

public:
	bool init(unsigned int width, unsigned int height, std::string title);
	void setTitle(std::string title);
	void mainLoop();
	void cleanup();
};

#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

#include <GLFW/glfw3.h>

class Window {
private:
	GLFWwindow* mWindow = nullptr;
	const std::unordered_set<int> trackedKeys = {
		GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D,
		GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_RIGHT
	};
	std::unordered_map<int, bool> inputState;
	void handleWindowCloseEvents();
	void handleKeyEvents(int key, int scancode, int action, int mods);
	void handleCursorPosEvents(double xpos, double ypos);
	void handleMouseButtonEvents(int button, int action, int mods);
	void handleWindowSizeEvents(int width, int height);

public:
	bool init(unsigned int width, unsigned int height, std::string title);
	void setTitle(std::string title);
	void mainLoop();
	void cleanup();
};

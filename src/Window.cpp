#include "Window.h"
#include "Logger.h"

bool Window::init(unsigned int width, unsigned int height, std::string title) {
	if (!glfwInit()) {
		Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
		return false;
	}

	mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!mWindow) {
		Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(mWindow);

	glfwSetWindowUserPointer(mWindow, this);

	glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
		auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
		self->handleWindowCloseEvents();
	});

	glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
		self->handleKeyEvents(key, scancode, action, mods);
	});

	/* this one gets noisy in the logs */
	//glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos) {
	//	auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	//	self->handleCursorPosEvents(xpos, ypos);
	//});

	glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
		auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
		self->handleMouseButtonEvents(button, action, mods);
	});

	glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
		auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
		self->handleWindowSizeEvents(width, height);
	});

	Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);
	
	return true;
}

void Window::setTitle(std::string title) {
	glfwSetWindowTitle(mWindow, title.c_str());
}

void Window::mainLoop() {
	glfwSwapInterval(1);
	float color = 0.0f;

	while (!glfwWindowShouldClose(mWindow)) {
		color >= 1.0f ? color = 0.0f : color += 0.01f;
		glClearColor(color, color, color, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mWindow);

		/* poll events in a loop */
		glfwPollEvents();
	}
}

void Window::handleWindowCloseEvents() {
	Logger::log(1, "%s: Window received close event... bye!\n", __FUNCTION__);
}

void Window::handleKeyEvents(int key, int scancode, int action, int mods) {
	if (trackedKeys.find(key) != trackedKeys.end()) {
		inputState[key] = (action != GLFW_RELEASE);
	}

	const char* keyName = glfwGetKeyName(key, 0);
	const char* actionName;

	switch (action) {
		case GLFW_PRESS:
			actionName = "pressed";
			break;
		case GLFW_RELEASE:
			actionName = "released";
			break;
		case GLFW_REPEAT:
			actionName = "repeated";
			break;
		default:
			actionName = "invalid";
			break;
	}

	Logger::log(1, "%s: Key %s (%i) %s\n", __FUNCTION__, keyName, key, actionName);
}

void Window::handleCursorPosEvents(double xpos, double ypos) {
	Logger::log(1, "%s: Mouse moved (x: %f, y: %f)\n", __FUNCTION__, xpos, ypos);
}

void Window::handleMouseButtonEvents(int button, int action, int mods) {
	char* actionName;
	switch (action) {
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	default:
		actionName = "invalid";
		break;
	}

	char* buttonName;
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		buttonName = "Left";
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		buttonName = "Middle";
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		buttonName = "Right";
		break;
	default:
		buttonName = "Other";
		break;
	}

	Logger::log(1, "%s: %s mouse button (%i) %s\n", __FUNCTION__, buttonName, button, actionName);
}

void Window::handleWindowSizeEvents(int width, int height) {
	Logger::log(1, "%s: Window resized to %ix%i\n", __FUNCTION__, width, height);
}

void Window::cleanup() {
	Logger::log(1, "%s: Terminating window\n", __FUNCTION__);
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

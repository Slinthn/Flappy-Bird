#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
	bool keys[GLFW_KEY_LAST + 1], polledKeys[GLFW_KEY_LAST + 1];
	GLFWwindow* window;
	int width, height;
	Window(int width, int height, const char* title);
	void setIcon(const char* path);
	bool isOpened();
	void swapBuffers();
	void pollEvents();
	double currentTime();
	void close();
	void clear(float r, float g, float b, float a = 1);
	void start(void update(double), double fps);
	bool keyDown(int key);
	bool keyPressed(int key);
	bool keyUp(int key);
	bool keyReleased(int key);
};
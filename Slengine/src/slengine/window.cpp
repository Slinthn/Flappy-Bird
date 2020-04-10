#include "window.h"
#include <cstdlib>
#include <iostream>
#include "resource.cpp"

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Window::Window(int w, int h, const char* t) : width(w), height(h) {
	if (!glfwInit()) {
		printf("GLFW could not be initialised.\n");
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
	this->window = glfwCreateWindow(w, h, t, 0, 0);
	if (!this->window) {
		printf("A window could not be created.\n");
		exit(-1);
	}

	glfwSetWindowUserPointer(this->window, this);
	glfwMakeContextCurrent(this->window);
	glViewport(0, 0, w, h);
	if (glewInit()) { // (If not initialised correctly)
		printf("GLEW could not be initialised.\n");
		exit(-1);
	}
	
	glfwSetKeyCallback(this->window, keyCallback);
	glEnable(GL_DEPTH_TEST);

}

void Window::setIcon(const char* path) {
	GLFWimage image;
	int n;
	stbi_set_flip_vertically_on_load(0);
	image.pixels = stbi_load(path, &image.width, &image.height, &n, 0);
	glfwSetWindowIcon(this->window, 1, &image);
}

bool Window::isOpened() {
	return !glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

double Window::currentTime() {
	return glfwGetTime();
}

void Window::close() {
	glfwSetWindowShouldClose(this->window, 1);
}

void Window::clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Window::start(void update(double), double fps) {
	int frames = 0;
	double lastTime = 0, timer = 0;
	double desired = 1.0 / 60.0;
	double limiter = 0;
	double elapsed = 0;

	while (this->isOpened()) {
		double now = this->currentTime();
		double delta = now - lastTime;
		lastTime = now;
		timer += delta;
		limiter += delta;
		elapsed += delta;
		
		if (limiter > desired) {
			update(elapsed);
			frames++;
			limiter = 0;
			elapsed = 0;
		
			memset(this->polledKeys, 0, GLFW_KEY_LAST);
			this->pollEvents();
		}
		if (timer >= 1) {
			printf("Time: %fs - FPS: %i\n", timer, frames);
			timer -= 1;
			frames = 0;
		}

		int error;
		while ((error = glGetError()) != GL_NO_ERROR)
			printf("%s - %i\n", glewGetErrorString(error), error);
	}
}

bool Window::keyDown(int key) {
	return this->keys[key];
}

bool Window::keyPressed(int key) {
	return keyDown(key) && this->polledKeys[key];
}

bool Window::keyUp(int key) {
	return !keyDown(key);
}

bool Window::keyReleased(int key) {
	return keyUp(key) && this->polledKeys[key];
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_REPEAT)
		return;

	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->keys[key] = action;
	win->polledKeys[key] = 1;
}
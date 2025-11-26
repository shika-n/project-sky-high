#include "platform/window.h"
#include "macros.h"
#include <cstdint>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Tramongi {

bool Window::init(uint32_t width, uint32_t height, const char *title) {
	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, resize_callback);

	return window != nullptr;
}

void Window::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

std::vector<const char *> Window::get_required_extensions() {
	uint32_t extension_count = 0;
	auto extensions = glfwGetRequiredInstanceExtensions(&extension_count);
	return std::vector(extensions, extensions + extension_count);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::resize_callback(GLFWwindow *window, int width, int height) {
	auto instance = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
	instance->resized = true;
	DLOG("Resized to {}x{}", width, height);
}

} // namespace Tramongi

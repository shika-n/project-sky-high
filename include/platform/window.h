#pragma once

#include <cstdint>
#include <vector>
class GLFWwindow;

namespace Tramongi {

class Window {
public:
	bool init(uint32_t width, uint32_t height, const char *title);

	void run();

	std::vector<const char *> get_required_extensions();

	~Window();

private:
	GLFWwindow *window = nullptr;
	bool resized = false;

	static void resize_callback(GLFWwindow *window, int width, int height);
};

} // namespace Tramongi

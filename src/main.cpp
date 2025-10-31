#include <cstdint>
#include <exception>
#include <print>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_raii.hpp>

#include "macros.h"

constexpr uint32_t WIDTH = 1280;
constexpr uint32_t HEIGHT = 720;

class ProjectSkyHigh {
	public:
		void run() {
			init_window();
			init_vulkan();
			main_loop();
			cleanup();
		}

	private:
		GLFWwindow *window = nullptr;

		void init_window() {
			if (!glfwInit()) {
				throw std::runtime_error("Failed to initialize GLFW");
			}

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(
				WIDTH,
				HEIGHT,
				"Project Sky-High",
				nullptr,
				nullptr
			);

			glfwShowWindow(window);
		}

		void init_vulkan() {
			constexpr vk::ApplicationInfo app_info {
				.pApplicationName = "Project Sky-High",
				.applicationVersion = VK_MAKE_VERSION(0, 1, 0),
				.pEngineName = "Sky-High Engine",
				.engineVersion = VK_MAKE_VERSION(0, 1, 0),
				.apiVersion = vk::ApiVersion14,
			};
			vk::InstanceCreateInfo create_info {
				.pApplicationInfo = &app_info,
			};
			vk::raii::Context context;
			vk::raii::Instance instance(context, create_info);
		}

		void main_loop() {
			while (!glfwWindowShouldClose(window)) {
				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}

		void cleanup() {
			glfwDestroyWindow(window);

			glfwTerminate();
		}
};

int main() {
	DLOG("Running in DEBUG mode");

	ProjectSkyHigh skyhigh;

	try {
		skyhigh.run();
	} catch (const std::exception &e) {
		std::println(stderr, "Error: {}", e.what());
		return EXIT_FAILURE;
	}

	DLOG("Exited successfully");
	return EXIT_SUCCESS;
}

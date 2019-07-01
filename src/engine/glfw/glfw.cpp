#include "glfw.hpp"

namespace engine {
	namespace glfw {
		void start() {
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(400, 300, "VulkanTest", nullptr, nullptr);
		}

		void shutdown() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		//void loopStep();
	}
}
#pragma once
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace engine {
	namespace glfw {
		static GLFWwindow* window;

		void start();
		void shutdown();

		//void loopStep();
	}
}
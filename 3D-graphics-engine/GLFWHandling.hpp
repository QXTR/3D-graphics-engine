#pragma once
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "GraphicsEngineUtil.hpp"

namespace graphicsEngine {
	namespace glfwHandling {
		static GLFWwindow* window;

		void start(vulkanHandling::InitInfo*);
		void shutdown();

		int loopStep();

		void fillInitInfo(vulkanHandling::InitInfo*);
	}
}
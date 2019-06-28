#pragma once
#include "VulkanHandling.hpp"
#include "GLFWHandling.hpp"

namespace graphicsEngine {

	static int windowCloseStatus = 0;

	void start();
	void shutdown();
	void loop();
}
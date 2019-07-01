#include "engine.hpp"
#include <iostream>

namespace engine {
	void start() {
		std::cout << "start" << std::endl;
		glfw::start();
		vulkan::start();
	}

	void shutdown() {
		std::cout << "shutdown" << std::endl;
		vulkan::shutdown();
		glfw::shutdown();
	}
}
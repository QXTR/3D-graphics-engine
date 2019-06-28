#include "GraphicsEngine.hpp"

namespace graphicsEngine {

	namespace gh = glfwHandling;
	namespace vh = vulkanHandling;
	namespace vhd = vh::debug;

	void start() {
		vh::InitInfo vkInitInfo;
		vkInitInfo.usedDebugStartupFlags = vhd::STARTUP_FLAG_BITS_MAX_ENUM /*& ~vhd::STARTUP_INSTANCE_LAYERS_BIT*/ & ~vhd::STARTUP_INSTANCE_EXTENSIONS_BIT & ~vhd::STARTUP_QUEUE_FAMILIES_BIT;
		gh::start(&vkInitInfo);
		vh::start(vkInitInfo);
	}

	void shutdown() {
		vh::shutdown();
		gh::shutdown();
	}

	void loop() {
		while (!windowCloseStatus) {
			windowCloseStatus = gh::loopStep();
		}
	}
}
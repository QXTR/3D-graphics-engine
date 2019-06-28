#include <iostream>
#include "GraphicsEngine.hpp"

namespace ge = graphicsEngine;
namespace gh = ge::glfwHandling;
namespace vh = ge::vulkanHandling;
namespace vhd = vh::debug;

int main()
{
	ge::start();
	ge::loop();
	ge::shutdown();
	return 0;
}
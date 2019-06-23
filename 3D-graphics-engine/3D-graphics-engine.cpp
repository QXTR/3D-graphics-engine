#include <iostream>
#include "vulkan/vulkan.h"
#include "VulkanHandling.h"

namespace vh = graphicsEngine::vulkanHandling;

int main()
{
	vh::startVulkan(true); 
	return 0;
}
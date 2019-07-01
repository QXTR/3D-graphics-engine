#pragma once
#include <vector>
#include "vulkan/vulkan.h"

namespace engine {
	namespace vulkan {
		static VkResult result;

		static VkInstance instance;
		static VkSurfaceKHR surface;
		static std::vector<VkPhysicalDevice> physicalDevices;
		static VkDevice device;
		static VkQueue queue;

		void start();
		void shutdown();

		void createInstance();
		void createPhysicalDevices();
		/*uint32_t createDevice();
		uint32_t createQueue();
		uint32_t createSwapchain();*/

		void createApplicationInfo(VkApplicationInfo*);
		void createInstanceInfo(VkInstanceCreateInfo*, VkApplicationInfo*);

		/*uint32_t createDeviceQueueCreateInfo();
		uint32_t createDeviceCreateInfo();

		uint32_t chooseInstanceLayers();
		uint32_t chooseInstanceExtensions();*/
	}
}
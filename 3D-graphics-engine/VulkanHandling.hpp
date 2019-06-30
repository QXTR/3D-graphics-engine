#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include "GraphicsEngineUtil.hpp"
#include "VulkanHandlingDebug.hpp"

namespace graphicsEngine {
	namespace vulkanHandling {
		static VkResult result;
		static flags32 usedDebugStartupFlags = 0;

		static VkInstance instance;
		static VkSurfaceKHR surface = VK_NULL_HANDLE;
		static std::vector<VkPhysicalDevice> physicalDevices;
		static VkDevice device;
		static VkQueue queue;

		static VkApplicationInfo applicationInfo;
		static VkInstanceCreateInfo instanceInfo;
		static VkDeviceQueueCreateInfo deviceQueueInfo;
		static VkDeviceCreateInfo deviceInfo;

		static void* window = nullptr;

		static std::vector<std::vector<VkQueueFamilyProperties>> queueFamilyProperties;
		static int deviceQueueFamilyIndex = 0;
		static std::vector<float> queuePriorities = { 1.0f };

		static std::vector<VkLayerProperties> instanceLayers = {};
		static std::vector<const char*> usedInstanceLayers = {};

		static std::vector<VkExtensionProperties> instanceExtensions = {};
		static std::vector<const char*> usedInstanceExtensions = {};

		static const VkPhysicalDeviceFeatures usedFeatures = {};

		void start(InitInfo);
		void shutdown();

		void createInstance(std::function<std::vector<const char*>()>, const void*);
		void createPhysicalDevices();
		void createDevice();
		void createQueue();
		void createSwapchain();

		void createApplicationInfo();
		void createInstanceInfo(const void*);

		void createDeviceQueueCreateInfo();
		void createDeviceCreateInfo();

		void chooseInstanceLayers();
		void chooseInstanceExtensions(std::function<std::vector<const char*>()>);
	}
}
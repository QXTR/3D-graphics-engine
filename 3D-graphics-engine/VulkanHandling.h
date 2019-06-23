#pragma once
#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"

namespace graphicsEngine {
	namespace vulkanHandling {
		static bool debugFlag;
		static VkResult result;

		static VkApplicationInfo applicationInfo;
		static VkInstanceCreateInfo instanceInfo;
		static VkInstance instance;

		static uint32_t physicalDeviceCount = 0;
		static std::vector<VkPhysicalDevice> physicalDevices;
		static VkDeviceQueueCreateInfo deviceQueueInfo;
		static VkDeviceCreateInfo deviceInfo;
		static VkDevice device;

		static uint32_t instanceLayerCount = 0;
		static std::vector<VkLayerProperties> instanceLayers;

		void startVulkan(bool debugFlagInput); 

		static void createApplicationInfo();
		static void createInstanceInfo();
		static void createInstance();

		static void createPhysicalDevices();
		static void createDeviceQueueCreateInfo();
		static void createDeviceCreateInfo();
		static void createDevice();

		static void chooseInstanceLayers();


		namespace debug {
			static void printProperties();
			static void printProperties(uint32_t, const char[]);
			static void printProperties(VkPhysicalDevice&);
			static void printProperties(VkPhysicalDevice*, uint32_t);
			static void printProperties(VkQueueFamilyProperties&);
			static void printProperties(VkQueueFamilyProperties*, uint32_t);
			static void printProperties(VkLayerProperties&);
			static void printProperties(VkLayerProperties*, uint32_t);
		}
	}
}
#pragma once
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vulkan/vulkan.h>

namespace azu_engine {
	class GraphicsEngine {

	public:
		void init();
		void shutdown();
		void loop();

	private:

		GLFWwindow* window;

		VkApplicationInfo appInfo{};
		VkInstanceCreateInfo instanceInfo{};

		VkDeviceQueueCreateInfo deviceQueueInfo{};
		VkDeviceCreateInfo deviceInfo{};

		VkInstance instance;
		VkSurfaceKHR surface;
		std::vector<VkPhysicalDevice> physicalDevices;
		VkDevice device;
		VkQueue queue;

		std::vector<std::vector<VkQueueFamilyProperties>> queueFamilyProperties;
		int deviceQueueFamilyIndex = 0;
		std::vector<float> queuePriorities = { 1.0f };

		void createInstance();
		void createSurface();
		void createPhysicalDevices();
		void createDevice();
		void createQueue();
		void createSwapchain();

		void createApplicationInfo();
		void createInstanceInfo();

		void createDeviceQueueCreateInfo(VkDeviceQueueCreateInfo*);
		void createDeviceCreateInfo(VkDeviceCreateInfo*, VkDeviceQueueCreateInfo*);

		void chooseInstanceLayers();
		void chooseInstanceExtensions();
	};
}
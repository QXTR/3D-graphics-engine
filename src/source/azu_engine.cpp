#include "azu_engine.hpp"

#define PRINTL(text) std::cout << #text << std::endl;

#define ASSERT_VULKAN if(result != VK_SUCCESS) __debugbreak()

namespace azu_engine {
	void GraphicsEngine::init() {
		PRINTL(init begins)

		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(400, 300, "VulkanTest", nullptr, nullptr);

		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Azu test";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "No Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		createInstance();
		createSurface();
		createPhysicalDevices();
		createDevice();
		createQueue();
		createSwapchain();

		PRINTL(init ends)
	}

	void GraphicsEngine::loop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void GraphicsEngine::shutdown() {
		PRINTL(shutdown begins)

		glfwDestroyWindow(window);
		glfwTerminate();

		vkDeviceWaitIdle(device);
		vkDestroyDevice(device, nullptr);
		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);

		PRINTL(shutdown ends)
	}

	void GraphicsEngine::createInstance() {
		createApplicationInfo();
		createInstanceInfo();
		VkResult result;
		result = vkCreateInstance(&instanceInfo, nullptr, &instance);
		ASSERT_VULKAN;
	}

	void GraphicsEngine::createSurface() {
		VkResult result;
		result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
		ASSERT_VULKAN;
	}

	void GraphicsEngine::createPhysicalDevices() {
		uint32_t physicalDeviceCount = 0;
		VkResult result;
		result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
		ASSERT_VULKAN;

		physicalDevices.resize(physicalDeviceCount);

		result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
		ASSERT_VULKAN;
	}

	void GraphicsEngine::createDevice() {

		createDeviceQueueCreateInfo(&deviceQueueInfo);
		createDeviceCreateInfo(&deviceInfo, &deviceQueueInfo);
		VkResult result;
		result = vkCreateDevice(physicalDevices[0], &deviceInfo, nullptr, &device); //TODO civ
		ASSERT_VULKAN;
	}

	void GraphicsEngine::createQueue() {

	}

	void GraphicsEngine::createSwapchain() {

	}

	void GraphicsEngine::createApplicationInfo() {
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext = nullptr;
		appInfo.pApplicationName = "VulkanTest";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
		appInfo.pEngineName = "3D-graphics-engine";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_1;
	}

	void GraphicsEngine::createInstanceInfo() {
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pNext = nullptr;
		instanceInfo.flags = NULL;
		instanceInfo.pApplicationInfo = &appInfo;
		instanceInfo.enabledLayerCount = 0; //usedInstanceLayers.size();
		instanceInfo.ppEnabledLayerNames = nullptr; //usedInstanceLayers.data();
		instanceInfo.enabledExtensionCount = 0; //usedInstanceExtensions.size();
		instanceInfo.ppEnabledExtensionNames = nullptr; //usedInstanceExtensions.data();
	}

	void GraphicsEngine::createDeviceQueueCreateInfo(VkDeviceQueueCreateInfo* deviceQueueInfo) {
		std::vector<uint32_t> queueFamilyCounts;

		for (auto physicalDevice : physicalDevices) {
			uint32_t dataI = 0;
			std::vector<VkQueueFamilyProperties> dataV;
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &dataI, nullptr);
			dataV.resize(dataI);
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &dataI, dataV.data());
			queueFamilyCounts.push_back(dataI);
			queueFamilyProperties.push_back(dataV);
		}

		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[0], &queueFamilyCounts[0], queueFamilyProperties[0].data());

		deviceQueueInfo->sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueInfo->pNext = nullptr;
		deviceQueueInfo->flags = NULL;
		deviceQueueInfo->queueFamilyIndex = deviceQueueFamilyIndex;			//TODO civ
		deviceQueueInfo->queueCount = 1;										//TODO civ
		deviceQueueInfo->pQueuePriorities = queuePriorities.data();

	}

	void GraphicsEngine::createDeviceCreateInfo(VkDeviceCreateInfo* deviceInfo, VkDeviceQueueCreateInfo* deviceQueueInfo) {
		deviceInfo->sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo->pNext = nullptr;
		deviceInfo->flags = NULL;
		deviceInfo->queueCreateInfoCount = 1;
		deviceInfo->pQueueCreateInfos = deviceQueueInfo;
		deviceInfo->enabledLayerCount = 0;
		deviceInfo->ppEnabledLayerNames = nullptr;
		deviceInfo->enabledExtensionCount = 0;
		deviceInfo->ppEnabledExtensionNames = nullptr;
		deviceInfo->pEnabledFeatures = {};
	}

	void GraphicsEngine::chooseInstanceLayers() {

	}

	void GraphicsEngine::chooseInstanceExtensions() {

	}

}
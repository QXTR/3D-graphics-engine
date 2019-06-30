#include "VulkanHandling.hpp"


namespace graphicsEngine {
	namespace vulkanHandling {
		void start(InitInfo initInfo) {
			usedDebugStartupFlags = initInfo.usedDebugStartupFlags;
			window = initInfo.window;
			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				debug::printProperties(usedDebugStartupFlags);
			}
			void* instanceInfoPNext = nullptr;
			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				instanceInfoPNext = debug::createDebugMessengerInfo();
			}
			createInstance(initInfo.glfwExtensions, instanceInfoPNext);
			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				debug::createDebugMessenger(instance);
			}
			VkSurfaceKHR tempSurface = VK_NULL_HANDLE;
			initInfo.createSurface(&instance, &window, &tempSurface);
			surface = tempSurface;
			createPhysicalDevices();
			createDevice();
			createQueue();
			createSwapchain();
		}

		void shutdown() {
			vkDeviceWaitIdle(device);
			vkDestroyDevice(device, nullptr);
			vkDestroySurfaceKHR(instance, surface, nullptr);
			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				debug::destroyDebugMessenger(instance);
			}
			vkDestroyInstance(instance, nullptr);
		}

		void createInstance(std::function<std::vector<const char*>()> func, const void* input) {
			createApplicationInfo();
			chooseInstanceLayers();
			chooseInstanceExtensions(func);
			createInstanceInfo(input);
			result = vkCreateInstance(&instanceInfo, nullptr, &instance);
			ASSERT_VULKAN(result);
		}

		void createPhysicalDevices() {
			uint32_t physicalDeviceCount = 0;
			result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
			ASSERT_VULKAN(result);

			physicalDevices.resize(physicalDeviceCount);

			result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
			ASSERT_VULKAN(result);

			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				if (usedDebugStartupFlags & debug::STARTUP_PHYSICAL_DEVICES_BIT) {
					debug::printProperties(physicalDeviceCount, "physicalDeviceCount");
					debug::printProperties(physicalDevices.data(), physicalDeviceCount);
				}
			}
		}

		void createDevice() {
			createDeviceQueueCreateInfo();
			createDeviceCreateInfo();
			result = vkCreateDevice(physicalDevices[0], &deviceInfo, nullptr, &device); //TODO civ
			ASSERT_VULKAN(result);
		}

		void createQueue() {
			vkGetDeviceQueue(device, deviceQueueFamilyIndex, 0, &queue);
		}

		void createSwapchain() {
			VkSurfaceCapabilitiesKHR surfaceCapabilities;
			result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevices[0], surface, &surfaceCapabilities);
			ASSERT_VULKAN(result);
			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				if (usedDebugStartupFlags & debug::STARTUP_PHYSICAL_DEVICES_BIT) {
					debug::printProperties(&surfaceCapabilities);
				}
			}
		}

		void createApplicationInfo() {
			applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo.pNext = nullptr;
			applicationInfo.pApplicationName = "VulkanTest";
			applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
			applicationInfo.pEngineName = "3D-graphics-engine";
			applicationInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
			applicationInfo.apiVersion = VK_API_VERSION_1_1;
		}

		void createInstanceInfo(const void* input) {
			instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) input;
			instanceInfo.flags = NULL;
			instanceInfo.pApplicationInfo = &applicationInfo;
			instanceInfo.enabledLayerCount = usedInstanceLayers.size();
			instanceInfo.ppEnabledLayerNames = usedInstanceLayers.data();
			instanceInfo.enabledExtensionCount = usedInstanceExtensions.size();
			instanceInfo.ppEnabledExtensionNames = usedInstanceExtensions.data();
		}

		void createDeviceQueueCreateInfo() {
			std::vector<uint32_t> queueFamilyCounts;

			for(auto physicalDevice : physicalDevices) {
				uint32_t dataI = 0;
				std::vector<VkQueueFamilyProperties> dataV;
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &dataI, nullptr);
				dataV.resize(dataI);
				vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &dataI, dataV.data());
				queueFamilyCounts.push_back(dataI);
				queueFamilyProperties.push_back(dataV);
			}

			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevices[0], &queueFamilyCounts[0], queueFamilyProperties[0].data());

			deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueInfo.pNext = nullptr;
			deviceQueueInfo.flags = NULL;
			deviceQueueInfo.queueFamilyIndex = deviceQueueFamilyIndex;			//TODO civ
			deviceQueueInfo.queueCount = 1;										//TODO civ
			deviceQueueInfo.pQueuePriorities = queuePriorities.data();
		}

		void createDeviceCreateInfo() {
			deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
			deviceInfo.pNext = nullptr;
			deviceInfo.flags = NULL;
			deviceInfo.queueCreateInfoCount = 1;
			deviceInfo.pQueueCreateInfos = &deviceQueueInfo;
			deviceInfo.enabledLayerCount = 0;
			deviceInfo.ppEnabledLayerNames = nullptr;
			deviceInfo.enabledExtensionCount = 0;
			deviceInfo.ppEnabledExtensionNames = nullptr;
			deviceInfo.pEnabledFeatures = &usedFeatures;
		}

		void chooseInstanceLayers() {
			uint32_t instanceLayerCount = 0;
			result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
			ASSERT_VULKAN(result);

			instanceLayers.resize(instanceLayerCount);

			result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayers.data());
			ASSERT_VULKAN(result);

			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				if (usedDebugStartupFlags & debug::STARTUP_INSTANCE_LAYERS_BIT) {
					debug::printProperties(instanceLayerCount, "instanceLayerCount");
					debug::printProperties(instanceLayers.data(), instanceLayerCount);
				}
			}

			for (auto layer : debug::instanceLayers)
				usedInstanceLayers.push_back(layer);
		}

		void chooseInstanceExtensions(std::function<std::vector<const char*>()> glfwExtensions) {
			uint32_t instanceExtensionCount = 0;
			result = vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr);
			ASSERT_VULKAN(result);

			instanceExtensions.resize(instanceExtensionCount);

			result = vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, instanceExtensions.data());
			ASSERT_VULKAN(result);

			std::vector<const char*> temp = glfwExtensions();
			usedInstanceExtensions.swap(temp);

			if (usedDebugStartupFlags & debug::STARTUP_ACTIVE_BIT) {
				if (usedDebugStartupFlags & debug::STARTUP_INSTANCE_EXTENSIONS_BIT) {
					debug::printProperties(instanceExtensionCount, "instanceExtensionCount");
					debug::printProperties(instanceExtensions.data(), instanceExtensionCount);
				}
			}

			for (auto extension : debug::instanceExtensions)
				usedInstanceExtensions.push_back(extension);
		}
	}
}
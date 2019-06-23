#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"
#include "VulkanHandling.h"

#define ASSERT_VULKAN(val)\
		if(val != VK_SUCCESS){\
			__debugbreak();\
		}

namespace graphicsEngine {
	namespace vulkanHandling {

		void startVulkan(bool debugFlagInput) {
			debugFlag = debugFlagInput;
			if (debugFlag)
				debug::printProperties();
			createInstance();
			createPhysicalDevices();
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

		void createInstanceInfo() {
			instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceInfo.pNext = nullptr;
			instanceInfo.flags = NULL;
			instanceInfo.pApplicationInfo = &applicationInfo;
			instanceInfo.enabledLayerCount = NULL;
			instanceInfo.ppEnabledLayerNames = nullptr;
			instanceInfo.enabledExtensionCount = NULL;
			instanceInfo.ppEnabledExtensionNames = nullptr;
		}

		void createInstance() {
			createApplicationInfo();
			chooseInstanceLayers();
			createInstanceInfo();
			result = vkCreateInstance(&instanceInfo, NULL, &instance);
			ASSERT_VULKAN(result);
		}

		void createPhysicalDevices() {
			result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
			ASSERT_VULKAN(result);
			if (debugFlag)
				debug::printProperties(physicalDeviceCount, "physicalDeviceCount");

			physicalDevices.resize(physicalDeviceCount);

			result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());
			ASSERT_VULKAN(result);
			if (debugFlag)
				debug::printProperties(physicalDevices.data(), physicalDeviceCount);
		}

		void createDeviceQueueCreateInfo() {
			deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueInfo.pNext = nullptr;
			deviceQueueInfo.flags = NULL;
			deviceQueueInfo.queueFamilyIndex = 0;								//TODO civ
			deviceQueueInfo.queueCount = 1;										//TODO civ
			deviceQueueInfo.pQueuePriorities = NULL;
		}

		void createDeviceCreateInfo() {
			VkPhysicalDeviceFeatures usedFeatures = {};

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

		void createDevice() {
			result = vkCreateDevice(physicalDevices[0], &deviceInfo, nullptr, &device); //TODO civ
			ASSERT_VULKAN(result);
		}

		void chooseInstanceLayers() {
			result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, NULL);
			ASSERT_VULKAN(result);
			if (debugFlag)
				debug::printProperties(instanceLayerCount, "instanceLayerCount");

			instanceLayers.resize(instanceLayerCount);

			result = vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayers.data());
			ASSERT_VULKAN(result);
			if (debugFlag)
				debug::printProperties(instanceLayers.data(), instanceLayerCount);
		}

		namespace debug {
			static void printProperties() {
				std::cout << "No input\n" << std::endl;
			}

			static void printProperties(uint32_t input, const char name[]) {
				std::cout << name << ": " << input << "\n" << std::endl;
			}

			static void printProperties(VkPhysicalDevice& input) {
				VkPhysicalDeviceProperties properties;
				vkGetPhysicalDeviceProperties(input, &properties);
				std::cout << "deviceName:              " << properties.deviceName << std::endl;
				std::cout << "apiVersion:              " << VK_VERSION_MAJOR(properties.apiVersion) << "." << VK_VERSION_MINOR(properties.apiVersion) << "." << VK_VERSION_PATCH(properties.apiVersion) << std::endl;
				std::cout << "driverVersion:           " << properties.driverVersion << std::endl;
				std::cout << "vendorID:                " << properties.vendorID << std::endl;
				std::cout << "deviceID:                " << properties.deviceID << std::endl;
				std::cout << "deviceType:              " << properties.deviceType << std::endl;
				std::cout << "discreteQueuePriorities: " << properties.limits.discreteQueuePriorities << std::endl;

				VkPhysicalDeviceFeatures features;
				vkGetPhysicalDeviceFeatures(input, &features);
				std::cout << "geometryShader: " << features.geometryShader << std::endl;

				VkPhysicalDeviceMemoryProperties memorieProperties;
				vkGetPhysicalDeviceMemoryProperties(input, &memorieProperties);

				std::cout << std::endl;

				uint32_t queueFamilyCount = 0;
				vkGetPhysicalDeviceQueueFamilyProperties(input, &queueFamilyCount, nullptr);
				printProperties(queueFamilyCount, "queueFamilyCount");

				std::vector<VkQueueFamilyProperties> queueFamilyProperties;
				queueFamilyProperties.resize(queueFamilyCount);
				vkGetPhysicalDeviceQueueFamilyProperties(input, &queueFamilyCount, queueFamilyProperties.data());
				printProperties(queueFamilyProperties.data(), queueFamilyCount);

				std::cout << std::endl;
			}

			static void printProperties(VkPhysicalDevice* input, uint32_t size) {
				for (unsigned int i = 0; i < size; i++)
				{
					std::cout << "physicalDevice " << i << " : " << std::endl;
					printProperties(input[i]);
				}
			}

			void printProperties(VkQueueFamilyProperties& input) {
				std::cout << "VK_QUEUE_GRAPHICS_BIT:       " << ((input.queueFlags & VK_QUEUE_GRAPHICS_BIT)) << std::endl;
				std::cout << "VK_QUEUE_COMPUTE_BIT:        " << ((input.queueFlags & VK_QUEUE_COMPUTE_BIT)) << std::endl;
				std::cout << "VK_QUEUE_TRANSFER_BIT:       " << ((input.queueFlags & VK_QUEUE_TRANSFER_BIT)) << std::endl;
				std::cout << "VK_QUEUE_SPARSE_BINDING_BIT: " << ((input.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)) << std::endl;
				std::cout << "queueCount:                  " << input.queueCount << std::endl;
				std::cout << "timestampValidBits:          " << input.timestampValidBits << std::endl;
				std::cout << "minImageTransferGranularity: " << input.minImageTransferGranularity.width << "," << input.minImageTransferGranularity.height << "," << input.minImageTransferGranularity.depth << std::endl;
				std::cout << std::endl;
			}

			void printProperties(VkQueueFamilyProperties* input, uint32_t size) {
				for (unsigned int i = 0; i < size; i++)
				{
					std::cout << "queueFamily " << i << " : " << std::endl;
					printProperties(input[i]);
				}
			}

			void printProperties(VkLayerProperties& input) {
				std::cout << "layerName:             " << input.layerName << std::endl;
				std::cout << "description:           " << input.description << std::endl;
				std::cout << "specVersion:           " << input.specVersion << std::endl;
				std::cout << "implementationVersion: " << input.implementationVersion << std::endl;
			}

			void printProperties(VkLayerProperties* input, uint32_t size) {
				for (unsigned int i = 0; i < size; i++)
				{
					std::cout << "layer " << i << " : " << std::endl;
					printProperties(input[i]);
				}
			}
		}
	}
}
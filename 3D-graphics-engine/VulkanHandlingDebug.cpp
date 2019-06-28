#include "VulkanHandlingDebug.hpp"

namespace graphicsEngine {
	namespace vulkanHandling {
		namespace debug {
			void printProperties(flags32 debugStartupFlagsInput) {
				std::cout << "Debug Active\n" << std::endl;
				usedDebugStartupFlags = debugStartupFlagsInput;
			}

			void printProperties(uint32_t input, const char name[]) {
				std::cout << name << ": " << input << "\n" << std::endl;
			}

			void printProperties(VkPhysicalDevice& input) {
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

				if (usedDebugStartupFlags & STARTUP_QUEUE_FAMILIES_BIT) {
					uint32_t queueFamilyCount = 0;
					vkGetPhysicalDeviceQueueFamilyProperties(input, &queueFamilyCount, nullptr);

					printProperties(queueFamilyCount, "queueFamilyCount");

					std::vector<VkQueueFamilyProperties> queueFamilyProperties;
					queueFamilyProperties.resize(queueFamilyCount);
					vkGetPhysicalDeviceQueueFamilyProperties(input, &queueFamilyCount, queueFamilyProperties.data());
					printProperties(queueFamilyProperties.data(), queueFamilyCount);

					std::cout << std::endl;
				}
			}

			void printProperties(VkPhysicalDevice* input, uint32_t size) {
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
				std::cout << std::endl;
			}

			void printProperties(VkLayerProperties* input, uint32_t size) {
				for (unsigned int i = 0; i < size; i++)
				{
					std::cout << "layer " << i << " : " << std::endl;
					printProperties(input[i]);
				}
			}

			void printProperties(VkExtensionProperties& input) {
				std::cout << "extensionName: " << input.extensionName << std::endl;
				std::cout << "specVersion:   " << input.specVersion << std::endl;
				std::cout << std::endl;
			}

			void printProperties(VkExtensionProperties* input, uint32_t size) {
				for (unsigned int i = 0; i < size; i++)
				{
					std::cout << "extension " << i << " : " << std::endl;
					printProperties(input[i]);
				}
			}
		}
	}
}
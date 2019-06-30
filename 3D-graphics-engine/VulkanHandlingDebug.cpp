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
				std::cout << "geometryShader:          " << features.geometryShader << std::endl;

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

			void printProperties(VkSurfaceCapabilitiesKHR* input) {
				std::cout << "minImageCount:             " << input->minImageCount		    << std::endl;
				std::cout << "maxImageCount:			 " << input[0].maxImageCount		    << std::endl;
				std::cout << "currentExtent:			 " << input[0].currentExtent.width << "x" <<  input[0].currentExtent.height << std::endl;
				std::cout << "minImageExtent:			 " << input[0].minImageExtent.width << "x" << input[0].minImageExtent.height << std::endl;
				std::cout << "maxImageExtent:			 " << input[0].maxImageExtent.width << "x" << input[0].maxImageExtent.height << std::endl;
				std::cout << "maxImageArrayLayers:		 " << input[0].maxImageArrayLayers	    << std::endl;
				std::cout << "supportedTransforms:		 " << input[0].supportedTransforms	    << std::endl;
				std::cout << "currentTransform:			 " << input[0].currentTransform	    << std::endl;
				std::cout << "supportedCompositeAlpha:	 " << input[0].supportedCompositeAlpha << std::endl;
				std::cout << "supportedUsageFlags:		 " << input[0].supportedUsageFlags	    << std::endl;
			}

			void createDebugMessenger(VkInstance instance) {
				auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
				result = func(instance, &debugMessengerInfo, nullptr, &debugMessenger);
				ASSERT_VULKAN(result);
			}

			void destroyDebugMessenger(VkInstance instance) {
				auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
				func(instance, debugMessenger, nullptr);
			}

			void* createDebugMessengerInfo() {
				debugMessengerInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
				debugMessengerInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT /*| VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT*/ | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
				debugMessengerInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
				debugMessengerInfo.pfnUserCallback = debugCallback;
				debugMessengerInfo.pUserData = nullptr;
				return &debugMessengerInfo;
			}
			
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData) {

				std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

				return VK_FALSE;
			}
		}
	}
}
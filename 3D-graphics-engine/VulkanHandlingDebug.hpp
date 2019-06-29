#pragma once
#include <iostream>
#include <vector>
#include "vulkan/vulkan.h"
#include "GraphicsEngineUtil.hpp"


namespace graphicsEngine {
	namespace vulkanHandling {
		namespace debug {
			enum startupBits {
				STARTUP_ACTIVE_BIT = 0x00000001,
				STARTUP_PHYSICAL_DEVICES_BIT = 0x00000002,
				STARTUP_QUEUE_FAMILIES_BIT = 0x00000004,
				STARTUP_SURFACE_CAPABILITIES_BIT = 0x00000008,
				STARTUP_INSTANCE_LAYERS_BIT = 0x00000010,
				STARTUP_INSTANCE_EXTENSIONS_BIT = 0x00000020,
				STARTUP_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
			};

			static flags32 usedDebugStartupFlags;

			static VkDebugUtilsMessengerEXT debugMessenger;

			static std::vector<const char*> instanceLayers = { "VK_LAYER_LUNARG_standard_validation", "VK_LAYER_KHRONOS_validation" };
			static std::vector<const char*> instanceExtensions = { VK_EXT_DEBUG_UTILS_EXTENSION_NAME };

			void printProperties(flags32);
			void printProperties(uint32_t, const char[]);
			void printProperties(VkPhysicalDevice&);
			void printProperties(VkPhysicalDevice*, uint32_t);
			void printProperties(VkQueueFamilyProperties&);
			void printProperties(VkQueueFamilyProperties*, uint32_t);
			void printProperties(VkLayerProperties&);
			void printProperties(VkLayerProperties*, uint32_t);
			void printProperties(VkExtensionProperties&);
			void printProperties(VkExtensionProperties*, uint32_t);
			void printProperties(VkSurfaceCapabilitiesKHR*);

			void createDebugMessenger();

			void createDebugMessengerInfo();

			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
				VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
				VkDebugUtilsMessageTypeFlagsEXT messageType,
				const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
				void* pUserData);
		}
	}
}
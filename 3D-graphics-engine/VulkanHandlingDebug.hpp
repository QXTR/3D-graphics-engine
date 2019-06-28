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
				STARTUP_INSTANCE_LAYERS_BIT = 0x00000008,
				STARTUP_INSTANCE_EXTENSIONS_BIT = 0x00000010,
				STARTUP_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
			};

			static flags32 usedDebugStartupFlags;

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
		}
	}
}
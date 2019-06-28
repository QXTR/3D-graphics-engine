#pragma once
#include <functional>

#define ASSERT_VULKAN(val)\
		if(val != VK_SUCCESS){\
			__debugbreak();\
		}

namespace graphicsEngine {
	typedef uint8_t flags8;
	typedef uint16_t flags16;
	typedef uint32_t flags32;
	typedef uint64_t flags64;
	namespace vulkanHandling {
		struct InitInfo {
			flags32 usedDebugStartupFlags = 0;// 
			std::function<void(void* instance, void* surface)> createSurface = nullptr;
		};
	}
}
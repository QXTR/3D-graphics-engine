#include <functional>
#include <vector>

namespace engine {
	struct VulkanInitInfo {
		std::function<std::vector<const char*>()> glfwExtensions = nullptr;
		std::function<void(void* instance, void* window, void* surface)> createSurface = nullptr;
	};
}
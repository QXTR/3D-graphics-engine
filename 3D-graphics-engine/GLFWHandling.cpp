#include "GLFWHandling.hpp"

namespace graphicsEngine {
	namespace glfwHandling {
		void start(vulkanHandling::InitInfo* initInfo) {
			glfwInit();
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

			window = glfwCreateWindow(400, 300, "VulkanTest", nullptr, nullptr);
			fillInitInfo(initInfo);
		}

		void shutdown() {
			glfwDestroyWindow(window);
		}

		int loopStep() {
			glfwPollEvents();
			return glfwWindowShouldClose(window);
		}

		void fillInitInfo(vulkanHandling::InitInfo* initInfo) {
			initInfo->window = &window;
			initInfo->createSurface = [](void* instance, void* window, void* surface) {
				VkInstance tempInstance = *static_cast<VkInstance*>(instance);
				VkResult result = glfwCreateWindowSurface(tempInstance, (GLFWwindow*)window, nullptr, (VkSurfaceKHR*)surface);
				ASSERT_VULKAN(result);
			};
			initInfo->glfwExtensions = []() {
				std::vector<const char*> extensions = {};
				uint32_t size = 0;
				const char** extensionsp = glfwGetRequiredInstanceExtensions(&size);
				extensions.reserve(size);
				for (unsigned int i = 0; i < size; i++) {
					extensions.push_back(extensionsp[i]);
				}
				return extensions;
			};
		}
	}
}
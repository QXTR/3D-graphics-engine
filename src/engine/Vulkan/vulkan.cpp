#include "vulkan.hpp"

#define ASSERT_VULKAN if(result != VK_SUCCESS) __debugbreak()

namespace engine {
	namespace vulkan {
		void start() {
			createInstance();
		}

		void shutdown() {
		}

		void createInstance() {
			VkApplicationInfo applicationInfo;
			VkInstanceCreateInfo instanceInfo;

			createApplicationInfo(&applicationInfo);
			createInstanceInfo(&instanceInfo, &applicationInfo);
			result = vkCreateInstance(&instanceInfo, nullptr, &instance);
			ASSERT_VULKAN;
		}

		void createPhysicalDevices() {
			uint32_t physicalDeviceCount = 0;
			result = vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
			ASSERT_VULKAN;
		}

		/*uint32_t createDevice();

		uint32_t createQueue();

		uint32_t createSwapchain();*/

		void createApplicationInfo(VkApplicationInfo* applicationInfo) {
			applicationInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo->pNext = nullptr;
			applicationInfo->pApplicationName = "VulkanTest";
			applicationInfo->applicationVersion = VK_MAKE_VERSION(0, 0, 0);
			applicationInfo->pEngineName = "3D-graphics-engine";
			applicationInfo->engineVersion = VK_MAKE_VERSION(0, 0, 0);
			applicationInfo->apiVersion = VK_API_VERSION_1_1;
		}

		void createInstanceInfo(VkInstanceCreateInfo* instanceInfo, VkApplicationInfo* applicationInfo) {
			instanceInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceInfo->pNext = nullptr;
			instanceInfo->flags = NULL;
			instanceInfo->pApplicationInfo = applicationInfo;
			instanceInfo->enabledLayerCount = 0; //usedInstanceLayers.size();
			instanceInfo->ppEnabledLayerNames = nullptr; //usedInstanceLayers.data();
			instanceInfo->enabledExtensionCount = 0; //usedInstanceExtensions.size();
			instanceInfo->ppEnabledExtensionNames = nullptr; //usedInstanceExtensions.data();
		}

		/*uint32_t createDeviceQueueCreateInfo();

		uint32_t createDeviceCreateInfo();

		uint32_t chooseInstanceLayers();
		
		uint32_t chooseInstanceExtensions();*/
	}
}
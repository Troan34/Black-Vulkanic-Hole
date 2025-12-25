#include "FirstApp.hpp"

namespace engine
{
	FirstApp::~FirstApp()
	{
		vkDestroyInstance(Instance, nullptr);
		
		window.~Window();

	}

	void FirstApp::InitVulkan()
	{
		CreateInstance();
	}

	void FirstApp::CreateInstance()
	{
		if (enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}

		VkApplicationInfo Info{};
		Info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		Info.pApplicationName = "Black Vulkanic Hole";
		Info.applicationVersion = VK_MAKE_VERSION(1, 4, 0);
		Info.pEngineName = "Troan Engine";
		Info.engineVersion = VK_MAKE_VERSION(1, 4, 0);
		Info.apiVersion = VK_API_VERSION_1_4;


		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &Info;

		uint32_t glfwExtensionCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		
		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}
		
		VkCall(vkCreateInstance(&createInfo, nullptr, &Instance));

		
	}

	void FirstApp::run()
	{
		while (!window.ShouldClose())
		{
			glfwPollEvents();
		}

	}
}
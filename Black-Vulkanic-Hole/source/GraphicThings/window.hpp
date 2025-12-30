#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>
#include <exception>
#include <stdexcept>

namespace engine
{
	class Window
	{
	private:
		void InitWindow();

		const int Width;
		const int Height;
		
		std::string WindowName;
		GLFWwindow* Window_;

	public:

		Window(int height, int width, std::string name);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		
		[[nodiscard]] bool inline ShouldClose() { return glfwWindowShouldClose(Window_); }
		VkExtent2D inline GetExtent() { return { static_cast<uint32_t>(Width), static_cast<uint32_t>(Height) }; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	};
}
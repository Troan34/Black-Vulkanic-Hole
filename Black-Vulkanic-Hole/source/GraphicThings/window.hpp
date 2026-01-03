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
		int width_m;
		int height_m;
		bool frameBufferResized = false;

		std::string WindowName;
		GLFWwindow* window_m;

		void InitWindow();
		static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);

		

	public:

		Window(int height_m, int width_m, std::string name);
		~Window();

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		
		[[nodiscard]] bool inline ShouldClose() { return glfwWindowShouldClose(window_m); }
		[[nodiscard]] bool inline WasWindowResized() const { return frameBufferResized; }
		void inline ResetWindowResizedFlag() { frameBufferResized = false; }

		[[nodiscard]] VkExtent2D inline GetExtent() const { return { static_cast<uint32_t>(width_m), static_cast<uint32_t>(height_m) }; }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

	};
}
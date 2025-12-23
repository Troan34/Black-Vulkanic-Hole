#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <string>

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
		
		bool inline ShouldClose() { return glfwWindowShouldClose(Window_); }


	};
}
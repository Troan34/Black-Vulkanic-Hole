#include "window.hpp"

namespace engine
{
	Window::Window(int height, int width, std::string name)
		:height_m(height), width_m(width), WindowName(name)
	{
		InitWindow();
	}

	Window::~Window()
	{
		glfwDestroyWindow(window_m);
		glfwTerminate();
	}

	void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window_m, nullptr, surface))
		{
			throw std::runtime_error("Failed to create window surface");
		}
	}

	void Window::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window_m = glfwCreateWindow(width_m, height_m, WindowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window_m, this);
		glfwSetFramebufferSizeCallback(window_m, FrameBufferResizeCallback);
	}


	void Window::FrameBufferResizeCallback(GLFWwindow* window_, int width, int height)
	{
		auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window_));
		window->frameBufferResized = true;
		window->width_m = width;
		window->height_m = height;
	}
	
}


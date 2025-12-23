#include "window.hpp"

namespace engine
{
	Window::Window(int height, int width, std::string name)
		:Height(height), Width(width), WindowName(name)
	{
		InitWindow();
	}

	Window::~Window()
	{
		glfwDestroyWindow(Window_);
		glfwTerminate();
	}

	void Window::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		Window_ = glfwCreateWindow(Width, Height, WindowName.c_str(), nullptr, nullptr);
	}
	
}


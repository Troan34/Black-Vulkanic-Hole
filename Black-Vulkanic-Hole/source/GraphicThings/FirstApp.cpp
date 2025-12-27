#include "FirstApp.hpp"

namespace engine
{
	FirstApp::~FirstApp()
	{
		window.~Window();
	}

	void FirstApp::InitVulkan()
	{
	}

	void FirstApp::run()
	{
		while (!window.ShouldClose())
		{
			glfwPollEvents();
		}

	}
}
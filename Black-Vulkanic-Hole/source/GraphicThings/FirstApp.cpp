#include "FirstApp.hpp"

namespace engine
{
	void FirstApp::run()
	{
		while (!window.ShouldClose())
		{
			glfwPollEvents();
		}

	}
}
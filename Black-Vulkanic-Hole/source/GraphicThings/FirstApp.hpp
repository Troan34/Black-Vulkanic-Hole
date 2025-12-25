#pragma once

#include "window.hpp"
#include "pipeline.hpp"

namespace engine
{
	class FirstApp
	{
	private:
		Window window{ Height, Width, "Black Hole" };
		Pipeline pipeline{};
		VkInstance Instance;

		void InitVulkan();
		void MainLoop();
		void CreateInstance();

	public:
		static constexpr int Width = 800;
		static constexpr int Height = 600;
		
		~FirstApp();

		void run();
	};
}
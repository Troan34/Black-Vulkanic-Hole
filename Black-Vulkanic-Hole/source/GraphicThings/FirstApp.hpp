#pragma once

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"

namespace engine
{
	class FirstApp
	{
	private:
		Window window{ Height, Width, "Black Hole" };
		Device device{ window };
		Pipeline pipeline{ device, Pipeline::DefaultPipelineConfigInfo(Width, Height) };

		void InitVulkan();
		void MainLoop();


	public:
		static constexpr int Width = 800;
		static constexpr int Height = 600;
		
		~FirstApp();

		void run();
	};
}
#pragma once

#include <array>

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swap_chain.hpp"

namespace engine
{
	class FirstApp
	{
	private:
		Window window{ Height, Width, "Black Hole" };
		Device device{ window };
		SwapChain swapChain{ device, window.GetExtent() };
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<Model> model;
		

		void InitVulkan();
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void DrawFrame();
		void LoadModels();
		
		
	public:
		static constexpr int Width = 800;
		static constexpr int Height = 600;
		
		FirstApp();
		~FirstApp();
		FirstApp(const FirstApp&) = delete;
		FirstApp &operator=(const FirstApp&) = delete;

		void run();
	};
}
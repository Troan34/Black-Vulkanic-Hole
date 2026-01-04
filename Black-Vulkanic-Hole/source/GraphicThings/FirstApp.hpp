#pragma once

#include <array>

#include "window.hpp"
#include "pipeline.hpp"
#include "device.hpp"
#include "swap_chain.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace engine
{
	struct SimplePushConstantData
	{
		glm::vec2 offset;
		alignas(16) glm::vec3 color;
	};

	class FirstApp
	{
	private:
		Window window{ height_m, width_m, "Black Hole" };
		Device device{ window };
		std::unique_ptr<SwapChain> swapChain;
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<Model> model;
		
		void CreatePipelineLayout();
		void CreatePipeline();
		void CreateCommandBuffers();
		void FreeCommandBuffers();
		void DrawFrame();
		void LoadModels();
		void RecreateSwapChain();
		void RecordCommandBuffer(int imageIndex);
		
		
	public:
		static constexpr int width_m = 800;
		static constexpr int height_m = 600;
		
		FirstApp();
		~FirstApp();
		FirstApp(const FirstApp&) = delete;
		FirstApp &operator=(const FirstApp&) = delete;

		void run();
	};
}